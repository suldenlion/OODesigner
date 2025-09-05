// CResizableMiniDockFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CMainFrame.h"
#include "CResizableMiniDockFrameWnd.h"
#include "CResizableControlBar.h"
#include "CResizableDockBar.h"
#include "ResizeGlobalData.h"

extern ResizeGlobalData afxData;

void AdjustForBorders(CRect& rect, DWORD dwStyle)
// Helper function: used below
// adjusts the size, depending on the borders specified by the CControlBar style
//------------------------------------------------------------------------------
{
//TRACE0("AdjustForBorders\n");
	if (dwStyle & CBRS_BORDER_LEFT)
		rect.left -= afxData.cxBorder2;
	if (dwStyle & CBRS_BORDER_TOP)
		rect.top -= afxData.cyBorder2;
	if (dwStyle & CBRS_BORDER_RIGHT)
		rect.right += afxData.cxBorder2;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		rect.bottom += afxData.cyBorder2;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CResizableMiniDockFrameWnd, CMiniDockFrameWnd)
/////////////////////////////////////////////////////////////////////////////
// CResizableMiniDockFrameWnd

CResizableMiniDockFrameWnd::CResizableMiniDockFrameWnd()
{
//TRACE0("CResizableMiniDockFrameWnd::CResizableMiniDockFrameWnd\n");
}

CResizableMiniDockFrameWnd::~CResizableMiniDockFrameWnd()
{
//TRACE0("CResizableMiniDockFrameWnd::~CResizableMiniDockFrameWnd\n");
}


BEGIN_MESSAGE_MAP(CResizableMiniDockFrameWnd, CMiniDockFrameWnd)
	//{{AFX_MSG_MAP(CResizableMiniDockFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
    ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCLBUTTONDOWN()
    ON_WM_WINDOWPOSCHANGED()
// 2014 OODesigner 수정 	ON_WM_NCHITTEST()
	ON_WM_MOUSEACTIVATE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

enum CResizableMiniDockFrameWnd::ContainedBarType CResizableMiniDockFrameWnd::GetContainedBarType()
{
//TRACE0("CResizableMiniDockFrameWnd::GetContainedBarType\n");
	if (m_nContainedBarType == Unknown)
	{
		m_nContainedBarType = MFCBase;
		if ((m_wndDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0) // don't handle this
	    {
	       	CResizableControlBar* pBar = ((CResizableDockBar *)(&m_wndDockBar))->GetFirstControlBar();
	        if (pBar != NULL)
			{
				if (IsSizeable(pBar))
				{		
					m_nContainedBarType = MRCSizeBar;
					GetSystemMenu(TRUE);					// reset the system menu
					
					// delete sys menu items that might be present....
					CMenu* pSysMenu = GetSystemMenu(FALSE);
					pSysMenu->DeleteMenu(SC_MAXIMIZE, MF_BYCOMMAND);
					pSysMenu->DeleteMenu(SC_MINIMIZE, MF_BYCOMMAND);
					pSysMenu->DeleteMenu(SC_RESTORE, MF_BYCOMMAND);
					pSysMenu->DeleteMenu(SC_TASKLIST, MF_BYCOMMAND);
					while (pSysMenu->DeleteMenu(0, MF_BYCOMMAND));	// remove anything with ID=0
					
					//pSysMenu->AppendMenu(MF_STRING | MF_ENABLED, SC_SIZE, "&Size");

					// if window is meant to close, ensure sysmenu has "Close" on it, not "Hide"
					// MFC4.0 replaces "Close" with "Hide"
					// extract close text from ID_FILE_CLOSE after the "\n" for the tooltip prompt
					if (!(pBar->m_Style & SZBARF_DESTROY_ON_CLOSE))
					{
						CString strHide;
						if (strHide.LoadString(AFX_IDS_HIDE))
						{
							// modify menu text to be "Hide" instrad of close
							VERIFY(pSysMenu->ModifyMenu(SC_CLOSE, MF_BYCOMMAND | MF_STRING, SC_CLOSE, strHide));  
							
							//pSysMenu->DeleteMenu(SC_CLOSE, MF_BYCOMMAND);
							//pSysMenu->AppendMenu(MF_STRING|MF_ENABLED, SC_CLOSE, strHide);
						} 
						/*
						CString strClose;
						if (strClose.LoadString(ID_FILE_CLOSE))
						{
							LPCTSTR pCloseText = strchr(strClose, '\n');
							if (pCloseText != NULL)
								pSysMenu->DeleteMenu(SC_CLOSE, MF_BYCOMMAND);
								pSysMenu->AppendMenu(MF_STRING|MF_ENABLED, SC_CLOSE, pCloseText + 1);
						} */
					}
				}
				else
				{
					if ((pBar->m_dwStyle & CBRS_SIZE_DYNAMIC))	 // dynamic bar - turn on MFS_4THICKFRAME
					{
						ModifyStyle(0, MFS_4THICKFRAME);	
						return m_nContainedBarType;
					}
			
				}
			}
		}
		if (m_nContainedBarType == MFCBase)
		{
			ModifyStyle(WS_THICKFRAME, MFS_MOVEFRAME);
		}
	}		
	// if bar is MFC bar (and not CBRS_SIZE_DYNAMIC, turn on MFS_MOVEFRAME)
	return m_nContainedBarType;
}


/////////////////////////////////////////////////////////////////////////////
// CResizableMiniDockFrameWnd message handlers

BOOL CResizableMiniDockFrameWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
//TRACE0("CResizableMiniDockFrameWnd::PreCreateWindow\n");
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= WS_CLIPCHILDREN;
    
