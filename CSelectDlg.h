#if !defined(AFX_CSELECTDLG_H__AE19BBEA_FFC7_4105_996B_7B9695F81879__INCLUDED_)
#define AFX_CSELECTDLG_H__AE19BBEA_FFC7_4105_996B_7B9695F81879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog

class CSelectDlg : public CDialog
{
private:
	int _index;
	CString _dgmType;

// Construction
public:
	CSelectDlg(CWnd* pParent = NULL);   // standard constructor
	int fileType() { return _index; }

// Dialog Data
	//{{AFX_DATA(CSelectDlg)
	enum { IDD = IDD_WHICHDLG };
	CListBox	m_fileTypes;
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectDlg)
	afx_msg void OnDblclkFileTypeList();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeFileTypeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSELECTDLG_H__AE19BBEA_FFC7_4105_996B_7B9695F81879__INCLUDED_)
