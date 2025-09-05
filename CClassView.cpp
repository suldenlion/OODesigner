// CClassView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CMainFrame.h"
#include "CClassView.h"
#include "Figures.h"
#include "LineNodeList.h"
#include "UnsignedLong.h"
#include "COODClassDoc.h"
#include "COODCommonDoc.h"
#include "CResizableTreeBar.h"
#include "CodeGenerators.h"
#include "ClassPropDlg.h"
#include "MemberPropDlg.h"
#include "PackageLibrary.h"
#include "ClassContent.h"
#include "NodeFigureList.h"
#include "ClassLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CClassView, COODView)
/////////////////////////////////////////////////////////////////////////////
// CClassView

CClassView::CClassView()
: COODView()
{
}

CClassView::~CClassView()
{
}

BEGIN_MESSAGE_MAP(CClassView, COODView)
	//{{AFX_MSG_MAP(CClassView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
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
	ON_COMMAND(ID_POPUP_OPEN_PACKAGE, OnPopupOpenPackage)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPEN_PACKAGE, OnUpdatePopupOpenPackage)
	ON_COMMAND(ID_CREATE_ASSOCIATION_CLASS, OnCreateAssociationClass)
	ON_UPDATE_COMMAND_UI(ID_CREATE_ASSOCIATION_CLASS, OnUpdateCreateAssociationClass)
	ON_COMMAND(ID_SUPRESS_DATA_MEMBERS, OnSupressDataMembers)
	ON_UPDATE_COMMAND_UI(ID_SUPRESS_DATA_MEMBERS, OnUpdateSupressDataMembers)
	ON_COMMAND(ID_SUPRESS_MEMBER_FUNCTIONS, OnSupressMemberFunctions)
	ON_UPDATE_COMMAND_UI(ID_SUPRESS_MEMBER_FUNCTIONS, OnUpdateSupressMemberFunctions)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_INTERFACE_PROPERTIES, OnInterfaceProperties)
	ON_COMMAND(ID_GENERATE_CODE, OnGenerateCode)
	ON_UPDATE_COMMAND_UI(ID_GENERATE_CODE, OnUpdateGenerateCode)
	ON_COMMAND(ID_TOOLS_GENERATE_CODE, OnToolsGenerateCode)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_GENERATE_CODE, OnUpdateToolsGenerateCode)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CREATE_CLASSTEMPLATE, CClassView::OnCreateClassTemplate)
	ON_COMMAND(ID_CREATE_INTERFACE, CClassView::OnCreateInterface)
	ON_COMMAND(ID_CREATE_UTILITY, CClassView::OnCreateUtility)
	ON_COMMAND(ID_CRETAE_TEMPLATECLASS, CClassView::OnCreateTemplateClass)
	ON_COMMAND(ID_CREATE_INTERFACE_PORT, CClassView::OnCreateInterfacePort)
	ON_COMMAND(ID_CREATE_PACKAGETEMPLATE, CClassView::OnCreatePackageTemplate)
	ON_COMMAND(ID_CREATE_WIDEPACKAGE, CClassView::OnCreateWidePackage)
	ON_COMMAND(ID_CREATE_GENERALIZATION, CClassView::OnCreateGeneralization)
	ON_COMMAND(ID_CREATE_REFINEMENT, CClassView::OnCreateRefinement)
	ON_COMMAND(ID_CREATE_AGGREGATION, CClassView::OnCreateAggregation)
	ON_COMMAND(ID_CREATE_ASSOCIATION, CClassView::OnCreateAssociation)
	ON_COMMAND(ID_CREATE_COMPOSITION, CClassView::OnCreateComposition)
	ON_COMMAND(ID_CREATE_DEPENDENCY, CClassView::OnCreateDependency)
	ON_COMMAND(ID_CLASSTEMPLATE_SIZE, CClassView::OnChangeClassSize)
	ON_COMMAND(ID_CONNECTION_NAME_EDIT, CClassView::OnEditConnectionName)
	ON_COMMAND(ID_EDIT_MULTIPLICITY, CClassView::OnEditMultiplicity)
	ON_COMMAND(ID_EDIT_QUALIFICATION, CClassView::OnEditQualification)
END_MESSAGE_MAP()

void CClassView::setPopups()
{
	_mainPopup = theAppPtr->theClassMainPopup;
}

