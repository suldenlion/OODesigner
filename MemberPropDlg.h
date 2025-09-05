#if !defined(AFX_MEMBERPROPDLG_H__3A397B04_3E48_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_MEMBERPROPDLG_H__3A397B04_3E48_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MemberPropDlg.h : header file
//

#define DATA_MEMBER			(0)
#define MEMBER_FUNCTION		(1)

/////////////////////////////////////////////////////////////////////////////
// MemberPropDlg dialog
#include "Classes.h"
#include "PropCommonDlg.h"

class MemberPropDlg : public PropCommonDlg
{
public:
	static const int ClientMinWidth;
	static const int ClientMinHeight;
	static const int MinWidth;
	static const int MinHeight;
	static const int BoundaryGapX;
	static const int BoundaryGapY;
private:
	int _initialWidth;
	int _initialHeight;
	int _index;
	int _whichMember;
	CDialog *_generalOption;
	CommentDlg *_commentOption;
	MethodBodyDlg *_methodBodyOption;
// Construction
public:
	MemberPropDlg(int whichMember,const char* language, CWnd* pParent = NULL);   // standard constructor
	virtual ~MemberPropDlg();
	void loadFromClassTextLine(COODView *aView,ClassTextLine *aLine,int index,ClassContent *aContent,CString &className,CString &packageName);
	virtual void loadFromClassTextLine();
	virtual BOOL saveToClassTextLine();
	virtual void clearContents();
	void resizeIfNeededOnCreate();
	void setInitialWidth(int w) { 
		_initialWidth = w; 
	}
	void setInitialHeight(int h) { 
		_initialHeight = h; 
	}
	int getInitialWidth() {
		return _initialWidth;
	}
	int getInitialHeight() {
		return _initialHeight;
	}
private:
	void repositionBotton(RECT dialogRect,CButton& buttonCtrl);
	void resizeTabDialog(RECT dialogRect,MemberOptionDlg* tabDialog);
	void repositionAndResizeSubcontrols();
// Dialog Data
	//{{AFX_DATA(MemberPropDlg)
	enum { IDD = IDD_MEMBER_PROP_DLG };
	CButton	m_buttonOKCtrl;
	CButton	m_buttonCancelCtrl;
	CButton	m_buttonPrevCtrl;
	CButton	m_buttonNextCtrl;
	CTabCtrl	m_optionsTab;
	CStatic	m_staticClassNameCtrl;
	CEdit	m_editMemberNameCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MemberPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MemberPropDlg)
	afx_msg void OnSelchangeTabMemberProp(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonPrev();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMBERPROPDLG_H__3A397B04_3E48_11D4_AED4_00A0C9BA6734__INCLUDED_)
