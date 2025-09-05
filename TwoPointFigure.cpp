#include "stdafx.h"
/* TwoPointFigure.C */

#include "TwoPointFigure.h"
// Super Class : Figure

#include "COODView.h" // Collaboration
#include "Line.h" // Collaboration

IMPLEMENT_SERIAL(TwoPointFigure,Figure,1)

TwoPointFigure::~TwoPointFigure()
{
	// Empty
}

BOOL TwoPointFigure::checkMinWH()
{
	int w = _x2.x - _x1.x;
	int h = _y2.y - _y1.y;
	if (abs(w) >= FIGUREMINW && abs(h) >= FIGUREMINH) return(FALSE);
	_controller->beep("TwoPointFigure::checkMinWH()");
	return(TRUE);
}

void TwoPointFigure::setController(COODView *ptr)
{
	Figure::setController(ptr) ;
	_x1.setController(ptr);
	_y1.setController(ptr);
	_x2.setController(ptr);
	_y2.setController(ptr);
}   	

TwoPointFigure::TwoPointFigure(COODView *controller,int x,int y)
: Figure(controller)
{
	_points = new POINT[4];
	if (controller == NIL) return;
	_x1.setController(controller);
	_y1.setController(controller);
	_x2.setController(controller);
	_y2.setController(controller);
	_x1.set(x); _x2.set(x);
	_y1.set(y); _y2.set(y);
	_hotX = NIL;
	_hotY = NIL;
	_filled = FALSE;
}

TwoPointFigure::TwoPointFigure(COODView *controller,int x1,int y1,int x2,int y2)
: Figure(controller)
{
	_points = new POINT[4];
	checkPoints(x1,y1,x2,y2);
	if (controller == NIL) return;
	_x1.setController(controller);
	_y1.setController(controller);
	_x2.setController(controller);
	_y2.setController(controller);
	_x1.set(x1); _y1.set(y1);
	_x2.set(x2); _y2.set(y2);
	_hotX = NIL;
	_hotY = NIL;
	_filled = FALSE;
}

TwoPointFigure::TwoPointFigure()
: Figure()
{
	_points = new POINT[4];
	_x1.setController(NIL);
	_y1.setController(NIL);
	_x2.setController(NIL);
	_y2.setController(NIL);
	_hotX = NIL;
	_hotY = NIL;
	_filled = FALSE;
}

void TwoPointFigure::Serialize(CArchive& ar)
{
	Figure::Serialize(ar);
	_x1.Serialize(ar);
	_y1.Serialize(ar);
	_x2.Serialize(ar);
	_y2.Serialize(ar);
	if (ar.IsStoring()) {
		ar << (BYTE)_filled;
	} else {
		ar >> (BYTE&)_filled;
	}
}

int TwoPointFigure::width()
{
	return abs(_x2.x - _x1.x);
}

void TwoPointFigure::fill(CDC* dcp)
{
	return;
}

BOOL &TwoPointFigure::filled()
{
	return _filled;
}

void TwoPointFigure::getExclusiveClipRect(int &x1,int &y1,int &x2,int &y2)
{
	x1 = _x1.get(); y1 = _y1.get();
	x2 = _x2.get(); y2 = _y2.get();
}

void TwoPointFigure::center(int& x,int& y)
{
	x = (_x1.get() + _x2.get()) / 2;	  
	y = (_y1.get() + _y2.get()) / 2; 
}

void TwoPointFigure::last(int& x,int& y)
{
	x = _x2.get(); y = _y2.get(); 
}

XCoord *TwoPointFigure::notHotX()
{
	if (_hotX == &_x1) return &_x2;
	else return &_x1;
}

YCoord *TwoPointFigure::notHotY()
{
	if (_hotY == &_y1) return &_y2;
	else return &_y1;
}

void TwoPointFigure::swapPoints()
{
	XCoord tx;
	YCoord ty;
	tx.x = _x1.x;
	ty.y = _y1.y;
	_x1.x = _x2.x;
	_y1.y = _y2.y;
	_x2.x = tx.x;
	_y2.y = ty.y;
}

