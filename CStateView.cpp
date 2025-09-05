// CStateView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CStateView.h"
#include "CMainFrame.h"
#include "Figures.h"
#include "LineNodeList.h"
#include "UnsignedLong.h"
#include "COODDoc.h"
#include "WideStateDlg.h"
#include "NodeFigureList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CStateView, COODView)

/////////////////////////////////////////////////////////////////////////////
// CStateView

CStateView::CStateView()
: COODView()
{
}

CStateView::~CStateView()
{
}


BEGIN_MESSAGE_MAP(CStateView, COODView)
	//{{AFX_MSG_MAP(CStateView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TB_TRANSITION, OnTbTransition)
	ON_COMMAND(ID_TB_STATE, OnTbState)
	ON_COMMAND(ID_TB_INITIAL_STATE, OnTbInitialState)
	ON_COMMAND(ID_TB_FINAL_STATE, OnTbFinalState)
	ON_COMMAND(ID_TB_WIDE_STATE, OnTbWideState)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CREATE_STATE, CStateView::OnCreateState)
	ON_COMMAND(ID_CREATE_WIDE_STATE, CStateView::OnCreateWideState)
	ON_COMMAND(ID_CREATE_INITIAL_STATE, CStateView::OnCreateInitialState)
	ON_COMMAND(ID_CREATE_FINAL_STATE, CStateView::OnCreateFinalState)
	ON_COMMAND(ID_CREATE_TRANSITION, CStateView::OnCreateTransition)
	ON_COMMAND(ID_CONNECTION_NAME_EDIT, CStateView::OnEventTransition)
END_MESSAGE_MAP()

void CStateView::setPopups()
{
	_mainPopup = theAppPtr->theStateMainPopup;
}

