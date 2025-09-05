#if !defined(AFX_CRESIZABLEMINIDOCKFRAMEWND_H__91AA8C32_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLEMINIDOCKFRAMEWND_H__91AA8C32_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableMiniDockFrameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableMiniDockFrameWnd window
#include <afxpriv.h>
class CResizableDockContext;

class CResizableMiniDockFrameWnd : public CMiniDockFrameWnd
{
friend class CResizableDockContext; 		// access to IgnoreSysMove flag
    DECLARE_DYNCREATE(CResizableMiniDockFrameWnd)
// Construction
public:
	CResizableMiniDockFrameWnd();

// Attributes
public:
	enum ContainedBarType { Unknown, MFCBase, MRCSizeBar } ;
	enum ContainedBarType GetContainedBarType();
protected:
	enum ContainedBarType m_nContainedBarType;	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableMiniDockFrameWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizableMiniDockFrameWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CResizableMiniDockFrameWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLEMINIDOCKFRAMEWND_H__91AA8C32_7A3E_11D2_AC44_00008610434C__INCLUDED_)
