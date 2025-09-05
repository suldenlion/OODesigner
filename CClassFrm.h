#if !defined(AFX_CCLASSFRM_H__91AA8C1A_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CCLASSFRM_H__91AA8C1A_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CClassFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClassFrm window

#include "Classes.h"
#include "CChildFrm.h" // Generalization

class CClassFrm : public CChildFrm
{
	DECLARE_DYNCREATE(CClassFrm)
// Construction
public:
	CClassFrm();

// Attributes
public:
	static BOOL ModelTBSupressedExplicitely;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassFrm)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClassFrm();
	virtual CControlBar *getModelToolBar();
	// Generated message map functions
protected:
	//{{AFX_MSG(CClassFrm)
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCLASSFRM_H__91AA8C1A_7A3E_11D2_AC44_00008610434C__INCLUDED_)
