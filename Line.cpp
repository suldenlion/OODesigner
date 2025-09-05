#include "stdafx.h"
/* Line.C */

#include "OOD.h"
#include "Line.h"
// Super Class : TwoPointFigure

#include "COODView.h" 
#include "LinePopup.h"

IMPLEMENT_SERIAL(Line,TwoPointFigure,1)

Line::~Line()
{
	// Empty
}

void Line::setThickness(int val)
{
	_thickness = val;
}

void Line::makeSmallRegion()
{
	int x = _x1.get();
	int y = _y1.get();
	int w = _x2.get()-_x1.get();
	int h = _y2.get()-_y1.get();
	if (_orient == NORTH) {
		if (abs(h) < 2) {
			if (_region) delete _region;
			_region = createRegion();
			return;
		}
		_points[0].x = x - 1;
		_points[0].y = y + sign(h)*1;
		_points[1].x = x + 1;
		_points[1].y = y + sign(h)*1;
		_points[2].x = x + 1;
		_points[2].y = y + h - sign(h)*1;
		_points[3].x = x - 1;
		_points[3].y = y + h - sign(h)*1;
		if (_region) delete _region;
		_region = _controller->createPolygonRegion(_points,4);
	} else if (_orient == EAST) {
		if (abs(w) < 2) {
			if (_region) delete _region;
			_region = createRegion();
			return;
		}
		_points[0].x = x + sign(w)*1;
		_points[0].y = y - 1;
		_points[1].x = x + w - sign(w)*1;
		_points[1].y = y - 1;
		_points[2].x = x + w - sign(w)*1;
		_points[2].y = y + 1;
		_points[3].x = x + sign(w)*1;
		_points[3].y = y + 1;
		if (_region) delete _region;
		_region = _controller->createPolygonRegion(_points,4);
	} else {
		if (_region) delete _region;
		_region = createRegion();
	}
}

void Line::makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn)
{
	int regionlength = _controller->regionLength();
	x = x;
	y = y;
	double angle;
	double theta = w ? atan(double(h)/double(w)) : sign(h)*M_PI/2.;
	if (theta < 0) theta = theta + 2 * M_PI;
	angle = (theta + M_PI / 2.);
	int dx = irint(regionlength * cos(angle));
	int dy = irint(regionlength * sin(angle));
	_points[0].x = x + dx;
	_points[0].y = y + dy;
	_points[1].x = x - dx;
	_points[1].y = y - dy;
	_points[2].x = x + w - dx;
	_points[2].y = y + h - dy;
	_points[3].x = x + w + dx;
	_points[3].y = y + h + dy;
	if (_region) delete _region;
	_region = _controller->createPolygonRegion(_points,4);
}

int &Line::style()
{
	return _style;
}

void Line::Serialize(CArchive& ar)
{
	TwoPointFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _direct << (LONG) _type;
		ar << (LONG) _style << (LONG) _orient;
		ar << (LONG) _head << (LONG) _thickness;
		ar << (LONG) _absoluteFollowPos << (DOUBLE) _slope;
	} else {
		ar >> (LONG&) _direct >> (LONG&) _type;
		ar >> (LONG&) _style >> (LONG&) _orient;
		ar >> (LONG&) _head >> (LONG&) _thickness;
		ar >> (LONG&) _absoluteFollowPos >> (DOUBLE&) _slope;
	}
}

Line::Line()
: TwoPointFigure()
{
	_popup = theAppPtr->theLinePopup;

	_direct = NODIR;
	_type = 0;
	_style = SOLID;
	_orient = UNDEFINED;
	_head = HEADNONE;
	_slope = 0;
	_thickness = 1;
	_absoluteFollowPos = ATNOWHERE;
}

Line::Line(COODView *controller,int x,int y,Popup* popup,int type)
: TwoPointFigure(controller,x,y)
{
	_popup = popup;
	_direct = NODIR;
	_type = type;
	_style = SOLID;
	_orient = UNDEFINED;
	_head = HEADNONE;
	_slope = 0;
	_thickness = 1;
	_absoluteFollowPos = ATNOWHERE;
}

Line::Line(COODView *controller,int x1,int y1,int x2,int y2,Popup* popup,int type)
: TwoPointFigure(controller,x1,y1,x2,y2)
{
	_x1.set(x1); _y1.set(y1);
	_x2.set(x2); _y2.set(y2);
	_popup = popup;
	_direct = NODIR;
	_type = type;
	_style = SOLID;
	_orient = UNDEFINED;
	_head = HEADNONE;
	_slope = 0;
	_thickness = 1;
	_absoluteFollowPos = ATNOWHERE;
}

void Line::clear(CDC* dcp)
{
	draw(dcp);
	if (_direct == NODIR) return;
	if (_head == HEADNONE) return;
	int x1 = getX1(); int y1 = getY1();
	int x2 = getX2(); int y2 = getY2();
	if (x1 == x2) {
		CRect tmp(x1-10,y1,x2+10,y2);
		_controller->invalidateRect(&tmp);
	} else if (y1 == y2) {
		CRect tmp(x1,y1-10,x2,y2+10);
		_controller->invalidateRect(&tmp);
	}
}

void Line::fillFgArrow(CDC* dcp,int x,int y,int dx1,int dy1,int dx2,int dy2)
{
	POINT data[3];
	data[0].x = x;
	data[0].y = y;
	data[1].x = x + dx1;
	data[1].y = y + dy1;
	data[2].x = x + dx2;
	data[2].y = y + dy2;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN && _brushIndex == RED_BRUSH) {
		CBrush *oldBrush = dcp->SelectObject(COODView::HighlightBrush);
		FillPolygon(dcp,data,3);
		dcp->SelectObject(oldBrush);
	} else {
		CBrush brush(theAppPtr->shapeForegroundColor);
		CBrush *oldBrush = dcp->SelectObject(&brush);
		FillPolygon(dcp,data,3);
		dcp->SelectObject(oldBrush);
	}
	if (mode == R2_NOTXORPEN) {
		// rubber banding 잔상 때문에 가운데 선 한번 더 그림
		DrawLine(dcp,x,y,x+(dx1+dx2)/2,y+(dy1+dy2)/2); 
	}
}

