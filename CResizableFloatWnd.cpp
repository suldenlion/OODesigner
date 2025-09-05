// CResizableFloatWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CMainFrame.h"
#include "CResizableFloatWnd.h"
#include "CResizableControlBar.h"
#include "CResizableDockBar.h"

extern void AdjustForBorders(CRect& rect, DWORD dwStyle);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CResizableFloatWnd, CFrameWnd)
/////////////////////////////////////////////////////////////////////////////
// CResizableFloatWnd

CResizableFloatWnd::CResizableFloatWnd() : m_wndMDIDockBar(TRUE)
{
//TRACE0("CResizableFloatWnd::CResizableFloatWnd\n");	
	m_wndMDIDockBar.m_bAutoDelete = FALSE;
}

CResizableFloatWnd::~CResizableFloatWnd()
{
//TRACE0("CResizableFloatWnd::~CResizableFloatWnd\n");	
}


BEGIN_MESSAGE_MAP(CResizableFloatWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CResizableFloatWnd)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_GETMINMAXINFO()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResizableFloatWnd message handlers

void CResizableFloatWnd::OnSize(UINT nType, int cx, int cy) 
{
//TRACE0("CResizableFloatWnd::OnSize\n");	
    if (cx == 0 && cy == 0)
    	return;

	CDockBar* pDock = &m_wndMDIDockBar;

    // We don't support CBRS_FLOAT_MULTI
    if ((pDock->m_dwStyle & CBRS_FLOAT_MULTI) == 0)
    {
        // CMiniDockFrameWnd class assumes if there is only 1 bar, then it's at position 1
        // in the array
        CResizableControlBar* pBar = ((CResizableDockBar *)pDock)->GetFirstControlBar();
        // ignore size request if not visible....
        if (pBar != NULL && IsSizeable(pBar) && pBar->IsVisible())
        {
			CRect rect(0, 0, cx, cy);
    		AdjustForBorders(rect, pBar->m_dwStyle);

            pBar->m_FloatSize.cx = rect.Width();
            pBar->m_FloatSize.cy = rect.Height();
        }
    }
	CFrameWnd::OnSize(nType, cx, cy);	// call parent to update menu's etc.
}

void CResizableFloatWnd::OnClose() 
{
//TRACE0("CResizableFloatWnd::OnClose\n");	
	// TODO: Add your message handler code here and/or call default
	CDockBar* pDock = &m_wndMDIDockBar;

	if ((pDock->m_dwStyle & CBRS_FLOAT_MULTI) == 0)
    {
     // CMiniDockFrameWnd class assumes if there is only 1 bar, then it's at position 1
     // in the array
    	CControlBar* pBar = ((CResizableDockBar *) pDock)->GetFirstControlBar();
     	if (pBar != NULL && pBar->IsKindOf(RUNTIME_CLASS(CResizableControlBar)) )
 			if (((CResizableControlBar *)pBar)->m_Style & SZBARF_DESTROY_ON_CLOSE)
            {
 				CResizableControlBar *tBar = (CResizableControlBar *)pBar;
				if (tBar->hasDocument()) {
					if(!tBar->SaveModified()) return;
				}

				// close the Frame Window
              	CFrameWnd::OnClose();       // close the window
              	delete pBar;            // now explicitly delete the control bar
              	return;
			}
    } 

	// hide all the control bars...
    CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->SetActiveView(NULL,FALSE);

	m_wndMDIDockBar.ShowAll(FALSE);
}

void CResizableFloatWnd::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
//TRACE0("CResizableFloatWnd::OnWindowPosChanged\n");	
	CFrameWnd::OnWindowPosChanged(lpwndpos);

	if ((m_wndMDIDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0)
    {
		CResizableControlBar* pBar = ((CResizableDockBar *) &m_wndMDIDockBar)->GetFirstControlBar();
     	if (pBar != NULL)
 		{
			ASSERT(pBar->m_pDockContext != NULL);
			CRect rcWindow;
			GetWindowRect(rcWindow);
			pBar->m_pDockContext->m_ptMRUFloatPos = rcWindow.TopLeft();
 		}	
	}
}

