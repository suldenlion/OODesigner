#if !defined(AFX_QUERYTEXTDLG_H__719DE1C3_34F2_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_QUERYTEXTDLG_H__719DE1C3_34F2_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// QueryTextDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// QueryTextDlg dialog
#define FOR_PACKAGE				(0)
#define FOR_CLASS				(1)
#define FOR_DATA_MEMBER			(2)
#define FOR_MEMBER_FUNCTION		(3)

#define IDMORE					(100)

class QueryTextDlg : public CDialog
{
// Construction
public:
	QueryTextDlg(int purpose,const char* question,CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(QueryTextDlg)
	enum { IDD = IDD_QUERY_TEXT_DIALOG };
	CButton	m_buttonPropertiesCtrl;
	CString	m_editAnswer;
	CString	m_staticQuestion;
	//}}AFX_DATA

private:
	int _forWhich;
	void saveAnswer();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(QueryTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(QueryTextDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonProperties();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYTEXTDLG_H__719DE1C3_34F2_11D5_A72B_0050DA2D4248__INCLUDED_)
