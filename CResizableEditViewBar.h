#if !defined(AFX_CRESIZABLEEDITVIEWBAR_H__91AA8C2E_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLEEDITVIEWBAR_H__91AA8C2E_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableEditViewBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableEditViewBar window
#include "CResizableControlBar.h"

class CResizableEditViewBar : public CResizableControlBar
{
	DECLARE_DYNCREATE(CResizableEditViewBar)
// Construction
public:
	CResizableEditViewBar();

// Attributes
public:
	CView *m_pChildView;

// Operations
public:
	virtual void OnSizedOrDocked(int cx,int cy,BOOL bFloating,int flags);
	virtual BOOL hasDocument() { return TRUE; }
	virtual BOOL SaveModified();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableEditViewBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizableEditViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CResizableEditViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLEEDITVIEWBAR_H__91AA8C2E_7A3E_11D2_AC44_00008610434C__INCLUDED_)
