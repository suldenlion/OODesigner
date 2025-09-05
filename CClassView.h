#if !defined(AFX_CCLASSVIEW_H__91AA8C1B_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CCLASSVIEW_H__91AA8C1B_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CClassView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClassView window
#include "Classes.h"
#include "COODView.h" // Generalization

class CClassView : public COODView
{
	DECLARE_DYNCREATE(CClassView)
private:
	BOOL validWhatTionToDraw();
	void createNewConnection(CPoint point);
// Construction
public:
	CClassView();

// Attributes
public:

// Operations
public:
	virtual void setPopups();
	virtual void startFork();
	virtual void drawingEpilog();

	void onLButtonDown(UINT nFlags, CPoint point) { OnLButtonDown(nFlags,point); }
	void onMouseMove(UINT nFlags, CPoint point) { OnMouseMove(nFlags,point); }
	void onLButtonUp(UINT nFlags, CPoint point) { OnLButtonUp(nFlags,point); }
	void onLButtonDblClk(UINT nFlags, CPoint point) { OnLButtonDblClk(nFlags,point); }
	void onTbAggregation() { OnTbAggregation(); }
	void onTbAssociation() { OnTbAssociation(); }
	void onTbClasstemplate() { OnTbClasstemplate(); }
	void onTbComposition() { OnTbComposition(); }
	void onTbDependency() { OnTbDependency(); }
	void onTbGeneralization() { OnTbGeneralization(); }
	void onTbInterface() { OnTbInterface(); }
	void onTbPackage() { OnTbPackage(); }
	void onTbRefinement() { OnTbRefinement(); }
	void onTbTemplateclass() { OnTbTemplateclass(); }
	void onTbUtility() { OnTbUtility(); }
	void onTbWidePackage() { OnTbWidePackage(); }
	void onCreateAssociationClass() { OnCreateAssociationClass(); }
	void onUpdateCreateAssociationClass(CCmdUI* pCmdUI) { OnUpdateCreateAssociationClass(pCmdUI); }
	void onSupressDataMembers() { OnSupressDataMembers(); }
	void onUpdateSupressDataMembers(CCmdUI* pCmdUI) { OnUpdateSupressDataMembers(pCmdUI); }
	void onSupressMemberFunctions() { OnSupressMemberFunctions(); }
	void onUpdateSupressMemberFunctions(CCmdUI* pCmdUI) { OnUpdateSupressMemberFunctions(pCmdUI); }
	void onClassProperties() { OnClassProperties(); }
	void onInterfaceProperties() { OnInterfaceProperties(); }
	void onCreateClassTemplate() { OnCreateClassTemplate(); }
	void onCreateInterface() { OnCreateInterface(); }
	void onCreateUtility() { OnCreateUtility(); }
	void onCreateTemplateClass() { OnCreateTemplateClass(); }
	void onCreatePackageTemplate() { OnCreatePackageTemplate(); }
	void onCreateWidePackage() { OnCreateWidePackage(); }
	void onCreateGeneralization() { OnCreateGeneralization(); }
	void onCreateRefinement() { OnCreateRefinement(); }
	void onCreateAggregation() { OnCreateAggregation(); }
	void onCreateAssociation() { OnCreateAssociation(); }
	void onCreateComposition() { OnCreateComposition(); }
	void onCreateDependency() { OnCreateDependency(); }
	void onChangeClassSize() { OnChangeClassSize(); }
	void onEditConnectionName() { OnEditConnectionName(); }
	void onEditMultiplicity() { OnEditMultiplicity(); }
	void onEditQualification() { OnEditQualification(); }
	void onCreateInterfacePort() { OnCreateInterfacePort(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassView)
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClassView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClassView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTbAggregation();
	afx_msg void OnTbAssociation();
	afx_msg void OnTbClasstemplate();
	afx_msg void OnTbComposition();
	afx_msg void OnTbDependency();
	afx_msg void OnTbGeneralization();
	afx_msg void OnTbInterface();
	afx_msg void OnTbPackage();
	afx_msg void OnTbRefinement();
	afx_msg void OnTbTemplateclass();
	afx_msg void OnTbUtility();
	afx_msg void OnTbWidePackage();
	afx_msg void OnPopupOpenPackage();
	afx_msg void OnUpdatePopupOpenPackage(CCmdUI* pCmdUI);
	afx_msg void OnCreateAssociationClass();
	afx_msg void OnUpdateCreateAssociationClass(CCmdUI* pCmdUI);
	afx_msg void OnSupressDataMembers();
	afx_msg void OnUpdateSupressDataMembers(CCmdUI* pCmdUI);
	afx_msg void OnSupressMemberFunctions();
	afx_msg void OnUpdateSupressMemberFunctions(CCmdUI* pCmdUI);
	afx_msg void OnClassProperties();
	afx_msg void OnInterfaceProperties();
	afx_msg void OnGenerateCode();
	afx_msg void OnUpdateGenerateCode(CCmdUI* pCmdUI);
	afx_msg void OnToolsGenerateCode();
	afx_msg void OnUpdateToolsGenerateCode(CCmdUI* pCmdUI);
	//}}AFX_MSG
	void OnCreateClassTemplate();
	void OnCreateInterface();
	void OnCreateUtility();
	void OnCreateTemplateClass();
	void OnCreatePackageTemplate();
	void OnCreateWidePackage();
	void OnCreateGeneralization();
	void OnCreateRefinement();
	void OnCreateAggregation();
	void OnCreateAssociation();
	void OnCreateComposition();
	void OnCreateDependency();
	void OnChangeClassSize();
	void OnEditConnectionName();
	void OnEditMultiplicity();
	void OnEditQualification();
	void OnCreateInterfacePort();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCLASSVIEW_H__91AA8C1B_7A3E_11D2_AC44_00008610434C__INCLUDED_)
