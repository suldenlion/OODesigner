// CResizableControlBar.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "macro_def.h"
#include "CResizableControlBar.h"
#include "CResizableDockContext.h"
#include "CResizableFloatWnd.h"
#include "CResizableMDIFrameWnd.h"
#include "CResizableMiniDockFrameWnd.h"
#include "ResizeGlobalData.h"

extern ResizeGlobalData afxData;
CObArray * CResizableControlBar::m_parrAllocBars;	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CResizableControlBar, CControlBar)
/////////////////////////////////////////////////////////////////////////////
// CResizableControlBar

CResizableControlBar::CResizableControlBar(int nStyle)
{
//TRACE0("CResizableControlBar::CResizableControlBar\n");
	m_Style = nStyle;						
    m_PrevSize.cx = 0xffff;         // dummy values so WindowPosChanged will respond correctly
    m_bPrevFloating = 3;            // neither TRUE not FALSE;

	m_FloatingPosition  = CPoint(0,0);	
	m_dwAllowDockingState = 0;
	if (nStyle & SZBARF_AUTOTIDY)
	{
		if (m_parrAllocBars == NULL)
			m_parrAllocBars = new CObArray;
		
		m_parrAllocBars->Add(this);
	}
}

CResizableControlBar::~CResizableControlBar()
{
//TRACE0("CResizableControlBar::~CResizableControlBar\n");
	// if the bar was created with this flag, then ensure it is deleted with it also.
	if (m_Style & SZBARF_AUTOTIDY)
	{
		int i;
		for (i = m_parrAllocBars->GetUpperBound(); i >= 0; i--)
			if ((*m_parrAllocBars)[i] == this)	
			{
				m_parrAllocBars->RemoveAt(i);
				break;
			}
		ASSERT(i >= 0);			// means we didn't delete this item from the list
	}

	// This loop of debug code checks that we don;t have any other references in the array.
	// This happens if we changed the auto delete flag during the lifetime of the control bar.
#ifdef _DEBUG
	if (m_parrAllocBars != NULL)
	{
		for (int i = m_parrAllocBars->GetUpperBound(); i >= 0; i--)
			ASSERT ((*m_parrAllocBars)[i] != this);	
	}
#endif

    // delete the dock context here - in an attempt to call the correct destructor
    delete (CResizableDockContext *) m_pDockContext;
    m_pDockContext = NULL;
}

void CResizableControlBar::TidyUp()
{
//TRACE0("CResizableControlBar::TidyUp\n");
// just need to delete the contents of the array - the destructor will remove the element
// from the array. 
	if (m_parrAllocBars != NULL)
	{
		for (int i = m_parrAllocBars->GetUpperBound(); i >= 0; i--)
		{
			ASSERT((*m_parrAllocBars)[i]->IsKindOf(RUNTIME_CLASS(CResizableControlBar)));
			delete ((*m_parrAllocBars)[i]);
		}
		delete m_parrAllocBars;
		m_parrAllocBars = NULL;
	}
}


BEGIN_MESSAGE_MAP(CResizableControlBar, CControlBar)
	//{{AFX_MSG_MAP(CResizableControlBar)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
    ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_BAR_HIDE, OnHide)
	ON_COMMAND(ID_BAR_ALLOWDOCKING, OnToggleAllowDocking)
	ON_COMMAND(ID_BAR_MDIFLOAT,	OnFloatAsMDI)
	ON_MESSAGE(WM_ADDCONTEXTMENUITEMS, OnAddContextMenuItems)
	ON_MESSAGE(WM_USER_AFTERFLOAT_MSG, OnAfterFloatMessage)
	ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
END_MESSAGE_MAP()

CSize CResizableControlBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
//TRACE0("CResizableControlBar::CalcFixedLayout\n");
#ifdef _VERBOSE_TRACE
	CString strTitle;
	GetWindowText(strTitle);
	TRACE("CalcFixedLayout: '%s' Horz(%d,%d)\n", LPCTSTR(strTitle), 
				m_HorzDockSize.cx, m_HorzDockSize.cy);
#endif	
	CControlBar::CalcFixedLayout(bStretch, bHorz);
    if (IsFloating())
		return m_FloatSize;

    if (bHorz)
		return m_HorzDockSize;
	else
		return m_VertDockSize;
}

void CResizableControlBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
//TRACE0("CResizableControlBar::OnUpdateCmdUI\n");
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

void CResizableControlBar::SetSizeDockStyle(DWORD dwStyle)
{
//TRACE0("CResizableControlBar::SetSizeDockStyle\n");
	m_Style = dwStyle;
}

