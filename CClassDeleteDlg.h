#if !defined(AFX_CCLASSDELETEDLG_H__DCAAF6DF_00CC_4A1C_90AC_7A28CC504E05__INCLUDED_)
#define AFX_CCLASSDELETEDLG_H__DCAAF6DF_00CC_4A1C_90AC_7A28CC504E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CClassDeleteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClassDeleteDlg dialog

class CClassDeleteDlg : public CDialog
{
// Construction
public:
	CClassDeleteDlg(const char *className,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClassDeleteDlg)
	enum { IDD = IDD_CLASS_DEL_DLG };
	CString	m_staticClassName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassDeleteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClassDeleteDlg)
	afx_msg void OnNo();
	afx_msg void OnNoalways();
	afx_msg void OnYes();
	afx_msg void OnYesalways();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCLASSDELETEDLG_H__DCAAF6DF_00CC_4A1C_90AC_7A28CC504E05__INCLUDED_)
