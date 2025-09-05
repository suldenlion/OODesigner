#if !defined(AFX_SCREENCAPTUREDLG_H__33357808_28ED_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_SCREENCAPTUREDLG_H__33357808_28ED_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScreenCaptureDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ScreenCaptureDlg dialog

class ScreenCaptureDlg : public CDialog
{
private:
	BOOL _viewFlag;
// Construction
public:
	ScreenCaptureDlg(CString &fName,BOOL captureView,CWnd* pParent = NULL);   // standard constructor
	BOOL getViewFlag() { return _viewFlag; }

public:
// Dialog Data
	//{{AFX_DATA(ScreenCaptureDlg)
	enum { IDD = IDD_SCREEN_CAPTURE_DLG };
	CString	m_editBMPFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScreenCaptureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ScreenCaptureDlg)
	afx_msg void OnRadioUserRect();
	afx_msg void OnRadioView();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENCAPTUREDLG_H__33357808_28ED_11D5_A72B_0050DA2D4248__INCLUDED_)