BOOL TwoPointFigure::checkNear(int x,int y)
{
	int l1 = distance(x,y,_x1.get(),_y1.get());
	int l2 = distance(x,y,_x2.get(),_y2.get());
	if (l1 < l2) {
		TwoPointFigure::swapPoints();
		return TRUE;
	} else {
		return FALSE;
	}	
}

BOOL TwoPointFigure::checkInRegion(CRgn* someregion)
{
	return _controller->checkInRegion(someregion,_x1,_y1,_x2,_y2);
}

void TwoPointFigure::coords(int& x1,int& y1,int& x2,int& y2)
{
	x1 = _x1.get(); y1 = _y1.get(); 
	x2 = _x2.get(); y2 = _y2.get(); 
}

void TwoPointFigure::setCoords(int x1,int y1,int x2,int y2)
{
	_x1.set(x1); _y1.set(y1);
	_x2.set(x2); _y2.set(y2);
}

void TwoPointFigure::invalidate()
{
	CRect tmp(getX1()-1,getY1()-1,getX2()+1,getY2()+1);
	_controller->invalidateRect(&tmp,TRUE);
}

void TwoPointFigure::minMaxXY()
{
	_controller->minMaxXY(_x1,_y1,_x2,_y2);
}

void TwoPointFigure::getMinMaxXY(int &minX,int &minY,int &maxX,int &maxY)
{
	if (minX > _x1.get()) minX = _x1.get();
	if (maxX < _x1.get()) maxX = _x1.get();
	if (minY > _y1.get()) minY = _y1.get();
	if (maxY < _y1.get()) maxY = _y1.get();
	if (minX > _x2.get()) minX = _x2.get();
	if (maxX < _x2.get()) maxX = _x2.get();
	if (minY > _y2.get()) minY = _y2.get();
	if (maxY < _y2.get()) maxY = _y2.get();
}

BOOL TwoPointFigure::isTroublesomeToModifyObject()
{
	return FALSE;
}

void TwoPointFigure::eraseDots(CDC* dcp)
{
	if (_dotedFlag == FALSE) return;
	drawDots(dcp);
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	_controller->clearArea(x1-DOTSIZE,y1-DOTSIZE,DOTSIZE,DOTSIZE);
	_controller->clearArea(x2,y1-DOTSIZE,DOTSIZE,DOTSIZE);
	_controller->clearArea(x2,y2,DOTSIZE,DOTSIZE);
	_controller->clearArea(x1-DOTSIZE,y2,DOTSIZE,DOTSIZE);
	/*
	_controller->clearArea(x1-DOTSIZE/2,y1-DOTSIZE/2,DOTSIZE,DOTSIZE);
	_controller->clearArea(x2-DOTSIZE/2,y1-DOTSIZE/2,DOTSIZE,DOTSIZE);
	_controller->clearArea(x2-DOTSIZE/2,y2-DOTSIZE/2,DOTSIZE,DOTSIZE);
	_controller->clearArea(x1-DOTSIZE/2,y2-DOTSIZE/2,DOTSIZE,DOTSIZE);
	*/
	_dotedFlag = FALSE;
}

void TwoPointFigure::clear(CDC* dcp)
{
	draw(dcp);
	int w = _x2.get() - _x1.get();
	int h = _y2.get() - _y1.get();
	if (w == 0 || h == 0) return;
	_controller->clearArea(_x1.get(),_y1.get(),w,h);
}

void TwoPointFigure::drawing(CDC* dcp,int dx,int dy)
{
	if (_hotX == NIL || _hotY == NIL) return;
	drawBoundary(dcp);
	_hotX->set(_hotX->get() + dx);
	_hotY->set(_hotY->get() + dy);
	drawBoundary(dcp);
}