void CClassView::startFork()
{
	if (_currentFocus == NIL) return;
	if (_currentFocus->whoAreYou()->equals(IAMGENERALIZATION)) {
		_whatTionToDraw = KTG_GENERALIZATION;
	} else if (_currentFocus->whoAreYou()->equals(IAMAGGREGATION)) {
		_whatTionToDraw = KTG_AGGREGATION;
	} else if (_currentFocus->whoAreYou()->equals(IAMDEPENDENCY)) {
		_whatTionToDraw = KTG_DEPENDENCY;
	} else if (_currentFocus->whoAreYou()->equals(IAMASSOCIATION)) {
		_whatTionToDraw = KTG_ASSOCIATION;
	} else {
		return;
	}
	collectActiveNodes(WEARECLASSOBJECTS);

	checkInList(_currentFocus);
	figures()->remove(_currentFocus);

	CPoint cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(&cursorPos);
	DPtoLP(cursorPos);
	int tx = cursorPos.x;
	int ty = cursorPos.y;
	_currentConnection = (Connection *)_currentFocus;
	_currentConnection->calcForkPoint(tx,ty,_forkX,_forkY);
	if (_forkX == -1 || _forkY == -1) return;
	Line *aLine = new Line(this,_forkX,_forkY,NIL,STRAIGHT);
	aLine->setOrient(Line::invertOrient(currentOrient));
	aLine->style() = _currentConnection->style();
	_currentX = _forkX;
	_currentY = _forkY;
	_currentConnection->insertALine(aLine,TRUE);
	LineNode *node = _currentConnection->node(aLine);
	_currentConnection->activeLines()->insert(node);
	aLine->setFollowing2(_forkX,_forkY);
	_forkX = -1; _forkY = -1;

	ktgF_connectionDrawing = TRUE;
}

void CClassView::OnEditQualification()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnEditQualification()");
		return;
	}
	UnsignedLong *id = _currentFocus->whoAreYou();
	if (id->equals(IAMASSOCIATION) == FALSE) {
		beep("CClassView::OnEditQualification()");
		return;
	}
	lowlight(_currentFocus);
	_editingTag = TRUE;
	Connection * thisConnection = (Connection *)_currentFocus;
	QualificationText *aText = thisConnection->selectOrCreateQualification(_popupX,_popupY);
	if (aText == NIL) {
		_editingTag = FALSE;
		return;
	}
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	aText->startEdit();
	ktgF_processKeys = TRUE;
}

void CClassView::OnEditMultiplicity()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnEditMultiplicity()");
		return;
	}
	UnsignedLong *id = _currentFocus->whoAreYou();
	if (id->equals(IAMAGGREGATION) == FALSE &&
		id->equals(IAMDEPENDENCY) == FALSE &&
		id->equals(IAMASSOCIATION) == FALSE) {
		beep("CClassView::OnEditMultiplicity()");
		return;
	}
	lowlight(_currentFocus);
	_editingTag = TRUE;
	Connection * thisConnection = (Connection *)_currentFocus;
	OneLineText *aText = thisConnection->selectOrCreateMultiplicity(_popupX,_popupY);
	if (aText == NIL) {
		_editingTag = FALSE;
		return;
	}
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	aText->startEdit();
	ktgF_processKeys = TRUE;
}

void CClassView::OnEditConnectionName()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnEditConnectionName()");
		return;
	}
	UnsignedLong *id = _currentFocus->whoAreYou();
	if (id->equals(IAMGENERALIZATION) == FALSE &&
		id->equals(IAMAGGREGATION) == FALSE &&
		id->equals(IAMDEPENDENCY) == FALSE &&
		id->equals(IAMASSOCIATION) == FALSE) {
		beep("CClassView::OnEditConnectionName()");
		return;
	}
	lowlight(_currentFocus);
	_editingTag = TRUE;
	Connection * thisConnection = (Connection *)_currentFocus;
	ConnectionText *aText = thisConnection->selectOrCreateText();
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	aText->startEdit();
	ktgF_processKeys = TRUE;
}

void CClassView::OnCreateGeneralization()
{
	collectActiveNodes(WEARECLASSOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named classes.");
		return;
	}
	_whatTionToDraw = KTG_GENERALIZATION;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_GENERALIZATION);
}

void CClassView::OnCreateRefinement()
{
	collectActiveNodes(WEARECLASSOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named classes.");
		return;
	}
	_whatTionToDraw = KTG_REFINEMENT;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_REFINEMENT);
}

void CClassView::OnCreateAssociation()
{
	collectActiveNodes(WEARECLASSOBJECTS);
	if (_activeNodes->nOfList() < 1) {
		_activeNodes->clear();
		WarningMsg("You must have one or more named classes.");
		return;
	}
	_whatTionToDraw = KTG_ASSOCIATION;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_ASSOCIATION);
}

void CClassView::OnCreateAggregation()
{
	collectActiveNodes(WEARECLASSOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named classes.");
		return;
	}
	_whatTionToDraw = KTG_AGGREGATION;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_AGGREGATION);
}

void CClassView::OnCreateComposition()
{
	collectActiveNodes(WEARECLASSOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named classes.");
		return;
	}
	_whatTionToDraw = KTG_COMPOSITION;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_COMPOSITION);
}

void CClassView::OnCreateDependency()
{
	collectActiveNodes(WEARECLASSOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named classes.");
		return;
	}
	_whatTionToDraw = KTG_DEPENDENCY;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_DEPENDENCY);
}

