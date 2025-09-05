#if !defined(AFX_CRESIZABLECONTROLBAR_H__91AA8C27_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLECONTROLBAR_H__91AA8C27_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableControlBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableControlBar window
#include <afxpriv.h>

#define SZBARF_DESTROY_ON_CLOSE     1       // closing the floating window closes the control bar
#define SZBARF_AUTOTIDY             2               // keeps window in an array, so it can be deleted
										
#define SZBARF_STDMOUSECLICKS           4               // standard mouse handling for the menu
#define SZBARF_DLGAUTOSIZE                      8               // auto-size dialog bars
#define SZBARF_ALLOW_MDI_FLOAT     16           // allow bar to float in an MDI window

#define CBRS_MOVED_BY_USER       0x0001L    // set if dragged by user 

class CResizableControlBar : public CControlBar
{
	DECLARE_DYNAMIC(CResizableControlBar)
// Attributes
private:
	static CObArray * m_parrAllocBars;              // array of dynamically allocated bars
public:

	CSize           m_FloatSize;           // size when floating
	CSize           m_HorzDockSize;                 // size when docked horizontal
	CSize           m_VertDockSize;                 // size when docked vertical
	//  - size reflects the current docked size of the window (I do nothing clever for stretched)
	//  - height is generally shared across the rows

    CPoint          m_FloatingPosition;             // floating position
	DWORD           m_dwAllowDockingState;  // saved enable style for allow docking on/off
    int             m_Style;                // style flags
    CSize           m_PrevSize;
    BOOL            m_bPrevFloating;
// Construction
public:
    CResizableControlBar(int nStyle = SZBARF_STDMOUSECLICKS);

// Attributes
public:

// Operations
public:
	static void TidyUp();
	BOOL Create(CWnd * pParent, LPCTSTR lpszTitle, UINT nID = 1,
			 DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
			   const RECT & rect = CFrameWnd::rectDefault);

	void SetSizeDockStyle(DWORD dwStyle);
    void EnableDocking(DWORD dwDockStyle);
		
	BOOL IsProbablyFloating();

	// command handlers for standard menus
	void OnHide();
	void OnToggleAllowDocking();
	void OnFloatAsMDI();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableControlBar)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizableControlBar();

	virtual BOOL hasDocument() { return FALSE; } // generally no document contained
	virtual BOOL SaveModified() { return TRUE; } // keep going

    virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

	// Generated message map functions
protected:
    virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	virtual LONG OnAddContextMenuItems(UINT wParam, LPARAM lParam);
	//{{AFX_MSG(CResizableControlBar)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	LONG OnSetMessageString(WPARAM wParam, LPARAM lParam);
public:
	LONG OnAfterFloatMessage(UINT, LONG);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLECONTROLBAR_H__91AA8C27_7A3E_11D2_AC44_00008610434C__INCLUDED_)
