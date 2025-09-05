#if !defined(AFX_JAVACLASSPROPGENERAL_H__467A9522_3DE9_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_JAVACLASSPROPGENERAL_H__467A9522_3DE9_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// JavaClassPropGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// JavaClassPropGeneral dialog
#include "MemberOptionDlg.h"

class JavaClassPropGeneral : public MemberOptionDlg
{
// Construction
public:
	JavaClassPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	// repaint 할 필요가 있는 경우에 TRUE 아니면 FALSE ...
	virtual BOOL writeOptionsToClassTextLine();

// Dialog Data
	//{{AFX_DATA(JavaClassPropGeneral)
	enum { IDD = IDD_JAVA_CLASS_PROP_GENERAL };
	CButton	m_checkStaticCtrl;
	CButton	m_checkConcreteCtrl;
	CButton	m_checkAbstractCtrl;
	CString	m_comboStereotype;
	CString	m_comboVisibility;
	CString	m_editInnerClassOf;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(JavaClassPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(JavaClassPropGeneral)
	afx_msg void OnCheckAbstract();
	afx_msg void OnCheckConcrete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JAVACLASSPROPGENERAL_H__467A9522_3DE9_11D4_AED4_00A0C9BA6734__INCLUDED_)
