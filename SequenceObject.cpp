// SequenceObject.cpp: implementation of the SequenceObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SequenceObject.h"
#include "ObjectText.h"
#include "SlaveryTextList.h"
#include "FigureList.h"
#include "COODView.h"
#include "Line.h"
#include "LineNode.h"
#include "LineNodeList.h"
#include "ActivationBarList.h"
#include "ActivationBar.h"
#include "UnsignedLong.h"
#include "ConnectionList.h"
#include "Connection.h"
#include "SimpleConnection.h"
#include "Popup.h"
#include "SequenceSelfDelegation.h"

#define DEAULT_LANE_LENGTH		(300)
#define GRAY_RGB				(RGB(200,200,200))

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SequenceObject,EditableFigure,1)

SequenceObject::SequenceObject()
: EditableFigure()
{
	_popup = theAppPtr->theSequenceObjectPopup;

	_hiddenFocus = NIL;
	_activationBars = NIL;
	_lifeLane = NIL;
	_killSignFlag = FALSE;
	_resizeUpperBound = 0;
	_resizeLowerBound = 0;
	_canDoKillSign = FALSE;
}

SequenceObject::SequenceObject(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	_hiddenFocus = NIL;
	_activationBars = NIL;
	_lifeLane = NIL;
	_killSignFlag = FALSE;
	_canDoKillSign = FALSE;
	if (controller == NIL) return;
	_popup = popup;
	_initWidth = SEQUENCE_OBJECT_INIT_WIDTH;
	_gapX = XGAP_SEQUENCE_OBJECT;
	_gapY = YGAP_SEQUENCE_OBJECT;
	_shape = new Box(controller,ox,oy,ox+_initWidth,oy+2*_gapY+deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	EditableFigure::setBackground(theAppPtr->shapeBackgroundColor);
	_texts->insert(new ObjectText(controller,this,IAMOBJECTNAME,ox+_gapX,oy+_gapY));
	int laneOx = ox+_initWidth/2;
	int laneOy = oy+2*_gapY+deltaV;
	Popup *lanePopup = theAppPtr->theSequenceLanePopup;
	_lifeLane = new Line(controller,laneOx,laneOy,laneOx,laneOy+DEAULT_LANE_LENGTH,lanePopup,STRAIGHT);
	_lifeLane->setOrient(NORTH);
	_lifeLane->style() = DASHED;
	_activationBars = new ActivationBarList();
}

SequenceObject::~SequenceObject()
{
	_hiddenFocus = NIL;
	if (_lifeLane != NIL) {
		delete _lifeLane; _lifeLane = NIL;
	}
	if (_activationBars != NIL) {
		ActivationBar *anActivationBar = _activationBars->getFirst();
		while (anActivationBar != NIL) {
			delete anActivationBar;
			anActivationBar = _activationBars->getNext();
		}
		_activationBars->clear();
		delete _activationBars; _activationBars = NIL;
	}
}

void SequenceObject::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _resizeUpperBound << (LONG) _resizeLowerBound;
		ar << (BYTE) _killSignFlag;
		ar << _activationBars << _lifeLane;
	} else {
		ar >> (LONG&) _resizeUpperBound >> (LONG&) _resizeLowerBound;
		ar >> (BYTE&) _killSignFlag;
		ar >> _activationBars >> _lifeLane;
		if (_lifeLane != NIL) 
			_lifeLane->setPopupPointer(theAppPtr->theSequenceLanePopup);
	}
	_lifeLane->style() = DASHED;  // 이 줄은 2005년도에는 없애도록 할 것
}

SequenceSelfDelegation * SequenceObject::createSelfDelegation(COODView *controller,int ox,int oy,Popup *popup)
{
	int startX = _lifeLane->getX1();
	int startY = oy;
	SequenceSelfDelegation * aSelfDelegation =
		new SequenceSelfDelegation(controller,this,startX,startY,popup);
	if (aSelfDelegation == NIL) return NIL;
	_connections->insert(aSelfDelegation);
	aSelfDelegation->tailorEndLinesAll();
	return aSelfDelegation;
}

