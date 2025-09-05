#if !defined(AFX_CLASSPROPDLG_H__3A397B02_3E48_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CLASSPROPDLG_H__3A397B02_3E48_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClassPropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ClassPropDlg dialog
#include "Classes.h"
#include "PropCommonDlg.h"

class ClassPropDlg : public PropCommonDlg
{
	DECLARE_DYNAMIC(ClassPropDlg)
private:
	MemberOptionDlg *_generalOption;
	DataMembersOption *_dataMembersOption;
	MemberFunctionsOption *_memberFunctionsOption;
	ClassDocumentDlg *_documentOption;
	VCPPClassPropMaps *_vcppMapsOption; 
	ClassOthersOption *_classOthersOption;
// Construction
public:
	ClassPropDlg(const char *language,CWnd* pParent = NULL);   // standard constructor
	virtual ~ClassPropDlg();
	void loadFromClassContent(COODView *theView,ClassContent *theContent,CString &className,CString &packageName);
	virtual BOOL saveToClassTextLine();
	void reloadClassMembers();
	// 이 함수는 VCPPClassPropMaps에 의해서만 호출됨
	void setMfcClassFlag();

// Dialog Data
	//{{AFX_DATA(ClassPropDlg)
	enum { IDD = IDD_CLASS_PROP_DLG };
	CTabCtrl	m_optionsTab;
	CStatic	m_staticClassNameCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ClassPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ClassPropDlg)
	afx_msg void OnSelchangeTabClassProp(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSPROPDLG_H__3A397B02_3E48_11D4_AED4_00A0C9BA6734__INCLUDED_)
