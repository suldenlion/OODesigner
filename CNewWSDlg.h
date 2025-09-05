#if !defined(AFX_CNEWWSDLG_H__86D97A46_1491_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CNEWWSDLG_H__86D97A46_1491_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNewWSDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewWSDlg dialog

class CNewWSDlg : public CDialog
{
private:
	CString _selectedDrive;
	CString _selectedDir;
// Construction
public:
	CNewWSDlg(CString &wsName,CWnd* pParent = NULL);   // standard constructor
public:
	CString wsLocation;
public:
// Dialog Data
	//{{AFX_DATA(CNewWSDlg)
	enum { IDD = IDD_NEWWSDLG };
	CEdit	m_editLocation;
	CString	m_language;
	CString	workspaceName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewWSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewWSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditName();
	virtual void OnOK();
	afx_msg void OnDirButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNEWWSDLG_H__86D97A46_1491_11D4_AED4_00A0C9BA6734__INCLUDED_)
