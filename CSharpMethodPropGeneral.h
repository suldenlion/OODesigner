#if !defined(AFX_CSHARPMETHODPROPGENERAL_H__70C77082_8697_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_CSHARPMETHODPROPGENERAL_H__70C77082_8697_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSharpMethodPropGeneral.h : header file
//
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSharpMethodPropGeneral dialog

class CSharpMethodPropGeneral : public MemberOptionDlg
{
// Construction
public:
	CSharpMethodPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();

// Dialog Data
	//{{AFX_DATA(CSharpMethodPropGeneral)
	enum { IDD = IDD_CSHARP_METHOD_PROP_GENERAL };
	CButton	m_checkOverrideCtrl;
	CButton	m_checkExternCtrl;
	CButton	m_checkVirtualCtrl;
	CButton	m_checkStaticCtrl;
	CButton	m_checkInternalCtrl;
	CButton	m_checkAbstractCtrl;
	CString	m_comboVisibility;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSharpMethodPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSharpMethodPropGeneral)
	afx_msg void OnCheckStatic();
	afx_msg void OnCheckVirtual();
	afx_msg void OnCheckInternal();
	afx_msg void OnCheckExtern();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSHARPMETHODPROPGENERAL_H__70C77082_8697_11D5_A72B_0050DA2D4248__INCLUDED_)