UnsignedLong* SequenceObject::whoAreYou()
{
	return IAMSEQUENCEOBJECT; 
}

Figure* SequenceObject::born(Figure* ptr)
{
	SequenceObject *copied;
	if (ptr == NIL) {
		copied = new SequenceObject(NIL,0,0,0,NIL);
	} else {
		copied = (SequenceObject *)ptr;
	}
	copied->_lifeLane = (Line *)_lifeLane->born();
	copied->_killSignFlag = _killSignFlag;
	return (EditableFigure::born((Figure *)copied));
}

BOOL SequenceObject::containedWithin(int x1,int y1,int x2,int y2)
{
	BOOL val = _shape->containedWithin(x1,y1,x2,y2);
	if (val == FALSE) return FALSE;
	return _lifeLane->containedWithin(x1,y1,x2,y2);
}

void SequenceObject::processKillSign()
{
	if (_killSignFlag) {
		_killSignFlag = FALSE;
	} else {
		ActivationBar *lastBar = _activationBars->getLast();
		if (lastBar == NIL) return;
		int barY2 = lastBar->getY2();
		int laneY2 = _lifeLane->getY2();
		if (barY2+ACTIVATION_BAR_WIDTH > laneY2) {
			_lifeLane->_y2.set(barY2+ACTIVATION_BAR_WIDTH+1);
		}
		_killSignFlag = TRUE;
	}
}

void SequenceObject::clear(CDC *dcp)
{
	EditableFigure::clear(dcp);
	_lifeLane->clear(dcp);

	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->clear(dcp);
		anActivationBar = _activationBars->getNext();
	}
}

void SequenceObject::setController(COODView *ptr)
{
	EditableFigure::setController(ptr);
	_lifeLane->setController(ptr);
	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->setController(ptr);
		anActivationBar = _activationBars->getNext();
	}
}

void SequenceObject::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(clip(dcp),RGN_COPY);
		excludeRects(dcp);
	}
	EditableFigure::draw(dcp);
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(NULL,RGN_COPY);
	}
	_lifeLane->draw(dcp);

	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->draw(dcp);
		anActivationBar = _activationBars->getNext();
	}
	if (_killSignFlag) {
		drawKillSign(dcp);
	}

	mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) return;
	ConnectionList *copiedList = new ConnectionList();
	copiedList->copy(_connections);
	Connection *aConnection = copiedList->getFirst();
	while (aConnection != NIL) {
		if (aConnection->whoAreYou()->equals(IAMSEQUENCESELFDELEGATION) &&
			_controller->ktgF_simpleMoving == FALSE) 
			aConnection->drawBoundary(dcp);
		aConnection = copiedList->getNext();
	}
	delete copiedList;
}

void SequenceObject::drawOnMetaFile(CDC *dcp)
{
	if (!_inCanvas) return;

	EditableFigure::drawOnMetaFile(dcp);

	_lifeLane->drawOnMetaFile(dcp);

	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->drawOnMetaFile(dcp);
		anActivationBar = _activationBars->getNext();
	}
	if (_killSignFlag) {
		drawKillSign(dcp);
	}

	ConnectionList *copiedList = new ConnectionList();
	copiedList->copy(_connections);
	Connection *aConnection = copiedList->getFirst();
	while (aConnection != NIL) {
		if (aConnection->whoAreYou()->equals(IAMSEQUENCESELFDELEGATION)) 
			aConnection->drawOnMetaFile(dcp);
		aConnection = copiedList->getNext();
	}
	delete copiedList;
}

void SequenceObject::drawKillSign(CDC *dcp)
{
	ActivationBar *anActivationBar = _activationBars->getLast();
	if (anActivationBar == NIL) return;
	int sx = anActivationBar->getX1();
	int sy = anActivationBar->getY2();
	Figure::DrawLine(dcp,sx,sy,
		sx+2*ACTIVATION_BAR_WIDTH+1,sy+2*ACTIVATION_BAR_WIDTH+1,1);
	Figure::DrawLine(dcp,sx,sy+2*ACTIVATION_BAR_WIDTH,
		sx+2*ACTIVATION_BAR_WIDTH,sy,1);
}

