#if !defined(AFX_CLASSMEMBERLISTVIEW_H__5E88F1A5_37E1_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_CLASSMEMBERLISTVIEW_H__5E88F1A5_37E1_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClassMemberListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ClassMemberListView view
#include "Afxcview.h"

class ClassMemberListView : public CListView
{
protected:
	ClassMemberListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ClassMemberListView)

// Attributes
private:
	int _whichMember;
	CString _className;
	CString _packageName;
// Operations
public:
	void deleteAllItems();
	void loadDataMembers(CString className,CString packageName);
	void loadMemberFunctions(CString className,CString packageName);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ClassMemberListView)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ClassMemberListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ClassMemberListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSMEMBERLISTVIEW_H__5E88F1A5_37E1_11D5_A72B_0050DA2D4248__INCLUDED_)
