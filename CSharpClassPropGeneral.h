#if !defined(AFX_CSHARPCLASSPROPGENERAL_H__70C77081_8697_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_CSHARPCLASSPROPGENERAL_H__70C77081_8697_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSharpClassPropGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSharpClassPropGeneral dialog
#include "MemberOptionDlg.h"

class CSharpClassPropGeneral : public MemberOptionDlg
{
// Construction
public:
	CSharpClassPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	// repaint 할 필요가 있는 경우에 TRUE 아니면 FALSE ...
	virtual BOOL writeOptionsToClassTextLine();


// Dialog Data
	//{{AFX_DATA(CSharpClassPropGeneral)
	enum { IDD = IDD_CSHARP_CLASS_PROP_GENERAL };
	CButton	m_checkConcreteCtrl;
	CButton	m_checkAbstractCtrl;
	CString	m_comboStereotype;
	CString	m_comboVisibility;
	CString	m_editInnerClassOf;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSharpClassPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSharpClassPropGeneral)
	afx_msg void OnCheckAbstract();
	afx_msg void OnCheckConcrete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSHARPCLASSPROPGENERAL_H__70C77081_8697_11D5_A72B_0050DA2D4248__INCLUDED_)
