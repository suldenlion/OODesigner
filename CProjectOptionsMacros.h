#if !defined(AFX_CPROJECTOPTIONSMACROS_H__8BCC9620_1159_11D5_A80A_0050DA2D4248__INCLUDED_)
#define AFX_CPROJECTOPTIONSMACROS_H__8BCC9620_1159_11D5_A80A_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CProjectOptionsMacros.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsMacros dialog

class CProjectOptionsMacros : public CDialog
{
private:
	CString _language;
	void writeAMacro(CStringList &theMacro,CEdit &theEditCtrl);
// Construction
public:
	CProjectOptionsMacros(CWnd* pParent = NULL);   // standard constructor
	void languageSelected(CString &language);
	void writeMacros();

// Dialog Data
	//{{AFX_DATA(CProjectOptionsMacros)
	enum { IDD = IDD_PROJECT_OPTIONS_MACROS };
	CEdit	m_editSourceFileCtrl;
	CEdit	m_editHeaderFileCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectOptionsMacros)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectOptionsMacros)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPROJECTOPTIONSMACROS_H__8BCC9620_1159_11D5_A80A_0050DA2D4248__INCLUDED_)
