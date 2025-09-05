#if !defined(AFX_CRESIZABLEFLOATWND_H__91AA8C30_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLEFLOATWND_H__91AA8C30_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableFloatWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableFloatWnd window
#include <afxpriv.h>

class CResizableFloatWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CResizableFloatWnd)
// Construction
protected:
	CResizableFloatWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CDockBar	m_wndMDIDockBar;		

// Operations
public:
	virtual BOOL Create(CWnd* pParent, DWORD dwBarStyle);

// Overrides
	void RecalcLayout(BOOL bNotify = TRUE);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableFloatWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizableFloatWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CResizableFloatWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLEFLOATWND_H__91AA8C30_7A3E_11D2_AC44_00008610434C__INCLUDED_)
