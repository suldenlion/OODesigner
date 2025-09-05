#if !defined(AFX_PACKAGECOMMENTDLG_H__EF60EBE2_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_PACKAGECOMMENTDLG_H__EF60EBE2_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PackageCommentDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PackageCommentDlg dialog

class PackageCommentDlg : public CDialog
{
// Construction
public:
	PackageCommentDlg(CWnd* pParent = NULL);   // standard constructor
	void loadComment(CStringList *comment);
	void writeComment();
	void clearContents();
private:
	CStringList *_comment;
	CEdit *_pFocusEditCtrl;
// Dialog Data
	//{{AFX_DATA(PackageCommentDlg)
	enum { IDD = IDD_PACKAGE_COMMENT_DLG };
	CEdit	m_editCommentCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PackageCommentDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PackageCommentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEditComment();
	afx_msg void OnSetfocusEditComment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PACKAGECOMMENTDLG_H__EF60EBE2_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_)
