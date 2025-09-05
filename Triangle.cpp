#include "stdafx.h"
/* Triangle.C */

#include "Triangle.h"
// Super Class : TwoPointFigure

#include "COODView.h" // Collaboration

IMPLEMENT_SERIAL(Triangle,TwoPointFigure,1)

Triangle::~Triangle()
{
	// Empty
}

void Triangle::makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn)
{
	int length = irint(sqrt((double)(w*w + h*h))/2./sin(M_PI/3.));
	double theta = w ? atan(double(h)/double(w)) : sign(h)*M_PI/2.;
	if (theta < 0) theta = theta + 2 * M_PI;
	double angle = (theta + M_PI / 2.);
	int dx = irint(length * cos(angle));
	int dy = irint(length * sin(angle));
	_points[0].x = x + dx;
	_points[0].y = y + dy;
	_points[1].x = x - dx;
	_points[1].y = y - dy;
	_points[2].x = x + w;
	_points[2].y = y + h;
	if (_region) delete _region;
	_region = _controller->createPolygonRegion(_points,3);
}


BOOL Triangle::checkMinWH()
{
	int w = _x2.get() - _x1.get();
	int h = _y2.get() - _y1.get();
	int length;
	if ( w == 0 && h == 0 ) length = 0;
	else if ( w == 0 ) length = abs(h);
	else if ( h == 0 ) length = abs(w);
	else length = irint(sqrt((double)(w*w + h*h)));
	if (length >= FIGUREMINL) return FALSE;
	return TRUE;
}

void Triangle::initializePoints()
{
	_points[0].x = 0;
	_points[0].y = 0;
	_points[1].x = 0;
	_points[1].y = 0;
	_points[2].x = 0;
	_points[2].y = 0;
}

Triangle::Triangle()
: TwoPointFigure()
{
	_points = new POINT[3];
	initializePoints();
}

Triangle::Triangle(COODView *controller,int x,int y,Popup* popup)
: TwoPointFigure(controller,x,y)
{
	if (_points != NIL) delete []_points;
	_points = new POINT[3];
	initializePoints();
	_popup = popup;
}

Triangle::Triangle(COODView *controller,int x1,int y1,int x2,int y2,Popup* popup)
: TwoPointFigure(controller,x1,y1,x2,y2)
{
	if (_points != NIL) delete []_points;
	_points = new POINT[3];
	initializePoints();
	// cancel check_points within the constructor of TwoPointFigure
	if (controller == NIL) return;
	_x1.setController(controller);
	_y1.setController(controller);
	_x2.setController(controller);
	_y2.setController(controller);
	_x1.set(x1); _y1.set(y1);
	_x2.set(x2); _y2.set(y2);
	_popup = popup;
}

void Triangle::Serialize(CArchive& ar)
{
	TwoPointFigure::Serialize(ar);
}

void Triangle::clear(CDC* dcp)
{
	draw(dcp);
	int minx,miny,maxx,maxy;
	getMinMaxOfThis(minx,miny,maxx,maxy);
	TRACE1("minx = %d ",minx);
	TRACE1("miny = %d ",miny);
	TRACE1("maxx = %d ",maxx);
	TRACE1("maxy = %d\n",maxy);
	_controller->clearArea(minx,miny,maxx-minx,maxy-miny);
}

void Triangle::getMinMaxOfThis(int &minx,int &miny,int &maxx,int &maxy)
{
	minx = _points[0].x;
	maxx = _points[0].x;
	int x = _points[1].x;
	if (minx > x) minx = x;
	if (maxx < x) maxx = x;
	x = _points[2].x;
	if (minx > x) minx = x;
	if (maxx < x) maxx = x;
	miny = _points[0].y;
	maxy = _points[0].y;
	int y = _points[1].y;
	if (miny > y) miny = y;
	if (maxy < y) maxy = y;
	y = _points[2].y;
	if (miny > y) miny = y;
	if (maxy < y) maxy = y;
}

