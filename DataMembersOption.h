#if !defined(AFX_DATAMEMBERSOPTION_H__F293EB85_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_DATAMEMBERSOPTION_H__F293EB85_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DataMembersOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DataMembersOption dialog
#include "MemberOptionDlg.h"

class DataMembersOption : public MemberOptionDlg
{
private:
	int _iSelectedItem;
	BOOL _newButtonPressed;
	void releaseNewButton();
	void loadClassTextLine(int i,ClassTextLine *pLine);
	void setEditField(NMHDR* pNMHDR);
// Construction
public:
	DataMembersOption(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	// repaint 할 필요가 있는 경우에 TRUE 아니면 FALSE ...
	virtual BOOL writeOptionsToClassTextLine();
	void reloadClassMembers();
// Dialog Data
	//{{AFX_DATA(DataMembersOption)
	enum { IDD = IDD_DATA_MEMBERS };
	CEdit	m_editDataMemberCtrl;
	CButton	m_buttonNewCtrl;
	CButton	m_buttonUpdateCtrl;
	CListCtrl	m_listDataMembers;
	CString	m_editDataMember;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DataMembersOption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DataMembersOption)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditDataMember();
	afx_msg void OnClickListDataMembers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonDelete();
	afx_msg void OnDblclkListDataMembers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAMEMBERSOPTION_H__F293EB85_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_)
