#if !defined(AFX_COODCOMMONVIEW_H__DF0EB26E_285D_4575_96FC_1A68FDEB7A4A__INCLUDED_)
#define AFX_COODCOMMONVIEW_H__DF0EB26E_285D_4575_96FC_1A68FDEB7A4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// COODCommonView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COODCommonView view
#include "Classes.h"
#include "COODView.h" // Generalization

class COODCommonView : public COODView
{
	DECLARE_DYNCREATE(COODCommonView)
private:
	const char *getOleExtension();

// Construction
public:
	COODCommonView();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void setMainPopup();
	virtual void startFork();
	virtual void drawingEpilog();
	virtual void startResize();
	virtual BOOL checkLimitForFigure(int newx,int newy,int *deltax = NIL,int *deltay = NIL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODCommonView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COODCommonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(COODCommonView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTbActivity();
	afx_msg void OnTbBeginActivity();
	afx_msg void OnTbEndActivity();
	afx_msg void OnTbSyncBar();
	afx_msg void OnTbTrigger();
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
	afx_msg void OnCreateAssociationClass();
	afx_msg void OnUpdateCreateAssociationClass(CCmdUI* pCmdUI);
	afx_msg void OnSupressDataMembers();
	afx_msg void OnUpdateSupressDataMembers(CCmdUI* pCmdUI);
	afx_msg void OnSupressMemberFunctions();
	afx_msg void OnUpdateSupressMemberFunctions(CCmdUI* pCmdUI);
	afx_msg void OnClassProperties();
	afx_msg void OnInterfaceProperties();
	afx_msg void OnTbColMessage();
	afx_msg void OnTbColMultiObject();
	afx_msg void OnTbColObject();
	afx_msg void OnSelfDelegationCollaborationObject();
	afx_msg void OnUpdateSelfDelegationCollaborationObject(CCmdUI* pCmdUI);
	afx_msg void OnSelfDelegationDelete();
	afx_msg void OnTbDepCommunication();
	afx_msg void OnTbDepComponent();
	afx_msg void OnTbDepDependency();
	afx_msg void OnTbDepHwConnection();
	afx_msg void OnTbHwnode();
	afx_msg void OnTbTransition();
	afx_msg void OnTbState();
	afx_msg void OnTbInitialState();
	afx_msg void OnTbFinalState();
	afx_msg void OnTbWideState();
	afx_msg void OnTbActor();
	afx_msg void OnTbUsecase();
	afx_msg void OnTbUsecaseAssociates();
	afx_msg void OnTbUsecaseExtends();
	afx_msg void OnTbUsecaseSystem();
	afx_msg void OnTbUsecaseUses();
	afx_msg void OnTbSequenceAsync();
	afx_msg void OnTbSequenceObject();
	afx_msg void OnTbSequenceReturn();
	afx_msg void OnTbSequenceSync();
	afx_msg void OnActivationKillSign();
	afx_msg void OnUpdateActivationKillSign(CCmdUI* pCmdUI);
	//}}AFX_MSG
	// CActivityView
	void OnCreateTrigger();
	void OnCreateActivity();
	void OnCreateSyncBar();
	void OnCreateBeginActivity();
	void OnCreateEndActivity();
	// CClassView
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
	// CCollaborationView
	void OnCreateCollaborationObject();
	void OnCreateCollaborationMultiObject();
	void OnCreateMessageFlow();
	void OnMessageMessageFlow();
	void OnShiftArrowMessageText();
	void OnInvertArrowMessageText();
	// CDeploymentView
	void OnCreateHardwareNode();
	void OnCreateComponentTemplate();
	void OnCreateHWConnection();
	void OnCreateCommunication();
	// CStateView
	void OnCreateState();
	void OnCreateWideState();
	void OnCreateInitialState();
	void OnCreateFinalState();
	void OnCreateTransition();
	// CUseCaseView
//	void OnCreateActor();
	void OnCreateUseCase();
	void OnCreateUseCaseLink();
	void OnCreateUseCaseUsesLink();
	void OnCreateUseCaseExtendsLink();
	void OnCreateSystemBoundary();
	// CSequenceView
	void OnCreateSequenceObject();
	void OnCreateSequenceActivation();
	void OnCreateSyncMessage();
	void OnCreateAsyncMessage();
	void OnCreateReturnMessage();
	void OnCreateSelfDelegation();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COODCOMMONVIEW_H__DF0EB26E_285D_4575_96FC_1A68FDEB7A4A__INCLUDED_)
