#if !defined(AFX_VCPPMAPEDITOR_H__26DECAB2_460A_4DD2_956A_DA5664BD3A58__INCLUDED_)
#define AFX_VCPPMAPEDITOR_H__26DECAB2_460A_4DD2_956A_DA5664BD3A58__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VCPPMapEditor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VCPPMapEditor dialog
#include "Classes.h"

class VCPPMapEditor : public CDialog
{
// Construction
public:
	VCPPMapEditor(CString &mapName,ClassContent *aContent,CWnd* pParent = NULL);   // standard constructor
private:
	CString _mapName;
	CString _className;
	ClassContent *_classContent;
	CEdit *_pFocusEditCtrl;
	CStringList *_currentMap;

// Dialog Data
	//{{AFX_DATA(VCPPMapEditor)
	enum { IDD = IDD_VCPP_MAP_EDITOR };
	CEdit	m_editCtrl;
	CString	m_staticBegin;
	CString	m_staticEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VCPPMapEditor)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VCPPMapEditor)
	afx_msg void OnKillfocusEdit();
	afx_msg void OnSetfocusEdit();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCPPMAPEDITOR_H__26DECAB2_460A_4DD2_956A_DA5664BD3A58__INCLUDED_)
