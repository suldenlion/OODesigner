#if !defined(AFX_COMMENTDLG_H__97611CD4_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_COMMENTDLG_H__97611CD4_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CommentDlg.h : header file
//
#include "Classes.h"
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CommentDlg dialog

class CommentDlg : public MemberOptionDlg
{
DECLARE_DYNAMIC(CommentDlg)
private:
	CEdit *_pFocusEditCtrl;
	static const int BoundaryGapX;
	static const int BoundaryGapY;
	static const int BoundaryGapXForEditBox;
	static const int BoundaryGapYForEditBox;

// Construction
public:
	CommentDlg(const char* forName,CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();
	virtual void resizeDialogToFitPropertyDialog(RECT propRect);

// Dialog Data
	//{{AFX_DATA(CommentDlg)
	enum { IDD = IDD_COMMENT_DLG };
	CEdit	m_editCommentCtrl;
	CString	m_editComment;
	CString	m_staticForName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CommentDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CommentDlg)
	afx_msg void OnKillfocusEditComment();
	afx_msg void OnSetfocusEditComment();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMENTDLG_H__97611CD4_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_)
