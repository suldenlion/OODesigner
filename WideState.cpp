// WideState.cpp: implementation of the WideState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "WideState.h"
#include "RoundBoxB.h"
#include "COODView.h"
#include "Text.h"
#include "FigureList.h"
#include "Connection.h"
#include "TextContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define INIT_WIDE_STATE_WIDTH	(400)
#define INIT_WIDE_STATE_HEIGHT (300)

#define NAME_TEXT_DX (10)
#define NAME_TEXT_DY (10)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(WideState,NodeFigure,1)

WideState::WideState()
: NodeFigure()
{
	_savedX1 = -1;
	_savedY1 = -1;
	_savedX2 = -1;
	_savedY2 = -1;
	_stateName = NIL;
	_nOfSeperators = 0;
}

WideState::WideState(COODView *controller,int ox,int oy,int nOfSeperators,Popup *popup)
: NodeFigure(controller)
{
	_popup = popup;
	_nOfSeperators = nOfSeperators;
	_savedX1 = -1;
	_savedY1 = -1;
	_savedX2 = -1;
	_savedY2 = -1;
	if (_nOfSeperators < 0) _nOfSeperators = 0;
	if (_nOfSeperators > 100) _nOfSeperators = 100;

	if (controller == NIL) return;
	_shape = new RoundBoxB(controller,ox,oy,
						ox+INIT_WIDE_STATE_WIDTH,
						oy+INIT_WIDE_STATE_HEIGHT,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	NodeFigure::setBackground(theAppPtr->shapeBackgroundColor);
	_stateName = new Text(controller,ox+NAME_TEXT_DX,oy+NAME_TEXT_DY,NIL);
	_stateName->setAutoDelete(FALSE);
	_stateName->setBoldFont(TRUE);
	_stateName->setMaxLines(2);
}

WideState::~WideState()
{
	if (_stateName != NIL) {
		delete _stateName;
		_stateName = NIL;
	}
}

void WideState::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _stateName;
		ar << (LONG) _nOfSeperators;
	} else {
		ar >> _stateName;
		ar >> (LONG &) _nOfSeperators;
	}
}

UnsignedLong* WideState::whoAreYou()
{
	return IAMWIDESTATE; 
}

Figure* WideState::born(Figure* ptr)
{
	WideState *copied;
	if (ptr == NIL) {
		copied = new WideState(NIL,0,0,0,NIL);
	} else {
		copied = (WideState *)ptr;
	}
	copied->_stateName = (Text *)_stateName->born(NIL);
	return (NodeFigure::born((Figure *)copied));
}

BOOL WideState::wantToResize(int& x,int& y)
{
	if (_shape->wantToResize(x,y)) {
		_savedX1 = _shape->_x1.x;
		_savedY1 = _shape->_y1.y;
		_savedX2 = _shape->_x2.x;
		_savedY2 = _shape->_y2.y;
		return TRUE;
	}
	_savedX1 = -1;
	_savedY1 = -1;
	_savedX2 = -1;
	_savedY2 = -1;
	_shape->resetHotXY();
	return FALSE;
}

void WideState::setInCanvas(BOOL flag)
{
	NodeFigure::setInCanvas(flag);
	_stateName->setInCanvas(flag);
}

void WideState::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	NodeFigure::draw(dcp);
	int mode = dcp->GetROP2();
	if (_stateName->isEmpty()) {
		if (mode != R2_NOTXORPEN) {
			drawSeparators(dcp);
		}
	} else if (mode != R2_NOTXORPEN) {
		COLORREF oldColor = dcp->SetBkColor(background());
		_stateName->draw(dcp);
		dcp->SetBkColor(oldColor);
		drawSeparators(dcp);
	}
}

void WideState::drawSeparators(CDC *dcp)
{
	if (_nOfSeperators <= 0) return;
	int x1 = _shape->getX1();
	int y1 = _shape->getY1();
	int x2 = _shape->getX2();
	int y2 = _shape->getY2();

	int deltaY = (y2-y1) / (_nOfSeperators+1);
	int remainder = (y2-y1) - deltaY*(_nOfSeperators+1);
	if (remainder == 0) remainder = 1;
	int intervalToMorePoint = _nOfSeperators / remainder;
	int yBase = y1;

	for (int i = 0; i < _nOfSeperators; i++) {
		if (i == 0) {
			yBase = yBase + deltaY;
		} else if (i/intervalToMorePoint*intervalToMorePoint == i) {
			yBase = yBase + deltaY + 1;
		} else {
			yBase = yBase + deltaY;
		}
		DrawLine(dcp,x1,yBase,x2,yBase,1,DOTED);
	}
}

void WideState::drawBoundary(CDC* dcp)
{
	NodeFigure::drawBoundary(dcp);
}

void WideState::move(CDC* dcp,int dx,int dy)
{
	NodeFigure::move(dcp,dx,dy);
	_stateName->moveCoord(dx,dy);
}

void WideState::moveCoord(int dx,int dy)
{
	NodeFigure::moveCoord(dx,dy);
	_stateName->moveCoord(dx,dy);
}

void WideState::setController(COODView *ptr)
{
	NodeFigure::setController(ptr);
	_stateName->setController(ptr);
}

BOOL WideState::startEdit()
{
	_focus = _stateName;
	_stateName->startEdit();
	return TRUE;
}

void WideState::bye()
{
	if (_focus == NIL) return;
	_stateName->bye();
	return;
}

void WideState::epilog(BOOL skipflag)
{
	if (_savedX2 == -1 && _savedY2 == -1) {
		NodeFigure::epilog(skipflag);
		_shape->arrangeXY12();
		_stateName->recalcCoordFromXY1(_shape->getX1()+NAME_TEXT_DX,
									_shape->getY1()+NAME_TEXT_DY);
		return;
	}
	if (_shape->hotX() == NIL || _shape->hotY() == NIL) {
		NodeFigure::epilog(skipflag);
		_shape->arrangeXY12();
		_stateName->recalcCoordFromXY1(_shape->getX1()+NAME_TEXT_DX,
									_shape->getY1()+NAME_TEXT_DY);
		return;
	}
	int nameW = _stateName->content()->otherLinesMaxWidth();
	int limitX = _savedX1 + nameW + 4;
	int limitY = _savedY1 + 20;
	int lastX = _shape->hotX()->x;
	int lastY = _shape->hotY()->y;
	if (lastX < limitX ||
		lastY < limitY) {
		_controller->beep("Resizing aborted.");
		_shape->_x1.x = _savedX1;
		_shape->_y1.y = _savedY1;
		_shape->_x2.x = _savedX2;
		_shape->_y2.y = _savedY2;
		_savedX1 = -1;
		_savedY1 = -1;
		_savedX2 = -1;
		_savedY2 = -1;
		_controller->Invalidate();
		return;
	}
	_savedX1 = -1;
	_savedY1 = -1;
	_savedX2 = -1;
	_savedY2 = -1;
	makeRegion(_controller->canvasRgn());
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->extendToNodeFigure(this);
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->tailorEndLinesAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setModelSpecificSymbolAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->makeRegion(_controller->canvasRgn());
		ptr = _connections->getNext();
	}
	_controller->Invalidate();
}
