#if !defined(AFX_CDEPLOYMENTVIEW_H__91AA8C1C_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CDEPLOYMENTVIEW_H__91AA8C1C_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDeploymentView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeploymentView window
#include "Classes.h"
#include "COODView.h" // Generalization

class CDeploymentView : public COODView
{
	DECLARE_DYNCREATE(CDeploymentView)
private:
	BOOL validWhatTionToDraw();
	void createNewConnection(CPoint point);
// Construction
public:
	CDeploymentView();

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
	void onTbDepCommunication() { OnTbDepCommunication(); }
	void onTbDepComponent() { OnTbDepComponent(); }
	void onTbDepDependency() { OnTbDepDependency(); }
	void onTbDepHwConnection() { OnTbDepHwConnection(); }
	void onTbHwnode() { OnTbHwnode(); }
	void onCreateHardwareNode() { OnCreateHardwareNode(); }
	void onCreateComponentTemplate() { OnCreateComponentTemplate(); }
	void onCreateHWConnection() { OnCreateHWConnection(); }
	void onCreateDependency() { OnCreateDependency(); }
	void onCreateCommunication() { OnCreateCommunication(); }
	void onEditConnectionName() { OnEditConnectionName(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeploymentView)
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDeploymentView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDeploymentView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTbDepCommunication();
	afx_msg void OnTbDepComponent();
	afx_msg void OnTbDepDependency();
	afx_msg void OnTbDepHwConnection();
	afx_msg void OnTbHwnode();
	//}}AFX_MSG
	void OnCreateHardwareNode();
	void OnCreateComponentTemplate();
	void OnCreateHWConnection();
	void OnCreateDependency();
	void OnCreateCommunication();
	void OnEditConnectionName();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDEPLOYMENTVIEW_H__91AA8C1C_7A3E_11D2_AC44_00008610434C__INCLUDED_)