void CClassView::OnCreateUtility()
{
	ClassTemplate *aClass = new ClassTemplate(this,_popupX,_popupY,_fontHeight,theAppPtr->theClassTemplatePopup);
	aClass->setStereotype("utility");
	aClass->setFocus();
	BOOL ok = aClass->startEdit();
	if (ok == FALSE) {
		beep("CClassView::OnCreateClassTemplate()");
		delete aClass;
		return;
	}
	draw(aClass);
	_currentFocus = (Figure *)aClass;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CClassView::OnCreateInterface()
{
	ClassTemplate *aClass = new ClassTemplate(this,_popupX,_popupY,_fontHeight,theAppPtr->theClassTemplatePopup);
	aClass->setStereotype("interface");
	aClass->setFocus();
	BOOL ok = aClass->startEdit();
	if (ok == FALSE) {
		beep("CClassView::OnCreateClassTemplate()");
		delete aClass;
		return;
	}
	draw(aClass);
	_currentFocus = (Figure *)aClass;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CClassView::OnCreateTemplateClass()
{
	ClassTemplate *aClass = new ClassTemplate(this,_popupX,_popupY,_fontHeight,theAppPtr->theClassTemplatePopup);
	aClass->setTemplateFlag();
	aClass->setFocus();
	BOOL ok = aClass->startEdit();
	if (ok == FALSE) {
		beep("CClassView::OnCreateTemplateClass()");
		delete aClass;
		return;
	}
	draw(aClass);
	_currentFocus = (Figure *)aClass;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CClassView::OnCreateAssociationClass()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnCreateAssociationClass()");
		return;
	}
	UnsignedLong *id = _currentFocus->whoAreYou();
	if (id->equals(IAMASSOCIATION) == FALSE) {
		beep("CClassView::OnCreateAssociationClass()");
		return;
	}
	lowlight(_currentFocus);
	int cx,cy;
	Association *theAssociation = (Association *)_currentFocus;
	theAssociation->getCenterPosition(cx,cy);
	int x1 = cx - CLASSTEMPLATE_INIT_WIDTH/2;
	int y1 = cy + CLASSTEMPLATE_INIT_WIDTH;
	ClassTemplate *aClass = new ClassTemplate(this,x1,y1,_fontHeight,theAppPtr->theClassTemplatePopup);
	theAssociation->setAssociationClassPtr(aClass);
	aClass->setAssociationPtr(theAssociation);
	aClass->setFocus();
	BOOL ok = aClass->startEdit();
	if (ok == FALSE) {
		beep("CClassView::OnCreateClassTemplate()");
		delete aClass;
		return;
	}
	draw(aClass);
	_currentFocus = (Figure *)aClass;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CClassView::OnCreateClassTemplate()
{
	ClassTemplate *aClass = new ClassTemplate(this,_popupX,_popupY,_fontHeight,theAppPtr->theClassTemplatePopup);
	aClass->setFocus();
	BOOL ok = aClass->startEdit();
	if (ok == FALSE) {
		beep("CClassView::OnCreateClassTemplate()");
		delete aClass;
		return;
	}
	draw(aClass);
	_currentFocus = (Figure *)aClass;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CClassView::OnCreatePackageTemplate()
{
	PackageTemplate *aPackage = new PackageTemplate(this,_popupX,_popupY,_fontHeight,theAppPtr->thePackagePopup);
	aPackage->setFocus();
	BOOL ok = aPackage->startEdit();
	if (ok == FALSE) {
		beep("CClassView::OnCreatePackageTemplate()");
		delete aPackage;
		return;
	}
	draw(aPackage);
	_currentFocus = (Figure *)aPackage;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CClassView::OnCreateWidePackage()
{
	WidePackage *aPackage = new WidePackage(this,_popupX,_popupY,NIL);
	aPackage->setFocus();
	BOOL ok = aPackage->startEdit();
	if (ok == FALSE) {
		beep("CClassView::OnCreateWidePackage()");
		delete aPackage;
		return;
	}
	draw(aPackage);
	_currentFocus = (Figure *)aPackage;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CClassView::OnSupressDataMembers()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnSupressDataMembers()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		beep("CClassView::OnSupressDataMembers()");
		return;
	}
	ClassTemplate *aClass = (ClassTemplate *) _currentFocus;
	aClass->supressDataMembers();
	Invalidate();
	_currentFocus = NIL;
}

void CClassView::OnSupressMemberFunctions()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnSupressDataMembers()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		beep("CClassView::OnSupressDataMembers()");
		return;
	}
	ClassTemplate *aClass = (ClassTemplate *) _currentFocus;
	aClass->supressMemberFuctions();
	Invalidate();
	_currentFocus = NIL;
}

void CClassView::OnCreateInterfacePort()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnCreateInterfacePort()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		beep("CClassView::OnCreateInterfacePort()");
		return;
	}
	ClassTemplate *aClass = (ClassTemplate *) _currentFocus;
	InterfacePortText* aText = aClass->createInterfacePort();

	BOOL ok = aClass->startEdit();
	if (ok == FALSE) {
		beep("CClassView::OnCreateInterfacePort()");
		return;
	}
	draw(aClass);
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CClassView::OnPopupOpenPackage()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnPopupOpenPackage()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMPACKAGETEMPLATE) == FALSE) {
		beep("CClassView::OnPopupOpenPackage()");
		return;
	}
	PackageTemplate *aPackage = (PackageTemplate *) _currentFocus;
	_currentFocus = NIL;
	char packageName[BUFSIZ];
	aPackage->getName(packageName,BUFSIZ);
	BOOL okFlag = mainFramePtr->createNewClassFrame(theAppPtr->pClassDocTemplate,(CDocument *)theAppPtr->pCOODClassDoc,packageName);
	if (okFlag == FALSE) { 
		ErrorMsg("File creation fails.\r\nPlease contact to the vendor.");
		return;
	}
	CString newDgmName = packageName;
	newDgmName = newDgmName + _PAK_EXT;
	POSITION pos = theAppPtr->pCOODClassDoc->activeViewNames.Find(newDgmName);
	if (pos == NULL) {
		theAppPtr->pCOODClassDoc->insertViewName(newDgmName);
		mainFramePtr->m_wndTreeBar.insertDiagramName(newDgmName);
	}
}

