// CChildFrm.h : interface of the CChildFrm class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCHILDFRM_H__91AA8C0B_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CCHILDFRM_H__91AA8C0B_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "KtgMacro.h"

class CChildFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrm)
public:
	CChildFrm();

// Attributes
protected:
	CString _diagramType;

public:
	CString frameName;
	CString frameTitle;
// Operations
public:
	const char* diagramType() {
		return _diagramType;
	}
	virtual CControlBar *getModelToolBar() {
		return NIL;
	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrm)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);

// Implementation
public:
	virtual ~CChildFrm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrm)
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnClose();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCHILDFRM_H__91AA8C0B_7A3E_11D2_AC44_00008610434C__INCLUDED_)

