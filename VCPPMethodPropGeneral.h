#if !defined(AFX_VCPPMETHODPROPGENERAL_H__B73B8102_22A7_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_VCPPMETHODPROPGENERAL_H__B73B8102_22A7_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VCPPMethodPropGeneral.h : header file
//
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// VCPPMethodPropGeneral dialog

class VCPPMethodPropGeneral : public MemberOptionDlg
{
// Construction
public:
	VCPPMethodPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();

// Dialog Data
	//{{AFX_DATA(VCPPMethodPropGeneral)
	enum { IDD = IDD_VCPP_METHOD_PROP_GENERAL };
	CButton	m_checkMfcvirtualCtrl;
	CButton	m_checkVirtualCtrl;
	CButton	m_checkStaticCtrl;
	CButton	m_checkAfxmsgCtrl;
	CButton	m_checkInlineCtrl;
	CButton	m_checkConstCtrl;
	CString	m_comboVisibility;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VCPPMethodPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VCPPMethodPropGeneral)
	afx_msg void OnCheckAfxmsg();
	afx_msg void OnCheckStatic();
	afx_msg void OnCheckVirtual();
	afx_msg void OnCheckMfcvirtual();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCPPMETHODPROPGENERAL_H__B73B8102_22A7_11D4_AED4_00A0C9BA6734__INCLUDED_)