void CClassView::OnClassProperties()
{
	if (_currentFocus == NIL) {
		::SendMessage(mainFramePtr->m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_PROPERTIES,0);
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		beep("CClassView::OnClassProperties()");
		return;
	}
	ClassTemplate *aClass = (ClassTemplate *) _currentFocus;
	eraseDots(_currentFocus);

	char buffer[BUFSIZ];
	aClass->getName(buffer,BUFSIZ);
	CString className = buffer;
	CString packageName = viewTitleWithOutExtension;
	ClassContent *theContent = aClass->classContent();
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)))
		theAppPtr->pCOODClassDoc->getAllClassContents()->getPackageNameFor(className,packageName);

	int whichField = aClass->ptInWhichField(_popupX,_popupY);

	if (whichField == IAMVARIABLES &&
		aClass->nOfDataMembers() > 0) {
		MemberPropDlg *memberDlg = theAppPtr->getActiveVarPropDlg();
		if (memberDlg == NIL) {
			beep("CClassView::OnClassProperties()");
			return;
		}
		if ((memberDlg->GetStyle() & WS_VISIBLE) == 0) {
			memberDlg->ShowWindow(SW_SHOW);
		}
		theAppPtr->deactivateClassPropertyDlgs();
		ClassTextLine *theLine = theContent->getDataMemberLine(0);
		memberDlg->loadFromClassTextLine(this,theLine,0,theContent,className,packageName);
	} else if (whichField == IAMMETHODS &&
		aClass->nOfMemberFunctions() > 0) {
		MemberPropDlg *memberDlg = theAppPtr->getActiveMethodPropDlg();
		if (memberDlg == NIL) {
			beep("CClassView::OnClassProperties()");
			return;
		}
		if ((memberDlg->GetStyle() & WS_VISIBLE) == 0) {
			memberDlg->ShowWindow(SW_SHOW);
		}
		theAppPtr->deactivateClassPropertyDlgs();
		ClassTextLine *theLine = theContent->getMemberFunctionLine(0);
		memberDlg->loadFromClassTextLine(this,theLine,0,theContent,className,packageName);
	} else {
		ClassPropDlg *classDlg = theAppPtr->getActiveClassPropDlg();
		if (classDlg == NIL) {
			beep("CClassView::OnClassProperties()");
			return;
		}
		if ((classDlg->GetStyle() & WS_VISIBLE) == 0) {
			classDlg->ShowWindow(SW_SHOW);
		}
		classDlg->loadFromClassContent(this,theContent,className,packageName);
	}
}

void CClassView::OnInterfaceProperties()
{
	if (_currentFocus == NIL) {
		::SendMessage(mainFramePtr->m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_PROPERTIES,0);
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		beep("CClassView::OnInterfaceProperties()");
		return;
	}
	ClassTemplate *aClass = (ClassTemplate *) _currentFocus;
	char interfaceName[BUFSIZ];
	aClass->getInterfacePortText(interfaceName,BUFSIZ);

	if (strlen(interfaceName) == 0) {
		WarningMsg("I am sorry.\r\nThis interface has no name.");
		return;
	}
	CString className = interfaceName;
	CString packageName = viewTitleWithOutExtension;
	COODDoc *pDoc = GetDocument();
	if (pDoc->IsKindOf(RUNTIME_CLASS(COODClassDoc)))
		theAppPtr->pCOODClassDoc->getAllClassContents()->getPackageNameFor(className,packageName);
	ClassContent *theContent = NIL;
	if (pDoc->IsKindOf(RUNTIME_CLASS(COODClassDoc)))
		theContent = theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(className);
	else if (pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) 
		theContent = ((COODCommonDoc *)pDoc)->getClassContentFor(className,NIL);
	if (theContent == NIL) {
		WarningMsg("I am sorry.\r\nThis interface was not registered.");
		return;
	}
	ClassPropDlg *classDlg = theAppPtr->getActiveClassPropDlg();
	if (classDlg == NIL) {
		beep("CClassView::OnInterfaceProperties()");
		return;
	}
	if ((classDlg->GetStyle() & WS_VISIBLE) == 0) {
		classDlg->ShowWindow(SW_SHOW);
	}
	classDlg->loadFromClassContent(this,theContent,className,packageName);
}