void Line::fillFgHalfArrow(CDC* dcp,int x,int y,int dx1,int dy1,int dx2,int dy2)
{
	POINT data[3];
	data[0].x = x;
	data[0].y = y;
	data[1].x = x + dx1;
	data[1].y = y + dy1;
	data[2].x = x + dx2;
	data[2].y = y + dy2;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN && _brushIndex == RED_BRUSH) {
		CBrush *oldBrush = dcp->SelectObject(COODView::HighlightBrush);
		FillPolygon(dcp,data,3);
		dcp->SelectObject(oldBrush);
	} else {
		CBrush brush(theAppPtr->shapeForegroundColor);
		CBrush *oldBrush = dcp->SelectObject(&brush);
		FillPolygon(dcp,data,3);
		dcp->SelectObject(oldBrush);
	}
}

void Line::fillBgArrow(CDC* dcp,int x,int y,int dx1,int dy1,int dx2,int dy2)
{
	POINT data[3];
	data[0].x = x;
	data[0].y = y;
	data[1].x = x + dx1;
	data[1].y = y + dy1;
	data[2].x = x + dx2;
	data[2].y = y + dy2;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		CBrush brush(theAppPtr->paperColor);
		CBrush *oldBrush = dcp->SelectObject(&brush);
		FillPolygon(dcp,data,3);
		dcp->SelectObject(oldBrush);
	}
	DrawLine(dcp,data[0].x,data[0].y,data[1].x,data[1].y);
	DrawLine(dcp,data[1].x,data[1].y,data[2].x,data[2].y);
	DrawLine(dcp,data[2].x,data[2].y,data[0].x,data[0].y);
}

void Line::drawLineArrow(CDC* dcp,int x,int y,int dx1,int dy1,int dx2,int dy2)
{
	POINT data[3];
	data[0].x = x;
	data[0].y = y;
	data[1].x = x + dx1;
	data[1].y = y + dy1;
	data[2].x = x + dx2;
	data[2].y = y + dy2;
	DrawLine(dcp,data[1].x,data[1].y,data[0].x,data[0].y,_thickness,SOLID);
	DrawLine(dcp,data[2].x,data[2].y,data[0].x,data[0].y,_thickness,SOLID);
}

void Line::drawHead(CDC* dcp)
{
	if (_direct == NODIR || _direct == INVERT_DIR) return;
	if (_head == HEADNONE) return;
	int arrowlength = _controller->arrowLength();
	if (_head == HEADARROW1) {
		double deltax = (double)(_x2.get() - _x1.get());
		double deltay = (double)(_y2.get() - _y1.get());
		double theta;
		if (deltax == 0) {
			theta = sign(deltay)*M_PI/2.;
		} else {
			theta = atan(deltay/deltax);
		}
		double angle1 = theta - (M_PI * 3. / 4. + 0.5);
		double angle2 = theta + (M_PI * 3. / 4. + 0.5);
		int dx1 = irint(arrowlength * cos(angle1));
		int dy1 = irint(arrowlength * sin(angle1));
		int dx2 = irint(arrowlength * cos(angle2));
		int dy2 = irint(arrowlength * sin(angle2));
		if ( deltax >= 0 ) {
			fillFgArrow(dcp,_x2.get(),_y2.get(),dx1,dy1,dx2,dy2);
		} else {
			fillFgArrow(dcp,_x2.get(),_y2.get(),-dx1,-dy1,-dx2,-dy2);
		}
	} else if (_head == HEADARROW2) {
		double deltax = (double)(_x2.get() - _x1.get());
		double deltay = (double)(_y2.get() - _y1.get());
		double theta;
		if (deltax == 0) {
			theta = sign(deltay)*M_PI/2.;
		} else {
			theta = atan(deltay/deltax);
		}
		double angle1 = theta - (M_PI * 3. / 4. + 0.5);
		double angle2 = theta + (M_PI * 3. / 4. + 0.5);
		int dx1 = irint(arrowlength * cos(angle1));
		int dy1 = irint(arrowlength * sin(angle1));
		int dx2 = irint(arrowlength * cos(angle2));
		int dy2 = irint(arrowlength * sin(angle2));
		if ( deltax >= 0 ) {
			drawLineArrow(dcp,_x2.get(),_y2.get(),dx1,dy1,dx2,dy2);
		} else {
			drawLineArrow(dcp,_x2.get(),_y2.get(),-dx1,-dy1,-dx2,-dy2);
		}
	} else if (_head == HEADARROW3) {
		double deltax = (double)(_x2.get() - _x1.get());
		double deltay = (double)(_y2.get() - _y1.get());
		double theta;
		if (deltax == 0) {
			theta = sign(deltay)*M_PI/2.;
		} else {
			theta = atan(deltay/deltax);
		}
		double angle1 = theta - (M_PI * 3. / 4. + 0.5);
		double angle2 = theta + (M_PI * 3. / 4. + 0.5);
		int dx1 = irint(1.2 * arrowlength * cos(angle1));
		int dy1 = irint(1.2 * arrowlength * sin(angle1));
		int dx2 = irint(1.2 * arrowlength * cos(angle2));
		int dy2 = irint(1.2 * arrowlength * sin(angle2));
		if ( deltax >= 0 ) {
			fillBgArrow(dcp,_x2.get(),_y2.get(),dx1,dy1,dx2,dy2);
		} else {
			fillBgArrow(dcp,_x2.get(),_y2.get(),-dx1,-dy1,-dx2,-dy2);
		}
	} else if (_head == HEADARROW4) {
		double deltax = (double)(_x2.get() - _x1.get());
		double deltay = (double)(_y2.get() - _y1.get());
		double theta;
		if (deltax == 0) {
			theta = sign(deltay)*M_PI/2.;
		} else {
			theta = atan(deltay/deltax);
		}
		double angle1 = theta - (M_PI * 3. / 4. + 0.4);
		double angle2 = theta + (M_PI * 3. / 4. + 0.4);
		int dx1 = irint(1.05 * arrowlength * cos(angle1));
		int dy1 = irint(1.05 * arrowlength * sin(angle1));
		int dx2 = irint(1.05 * arrowlength * cos(angle2));
		int dy2 = irint(1.05 * arrowlength * sin(angle2));
		int cx = (dx1+dx2)/2;
		int cy = (dy1+dy2)/2;
		if ( deltax >= 0 ) {
			fillFgHalfArrow(dcp,_x2.get(),_y2.get(),dx2,dy2,cx,cy);
		} else {
			fillFgHalfArrow(dcp,_x2.get(),_y2.get(),-dx1,-dy1,-cx,-cy);
		}
	}
}

