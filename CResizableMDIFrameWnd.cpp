// CResizableMDIFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include <afxpriv.h>
#include "macro_def.h"
#include "CResizableMDIFrameWnd.h"
#include "CResizableMiniDockFrameWnd.h"
#include "CResizableDockBar.h"
#include "CWndSpaceElt.h"
#include "ResizeGlobalData.h"
#include "CResizableControlBar.h"
#include "CResizableFloatWnd.h"
#include "CResizableDockState.h"

#define REG_VERSION    		"Version"
#define REG_VERSION_NO		2		// current version of docking state

extern ResizeGlobalData afxData;

static const DWORD dwMRCDockBarMap[4][2] =
{
        { AFX_IDW_DOCKBAR_TOP,      CBRS_TOP    },
        { AFX_IDW_DOCKBAR_BOTTOM,   CBRS_BOTTOM },
        { AFX_IDW_DOCKBAR_LEFT,     CBRS_LEFT   },
        { AFX_IDW_DOCKBAR_RIGHT,    CBRS_RIGHT  },
};

static BOOL MRCWriteProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, 
										LPVOID pData, DWORD nBufferSize)
{
//TRACE0("MRCWriteProfileBinary\n");
	CWinApp * pApp = AfxGetApp();
	ASSERT(pApp != NULL);
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(pApp->m_pszRegistryKey != NULL); // We must be using the registry not 
									  // INI files for binary to be supported
	LONG lRes;
	
	HKEY hSecKey = pApp->GetSectionKey(lpszSection);
	if (hSecKey == NULL)
		return FALSE;
	if (pData == NULL)
	{
		lRes = ::RegDeleteValue(hSecKey, (LPTSTR)lpszEntry);
	}
	else
	{
		lRes = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_BINARY,
								(LPBYTE)pData, nBufferSize);
	}
	RegCloseKey(hSecKey);
	return (lRes == ERROR_SUCCESS) ? TRUE : FALSE;
}


static BOOL MRCGetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry,
					LPVOID pData, DWORD nBufferSize)
{
//TRACE0("MRCGetProfileBinary\n");
	CWinApp * pApp = AfxGetApp();
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(pApp->m_pszRegistryKey != NULL); // We must be using the registry not INI files 
									 //for binary to be supported

	HKEY hSecKey = pApp->GetSectionKey(lpszSection);
	if (hSecKey == NULL)
		return FALSE;
	DWORD dwType;
	DWORD dwCount = nBufferSize;
	LONG lRes = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
					(LPBYTE)pData, &dwCount);
	RegCloseKey(hSecKey);
	ASSERT(lRes != ERROR_MORE_DATA); // Is Data in the registry larger than the buffer?
		 							 // We should have converted registry data on start up.
	if (lRes == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_BINARY);
		ASSERT(dwCount = nBufferSize); // The data should be the expected size
		return TRUE;
	}
	return FALSE;
}

static LPVOID MRCGetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, int * pBytesRead)
{
//TRACE0("MRCGetProfileBinary\n");
	CWinApp * pApp = AfxGetApp();
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(pApp->m_pszRegistryKey != NULL); // We must be using the registry not INI files 


	HKEY hSecKey = pApp->GetSectionKey(lpszSection);
	if (hSecKey == NULL)
    	return NULL;
	
	LPBYTE lpValue = NULL;
	DWORD dwType, dwCount;
	LONG lRes = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount);
	if (lRes == ERROR_SUCCESS)
	{
		lpValue = new BYTE[dwCount];
		ASSERT(dwType == REG_BINARY);
		lRes = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType, lpValue, &dwCount);
		if (lRes != ERROR_SUCCESS)
		{
			delete lpValue;			// error reading - deallocate the memory
   			lpValue = NULL;
   		}
	}
	RegCloseKey(hSecKey);

	if (pBytesRead != NULL)	   		// return length if we want this
		*pBytesRead = dwCount;

	return lpValue;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CResizableMDIFrameWnd, CMDIFrameWnd)
