#if !defined(AFX_METHODBODYDLG_H__97611CD3_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_METHODBODYDLG_H__97611CD3_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MethodBodyDlg.h : header file
//
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// MethodBodyDlg dialog

class MethodBodyDlg : public MemberOptionDlg
{
DECLARE_DYNAMIC(MethodBodyDlg)
private:
	CEdit *_pFocusEditCtrl;
	static const int BoundaryGapX;
	static const int BoundaryGapY;
	static const int BoundaryGapXForEditBox;
	static const int BoundaryGapYForEditBox;
	static const int BoundaryGapXForBrace;
	static const int BoundaryGapYForBrace;

// Construction
public:
	MethodBodyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();
	virtual void resizeDialogToFitPropertyDialog(RECT propRect);

// Dialog Data
	//{{AFX_DATA(MethodBodyDlg)
	enum { IDD = IDD_METHOD_BODY_DLG };
	CStatic	m_staticClosingBrace;
	CButton	m_buttonMore;
	CComboBox	m_comboTypeCtrl;
	CStatic	m_staticSignature;
	CEdit	m_editMethodBodyCtrl;
	CString	m_editMethodBody;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MethodBodyDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MethodBodyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDropdownComboType();
	afx_msg void OnEditchangeComboType();
	afx_msg void OnKillfocusEditMethodBody();
	afx_msg void OnSetfocusEditMethodBody();
	afx_msg void OnButtonMore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METHODBODYDLG_H__97611CD3_21DD_11D4_AED4_00A0C9BA6734__INCLUDED_)
