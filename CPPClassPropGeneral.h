#if !defined(AFX_CPPCLASSPROPGENERAL_H__F293EB83_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPPCLASSPROPGENERAL_H__F293EB83_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CPPClassPropGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPClassPropGeneral dialog
#include "MemberOptionDlg.h"

class CPPClassPropGeneral : public MemberOptionDlg
{
// Construction
public:
	CPPClassPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	// repaint 할 필요가 있는 경우에 TRUE 아니면 FALSE ...
	virtual BOOL writeOptionsToClassTextLine();

// Dialog Data
	//{{AFX_DATA(CPPClassPropGeneral)
	enum { IDD = IDD_CPP_CLASS_PROP_GENERAL };
	CButton	m_checkConcreteCtrl;
	CButton	m_checkAbstractCtrl;
	CString	m_comboStereotype;
	CString	m_editInnerClassOf;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPClassPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPPClassPropGeneral)
	afx_msg void OnCheckAbstract();
	afx_msg void OnCheckConcrete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPCLASSPROPGENERAL_H__F293EB83_3C69_11D4_AED4_00A0C9BA6734__INCLUDED_)
