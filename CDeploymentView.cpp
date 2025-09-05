// CDeploymentView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CDeploymentView.h"
#include "CMainFrame.h"
#include "Figures.h"
#include "LineNodeList.h"
#include "UnsignedLong.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDeploymentView, COODView)
/////////////////////////////////////////////////////////////////////////////
// CDeploymentView

CDeploymentView::CDeploymentView()
: COODView()
{
}

CDeploymentView::~CDeploymentView()
{
}


BEGIN_MESSAGE_MAP(CDeploymentView, COODView)
	//{{AFX_MSG_MAP(CDeploymentView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TB_DEP_COMMUNICATION, OnTbDepCommunication)
	ON_COMMAND(ID_TB_DEP_DEPENDENCY, OnTbDepDependency)
	ON_COMMAND(ID_TB_DEP_HW_CONNECTION, OnTbDepHwConnection)
	ON_COMMAND(ID_TB_DEP_COMPONENT, OnTbDepComponent)
	ON_COMMAND(ID_TB_HWNODE, OnTbHwnode)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CREATE_HARDWARE_NODE, CDeploymentView::OnCreateHardwareNode)
	ON_COMMAND(ID_CREATE_COMPONENT_TEMPLATE, CDeploymentView::OnCreateComponentTemplate)
	ON_COMMAND(ID_CREATE_HWCONNECTION, CDeploymentView::OnCreateHWConnection)
	ON_COMMAND(ID_CREATE_DEPENDENCY, CDeploymentView::OnCreateDependency)
	ON_COMMAND(ID_CREATE_COMMUNICATION, CDeploymentView::OnCreateCommunication)
	ON_COMMAND(ID_CONNECTION_NAME_EDIT, CDeploymentView::OnEditConnectionName)
END_MESSAGE_MAP()

void CDeploymentView::setPopups()
{
	_mainPopup = theAppPtr->theDeploymentMainPopup;
}

void CDeploymentView::OnCreateHardwareNode()
{
	HardwareNode *aNode = new HardwareNode(this,_popupX,_popupY,NIL);
	aNode->setFocus();
	BOOL ok = aNode->startEdit();
	if (ok == FALSE) {
		beep("CDeploymentView::OnCreateHardwareNode()");
		delete aNode;
		return;
	}
	draw(aNode);
	_currentFocus = (Figure *)aNode;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CDeploymentView::OnCreateComponentTemplate()
{
	ComponentTemplate *aComponent = new ComponentTemplate(this,_popupX,_popupY,_fontHeight,/*theAppPtr->theComponentTemplatePopup*/NIL);
	aComponent->setFocus();
	BOOL ok = aComponent->startEdit();
	if (ok == FALSE) {
		beep("CDeploymentView::OnCreateComponentTemplate()");
		delete aComponent;
		return;
	}
	draw(aComponent);
	_currentFocus = (Figure *)aComponent;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CDeploymentView::OnCreateHWConnection()
{
	collectActiveNodes(IAMHARDWARENODE);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more H/W nodes.");
		return;
	}
	_whatTionToDraw = KTG_HWCONNECTION;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_DEP_HW_CONNECTION);
}

void CDeploymentView::OnCreateDependency()
{
	collectActiveNodes(IAMCOMPONENTTEMPLATE);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named components.");
		return;
	}
	_whatTionToDraw = KTG_DEPENDENCY;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_DEP_DEPENDENCY);
}

void CDeploymentView::OnCreateCommunication()
{
	collectActiveNodes(IAMCOMPONENTTEMPLATE);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named components.");
		return;
	}
	_whatTionToDraw = KTG_COMMUNICATION;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_DEP_COMMUNICATION);
}

