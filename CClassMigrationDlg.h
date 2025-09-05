#if !defined(AFX_CCLASSMIGRATIONDLG_H__5EA95A69_45CF_4545_A870_CABED12D213C__INCLUDED_)
#define AFX_CCLASSMIGRATIONDLG_H__5EA95A69_45CF_4545_A870_CABED12D213C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CClassMigrationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClassMigrationDlg dialog

class CClassMigrationDlg : public CDialog
{
// Construction
public:
	CClassMigrationDlg(CString& currentPack,CStringList& packNames,CWnd* pParent = NULL);   // standard constructor
private:
	CString _packageName;
	CStringList& _packageNames;

public:
// Dialog Data
	//{{AFX_DATA(CClassMigrationDlg)
	enum { IDD = IDD_CLASS_MIGRATION_DLG };
	CComboBox	m_comboDestinationCtrl;
	CString	m_DestinationString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassMigrationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClassMigrationDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCLASSMIGRATIONDLG_H__5EA95A69_45CF_4545_A870_CABED12D213C__INCLUDED_)
