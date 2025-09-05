// COODCommonView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "COODCommonView.h"
#include "COODCommonDoc.h"
#include "Views.h"
#include "Figures.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COODCommonView

IMPLEMENT_DYNCREATE(COODCommonView, COODView)

COODCommonView::COODCommonView()
{
}

COODCommonView::~COODCommonView()
{
}

const char *COODCommonView::getOleExtension()
{
	COODDoc *pDoc = GetDocument();
	if (pDoc == NIL) return NIL;
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODDoc))) return NIL;
	return ((COODDoc*)pDoc)->extensionNameAfterLoad;
}

void COODCommonView::setMainPopup()
{
	CString extension = getOleExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		_mainPopup = theAppPtr->theClassMainPopup;
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		_mainPopup = theAppPtr->theUseCaseMainPopup;
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		_mainPopup = theAppPtr->theSequenceMainPopup;
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		_mainPopup = theAppPtr->theCollaborationMainPopup;
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		_mainPopup = theAppPtr->theStateMainPopup;
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		_mainPopup = theAppPtr->theActivityMainPopup;
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		_mainPopup = theAppPtr->theDeploymentMainPopup;
	}
}

BEGIN_MESSAGE_MAP(COODCommonView, COODView)
	//{{AFX_MSG_MAP(COODCommonView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TB_ACTIVITY, OnTbActivity)
	ON_COMMAND(ID_TB_BEGIN_ACTIVITY, OnTbBeginActivity)
	ON_COMMAND(ID_TB_END_ACTIVITY, OnTbEndActivity)
	ON_COMMAND(ID_TB_SYNC_BAR, OnTbSyncBar)
	ON_COMMAND(ID_TB_TRIGGER, OnTbTrigger)
	ON_COMMAND(ID_TB_AGGREGATION, OnTbAggregation)
	ON_COMMAND(ID_TB_ASSOCIATION, OnTbAssociation)
	ON_COMMAND(ID_TB_CLASSTEMPLATE, OnTbClasstemplate)
	ON_COMMAND(ID_TB_COMPOSITION, OnTbComposition)
	ON_COMMAND(ID_TB_DEPENDENCY, OnTbDependency)
	ON_COMMAND(ID_TB_GENERALIZATION, OnTbGeneralization)
	ON_COMMAND(ID_TB_INTERFACE, OnTbInterface)
	ON_COMMAND(ID_TB_PACKAGE, OnTbPackage)
	ON_COMMAND(ID_TB_REFINEMENT, OnTbRefinement)
	ON_COMMAND(ID_TB_TEMPLATECLASS, OnTbTemplateclass)
	ON_COMMAND(ID_TB_UTILITY, OnTbUtility)
	ON_COMMAND(ID_TB_WIDE_PACKAGE, OnTbWidePackage)
	ON_COMMAND(ID_CREATE_ASSOCIATION_CLASS, OnCreateAssociationClass)
	ON_UPDATE_COMMAND_UI(ID_CREATE_ASSOCIATION_CLASS, OnUpdateCreateAssociationClass)
	ON_COMMAND(ID_SUPRESS_DATA_MEMBERS, OnSupressDataMembers)
	ON_UPDATE_COMMAND_UI(ID_SUPRESS_DATA_MEMBERS, OnUpdateSupressDataMembers)
	ON_COMMAND(ID_SUPRESS_MEMBER_FUNCTIONS, OnSupressMemberFunctions)
	ON_UPDATE_COMMAND_UI(ID_SUPRESS_MEMBER_FUNCTIONS, OnUpdateSupressMemberFunctions)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_INTERFACE_PROPERTIES, OnInterfaceProperties)
	ON_COMMAND(ID_TB_COL_MESSAGE, OnTbColMessage)
	ON_COMMAND(ID_TB_COL_MULTI_OBJECT, OnTbColMultiObject)
	ON_COMMAND(ID_TB_COL_OBJECT, OnTbColObject)
	ON_COMMAND(ID_SELF_DELEGATION_COLLABORATION_OBJECT, OnSelfDelegationCollaborationObject)
	ON_UPDATE_COMMAND_UI(ID_SELF_DELEGATION_COLLABORATION_OBJECT, OnUpdateSelfDelegationCollaborationObject)
	ON_COMMAND(ID_SELF_DELEGATION_DELETE, OnSelfDelegationDelete)
	ON_COMMAND(ID_TB_DEP_COMMUNICATION, OnTbDepCommunication)
	ON_COMMAND(ID_TB_DEP_COMPONENT, OnTbDepComponent)
	ON_COMMAND(ID_TB_DEP_DEPENDENCY, OnTbDepDependency)
	ON_COMMAND(ID_TB_DEP_HW_CONNECTION, OnTbDepHwConnection)
	ON_COMMAND(ID_TB_HWNODE, OnTbHwnode)
	ON_COMMAND(ID_TB_TRANSITION, OnTbTransition)
	ON_COMMAND(ID_TB_STATE, OnTbState)
	ON_COMMAND(ID_TB_INITIAL_STATE, OnTbInitialState)
	ON_COMMAND(ID_TB_FINAL_STATE, OnTbFinalState)
	ON_COMMAND(ID_TB_WIDE_STATE, OnTbWideState)
	ON_COMMAND(ID_TB_ACTOR, OnTbActor)
	ON_COMMAND(ID_TB_USECASE, OnTbUsecase)
	ON_COMMAND(ID_TB_USECASE_ASSOCIATES, OnTbUsecaseAssociates)
	ON_COMMAND(ID_TB_USECASE_EXTENDS, OnTbUsecaseExtends)
	ON_COMMAND(ID_TB_USECASE_SYSTEM, OnTbUsecaseSystem)
	ON_COMMAND(ID_TB_USECASE_USES, OnTbUsecaseUses)
	ON_COMMAND(ID_TB_SEQUENCE_ASYNC, OnTbSequenceAsync)
	ON_COMMAND(ID_TB_SEQUENCE_OBJECT, OnTbSequenceObject)
	ON_COMMAND(ID_TB_SEQUENCE_RETURN, OnTbSequenceReturn)
	ON_COMMAND(ID_TB_SEQUENCE_SYNC, OnTbSequenceSync)
	ON_COMMAND(ID_ACTIVATION_KILL_SIGN, OnActivationKillSign)
	ON_UPDATE_COMMAND_UI(ID_ACTIVATION_KILL_SIGN, OnUpdateActivationKillSign)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CREATE_ACTIVITY, COODCommonView::OnCreateActivity)
	ON_COMMAND(ID_CREATE_TRIGGER, COODCommonView::OnCreateTrigger)
	ON_COMMAND(ID_CREATE_SYNCHRONIZATION_BAR, COODCommonView::OnCreateSyncBar)
	ON_COMMAND(ID_CREATE_BEGIN_ACTIVITY, COODCommonView::OnCreateBeginActivity)
	ON_COMMAND(ID_CREATE_END_ACTIVITY, COODCommonView::OnCreateEndActivity)
	ON_COMMAND(ID_CREATE_CLASSTEMPLATE, COODCommonView::OnCreateClassTemplate)
	ON_COMMAND(ID_CREATE_INTERFACE, COODCommonView::OnCreateInterface)
	ON_COMMAND(ID_CREATE_UTILITY, COODCommonView::OnCreateUtility)
	ON_COMMAND(ID_CRETAE_TEMPLATECLASS, COODCommonView::OnCreateTemplateClass)
	ON_COMMAND(ID_CREATE_INTERFACE_PORT, COODCommonView::OnCreateInterfacePort)
	ON_COMMAND(ID_CREATE_PACKAGETEMPLATE, COODCommonView::OnCreatePackageTemplate)
	ON_COMMAND(ID_CREATE_WIDEPACKAGE, COODCommonView::OnCreateWidePackage)
	ON_COMMAND(ID_CREATE_GENERALIZATION, COODCommonView::OnCreateGeneralization)
	ON_COMMAND(ID_CREATE_REFINEMENT, COODCommonView::OnCreateRefinement)
	ON_COMMAND(ID_CREATE_AGGREGATION, COODCommonView::OnCreateAggregation)
	ON_COMMAND(ID_CREATE_ASSOCIATION, COODCommonView::OnCreateAssociation)
	ON_COMMAND(ID_CREATE_COMPOSITION, COODCommonView::OnCreateComposition)
	ON_COMMAND(ID_CREATE_DEPENDENCY, COODCommonView::OnCreateDependency)
	ON_COMMAND(ID_CLASSTEMPLATE_SIZE, COODCommonView::OnChangeClassSize)
	ON_COMMAND(ID_CONNECTION_NAME_EDIT, COODCommonView::OnEditConnectionName)
	ON_COMMAND(ID_EDIT_MULTIPLICITY, COODCommonView::OnEditMultiplicity)
	ON_COMMAND(ID_EDIT_QUALIFICATION, COODCommonView::OnEditQualification)
	ON_COMMAND(ID_CREATE_COLLABORATION_OBJECT, COODCommonView::OnCreateCollaborationObject)
	ON_COMMAND(ID_CREATE_COLLABORATION_MULTI_OBJECT, COODCommonView::OnCreateCollaborationMultiObject)
	ON_COMMAND(ID_CREATE_MESSAGE_FLOW, COODCommonView::OnCreateMessageFlow)
	ON_COMMAND(ID_MESSAGE_MESSAGE_FLOW, COODCommonView::OnMessageMessageFlow)
	ON_COMMAND(ID_SHIFT_ARROW_MESSAGE_TEXT, COODCommonView::OnShiftArrowMessageText)
	ON_COMMAND(ID_INVERT_ARROW_MESSAGE_TEXT, COODCommonView::OnInvertArrowMessageText)
	ON_COMMAND(ID_CREATE_HARDWARE_NODE, COODCommonView::OnCreateHardwareNode)
	ON_COMMAND(ID_CREATE_COMPONENT_TEMPLATE, COODCommonView::OnCreateComponentTemplate)
	ON_COMMAND(ID_CREATE_HWCONNECTION, COODCommonView::OnCreateHWConnection)
	ON_COMMAND(ID_CREATE_COMMUNICATION, COODCommonView::OnCreateCommunication)
	ON_COMMAND(ID_CREATE_STATE, COODCommonView::OnCreateState)
	ON_COMMAND(ID_CREATE_WIDE_STATE, COODCommonView::OnCreateWideState)
	ON_COMMAND(ID_CREATE_INITIAL_STATE, COODCommonView::OnCreateInitialState)
	ON_COMMAND(ID_CREATE_FINAL_STATE, COODCommonView::OnCreateFinalState)
	ON_COMMAND(ID_CREATE_TRANSITION, COODCommonView::OnCreateTransition)