void CClassView::OnChangeClassSize()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnChangeClassSize()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		beep("CClassView::OnChangeClassSize()");
		return;
	}
	ClassTemplate *aClass = (ClassTemplate *) _currentFocus;
	aClass->changeSize();
	Invalidate();
	_currentFocus = NIL;
}

BOOL CClassView::validWhatTionToDraw()
{
	if (_whatTionToDraw == KTG_GENERALIZATION ||
		_whatTionToDraw == KTG_REFINEMENT ||
		_whatTionToDraw == KTG_AGGREGATION ||
		_whatTionToDraw == KTG_COMPOSITION ||
		_whatTionToDraw == KTG_DEPENDENCY ||
		_whatTionToDraw == KTG_ASSOCIATION) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void CClassView::createNewConnection(CPoint point)
{
	lowlightDrawBoundary(_currentFocus);
	int x = point.x;
	int y = point.y;
	_currentX = x;
	_currentY = y;
	Line *aLine = new Line(this,x,y,NIL,STRAIGHT);
	aLine->setFollowing2(x,y);
	UINT commandID = 0;
	if (_whatTionToDraw == KTG_GENERALIZATION) {
		commandID = ID_TB_GENERALIZATION;
		_currentConnection = new Generalization(this,theAppPtr->theGeneralizationPopup,aLine);
	} else if (_whatTionToDraw == KTG_REFINEMENT) {
		commandID = ID_TB_REFINEMENT;
		Generalization *newGeneralization = new Generalization(this,theAppPtr->theGeneralizationPopup,aLine);
		newGeneralization->setRefinement();
		_currentConnection = newGeneralization;
	} else if (_whatTionToDraw == KTG_AGGREGATION) {
		commandID = ID_TB_AGGREGATION;
		_currentConnection = new Aggregation(this,theAppPtr->theAggregationPopup,aLine);
	} else if (_whatTionToDraw == KTG_COMPOSITION) {
		commandID = ID_TB_COMPOSITION;
		Aggregation *newAggregation = new Aggregation(this,theAppPtr->theAggregationPopup,aLine);
		newAggregation->setComposition();
		_currentConnection = newAggregation;
	} else if (_whatTionToDraw == KTG_ASSOCIATION) {
		commandID = ID_TB_ASSOCIATION;
		_currentConnection = new Association(this,theAppPtr->theAssociationPopup,aLine);
	} else {
		commandID = ID_TB_DEPENDENCY;
		_currentConnection = new Dependency(this,theAppPtr->theDependencyPopup,aLine);
	}
	if (commandID != 0)
		releaseModelTBButton(commandID);
	EditableFigure *eNode = (EditableFigure *)_currentFocus;
	eNode->insert(_currentConnection);
	_currentConnection->insert(eNode);
	LineNode *node = _currentConnection->node(aLine);
	_currentConnection->activeLines()->insert(node);
	aLine->setOrient(Line::invertOrient(currentOrient));
	aLine->style() = _currentConnection->style();

	NodeFigure *thisNode = (NodeFigure *)_currentFocus;
	NodeFigure *aFigure = (NodeFigure *)_activeNodes->getFirst();
	while (aFigure != NIL) {
		int x1 = aFigure->shape()->getX1();
		int y1 = aFigure->shape()->getY1();
		int x2 = aFigure->shape()->getX2();
		int y2 = aFigure->shape()->getY2();
		UnsignedLong *who = aFigure->whoAreYou();
		if (who->equals(IAMWIDEPACKAGE) &&
			thisNode->containedWithin(x1,y1,x2,y2)) {
			_activeNodes->remove(aFigure);
			aFigure = (NodeFigure *)_activeNodes->getFirst();
		} else {
			aFigure = (NodeFigure *)_activeNodes->getNext();
		}
	}
}

void CClassView::drawingEpilog()
{
	COODView::drawingEpilog();
}

/////////////////////////////////////////////////////////////////////////////
// CClassView message handlers


void CClassView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pSender == NULL) {
		Invalidate();
		return;
	}
	if (!pSender->IsKindOf(RUNTIME_CLASS(CClassView))) return;
	Invalidate();
}

