#if !defined(AFX_CACTIVITYFRM_H__91AA8C18_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CACTIVITYFRM_H__91AA8C18_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CActivityFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActivityFrm window

#include "Classes.h"
#include "CChildFrm.h" // Generalization

class CActivityFrm : public CChildFrm
{
	DECLARE_DYNCREATE(CActivityFrm)
// Construction
public:
	CActivityFrm();

// Attributes
public:
	static BOOL ModelTBSupressedExplicitely;
// Operations
public:
	virtual CControlBar *getModelToolBar();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActivityFrm)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CActivityFrm();

	// Generated message map functions
protected:
	//{{AFX_MSG(CActivityFrm)
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACTIVITYFRM_H__91AA8C18_7A3E_11D2_AC44_00008610434C__INCLUDED_)

