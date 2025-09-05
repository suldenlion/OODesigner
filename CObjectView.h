#if !defined(AFX_COBJECTVIEW_H__028DB5A3_9D59_11D6_9C59_0050047F7901__INCLUDED_)
#define AFX_COBJECTVIEW_H__028DB5A3_9D59_11D6_9C59_0050047F7901__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CObjectView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectView view
#include "Classes.h"
#include "CClassView.h"

class CObjectView : public CClassView
{
	DECLARE_DYNCREATE(CObjectView)
protected:
	CObjectView();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CObjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CObjectView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COBJECTVIEW_H__028DB5A3_9D59_11D6_9C59_0050047F7901__INCLUDED_)