void TwoPointFigure::drawDots(CDC* dcp)
{
	_dotedFlag = TRUE;
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	dcp->Rectangle(x1-DOTSIZE,y1-DOTSIZE,x1,y1);
	dcp->Rectangle(x2,y1-DOTSIZE,x2+DOTSIZE,y1);
	dcp->Rectangle(x2,y2,x2+DOTSIZE,y2+DOTSIZE);
	dcp->Rectangle(x1-DOTSIZE,y2,x1,y2+DOTSIZE);
}

BOOL TwoPointFigure::wantToResize(int x,int y,int px,int py)
{
	if (distance(x,y,px,py) <= DOTSIZE/2) return TRUE;
	return FALSE;
}

BOOL TwoPointFigure::wantToResizeExact(int x,int y)
{
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (x == x2 && y == y2) {
		_hotX = &_x2; _hotY = &_y2;
		return TRUE;
	} else if (x == x1 && y == y1) {
		_hotX = &_x1; _hotY = &_y1;
		return TRUE;
	} 
	_hotX = NIL; _hotY = NIL;
	return FALSE;
}

BOOL TwoPointFigure::wantToResize(int& x,int& y)
{
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (wantToResize(x,y,x1,y1)) {
		_hotX = &_x1; _hotY = &_y1;
		x = _x1.get(); y = _y1.get();
		return TRUE;
	} else if (wantToResize(x,y,x2,y1)) {
		_hotX = &_x2; _hotY = &_y1;
		x = _x2.get(); y = _y1.get();
		return TRUE;
	} else if (wantToResize(x,y,x2,y2)) {
		_hotX = &_x2; _hotY = &_y2;
		x = _x2.get(); y = _y2.get();
		return TRUE;
	} else if (wantToResize(x,y,x1,y2)) {
		_hotX = &_x1; _hotY = &_y2;
		x = _x1.get(); y = _y2.get();
		return TRUE;
	}
	_hotX = NIL; _hotY = NIL;
	return FALSE;
}

void TwoPointFigure::move(CDC* dcp,int dx,int dy)
{
	drawBoundary(dcp);
	_x1.set(_x1.get()+dx);
	_y1.set(_y1.get()+dy);
	_x2.set(_x2.get()+dx);
	_y2.set(_y2.get()+dy);
	drawBoundary(dcp);
}

void TwoPointFigure::moveCoord(int dx,int dy)
{
	_x1.x = _x1.x + dx; _y1.y = _y1.y + dy;
	_x2.x = _x2.x + dx; _y2.y = _y2.y + dy;
}

int TwoPointFigure::setHotXY(int x,int y)
{
	if (_hotX == NIL || _hotY == NIL) return 0;
	_hotX->set(x);
	_hotY->set(y);
	return 0;
}

Figure* TwoPointFigure::born(Figure* ptr)
{
	TwoPointFigure *copied = (TwoPointFigure *)ptr;
	copied->_x1.set(_x1);
	copied->_y1.set(_y1);
	copied->_x2.set(_x2);
	copied->_y2.set(_y2);
	copied->_filled = _filled;
	return (Figure::born((Figure *)copied));
}

void TwoPointFigure::setXY1(int x,int y)
{
	_x1.set(x); _y1.set(y);
}

void TwoPointFigure::setXY2(int x,int y)
{
	_x2.set(x); _y2.set(y);
}

void TwoPointFigure::adjustXYValue(int oldx,int oldy,int newx,int newy)
{
	if (_x1.get() == oldx && _y1.get() == oldy) {
		_x1.set(newx); _y1.set(newy);
	} else if (_x2.get() == oldx && _y2.get() == oldy) {
		_x2.set(newx); _y2.set(newy);
	}
}

BOOL TwoPointFigure::arrangeXY12()
{
	BOOL modified = FALSE;
	if (_x2.x < _x1.x) {
		int t = _x1.x;
		_x1.x = _x2.x;
		_x2.x = t;
		modified = TRUE;
	}
	if (_y2.y < _y1.y) {
		int t = _y1.y;
		_y1.y = _y2.y;
		_y2.y = t;
		modified = TRUE;
	}
	return modified;
}

