#if !defined(AFX_CSHARPVARPROPGENERAL_H__70C77083_8697_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_CSHARPVARPROPGENERAL_H__70C77083_8697_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSharpVarPropGeneral.h : header file
//
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSharpVarPropGeneral dialog

class CSharpVarPropGeneral : public MemberOptionDlg
{
// Construction
public:
	CSharpVarPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();

// Dialog Data
	//{{AFX_DATA(CSharpVarPropGeneral)
	enum { IDD = IDD_CSHARP_VAR_PROP_GENERAL };
	CStatic	m_staticEqualCtrl;
	CEdit	m_editDefaultValueCtrl;
	CComboBox	m_comboTypeCtrl;
	CButton	m_checkStaticCtrl;
	CButton	m_checkReadonlyCtrl;
	CButton	m_checkInternalCtrl;
	CString	m_comboVisibility;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSharpVarPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSharpVarPropGeneral)
	virtual BOOL OnInitDialog();
	afx_msg void OnDropdownComboType();
	afx_msg void OnEditchangeComboType();
	afx_msg void OnChangeEditDefaultValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSHARPVARPROPGENERAL_H__70C77083_8697_11D5_A72B_0050DA2D4248__INCLUDED_)
