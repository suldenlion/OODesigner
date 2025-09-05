#if !defined(AFX_COBJECTFRM_H__028DB5A2_9D59_11D6_9C59_0050047F7901__INCLUDED_)
#define AFX_COBJECTFRM_H__028DB5A2_9D59_11D6_9C59_0050047F7901__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CObjectFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectFrm frame
#include "Classes.h"
#include "CChildFrm.h" // Generalization

class CObjectFrm : public CChildFrm
{
	DECLARE_DYNCREATE(CObjectFrm)
//Construction
public:
	CObjectFrm();           

// Attributes
public:
	static BOOL ModelTBSupressedExplicitely;

// Operations
public:
	virtual CControlBar *getModelToolBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectFrm)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CObjectFrm();

	// Generated message map functions
	//{{AFX_MSG(CObjectFrm)
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COBJECTFRM_H__028DB5A2_9D59_11D6_9C59_0050047F7901__INCLUDED_)
