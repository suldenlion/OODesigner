#if !defined(AFX_PROPCOMMONDLG_H__5FC5B282_3B19_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_PROPCOMMONDLG_H__5FC5B282_3B19_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropCommonDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// PropCommonDlg dialog
#include "TabDlgWithName.h"

class PropCommonDlg : public TabDlgWithName
{
	DECLARE_DYNAMIC(PropCommonDlg)
// Construction
protected:
	PropCommonDlg(UINT id,CWnd* pParent = NULL);   // standard constructor

	COODView *_pView;
	ClassTextLine *_currentLine;
	ClassContent *_classContent;
	CString _languageName;
	CString _className;
	CString _packageName;
	CStatic *_pStaticClassNameCtrl;
public:
	void deactivate() {
		OnCancel();
	}
	BOOL ShowWindow(int nCmdShow);
	void resetCurrentLine();
	virtual void loadFromClassTextLine();
	virtual BOOL saveToClassTextLine();
	virtual void clearContents();
	CString &className() { return _className; }
	CString &packageName() { return _packageName; }
	COODView *pView() { return _pView; }

// Dialog Data
	//{{AFX_DATA(PropCommonDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PropCommonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PropCommonDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPCOMMONDLG_H__5FC5B282_3B19_11D4_AED4_00A0C9BA6734__INCLUDED_)
