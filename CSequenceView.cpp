// CSequenceView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CSequenceView.h"
#include "CMainFrame.h"
#include "Figures.h"
#include "UnsignedLong.h"
#include "ConnectionInfoTuple.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "COODDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSequenceView, COODView)
/////////////////////////////////////////////////////////////////////////////
// CSequenceView

CSequenceView::CSequenceView()
: COODView()
{
}

CSequenceView::~CSequenceView()
{
}


BEGIN_MESSAGE_MAP(CSequenceView, COODView)
	//{{AFX_MSG_MAP(CSequenceView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TB_SEQUENCE_ASYNC, OnTbSequenceAsync)
	ON_COMMAND(ID_TB_SEQUENCE_OBJECT, OnTbSequenceObject)
	ON_COMMAND(ID_TB_SEQUENCE_RETURN, OnTbSequenceReturn)
	ON_COMMAND(ID_TB_SEQUENCE_SYNC, OnTbSequenceSync)
	ON_COMMAND(ID_ACTIVATION_KILL_SIGN, OnActivationKillSign)
	ON_UPDATE_COMMAND_UI(ID_ACTIVATION_KILL_SIGN, OnUpdateActivationKillSign)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CREATE_SEQUENCE_OBJECT, CSequenceView::OnCreateSequenceObject)
	ON_COMMAND(ID_ACTIVATION_SEQUENCE_OBJECT, CSequenceView::OnCreateSequenceActivation)
	ON_COMMAND(ID_CREATE_SYNC_MESSAGE, CSequenceView::OnCreateSyncMessage)
	ON_COMMAND(ID_CREATE_ASYNC_MESSAGE, CSequenceView::OnCreateAsyncMessage)
	ON_COMMAND(ID_CREATE_RETURN_MESSAGE, CSequenceView::OnCreateReturnMessage)
	ON_COMMAND(ID_CONNECTION_NAME_EDIT, CSequenceView::OnEditConnectionName)
	ON_COMMAND(ID_SEQUENCE_SELF_DELEGATION, CSequenceView::OnCreateSelfDelegation)
END_MESSAGE_MAP()

void CSequenceView::setPopups()
{
	_mainPopup = theAppPtr->theSequenceMainPopup;
}

BOOL CSequenceView::checkLimitForFigure(int newx,int newy,int *deltax,int *deltay)
{
	if (_currentConnection != NIL &&
		_currentConnection->whoAreYou()->isIn(WEARESIMPLECONNECTIONS)) {
		return COODView::checkLimitForFigure(newx,newy,deltax,deltay);
	} else if (_currentFocus != NIL &&
		_currentFocus->whoAreYou()->equals(IAMBUCKET)) {
		return COODView::checkLimitForFigure(newx,newy,deltax,deltay);
	} else {
		return FALSE;
	}
}

void CSequenceView::startResize()
{
	COODView::startResize();
	_savedHotX = -1;
	_savedHotY = -1;
	if (_currentFocus->whoAreYou()->isIn(WEARESIMPLECONNECTIONS)) {
		Connection *currentConnection = (Connection *)_currentFocus;
		currentConnection->getHotXY(_savedHotX,_savedHotY);
	}
}

void CSequenceView::OnCreateSelfDelegation()
{
	GetDocument()->setModifiedFlag(); 
	if (_currentFocus == NIL) {
		beep("CSequenceView::OnCreateSelfDelegation()");
		return;
	}
	lowlight(_currentFocus);
	SequenceObject *anObject = (SequenceObject *)_currentFocus;
	_currentFocus = NIL;
	SequenceSelfDelegation * aSelfDelegation =
		anObject->createSelfDelegation(this,_popupX,_popupY,theAppPtr->theMessagePopup);
	if (aSelfDelegation == NIL) {
		beep("CSequenceView::OnCreateSelfDelegation()");
		return;
	}
	aSelfDelegation->makeRegion(_canvasRgn);
	addExcludeRectForBottomObjects(aSelfDelegation,figures());
	figures()->insert(aSelfDelegation);
	Invalidate();
}

void CSequenceView::OnCreateSequenceActivation()
{
	if (_currentFocus == NIL) {
		beep("CSequenceView::OnCreateSequenceActivation()");
		return;
	}
	lowlight(_currentFocus);
	if (_currentFocus->focus() == NIL) {
		beep("CSequenceView::OnCreateSequenceActivation()");
		return;
	}
	SequenceObject *anObject = (SequenceObject *)_currentFocus;
	anObject->makeNewActivationBar(_popupX,_popupY);
	anObject->makeRegion(_canvasRgn);
	draw(anObject);
	_currentFocus = NIL;
}

void CSequenceView::OnCreateSequenceObject()
{
	SequenceObject *anObject = new SequenceObject(this,_popupX,_popupY,_fontHeight,theAppPtr->theSequenceObjectPopup);
	anObject->setFocus();
	BOOL ok = anObject->startEdit();
	if (ok == FALSE) {
		beep("CSequenceView::OnCreateSequenceObject()");
		delete anObject;
		return;
	}
	draw(anObject);
	_currentFocus = (Figure *)anObject;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CSequenceView::OnCreateSyncMessage()
{
	collectActiveNodes(WEARESEQUENCEOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named objects.");
		return;
	}
	_whatTionToDraw = KTG_SYNCMESSAGE;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_SEQUENCE_SYNC);
}