//	ON_COMMAND(ID_CREATE_ACTOR, COODCommonView::OnCreateActor)
	ON_COMMAND(ID_CREATE_USECASE, COODCommonView::OnCreateUseCase)
	ON_COMMAND(ID_CREATE_USECASELINK, COODCommonView::OnCreateUseCaseLink)
	ON_COMMAND(ID_CREATE_USECASEUSESLINK, COODCommonView::OnCreateUseCaseUsesLink)
	ON_COMMAND(ID_CREATE_USECASEEXTENDSLINK, COODCommonView::OnCreateUseCaseExtendsLink)
	ON_COMMAND(ID_CREATE_SYSTEMBOUNDARY, COODCommonView::OnCreateSystemBoundary)
	ON_COMMAND(ID_CREATE_SEQUENCE_OBJECT, COODCommonView::OnCreateSequenceObject)
	ON_COMMAND(ID_ACTIVATION_SEQUENCE_OBJECT, COODCommonView::OnCreateSequenceActivation)
	ON_COMMAND(ID_CREATE_SYNC_MESSAGE, COODCommonView::OnCreateSyncMessage)
	ON_COMMAND(ID_CREATE_ASYNC_MESSAGE, COODCommonView::OnCreateAsyncMessage)
	ON_COMMAND(ID_CREATE_RETURN_MESSAGE, COODCommonView::OnCreateReturnMessage)
	ON_COMMAND(ID_SEQUENCE_SELF_DELEGATION, COODCommonView::OnCreateSelfDelegation)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODCommonView drawing