void SequenceObject::showBaseLine(CDC *dcp,int baseY)
{
	CPen grayPen1(PS_SOLID,1,GRAY_RGB);
	CPen *oldPen = dcp->SelectObject(&grayPen1);
	Figure::DrawLine(dcp,0,baseY,_controller->width(),baseY);
	dcp->SelectObject(oldPen);
}

void SequenceObject::drawing(CDC *dcp,int dx,int dy)
{
	if (_hiddenFocus == _lifeLane) {
		if (_lifeLane->getY2()+dy < _resizeUpperBound) return;

		showBaseLine(dcp,_lifeLane->getY2());

		_lifeLane->drawing(dcp,0,dy);

		showBaseLine(dcp,_lifeLane->getY2());
	} else if (_hiddenFocus != NIL &&
		_hiddenFocus->whoAreYou()->equals(IAMACTIVATIONBAR)) {
		ActivationBar *aBar = (ActivationBar *)_hiddenFocus;
		if (aBar->hotY()->get()+dy < _resizeUpperBound) return;
		if (aBar->hotY()->get()+dy > _resizeLowerBound) return;
		if (aBar->hotY() != NIL) {
			showBaseLine(dcp,aBar->hotY()->get());
		}
		if (aBar == _activationBars->getLast() &&
			_killSignFlag) {
			drawKillSign(dcp);
		}
		aBar->drawing(dcp,0,dy);
		if (aBar->hotY() != NIL) {
			showBaseLine(dcp,aBar->hotY()->get());
		}
		if (aBar == _activationBars->getLast() &&
			_killSignFlag) {
			drawKillSign(dcp);
		}
	}
}

void SequenceObject::drawBoundary(CDC *dcp)
{
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) {
		showBaseLine(dcp,getY1());
		showBaseLine(dcp,_lifeLane->getY2());
		if (_hiddenFocus != NIL &&
			_hiddenFocus->whoAreYou()->equals(IAMACTIVATIONBAR)) {
			ActivationBar *aBar = (ActivationBar *)_hiddenFocus;
			showBaseLine(dcp,aBar->getY1());
			showBaseLine(dcp,aBar->getY2());
		}
	}
	EditableFigure::drawBoundary(dcp);
	if (_killSignFlag) {
		drawKillSign(dcp);
	}
	_lifeLane->drawBoundary(dcp);

	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->drawBoundary(dcp);
		anActivationBar = _activationBars->getNext();
	}

	mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) return;
	ConnectionList *copiedList = new ConnectionList();
	copiedList->copy(_connections);
	Connection *aConnection = copiedList->getFirst();
	while (aConnection != NIL) {
		if (aConnection->whoAreYou()->equals(IAMSEQUENCESELFDELEGATION) &&
			_controller->ktgF_simpleMoving == FALSE) 
			aConnection->drawBoundary(dcp);
		aConnection = copiedList->getNext();
	}
	delete copiedList;
}

void SequenceObject::move(CDC *dcp,int dx,int dy)
{
	if (_hiddenFocus == _lifeLane) return;
	if (_hiddenFocus != NIL &&
		_hiddenFocus->whoAreYou()->equals(IAMACTIVATIONBAR)) {
		ActivationBar *aBar = (ActivationBar *)_hiddenFocus;
		if (aBar->getY1() + dy < _resizeUpperBound) return;
		if (aBar->getY2() + dy > _resizeLowerBound) return;
		showBaseLine(dcp,aBar->getY1());
		showBaseLine(dcp,aBar->getY2());
		if (aBar == _activationBars->getLast() &&
			_killSignFlag) {
			drawKillSign(dcp);
		}

		aBar->move(dcp,0,dy);

		Connection *ptr = _connections->getFirst();
		while (ptr != NIL) {
			ptr->comeOn(dcp,0,dy);
			ptr = _connections->getNext();
		}

		showBaseLine(dcp,aBar->getY1());
		showBaseLine(dcp,aBar->getY2());
		if (aBar == _activationBars->getLast() &&
			_killSignFlag) {
			drawKillSign(dcp);
		}
		return;
	}
	showBaseLine(dcp,getY1());
	showBaseLine(dcp,_lifeLane->getY2());
	if (_killSignFlag) {
		drawKillSign(dcp);
	}

	EditableFigure::move(dcp,dx,dy);

	_lifeLane->move(dcp,dx,dy);

	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->move(dcp,dx,dy);
		anActivationBar = _activationBars->getNext();
	}

	if (_killSignFlag) {
		drawKillSign(dcp);
	}
	showBaseLine(dcp,getY1());
	showBaseLine(dcp,_lifeLane->getY2());
}