void CSequenceView::OnCreateAsyncMessage()
{
	collectActiveNodes(WEARESEQUENCEOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named objects.");
		return;
	}
	_whatTionToDraw = KTG_ASYNCMESSAGE;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_SEQUENCE_ASYNC);
}

void CSequenceView::OnCreateReturnMessage()
{
	collectActiveNodes(WEARESEQUENCEOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named objects.");
		return;
	}
	_whatTionToDraw = KTG_RETURNMESSAGE;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_SEQUENCE_RETURN);
}

void CSequenceView::OnEditConnectionName()
{
	if (_currentFocus == NIL) {
		beep("CSequenceView::OnEditConnectionName()");
		return;
	}
	lowlight(_currentFocus);
	if (_currentFocus->whoAreYou()->equals(IAMSYNCMESSAGE) == TRUE) {
		_editingTag = TRUE;
		SequenceSyncMessage * thisMessage = (SequenceSyncMessage *)_currentFocus;
		SequenceMessageText *aText = thisMessage->selectOrCreateText();
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
		aText->startEdit();
		ktgF_processKeys = TRUE;
		return;
	} else if (_currentFocus->whoAreYou()->equals(IAMASYNCMESSAGE) == TRUE) {
		_editingTag = TRUE;
		SequenceAsyncMessage * thisMessage = (SequenceAsyncMessage *)_currentFocus;
		SequenceMessageText *aText = thisMessage->selectOrCreateText();
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
		aText->startEdit();
		ktgF_processKeys = TRUE;
		return;
	} else if (_currentFocus->whoAreYou()->equals(IAMRETURNMESSAGE) == TRUE) {
		_editingTag = TRUE;
		SequenceReturnMessage * thisMessage = (SequenceReturnMessage *)_currentFocus;
		SequenceMessageText *aText = thisMessage->selectOrCreateText();
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
		aText->startEdit();
		ktgF_processKeys = TRUE;
		return;
	} else if (_currentFocus->whoAreYou()->equals(IAMSEQUENCESELFDELEGATION) == TRUE) {
		_editingTag = TRUE;
		SequenceSelfDelegation * thisMessage = (SequenceSelfDelegation *)_currentFocus;
		ConnectionText *aText = thisMessage->selectOrCreateText();
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
		aText->startEdit();
		ktgF_processKeys = TRUE;
		return;
	} else {
		beep("CSequenceView::OnEditConnectionName()");
		return;
	}
}

BOOL CSequenceView::validWhatTionToDraw()
{
	if (_whatTionToDraw == KTG_SYNCMESSAGE ||
		_whatTionToDraw == KTG_ASYNCMESSAGE ||
		_whatTionToDraw == KTG_RETURNMESSAGE) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void CSequenceView::createNewConnection(CPoint point)
{
	lowlightDrawBoundary(_currentFocus);
	int x = point.x;
	int y = point.y;
	_currentX = x;
	_currentY = y;
	Line *aLine = new Line(this,x,y,NIL,ORDINARY);
	aLine->setFollowing2(x,y);
	UINT commandID = 0;
	if (_whatTionToDraw == KTG_SYNCMESSAGE) {
		commandID = ID_TB_SEQUENCE_SYNC;
		_currentConnection = new SequenceSyncMessage(this,theAppPtr->theMessagePopup,aLine);
	} else if (_whatTionToDraw == KTG_ASYNCMESSAGE) {
		commandID = ID_TB_SEQUENCE_ASYNC;
		_currentConnection = new SequenceAsyncMessage(this,theAppPtr->theMessagePopup,aLine);
	} else if (_whatTionToDraw == KTG_RETURNMESSAGE) {
		commandID = ID_TB_SEQUENCE_RETURN;
		_currentConnection = new SequenceReturnMessage(this,theAppPtr->theMessagePopup,aLine);
	}
	if (commandID != 0)
		releaseModelTBButton(commandID);
	EditableFigure *eNode = (EditableFigure *)_currentFocus;
	eNode->insert(_currentConnection);
	_currentConnection->insert(eNode);
	LineNode *node = _currentConnection->node(aLine);
	_currentConnection->activeLines()->insert(node);
	aLine->style() = _currentConnection->style();
}

void CSequenceView::drawingEpilog()
{
	COODView::drawingEpilog();
}
/////////////////////////////////////////////////////////////////////////////
// CSequenceView message handlers

void CSequenceView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COODView::OnDraw(pDC);
	if (_currentConnection != NIL) {
		if (ktgF_connectionDrawing) {
			rubberbanding(_currentConnection);
		}
	}
}

void CSequenceView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pSender == NULL) return;
	if (!pSender->IsKindOf(RUNTIME_CLASS(CSequenceView))) return;
}

