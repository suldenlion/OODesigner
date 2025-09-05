#if !defined(AFX_CUSECASEVIEW_H__91AA8C1F_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CUSECASEVIEW_H__91AA8C1F_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CUseCaseView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUseCaseView window
#include "Classes.h"
#include "COODView.h" // Generalization

class CUseCaseView : public COODView
{
	DECLARE_DYNCREATE(CUseCaseView)
private:
	BOOL validWhatTionToDraw();
	void createNewConnection(CPoint point);
// Construction
public:
	CUseCaseView();

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
	void onTbActor() { OnTbActor(); }
	void onTbUsecase() { OnTbUsecase(); }
	void onTbUsecaseAssociates() { OnTbUsecaseAssociates(); }
	void onTbUsecaseExtends() { OnTbUsecaseExtends(); }
	void onTbUsecaseSystem() { OnTbUsecaseSystem(); }
	void onTbUsecaseUses() { OnTbUsecaseUses(); }
	void onCreateUseCase() { OnCreateUseCase(); }
	void onCreateUseCaseLink() { OnCreateUseCaseLink(); }
	void onCreateUseCaseUsesLink() { OnCreateUseCaseUsesLink(); }
	void onCreateUseCaseExtendsLink() { OnCreateUseCaseExtendsLink(); }
	void onCreateSystemBoundary() { OnCreateSystemBoundary(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseCaseView)
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUseCaseView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUseCaseView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTbUsecase();
	afx_msg void OnTbUsecaseAssociates();
	afx_msg void OnTbUsecaseExtends();
	afx_msg void OnTbUsecaseSystem();
	afx_msg void OnTbUsecaseUses();
	//}}AFX_MSG
	void OnCreateUseCase();
	void OnCreateUseCaseLink();
	void OnCreateUseCaseUsesLink();
	void OnCreateUseCaseExtendsLink();
	void OnCreateSystemBoundary();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSECASEVIEW_H__91AA8C1F_7A3E_11D2_AC44_00008610434C__INCLUDED_)
