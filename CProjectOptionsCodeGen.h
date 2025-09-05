#if !defined(AFX_CPROJECTOPTIONSCODEGEN_H__BD3B2762_1B93_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPROJECTOPTIONSCODEGEN_H__BD3B2762_1B93_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CProjectOptionsCodeGen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsCodeGen dialog

class CProjectOptionsCodeGen : public CDialog
{
// Construction
public:
	CProjectOptionsCodeGen(CWnd* pParent = NULL);   // standard constructor
	void languageSelected(CString &language);
// Dialog Data
	//{{AFX_DATA(CProjectOptionsCodeGen)
	enum { IDD = IDD_PROJECT_OPTIONS_CODEGEN };
	CComboBox	m_comboHFExtensionCtrl;
	CComboBox	m_comboSFExtensionCtrl;
	CButton	m_buttonChooseDir;
	CString	m_comboHFExtension;
	CString	m_comboSFExtension;
	CString	m_editTargetDirectory;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectOptionsCodeGen)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectOptionsCodeGen)
	afx_msg void OnButtonChooseDir();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPROJECTOPTIONSCODEGEN_H__BD3B2762_1B93_11D4_AED4_00A0C9BA6734__INCLUDED_)