void COODCommonView::OnDraw(CDC* pDC)
{
	// TODO: Add your specialized code here and/or call the base class
	
	COODView::OnDraw(pDC);
	if (_currentConnection != NIL) {
		if (ktgF_connectionDrawing) {
			rubberbanding(_currentConnection);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// COODCommonView diagnostics

#ifdef _DEBUG
void COODCommonView::AssertValid() const
{
	CScrollView::AssertValid();
}

void COODCommonView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

void COODCommonView::startFork()
{
	CString extension = getOleExtension();
	// static binding 이 필요하다.
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->CClassView::startFork();
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		((CUseCaseView *)this)->CUseCaseView::startFork();
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		((CSequenceView *)this)->CSequenceView::startFork();
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		((CCollaborationView *)this)->CCollaborationView::startFork();
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		((CStateView *)this)->CStateView::startFork();
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		((CActivityView *)this)->CActivityView::startFork();
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->CDeploymentView::startFork();
	}
}

void COODCommonView::startResize()
{
	CString extension = getOleExtension();
	// static binding 이 필요하다.
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->CClassView::startResize();
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		((CUseCaseView *)this)->CUseCaseView::startResize();
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		((CSequenceView *)this)->CSequenceView::startResize();
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		((CCollaborationView *)this)->CCollaborationView::startResize();
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		((CStateView *)this)->CStateView::startResize();
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		((CActivityView *)this)->CActivityView::startResize();
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->CDeploymentView::startResize();
	}
}

BOOL COODCommonView::checkLimitForFigure(int newx,int newy,int *deltax,int *deltay)
{
	CString extension = getOleExtension();
	// static binding 이 필요하다.
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		 return ((CClassView *)this)->CClassView::checkLimitForFigure(newx,newy,deltax,deltay);
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		return ((CUseCaseView *)this)->CUseCaseView::checkLimitForFigure(newx,newy,deltax,deltay);
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		return ((CSequenceView *)this)->CSequenceView::checkLimitForFigure(newx,newy,deltax,deltay);
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		return ((CCollaborationView *)this)->CCollaborationView::checkLimitForFigure(newx,newy,deltax,deltay);
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		return ((CStateView *)this)->CStateView::checkLimitForFigure(newx,newy,deltax,deltay);
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		return ((CActivityView *)this)->CActivityView::checkLimitForFigure(newx,newy,deltax,deltay);
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		return ((CDeploymentView *)this)->CDeploymentView::checkLimitForFigure(newx,newy,deltax,deltay);
	}
	return FALSE;
}