void Triangle::invalidate()
{
	int minx,miny,maxx,maxy;
	getMinMaxOfThis(minx,miny,maxx,maxy);
	CRect tmp(minx-4,miny-4,maxx+4,maxy+4);
	_controller->invalidateRect(&tmp,TRUE);
}

void Triangle::drawDots(CDC* dcp)
{
	_dotedFlag = TRUE;
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	dcp->Rectangle(x1-DOTSIZE/2,y1-DOTSIZE/2,x1+DOTSIZE/2,y1+DOTSIZE/2);
	dcp->Rectangle(x2-DOTSIZE/2,y2-DOTSIZE/2,x2+DOTSIZE/2,y2+DOTSIZE/2);
}

BOOL Triangle::wantToResize(int& x,int& y)
{
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (TwoPointFigure::wantToResize(x,y,x1,y1)) {
		_hotX = &_x1; _hotY = &_y1;
		x = _x1.get(); y = _y1.get();
		return TRUE;
	} else if (TwoPointFigure::wantToResize(x,y,x2,y2)) {
		_hotX = &_x2; _hotY = &_y2;
		x = _x2.get(); y = _y2.get();
		return TRUE;
	}
	_hotX = NIL; _hotY = NIL;
	return FALSE;
}

void Triangle::eraseDots(CDC* dcp)
{
	if (_dotedFlag == FALSE) return;
	drawDots(dcp);
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	_controller->clearArea(x1-DOTSIZE/2,y1-DOTSIZE/2,DOTSIZE,DOTSIZE);
	_controller->clearArea(x2-DOTSIZE/2,y2-DOTSIZE/2,DOTSIZE,DOTSIZE);
	_dotedFlag = FALSE;
}

void Triangle::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int w = _x2.get() - _x1.get();
	int h = _y2.get() - _y1.get();
	int length = irint(sqrt((double)(w*w + h*h))/2./sin(M_PI/3.));
	double angle;
	double theta = w ? atan(double(h)/double(w)) : sign(h)*M_PI/2.;
	if (theta < 0) theta = theta + 2 * M_PI;
	angle = (theta + M_PI / 2.);
	int dx = irint(length * cos(angle));
	int dy = irint(length * sin(angle));
	POINT left;
	POINT right;
	left.x = _x1.get()+dx;
	left.y = _y1.get()+dy;
	right.x = _x1.get()-dx;
	right.y = _y1.get()-dy;

	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		CPen *oldPen = dcp->SelectObject(COODView::ErasePen);
		DrawLine(dcp,_x1.get(),_y1.get(),_x2.get(),_y2.get());
		dcp->SelectObject(oldPen);
	} else {
		DrawLine(dcp,_x1.get(),_y1.get(),_x2.get(),_y2.get());
	}
	DrawLine(dcp,_x2.get(),_y2.get(),left.x,left.y);
	DrawLine(dcp,left.x,left.y,right.x,right.y);
	DrawLine(dcp,right.x,right.y,_x2.get(),_y2.get());
}

void Triangle::fill(CDC* dcp)
{
	if (!_inCanvas) return;
	int w = _x2.get() - _x1.get();
	int h = _y2.get() - _y1.get();
	int length = irint(sqrt((double)(w*w + h*h))/2./sin(M_PI/3.));
	double angle;
	double theta = w ? atan(double(h)/double(w)) : sign(h)*M_PI/2.;
	if (theta < 0) theta = theta + 2 * M_PI;
	angle = (theta + M_PI / 2.);
	int dx = irint(length * cos(angle));
	int dy = irint(length * sin(angle));
	POINT data[3];
	data[0].x = _x2.get();
	data[0].y = _y2.get();
	data[1].x = _x1.get()+dx;
	data[1].y = _y1.get()+dy;
	data[2].x = _x1.get()-dx;
	data[2].y = _y1.get()-dy;
	FillPolygon(dcp,data,3);
}

UnsignedLong *Triangle::whoAreYou()
{
	return IAMTRIANGLE; 
}