    cs.style |= MFS_THICKFRAME | WS_THICKFRAME; 
    cs.style &= ~( MFS_MOVEFRAME | MFS_4THICKFRAME );		
    return CMiniDockFrameWnd::PreCreateWindow(cs);
}

int CResizableMiniDockFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
//TRACE0("CResizableMiniDockFrameWnd::OnCreate\n");
	if (CMiniDockFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
    m_nContainedBarType = Unknown;
	return 1;
}

void CResizableMiniDockFrameWnd::OnSize(UINT nType, int cx, int cy) 
{
//TRACE0("CResizableMiniDockFrameWnd::OnSize\n");
    if (cx == 0 && cy == 0)
    	return;

    // We don't support CBRS_FLOAT_MULTI
    if ((m_wndDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0)
    {
        // CMiniDockFrameWnd class assumes if there is only 1 bar, then it's at position 1
        // in the array
        CResizableControlBar* pBar = ((CResizableDockBar *)(&m_wndDockBar))->GetFirstControlBar();
        // ignore size request if not visible....
        if (pBar != NULL && IsSizeable(pBar) && pBar->IsVisible())
        {
			CRect rect(0, 0, cx, cy);
    		AdjustForBorders(rect, pBar->m_dwStyle);

            pBar->m_FloatSize.cx = rect.Width();
            pBar->m_FloatSize.cy = rect.Height();
        }
    }
    RecalcLayout();
}

void CResizableMiniDockFrameWnd::OnClose() 
{
//TRACE0("CResizableMiniDockFrameWnd::OnClose\n");
	if ((m_wndDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0)
    {
     // CMiniDockFrameWnd class assumes if there is only 1 bar, then it's at position 1
     // in the array
    	CControlBar* pBar = ((CResizableDockBar *) &m_wndDockBar)->GetFirstControlBar();
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
    // otherwise just show it.
    CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->SetActiveView(NULL,FALSE);

    CMiniDockFrameWnd::OnClose();
    return;
}

void CResizableMiniDockFrameWnd::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
//TRACE0("CResizableMiniDockFrameWnd::OnNcLButtonDown\n");
	enum ContainedBarType Type = GetContainedBarType();
	if (Type == MRCSizeBar)
	{
		if (nHitTest >= HTSIZEFIRST && nHitTest <= HTSIZELAST)
		{
			// special activation for floating toolbars
			ActivateTopParent();
			CMiniFrameWnd::OnNcLButtonDown(nHitTest, point);
			return;
		}
		else if (nHitTest == HTSYSMENU)
		{
			// do the system menu - ie give move,size,hide, etc options as would Win95.						
// 2014 OODesigner 수정 			InvertSysMenu();
			CPoint pt(0,0);
			ClientToScreen(&pt);
			CRect rcSysIcon;
			GetWindowRect(&rcSysIcon);
			rcSysIcon.right = rcSysIcon.left + 12;		// NB:hard-coded value for width of system icon
			rcSysIcon.bottom = pt.y;					
			
			CMenu * pSysMenu = GetSystemMenu(FALSE);
			int nCmd = pSysMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, this, & rcSysIcon);
// 2014 OODesigner 수정 			InvertSysMenu();
			if (nCmd != 0)
			{
				SendMessage(WM_SYSCOMMAND, nCmd, 0);
			}
			return;
		}
	}
	if (nHitTest == HTCAPTION)
	{
		SetForegroundWindow();
	}
	CMiniDockFrameWnd::OnNcLButtonDown(nHitTest, point);
}

UINT CResizableMiniDockFrameWnd::OnNcHitTest(CPoint point) 
{
//TRACE0("CResizableMiniDockFrameWnd::OnNcHitTest\n");
	enum ContainedBarType Type = GetContainedBarType();
	return CMiniDockFrameWnd::OnNcHitTest(point);
}

int CResizableMiniDockFrameWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
//TRACE0("CResizableMiniDockFrameWnd::OnMouseActivate\n");
	enum ContainedBarType Type = GetContainedBarType();
	if (Type == MRCSizeBar)
	{
		if (nHitTest >= HTSIZEFIRST && nHitTest <= HTSIZELAST)
			return CMiniFrameWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return CMiniDockFrameWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CResizableMiniDockFrameWnd::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
//TRACE0("CResizableMiniDockFrameWnd::OnGetMinMaxInfo\n");
	// TODO: Add your message handler code here and/or call default
	CMiniDockFrameWnd::OnGetMinMaxInfo(lpMMI);

    if ((m_wndDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0) // don't handle this
	{
	    CResizableControlBar* pBar = ((CResizableDockBar *)(&m_wndDockBar))->GetFirstControlBar();
	    if (pBar != NULL)
        {	
            if (pBar->SendMessage(WM_GETMINMAXINFO, NULL, (LPARAM)lpMMI) == 0)
            {
                CRect rect(0, 0, 0, 0);
                AdjustWindowRectEx(&rect, GetStyle(), FALSE, GetExStyle());
                lpMMI->ptMaxSize.x += rect.Width();
                lpMMI->ptMaxSize.y += rect.Height();
                lpMMI->ptMaxTrackSize.x += rect.Width();
                lpMMI->ptMaxTrackSize.y += rect.Height();
            }
    
        }
    }
}
