// CUseCaseView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CUseCaseView.h"
#include "CMainFrame.h"
#include "Figures.h"
#include "LineNodeList.h"
#include "UnsignedLong.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CUseCaseView, COODView)
/////////////////////////////////////////////////////////////////////////////
// CUseCaseView

CUseCaseView::CUseCaseView()
: COODView()
{
}

CUseCaseView::~CUseCaseView()
{
}


BEGIN_MESSAGE_MAP(CUseCaseView, COODView)
	//{{AFX_MSG_MAP(CUseCaseView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TB_USECASE, OnTbUsecase)
	ON_COMMAND(ID_TB_USECASE_ASSOCIATES, OnTbUsecaseAssociates)
	ON_COMMAND(ID_TB_USECASE_EXTENDS, OnTbUsecaseExtends)
	ON_COMMAND(ID_TB_USECASE_SYSTEM, OnTbUsecaseSystem)
	ON_COMMAND(ID_TB_USECASE_USES, OnTbUsecaseUses)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CREATE_USECASE, CUseCaseView::OnCreateUseCase)
	ON_COMMAND(ID_CREATE_USECASELINK, CUseCaseView::OnCreateUseCaseLink)
	ON_COMMAND(ID_CREATE_USECASEUSESLINK, CUseCaseView::OnCreateUseCaseUsesLink)
	ON_COMMAND(ID_CREATE_USECASEEXTENDSLINK, CUseCaseView::OnCreateUseCaseExtendsLink)
	ON_COMMAND(ID_CREATE_SYSTEMBOUNDARY, CUseCaseView::OnCreateSystemBoundary)
END_MESSAGE_MAP()

void CUseCaseView::setPopups()
{
	_mainPopup = theAppPtr->theUseCaseMainPopup;
}

void CUseCaseView::OnCreateUseCase()
{
	UseCase *anUseCase = new UseCase(this,_popupX,_popupY,_fontHeight,NIL);
	anUseCase->setFocus();
	BOOL ok = anUseCase->startEdit();
	if (ok == FALSE) {
		beep("CUseCaseView::OnCreateUseCase()");
		delete anUseCase;
		return;
	}
	draw(anUseCase);
	_currentFocus = (Figure *)anUseCase;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CUseCaseView::OnCreateSystemBoundary()
{
	SystemBoundary *aSystem = new SystemBoundary(this,_popupX,_popupY,NIL);
	aSystem->setFocus();
	BOOL ok = aSystem->startEdit();
	if (ok == FALSE) {
		beep("CUseCaseView::OnCreateSystemBoundary()");
		delete aSystem;
		return;
	}
	draw(aSystem);
	_currentFocus = (Figure *)aSystem;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void CUseCaseView::OnCreateUseCaseLink()
{
	collectActiveNodes(WEAREUSECASEOBJECTS);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named use cases.");
		return;
	}
	_whatTionToDraw = KTG_USECASELINK;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_USECASE_ASSOCIATES);
}

void CUseCaseView::OnCreateUseCaseUsesLink()
{
	collectActiveNodes(IAMUSECASE);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named use cases.");
		return;
	}
	_whatTionToDraw = KTG_USECASEUSESLINK;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_USECASE_USES);
}

void CUseCaseView::OnCreateUseCaseExtendsLink()
{
	collectActiveNodes(IAMUSECASE);
	if (_activeNodes->nOfList() <= 1) {
		_activeNodes->clear();
		WarningMsg("You must have two or more named use cases.");
		return;
	}
	_whatTionToDraw = KTG_USECASEEXTENDSLINK;
	ktgF_connectionStartDraw = TRUE;
	pressModelTBButton(ID_TB_USECASE_EXTENDS);
}

