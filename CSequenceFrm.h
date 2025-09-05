#if !defined(AFX_CSEQUENCEFRM_H__BF9456A1_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_CSEQUENCEFRM_H__BF9456A1_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSequenceFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSequenceFrm window
#include "Classes.h"
#include "CChildFrm.h" // Generalization

class CSequenceFrm : public CChildFrm
{
	DECLARE_DYNCREATE(CSequenceFrm)
// Construction
public:
	CSequenceFrm();

// Attributes
public:
	static BOOL ModelTBSupressedExplicitely;

// Operations
public:
	virtual CControlBar *getModelToolBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSequenceFrm)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSequenceFrm();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSequenceFrm)
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSEQUENCEFRM_H__BF9456A1_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_)