void CClassView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint orgPoint(point);
	DPtoLP(point);
	if (validWhatTionToDraw() == FALSE) {
		if (_whatNodeToDraw == -1) {
			COODView::OnLButtonDown(nFlags, orgPoint);
		} else {
			_popupX = point.x;
			_popupY = point.y;
			switch (_whatNodeToDraw) {
			case ID_TB_ALPHABET:
				startEditor(point);
				break;
			case ID_TB_NOTE:
				OnCreateNote();
				break;
			case ID_TB_ACTOR:
				OnCreateActor();
				break;
			case ID_TB_CLASSTEMPLATE:
				OnCreateClassTemplate();
				break;
			case ID_TB_TEMPLATECLASS:
				OnCreateTemplateClass();
				break;
			case ID_TB_INTERFACE:
				OnCreateInterface();
				break;
			case ID_TB_UTILITY:
				OnCreateUtility();
				break;
			case ID_TB_PACKAGE:
				OnCreatePackageTemplate();
				break;
			case ID_TB_WIDE_PACKAGE:
				OnCreateWidePackage();
				break;
			}
			if (_whatNodeToDraw != -1)
				releaseModelTBButton(_whatNodeToDraw);
			_whatNodeToDraw = -1;
			CScrollView::OnLButtonDown(nFlags, orgPoint);
		}
		return;
	}
	if (ktgF_connectionStartDraw) {
		if (_currentFocus == NIL) {
			InfoMsg("Please drag from a node figure."); 
			ktgF_connectionStartDraw = FALSE;
			releaseModelTBButton();
			drawingEpilog();
			CScrollView::OnLButtonDown(nFlags, orgPoint);
			return;
		} 
		if (_whatTionToDraw == KTG_REFINEMENT) {
			UnsignedLong *who = _currentFocus->whoAreYou();
			if (who->equals(IAMCLASSTEMPLATE) == FALSE) {
				lowlightDrawBoundary(_currentFocus);
				beep("You must choose an interface or a template."); 
				ktgF_connectionStartDraw = FALSE;
				releaseModelTBButton();
				drawingEpilog();
				_currentFocus = NIL;
				CScrollView::OnLButtonDown(nFlags, orgPoint);
				return;
			}
			ClassTemplate *aClass = (ClassTemplate *)_currentFocus;
			if (aClass->getInterfaceFlag() == FALSE &&
				aClass->getTemplateFlag() == FALSE) {
				lowlightDrawBoundary(_currentFocus);
				beep("You must choose an interface or a template."); 
				ktgF_connectionStartDraw = FALSE;
				releaseModelTBButton();
				drawingEpilog();
				_currentFocus = NIL;
				CScrollView::OnLButtonDown(nFlags, orgPoint);
				return;
			}
		} else if (_whatTionToDraw == KTG_GENERALIZATION) {
			UnsignedLong *who = _currentFocus->whoAreYou();
			if (who->equals(IAMCLASSTEMPLATE) == TRUE &&
				((ClassTemplate *)_currentFocus)->getInterfaceFlag() == TRUE) {
				lowlightDrawBoundary(_currentFocus);
				beep("You may not start from interface for drawing generalization. Please use refinement."); 
				ktgF_connectionStartDraw = FALSE;
				releaseModelTBButton();
				drawingEpilog();
				_currentFocus = NIL;
				CScrollView::OnLButtonDown(nFlags, orgPoint);
				return;
			}
		}
		ktgF_connectionStartDraw = FALSE;
		createNewConnection(point);
		ktgF_connectionDrawing = TRUE;
	} else if (ktgF_connectionContinueDraw) {
		if (_currentConnection == NIL) {
			beep("CClassView::OnLButtonDown(UINT nFlags, CPoint point)");
			ktgF_connectionStartDraw = FALSE;
			ktgF_connectionContinueDraw = FALSE;
			drawingEpilog();
			CScrollView::OnLButtonDown(nFlags, orgPoint);
			return;
		} 
		ktgF_connectionContinueDraw = FALSE;
		_currentConnection->continueDraw();
		ktgF_connectionDrawing = TRUE;
	}
	SetCapture();
	CScrollView::OnLButtonDown(nFlags, orgPoint);
}

void CClassView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint orgPoint(point);
	DPtoLP(point);
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnMouseMove(nFlags, orgPoint);
		return;
	} else {
		setPositionOnStatusBar(point.x,point.y);
		if (ktgF_connectionDrawing && 
			nFlags == MK_LBUTTON) {
			CPoint testPoint;
			Line *focusLine = (Line *)_currentConnection->focus();
			testPoint.x = focusLine->getX2();
			testPoint.y = focusLine->getY2();
			localTraceEnter(testPoint,_activeNodes,FALSE);
			drawingHandler(point,_currentConnection);
		} else if (ktgF_connectionContinueDraw == FALSE) {
			localTraceEnter(point,_activeNodes,FALSE);
		}
	}	
	CScrollView::OnMouseMove(nFlags, orgPoint);
}