void Line::drawTail(CDC* dcp)
{
	if (_direct == NODIR || _direct == NORMAL_DIR) return;
	if (_head == HEADNONE) return;
	int arrowlength = _controller->arrowLength();
	if (_head == HEADARROW1) {
		double deltax = (double)(_x1.get() - _x2.get());
		double deltay = (double)(_y1.get() - _y2.get());
		double theta;
		if (deltax == 0) {
			theta = sign(deltay)*M_PI/2.;
		} else {
			theta = atan(deltay/deltax);
		}
		double angle1 = theta - (M_PI * 3. / 4. + 0.5);
		double angle2 = theta + (M_PI * 3. / 4. + 0.5);
		int dx1 = irint(arrowlength * cos(angle1));
		int dy1 = irint(arrowlength * sin(angle1));
		int dx2 = irint(arrowlength * cos(angle2));
		int dy2 = irint(arrowlength * sin(angle2));
		if ( deltax >= 0 ) {
			fillFgArrow(dcp,_x1.get(),_y1.get(),dx1,dy1,dx2,dy2);
		} else {
			fillFgArrow(dcp,_x1.get(),_y1.get(),-dx1,-dy1,-dx2,-dy2);
		}
	} else if (_head == HEADARROW2) {
		double deltax = (double)(_x1.get() - _x2.get());
		double deltay = (double)(_y1.get() - _y2.get());
		double theta;
		if (deltax == 0) {
			theta = sign(deltay)*M_PI/2.;
		} else {
			theta = atan(deltay/deltax);
		}
		double angle1 = theta - (M_PI * 3. / 4. + 0.5);
		double angle2 = theta + (M_PI * 3. / 4. + 0.5);
		int dx1 = irint(arrowlength * cos(angle1));
		int dy1 = irint(arrowlength * sin(angle1));
		int dx2 = irint(arrowlength * cos(angle2));
		int dy2 = irint(arrowlength * sin(angle2));
		if ( deltax >= 0 ) {
			drawLineArrow(dcp,_x1.get(),_y1.get(),dx1,dy1,dx2,dy2);
		} else {
			drawLineArrow(dcp,_x1.get(),_y1.get(),-dx1,-dy1,-dx2,-dy2);
		}
	} else if (_head == HEADARROW3) {
		double deltax = (double)(_x1.get() - _x2.get());
		double deltay = (double)(_y1.get() - _y2.get());
		double theta;
		if (deltax == 0) {
			theta = sign(deltay)*M_PI/2.;
		} else {
			theta = atan(deltay/deltax);
		}
		double angle1 = theta - (M_PI * 3. / 4. + 0.5);
		double angle2 = theta + (M_PI * 3. / 4. + 0.5);
		int dx1 = irint(1.2 * arrowlength * cos(angle1));
		int dy1 = irint(1.2 * arrowlength * sin(angle1));
		int dx2 = irint(1.2 * arrowlength * cos(angle2));
		int dy2 = irint(1.2 * arrowlength * sin(angle2));
		if ( deltax >= 0 ) {
			fillBgArrow(dcp,_x1.get(),_y1.get(),dx1,dy1,dx2,dy2);
		} else {
			fillBgArrow(dcp,_x1.get(),_y1.get(),-dx1,-dy1,-dx2,-dy2);
		}
	} else if (_head == HEADARROW4) {
		double deltax = (double)(_x1.get() - _x2.get());
		double deltay = (double)(_y1.get() - _y2.get());
		double theta;
		if (deltax == 0) {
			theta = sign(deltay)*M_PI/2.;
		} else {
			theta = atan(deltay/deltax);
		}
		double angle1 = theta - (M_PI * 3. / 4. + 0.4);
		double angle2 = theta + (M_PI * 3. / 4. + 0.4);
		int dx1 = irint(1.05 * arrowlength * cos(angle1));
		int dy1 = irint(1.05 * arrowlength * sin(angle1));
		int dx2 = irint(1.05 * arrowlength * cos(angle2));
		int dy2 = irint(1.05 * arrowlength * sin(angle2));
		int cx = (dx1+dx2)/2;
		int cy = (dy1+dy2)/2;
		if ( deltax >= 0 ) {
			fillFgHalfArrow(dcp,_x1.get(),_y1.get(),dx2,dy2,cx,cy);
		} else {
			fillFgHalfArrow(dcp,_x1.get(),_y1.get(),-dx1,-dy1,-cx,-cy);
		}
	}
}

void Line::eraseDots(CDC* dcp)
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

void Line::drawDots(CDC* dcp)
{
	_dotedFlag = TRUE;
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	dcp->Rectangle(x1-DOTSIZE/2,y1-DOTSIZE/2,x1+DOTSIZE/2,y1+DOTSIZE/2);
	dcp->Rectangle(x2-DOTSIZE/2,y2-DOTSIZE/2,x2+DOTSIZE/2,y2+DOTSIZE/2);
}

void Line::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	DrawLine(dcp,_x1.get(),_y1.get(),_x2.get(),_y2.get(),_thickness,_style);
	drawHead(dcp);
	drawTail(dcp);
}

