#if !defined(AFX_CCHOOSEDIRDLG_H__6ABB1C04_1519_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CCHOOSEDIRDLG_H__6ABB1C04_1519_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CChooseDirDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseDirDlg dialog

class CChooseDirDlg : public CDialog
{
private:
    CImageList  _directoryImageList;
	CString _initDriveName;
	BOOL _remakeTreeFlag;

	void showDirectory();
// Construction
public:
	CChooseDirDlg(CString &driveName,CString& dirName,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseDirDlg)
	enum { IDD = IDD_CHOOSE_DIR };
	CComboBox	m_comboDriveNames;
	CTreeCtrl	m_treeDirs;
	CString	m_dirName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseDirDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseDirDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDriveName();
	afx_msg void OnDblclkTreeDirs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCHOOSEDIRDLG_H__6ABB1C04_1519_11D4_AED4_00A0C9BA6734__INCLUDED_)
