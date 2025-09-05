#if !defined(AFX_JAVAMETHODPROPGENERAL_H__E8D7C1E2_238A_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_JAVAMETHODPROPGENERAL_H__E8D7C1E2_238A_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// JavaMethodPropGeneral.h : header file
//
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// JavaMethodPropGeneral dialog

class JavaMethodPropGeneral : public MemberOptionDlg
{
// Construction
public:
	JavaMethodPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();

// Dialog Data
	//{{AFX_DATA(JavaMethodPropGeneral)
	enum { IDD = IDD_JAVA_METHOD_PROP_GENERAL };
	CButton	m_checkFinalCtrl;
	CButton	m_checkNativeCtrl;
	CButton	m_checkSynchronizedCtrl;
	CButton	m_checkStaticCtrl;
	CButton	m_checkAbstractCtrl;
	CString	m_comboVisibility;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(JavaMethodPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(JavaMethodPropGeneral)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JAVAMETHODPROPGENERAL_H__E8D7C1E2_238A_11D4_AED4_00A0C9BA6734__INCLUDED_)