void Line::following(CDC* dcp,int dx,int dy)
{
	/*
	if (_type == ORDINARY) {
		drawing(dcp,dx,dy);
	} else { // STRAIGHT
		myDrawLine(dcp,_x1,_y1,_x2,_y2);
		drawHead(dcp);
		drawTail(dcp);
		if (_orient == NORTH) {
			_x1 = newx;
		} else if (_orient == EAST) {
			_y1 = newy;
		}
		myDrawLine(dcp,_x1,_y1,newx,newy);
		_x2 = newx;
		_y2 = newy;
		drawHead(dcp);
		drawTail(dcp);
	}
	*/	
}

BOOL Line::wantToResize(int& x,int& y)
{
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (TwoPointFigure::wantToResize(x,y,x2,y2)) {
		_hotX = &_x2; _hotY = &_y2;
		x = _x2.get(); y = _y2.get();
		return TRUE;
	} else if (TwoPointFigure::wantToResize(x,y,x1,y1)) {
		_hotX = &_x1; _hotY = &_y1;
		x = _x1.get(); y = _y1.get();
		return TRUE;
	}
	_hotX = NIL; _hotY = NIL;
	return FALSE;
}

void Line::setSuperHotXY(int x,int y)
{
	TwoPointFigure::setHotXY(x,y);
}

int Line::resizeCoordDXY(int dx,int dy)
{
	if (_hotX == NIL || _hotY == NIL) return ATNOWHERE;
	int followPos = ATNOWHERE;
	if (_type == ORDINARY) {
		_hotX->set(_hotX->get() + dx);
		_hotY->set(_hotY->get() + dy);
	} else {
		if (_orient == NORTH) {
			_hotX->set(_hotX->get() + dx);
			_hotY->set(_hotY->get() + dy);
			if (_hotX == &_x1) {
				_x2.set(_x2.get() + dx);
				followPos = ATAFTER;
			} else {
				_x1.set(_x1.get() + dx);
				followPos = ATBEFORE;
			}
		} else if (_orient == EAST) {
			_hotX->set(_hotX->get() + dx);
			_hotY->set(_hotY->get() + dy);
			if (_hotY == &_y1) {
				_y2.set(_y2.get() + dy);
				followPos = ATAFTER;
			} else {
				_y1.set(_y1.get() + dy);
				followPos = ATBEFORE;
			}
		} else {
			_hotX->set(_hotX->get() + dx);
			_hotY->set(_hotY->get() + dy);
			_type = ORDINARY;
		}
	}
	return followPos;
}

int Line::resizeCoord(int x,int y)
{
	int followPos = ATNOWHERE;
	if (_type == ORDINARY) {
		_hotX->set(x);
		_hotY->set(y);
	} else {
		if (_orient == NORTH) {
			_hotX->set(x);
			_hotY->set(y);
			if (_hotX == &_x1) {
				_x2.set(x);
				followPos = ATAFTER;
			} else {
				_x1.set(x);
				followPos = ATBEFORE;
			}
		} else if (_orient == EAST) {
			_hotX->set(x);
			_hotY->set(y);
			if (_hotY == &_y1) {
				_y2.set(y);
				followPos = ATAFTER;
			} else {
				_y1.set(y);
				followPos = ATBEFORE;
			}
		} else {
			_hotX->set(x);
			_hotY->set(y);
			_type = ORDINARY;
		}
	}
	return followPos;
}

int Line::setHotXY(int x,int y)
{
	if (_hotX == NIL || _hotY == NIL) return ATNOWHERE;
	if (_type == ORDINARY) {
		_hotX->set(x);
		_hotY->set(y);
		return ATNOWHERE;
	} else {
		if (_orient == NORTH) {
			_hotY->set(y);
			if (_hotY == &_y1) return ATAFTER;
			else return ATBEFORE;
		} else if (_orient == EAST) {
			_hotX->set(x);
			if (_hotX == &_x1) return ATAFTER;
			else return ATBEFORE;
		} else {
			int cX = x;
			int cY = y;
			int w = abs(cX - notHotX()->get());
			int h = abs(cY - notHotY()->get());
			if (w > h) {
				_hotX->set(cX);
				_hotY->set(notHotY()->get());
			} else {
				_hotX->set(notHotX()->get());
				_hotY->set(cY);
			}
		}
	}
	return ATNOWHERE;
}

void Line::drawingCoord(int dx,int dy)
{
	if (_type == ORDINARY) {
		_hotX->set(_hotX->get() + dx);
		_hotY->set(_hotY->get() + dy);
	} else {
		if (_orient == NORTH) {
			_hotY->set(_hotY->get() + dy);
		} else if (_orient == EAST) {
			_hotX->set(_hotX->get() + dx);
		} else {
			int cX = _controller->currentX();
			int cY = _controller->currentY();
			int w = abs(cX - notHotX()->get());
			int h = abs(cY - notHotY()->get());
			if (w > h) {
				_hotX->set(cX);
				_hotY->set(notHotY()->get());
			} else {
				_hotX->set(notHotX()->get());
				_hotY->set(cY);
			}
		}
	}
}

void Line::drawing(CDC* dcp,int dx,int dy)
{
	if (_hotX == NIL || _hotY == NIL) {
		return;
	}
	DrawLine(dcp,_x1.get(),_y1.get(),_x2.get(),_y2.get(),_thickness,_style);
	drawHead(dcp);
	drawTail(dcp);
	drawingCoord(dx,dy);
	DrawLine(dcp,_x1.get(),_y1.get(),_x2.get(),_y2.get(),_thickness,_style);
	drawHead(dcp);
	drawTail(dcp);
}

