#if !defined(AFX_MEMBERFUNCTIONSOPTION_H__F293EB86_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_MEMBERFUNCTIONSOPTION_H__F293EB86_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MemberFunctionsOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MemberFunctionsOption dialog
#include "MemberOptionDlg.h"

class MemberFunctionsOption : public MemberOptionDlg
{
private:
	int _iSelectedItem;
	BOOL _newButtonPressed;
	void releaseNewButton();
	void loadClassTextLine(int i,ClassTextLine *pLine);
	void setEditField(NMHDR* pNMHDR);
// Construction
public:
	MemberFunctionsOption(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	// repaint 할 필요가 있는 경우에 TRUE 아니면 FALSE ...
	virtual BOOL writeOptionsToClassTextLine();
	void reloadClassMembers();
// Dialog Data
	//{{AFX_DATA(MemberFunctionsOption)
	enum { IDD = IDD_MEMBER_FUNCTIONS };
	CListCtrl	m_listMemberFunctions;
	CEdit	m_editMemberFunctionCtrl;
	CButton	m_buttonUpdateCtrl;
	CButton	m_buttonNewCtrl;
	CString	m_editMemberFunction;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MemberFunctionsOption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MemberFunctionsOption)
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonUpdate();
	afx_msg void OnClickListMemberFunctions(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListMemberFunctions(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditMemberFunction();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMBERFUNCTIONSOPTION_H__F293EB86_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_)
