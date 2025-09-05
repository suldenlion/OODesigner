#if !defined(AFX_CAPTUREDLG_H__D6BBE200_2D18_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_CAPTUREDLG_H__D6BBE200_2D18_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CaptureDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CaptureDlg dialog

class CaptureDlg : public CDialog
{
// Construction
public:
	CaptureDlg(CWnd* pParent = NULL);   // standard constructor
	CBitmap	resultBitmap;
private:
	CRect _userRect;
	CBitmap	_bitmap;
// Dialog Data
	//{{AFX_DATA(CaptureDlg)
	enum { IDD = IDD_CAPTURE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CaptureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CaptureDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREDLG_H__D6BBE200_2D18_11D5_A72B_0050DA2D4248__INCLUDED_)
