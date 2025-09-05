#if !defined(AFX_CPROJECTOPTIONSREVERSE_H__BD3B2763_1B93_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPROJECTOPTIONSREVERSE_H__BD3B2763_1B93_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CProjectOptionsReverse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsReverse dialog

class CProjectOptionsReverse : public CDialog
{
// Construction
public:
	CProjectOptionsReverse(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectOptionsReverse)
	enum { IDD = IDD_PROJECT_OPTIONS_REVERSE };
	CButton	m_radioNo;
	CButton	m_radioYes;
	CString	m_comboTreeOrient;
	CString	m_editSourceDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectOptionsReverse)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectOptionsReverse)
	afx_msg void OnButtonChooseDir();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPROJECTOPTIONSREVERSE_H__BD3B2763_1B93_11D4_AED4_00A0C9BA6734__INCLUDED_)
