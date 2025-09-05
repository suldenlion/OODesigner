#if !defined(AFX_TIPDIALOG_H__653AAA82_2778_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_TIPDIALOG_H__653AAA82_2778_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TipDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TipDialog dialog
#include "TipBoard.h"

class TipDialog : public CDialog
{
// Construction
public:
	TipDialog(CWnd* pParent = NULL);   // standard constructor
private:
	TipBoard _whiteBoard;

// Dialog Data
	//{{AFX_DATA(TipDialog)
	enum { IDD = IDD_TIP_DIALOG };
	BOOL	m_checkStartUp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TipDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TipDialog)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPDIALOG_H__653AAA82_2778_11D5_A72B_0050DA2D4248__INCLUDED_)