BOOL Line::setFollowing(int x,int y,int orient)
{
	if (setFollowing(x,y)) {
		if (orient == _orient) {
			_hotX = NIL;
			_hotY = NIL;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Line::setFollowing2(int x,int y)
{
	_hotX = &_x2;
	_hotY = &_y2;
	return TRUE;
}

BOOL Line::setFollowing(int x,int y)
{
	if (_hotX != NIL || _hotY != NIL) return FALSE;
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (x == x1 && y == y1) {
		_hotX = &_x1; _hotY = &_y1;
		return TRUE;
	} else if (x == x2 && y == y2) {
		_hotX = &_x2; _hotY = &_y2;
		return TRUE;
	}
	_hotX = NIL; _hotY = NIL;
	return FALSE;
}

int Line::whereToFollow()
{
	if (_hotX == NIL || _hotY == NIL) return ATNOWHERE;
	int followPos = ATNOWHERE;
	if (_type == STRAIGHT) {
		if (_hotX == &_x1 && _hotY == &_y1) {
			followPos = ATAFTER;
		} else if (_hotX == &_x2 && _hotY == &_y2) {
			followPos = ATBEFORE;
		}
	}
	return followPos;
}

int Line::resizing(CDC* dcp,int dx,int dy)
{
	if (_hotX == NIL || _hotY == NIL) return ATNOWHERE;
	DrawLine(dcp,_x1.get(),_y1.get(),_x2.get(),_y2.get(),_thickness,_style);
	drawHead(dcp);
	drawTail(dcp);
	int followPos = resizeCoordDXY(dx,dy);
	DrawLine(dcp,_x1.get(),_y1.get(),_x2.get(),_y2.get(),_thickness,_style);
	drawHead(dcp);
	drawTail(dcp);
	if (_absoluteFollowPos != ATNOWHERE) return _absoluteFollowPos;
	return followPos;
}

UnsignedLong *Line::whoAreYou()
{
	return IAMLINE; 
}

Figure* Line::born(Figure* ptr)
{
	Line *copied;
	if (ptr == NIL) {
		copied = new Line(NIL,0,0,NIL,_type);
	} else {
		copied = (Line *)ptr;
	}
	copied->_slope = _slope;
	copied->_direct = _direct;
	copied->_type = _type;
	copied->_style = _style;
	copied->_orient = _orient;
	copied->_head = _head;
	copied->_thickness = _thickness;
	return (TwoPointFigure::born((Figure *)copied));
}

void Line::makeRegion(CRgn *sourceClipRgn)
{
	makeRegion(_x1.get(),_y1.get(),_x2.get()-_x1.get(),_y2.get()-_y1.get(),sourceClipRgn);
}

BOOL Line::checkMinWH()
{
	int len = length();
	if (len >= FIGUREMINW) return(FALSE);
	_controller->beep("Line::checkMinWH()");
	return(TRUE);
}

int Line::length()
{
	int w = _x2.get() - _x1.get();
	int h = _y2.get() - _y1.get();
	int len;
	if ( w == 0 && h == 0 ) len = 0;
	else if ( w == 0 ) len = abs(h);
	else if ( h == 0 ) len = abs(w);
	else len = irint(sqrt((double)(w*w + h*h)));
	return len;
}

int Line::whereToMeet(int x,int y)
{
	if (_x1.get() == x && _y1.get() == y) {
		return ATBEFORE;
	} else if (_x2.get() == x && _y2.get() == y) {
		return ATAFTER;
	} else {
		return ATNOWHERE;
	}
}

int Line::whereToMeet(Line *line)
{
	if (_x1.get() == line->_x1.get() && _y1.get() == line->_y1.get()) {
		return ATBEFORE;
	} else if (_x1.get() == line->_x2.get() && _y1.get() == line->_y2.get()) {
		return ATBEFORE;
	} else if (_x2.get() == line->_x1.get() && _y2.get() == line->_y1.get()) {
		return ATAFTER;
	} else if (_x2.get() == line->_x2.get() && _y2.get() == line->_y2.get()) {
		return ATAFTER;
	} else {
		return ATNOWHERE;
	}
}

BOOL Line::doesCross(Line *that)
{
	Line *north;
	Line *east;
	if (_orient == NORTH) {
		north = this;
		east = that;
	} else {
		north = that;
		east = this;
	}
	if (east->_x1.get() < east->_x2.get()) {
		if (north->_x1.get() < east->_x1.get()) return FALSE;
		if (north->_x1.get() > east->_x2.get()) return FALSE;
	} else if (east->_x1.get() > east->_x2.get()) {
		if (north->_x1.get() < east->_x2.get()) return FALSE;
		if (north->_x1.get() > east->_x1.get()) return FALSE;
	}
	if (north->_y1.get() < north->_y2.get()) {
		if (east->_y1.get() < north->_y1.get()) return FALSE;
		if (east->_y1.get() > north->_y2.get()) return FALSE;
	} else if (north->_y1.get() > north->_y2.get()) {
		if (east->_y1.get() < north->_y2.get()) return FALSE;
		if (east->_y1.get() > north->_y1.get()) return FALSE;
	}
	return TRUE;	
}

BOOL Line::doesMeet(int x,int y)
{
	if ( (_x1.get() == x && _y1.get() == y) ||
	     (_x2.get() == x && _y2.get() == y) )
		return TRUE;
	else
		return FALSE;
}

BOOL Line::checkNear(int x,int y)
{
	if (TwoPointFigure::checkNear(x,y)) {
		invertDir();
		return TRUE;
	} else {
		return FALSE;
	}
}

void Line::setArrow(int popupX,int popupY) 
{
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (distance(popupX,popupY,x1,y1) < distance(popupX,popupY,x2,y2)) {
		if (_direct == NODIR) {
			_direct = INVERT_DIR;
		} else if (_direct == NORMAL_DIR) {
			_direct = BIDIR;
		} else if (_direct == INVERT_DIR) {
			_direct = NODIR;
		} else if (_direct == BIDIR) {
			_direct = NORMAL_DIR;
		}
	} else {
		if (_direct == NODIR) {
			_direct = NORMAL_DIR;
		} else if (_direct == NORMAL_DIR) {
			_direct = NODIR;
		} else if (_direct == INVERT_DIR) {
			_direct = BIDIR;
		} else if (_direct == BIDIR) {
			_direct = INVERT_DIR;
		}
	}
}

void Line::swapPoints()
{
	TwoPointFigure::swapPoints();
	invertDir();
}

void Line::invertDir()
{
	if (_direct == NODIR || _direct == BIDIR) return;
	if (_direct == NORMAL_DIR)
		_direct = INVERT_DIR;
	else
		_direct = NORMAL_DIR;
}

BOOL Line::isObsolete()
{
	if (_x1.get() == _x2.get() && _y1.get() == _y2.get()) {
		return TRUE;
	} else {
		return FALSE;
	}
}

BOOL Line::checkToMerge(Line *node)
{
	int head1 = _head;
	int head2 = node->_head;
	int orient1 = orient();
	int orient2 = node->orient();
	if (orient1 != UNDEFINED && orient2 != UNDEFINED) {
		if (orient1 != orient2) return FALSE;
		if (_x1.get() == _x2.get() && 
			_x1.get() == node->_x1.get() && 
			node->_x1.get() == node->_x2.get()) 
			return TRUE;
		if (_y1.get() == _y2.get() && 
			_y1.get() == node->_y1.get() && 
			node->_y1.get() == node->_y2.get()) 
			return TRUE;
		return FALSE;
	}
	if (_type == STRAIGHT) return FALSE;
	double slope1 = slope();
	double slope2 = node->slope();
	double ratio;
	ratio = (slope1 - slope2);
	double tolerance = 0.02;
	if (ratio > -tolerance && ratio < tolerance)
		return TRUE;
	else
		return FALSE;
}

double Line::slope()
{
	int w = _x2.get() - _x1.get();
	int h = _y2.get() - _y1.get();
	_slope = w ? atan(double(h)/double(w)) : sign(h)*M_PI/2.;
	return _slope;
}

void Line::merge(Line *node)
{
	if (_x2.get() == node->_x1.get() && _y2.get() == node->_y1.get()) {
		if (_direct == BIDIR || node->_direct == BIDIR ||
			(_direct == INVERT_DIR && node->_direct == NORMAL_DIR)) {
			_direct = BIDIR;
		} else if ((_direct == NODIR && node->_direct == NODIR) ||
			(_direct == NORMAL_DIR && node->_direct == INVERT_DIR)) {
			_direct = NODIR;
		} else if (_direct == NORMAL_DIR || node->_direct == NORMAL_DIR) {
			_direct = NORMAL_DIR;
		} else {
			_direct = INVERT_DIR;
		}
		_x2.set(node->_x2.get());
		_y2.set(node->_y2.get());
	} else if (_x2.get() == node->_x2.get() && _y2.get() == node->_y2.get()) {
		if (_direct == BIDIR || node->_direct == BIDIR ||
			(_direct == INVERT_DIR && node->_direct == INVERT_DIR)) {
			_direct = BIDIR;
		} else if ((_direct == NODIR && node->_direct == NODIR) ||
			(_direct == NORMAL_DIR && node->_direct == NORMAL_DIR)) {
			_direct = NODIR;
		} else if (_direct == NORMAL_DIR || 
			(_direct == NODIR && node->_direct == INVERT_DIR)) {
			_direct = NORMAL_DIR;
		} else {
			_direct = INVERT_DIR;
		}
		_x2.set(node->_x1.get());
		_y2.set(node->_y1.get());
	} else if (_x1.get() == node->_x1.get() && _y1.get() == node->_y1.get()) {
		if (_direct == BIDIR || node->_direct == BIDIR ||
			(_direct == NORMAL_DIR && node->_direct == NORMAL_DIR)) {
			_direct = BIDIR;
		} else if ((_direct == NODIR && node->_direct == NODIR) ||
			(_direct == INVERT_DIR && node->_direct == INVERT_DIR)) {
			_direct = NODIR;
		} else if (_direct == NORMAL_DIR || 
			(_direct == NODIR && node->_direct == INVERT_DIR)) {
			_direct = NORMAL_DIR;
		} else {
			_direct = INVERT_DIR;
		}
		_x1.set(node->_x2.get());
		_y1.set(node->_y2.get());
	} else if (_x1.get() == node->_x2.get() && _y1.get() == node->_y2.get()) {
		if (_direct == BIDIR || node->_direct == BIDIR ||
			(_direct == NORMAL_DIR && node->_direct == INVERT_DIR)) {
			_direct = BIDIR;
		} else if ((_direct == NODIR && node->_direct == NODIR) ||
			(_direct == INVERT_DIR && node->_direct == NORMAL_DIR)) {
			_direct = NODIR;
		} else if (_direct == NORMAL_DIR || 
			(_direct == NODIR && node->_direct == NORMAL_DIR)) {
			_direct = NORMAL_DIR;
		} else {
			_direct = INVERT_DIR;
		}
		_x1.set(node->_x1.get());
		_y1.set(node->_y1.get());
	}
	if (_head == HEADARROW1 || node->_head == HEADARROW1)
		_head = HEADARROW1;
	else if (_head == HEADARROW2 || node->_head == HEADARROW2)
		_head = HEADARROW2;
}

int Line::orient()
{
	return _orient;
}

Line *Line::calcForkPoint(int popupX,int popupY,int &newx,int &newy,BOOL &swaped)
{
	swaped = FALSE;
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (x1 == popupX && y1 == popupY) {
		swapPoints();
		newx = popupX,
		newy = popupY;
		swaped = TRUE;
		return NIL;
	}
	if (x2 == popupX && y2 == popupY) {
		newx = popupX;
		newy = popupY;
		return NIL;
	}
	int dist = distance(popupX,popupY,x1,y1);
	int forktolerance = FORKTOLERANCE;
	if (dist <= forktolerance) {
		swapPoints();
		newx = x1;
		newy = y1;
		swaped = TRUE;
		return NIL;
	}
	dist = distance(popupX,popupY,x2,y2);
	if (dist <= forktolerance) {
		newx = x2;
		newy = y2;
		return NIL;
	}
	if (_orient == NORTH) {
		newx = x1;
		newy = popupY;
	} else if (_orient == EAST) {
		newx = popupX;
		newy = y2;
	} else if (x1 == x2) {
		newx = x1;
		newy = popupY;
	} else {
		double s = slope();
		double abss;
		if (s < 0) abss = s + 2 * M_PI;
		else abss = s;
		if ((abss >= 0 && abss <= M_PI/4.) ||
		    (abss >= M_PI*3./4. && abss <= M_PI*5./4.) ||
		    (abss >= M_PI*7./4.)) {
			newx = popupX;
			newy = y1 + irint((popupX-x1)*tan(s));
		} else {
			newx = x1 + irint((popupY-y1)*tan(M_PI/2.-s));
			newy = popupY;
		}
	}
	Line *newline = new Line(_controller,newx,newy,x2,y2,NIL,_type);
	newline->_style = _style;
	newline->_orient = _orient;
	_x2.set(newx);
	_y2.set(newy);
	adjustDirs(newline);
	return newline;
}

void Line::calcForkPoint(int popupX,int popupY,int &newx,int &newy)
{
	newx = -1;
	newy = -1;
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (x1 == popupX && y1 == popupY) {
		newx = popupX,
		newy = popupY;
		return;
	}
	if (x2 == popupX && y2 == popupY) {
		newx = popupX;
		newy = popupY;
		return;
	}
	int dist = distance(popupX,popupY,x1,y1);
	int forktolerance = FORKTOLERANCE;
	if (dist <= forktolerance) {
		newx = x1;
		newy = y1;
		return;
	}
	dist = distance(popupX,popupY,x2,y2);
	if (dist <= forktolerance) {
		newx = x2;
		newy = y2;
		return;
	}
	if (_orient == NORTH) {
		newx = x1;
		newy = popupY;
	} else if (_orient == EAST) {
		newx = popupX;
		newy = y2;
	} else if (x1 == x2) {
		newx = x1;
		newy = popupY;
	} else {
		double s = slope();
		double abss;
		if (s < 0) abss = s + 2 * M_PI;
		else abss = s;
		if ((abss >= 0 && abss <= M_PI/4.) ||
		    (abss >= M_PI*3./4. && abss <= M_PI*5./4.) ||
		    (abss >= M_PI*7./4.)) {
			newx = popupX;
			newy = y1 + irint((popupX-x1)*tan(s));
		} else {
			newx = x1 + irint((popupY-y1)*tan(M_PI/2.-s));
			newy = popupY;
		}
	}
}

Line *Line::calcBreakPoint(int popupX,int popupY,int &newx,int &newy,BOOL &swaped)
{
	center(newx,newy);
	int x1 = _x1.get();
	int y1 = _y1.get();
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (distance(popupX,popupY,x1,y1) < distance(popupX,popupY,x2,y2)) {
		swaped = FALSE;
	} else {
		swaped = TRUE;
	}
	Line *newline = new Line(_controller,newx,newy,x2,y2,NIL,_type);
	newline->_style = _style;
	newline->_orient = _orient;
	_x2.set(newx);
	_y2.set(newy);
	adjustDirs(newline);
	return newline;
}

void Line::adjustDirs(Line *second)
{
	int dir = _direct;
	if (dir == NORMAL_DIR) {
		setDir(NODIR,_head);
		second->setDir(NORMAL_DIR,_head);
	} else if (dir == BIDIR) {
		setDir(INVERT_DIR,_head);
		second->setDir(NORMAL_DIR,_head);
	}
}

void Line::setDir(int dir,int headtype)
{
	_direct = dir;
	_head = headtype;
}

int &Line::head()
{
	return _head;
}

void Line::toggleHead(BOOL uniflag,int popupX,int popupY)
{
//	_head = HEADARROW1;
	if (uniflag) {
		int x1 = _x1.get();
		int y1 = _y1.get();
		int x2 = _x2.get();
		int y2 = _y2.get();
		int dist1 = distance(popupX,popupY,x1,y1);
		int dist2 = distance(popupX,popupY,x2,y2);
		if (dist1 > dist2) {
			_direct = _direct ^ NORMAL_DIR;
		} else {
			_direct = _direct ^ INVERT_DIR;
		}
	} else {
		_direct = _direct ^ BIDIR;
	}
	if (_direct == NODIR) _head = HEADNONE;
}

BOOL Line::checkIfSame(Line *line)
{
	if (_x1.get() == line->_x1.get() && _y1.get() == line->_y1.get() && 
		_x2.get() == line->_x2.get() && _y2.get() == line->_y2.get()) {
		return TRUE;
	} else if (_x1.get() == line->_x2.get() && _y1.get() == line->_y2.get() && 
		_x2.get() == line->_x1.get() && _y2.get() == line->_y1.get()) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int Line::setOrient(int orient)
{
	if (_type == ORDINARY) return UNDEFINED;
	if (orient == RESETORIENT) {
		if (isObsolete()) {
			_orient = UNDEFINED;
		} else if (_x1.get() == _x2.get()) {
			_orient = NORTH;
		} else if (_y1.get() == _y2.get()) {
			_orient = EAST;
		} else {
			_orient = UNDEFINED;
		}
	} else {
		_orient = orient;
	}
	return _orient;
}

BOOL Line::incl(int x,int y)
{
	if (isObsolete()) return FALSE;
   	int x1 = _x1.get();
   	int y1 = _y1.get();
   	int x2 = _x2.get();
   	int y2 = _y2.get();
	if (_orient == NORTH) {
		if (x1 != x || x2 != x) return FALSE;
		if (y1 > y2) {
			if (y1 >= y && y >= y2) return TRUE;
			else return FALSE;
		} else  { // y1 <= y2 
			if (y1 <= y && y <= y2) return TRUE;
			else return FALSE;
		}
	} else if (_orient == EAST) {
		if (y1 != y || y2 != y) return FALSE;
		if (x1 > x2) {
			if (x1 >= x && x >= x2) return TRUE;
			else return FALSE;
		} else { // x1 <= x2 
			if (x1 <= x && x <= x2) return TRUE;
			else return FALSE;
		}
	}
	return FALSE;
}

BOOL Line::incl(Line *aline,int &x,int &y)
{
	if (isObsolete()) return FALSE;
	if (_orient != aline->_orient) return FALSE;
   	int x1 = _x1.get();
   	int y1 = _y1.get();
   	int x2 = _x2.get();
   	int y2 = _y2.get();
	if (_orient == NORTH) {
		if (x1 != x || x2 != x) return FALSE;
		if (y1 > y2) {
			if (y1 > y && y > y2) return TRUE;
			else return FALSE;
		} else if (y1 < y2) {
			if (y1 < y && y < y2) return TRUE;
			else return FALSE;
		} else {
			return FALSE;
		}
	} else if (_orient == EAST) {
		if (y1 != y || y2 != y) return FALSE;
		if (x1 > x2) {
			if (x1 > x && x > x2) return TRUE;
			else return FALSE;
		} else if (x1 < x2) {
			if (x1 < x && x < x2) return TRUE;
			else return FALSE;
		} else {
			return FALSE;
		}
	} else {
		if (_type == STRAIGHT) return FALSE;
		if ((x1 == x2) && (aline->_x1.get() == aline->_x2.get())) {
			if (x1 != x || x2 != x) return FALSE;
			if (y1 > y2) {
				if (y1 >= y && y >= y2) return TRUE;
				else return FALSE;
			} else {
				if (y1 <= y && y <= y2) return TRUE;
				else return FALSE;
			}
		}
		if ((x == x1) && (y == y1)) return TRUE;
		if ((x == x2) && (y == y2)) return TRUE;
		double slope = _slope;
		double absslope;
		if (slope < 0) absslope = slope + 2 * M_PI;
		else absslope = slope;
		if ((absslope >= 0 && absslope <= M_PI/4.) ||
		    (absslope >= M_PI*3./4. && absslope <= M_PI*5./4.) ||
		    (absslope >= M_PI*7./4.)) {
			int calc_y = y1 + irint((x-x1)*tan(slope));
			if (abs(calc_y-y) <= 1) {
				if (x1 > x2) {
					if (x1 < x || x < x2) return FALSE;
				} else {
					if (x1 > x || x > x2) return FALSE;
				}
				if (y1 > y2) {
					if (y1 < y || y < y2) return FALSE;
				} else {
					if (y1 > y || y > y2) return FALSE;
				}
				y = calc_y;
				aline->_y2.set(calc_y);
				return TRUE;
			}
		} else {
			int calc_x = x1 + irint((y-y1)*tan(M_PI/2.-slope));
			if (abs(calc_x-x) <= 1) {
				if (x1 > x2) {
					if (x1 < x || x < x2) return FALSE;
				} else {
					if (x1 > x || x > x2) return FALSE;
				}
				if (y1 > y2) {
					if (y1 < y || y < y2) return FALSE;
				} else {
					if (y1 > y || y > y2) return FALSE;
				}
				x = calc_x;
				aline->_x2.set(calc_x);
				return TRUE;
			}
		}
		return FALSE;
	}
}

void Line::findTriangleStartPoints(int endX,int endY,int &startX,int &startY,int length)
{
	if (_x1.get() == _x2.get()) { // if this is vertical line
		startX = endX;
		if (endY > _y2.get()) {
			startY = endY - length;
		} else if (endY < _y2.get()) {
			startY = endY + length;
		} else if (endY > _y1.get()) {
			startY = endY - length;
		} else if (endY < _y1.get()) {
			startY = endY + length;
		} else {
			startY = endY - length;
		}
	} else {
		double deltax,deltay;
		double angle;
		if (endX == _x1.get() && endY == _y1.get()) {
			deltax = (double)(_x2.get() - _x1.get());
			deltay = (double)(_y2.get() - _y1.get());
		} else if (endX == _x2.get() && endY == _y2.get()) {
			deltax = (double)(_x1.get() - _x2.get());
			deltay = (double)(_y1.get() - _y2.get());
		}
		angle = atan(deltay/deltax);
		startX = endX + sign(deltax)*irint(length * cos(angle));
		startY = endY + sign(deltax)*irint(length * sin(angle));
	}
}

void Line::findDiamondEndCorners(int &endX,int &endY,int &startX,int &startY,int length,int offset)
{
	if (_x1.get() == _x2.get()) { // if this is vertical line
		startX = endX;
		if (endY > _y2.get()) {
			startY = endY - length;
		} else if (endY < _y2.get()) {
			startY = endY + length;
		} else if (endY > _y1.get()) {
			startY = endY - length;
		} else if (endY < _y1.get()) {
			startY = endY + length;
		} else {
			startY = endY - length;
		}
		checkPoints(startX,startY,endX,endY);
		startX = startX - offset;
		endX = endX + offset;
	} else if (_y1.get() == _y2.get()) { // if this is horizontal line
		startY = endY;
		if (endX > _x2.get()) {
			startX = endX - length;
		} else if (endX < _x2.get()) {
			startX = endX + length;
		} else if (endX > _x1.get()) {
			startX = endX - length;
		} else if (endX < _x1.get()) {
			startX = endX + length;
		}
		checkPoints(startX,startY,endX,endY);
		startY = startY - offset;
		endY = endY + offset;
	} else {
		startX = endX;
		startY = endY;
	}
}

int Line::type()
{
	return _type;
}

int Line::invertOrient(int orient)
{
	if (orient == NORTH) {
		return EAST;
	} else if (orient == EAST) {
		return NORTH;
	} else /* UNDEFINED */ {
		return UNDEFINED;
	}
}

BOOL Line::moveProlog(BOOL moveAllFlag)
{
	resetHotXY();
	return TRUE;
}