/////////////////////////////////////////////////////////////////////////////
// CResizableMDIFrameWnd

CResizableMDIFrameWnd::CResizableMDIFrameWnd()
{
//TRACE0("CResizableMDIFrameWnd::CResizableMDIFrameWnd\n");
}

CResizableMDIFrameWnd::~CResizableMDIFrameWnd()
{
//TRACE0("CResizableMDIFrameWnd::~CResizableMDIFrameWnd\n");
	CResizableControlBar::TidyUp();		// tidy up any outstanding control bars...
#ifdef _DEBUG
	CObArray arrWnd;
	GetFloatingBars(arrWnd);  // debug code to see what's still around !
#endif
}

BEGIN_MESSAGE_MAP(CResizableMDIFrameWnd, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CResizableMDIFrameWnd)
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CResizableMDIFrameWnd::FloatControlBarInMDIChild(CControlBar* pBar, CPoint point, DWORD dwStyle)
{
//TRACE0("CResizableMDIFrameWnd::FloatControlBarInMDIChild\n");
	ASSERT(pBar != NULL);

	// point is in screen co-ords - map to client
	::ScreenToClient(m_hWndMDIClient, &point);

	// clip to client MDI client rectangle - ensures it's going to be visible
	CRect rcMDIClient;
	::GetClientRect(m_hWndMDIClient, &rcMDIClient);
	point.x = min (point.x, rcMDIClient.right - 32);
	point.x = max (point.x, rcMDIClient.left);		
	point.y = min (point.y, rcMDIClient.bottom - 20);
	point.y = max (point.y, rcMDIClient.top);		
	
	// If the bar is already floating in an MDI child, then just move it
	// MFC has a similar optimization for CMiniDockFrameWnd 
	if (pBar->m_pDockSite != NULL && pBar->m_pDockBar != NULL)
	{
		CDockBar* pDockBar = pBar->m_pDockBar;
		ASSERT(pDockBar->IsKindOf(RUNTIME_CLASS(CDockBar)));
		CFrameWnd* pDockFrame = (CFrameWnd*)pDockBar->GetParent();
		ASSERT(pDockFrame != NULL);
		ASSERT(pDockFrame->IsKindOf(RUNTIME_CLASS(CFrameWnd)));
		if (pDockFrame->IsKindOf(RUNTIME_CLASS(CResizableFloatWnd)))
		{
		 	// already a floating as an MDI child, so just move it.
			if (pDockBar->m_bFloating && pDockBar->GetDockedCount() == 1 &&
				(dwStyle & pDockBar->m_dwStyle & CBRS_ALIGN_ANY) != 0)
		 	{
				pDockFrame->SetWindowPos(NULL, point.x, point.y, 0, 0,
							SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
				return;
			}
		}
	}

	// Create a CResizableFloatWnd, and dock the bar into it.
	CResizableFloatWnd * pDockFrame = (CResizableFloatWnd *)(RUNTIME_CLASS(CResizableFloatWnd))->CreateObject();
	ASSERT(pDockFrame != NULL);
	if (!pDockFrame->Create(this, dwStyle))
		AfxThrowResourceException();
	
	pDockFrame->SetWindowPos(NULL, point.x, point.y, 0, 0,
		SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
	
	if (pDockFrame->m_hWndOwner == NULL)
		pDockFrame->m_hWndOwner = pBar->m_hWnd;

	// Gets the dockbar created by the CResizableFloatWnd
	CDockBar* pDockBar = (CDockBar*)pDockFrame->GetDlgItem(AFX_IDW_DOCKBAR_FLOAT);
	ASSERT(pDockBar != NULL);
	ASSERT(pDockBar->IsKindOf(RUNTIME_CLASS(CDockBar)));

	ASSERT(pBar->m_pDockSite == this);
	// if this assertion occurred it is because the parent of pBar was not
	//  initially this CFrameWnd when pBar's OnCreate was called
	// (this control bar should have been created with a different
	//  parent initially)

	pDockBar->DockControlBar(pBar);
	pDockFrame->RecalcLayout();
	if (pBar->IsVisible())				// if the bar is visible...
	{
		pDockFrame->ShowWindow(SW_SHOWNA); // was SW_SHOWNA
		pDockFrame->UpdateWindow(); 
	}
}	


void CResizableMDIFrameWnd::UnFloatInMDIChild(CControlBar* pBar, CPoint point, DWORD dwStyle)
{
//TRACE0("CResizableMDIFrameWnd::UnFloatInMDIChild\n");
	ASSERT(pBar != NULL);
	ASSERT(pBar->IsFloating());
	CResizableFloatWnd * pFloatFrame = (CResizableFloatWnd *)pBar->GetParentFrame();
	ASSERT(pFloatFrame->IsKindOf(RUNTIME_CLASS(CResizableFloatWnd)));

	// point at which to float is ignored at present - use the co-ordinates of the current frame
	CRect rcMDIFloat;
	pFloatFrame->GetWindowRect(&rcMDIFloat);
	point = rcMDIFloat.TopLeft();
	
	// This is basically the code from MFC's CFrameWnd::FloatControlBar(), with the
	// test to avoid destroying/creating the floating frame window removed. 
	// Tried explicitly removing the control bar, but this doesn't work as it destroys the
	// CMDIFloatWnd, which in turn kills the child control bar. So need to create the floating
	// frame first, and then dock into this.  
	CMiniDockFrameWnd* pDockFrame = CreateFloatingFrame(dwStyle);
	ASSERT(pDockFrame != NULL);
	pDockFrame->SetWindowPos(NULL, point.x, point.y, 0, 0,
		SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
	if (pDockFrame->m_hWndOwner == NULL)
		pDockFrame->m_hWndOwner = pBar->m_hWnd;

	CDockBar* pDockBar = (CDockBar*)pDockFrame->GetDlgItem(AFX_IDW_DOCKBAR_FLOAT);
	ASSERT(pDockBar != NULL);
	ASSERT(pDockBar->IsKindOf(RUNTIME_CLASS(CDockBar)));

	ASSERT(pBar->m_pDockSite == this);
	// if this assertion occurred it is because the parent of pBar was not
	//  initially this CFrameWnd when pBar's OnCreate was called
	// (this control bar should have been created with a different
	//  parent initially)

	pDockBar->DockControlBar(pBar);
	pDockFrame->RecalcLayout();
	pDockFrame->ShowWindow(SW_SHOWNA);
	pDockFrame->UpdateWindow();
}

void CResizableMDIFrameWnd::DockControlBarLeftOf(CControlBar* pBar, CControlBar* pLeftOf)
{
//TRACE0("CResizableMDIFrameWnd::DockControlBarLeftOf\n");
    ASSERT_KINDOF(CControlBar, pBar);
    ASSERT_KINDOF(CControlBar, pLeftOf);
    
    CRect rect;
    pLeftOf->GetWindowRect(&rect);
    rect.OffsetRect(1,0);
    DWORD dwBarStyle = pLeftOf->GetBarStyle();
    for (int i = 0; i < 4; i++)
    {
        if (dwMRCDockBarMap[i][1] & dwBarStyle)
        {
            DockControlBar(pBar, dwMRCDockBarMap[i][0], &rect);
            return;
        }
    }
    TRACE("DockControlBarLeftOf() failed. Left bar has no recognized orientation\n");
    ASSERT(FALSE);
    return;
}

void CResizableMDIFrameWnd::EnableDocking(DWORD dwDockStyle)
{
//TRACE0("CResizableMDIFrameWnd::EnableDocking\n");
	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
    ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

    m_pFloatingFrameClass = RUNTIME_CLASS(CResizableMiniDockFrameWnd); // protected member
    for (int i = 0; i < 4; i++)
    {
    	if (dwMRCDockBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY)          // protected
        {
        	CDockBar* pDock = (CDockBar*)GetControlBar(dwMRCDockBarMap[i][0]);
            if (pDock == NULL)
            	{
                	pDock = new CResizableDockBar;
                    if (!pDock->Create(this,
						               WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
                                              dwMRCDockBarMap[i][1], dwMRCDockBarMap[i][0]))
                    {
                    	AfxThrowResourceException();
                    }
                }
        }
    }
}

void CResizableMDIFrameWnd::FloatControlBar(CControlBar* pBar, CPoint point, DWORD dwStyle)
{
//TRACE0("CResizableMDIFrameWnd::FloatControlBar\n");
	CFrameWnd::FloatControlBar(pBar, point, dwStyle);
	pBar->SendMessage(WM_USER_AFTERFLOAT_MSG);		// force update of float style
}

void CResizableMDIFrameWnd::TileDockedBars(DWORD dwDockStyle)
{
//TRACE0("CResizableMDIFrameWnd::TileDockedBars\n");
	for (int i = 0; i < 4; i++)
    {
    	if (dwMRCDockBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY)  //protected
        {
        	CResizableDockBar* pDock = (CResizableDockBar*)GetControlBar(dwMRCDockBarMap[i][0]);
            // ASSERT(pDock == NULL || pDock->IsKindOf(RUNTIME_CLASS(CResizableDockBar)));
            if (pDock != NULL && (pDock->m_dwStyle & dwDockStyle))
            {
            	pDock->TileDockedBars();
            }
        }
   	}
}

void CResizableMDIFrameWnd::ArrangeFloatingBars(DWORD dwOrient)
{
//TRACE0("CResizableMDIFrameWnd::ArrangeFloatingBars\n");
	CObArray arrWnd;
	GetFloatingBars(arrWnd);
	ASSERT (this->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)));
 	ASSERT(m_hWndMDIClient != NULL);
	// Use the MDI Client window - not the normal client area
	CWnd * pMDIClientWnd = CWnd::FromHandle(m_hWndMDIClient);
	CWndSpaceElt::ArrangeWindowsInWindow (pMDIClientWnd, arrWnd, dwOrient);

	// clear all the MOVED flags for sizeable windows...
	for (int i = arrWnd.GetUpperBound(); i >= 0; i--)
	{
        CResizableMiniDockFrameWnd * pFloatFrame = (CResizableMiniDockFrameWnd *) arrWnd[i]; 
        
		ASSERT(pFloatFrame->IsKindOf(RUNTIME_CLASS(CMiniDockFrameWnd)));
		pFloatFrame->ModifyStyle(CBRS_MOVED_BY_USER, 0);
	}
}

void CResizableMDIFrameWnd::ArrangeWindows(CObArray & arrWnd, DWORD dwOrient)
{
//TRACE0("CResizableMDIFrameWnd::ArrangeWindows\n");
	ASSERT (this->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)));
 	ASSERT(m_hWndMDIClient != NULL);
	// Use the MDI Client window - not the normal client area
	CWnd * pMDIClientWnd = CWnd::FromHandle(m_hWndMDIClient);
	CWndSpaceElt::ArrangeWindowsInWindow(pMDIClientWnd, arrWnd, dwOrient);
}