void CResizableControlBar::EnableDocking(DWORD dwDockStyle)
{
//TRACE0("CResizableControlBar::EnableDocking\n");
    ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

    m_dwDockStyle = dwDockStyle;
    if (m_pDockContext == NULL)
    	m_pDockContext = new CResizableDockContext(this);
	
    // permanently wire the bar's owner to its current parent
	if (m_hWndOwner == NULL)
    	m_hWndOwner = ::GetParent(m_hWnd);
}

afx_msg LONG CResizableControlBar::OnAfterFloatMessage(UINT wParam, LONG lParam)
{
//TRACE0("CResizableControlBar::OnAfterFloatMessage\n");
	CWnd * pFrame = GetParentFrame();
	if (pFrame != NULL && pFrame->IsKindOf(RUNTIME_CLASS(CResizableMiniDockFrameWnd)))
		((CResizableMiniDockFrameWnd *) pFrame)->GetContainedBarType();
	
	return TRUE;			// message handled.
}

void CResizableControlBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
{
//TRACE0("CResizableControlBar::OnSizedOrDocked\n");
}

BOOL CResizableControlBar::IsProbablyFloating()
{ 
//TRACE0("CResizableControlBar::IsProbablyFloating\n");
	return (m_pDockBar == NULL || (GetBarStyle() & CBRS_FLOATING));
}	

LONG CResizableControlBar::OnAddContextMenuItems(WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu = (HMENU)lParam;		// handle of menu.
	CMenu Menu;
	Menu.Attach(hMenu);

	DWORD dwDockStyle = m_dwDockStyle & CBRS_ALIGN_ANY;
	DWORD style;
	CString strMenu;

	BOOL bMDIFloating = FALSE;
	CFrameWnd *pParentFrame = GetParentFrame();
	if (IsFloating())
	{
		if (pParentFrame != NULL && pParentFrame->IsKindOf(RUNTIME_CLASS(CResizableFloatWnd)))
		{
			bMDIFloating = TRUE;
		}
	}
	style = (bMDIFloating ? MF_STRING | MF_CHECKED : MF_STRING);
	
	// if allowed - add the float as MDI floating window
	if (m_Style & SZBARF_ALLOW_MDI_FLOAT)
	{	
		VERIFY(strMenu.LoadString(ID_BAR_MDIFLOAT));
		Menu.AppendMenu(style, ID_BAR_MDIFLOAT, strMenu);
	}
	
	if (!bMDIFloating && (dwDockStyle != 0 || m_dwAllowDockingState != 0))	// ie docking is actually allowed ...
	{
		DWORD style = (dwDockStyle != 0 ? MF_STRING | MF_CHECKED : MF_STRING);
		VERIFY(strMenu.LoadString(ID_BAR_ALLOWDOCKING));
		Menu.AppendMenu(style, ID_BAR_ALLOWDOCKING, strMenu);
	}
	VERIFY(strMenu.LoadString(ID_BAR_HIDE));
	Menu.AppendMenu(MF_STRING, ID_BAR_HIDE, strMenu);

	Menu.Detach();	// detatch MFC object
	return TRUE;
}

void CResizableControlBar::OnHide()
{
//TRACE0("CResizableControlBar::OnHide\n");
	CFrameWnd * pFrameWnd = GetParentFrame();
	pFrameWnd->ShowControlBar(this, FALSE, FALSE);
}

void CResizableControlBar::OnToggleAllowDocking()
{
//TRACE0("CResizableControlBar::OnToggleAllowDocking\n");
	CFrameWnd *pParentFrame = GetParentFrame();
	if ((m_dwDockStyle & CBRS_ALIGN_ANY) != 0)
	{											   // docking currently allowed - disable it
		m_dwAllowDockingState = m_dwDockStyle & CBRS_ALIGN_ANY;	// save previous state
		if (!IsFloating())
		{	
			ASSERT(m_pDockContext != NULL);
			m_pDockContext->ToggleDocking();
		}
		EnableDocking(0);				// disable docking
	}
	else
	{
		EnableDocking (m_dwAllowDockingState);	// re-enable docking...
	}
}

