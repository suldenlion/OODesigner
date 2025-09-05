#if !defined(AFX_RELATIONTRAVERSEDLG_H__5E88F1A0_37E1_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_RELATIONTRAVERSEDLG_H__5E88F1A0_37E1_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RelationTraverseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RelationTraverseDlg dialog
#define GENERALIZATION_RELATIONSHIP		(0)
#define AGGREGATION_RELATIONSHIP		(1)
#define DEPENDENCY_RELATIONSHIP			(2)

#define	FORWARD_ORIENT					(0)
#define BACKWARD_ORIENT					(1)

class RelationTraverseFrame;
class ClassMemberListView;

class RelationTraverseDlg : public CDialog
{
	DECLARE_DYNAMIC(RelationTraverseDlg)
// Construction
public:
	RelationTraverseDlg(CWnd* pParent = NULL);   // standard constructor
	RelationTraverseDlg(CString &className,CString &packageName,CWnd* pParent = NULL);   // standard constructor
	void setNameAndLoadClassInfo(CString &className,CString &packageName);
	void reloadClassMembers();
	ClassMemberListView *getListView(int i);
	int getOrientString(CString &statement);
private:
	int _whichOrient;
	int _whichRelationship;
	CString _className;
	CString _packageName;
	RelationTraverseFrame *_theFrame;
	int _initX; 
	int _initY;

// Dialog Data
	//{{AFX_DATA(RelationTraverseDlg)
	enum { IDD = IDD_RELATION_TRAVERSE_DLG };
	CComboBox	m_comboOrientCtrl;
	CComboBox	m_comboRelationshipCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RelationTraverseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(RelationTraverseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeComboRelationship();
	afx_msg void OnSelchangeComboOrient();
	//}}AFX_MSG
	void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELATIONTRAVERSEDLG_H__5E88F1A0_37E1_11D5_A72B_0050DA2D4248__INCLUDED_)