void COODCommonView::drawingEpilog()
{
	CString extension = getOleExtension();
	// static binding 이 필요하다.
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->CClassView::drawingEpilog();
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		((CUseCaseView *)this)->CUseCaseView::drawingEpilog();
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		((CSequenceView *)this)->CSequenceView::drawingEpilog();
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		((CCollaborationView *)this)->CCollaborationView::drawingEpilog();
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		((CStateView *)this)->CStateView::drawingEpilog();
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		((CActivityView *)this)->CActivityView::drawingEpilog();
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->CDeploymentView::drawingEpilog();
	}
}

/////////////////////////////////////////////////////////////////////////////
// COODCommonView message handlers

void COODCommonView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CString extension = getOleExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->onLButtonDblClk(nFlags, point);
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		((CUseCaseView *)this)->onLButtonDblClk(nFlags, point);
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		((CSequenceView *)this)->onLButtonDblClk(nFlags, point);
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		((CCollaborationView *)this)->onLButtonDblClk(nFlags, point);
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		((CStateView *)this)->onLButtonDblClk(nFlags, point);
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		((CActivityView *)this)->onLButtonDblClk(nFlags, point);
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->onLButtonDblClk(nFlags, point);
	}
}

void COODCommonView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CString extension = getOleExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->onLButtonDown(nFlags, point);
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		((CUseCaseView *)this)->onLButtonDown(nFlags, point);
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		((CSequenceView *)this)->onLButtonDown(nFlags, point);
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		((CCollaborationView *)this)->onLButtonDown(nFlags, point);
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		((CStateView *)this)->onLButtonDown(nFlags, point);
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		((CActivityView *)this)->onLButtonDown(nFlags, point);
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->onLButtonDown(nFlags, point);
	}
}