void CSequenceView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonDblClk(nFlags, point);
		return;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CSequenceView::OnLButtonDown(UINT nFlags, CPoint point) 
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
			case ID_TB_SEQUENCE_OBJECT:
				OnCreateSequenceObject();
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
			InfoMsg("Please drag from a node figure or a life lane."); 
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
		/* 이 블럭은 거의 필요없음: 왜냐하면 Sequence 에서는 SimpleConnection 만 사용되기 때문에 */
		if (_currentConnection == NIL) {
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

void CSequenceView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (validWhatTionToDraw() == FALSE) {
		if (ktgF_simpleDrawing == TRUE &&
			_currentFocus != NIL &&
			_currentFocus->whoAreYou()->isIn(WEARESIMPLECONNECTIONS)) {
			SimpleConnection *currentConnection = (SimpleConnection *)_currentFocus;
			int testHotX = -1;
			int testHotY = -1;
			currentConnection->getHotXY(testHotX,testHotY);
			CPoint testPoint;
			testPoint.x = testHotX;
			testPoint.y = testHotY;
			localTraceEnter(testPoint,figures(),TRUE);

			NodeFigure *targetNode = currentConnection->getTargetNodeForResizing();
			if (_currentFocus == NIL ||
				targetNode == NIL || 
				targetNode != _currentFocus) {
				beep("Wrong position.");
				rubberbanding(currentConnection);
				currentConnection->setHotXY(_savedHotX,_savedHotY);
				rubberbanding(currentConnection);
			}
			_currentFocus = (Figure *)currentConnection;
		} 
		COODView::OnLButtonUp(nFlags, point);
		return;
	} else {
		if (ktgF_connectionDrawing == FALSE) {
			COODView::OnLButtonUp(nFlags, point);
			return;
		} else {
			ktgF_connectionDrawing = FALSE;
			NodeFigure *nodeFocus;
			BOOL abortFlag;
			if (_currentFocus != NIL && 
				_currentFocus->whoAreYou()->isIn(WEARESEQUENCEOBJECTS)) {
				nodeFocus = (NodeFigure *)_currentFocus;
				abortFlag = FALSE;
			} else {
				nodeFocus = NIL;
				abortFlag = TRUE;
			}
			if (abortFlag == FALSE) {
				abortFlag = _currentConnection->stopDraw(point,nodeFocus);
			}
			if (abortFlag) {
				BOOL abortAll = _currentConnection->abortDraw();
				if (abortAll) {
					delete _currentConnection;
					_currentConnection = NIL;
					Invalidate();
				} else {
					insert(_currentConnection);
				}
				_savedHotX = -1;
				_savedHotY = -1;
			}
			ktgF_connectionContinueDraw = FALSE;
			drawingEpilog();
			ReleaseCapture();
		}
	}	
	CScrollView::OnLButtonUp(nFlags, point);
}


void CSequenceView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint orgPoint(point);
	DPtoLP(point);
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnMouseMove(nFlags, orgPoint);
		return;
	} else {
		setPositionOnStatusBar(point.x,point.y);
		if (ktgF_connectionDrawing) {
			CPoint testPoint;
			Line *focusLine = (Line *)_currentConnection->focus();
			testPoint.x = focusLine->getX2();
			testPoint.y = focusLine->getY2();
			localTraceEnter(testPoint,_activeNodes,FALSE);
			drawingHandler(point,_currentConnection);
		} else {
			localTraceEnter(point,_activeNodes,FALSE);
		}
	}	
	CScrollView::OnMouseMove(nFlags, orgPoint);
}

void CSequenceView::OnTbSequenceAsync() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_SEQUENCE_ASYNC);
	if (itsMe) return;
	OnCreateAsyncMessage(); 		
}

void CSequenceView::OnTbSequenceReturn() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_SEQUENCE_RETURN);
	if (itsMe) return;
	OnCreateReturnMessage(); 		
}

void CSequenceView::OnTbSequenceSync() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_SEQUENCE_SYNC);
	if (itsMe) return;
	OnCreateSyncMessage(); 		
}

void CSequenceView::OnTbSequenceObject() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_SEQUENCE_OBJECT);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_SEQUENCE_OBJECT;
	pressModelTBButton(ID_TB_SEQUENCE_OBJECT);					
}


void CSequenceView::OnActivationKillSign() 
{
	// TODO: Add your command handler code here
	if (_currentFocus == NIL) {
		beep("CSequenceView::OnActivationKillSign()");
		return;
	}
	lowlight(_currentFocus);
	SequenceObject *anObject = (SequenceObject *)_currentFocus;
	anObject->processKillSign();
	anObject->makeRegion(_canvasRgn);
	Invalidate();
	_currentFocus = NIL;	
}

void CSequenceView::OnUpdateActivationKillSign(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (_currentFocus != NIL &&
		_currentFocus->whoAreYou()->equals(IAMSEQUENCEOBJECT)) {
		SequenceObject *anObject = (SequenceObject *)_currentFocus;
		pCmdUI->Enable(anObject->canDoKillSign());
		return;
	}
	pCmdUI->ContinueRouting();
}
