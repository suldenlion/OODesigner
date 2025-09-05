#if !defined(AFX_CLASSTREEVIEW_H__5E88F1A4_37E1_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_CLASSTREEVIEW_H__5E88F1A4_37E1_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClassTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ClassTreeView view
#include "Afxcview.h"
class RelationTraverseDlg;

class ClassTreeView : public CTreeView
{
protected:
	ClassTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ClassTreeView)
	RelationTraverseDlg *getParentDlg();
	RelationshipInfoTupleList *getActiveRelationshipLibrary();
	void loadGrandChildrens(HTREEITEM currentItem);
	BOOL ifExpanededAlready(HTREEITEM hItem);
	BOOL tryToDeleteSelectedItem();
	void loadTree();

// Attributes
private:
	int _whichRelationship;
	int _whichOrient;
	CString _rootClassName;
	CString _selectedClassName;
	CString _packageName;
    CImageList  _imageList;

// Operations
public:
	void loadTree(CString className,CString packageName,int relationship,int orient);
	void reloadClassMembers();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ClassTreeView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ClassTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ClassTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDeleteRelationship();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSTREEVIEW_H__5E88F1A4_37E1_11D5_A72B_0050DA2D4248__INCLUDED_)
