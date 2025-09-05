#if !defined(AFX_CPROJECTOPTIONSGENERAL_H__5C7CD802_1B7B_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPROJECTOPTIONSGENERAL_H__5C7CD802_1B7B_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CProjectOptionsGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsGeneral dialog
class CProjectOptionsCodeGen;
class CProjectOptionsMacros;

class CProjectOptionsGeneral : public CDialog
{
private:
	CProjectOptionsCodeGen *_codegenOption;
	CProjectOptionsMacros *_macrosOption;
// Construction
public:
	CProjectOptionsGeneral(CWnd* pParent = NULL);   // standard constructor
	void setProjectOptionsCodeGen(CProjectOptionsCodeGen *codegenOption) {
		_codegenOption = codegenOption;
	}
	void setProjectOptionsMacros(CProjectOptionsMacros *macrosOption) {
		_macrosOption = macrosOption;
	}

// Dialog Data
	//{{AFX_DATA(CProjectOptionsGeneral)
	enum { IDD = IDD_PROJECT_OPTIONS_GENERAL };
	CString	m_comboLanguage;
	CString	m_editAuthor;
	CString	m_editOrganization;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectOptionsGeneral)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectOptionsGeneral)
	afx_msg void OnSelchangeComboLanguage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPROJECTOPTIONSGENERAL_H__5C7CD802_1B7B_11D4_AED4_00A0C9BA6734__INCLUDED_)