void CDeploymentView::OnEditConnectionName()
{
	if (_currentFocus == NIL) {
		beep("CDeploymentView::OnEditConnectionName()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCOMMUNICATION) == FALSE &&
		_currentFocus->whoAreYou()->equals(IAMDEPENDENCY) == FALSE &&
		_currentFocus->whoAreYou()->equals(IAMHWCONNECTION) == FALSE) {
		beep("CDeploymentView::OnEditConnectionName()");
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

BOOL CDeploymentView::validWhatTionToDraw()
{
	if (_whatTionToDraw == KTG_DEPENDENCY ||
		_whatTionToDraw == KTG_COMMUNICATION ||
		_whatTionToDraw == KTG_HWCONNECTION) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void CDeploymentView::createNewConnection(CPoint point)
{
	lowlightDrawBoundary(_currentFocus);
	int x = point.x;
	int y = point.y;
	_currentX = x;
	_currentY = y;
	Line *aLine = new Line(this,x,y,NIL,STRAIGHT);
	aLine->setFollowing2(x,y);
	UINT commandID = 0;
	if (_whatTionToDraw == KTG_HWCONNECTION) {
		commandID = ID_TB_DEP_HW_CONNECTION;
		_currentConnection = new HWConnection(this,theAppPtr->theHWConnectionPopup,aLine);
	} else if (_whatTionToDraw == KTG_COMMUNICATION) {
		commandID = ID_TB_DEP_COMMUNICATION;
		_currentConnection = new Communication(this,theAppPtr->theDependencyPopup,aLine);
	} else if (_whatTionToDraw == KTG_DEPENDENCY) {
		commandID = ID_TB_DEP_DEPENDENCY;
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
}

void CDeploymentView::drawingEpilog()
{
	COODView::drawingEpilog();
}
/////////////////////////////////////////////////////////////////////////////
// CDeploymentView message handlers

void CDeploymentView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COODView::OnDraw(pDC);
	if (_currentConnection != NIL) {
		if (ktgF_connectionDrawing) {
			rubberbanding(_currentConnection);
		}
	}	
}

void CDeploymentView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
		
	if (pSender == NULL) return;
	if (!pSender->IsKindOf(RUNTIME_CLASS(CDeploymentView))) return;
}

void CDeploymentView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonDblClk(nFlags, point);
		return;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CDeploymentView::OnLButtonDown(UINT nFlags, CPoint point) 
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
			case ID_TB_HWNODE:
				OnCreateHardwareNode();
				break;
			case ID_TB_DEP_COMPONENT:
				OnCreateComponentTemplate();
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
		ktgF_connectionStartDraw = FALSE;
		createNewConnection(point);
		ktgF_connectionDrawing = TRUE;
	} else if (ktgF_connectionContinueDraw) {
		if (_currentConnection == NIL) {
			beep("CDeploymentView::OnLButtonDown(UINT nFlags, CPoint point)");
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

void CDeploymentView::OnLButtonUp(UINT nFlags, CPoint point) 
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
				_currentFocus->whoAreYou()->isIn(WEAREDEPLOYMENTOBJECTS)) {
				nodeFocus = (NodeFigure *)_currentFocus;
				stopFlag = TRUE;
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
				ktgF_connectionContinueDraw = FALSE;
				ReleaseCapture();
				if (_currentConnection != NIL &&
					_currentConnection->whoAreYou()->equals(IAMHWCONNECTION)) {
					currentOrient = UNDEFINED;
					_activeNodes->clear();
					_whatTionToDraw = -1;
					_currentFocus = _currentConnection;
					_currentConnection->setTextPosition(-30,20,-10);
					_currentConnection = NIL;
					if (_currentFocus->focus() != NIL &&
						_currentFocus->focus()->whoAreYou()->equals(IAMHWCONNECTIONTEXT)) {
						_editingTag = TRUE;
						HWConnectionText *aText = (HWConnectionText *)_currentFocus->focus();
						figures()->remove(_currentFocus);
						checkInList(_currentFocus);
						aText->startEdit();
						ktgF_processKeys = TRUE;
					}
				} else {
					drawingEpilog();
				}
			}
		}
	}	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CDeploymentView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CDeploymentView::OnTbDepCommunication() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_DEP_COMMUNICATION);
	if (itsMe) return;
	OnCreateCommunication(); 	
}

void CDeploymentView::OnTbDepDependency() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_DEP_DEPENDENCY);
	if (itsMe) return;
	OnCreateDependency(); 	
}

void CDeploymentView::OnTbDepHwConnection() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_DEP_HW_CONNECTION);
	if (itsMe) return;
	OnCreateHWConnection(); 	
}

void CDeploymentView::OnTbDepComponent() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_DEP_COMPONENT);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_DEP_COMPONENT;
	pressModelTBButton(ID_TB_DEP_COMPONENT);					
}

void CDeploymentView::OnTbHwnode() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_HWNODE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_HWNODE;
	pressModelTBButton(ID_TB_HWNODE);				
}
