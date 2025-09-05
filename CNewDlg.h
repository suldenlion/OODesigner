#if !defined(AFX_CNEWDLG_H__37F42B41_7A65_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CNEWDLG_H__37F42B41_7A65_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewDlg dialog

class CNewDlg : public CDialog
{
private:
	int _index;
	CString _dgmType;

// Construction
public:
	CNewDlg(CString dgmType,const char *defaultExtension,CWnd* pParent = NULL);   // standard constructor
	int fileType() { return _index; }

// Dialog Data
	//{{AFX_DATA(CNewDlg)
	enum { IDD = IDD_NEWDLG };
	CListBox	m_fileTypes;
	CString	m_name;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFileTypeList();
	afx_msg void OnDblclkFileTypeList();
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNEWDLG_H__37F42B41_7A65_11D2_AC44_00008610434C__INCLUDED_)
