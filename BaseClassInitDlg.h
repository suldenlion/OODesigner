#if !defined(AFX_BASECLASSINITDLG_H__AA39E383_12EC_11D5_A80A_0050DA2D4248__INCLUDED_)
#define AFX_BASECLASSINITDLG_H__AA39E383_12EC_11D5_A80A_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BaseClassInitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BaseClassInitDlg dialog

class BaseClassInitDlg : public CDialog
{
private:
	CStringList *_initValue;
// Construction
public:
	BaseClassInitDlg(CStringList *initValue,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BaseClassInitDlg)
	enum { IDD = IDD_BASE_CLASS_INIT_DLG };
	CEdit	m_editInitValueCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BaseClassInitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BaseClassInitDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASECLASSINITDLG_H__AA39E383_12EC_11D5_A80A_0050DA2D4248__INCLUDED_)
