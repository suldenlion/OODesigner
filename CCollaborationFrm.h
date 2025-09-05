#if !defined(AFX_CCOLLABORATIONFRM_H__ADFC18E1_CDB9_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_CCOLLABORATIONFRM_H__ADFC18E1_CDB9_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CCollaborationFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCollaborationFrm window
#include "Classes.h"
#include "CChildFrm.h" // Generalization

class CCollaborationFrm : public CChildFrm
{
	DECLARE_DYNCREATE(CCollaborationFrm)
// Construction
public:
	CCollaborationFrm();

// Attributes
public:
	static BOOL ModelTBSupressedExplicitely;

// Operations
public:
	virtual CControlBar *getModelToolBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollaborationFrm)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCollaborationFrm();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCollaborationFrm)
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCOLLABORATIONFRM_H__ADFC18E1_CDB9_11D3_BBC8_00A0C9BA6734__INCLUDED_)
