// CActivityView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CMainFrame.h"
#include "CActivityView.h"
#include "Figures.h"
#include "LineNodeList.h"
#include "UnsignedLong.h"
#include "COODDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CActivityView, COODView)

/////////////////////////////////////////////////////////////////////////////
// CActivityView

CActivityView::CActivityView()
: COODView()
{
}

CActivityView::~CActivityView()
{

}


BEGIN_MESSAGE_MAP(CActivityView, COODView)
	//{{AFX_MSG_MAP(CActivityView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TB_ACTIVITY, OnTbActivity)
	ON_COMMAND(ID_TB_BEGIN_ACTIVITY, OnTbBeginActivity)
	ON_COMMAND(ID_TB_END_ACTIVITY, OnTbEndActivity)
	ON_COMMAND(ID_TB_SYNC_BAR, OnTbSyncBar)
	ON_COMMAND(ID_TB_TRIGGER, OnTbTrigger)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CREATE_ACTIVITY, CActivityView::OnCreateActivity)
	ON_COMMAND(ID_CREATE_TRIGGER, CActivityView::OnCreateTrigger)
	ON_COMMAND(ID_CREATE_SYNCHRONIZATION_BAR, CActivityView::OnCreateSyncBar)
	ON_COMMAND(ID_CREATE_BEGIN_ACTIVITY, CActivityView::OnCreateBeginActivity)
	ON_COMMAND(ID_CREATE_END_ACTIVITY, CActivityView::OnCreateEndActivity)
	ON_COMMAND(ID_CONNECTION_NAME_EDIT, CActivityView::OnGuardTrigger)
END_MESSAGE_MAP()

void CActivityView::setPopups()
{
	_mainPopup = theAppPtr->theActivityMainPopup;
}

void CActivityView::startFork()
{
	if (_currentFocus == NIL) return;
	if (_currentFocus->whoAreYou()->equals(IAMTRIGGER)) {
		_whatTionToDraw = KTG_TRIGGER;
	} else {
		return;
	}
	collectActiveNodes(WEAREACTIVITYOBJECTS);

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
	_currentX = _forkX;
	_currentY = _forkY;
	_currentConnection->insertALine(aLine,TRUE);
	LineNode *node = _currentConnection->node(aLine);
	_currentConnection->activeLines()->insert(node);
	aLine->setFollowing2(_forkX,_forkY);
	_forkX = -1; _forkY = -1;

	ktgF_connectionDrawing = TRUE;
}

void CActivityView::OnCreateActivity()
{
	Activity *anActivity = new Activity(this,_popupX,_popupY,_fontHeight,NIL);
	anActivity->setFocus();
	BOOL ok = anActivity->startEdit();
	if (ok == FALSE) {
		beep("CActivityView::OnCreateActivity()");
		delete anActivity;
		return;
	}
	draw(anActivity);
	_currentFocus = (Figure *)anActivity;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CActivityView::OnCreateTrigger()
{
	collectActiveNodes(WEAREACTIVITYOBJECTS); 
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more activity objects.");
		return;
	}
	_whatTionToDraw = KTG_TRIGGER;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_TRIGGER);
}

void CActivityView::OnCreateSyncBar()
{
	GetDocument()->setModifiedFlag(); 
	SynchronizationBar *aBar = new SynchronizationBar(this,_popupX,_popupY,theAppPtr->theSynchronizationPopup);
	aBar->makeRegion(_canvasRgn);
	addExcludeRectForBottomObjects(aBar,figures());
	figures()->insert(aBar);
	draw(aBar);
}

void CActivityView::OnCreateBeginActivity()
{
	GetDocument()->setModifiedFlag(); 
	BeginActivity *anActivity = new BeginActivity(this,_popupX,_popupY,NIL);
	anActivity->makeRegion(_canvasRgn);
	addExcludeRectForBottomObjects(anActivity,figures());
	figures()->insert(anActivity);
	draw(anActivity);
}

void CActivityView::OnCreateEndActivity()
{
	GetDocument()->setModifiedFlag(); 
	EndActivity *anActivity = new EndActivity(this,_popupX,_popupY,NIL);
	anActivity->makeRegion(_canvasRgn);
	addExcludeRectForBottomObjects(anActivity,figures());
	figures()->insert(anActivity);
	draw(anActivity);
}

