#if !defined(AFX_CPPVARPROPGENERAL_H__36E11422_25D1_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPPVARPROPGENERAL_H__36E11422_25D1_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CPPVarPropGeneral.h : header file
//
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPPVarPropGeneral dialog

class CPPVarPropGeneral : public MemberOptionDlg
{
// Construction
public:
	CPPVarPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();

// Dialog Data
	//{{AFX_DATA(CPPVarPropGeneral)
	enum { IDD = IDD_CPP_VAR_PROP_GENERAL };
	CComboBox	m_comboTypeCtrl;
	CStatic	m_staticEqualCtrl;
	CEdit	m_editDefaultValueCtrl;
	CButton	m_checkTransientCtrl;
	CButton	m_checkStaticCtrl;
	CString	m_comboVisibility;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPVarPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPPVarPropGeneral)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeComboType();
	afx_msg void OnDropdownComboType();
	afx_msg void OnChangeEditDefaultValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPVARPROPGENERAL_H__36E11422_25D1_11D4_AED4_00A0C9BA6734__INCLUDED_)