void COODCommonView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CString extension = getOleExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->onLButtonUp(nFlags, point);
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		((CUseCaseView *)this)->onLButtonUp(nFlags, point);
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		((CSequenceView *)this)->onLButtonUp(nFlags, point);
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		((CCollaborationView *)this)->onLButtonUp(nFlags, point);
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		((CStateView *)this)->onLButtonUp(nFlags, point);
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		((CActivityView *)this)->onLButtonUp(nFlags, point);
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->onLButtonUp(nFlags, point);
	}
}

void COODCommonView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CString extension = getOleExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->onMouseMove(nFlags, point);
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		((CUseCaseView *)this)->onMouseMove(nFlags, point);
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		((CSequenceView *)this)->onMouseMove(nFlags, point);
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		((CCollaborationView *)this)->onMouseMove(nFlags, point);
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		((CStateView *)this)->onMouseMove(nFlags, point);
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		((CActivityView *)this)->onMouseMove(nFlags, point);
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->onMouseMove(nFlags, point);
	}
}

void COODCommonView::OnTbActivity() 
{
	// TODO: Add your command handler code here
	((CActivityView *)this)->onTbActivity();
}

void COODCommonView::OnTbBeginActivity() 
{
	// TODO: Add your command handler code here
	((CActivityView *)this)->onTbBeginActivity();	
}

void COODCommonView::OnTbEndActivity() 
{
	// TODO: Add your command handler code here
	((CActivityView *)this)->onTbEndActivity();	
}

void COODCommonView::OnTbSyncBar() 
{
	// TODO: Add your command handler code here
	((CActivityView *)this)->onTbSyncBar();	
}

void COODCommonView::OnTbTrigger() 
{
	// TODO: Add your command handler code here
	((CActivityView *)this)->onTbTrigger();	
}

void COODCommonView::OnCreateActivity()
{
	((CActivityView *)this)->onCreateActivity();	
}

void COODCommonView::OnCreateTrigger()
{
	((CActivityView *)this)->onCreateTrigger();	
}

void COODCommonView::OnCreateSyncBar()
{
	((CActivityView *)this)->onCreateSyncBar();	
}

void COODCommonView::OnCreateBeginActivity()
{
	((CActivityView *)this)->onCreateBeginActivity();	
}

void COODCommonView::OnCreateEndActivity()
{
	((CActivityView *)this)->onCreateEndActivity();	
}

void COODCommonView::OnTbAggregation() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbAggregation();	
}

void COODCommonView::OnTbAssociation() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbAssociation();	
}

void COODCommonView::OnTbClasstemplate() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbClasstemplate();	
}

void COODCommonView::OnTbComposition() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbComposition();	
}

void COODCommonView::OnTbDependency() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbDependency();	
}

void COODCommonView::OnTbGeneralization() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbGeneralization();	
}

void COODCommonView::OnTbInterface() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbInterface();	
}

void COODCommonView::OnTbPackage() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbPackage();	
}

void COODCommonView::OnTbRefinement() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbRefinement();	
}

void COODCommonView::OnTbTemplateclass() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbTemplateclass();	
}

void COODCommonView::OnTbUtility() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbUtility();	
}

void COODCommonView::OnTbWidePackage() 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onTbWidePackage();	
}

void COODCommonView::OnCreateClassTemplate()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateClassTemplate();	
}

void COODCommonView::OnCreateInterface()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateInterface();	
}

void COODCommonView::OnCreateUtility()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateUtility();	
}

void COODCommonView::OnCreateTemplateClass()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateTemplateClass();	
}

