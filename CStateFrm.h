#if !defined(AFX_CSTATEFRM_H__91AA8C22_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CSTATEFRM_H__91AA8C22_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CStateFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStateFrm window
#include "Classes.h"
#include "CChildFrm.h" // Generalization

class CStateFrm : public CChildFrm
{
	DECLARE_DYNCREATE(CStateFrm)
// Construction
public:
	CStateFrm();

// Attributes
public:
	static BOOL ModelTBSupressedExplicitely;

// Operations
public:
	virtual CControlBar *getModelToolBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStateFrm)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStateFrm();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStateFrm)
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTATEFRM_H__91AA8C22_7A3E_11D2_AC44_00008610434C__INCLUDED_)
