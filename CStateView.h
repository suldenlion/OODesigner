#if !defined(AFX_CSTATEVIEW_H__91AA8C1E_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CSTATEVIEW_H__91AA8C1E_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CStateView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStateView window
#include "Classes.h"
#include "COODView.h" // Generalization

class CStateView : public COODView
{
	DECLARE_DYNCREATE(CStateView)
private:
	BOOL validWhatTionToDraw();
	void createNewConnection(CPoint point);
// Construction
public:
	CStateView();

// Attributes
public:

// Operations
public:
	virtual void setPopups();
	virtual void drawingEpilog();

	void onLButtonDblClk(UINT nFlags, CPoint point) { OnLButtonDblClk(nFlags,point); }
	void onLButtonDown(UINT nFlags, CPoint point) { OnLButtonDown(nFlags,point); }
	void onLButtonUp(UINT nFlags, CPoint point) { OnLButtonUp(nFlags,point); }
	void onMouseMove(UINT nFlags, CPoint point) { OnMouseMove(nFlags,point); }
	void onTbTransition() { OnTbTransition(); }
	void onTbState() { OnTbState(); }
	void onTbInitialState() { OnTbInitialState(); }
	void onTbFinalState() { OnTbFinalState(); }
	void onTbWideState() { OnTbWideState(); }
	void onCreateState() { OnCreateState(); }
	void onCreateWideState() { OnCreateWideState(); }
	void onCreateInitialState() { OnCreateInitialState(); }
	void onCreateFinalState() { OnCreateFinalState(); }
	void onCreateTransition() { OnCreateTransition(); }
	void onEventTransition() { OnEventTransition(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStateView)
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStateView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStateView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTbTransition();
	afx_msg void OnTbState();
	afx_msg void OnTbInitialState();
	afx_msg void OnTbFinalState();
	afx_msg void OnTbWideState();
	//}}AFX_MSG
	void OnCreateState();
	void OnCreateWideState();
	void OnCreateInitialState();
	void OnCreateFinalState();
	void OnCreateTransition();
	void OnEventTransition();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTATEVIEW_H__91AA8C1E_7A3E_11D2_AC44_00008610434C__INCLUDED_)