void COODCommonView::OnCreateInterfacePort()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateInterfacePort();	
}

void COODCommonView::OnCreatePackageTemplate()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreatePackageTemplate();	
}

void COODCommonView::OnCreateWidePackage()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateWidePackage();	
}

void COODCommonView::OnCreateGeneralization()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateGeneralization();	
}

void COODCommonView::OnCreateRefinement()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateRefinement();	
}

void COODCommonView::OnCreateAggregation()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateAggregation();	
}

void COODCommonView::OnCreateAssociation()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateAssociation();	
}

void COODCommonView::OnCreateComposition()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateComposition();	
}

void COODCommonView::OnCreateDependency()
{
	// TODO: Add your command handler code here
	CString extension = getOleExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->onCreateDependency();	
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->onCreateDependency();	
	}
}

void COODCommonView::OnChangeClassSize()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onChangeClassSize();	
}

void COODCommonView::OnEditConnectionName()
{
	// TODO: Add your command handler code here
	CString extension = getOleExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		((CClassView *)this)->onEditConnectionName();	
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		((CActivityView *)this)->onGuardTrigger();	
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		((CStateView *)this)->onEventTransition();	
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		((CSequenceView *)this)->onEditConnectionName();	
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		((CDeploymentView *)this)->onEditConnectionName();	
	}
}

void COODCommonView::OnEditMultiplicity()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onEditMultiplicity();	
}

void COODCommonView::OnEditQualification()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onEditQualification();	
}

void COODCommonView::OnCreateAssociationClass()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onCreateAssociationClass();	
}

void COODCommonView::OnUpdateCreateAssociationClass(CCmdUI* pCmdUI) 
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onUpdateCreateAssociationClass(pCmdUI);	
}

void COODCommonView::OnSupressDataMembers()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onSupressDataMembers();	
}

void COODCommonView::OnSupressMemberFunctions()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onSupressMemberFunctions();	
}

void COODCommonView::OnUpdateSupressDataMembers(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	((CClassView *)this)->onUpdateSupressDataMembers(pCmdUI);	
}

void COODCommonView::OnUpdateSupressMemberFunctions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	((CClassView *)this)->onUpdateSupressMemberFunctions(pCmdUI);	
}

void COODCommonView::OnClassProperties()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onClassProperties();	
}

void COODCommonView::OnInterfaceProperties()
{
	// TODO: Add your command handler code here
	((CClassView *)this)->onInterfaceProperties();	
}

void COODCommonView::OnTbColMessage() 
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onTbColMessage();	
}

void COODCommonView::OnTbColMultiObject() 
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onTbColMultiObject();	
}

void COODCommonView::OnTbColObject() 
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onTbColObject();	
}

void COODCommonView::OnSelfDelegationCollaborationObject() 
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onSelfDelegationCollaborationObject();	
}

void COODCommonView::OnUpdateSelfDelegationCollaborationObject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	((CCollaborationView *)this)->onUpdateSelfDelegationCollaborationObject(pCmdUI);	
}

void COODCommonView::OnSelfDelegationDelete() 
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onSelfDelegationDelete();	
}

void COODCommonView::OnCreateCollaborationObject()
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onCreateCollaborationObject();	
}

void COODCommonView::OnCreateCollaborationMultiObject()
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onCreateCollaborationMultiObject();	
}

void COODCommonView::OnCreateMessageFlow()
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onCreateMessageFlow();	
}

void COODCommonView::OnMessageMessageFlow()
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onMessageMessageFlow();	
}

void COODCommonView::OnShiftArrowMessageText()
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onShiftArrowMessageText();	
}

void COODCommonView::OnInvertArrowMessageText()
{
	// TODO: Add your command handler code here
	((CCollaborationView *)this)->onInvertArrowMessageText();	
}

void COODCommonView::OnTbDepCommunication() 
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onTbDepCommunication();	
}

void COODCommonView::OnTbDepComponent() 
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onTbDepComponent();	
}

void COODCommonView::OnTbDepDependency() 
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onTbDepDependency();	
}