void SequenceObject::moveCoordForScroll(int dx,int dy)
{
	EditableFigure::moveCoordForScroll(dx,dy);
	_lifeLane->moveCoordForScroll(dx,dy);
	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->moveCoordForScroll(dx,dy);
		anActivationBar = _activationBars->getNext();
	}
}

void SequenceObject::bye()
{
	EditableFigure::bye();
	int laneX1 = _lifeLane->getX1();
	int laneY1 = _lifeLane->getY1();
	int baseX = (_shape->getX1() + _shape->getX2()) / 2;
	int baseY = _shape->getY2();
	if (laneX1 != baseX || laneY1 != baseY) {
		int dx = baseX - laneX1;
		int dy = baseY - laneY1;
		_controller->clear(_lifeLane);
		_lifeLane->moveCoord(0,dy);
		_lifeLane->moveCoord(dx,0);
		ActivationBar *anActivationBar = _activationBars->getFirst();
		while (anActivationBar != NIL) {
			_controller->clear(anActivationBar);
			anActivationBar->moveCoord(dx,dy);
			anActivationBar = _activationBars->getNext();
		}
		Connection *aConnection = _connections->getFirst();
		while (aConnection != NIL) {
			if (aConnection->whoAreYou()->isIn(WEARESIMPLECONNECTIONS)) {
				SimpleConnection *connection = (SimpleConnection *)aConnection;
				if (connection->amISource(this) == TRUE) {
					Line *aLine = connection->lines()->getFirst()->line();
					if (aLine != NIL) {
						int x = aLine->getX1() + dx;
						int y = aLine->getY1() + dy;
						aLine->_x1.set(x);
						aLine->_y1.set(y);
					}
				} else if (connection->amISink(this) == TRUE) {
					Line *aLine = connection->lines()->getFirst()->line();
					if (aLine != NIL) {
						int x = aLine->getX2() + dx;
						int y = aLine->getY2() + dy;
						aLine->_x2.set(x);
						aLine->_y2.set(y);
					}
				}
			} else if (aConnection->whoAreYou()->equals(IAMSEQUENCESELFDELEGATION)) {
				aConnection->moveCoord(dx,dy);
			}
			aConnection->makeRegion(_controller->canvasRgn());
			aConnection = _connections->getNext();
		}
		makeRegion(_controller->canvasRgn());
		_controller->Invalidate();
	}
}

void SequenceObject::drawDots(CDC* dcp)
{
	if (_focus != NIL) {
		_focus->drawDots(dcp);
		return;
	}
	EditableFigure::drawDots(dcp);
}

void SequenceObject::eraseDots(CDC* dcp)
{
	if (_focus != NIL) {
		_focus->eraseDots(dcp);
		_focus = NIL;
		return;
	}
	EditableFigure::eraseDots(dcp);
}