Figure* Triangle::born(Figure* ptr)
{
	Triangle *copied;
	if (ptr == NIL) {
		copied = new Triangle(NIL,0,0,NIL);
	} else {
		copied = (Triangle *)ptr;
	}
	return (TwoPointFigure::born((Figure *)copied));
}

void Triangle::makeRegion(CRgn *sourceClipRgn)
{
	makeRegion(_x1.get(),_y1.get(),_x2.get()-_x1.get(),_y2.get()-_y1.get(),sourceClipRgn);
}

void Triangle::center(int &x,int &y)
{ 	x = (_x2.get() - _x1.get()) / 3 + _x1.get();
	y = (_y2.get() - _y1.get()) / 3 + _y1.get(); 
}

void Triangle::minMaxXY()
{
	_controller->minMaxXY(_x1,_y1,_x2,_y2);
	int w = _x2.get() - _x1.get();
	int h = _y2.get() - _y1.get();
	int length = irint(sqrt((double)(w*w + h*h))/2./sin(M_PI/3.));
	double angle;
	double theta = w ? atan(double(h)/double(w)) : sign(h)*M_PI/2.;
	if (theta < 0) theta = theta + 2 * M_PI;
	angle = (theta + M_PI / 2.);
	int dx = irint(length * cos(angle));
	int dy = irint(length * sin(angle));
	XCoord x1;
	YCoord y1;
	XCoord x2;
	YCoord y2;
	x1.setController(_controller);
	y1.setController(_controller);
	x2.setController(_controller);
	y2.setController(_controller);
	x1.set(_x1.get()+dx);
	y1.set(_y1.get()+dy);
	x2.set(_x1.get()-dx);
	y2.set(_y1.get()-dy);
	_controller->minMaxXY(x1,y1,x2,y2);
}

BOOL Triangle::checkInRegion(CRgn* someregion)
{
	int sx = _x1.get(); int sy = _y1.get();
	int w = _x2.get() - _x1.get(); int h = _y2.get() - _y1.get();
	int length = irint(sqrt((double)(w*w + h*h))/2./sin(M_PI/3.));
	double theta = w ? atan(double(h)/double(w)) : sign(h)*M_PI/2.;
	if (theta < 0) theta = theta + 2 * M_PI;
	double angle = (theta + M_PI / 2.);
	int dx = irint(length * cos(angle));
	int dy = irint(length * sin(angle));
	_points[0].x = sx + dx;
	_points[0].y = sy + dy;
	_points[1].x = sx - dx;
	_points[1].y = sy - dy;
	_points[2].x = sx + w;
	_points[2].y = sy + h;

	int minx = _points[0].x;
	int maxx = _points[0].x;
	int x = _points[1].x;
	if (minx > x) minx = x;
	if (maxx < x) maxx = x;
	x = _points[2].x;
	if (minx > x) minx = x;
	if (maxx < x) maxx = x;
	int miny = _points[0].y;
	int maxy = _points[0].y;
	int y = _points[1].y;
	if (miny > y) miny = y;
	if (maxy < y) maxy = y;
	y = _points[2].y;
	if (miny > y) miny = y;
	if (maxy < y) maxy = y;
	return _controller->checkInRegion(someregion,minx,miny,maxx,maxy);
}

void Triangle::getMinMaxXY(int &minX,int &minY,int &maxX,int &maxY)
{
	int minx = _points[0].x;
	int maxx = _points[0].x;
	int x = _points[1].x;
	if (minx > x) minx = x;
	if (maxx < x) maxx = x;
	x = _points[2].x;
	if (minx > x) minx = x;
	if (maxx < x) maxx = x;
	int miny = _points[0].y;
	int maxy = _points[0].y;
	int y = _points[1].y;
	if (miny > y) miny = y;
	if (maxy < y) maxy = y;
	y = _points[2].y;
	if (miny > y) miny = y;
	if (maxy < y) maxy = y;
	if (minX > minx) minX = minx;
	if (minY > miny) minY = miny;
	if (maxX < maxx) maxX = maxx;
	if (maxY < maxy) maxY = maxy;
}

BOOL Triangle::checkNear(int,int)
{
	return FALSE;
}