void CClassView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonUp(nFlags, point);
		return;
	} else {
		if (ktgF_connectionDrawing == FALSE) {
			COODView::OnLButtonUp(nFlags, point);
			return;
		} else {
			CPoint testPoint;
			Line *focusLine = (Line *)_currentConnection->focus();
			testPoint.x = focusLine->getX2();
			testPoint.y = focusLine->getY2();
			localTraceEnter(testPoint,_activeNodes,FALSE);
			movePointer(testPoint.x,testPoint.y);

			BOOL stopFlag = FALSE;
			ktgF_connectionDrawing = FALSE;
			NodeFigure *nodeFocus;
			if (_currentFocus != NIL && 
				_currentFocus->whoAreYou()->isIn(WEARECLASSOBJECTS)) {
				NodeFigure *fromNode = _currentConnection->nodeFigures()->getFirst();
				NodeFigure *thisNode = (NodeFigure *)_currentFocus;
				int x1 = thisNode->shape()->getX1();
				int y1 = thisNode->shape()->getY1();
				int x2 = thisNode->shape()->getX2();
				int y2 = thisNode->shape()->getY2();
				if (_currentFocus->whoAreYou()->equals(IAMWIDEPACKAGE) &&
					fromNode != NIL &&
					fromNode->containedWithin(x1,y1,x2,y2)) {
					lowlightDrawBoundary(_currentFocus);
					nodeFocus = NIL;
					stopFlag = FALSE;
				} else {
					nodeFocus = (NodeFigure *)_currentFocus;
					stopFlag = TRUE;
				}
			} else {
				nodeFocus = NIL;
				stopFlag = FALSE;
			}
			BOOL abortFlag = _currentConnection->stopDraw(testPoint,nodeFocus);
			if (abortFlag) {
				BOOL abortAll = _currentConnection->abortDraw();
				if (abortAll) {
					delete _currentConnection;
					_currentConnection = NIL;
					Invalidate();
				} else {
					insert(_currentConnection);
				}
				stopFlag = TRUE;
			}
			if (stopFlag == FALSE) {
				ktgF_connectionContinueDraw = TRUE;
			} else {
				if (_currentConnection != NIL &&
					_currentConnection->whoAreYou()->equals(IAMGENERALIZATION)) {
					Generalization *theGeneralization = (Generalization *)_currentConnection;
					theGeneralization->registerGeneralizationInfo();
				} else if (_currentConnection != NIL &&
					_currentConnection->whoAreYou()->equals(IAMAGGREGATION)) {
					Aggregation *theAggregation = (Aggregation *)_currentConnection;
					theAggregation->registerAggregationInfo();
				} else if (_currentConnection != NIL &&
					_currentConnection->whoAreYou()->equals(IAMDEPENDENCY)) {
					Dependency *theDependency = (Dependency *)_currentConnection;
					theDependency->registerDependencyInfo();
				}
				ktgF_connectionContinueDraw = FALSE;
				drawingEpilog();
				ReleaseCapture();
			}
		}
	}	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CClassView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COODView::OnDraw(pDC);
	if (_currentConnection != NIL) {
		if (ktgF_connectionDrawing) {
			rubberbanding(_currentConnection);
		}
	}
}

void CClassView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonDblClk(nFlags, point);
		return;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CClassView::OnTbAggregation() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_AGGREGATION);
	if (itsMe) return;
	OnCreateAggregation(); 
}

void CClassView::OnTbAssociation() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_ASSOCIATION);
	if (itsMe) return;
	OnCreateAssociation();
}

void CClassView::OnTbComposition() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_COMPOSITION);
	if (itsMe) return;
	OnCreateComposition();	
}

void CClassView::OnTbDependency() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_DEPENDENCY);
	if (itsMe) return;
	OnCreateDependency();	
}

void CClassView::OnTbGeneralization() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_GENERALIZATION);
	if (itsMe) return;
	OnCreateGeneralization();	
}

void CClassView::OnTbRefinement() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_REFINEMENT);
	if (itsMe) return;
	OnCreateRefinement();	
}

void CClassView::OnTbInterface() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_INTERFACE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_INTERFACE;
	pressModelTBButton(ID_TB_INTERFACE);
}

void CClassView::OnTbPackage() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_PACKAGE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_PACKAGE;
	pressModelTBButton(ID_TB_PACKAGE);
}

void CClassView::OnTbClasstemplate() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_CLASSTEMPLATE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_CLASSTEMPLATE;
	pressModelTBButton(ID_TB_CLASSTEMPLATE);	
}

void CClassView::OnTbTemplateclass() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_TEMPLATECLASS);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_TEMPLATECLASS;
	pressModelTBButton(ID_TB_TEMPLATECLASS);		
}

void CClassView::OnTbUtility() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_UTILITY);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_UTILITY;
	pressModelTBButton(ID_TB_UTILITY);			
}


void CClassView::OnTbWidePackage() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_WIDE_PACKAGE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_WIDE_PACKAGE;
	pressModelTBButton(ID_TB_WIDE_PACKAGE);
}