void CActivityView::OnGuardTrigger()
{
	if (_currentFocus == NIL) {
		beep("CActivityView::OnGuardTrigger()");
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMTRIGGER) == FALSE) {
		beep("CActivityView::OnGuardTrigger()");
		return;
	}
	lowlight(_currentFocus);
	_editingTag = TRUE;
	Trigger * thisTrigger = (Trigger *)_currentFocus;
	TriggerText *aText = thisTrigger->selectOrCreateText();
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	aText->startEdit();
	ktgF_processKeys = TRUE;
}

BOOL CActivityView::validWhatTionToDraw()
{
	if (_whatTionToDraw == KTG_TRIGGER) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void CActivityView::createNewConnection(CPoint point)
{
	lowlightDrawBoundary(_currentFocus);
	int x = point.x;
	int y = point.y;
	_currentX = x;
	_currentY = y;
	Line *aLine = new Line(this,x,y,NIL,STRAIGHT);
	aLine->setFollowing2(x,y);
	UINT commandID = 0;
	if (_whatTionToDraw == KTG_TRIGGER) {
		commandID = ID_TB_TRIGGER;
		_currentConnection = new Trigger(this,theAppPtr->theTriggerPopup,aLine);
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

void CActivityView::drawingEpilog()
{
	COODView::drawingEpilog();
}
/////////////////////////////////////////////////////////////////////////////
// CActivityView message handlers

void CActivityView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COODView::OnDraw(pDC);
	if (_currentConnection != NIL) {
		if (ktgF_connectionDrawing) {
			rubberbanding(_currentConnection);
		}
	}
}

void CActivityView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pSender == NULL) return;
	if (!pSender->IsKindOf(RUNTIME_CLASS(CActivityView))) return;
}

void CActivityView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonDblClk(nFlags, point);
		return;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CActivityView::OnLButtonDown(UINT nFlags, CPoint point) 
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
			case ID_TB_ACTIVITY:
				OnCreateActivity();
				break;
			case ID_TB_BEGIN_ACTIVITY:
				OnCreateBeginActivity();
				break;
			case ID_TB_END_ACTIVITY:
				OnCreateEndActivity();
				break;
			case ID_TB_SYNC_BAR:
				OnCreateSyncBar();
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
		} else if (_currentFocus->whoAreYou()->equals(IAMSYNCHRONIZATIONBAR) &&
			_currentFocus->focus() != NIL &&
			_currentFocus->focus()->whoAreYou()->equals(IAMSYNCCONDITIONTEXT)) {
			InfoMsg("Please drag from synchronization bar rather than condition.");
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
			beep("CActivityView::OnLButtonDown(UINT nFlags, CPoint point)");
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

void CActivityView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonUp(nFlags, point);
		return;
	} else {
		if (ktgF_connectionDrawing == FALSE) {
			// 다음 명령어 주의 : Sync Condition 선택과 관련 있음
			// 절대로 COODView::OnLButtonUp(nFlags, point); 로 바꾸지 말것
			CScrollView::OnLButtonUp(nFlags, point);
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
				_currentFocus->whoAreYou()->equals(IAMSYNCHRONIZATIONBAR) &&
				_currentFocus->focus() != NIL &&
				_currentFocus->focus()->whoAreYou()->equals(IAMSYNCCONDITIONTEXT)) {
				nodeFocus = NIL;
				stopFlag = FALSE;
			} else if (_currentFocus != NIL && 
				_currentFocus->whoAreYou()->isIn(WEAREACTIVITYOBJECTS)) {
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
				Invalidate();
			}
		}
	}	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CActivityView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CActivityView::OnTbTrigger() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_TRIGGER);
	if (itsMe) return;
	OnCreateTrigger(); 		
}

void CActivityView::OnTbActivity() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_ACTIVITY);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_ACTIVITY;
	pressModelTBButton(ID_TB_ACTIVITY);					
}

void CActivityView::OnTbBeginActivity() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_BEGIN_ACTIVITY);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_BEGIN_ACTIVITY;
	pressModelTBButton(ID_TB_BEGIN_ACTIVITY);					
}

void CActivityView::OnTbEndActivity() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_END_ACTIVITY);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_END_ACTIVITY;
	pressModelTBButton(ID_TB_END_ACTIVITY);					
}

void CActivityView::OnTbSyncBar() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_SYNC_BAR);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_SYNC_BAR;
	pressModelTBButton(ID_TB_SYNC_BAR);					
}

