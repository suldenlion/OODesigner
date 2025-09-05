#if !defined(AFX_CSEQUENCEVIEW_H__BF9456A2_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_CSEQUENCEVIEW_H__BF9456A2_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSequenceView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSequenceView window

#include "Classes.h"
#include "COODView.h" // Generalization

class CSequenceView : public COODView
{
	DECLARE_DYNCREATE(CSequenceView)
private:
	BOOL validWhatTionToDraw();
	void createNewConnection(CPoint point);
// Construction
public:
	CSequenceView();

// Attributes
public:

// Operations
public:
	virtual void setPopups();
	virtual void startResize();
	virtual void drawingEpilog();
	virtual BOOL checkLimitForFigure(int newx,int newy,int *deltax = NIL,int *deltay = NIL);

	void onLButtonDblClk(UINT nFlags, CPoint point) { OnLButtonDblClk(nFlags,point); }
	void onLButtonDown(UINT nFlags, CPoint point) { OnLButtonDown(nFlags,point); }
	void onLButtonUp(UINT nFlags, CPoint point) { OnLButtonUp(nFlags,point); }
	void onMouseMove(UINT nFlags, CPoint point) { OnMouseMove(nFlags,point); }
	void onTbSequenceAsync() { OnTbSequenceAsync(); }
	void onTbSequenceObject() { OnTbSequenceObject(); }
	void onTbSequenceReturn() { OnTbSequenceReturn(); }
	void onTbSequenceSync() { OnTbSequenceSync(); }
	void onActivationKillSign() { OnActivationKillSign(); }
	void onUpdateActivationKillSign(CCmdUI* pCmdUI) { OnUpdateActivationKillSign(pCmdUI); }
	void onCreateSequenceObject() { OnCreateSequenceObject(); }
	void onCreateSequenceActivation() { OnCreateSequenceActivation(); }
	void onCreateSyncMessage() { OnCreateSyncMessage(); }
	void onCreateAsyncMessage() { OnCreateAsyncMessage(); }
	void onCreateReturnMessage() { OnCreateReturnMessage(); }
	void onEditConnectionName() { OnEditConnectionName(); }
	void onCreateSelfDelegation() { OnCreateSelfDelegation(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSequenceView)
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSequenceView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSequenceView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTbSequenceAsync();
	afx_msg void OnTbSequenceObject();
	afx_msg void OnTbSequenceReturn();
	afx_msg void OnTbSequenceSync();
	afx_msg void OnActivationKillSign();
	afx_msg void OnUpdateActivationKillSign(CCmdUI* pCmdUI);
	//}}AFX_MSG
	void OnCreateSequenceObject();
	void OnCreateSequenceActivation();
	void OnCreateSyncMessage();
	void OnCreateAsyncMessage();
	void OnCreateReturnMessage();
	void OnEditConnectionName();
	void OnCreateSelfDelegation();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSEQUENCEVIEW_H__BF9456A2_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_)