BOOL CUseCaseView::validWhatTionToDraw()
{
	if (_whatTionToDraw == KTG_USECASELINK ||
		_whatTionToDraw == KTG_USECASEUSESLINK ||
		_whatTionToDraw == KTG_USECASEEXTENDSLINK) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void CUseCaseView::createNewConnection(CPoint point)
{
	lowlightDrawBoundary(_currentFocus);
	int x = point.x;
	int y = point.y;
	_currentX = x;
	_currentY = y;
	Line *aLine = new Line(this,x,y,NIL,ORDINARY);
	aLine->setFollowing2(x,y);
	UINT commandID = 0;
	if (_whatTionToDraw == KTG_USECASELINK) {
		commandID = ID_TB_USECASE_ASSOCIATES;
		_currentConnection = new UseCaseLink(this,NIL,aLine);
	} else if (_whatTionToDraw == KTG_USECASEUSESLINK) {
		commandID = ID_TB_USECASE_USES;
		_currentConnection = new UseCaseUsesLink(this,NIL,aLine);
	} else if (_whatTionToDraw == KTG_USECASEEXTENDSLINK) {
		commandID = ID_TB_USECASE_EXTENDS;
		_currentConnection = new UseCaseExtendsLink(this,NIL,aLine);
	}
	if (commandID != 0)
		releaseModelTBButton(commandID);
	EditableFigure *eNode = (EditableFigure *)_currentFocus;
	eNode->insert(_currentConnection);
	_currentConnection->insert(eNode);
	LineNode *node = _currentConnection->node(aLine);
	_currentConnection->activeLines()->insert(node);
}

void CUseCaseView::drawingEpilog()
{
	COODView::drawingEpilog();
}

/////////////////////////////////////////////////////////////////////////////
// CUseCaseView message handlers

void CUseCaseView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COODView::OnDraw(pDC);
	if (_currentConnection != NIL) {
		if (ktgF_connectionDrawing) {
			rubberbanding(_currentConnection);
		}
	}
}

void CUseCaseView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pSender == NULL) return;
	if (!pSender->IsKindOf(RUNTIME_CLASS(CUseCaseView))) return;
}

void CUseCaseView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (validWhatTionToDraw() == FALSE) {
		COODView::OnLButtonDblClk(nFlags, point);
		return;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CUseCaseView::OnLButtonDown(UINT nFlags, CPoint point) 
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
			case ID_TB_USECASE:
				OnCreateUseCase();
				break;
			case ID_TB_USECASE_SYSTEM:
				OnCreateSystemBoundary();
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
		/* 이 블럭은 거의 필요없음: 왜냐하면 Use Case 에서는 SimpleConnection 만 사용되기 때문에 */
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

void CUseCaseView::OnLButtonUp(UINT nFlags, CPoint point) 
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
			ktgF_connectionDrawing = FALSE;
			NodeFigure *nodeFocus;
			BOOL abortFlag;
			if (_currentFocus != NIL && 
				_currentFocus->whoAreYou()->isIn(WEAREUSECASEOBJECTS)) {
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
				} else {
					insert(_currentConnection);
				}
			}
			ktgF_connectionContinueDraw = FALSE;
			drawingEpilog();
			ReleaseCapture();
			Invalidate();
		}
	}	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CUseCaseView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CUseCaseView::OnTbUsecaseAssociates() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_USECASE_ASSOCIATES);
	if (itsMe) return;
	OnCreateUseCaseLink(); 	
}

void CUseCaseView::OnTbUsecaseExtends() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_USECASE_EXTENDS);
	if (itsMe) return;
	OnCreateUseCaseExtendsLink(); 	
}

void CUseCaseView::OnTbUsecaseUses() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_USECASE_USES);
	if (itsMe) return;
	OnCreateUseCaseUsesLink(); 	
}

/*
void CUseCaseView::OnTbActor() 
{
	// TODO: Add your command handler code here
// 이 함수는 COODView로 이사 갔음	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_ACTOR);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_ACTOR;
	pressModelTBButton(ID_TB_ACTOR);					
}
*/

void CUseCaseView::OnTbUsecase() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_USECASE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_USECASE;
	pressModelTBButton(ID_TB_USECASE);					
}

void CUseCaseView::OnTbUsecaseSystem() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_USECASE_SYSTEM);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_USECASE_SYSTEM;
	pressModelTBButton(ID_TB_USECASE_SYSTEM);					
}

