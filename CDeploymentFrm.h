#if !defined(AFX_CDEPLOYMENTFRM_H__91AA8C20_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CDEPLOYMENTFRM_H__91AA8C20_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDeploymentFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeploymentFrm window
#include "Classes.h"
#include "CChildFrm.h" // Generalization

class CDeploymentFrm : public CChildFrm 
{
	DECLARE_DYNCREATE(CDeploymentFrm)
// Construction
public:
	CDeploymentFrm();

// Attributes
public:
	static BOOL ModelTBSupressedExplicitely;

// Operations
public:
	virtual CControlBar *getModelToolBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeploymentFrm)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDeploymentFrm();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDeploymentFrm)
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDEPLOYMENTFRM_H__91AA8C20_7A3E_11D2_AC44_00008610434C__INCLUDED_)
