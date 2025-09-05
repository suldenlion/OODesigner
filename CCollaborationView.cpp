// CCollaborationView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CMainFrame.h"
#include "CCollaborationView.h"
#include "Figures.h"
#include "UnsignedLong.h"
#include "ConnectionInfoTuple.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCollaborationView, COODView)
/////////////////////////////////////////////////////////////////////////////
// CCollaborationView

CCollaborationView::CCollaborationView()
: COODView()
{
}

CCollaborationView::~CCollaborationView()
{
}


BEGIN_MESSAGE_MAP(CCollaborationView, COODView)
	//{{AFX_MSG_MAP(CCollaborationView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TB_COL_MESSAGE, OnTbColMessage)
	ON_COMMAND(ID_TB_COL_MULTI_OBJECT, OnTbColMultiObject)
	ON_COMMAND(ID_TB_COL_OBJECT, OnTbColObject)
	ON_COMMAND(ID_SELF_DELEGATION_COLLABORATION_OBJECT, OnSelfDelegationCollaborationObject)
	ON_UPDATE_COMMAND_UI(ID_SELF_DELEGATION_COLLABORATION_OBJECT, OnUpdateSelfDelegationCollaborationObject)
	ON_COMMAND(ID_SELF_DELEGATION_DELETE, OnSelfDelegationDelete)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CREATE_COLLABORATION_OBJECT, CCollaborationView::OnCreateCollaborationObject)
	ON_COMMAND(ID_CREATE_COLLABORATION_MULTI_OBJECT, CCollaborationView::OnCreateCollaborationMultiObject)
	ON_COMMAND(ID_CREATE_MESSAGE_FLOW, CCollaborationView::OnCreateMessageFlow)
	ON_COMMAND(ID_MESSAGE_MESSAGE_FLOW, CCollaborationView::OnMessageMessageFlow)
	ON_COMMAND(ID_SHIFT_ARROW_MESSAGE_TEXT, CCollaborationView::OnShiftArrowMessageText)
	ON_COMMAND(ID_INVERT_ARROW_MESSAGE_TEXT, CCollaborationView::OnInvertArrowMessageText)
END_MESSAGE_MAP()

void CCollaborationView::setPopups()
{
	_mainPopup = theAppPtr->theCollaborationMainPopup;
}

void CCollaborationView::OnInvertArrowMessageText()
{
	if (_currentFocus == NIL) {
		beep("CCollaborationView::OnInvertArrowMessageText()");
		return;
	}
	lowlight(_currentFocus);
	if (_currentFocus->focus() == NIL) {
		beep("CCollaborationView::OnInvertArrowMessageText()");
		return;
	}
	if (_currentFocus->focus()->whoAreYou()->equals(IAMMESSAGETEXT) == FALSE) {
		beep("CCollaborationView::OnInvertArrowMessageText()");
		return;
	}
	MessageText *thisText = (MessageText *)_currentFocus->focus();
	thisText->invertArrow();
	_currentFocus = NIL;
}

void CCollaborationView::OnShiftArrowMessageText()
{
	if (_currentFocus == NIL) {
		beep("CCollaborationView::OnShiftArrowMessageText()");
		return;
	}
	lowlight(_currentFocus);
	if (_currentFocus->focus() == NIL) {
		beep("CCollaborationView::OnShiftArrowMessageText()");
		return;
	}
	if (_currentFocus->focus()->whoAreYou()->equals(IAMMESSAGETEXT) == FALSE) {
		beep("CCollaborationView::OnShiftArrowMessageText()");
		return;
	}
	MessageText *thisText = (MessageText *)_currentFocus->focus();
	thisText->shiftArrow();
	_currentFocus = NIL;
}