BOOL SequenceObject::onEnter(int x,int y)
{
	_focus = NIL;
	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		if (anActivationBar->onEnter(x,y)) {
			_focus = anActivationBar;
			_hiddenFocus = anActivationBar;
			char buffer[BUFSIZ];
			if (getName(buffer,BUFSIZ) < BUFSIZ) {
				if (strlen(buffer) == 0) {
					strcpy_s(buffer,BUFSIZ,"Null");
				}
				_controller->userMsgForUsingUpperCaseAsBlank("Object : ",buffer);
			}
			return TRUE;
		}
		anActivationBar = _activationBars->getNext();
	}
	if (_lifeLane->onEnter(x,y)) {
		_focus = _lifeLane;
		_hiddenFocus = _lifeLane;
		char buffer[BUFSIZ];
		if (getName(buffer,BUFSIZ) < BUFSIZ) {
			if (strlen(buffer) == 0) {
				strcpy_s(buffer,BUFSIZ,"Null");
			}
			_controller->userMsgForUsingUpperCaseAsBlank("Object : ",buffer);
		}
		return TRUE;
	}
	BOOL retVal = EditableFigure::onEnter(x,y);
	_hiddenFocus = _focus;
	return retVal;
}

void SequenceObject::makeRegion(CRgn *sourceClipRgn)
{
	EditableFigure::makeRegion(sourceClipRgn);
	_lifeLane->makeRegion(sourceClipRgn);
	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->makeRegion(sourceClipRgn);
		anActivationBar = _activationBars->getNext();
	}
}

void SequenceObject::resetRegion()
{
	EditableFigure::resetRegion();
	_lifeLane->resetRegion();
	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->resetRegion();
		anActivationBar = _activationBars->getNext();
	}
}

void SequenceObject::releaseRegion()
{
	EditableFigure::releaseRegion();
	_lifeLane->releaseRegion();
	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		anActivationBar->releaseRegion();
		anActivationBar = _activationBars->getNext();
	}
}

void SequenceObject::setResizeUpperBound()
{
	if (_hiddenFocus == _lifeLane) {
		_resizeUpperBound = _shape->getY2()+1;
		Connection *aConnection = _connections->getFirst();
		while (aConnection != NIL) {
			if (aConnection->amISource(this) == TRUE) {
				Line *aLine = aConnection->lines()->getFirst()->line();
				if (aLine != NIL) {
					int y = aLine->getY1();
					if (y > _resizeUpperBound) {
						_resizeUpperBound = y + 1;
					}
				}
			}
			if (aConnection->amISink(this) == TRUE) {
				Line *aLine = aConnection->lines()->getLast()->line();
				if (aLine != NIL) {
					int y = aLine->getY2();
					if (y > _resizeUpperBound) {
						_resizeUpperBound = y + 1;
					}
				}
			}
			aConnection = _connections->getNext();
		}
		ActivationBar *aBar = _activationBars->getLast();
		if (aBar == NIL) return;
		if (aBar->getY2() > _resizeUpperBound) {
			_resizeUpperBound = aBar->getY2()+1;
			if (_killSignFlag) {
				_resizeUpperBound = _resizeUpperBound + ACTIVATION_BAR_WIDTH;
			}
		}
	}
}

void SequenceObject::setResizeBoundsForActivation(ActivationBar *thisBar)
{
	_resizeUpperBound = _lifeLane->getY1() + 1;
	if (_killSignFlag) {
		_resizeLowerBound = _lifeLane->getY2() - ACTIVATION_BAR_WIDTH;
	} else {
		_resizeLowerBound = _lifeLane->getY2() - 1;
	}
	int yBase = thisBar->hotY()->get();
	if (thisBar->hotY() == &(thisBar->_y1)) {
		ActivationBar *aBar = _activationBars->getLast();
		while(aBar != NIL) {
			if (aBar->getY2() < yBase) {
				_resizeUpperBound = aBar->getY2() + 1;
				break;
			}
			aBar = _activationBars->getBack();
		}
		_resizeLowerBound = thisBar->getY2() - 1;
	} else if (thisBar->hotY() == &(thisBar->_y2)) {
		ActivationBar *aBar = _activationBars->getFirst();
		while(aBar != NIL) {
			if (aBar->getY1() > yBase) {
				_resizeLowerBound = aBar->getY1() - 1;
				break;
			}
			aBar = _activationBars->getNext();
		}
		_resizeUpperBound = thisBar->getY1() + 1;
	}
}

