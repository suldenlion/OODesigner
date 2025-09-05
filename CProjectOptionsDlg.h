#if !defined(AFX_CPROJECTOPTIONSDLG_H__863C08E2_1A0F_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPROJECTOPTIONSDLG_H__863C08E2_1A0F_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CProjectOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsDlg dialog
class CProjectOptionsGeneral;
class CProjectOptionsCodeGen;
class CProjectOptionsReverse;
class CProjectOptionsMacros;

class CProjectOptionsDlg : public CDialog
{
private:
    void ShowSelTabWindow();
    CWnd * GetTabWindow(int nTab);
	CProjectOptionsGeneral *_generalOption;
	CProjectOptionsCodeGen *_codegenOption;
	CProjectOptionsReverse *_reverseOption;
	CProjectOptionsMacros *_macrosOption;
// Construction
public:
	CProjectOptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjectOptionsDlg();

// Dialog Data
	//{{AFX_DATA(CProjectOptionsDlg)
	enum { IDD = IDD_PROJECT_OPTIONS_DLG };
	CTabCtrl	m_optionsTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectOptionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabProjectOptions(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMove(int x, int y);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPROJECTOPTIONSDLG_H__863C08E2_1A0F_11D4_AED4_00A0C9BA6734__INCLUDED_)
