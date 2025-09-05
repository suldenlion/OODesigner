#if !defined(AFX_CINPLACEFRAME_H__FBB20020_64E6_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_CINPLACEFRAME_H__FBB20020_64E6_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CInPlaceFrame.h : header file
//
#include "CustomToolBar.h"

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame frame

class CInPlaceFrame : public COleIPFrameWnd
{
	DECLARE_DYNCREATE(CInPlaceFrame)
protected:
	CInPlaceFrame();           // protected constructor used by dynamic creation

// Operations
private:
	BOOL createModelControlBar(CFrameWnd* pWndFrame);
	void insertInsertPulldownMenu(CMenu *pInsertMenu); // COODCommonFrm에 있는 함수 내용과 완조니 같음

// Attributes
private:
	BOOL _onActivateCalledFlag;
	CString _insertMenuID;
// Operations
public:
	void getZoomValue(CString &value);
	void setZoomValue(const char *value);
	void setZoomValue(CDocument *pDoc);
	void setZoomValue(COODView *pView);
	void setTextOnStatusBar(const char *text,int field = 0);
	void setPositionOnStatusBar(int x,int y,int field = 1);
	void userMsg(const char*);
	void userMsg(const char*,int n);
	void userMsgForUsingUpperCaseAsBlank(char *,char *);
	CToolBarCtrl *getModelToolBarCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceFrame)
	protected:
	virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInPlaceFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	modelDiagramToolBar;
	CustomToolBar  m_wndCustomBar;
	COleDropTarget	m_dropTarget;
	COleResizeBar   m_wndResizeBar;

	// Generated message map functions
	//{{AFX_MSG(CInPlaceFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	afx_msg void OnViewCustombar();
	afx_msg void OnUpdateViewCustombar(CCmdUI* pCmdUI);
	afx_msg void OnInitMenu(CMenu* pMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CINPLACEFRAME_H__FBB20020_64E6_11D5_A72B_0050DA2D4248__INCLUDED_)
