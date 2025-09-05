// SynchronizationBar.cpp: implementation of the SynchronizationBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SynchronizationBar.h"
#include "Line.h"
#include "SyncConditionText.h"
#include "COODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SynchronizationBar,NodeFigure,1)

SynchronizationBar::SynchronizationBar()
: NodeFigure()
{
	_popup = theAppPtr->theSynchronizationPopup;
	_conditionText = NIL;
}

SynchronizationBar::SynchronizationBar(COODView *controller,int x,int y,Popup* popup)
: NodeFigure(controller)
{
	_popup = popup;
	_conditionText = NIL;
	if (controller == NIL) return;
	Line *aBar = new Line(controller,
						x-INIT_SYNC_BAR_WIDTH/2,y,
						x+INIT_SYNC_BAR_WIDTH/2,y,
						NIL,STRAIGHT);
	aBar->setThickness(SYNC_BAR_THICKNESS);
	aBar->setOrient();
	_shape = aBar;
	int cx,cy;
	int x2,y2;
	aBar->center(cx,cy);
	aBar->last(x2,y2);
	_conditionText = new SyncConditionText(controller,this,
					x2+CONDITION_DX_FROM_X2,
					cy-controller->fontHeight()/2,NIL);
	_conditionText->setAutoDelete(FALSE);
	_conditionText->makeRegion(_controller->canvasRgn());
}

SynchronizationBar::~SynchronizationBar()
{
	if (_conditionText != NIL) {
		delete _conditionText; _conditionText = NIL;
	}
}

void SynchronizationBar::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _conditionText;
	} else {
		ar >> _conditionText;
	}
}

UnsignedLong* SynchronizationBar::whoAreYou()
{
	return IAMSYNCHRONIZATIONBAR; 
}

BOOL SynchronizationBar::adjustLine(Line *line,BOOL startPoint)
{
	int cy = _shape->getY1();
	int x1 = line->getX1();
	int y1 = line->getY1();
	int x2 = line->getX2();
	int y2 = line->getY2();
	Line *bar = (Line *)_shape;
	if (bar->incl(x1,y1) && bar->incl(x2,y2)) {
		return TRUE;
	}
	int orient = line->orient();
	if (orient == EAST) {
		if (bar->incl(x1,y1) && x1 < x2) {
			line->_x1.set(_shape->getX2());
		} else if (bar->incl(x1,y1) && x1 > x2) {
			line->_x1.set(_shape->getX1());
		} else if (bar->incl(x2,y2) && x1 < x2) {
			line->_x2.set(_shape->getX1());
		} else if (bar->incl(x2,y2) && x1 > x2) {
			line->_x2.set(_shape->getX2());
		}
	} else if (startPoint == TRUE && orient == NORTH) {
		line->_y1.set(cy);
	} else if (startPoint == FALSE && orient == NORTH) { 
		line->_y2.set(cy);
	}
	return FALSE;
}

Figure* SynchronizationBar::born(Figure* ptr)
{
	SynchronizationBar *copied;
	if (ptr == NIL) {
		copied = new SynchronizationBar(NIL,0,0,NIL);
	} else {
		copied = (SynchronizationBar *)ptr;
	}
	copied->_conditionText = (SyncConditionText *)_conditionText->born();
	return (NodeFigure::born((Figure *)copied));
}

BOOL SynchronizationBar::startEdit()
{
	_focus = _conditionText;
	_conditionText->startEdit();
	return TRUE;
}

void SynchronizationBar::bye()
{
	if (_focus == NIL) return;
	_conditionText->bye();
	_controller->clear(_conditionText);
	int x1 = _conditionText->getX1();
	int y1 = _conditionText->getY1();
	int x2 = _conditionText->getX2();
	int y2 = _conditionText->getY2();
	int height = y2-y1;
	int newX1 = _shape->getX2() + CONDITION_DX_FROM_X2;
	int newY1 = _shape->getY2() - height/2;
	_conditionText->recalcCoordFromXY1(newX1,newY1);
	_controller->draw(_conditionText);
	return;
}

void SynchronizationBar::clear(CDC* dcp)
{
	NodeFigure::clear(dcp);
	if (_conditionText->isEmpty() == FALSE) {
		_conditionText->clear(dcp);
	}
}

void SynchronizationBar::eraseDots(CDC* dcp)
{
	NodeFigure::eraseDots(dcp);
	if (_conditionText->isEmpty() == FALSE) {
		_conditionText->eraseDots(dcp);
	}
}

void SynchronizationBar::drawDots(CDC* dcp)
{
	NodeFigure::drawDots(dcp);
	if (_conditionText->isEmpty() == FALSE) {
		_conditionText->drawDots(dcp);
	}
}

void SynchronizationBar::setFocus(int x,int y)
{
	NodeFigure::setFocus(x,y);
	_conditionText->setXY(x,y);
}

BOOL SynchronizationBar::onEnter(int x,int y)
{
	if (_conditionText->isEmpty() == FALSE &&
		_conditionText->onEnter(x,y)) {
		_focus = _conditionText;
		return TRUE;
	}
	return NodeFigure::onEnter(x,y);
}

void SynchronizationBar::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	NodeFigure::draw(dcp);
	if (_conditionText->isEmpty()) return; 
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		_conditionText->draw(dcp);
	}
}

void SynchronizationBar::drawBoundary(CDC* dcp)
{
	NodeFigure::drawBoundary(dcp);
	if (_conditionText->isEmpty()) return; 
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) {
		_conditionText->drawBoundary(dcp);
	}
}

void SynchronizationBar::makeRegion(CRgn *sourceClipRgn)
{
	NodeFigure::makeRegion(sourceClipRgn);
	_conditionText->makeRegion(sourceClipRgn);
}

void SynchronizationBar::move(CDC* dcp,int dx,int dy)
{
	NodeFigure::move(dcp,dx,dy);
	if (_conditionText->isEmpty()) {
		_conditionText->moveCoord(dx,dy);
	} else {
		_conditionText->move(dcp,dx,dy);
	}
}

void SynchronizationBar::resetRegion()
{
	NodeFigure::resetRegion();
	_conditionText->resetRegion();
}

void SynchronizationBar::releaseRegion()
{
	NodeFigure::releaseRegion();
	_conditionText->releaseRegion();
}

void SynchronizationBar::setController(COODView *ptr)
{
	NodeFigure::setController(ptr);
	_conditionText->setController(ptr);
}

void SynchronizationBar::moveCoordForScroll(int dx,int dy)
{
	NodeFigure::moveCoordForScroll(dx,dy);
	_conditionText->moveCoord(dx,dy);
}

void SynchronizationBar::moveCoord(int dx,int dy)
{
	NodeFigure::moveCoord(dx,dy);
	_conditionText->moveCoord(dx,dy);
}

