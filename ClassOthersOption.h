#if !defined(AFX_CLASSOTHERSOPTION_H__32FB9C03_9626_46B1_AAD3_038E22CF0767__INCLUDED_)
#define AFX_CLASSOTHERSOPTION_H__32FB9C03_9626_46B1_AAD3_038E22CF0767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MemberOptionDlg.h"

// ClassOthersOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ClassOthersOption dialog

class ClassOthersOption : public MemberOptionDlg
{
// Construction
public:
	ClassOthersOption(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	// repaint 할 필요가 있는 경우에 TRUE 아니면 FALSE ...
	virtual BOOL writeOptionsToClassTextLine();
private:
	void loadTargetDirectoryForCodeGeneration(CString &directory);
	void loadFileNameSpecified(CString &fileName);
	BOOL writeFileNameSpecified(CString &fileName);
// Dialog Data
	//{{AFX_DATA(ClassOthersOption)
	enum { IDD = IDD_CLASS_OTHERS };
	CButton	m_checkCodeCtrl;
	CString	m_editDirectory;
	CString	m_editFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ClassOthersOption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ClassOthersOption)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSOTHERSOPTION_H__32FB9C03_9626_46B1_AAD3_038E22CF0767__INCLUDED_)