BOOL TwoPointFigure::containedWithin(int x1,int y1,int x2,int y2)
{
	int thisX1 = _x1.x;
	int thisY1 = _y1.y;
	int thisX2 = _x2.x;
	int thisY2 = _y2.y;
	checkPoints(thisX1,thisY1,thisX2,thisY2);
	if (thisX1 >= x1 && thisY1 >= y1 && 
		thisX2 <= x2 && thisY2 <= y2) return TRUE;
	return FALSE;
}

BOOL TwoPointFigure::contains(int x,int y) 
{
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	checkPoints(x1,y1,x2,y2);
	if (x >= x1 && x <= x2 && y >= y1 && y <= y2) return TRUE;
	return FALSE;
}

BOOL TwoPointFigure::containsOnLargeBound(int x,int y) 
{
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	checkPoints(x1,y1,x2,y2);
	x2++; y2++;
	if (x >= x1 && x <= x2 && y >= y1 && y <= y2) return TRUE;
	return FALSE;
}

int TwoPointFigure::onWhichSide(int x,int y)
{
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	checkPoints(x1,y1,x2,y2);
	if (y == y1) {
		return NORTH;
	} else if (x == x2) {
		return EAST;
	} else if (y == y2) {
		return SOUTH;
	} else if (x == x1) {
		return WEST;
	} else {
		return UNDEFINED;
	}
}

BOOL TwoPointFigure::onBound(Line *aLine)
{
	int lx1 = aLine->_x1.get();
	int ly1 = aLine->_y1.get();
	int lx2 = aLine->_x2.get();
	int ly2 = aLine->_y2.get();
	if (contains(lx1,ly1) == FALSE) return FALSE;
	if (contains(lx2,ly2) == FALSE) return FALSE;
	int w = lx2 - lx1;
	int h = ly2 - ly1;
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	checkPoints(x1,y1,x2,y2);
	if (h == 0) {
		if (ly1 == y1 || ly1 == y2) return TRUE;
	} else if (w == 0) {
		if (lx1 == x1 || lx2 == x2) return TRUE;
	}
	return FALSE;
}

BOOL TwoPointFigure::adjustLine(Line *line,BOOL startPoint)
{
	int bx1 = _x1.get();
	int by1 = _y1.get();
	int bx2 = _x2.get();
	int by2 = _y2.get();
	int x1 = line->getX1();
	int y1 = line->getY1();
	int x2 = line->getX2();
	int y2 = line->getY2();
	checkPoints(bx1,by1,bx2,by2);
	int orient = line->orient();
	if (x1 == x2 && y1 == y2) return TRUE;
	if (contains(x1,y1) && contains(x2,y2)) {
		return TRUE;
	}
	if (startPoint) {
		if (orient == NORTH) {
			if (y1 >= by1 && y2 <= by1) {
				line->_y1.set(by1);
			} else if (y1 <= by2 && y2 >= by2) {
				line->_y1.set(by2);
			} else {
				return TRUE;
			}
		} else { // EAST
			if (x1 >= bx1 && x2 <= bx1) {
				line->_x1.set(bx1);
			} else if (x1 <= bx2 && x2 >= bx2) {
				line->_x1.set(bx2);
			} else {
				return TRUE;
			}
		}
	} else { // end point
		if (orient == NORTH) {
			if (y1 <= by1 && y2 >= by1) {
				line->_y2.set(by1);
			} else if (y1 >= by2 && y2 <= by2) {
				line->_y2.set(by2);
			} else {
				return TRUE;
			}
		} else { // EAST
			if (x1 <= bx1 && x2 >= bx1) {
				line->_x2.set(bx1);
			} else if (x1 >= bx2 && x2 <= bx2) {
				line->_x2.set(bx2);
			} else {
				return TRUE;
			}
		}
	}
	x1 = line->getX1();
	y1 = line->getY1();
	x2 = line->getX2();
	y2 = line->getY2();
	if (x1 == x2 && y1 == y2) return TRUE;
	return FALSE;
}

