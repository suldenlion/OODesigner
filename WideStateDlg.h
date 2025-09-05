#if !defined(AFX_WIDESTATEDLG_H__30307B00_237F_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_WIDESTATEDLG_H__30307B00_237F_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WideStateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WideStateDlg dialog

class WideStateDlg : public CDialog
{
// Construction
private:
	int _nOfPlanes;
public:
	WideStateDlg(CWnd* pParent = NULL);   // standard constructor
	int nOfPlanes() { return _nOfPlanes; }

// Dialog Data
	//{{AFX_DATA(WideStateDlg)
	enum { IDD = IDD_WIDE_STATE_DLG };
	CEdit	m_editNumberCtrl;
	CComboBox	m_comboNumberCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WideStateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WideStateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboNumber();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIDESTATEDLG_H__30307B00_237F_11D5_A72B_0050DA2D4248__INCLUDED_)