void CResizableFloatWnd::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
//TRACE0("CResizableFloatWnd::OnGetMinMaxInfo\n");	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);

    if ((m_wndMDIDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0)
    {
		CResizableControlBar* pBar = ((CResizableDockBar *) &m_wndMDIDockBar)->GetFirstControlBar();
     	if (pBar != NULL)
 		{
			ASSERT(pBar->m_pDockContext != NULL);
            pBar->SendMessage(WM_GETMINMAXINFO, NULL, (LPARAM)lpMMI);

            CRect rect(0, 0, 0, 0);
            AdjustWindowRectEx(&rect, GetStyle(), FALSE, GetExStyle());
            lpMMI->ptMaxSize.x += rect.Width();
            lpMMI->ptMaxSize.y += rect.Height();
            lpMMI->ptMaxTrackSize.x += rect.Width();
            lpMMI->ptMaxTrackSize.y += rect.Height();
        }	
	}
}

void CResizableFloatWnd::OnSetFocus(CWnd* pOldWnd) 
{
//TRACE0("CResizableFloatWnd::OnSetFocus\n");	
    CResizableControlBar* pBar = ((CResizableDockBar *) &m_wndMDIDockBar)->GetFirstControlBar();
    if (pBar != NULL)
        pBar->SetFocus();
    else
        CFrameWnd::OnSetFocus(pOldWnd);
}

BOOL CResizableFloatWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
//TRACE0("CResizableFloatWnd::PreCreateWindow\n");	
	// Turn off the WS_EX_CLIENTEDGE style on the Frame.
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	return TRUE;
}

BOOL CResizableFloatWnd::Create(CWnd* pParent, DWORD dwBarStyle)
{
//TRACE0("CResizableFloatWnd::Create\n");	
	// set m_bInRecalcLayout to avoid flashing during creation
	// RecalcLayout will be called once something is docked
	m_bInRecalcLayout = TRUE;

	static CString strFloatClass;
	if (strFloatClass.IsEmpty())
		strFloatClass = AfxRegisterWndClass(CS_DBLCLKS);

	DWORD dwStyle = WS_CLIPCHILDREN /* | WS_CHILD */ | WS_OVERLAPPEDWINDOW | FWS_SNAPTOBARS;
	if (!CFrameWnd::Create(strFloatClass, NULL, dwStyle, rectDefault, NULL  /*(CMDIFrameWnd *)pParent)*/))
	{
		m_bInRecalcLayout = FALSE;
		return FALSE;
	}

	// Create a single dockbar for this frame with ID=AFX_IDW_DOCKBAR_FLOAT (picked up later)
	dwStyle = dwBarStyle & (CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT) ?
		CBRS_ALIGN_LEFT : CBRS_ALIGN_TOP;
	dwStyle |= dwBarStyle & CBRS_FLOAT_MULTI;

	if (!m_wndMDIDockBar.Create(pParent, WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | dwStyle, AFX_IDW_DOCKBAR_FLOAT))
	{
		m_bInRecalcLayout = FALSE;
		return FALSE;
	}
	m_wndMDIDockBar.SetParent(this);

	m_bInRecalcLayout = FALSE;
	return TRUE;			 
}


void CResizableFloatWnd::RecalcLayout(BOOL bNotify)
{
//TRACE0("CResizableFloatWnd::RecalcLayout\n");	
	if (!m_bInRecalcLayout)
	{
		CFrameWnd::RecalcLayout(bNotify);

		// syncronize window text of frame window with dockbar itself
		CString strTitle;
		m_wndMDIDockBar.GetWindowText(strTitle);
		AfxSetWindowText(m_hWnd, strTitle);
	}
}
