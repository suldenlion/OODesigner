#if !defined(AFX_MEMBEROPTIONDLG_H__E8D7C1E3_238A_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_MEMBEROPTIONDLG_H__E8D7C1E3_238A_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MemberOptionDlg.h : header file
//
#include "Classes.h"
#include "KtgMacro.h"
/////////////////////////////////////////////////////////////////////////////
// MemberOptionDlg dialog

class MemberOptionDlg : public CDialog
{
DECLARE_DYNAMIC(MemberOptionDlg)
// Construction
protected:
	ClassTextLine *_currentLine;
	ClassContent *_classContent;
	BOOL _modifiedFlag;

	void loadStereotype(CString &stereotype);
	BOOL writeStereotype(CString &stereotype);
	void loadInnerClassOf(CString &innerClassOf);
	BOOL writeInnerClassOf(CString &innerClassOf);
	void loadType(CComboBox *typeCombo,CString &typeString);
	void writeType(CComboBox *typeCombo,CString &typeString);
	void loadDefaultValue(CEdit *defaultValueEdit,CStringList &theValue);
	void writeDefaultValue(CEdit *defaultValueEdit,CStringList &theValue);
	void loadVisibilityForMember(CString &visibility);
	void loadVisibilityForClass(CString &visibility);
	BOOL writeVisibilityForMember(CString &visibility);
	BOOL writeVisibilityForClass(CString &visibility);
	void loadButtonState(CButton *aButton,BOOL state);
	BOOL writeButtonState(CButton *aButton,BOOL &state);
	MemberOptionDlg(UINT id,CWnd* pParent = NULL);   // standard constructor
	void refreshAllViews();
public:
	virtual void clearContents() {
		setModifiedFlag(FALSE);
	}
	virtual void loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName) = 0;
	// repaint 할 필요가 있는 경우에 TRUE 아니면 FALSE ...
	virtual BOOL writeOptionsToClassTextLine() = 0;
	virtual void resizeDialogToFitPropertyDialog(RECT propRect) {}
	void setCurrentLine(ClassTextLine *aLine) {
		_currentLine = aLine;
	}
	void resetCurrentLine() {
		_currentLine = NIL;
		_classContent = NIL;
	}
	void setModifiedFlag(BOOL flag) {
		_modifiedFlag = flag;
	}
	BOOL isModified() {
		return _modifiedFlag;
	}
// Dialog Data
	//{{AFX_DATA(MemberOptionDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MemberOptionDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MemberOptionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMBEROPTIONDLG_H__E8D7C1E3_238A_11D4_AED4_00A0C9BA6734__INCLUDED_)
