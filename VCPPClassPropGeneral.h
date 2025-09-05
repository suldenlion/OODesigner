#if !defined(AFX_VCPPCLASSPROPGENERAL_H__467A9523_3DE9_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_VCPPCLASSPROPGENERAL_H__467A9523_3DE9_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VCPPClassPropGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VCPPClassPropGeneral dialog
#include "MemberOptionDlg.h"

class VCPPClassPropGeneral : public MemberOptionDlg
{
	DECLARE_DYNAMIC(VCPPClassPropGeneral)
private:
	void loadResourceID(CString &resourceID);
	BOOL writeResourceID(CString &resourceID);

// Construction
public:
	VCPPClassPropGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	// repaint 할 필요가 있는 경우에 TRUE 아니면 FALSE ...
	virtual BOOL writeOptionsToClassTextLine();
	void setMFCClassCtrl();

// Dialog Data
	//{{AFX_DATA(VCPPClassPropGeneral)
	enum { IDD = IDD_VCPP_CLASS_PROP_GENERAL };
	CEdit	m_editResourceIDCtrl;
	CButton	m_checkDyncreateCtrl;
	CButton	m_checkDynamicCtrl;
	CButton	m_checkSerializableCtrl;
	CButton	m_checkMFCClassCtrl;
	CButton	m_checkConcreteCtrl;
	CButton	m_checkAbstractCtrl;
	CString	m_comboStereotype;
	CString	m_editResourceID;
	CString	m_editInnerClassOf;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VCPPClassPropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VCPPClassPropGeneral)
	afx_msg void OnCheckAbstract();
	afx_msg void OnCheckConcrete();
	afx_msg void OnCheckDynamic();
	afx_msg void OnCheckDyncreate();
	afx_msg void OnCheckSerializable();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckMfcClass();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCPPCLASSPROPGENERAL_H__467A9523_3DE9_11D4_AED4_00A0C9BA6734__INCLUDED_)