void CResizableControlBar::OnFloatAsMDI()
{
//TRACE0("CResizableControlBar::OnFloatAsMDI\n");
	ASSERT(m_Style & SZBARF_ALLOW_MDI_FLOAT);		// must have specified this

	CResizableMDIFrameWnd * pFrame = (CResizableMDIFrameWnd *) AfxGetMainWnd();
	ASSERT(pFrame != NULL);
	ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CResizableMDIFrameWnd)));

	CFrameWnd *pParentFrame = GetParentFrame();
	BOOL bMDIFloating = (IsFloating() && pParentFrame != NULL && pParentFrame->IsKindOf(RUNTIME_CLASS(CResizableFloatWnd)));
	
	ASSERT(m_pDockContext != NULL);
	
	if (bMDIFloating)
	{
		pFrame->UnFloatInMDIChild(this, m_pDockContext->m_ptMRUFloatPos);
	}
	else
	{
		pFrame->FloatControlBarInMDIChild(this, m_pDockContext->m_ptMRUFloatPos);
	}		
}

LONG CResizableControlBar::OnSetMessageString(WPARAM wParam, LPARAM lParam)
{
//TRACE0("CResizableControlBar::OnSetMessageString\n");
	CWnd * pOwner = GetOwner();
	if (pOwner != NULL)
		return pOwner->SendMessage(WM_SETMESSAGESTRING, wParam, lParam);
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CResizableControlBar message handlers

BOOL CResizableControlBar::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
//TRACE0("CResizableControlBar::Create\n");
	// TODO: Add your specialized code here and/or call the base class
    ASSERT(pParentWnd != NULL);

    // have to set the style here
    m_dwStyle = dwStyle;

    CRect Rectx;
    Rectx = rect;

    // calculate a sensible default rectangle if that's what the user wanted...
    if (memcmp(&rect, &CFrameWnd::rectDefault, sizeof(RECT)) == 0)
    {
        pParentWnd->GetClientRect(&Rectx);
        CSize def;
        def.cx = Rectx.right / 2;
        def.cy = Rectx.bottom  / 4;
        Rectx.left = Rectx.right - def.cx;
        Rectx.top  = Rectx.bottom - def.cy;
	}

   	// the rectangle specifies the default floating size.
   	m_FloatSize = Rectx.Size();
	
	// set default values for the docked sizes, based on this size.
	m_HorzDockSize.cx = m_FloatSize.cx;
	m_HorzDockSize.cy = m_FloatSize.cy / 2;	

	m_VertDockSize.cx = m_HorzDockSize.cy * 3 / 2;
	m_VertDockSize.cy = m_HorzDockSize.cx * 2 / 3;
        
    return CControlBar::Create(lpszClassName, lpszWindowName, dwStyle, Rectx, pParentWnd, nID, pContext);
}

BOOL CResizableControlBar::Create(CWnd * pParentWnd, LPCTSTR lpszWindowName, UINT nID,
								DWORD dwStyle, const RECT & rect)
{
//TRACE0("CResizableControlBar::Create\n");
	return Create(NULL, lpszWindowName, dwStyle, rect, pParentWnd, nID);
}

void CResizableControlBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
//TRACE0("CResizableControlBar::OnWindowPosChanged\n");
	CControlBar::OnWindowPosChanged(lpwndpos);
	
	// TODO: Add your message handler code here
    CSize NewSize(lpwndpos->cx, lpwndpos->cy);
    
	// This is meant to return "floating" if we're not docked yet...
    BOOL bFloating = IsProbablyFloating();
    
    int Flags = (NewSize == m_PrevSize ? 0 : 1);
    Flags |= (bFloating == m_bPrevFloating ? 0 : 2);
    if (Flags != 0)
    {
		m_PrevSize = NewSize;
        m_bPrevFloating = bFloating;
        OnSizedOrDocked(NewSize.cx, NewSize.cy, bFloating, Flags);
	}
}

BOOL CResizableControlBar::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
    pDC->GetClipBox(&rect);
    pDC->FillSolidRect(&rect, afxData.clrBtnFace); 
    return TRUE;
}

void CResizableControlBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	if (m_Style & SZBARF_STDMOUSECLICKS)
	{
		CMenu menu;
		if (menu.CreatePopupMenu())
		{
			OnAddContextMenuItems(0, (LPARAM)menu.m_hMenu);
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		}
	} 
	else
		CControlBar::OnContextMenu(pWnd, point);
}

void CResizableControlBar::OnSetFocus(CWnd* pOldWnd) 
{
//TRACE0("CResizableControlBar::OnSetFocus\n");
	if (IsFloating())
	{
		CFrameWnd * pFrame = GetParentFrame();
		if (pFrame != NULL)
		{
			pFrame->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
	}

	CControlBar::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}

