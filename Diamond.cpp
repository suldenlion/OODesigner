#include "stdafx.h"
/* Diamond.C */

#include "Diamond.h"

#include "COODView.h" // Collaboration

IMPLEMENT_SERIAL(Diamond,TwoPointFigure,1)

Diamond::~Diamond()
{
	// empty
}

void Diamond::makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn)
{
	_points[0].x = x + w / 2;
	_points[0].y = y;
	_points[1].x = x;
	_points[1].y = y + h / 2;
	_points[2].x = x + w / 2;
	_points[2].y = y + h;
	_points[3].x = x + w;
	_points[3].y = y + h / 2;
	if (_region) delete _region;
	_region = _controller->createPolygonRegion(_points,4);
}

Diamond::Diamond()
: TwoPointFigure()
{
}

Diamond::Diamond(COODView *controller,int x,int y,Popup* popup)
: TwoPointFigure(controller,x,y)
{
	_popup = popup;
}

Diamond::Diamond(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup)
: TwoPointFigure(controller,x1,y1,x2,y2)
{
	_popup = popup;
}

void Diamond::Serialize(CArchive& ar)
{
	TwoPointFigure::Serialize(ar);
}

void Diamond::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int width = _x2.get() - _x1.get();
	int height = _y2.get() - _y1.get();
	int dx = width/2;
	int dy = height/2;
	int mode = dcp->GetROP2();
	if (_filled == TRUE) {
		makeRegion(_controller->canvasRgn());
		dcp->FillRgn(_region,COODView::PlainBrush);
		if (mode == R2_NOTXORPEN) {
			if (width < height) {
				DrawLine(dcp,_x1.get()+dx,_y1.get(),_x1.get()+dx,_y2.get());
			} else {
				DrawLine(dcp,_x1.get(),_y1.get()+dy,_x2.get(),_y1.get()+dy);
			}
		}
	} else {
		if (mode != R2_NOTXORPEN) {
			CPen *oldPen = dcp->SelectObject(COODView::ErasePen);
			DrawLine(dcp,_x1.get()+dx,_y1.get(),_x1.get()+dx,_y2.get());
			DrawLine(dcp,_x1.get(),_y1.get()+dy,_x2.get(),_y1.get()+dy);
			dcp->SelectObject(oldPen);
		} else {
			if (width < height) {
				DrawLine(dcp,_x1.get()+dx,_y1.get(),_x1.get()+dx,_y2.get());
			} else {
				DrawLine(dcp,_x1.get(),_y1.get()+dy,_x2.get(),_y1.get()+dy);
			}
		}
		DrawLine(dcp,_x1.get()+dx,_y1.get(),_x1.get(),_y1.get()+dy);
		DrawLine(dcp,_x1.get(),_y1.get()+dy,_x1.get()+dx,_y2.get());
		DrawLine(dcp,_x1.get()+dx,_y2.get(),_x2.get(),_y1.get()+dy);
		DrawLine(dcp,_x2.get(),_y1.get()+dy,_x1.get()+dx,_y1.get());
	}
}

UnsignedLong *Diamond::whoAreYou()
{
	return IAMDIAMOND;
}

Figure* Diamond::born(Figure* ptr)
{
	Diamond *copied;
	if (ptr == NIL) {
		copied = new Diamond(NIL,0,0,NIL);
	} else {
		copied = (Diamond *)ptr;
	}
	return (TwoPointFigure::born((Figure *)copied));
}

void Diamond::makeRegion(CRgn *sourceClipRgn)
{
	makeRegion(_x1.get(),_y1.get(),_x2.get()-_x1.get(),_y2.get()-_y1.get(),sourceClipRgn);
}