void SequenceObject::setMoveBoundsForActivation(ActivationBar *thisBar)
{
	_resizeUpperBound = _lifeLane->getY1() + 1;
	if (_killSignFlag) {
		_resizeLowerBound = _lifeLane->getY2() - ACTIVATION_BAR_WIDTH;
	} else {
		_resizeLowerBound = _lifeLane->getY2() - 1;
	}
	int yBase = thisBar->getY1();
	ActivationBar *aBar = _activationBars->getLast();
	while(aBar != NIL) {
		if (aBar->getY2() < yBase) {
			_resizeUpperBound = aBar->getY2() + 1;
			break;
		}
		aBar = _activationBars->getBack();
	}
	yBase = thisBar->getY2();
	aBar = _activationBars->getFirst();
	while(aBar != NIL) {
		if (aBar->getY1() > yBase) {
			_resizeLowerBound = aBar->getY1() - 1;
			break;
		}
		aBar = _activationBars->getNext();
	}
}

BOOL SequenceObject::wantToResize(int& x,int& y)
{
	int x2 = _lifeLane->getX2();
	int y2 = _lifeLane->getY2();
	_hiddenFocus = NIL;
	_resizeUpperBound = -1;
	_resizeLowerBound = -1;
	ActivationBar *anActivationBar = _activationBars->getFirst();
	while (anActivationBar != NIL) {
		if (anActivationBar->wantToResize(x,y)) {
			_hiddenFocus = anActivationBar;
			setResizeBoundsForActivation(anActivationBar);
			return TRUE;
		}
		anActivationBar = _activationBars->getNext();
	}
	if (TwoPointFigure::wantToResize(x,y,x2,y2)) {
		_hiddenFocus = _lifeLane;
		_lifeLane->wantToResizeExact(x2,y2);
		x = x2; y = y2;
		setResizeUpperBound();
		return TRUE;
	}
	return FALSE;
}

void SequenceObject::epilog(BOOL skipflag)
{
	EditableFigure::epilog(skipflag);
	if (skipflag) return;
	_hiddenFocus = NIL;
	_controller->Invalidate();
}

BOOL SequenceObject::checkInRegion(CRgn* rgn)
{
	if (EditableFigure::checkInRegion(rgn)) return TRUE;
	if (_lifeLane->checkInRegion(rgn)) return TRUE;
	return FALSE;
}

void SequenceObject::popup(CPoint* event,BOOL)
{
	if (_focus != NIL && _focus->popupPointer() != NIL) {
		if (_focus->whoAreYou()->equals(IAMACTIVATIONBAR)) {
			ActivationBar *aBar = _activationBars->getLast();
			if (_focus == aBar) {
				_canDoKillSign = TRUE;
			} else {
				_canDoKillSign = FALSE;
			}
		}
		_focus->popup(event);
		return;
	}
	Figure::popup(event);
}

int SequenceObject::getNewActivationBarHeight(int topY)
{
	int bottomY = _lifeLane->getY2();
	ActivationBar *aBar = _activationBars->getLast();
	while(aBar != NIL) {
		if (topY < aBar->getY1()) {
			bottomY = aBar->getY1();
		} else {
			break;
		}
		aBar = _activationBars->getBack();
	}
	return (bottomY-topY)/2;
}

void SequenceObject::makeNewActivationBar(int x,int y)
{
	int cx = _lifeLane->getX1();
	int h = getNewActivationBarHeight(y);

	ActivationBar *aBar = new ActivationBar(_controller,
		cx-ACTIVATION_BAR_WIDTH,y,
		cx+ACTIVATION_BAR_WIDTH,y+h,theAppPtr->theActivationBarPopup);
	_activationBars->insert(aBar);

	Connection *aConnection = _connections->getFirst();
	while (aConnection != NIL) {
		aConnection->tailorEndLinesAll();
		aConnection = _connections->getNext();
	}
	_controller->Invalidate();
}

