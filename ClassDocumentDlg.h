#if !defined(AFX_CLASSDOCUMENTDLG_H__496E1B60_117B_11D5_A80A_0050DA2D4248__INCLUDED_)
#define AFX_CLASSDOCUMENTDLG_H__496E1B60_117B_11D5_A80A_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClassDocumentDlg.h : header file
//

#include "Classes.h"
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// ClassDocumentDlg dialog

class ClassDocumentDlg : public MemberOptionDlg
{
DECLARE_DYNAMIC(ClassDocumentDlg)
private:
	CStringList *_currentDocument;
	CEdit *_pFocusEditCtrl;
	int _whichRadio;

// Construction
public:
	ClassDocumentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();
private:
	void setStaticTitle(int which);
	void loadDocument();

// Dialog Data
	//{{AFX_DATA(ClassDocumentDlg)
	enum { IDD = IDD_CLASS_DOCUMENT_DLG };
	CButton	m_radioHFMiddleCtrl;
	CButton	m_radioSFFrontCtrl;
	CButton	m_radioHFEndCtrl;
	CEdit	m_editDocumentCtrl;
	CButton	m_radioHFFrontCtrl;
	CString	m_staticBegin;
	CString	m_staticEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ClassDocumentDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ClassDocumentDlg)
	afx_msg void OnSetfocusEditDocument();
	afx_msg void OnKillfocusEditDocument();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonSave();
	afx_msg void OnRadioHfEnd();
	afx_msg void OnRadioHfFront();
	afx_msg void OnRadioSfFront();
	afx_msg void OnRadioHfMiddle();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSDOCUMENTDLG_H__496E1B60_117B_11D5_A80A_0050DA2D4248__INCLUDED_)