void CStateView::OnCreateState()
{
	State *aState = new State(this,_popupX,_popupY,_fontHeight,theAppPtr->theStatePopup);
	aState->setFocus();
	BOOL ok = aState->startEdit();
	if (ok == FALSE) {
		beep("CStateView::OnCreateState()");
		delete aState;
		return;
	}
	draw(aState);
	_currentFocus = (Figure *)aState;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CStateView::OnCreateWideState()
{
	WideStateDlg aDlg;
	UINT ans = aDlg.DoModal();
	if (ans == IDCANCEL) return;
	int numOfPlanes = aDlg.nOfPlanes();

	WideState *aState = new WideState(this,_popupX,_popupY,numOfPlanes-1,NIL);
	aState->setFocus();
	BOOL ok = aState->startEdit();
	if (ok == FALSE) {
		beep("CStateView::OnCreateWideState()");
		delete aState;
		return;
	}
	draw(aState);
	_currentFocus = (Figure *)aState;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CStateView::OnCreateInitialState()
{
	GetDocument()->setModifiedFlag(); 
	InitialState *aState = new InitialState(this,_popupX,_popupY,NIL);
	aState->makeRegion(_canvasRgn);
	addExcludeRectForBottomObjects(aState,figures());
	figures()->insert(aState);
	draw(aState);
}

void CStateView::OnCreateFinalState()
{
	GetDocument()->setModifiedFlag(); 
	FinalState *aState = new FinalState(this,_popupX,_popupY,NIL);
	aState->makeRegion(_canvasRgn);
	addExcludeRectForBottomObjects(aState,figures());
	figures()->insert(aState);
	draw(aState);
}

void CStateView::OnCreateTransition()
{
	collectActiveNodes(WEARESTATEOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more states.");
		return;
	}
	_whatTionToDraw = KTG_TRANSITION;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_TRANSITION);
}

void CStateView::OnEventTransition()
{
	if (_currentFocus == NIL) {
		beep("CStateView::OnEventTransition()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMTRANSITION) == FALSE) {
		beep("CStateView::OnEventTransition()");
		return;
	}
	lowlight(_currentFocus);
	_editingTag = TRUE;
	Transition * thisTransition = (Transition *)_currentFocus;
	EventText *aText = thisTransition->selectOrCreateText();
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	aText->startEdit();
	ktgF_processKeys = TRUE;
}

BOOL CStateView::validWhatTionToDraw()
{
	if (_whatTionToDraw == KTG_TRANSITION) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void CStateView::createNewConnection(CPoint point)
{
	lowlightDrawBoundary(_currentFocus);
	int x = point.x;
	int y = point.y;
	_currentX = x;
	_currentY = y;
	Line *aLine = new Line(this,x,y,NIL,STRAIGHT);
	aLine->setFollowing2(x,y);
	UINT commandID = 0;
	if (_whatTionToDraw == KTG_TRANSITION) {
		commandID = ID_TB_TRANSITION;
		_currentConnection = new Transition(this,theAppPtr->theTransitionPopup,aLine);
	}
	if (commandID != 0)
		releaseModelTBButton(commandID);
	EditableFigure *eNode = (EditableFigure *)_currentFocus;
	eNode->insert(_currentConnection);
	_currentConnection->insert(eNode);
	LineNode *node = _currentConnection->node(aLine);
	_currentConnection->activeLines()->insert(node);
	aLine->setOrient(Line::invertOrient(currentOrient));

	NodeFigure *thisNode = (NodeFigure *)_currentFocus;
	NodeFigure *aFigure = (NodeFigure *)_activeNodes->getFirst();
	while (aFigure != NIL) {
		int x1 = aFigure->shape()->getX1();
		int y1 = aFigure->shape()->getY1();
		int x2 = aFigure->shape()->getX2();
		int y2 = aFigure->shape()->getY2();
		UnsignedLong *who = aFigure->whoAreYou();
		if (who->equals(IAMWIDESTATE) &&
			thisNode->containedWithin(x1,y1,x2,y2)) {
			_activeNodes->remove(aFigure);
			aFigure = (NodeFigure *)_activeNodes->getFirst();
		} else {
			aFigure = (NodeFigure *)_activeNodes->getNext();
		}
	}
}

void CStateView::drawingEpilog()
{
	COODView::drawingEpilog();
}

/////////////////////////////////////////////////////////////////////////////
// CStateView message handlers


void CStateView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COODView::OnDraw(pDC);
	if (_currentConnection != NIL) {
		if (ktgF_connectionDrawing) {
			rubberbanding(_currentConnection);
		}
	}
}

void CStateView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonDblClk(nFlags, point);
		return;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CStateView::OnLButtonDown(UINT nFlags, CPoint point) 
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
			case ID_TB_STATE:
				OnCreateState();
				break;
			case ID_TB_INITIAL_STATE:
				OnCreateInitialState();
				break;
			case ID_TB_FINAL_STATE:
				OnCreateFinalState();
				break;
			case ID_TB_WIDE_STATE:
				OnCreateWideState();
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
			CScrollView::OnLButtonDown(nFlags, point);
			return;
		} 
		ktgF_connectionStartDraw = FALSE;
		createNewConnection(point);
		ktgF_connectionDrawing = TRUE;
	} else if (ktgF_connectionContinueDraw) {
		if (_currentConnection == NIL) {
			beep("CStateView::OnLButtonDown(UINT nFlags, CPoint point)");
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

void CStateView::OnLButtonUp(UINT nFlags, CPoint point) 
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
				_currentFocus->whoAreYou()->isIn(WEARESTATEOBJECTS)) {
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
				drawingEpilog();
				ReleaseCapture();
			}
		}
	}	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CStateView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pSender == NULL) return;
	if (!pSender->IsKindOf(RUNTIME_CLASS(CStateView))) return;
}

void CStateView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CStateView::OnTbTransition() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_TRANSITION);
	if (itsMe) return;
	OnCreateTransition(); 	
}

void CStateView::OnTbState() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_STATE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_STATE;
	pressModelTBButton(ID_TB_STATE);				
}

void CStateView::OnTbInitialState() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_INITIAL_STATE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_INITIAL_STATE;
	pressModelTBButton(ID_TB_INITIAL_STATE);				
}

void CStateView::OnTbFinalState() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_FINAL_STATE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_FINAL_STATE;
	pressModelTBButton(ID_TB_FINAL_STATE);					
}

void CStateView::OnTbWideState() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_WIDE_STATE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_WIDE_STATE;
	pressModelTBButton(ID_TB_WIDE_STATE);				
}