BOOL SequenceObject::moveProlog(BOOL moveAllFlag)
{
	EditableFigure::moveProlog(moveAllFlag);
	if (moveAllFlag) {
		return TRUE;
	}
	if (_hiddenFocus != NIL &&
		_hiddenFocus->whoAreYou()->equals(IAMACTIVATIONBAR)) {
		ActivationBar *aBar = (ActivationBar *)_hiddenFocus;
		setMoveBoundsForActivation(aBar);

		int n = _connections->nOfList();
		if (n > 0) {
			int boxY1 = aBar->getY1();
			int boxY2 = aBar->getY2();
			Connection *ptr = _connections->getFirst();
			while (ptr != NIL) {
				ptr->resetHotXY();
				ptr = _connections->getNext();
			}
			ptr = _connections->getFirst();
			while (ptr != NIL) {
				Line * aLine = ptr->lines()->getFirst()->line();
				int x1 = aLine->getX1();
				int y1 = aLine->getY1();
				int x2 = aLine->getX2();
				int y2 = aLine->getY2();

				if (ptr->whoAreYou()->equals(IAMSEQUENCESELFDELEGATION) == FALSE &&
					ptr->amISource(this) &&
					y1 <= boxY2 &&
					y1 >= boxY1) {
					ptr->letsGo(this);
				} else if (ptr->whoAreYou()->equals(IAMSEQUENCESELFDELEGATION) == FALSE &&
					ptr->amISink(this) &&
					y2 <= boxY2 &&
					y2 >= boxY1) {
					ptr->letsGo(this);
				}
				ptr = _connections->getNext();
			}
		}
	}
	return FALSE;
}

void SequenceObject::deleteFocusObject()
{
	if (_focus == NIL) return;
	if (_focus->whoAreYou()->equals(IAMACTIVATIONBAR) == FALSE) return;
	if (_activationBars->inList((ActivationBar *)_focus) == FALSE) return;
//	_controller->lowlight(_focus);
//	_controller->clear(_focus);
	_activationBars->remove((ActivationBar *)_focus);
	_hiddenFocus = NIL;
	delete _focus; _focus = NIL;
	Connection *aConnection = _connections->getFirst();
	while (aConnection != NIL) {
		aConnection->tailorEndLinesAll();
		aConnection = _connections->getNext();
	}
}

BOOL SequenceObject::adjustLine(Line *line,BOOL startPoint)
{
	int cx = _lifeLane->getX1();
	int x1 = line->getX1();
	int y1 = line->getY1();
	int x2 = line->getX2();
	int y2 = line->getY2();
	if (_shape != NIL) {
		if (startPoint == TRUE && _shape->contains(x1,y1)) {
			return _shape->adjustLine(line,startPoint);
		} else if (startPoint == FALSE && _shape->contains(x2,y2)) {
			return _shape->adjustLine(line,startPoint);
		}
	}
	ActivationBar *aBar = _activationBars->getFirst();
	while(aBar != NIL) {
		if (startPoint == TRUE && aBar->contains(x1,y1)) {
			return aBar->adjustLine(line,startPoint);
		} else if (startPoint == FALSE && aBar->contains(x2,y2)) {
			return aBar->adjustLine(line,startPoint);
		}
		aBar = _activationBars->getNext();
	}
	if (startPoint == TRUE) {
		line->_x1.set(cx);
	} else if (startPoint == FALSE) { 
		line->_x2.set(cx);
	}
	// 작은 바 때문에 다시 한번 ...
	x2 = line->getX2();
	y2 = line->getY2();
	aBar = _activationBars->getFirst();
	while(aBar != NIL) {
		if (startPoint == FALSE && aBar->contains(x2,y2)) {
			return aBar->adjustLine(line,startPoint);
		}
		aBar = _activationBars->getNext();
	}
	return FALSE;
}

void SequenceObject::setBackground(COLORREF c)
{
	EditableFigure::setBackground(c);
	ActivationBar *aBar = _activationBars->getFirst();
	while(aBar != NIL) {
		aBar->setBackground(c);
		aBar = _activationBars->getNext();
	}
}