void CResizableMDIFrameWnd::GetFloatingBars(CObArray & arrWnd)
{
//TRACE0("CResizableMDIFrameWnd::GetFloatingBars\n");
	CPtrList & listControlBars = m_listControlBars;
	
	POSITION pos = listControlBars.GetHeadPosition();
	while (pos != NULL)
	{
		CControlBar* pBar = (CControlBar*)listControlBars.GetNext(pos);
		ASSERT(pBar != NULL);
		if (!pBar->IsDockBar() && pBar->IsFloating() && pBar->IsVisible()) 	// not a dockbar and floating....
		{
			ASSERT(pBar->m_pDockBar != NULL);
			CWnd * pFloatFrame = ((CWnd *)pBar->m_pDockBar)->GetParent(); 
			ASSERT(pBar != NULL);
			arrWnd.Add(pFloatFrame);
		}
	}
}

void CResizableMDIFrameWnd::DestroyDynamicBars()
{
//TRACE0("CResizableMDIFrameWnd::DestroyDynamicBars\n");
	CPtrList & listControlBars = m_listControlBars;
	
	CObArray arrBars;
	CResizableControlBar* pBar;
	
	// pass through the list and build an array of bars to destroy
	POSITION pos = listControlBars.GetHeadPosition();
	while (pos != NULL)
	{
		pBar = (CResizableControlBar *) listControlBars.GetNext(pos);
		ASSERT(pBar != NULL);
		if (pBar->IsKindOf(RUNTIME_CLASS(CResizableControlBar)) &&
				(pBar->m_Style & SZBARF_AUTOTIDY) != 0)
			arrBars.Add(pBar);
	}

	// now destroy these bars...
	for (int i = arrBars.GetUpperBound(); i >= 0; i--)
	{
		pBar = (CResizableControlBar *) arrBars[i];
		pBar->DestroyWindow();
	}
}

