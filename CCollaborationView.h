#if !defined(AFX_CCOLLABORATIONVIEW_H__ADFC18E2_CDB9_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_CCOLLABORATIONVIEW_H__ADFC18E2_CDB9_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CCollaborationView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCollaborationView window

#include "Classes.h"
#include "COODView.h" // Generalization

class CCollaborationView : public COODView
{
	DECLARE_DYNCREATE(CCollaborationView)
private:
	BOOL validWhatTionToDraw();
	void createNewConnection(CPoint point);
// Construction
public:
	CCollaborationView();

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
	void onTbColMessage() { OnTbColMessage(); }
	void onTbColMultiObject() { OnTbColMultiObject(); }
	void onTbColObject() { OnTbColObject(); }
	void onSelfDelegationCollaborationObject() { OnSelfDelegationCollaborationObject(); }
	void onUpdateSelfDelegationCollaborationObject(CCmdUI* pCmdUI) { OnUpdateSelfDelegationCollaborationObject(pCmdUI); }
	void onSelfDelegationDelete() { OnSelfDelegationDelete(); }
	void onCreateCollaborationObject() { OnCreateCollaborationObject(); }
	void onCreateCollaborationMultiObject() { OnCreateCollaborationMultiObject(); }
	void onCreateMessageFlow() { OnCreateMessageFlow(); }
	void onMessageMessageFlow() { OnMessageMessageFlow(); }
	void onShiftArrowMessageText() { OnShiftArrowMessageText(); }
	void onInvertArrowMessageText() { OnInvertArrowMessageText(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollaborationView)
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCollaborationView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCollaborationView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTbColMessage();
	afx_msg void OnTbColMultiObject();
	afx_msg void OnTbColObject();
	afx_msg void OnSelfDelegationCollaborationObject();
	afx_msg void OnUpdateSelfDelegationCollaborationObject(CCmdUI* pCmdUI);
	afx_msg void OnSelfDelegationDelete();
	//}}AFX_MSG
	void OnCreateCollaborationObject();
	void OnCreateCollaborationMultiObject();
	void OnCreateMessageFlow();
	void OnMessageMessageFlow();
	void OnShiftArrowMessageText();
	void OnInvertArrowMessageText();
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCOLLABORATIONVIEW_H__ADFC18E2_CDB9_11D3_BBC8_00A0C9BA6734__INCLUDED_)
