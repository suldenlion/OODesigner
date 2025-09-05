#if !defined(AFX_CPPMETHODPROPGENERAL_H__97611CD1_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPPMETHODPROPGENERAL_H__97611CD1_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CPPMethodPropGeneral.h : header file
//
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPPMethodPropGeneral dialog

class CPPMethodPropGeneral : public MemberOptionDlg
{
// Construction
public:
	CPPMethodPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();

// Dialog Data
	//{{AFX_DATA(CPPMethodPropGeneral)
	enum { IDD = IDD_CPP_METHOD_PROP_GENERAL };
	CButton	m_checkVirtualCtrl;
	CButton	m_checkStaticCtrl;
	CButton	m_checkInlineCtrl;
	CButton	m_checkConstCtrl;
	CString	m_comboVisibility;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPMethodPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPPMethodPropGeneral)
	afx_msg void OnCheckStatic();
	afx_msg void OnCheckVirtual();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPMETHODPROPGENERAL_H__97611CD1_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_)
