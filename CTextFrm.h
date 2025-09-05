#if !defined(AFX_CTEXTFRM_H__91AA8C25_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CTEXTFRM_H__91AA8C25_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CTextFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextFrm window
#include "Classes.h"
#include "CChildFrm.h" // Generalization

class CTextFrm : public CChildFrm
{
	DECLARE_DYNCREATE(CTextFrm)
// Construction
public:
	CTextFrm();

// Attributes
public:

// Operations
public:
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextFrm)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextFrm();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTEXTFRM_H__91AA8C25_7A3E_11D2_AC44_00008610434C__INCLUDED_)