void COODCommonView::OnTbDepHwConnection() 
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onTbDepHwConnection();	
}

void COODCommonView::OnTbHwnode() 
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onTbHwnode();	
}

void COODCommonView::OnCreateHardwareNode()
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onCreateHardwareNode();	
}

void COODCommonView::OnCreateComponentTemplate()
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onCreateComponentTemplate();	
}

void COODCommonView::OnCreateHWConnection()
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onCreateHWConnection();	
}

void COODCommonView::OnCreateCommunication()
{
	// TODO: Add your command handler code here
	((CDeploymentView *)this)->onCreateCommunication();	
}

void COODCommonView::OnTbTransition() 
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onTbTransition();	
}

void COODCommonView::OnTbState() 
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onTbState();	
}

void COODCommonView::OnTbInitialState() 
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onTbInitialState();	
}

void COODCommonView::OnTbFinalState() 
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onTbFinalState();	
}

void COODCommonView::OnTbWideState() 
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onTbWideState();	
}

void COODCommonView::OnCreateState()
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onCreateState();	
}

void COODCommonView::OnCreateWideState()
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onCreateWideState();	
}

void COODCommonView::OnCreateInitialState()
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onCreateInitialState();	
}

void COODCommonView::OnCreateFinalState()
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onCreateFinalState();	
}

void COODCommonView::OnCreateTransition()
{
	// TODO: Add your command handler code here
	((CStateView *)this)->onCreateTransition();	
}

void COODCommonView::OnTbActor() 
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onTbActor();	
}

void COODCommonView::OnTbUsecase() 
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onTbUsecase();	
}

void COODCommonView::OnTbUsecaseAssociates() 
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onTbUsecaseAssociates();	
}

void COODCommonView::OnTbUsecaseExtends() 
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onTbUsecaseExtends();	
}

void COODCommonView::OnTbUsecaseSystem() 
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onTbUsecaseSystem();	
}

void COODCommonView::OnTbUsecaseUses() 
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onTbUsecaseUses();	
}

/* COODView로 이동됨
void COODCommonView::OnCreateActor()
{
	// TODO: Add your command handler code here
	((COODView *)this)->onCreateActor();	
}
*/

void COODCommonView::OnCreateUseCase()
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onCreateUseCase();	
}

void COODCommonView::OnCreateUseCaseLink()
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onCreateUseCaseLink();	
}

void COODCommonView::OnCreateUseCaseUsesLink()
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onCreateUseCaseUsesLink();	
}

void COODCommonView::OnCreateUseCaseExtendsLink()
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onCreateUseCaseExtendsLink();	
}

void COODCommonView::OnCreateSystemBoundary()
{
	// TODO: Add your command handler code here
	((CUseCaseView *)this)->onCreateSystemBoundary();	
}

void COODCommonView::OnTbSequenceAsync() 
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onTbSequenceAsync();	
}

void COODCommonView::OnTbSequenceObject() 
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onTbSequenceObject();	
}

void COODCommonView::OnTbSequenceReturn() 
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onTbSequenceReturn();	
}

void COODCommonView::OnTbSequenceSync() 
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onTbSequenceSync();	
}

void COODCommonView::OnActivationKillSign()
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onActivationKillSign();	
}

void COODCommonView::OnUpdateActivationKillSign(CCmdUI* pCmdUI)
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onUpdateActivationKillSign(pCmdUI);	
}

void COODCommonView::OnCreateSequenceObject()
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onCreateSequenceObject();	
}

void COODCommonView::OnCreateSequenceActivation()
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onCreateSequenceActivation();	
}

void COODCommonView::OnCreateSyncMessage()
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onCreateSyncMessage();	
}

void COODCommonView::OnCreateAsyncMessage()
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onCreateAsyncMessage();	
}

void COODCommonView::OnCreateReturnMessage()
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onCreateReturnMessage();	
}

void COODCommonView::OnCreateSelfDelegation()
{
	// TODO: Add your command handler code here
	((CSequenceView *)this)->onCreateSelfDelegation();	
}

