#if !defined(AFX_VCPPCLASSPROPMAPS_H__5E475DFC_3452_4C60_A91A_6D581442A7A7__INCLUDED_)
#define AFX_VCPPCLASSPROPMAPS_H__5E475DFC_3452_4C60_A91A_6D581442A7A7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VCPPClassPropMaps.h : header file
//

#include "Classes.h"
#include "MemberOptionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// VCPPClassPropMaps dialog

class VCPPClassPropMaps : public MemberOptionDlg
{
	DECLARE_DYNAMIC(VCPPClassPropMaps)

// Construction
public:
	VCPPClassPropMaps(CWnd* pParent = NULL);   // standard constructor
	virtual void clearContents();
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName);
	virtual BOOL writeOptionsToClassTextLine();
private:
// Dialog Data
	//{{AFX_DATA(VCPPClassPropMaps)
	enum { IDD = IDD_VCPP_CLASS_PROP_MAPS };
	CListBox	m_listSystemMapsCtrl;
	CListBox	m_listClassMapsCtrl;
	CButton	m_buttonAddCtrl;
	CButton	m_buttonEditCtrl;
	CButton	m_buttonDeleteCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VCPPClassPropMaps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VCPPClassPropMaps)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusListClassMaps();
	afx_msg void OnSetfocusListSystemMaps();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonEdit();
	afx_msg void OnDblclkListClassMaps();
	afx_msg void OnDblclkListSystemMaps();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCPPCLASSPROPMAPS_H__5E475DFC_3452_4C60_A91A_6D581442A7A7__INCLUDED_)