void CClassView::OnUpdatePopupOpenPackage(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	if (GetDocument()->IsEmbedded()) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
}

void CClassView::OnUpdateCreateAssociationClass(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (_currentFocus != NIL &&
		_currentFocus->whoAreYou()->equals(IAMASSOCIATION)) {
		Association *theAssociation = (Association *)_currentFocus;
		pCmdUI->Enable(theAssociation->canDoAssociationClass());
		return;
	}
	pCmdUI->ContinueRouting();
}

void CClassView::OnUpdateSupressDataMembers(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (_currentFocus != NIL &&
		_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
		ClassTemplate *pClass = (ClassTemplate *)_currentFocus;
		pCmdUI->Enable(pClass->canDoSupressDataMembers());
		return;
	}
	pCmdUI->ContinueRouting();
}

void CClassView::OnUpdateSupressMemberFunctions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (_currentFocus != NIL &&
		_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
		ClassTemplate *pClass = (ClassTemplate *)_currentFocus;
		pCmdUI->Enable(pClass->canDoSupressMemberFunctions());
		return;
	}
	pCmdUI->ContinueRouting();
}

void CClassView::OnUpdateGenerateCode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (GetDocument()->IsEmbedded()) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
}

void CClassView::OnUpdateToolsGenerateCode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (_currentFocus == NIL) {
		pCmdUI->Enable(TRUE); // generate code for all class
	} else if (_currentFocus != NIL && _currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
		pCmdUI->Enable(TRUE); // generate code for a class
	} else {
		pCmdUI->Enable(FALSE);
	}
}

void CClassView::OnGenerateCode()
{
	if (_currentFocus == NIL) {
		beep("CClassView::OnGenerateCode()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		beep("CClassView::OnGenerateCode()");
		return;
	}
	ClassTemplate *aClass = (ClassTemplate *) _currentFocus;
	if (aClass->classContent() != NULL &&
		aClass->classContent()->generateCodeFlag() == FALSE) {
		char buf[BUFSIZ];
		sprintf_s(buf,BUFSIZ,"%s class is not supposed to be generated into code.\n\r\
Please check the corresponding item in <Properties>/<Others> option.",
			aClass->classContent()->className());
		InfoMsg(buf);
		return;
	}
	CodeGenerator *codeGenerator = theAppPtr->getActiveCodeGenerator();
	codeGenerator->generateCodeFor(aClass->classContent(),TRUE);
	_currentFocus = NIL;
}

void CClassView::OnToolsGenerateCode() 
{
	// TODO: Add your command handler code here
	
	if (_currentFocus != NIL) {
		if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
			beep("CClassView::OnGenerateCode()");
			return;
		}
		ClassTemplate *aClass = (ClassTemplate *) _currentFocus;
		if (aClass->classContent() != NULL &&
			aClass->classContent()->generateCodeFlag() == FALSE) {
			char buf[BUFSIZ];
			sprintf_s(buf,BUFSIZ,"%s class is not supposed to be generated into code.\n\r\
Please check the corresponding item in <Properties>/<Others> option.",
				aClass->classContent()->className());
			InfoMsg(buf);
			return;
		}
		_currentFocus = NIL;
		char buf[BUFSIZ];
		sprintf_s(buf,BUFSIZ,"Are you sure to generate code for \"%s\" class ?",aClass->classContent()->className());
		UINT ans = YesNoMsg(buf);
		if (ans == IDYES) {
			CodeGenerator *codeGenerator = theAppPtr->getActiveCodeGenerator();
			codeGenerator->generateCodeFor(aClass->classContent(),TRUE);
		}
		return;
	}
	// Generate code for all class
	ClassLibrary *contentsToGenerate = new ClassLibrary();

	CodeGenerator *codeGenerator = theAppPtr->getActiveCodeGenerator();
	PackageLibrary *allClassContents = theAppPtr->pCOODClassDoc->getAllClassContents();
	ClassLibrary *aLibrary = allClassContents->getFirst();
	while (aLibrary != NIL) {
		ClassContent *aContent = aLibrary->getFirst();
		while (aContent != NIL) {
			if (aContent->isInnerClass() == FALSE) {
				contentsToGenerate->insert(aContent);
			}
			aContent = aLibrary->getNext();
		}
		aLibrary = allClassContents->getNext();
	}

	ClassContent *pContent = contentsToGenerate->getFirst();
	while (pContent != NIL) {
		if (pContent->generateCodeFlag()) {
			char buf[BUFSIZ];
			sprintf_s(buf,BUFSIZ,"Are you sure to generate code for \"%s\" class ?",pContent->className());
			UINT ans = YesNoMsg(buf);
			if (ans == IDYES) {
				codeGenerator->generateCodeFor(pContent,TRUE);
			}
		}
		pContent = contentsToGenerate->getNext();
	}
	contentsToGenerate->clear();
	delete contentsToGenerate;
}