void CResizableMDIFrameWnd::SaveSizeBarState(LPCTSTR pszProfileName)
{
//TRACE0("CResizableMDIFrameWnd::SaveSizeBarState\n");
	DestroyDynamicBars();			// remove bars allocated dynamically
									// - we reload these at present
	
	CFrameWnd::SaveBarState(pszProfileName);	// save the raw states
#ifdef _VERBOSE_TRACE
	TRACE("Loading Bar Sizes\n");
#endif
	SaveBarSizes(pszProfileName, TRUE);			// save additional info
	AfxGetApp()->WriteProfileInt(pszProfileName, REG_VERSION, REG_VERSION_NO);
}

void CResizableMDIFrameWnd::LoadSizeBarState(LPCTSTR pszProfileName)
{
//TRACE0("CResizableMDIFrameWnd::LoadSizeBarState\n");
	// check the registry version. If it doesn't match, delete the previous key and return
	// this prevents us trying to load registry info from a previous version. This means that
	// bar states will be restored, but dockbars, etc will not.
	if (AfxGetApp()->GetProfileInt(pszProfileName, REG_VERSION, 0) != REG_VERSION_NO)
	{
		WriteProfileString(pszProfileName, NULL, NULL);		// this deletes this key from the registry
		return;
	}

    // Clear the dockbars' hidden lists to prevent interference with recalc layout (done by SaveBarSizes below)
	for (int i = 0; i < 4; i++)
	{
		CResizableDockBar* pDock = (CResizableDockBar*)GetControlBar(dwMRCDockBarMap[i][0]);
		if (pDock != NULL)
		{
			ASSERT(pDock->IsKindOf(RUNTIME_CLASS(CResizableDockBar)));
			pDock->m_arrHiddenBars.RemoveAll();
		}
	}

    LoadBarState(pszProfileName);
#ifdef _VERBOSE_TRACE
	TRACE("Loading Bar Sizes\n");
#endif
	SaveBarSizes(pszProfileName, FALSE);		// load the sizes back


}

