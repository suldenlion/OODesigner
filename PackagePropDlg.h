#if !defined(AFX_PACKAGEPROPDLG_H__EF60EBE1_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_PACKAGEPROPDLG_H__EF60EBE1_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PackagePropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PackagePropDlg dialog
class PackagePropGeneral;
class PackageCommentDlg;
class FigureLibrary;
#include "TabDlgWithName.h"

class PackagePropDlg : public TabDlgWithName
{
	DECLARE_DYNAMIC(PackagePropDlg)
// Construction
public:
	PackagePropDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~PackagePropDlg();
	void loadPackageInfo(CString &dgmName);
private:
	FigureLibrary *_packageInfo;
	CString _packageName;

	PackagePropGeneral *_generalOption;
	PackageCommentDlg *_commentOption;

// Dialog Data
	//{{AFX_DATA(PackagePropDlg)
	enum { IDD = IDD_PACKAGE_PROP_DLG };
	CStatic	m_staticPackageNameCtrl;
	CTabCtrl	m_optionsTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PackagePropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PackagePropDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabPackageProp(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PACKAGEPROPDLG_H__EF60EBE1_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_)
