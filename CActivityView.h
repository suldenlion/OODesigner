#if !defined(AFX_CACTIVITYVIEW_H__91AA8C19_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CACTIVITYVIEW_H__91AA8C19_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CActivityView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActivityView window
#include "Classes.h"
#include "COODView.h" // Generalization

class CActivityView : public COODView
{
	DECLARE_DYNCREATE(CActivityView)
private:
	BOOL validWhatTionToDraw();
	void createNewConnection(CPoint point);
// Construction
public:
	CActivityView();
// Attributes
public:

// Operations
public:
	virtual void setPopups();
	virtual void startFork();
	virtual void drawingEpilog();

	void onLButtonDblClk(UINT nFlags, CPoint point) { OnLButtonDblClk(nFlags,point); }
	void onLButtonDown(UINT nFlags, CPoint point) { OnLButtonDown(nFlags,point); }
	void onLButtonUp(UINT nFlags, CPoint point) { OnLButtonUp(nFlags,point); }
	void onMouseMove(UINT nFlags, CPoint point) { OnMouseMove(nFlags,point); }
	void onTbActivity() { OnTbActivity(); }
	void onTbBeginActivity() { OnTbBeginActivity(); }
	void onTbEndActivity() { OnTbEndActivity(); }
	void onTbSyncBar() { OnTbSyncBar(); }
	void onTbTrigger() { OnTbTrigger(); }
	void onCreateTrigger() { OnCreateTrigger(); }
	void onCreateActivity() { OnCreateActivity(); }
	void onCreateSyncBar() { OnCreateSyncBar(); }
	void onCreateBeginActivity() { OnCreateBeginActivity(); }
	void onCreateEndActivity() { OnCreateEndActivity(); }
	void onGuardTrigger() { OnGuardTrigger(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActivityView)
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CActivityView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CActivityView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTbActivity();
	afx_msg void OnTbBeginActivity();
	afx_msg void OnTbEndActivity();
	afx_msg void OnTbSyncBar();
	afx_msg void OnTbTrigger();
	//}}AFX_MSG
	void OnCreateTrigger();
	void OnCreateActivity();
	void OnCreateSyncBar();
	void OnCreateBeginActivity();
	void OnCreateEndActivity();
	void OnGuardTrigger();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACTIVITYVIEW_H__91AA8C19_7A3E_11D2_AC44_00008610434C__INCLUDED_)