void CResizableMDIFrameWnd::LoadBarState(LPCTSTR lpszProfileName)
{
//TRACE0("CResizableMDIFrameWnd::LoadBarState\n");
	CResizableDockState state;
	state.LoadState(lpszProfileName);
	SetDockState(state);
}

void CResizableMDIFrameWnd::SaveBarSizes(LPCTSTR pszSection, BOOL bSave)
{
//TRACE0("CResizableMDIFrameWnd::SaveBarSizes\n");
	
	BarSizeSaveInfo BSI;
	CResizableControlBar* pBar;
	char szBarId[20] = "BarSize_";

	CPtrArray arrFloatingBars;
	
	POSITION pos = m_listControlBars.GetHeadPosition();
	while (pos != NULL)
	{
		pBar = (CResizableControlBar *) m_listControlBars.GetNext(pos);
		ASSERT(pBar != NULL);
		if (pBar->IsKindOf(RUNTIME_CLASS(CResizableControlBar)))
		{
			UINT nID = pBar->GetDlgCtrlID();
			_itoa_s(nID, szBarId + 8, 20, 10);

			if (bSave)
			{
				BSI.VertDockSize 	= pBar->m_VertDockSize;
				BSI.HorzDockSize	= pBar->m_HorzDockSize;
				BSI.FloatSize 		= pBar->m_FloatSize;
				BSI.bMDIFloating = FALSE;
				// if floating in a MDI Float window.
				CFrameWnd * pBarFrame = pBar->GetDockingFrame();
				if (pBarFrame != NULL && pBarFrame->IsKindOf(RUNTIME_CLASS(CResizableFloatWnd)))
				{
					ASSERT(pBar->IsFloating());
					BSI.bMDIFloating = TRUE;
				}
				
				MRCWriteProfileBinary (pszSection, szBarId, &BSI, sizeof BSI);
			}
			else
			{
				if (MRCGetProfileBinary (pszSection, szBarId, &BSI, sizeof BSI))
				{
					pBar->m_VertDockSize	= BSI.VertDockSize;
					pBar->m_HorzDockSize	= BSI.HorzDockSize;
					pBar->m_FloatSize 		= BSI.FloatSize;
					
					// Now have to set the actual window size. The reason for this is
					// that the Adjustment algorithm looks at actual window rect sizes, so
					// it doesn't have to worry about borders etc.
					CSize NewSize = pBar->CalcFixedLayout(FALSE, (pBar->m_dwStyle & CBRS_ORIENT_HORZ));
					pBar->SetWindowPos(0, 0, 0, NewSize.cx, NewSize.cy, 
								SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER | SWP_NOMOVE);
					if (pBar->IsFloating())
					{
						if (BSI.bMDIFloating)	// floating in an MDI frame - do the float
						{
							// have to cast to CResizableMDIFrameWnd - as this is a CFrameWnd function
							ASSERT(this->IsKindOf(RUNTIME_CLASS(CResizableMDIFrameWnd)));
							arrFloatingBars.Add(pBar);
						}
						else
						{
							CFrameWnd * pFrame = pBar->GetParentFrame();
							if (pFrame != NULL)
								pFrame->RecalcLayout();
						}
					}
				}
#ifdef _VERBOSE_TRACE
				TRACE("Bar ID=%d, Floating(%d,%d), HorzDocked(%d,%d), VertDocked(%d.%d)\n",
						nID,
						BSI.FloatSize.cx,	BSI.FloatSize.cy,
						BSI.VertDockSize.cx, BSI.VertDockSize.cy,
						BSI.HorzDockSize.cx, BSI.HorzDockSize.cy);
#endif
			
			}

#ifdef _VERBOSE_TRACE
			CString strTitle;
			pBar->GetWindowText(strTitle);
			TRACE("%s '%s' ID=%d Float(%d,%d) Horz(%d,%d) Vert(%d,%d)\n",
					LPCTSTR(pBar->GetRuntimeClass()->m_lpszClassName),
					LPCTSTR(strTitle), nID,
					pBar->m_FloatSize.cx, pBar->m_FloatSize.cy,
					pBar->m_HorzDockSize.cx,  pBar->m_HorzDockSize.cy,
					pBar->m_VertDockSize.cx,  pBar->m_VertDockSize.cy);
#endif
		}
	}

	RecalcLayout();			// recalc the layout - so we end up with a meaningful set of bars
	if (!bSave)
	{
		for (int i = 0; i < arrFloatingBars.GetSize(); i++)
		{
			pBar = (CResizableControlBar *) arrFloatingBars[i];
			ASSERT(pBar->m_pDockContext != NULL);
			((CResizableMDIFrameWnd *)this)->FloatControlBarInMDIChild(pBar,
											pBar->m_pDockContext->m_ptMRUFloatPos);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CResizableMDIFrameWnd message handlers

void CResizableMDIFrameWnd::OnSysColorChange() 
{
//TRACE0("CResizableMDIFrameWnd::OnSysColorChange\n");
	afxData.UpdateSysColors();
	CMDIFrameWnd::OnSysColorChange();
}