void CCollaborationView::OnMessageMessageFlow()
{
	if (_currentFocus == NIL) {
		beep("CCollaborationView::OnMessageMessageFlow()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMMESSAGEFLOW) == FALSE) {
		beep("CCollaborationView::OnMessageMessageFlow()");
		return;
	}
	lowlight(_currentFocus);
	_editingTag = TRUE;
	MessageFlow * thisFlow = (MessageFlow *)_currentFocus;
	MessageText *aText = thisFlow->selectOrCreateText();
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	aText->startEdit();
	ktgF_processKeys = TRUE;
}

void CCollaborationView::OnCreateCollaborationObject()
{
	CollaborationObject *anObject = new CollaborationObject(this,_popupX,_popupY,_fontHeight,theAppPtr->theCollaborationObjectPopup);
	anObject->setFocus();
	BOOL ok = anObject->startEdit();
	if (ok == FALSE) {
		beep("CCollaborationView::OnCreateCollaborationObject()");
		delete anObject;
		return;
	}
	draw(anObject);
	_currentFocus = (Figure *)anObject;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CCollaborationView::OnCreateCollaborationMultiObject()
{
	CollaborationMultiObject *anObject = new CollaborationMultiObject(this,_popupX,_popupY,_fontHeight,theAppPtr->theCollaborationObjectPopup);
	anObject->setFocus();
	BOOL ok = anObject->startEdit();
	if (ok == FALSE) {
		beep("CCollaborationView::OnCreateCollaborationMultiObject()");
		delete anObject;
		return;
	}
	draw(anObject);
	_currentFocus = (Figure *)anObject;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CCollaborationView::OnCreateMessageFlow()
{
	collectActiveNodes(WEARECOLLABORATIONOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named objects.");
		return;
	}
	_whatTionToDraw = KTG_MESSAGEFLOW;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_COL_MESSAGE);
}

BOOL CCollaborationView::validWhatTionToDraw()
{
	if (_whatTionToDraw == KTG_MESSAGEFLOW) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void CCollaborationView::createNewConnection(CPoint point)
{
	lowlightDrawBoundary(_currentFocus);
	int x = point.x;
	int y = point.y;
	_currentX = x;
	_currentY = y;
	Line *aLine = new Line(this,x,y,NIL,STRAIGHT);
	aLine->setFollowing2(x,y);
	UINT commandID = 0;
	if (_whatTionToDraw == KTG_MESSAGEFLOW) {
		commandID = ID_TB_COL_MESSAGE;
		_currentConnection = new MessageFlow(this,theAppPtr->theMessageFlowPopup,aLine);
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

void CCollaborationView::drawingEpilog()
{
	COODView::drawingEpilog();
}

/////////////////////////////////////////////////////////////////////////////
// CCollaborationView message handlers

void CCollaborationView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COODView::OnDraw(pDC);
	if (_currentConnection != NIL) {
		if (ktgF_connectionDrawing) {
			rubberbanding(_currentConnection);
		}
	}
}

void CCollaborationView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pSender == NULL) return;
	if (!pSender->IsKindOf(RUNTIME_CLASS(CCollaborationView))) return;
}

void CCollaborationView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonDblClk(nFlags, point);
		return;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CCollaborationView::OnLButtonDown(UINT nFlags, CPoint point) 
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
			case ID_TB_COL_OBJECT:
				OnCreateCollaborationObject();
				break;
			case ID_TB_COL_MULTI_OBJECT:
				OnCreateCollaborationMultiObject();
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
			beep("CCollaborationView::OnLButtonDown(UINT nFlags, CPoint point)");
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

void CCollaborationView::OnLButtonUp(UINT nFlags, CPoint point) 
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
				_currentFocus->whoAreYou()->isIn(WEARECOLLABORATIONOBJECTS)) {
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
					_currentConnection->whoAreYou()->equals(IAMMESSAGEFLOW)) {
					currentOrient = UNDEFINED;
					_activeNodes->clear();
					_whatTionToDraw = -1;
					_currentFocus = _currentConnection;
					_currentConnection->setTextPosition(-30,20,-10);
					_currentConnection = NIL;
					if (_currentFocus->focus() != NIL &&
						_currentFocus->focus()->whoAreYou()->equals(IAMMESSAGETEXT)) {
						_editingTag = TRUE;
						MessageText *aText = (MessageText *)_currentFocus->focus();
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

void CCollaborationView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CCollaborationView::OnTbColMessage() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_COL_MESSAGE);
	if (itsMe) return;
	OnCreateMessageFlow(); 	
}

void CCollaborationView::OnTbColMultiObject() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_COL_MULTI_OBJECT);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_COL_MULTI_OBJECT;
	pressModelTBButton(ID_TB_COL_MULTI_OBJECT);			
}

void CCollaborationView::OnTbColObject() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_COL_OBJECT);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_COL_OBJECT;
	pressModelTBButton(ID_TB_COL_OBJECT);			
}

void CCollaborationView::OnSelfDelegationCollaborationObject() 
{
	// TODO: Add your command handler code here
	
	if (_currentFocus == NIL) {
		beep("CCollaborationView::OnMakeSelfDelegation()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCOLLABORATIONOBJECT) == FALSE) {
		beep("CCollaborationView::OnMakeSelfDelegation()");
		return;
	}
	lowlight(_currentFocus);
	CollaborationObject *thisObject = (CollaborationObject *)_currentFocus;
	CollaborationObjectMessageText * aText = thisObject->setSelfDelegation();
	if (aText == NIL) {
		/* turn off the text */
		_currentFocus = NIL;
		return; 
	}
	/* turn on the text */
	_editingTag = TRUE;
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	aText->startEdit();
	ktgF_processKeys = TRUE;
}

void CCollaborationView::OnUpdateSelfDelegationCollaborationObject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (_currentFocus != NIL &&
		_currentFocus->whoAreYou()->equals(IAMCOLLABORATIONOBJECT)) {
		CollaborationObject *thisObject = (CollaborationObject *)_currentFocus;
		pCmdUI->Enable(thisObject->canDoSelfDelegation());
		return;
	}
	pCmdUI->ContinueRouting();
}

void CCollaborationView::OnSelfDelegationDelete() 
{
	// TODO: Add your command handler code here
	OnSelfDelegationCollaborationObject();
}
