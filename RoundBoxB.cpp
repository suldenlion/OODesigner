#include "stdafx.h"
/* RoundBoxB.C */

#include "RoundBoxB.h"
// Super Class : TwoPointFigure

#include "COODView.h" // Collaboration

IMPLEMENT_SERIAL(RoundBoxB,TwoPointFigure,1)

BOOL RoundBoxB::setFollowing2(int x,int y)  // 2014 danger
{
	_hotX = &_x2;
	_hotY = &_y2;
	return TRUE;
}

RoundBoxB::~RoundBoxB()
{
	// Empty
}

void RoundBoxB::Serialize(CArchive& ar)
{
	TwoPointFigure::Serialize(ar);
}

void RoundBoxB::makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn)
{
	if (_region) delete _region;
    _region = _controller->makeRectRegion(x,y,w,h);
	if (_clip) delete _clip;
//    _clip = _controller->makeRectRegion(x,y,w+1,h+1);
	_clip = createRegion();
	_clip->CopyRgn(sourceClipRgn);
}

void RoundBoxB::drawRoundBox(CDC* dcp,int x,int y,int width,int height)
{
	if (width < ROUNDBOXBGAP || height < ROUNDBOXBGAP) {
		dcp->Rectangle(x,y,x+width+1,y+height+1);
		return;
	}
	dcp->RoundRect(x,y,x+width+1,y+height+1,ROUNDBOXBGAP,ROUNDBOXBGAP);
}

RoundBoxB::RoundBoxB()
: TwoPointFigure()
{
}

RoundBoxB::RoundBoxB(COODView *controller,int x,int y,Popup* popup)
: TwoPointFigure(controller,x,y)
{
	_popup = popup;
}

RoundBoxB::RoundBoxB(COODView *controller,int x1,int y1,int x2,int y2,Popup* popup)
: TwoPointFigure(controller,x1,y1,x2,y2)
{
	_popup = popup;
}

void RoundBoxB::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = abs(_x2.get() - _x1.get());
	int height = abs(_y2.get() - _y1.get());
	if (_x1.get() > _x2.get() ) x = _x2.get();
	else x = _x1.get();
	if (_y1.get() > _y2.get() ) y = _y2.get();
	else y = _y1.get();
	if (_filled == TRUE) {
		int mode = dcp->GetROP2();
		if (mode != R2_NOTXORPEN) {
			CBrush brush(_background);
			CBrush *oldBrush = dcp->SelectObject(&brush);
			drawRoundBox(dcp,x,y,width,height);
			dcp->SelectObject(oldBrush);
		} else {
			drawRoundBox(dcp,x,y,width,height);
		}
	} else {
		drawRoundBox(dcp,x,y,width,height);
	}
}

void RoundBoxB::drawBoundary(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = abs(_x2.get() - _x1.get());
	int height = abs(_y2.get() - _y1.get());
	if (_x1.get() > _x2.get() ) x = _x2.get();
	else x = _x1.get();
	if (_y1.get() > _y2.get() ) y = _y2.get();
	else y = _y1.get();
	drawRoundBox(dcp,x,y,width,height);
}

UnsignedLong *RoundBoxB::whoAreYou()
{
	return IAMROUNDBOXB; 
}

Figure* RoundBoxB::born(Figure* ptr)
{
	RoundBoxB *copied;
	if (ptr == NIL) {
		copied = new RoundBoxB(NIL,0,0,NIL);
	} else {
		copied = (RoundBoxB *)ptr;
	}
	return (TwoPointFigure::born((Figure *)copied));
}

void RoundBoxB::makeRegion(CRgn *sourceClipRgn)
{
	makeRegion(_x1.get(),_y1.get(),_x2.get()-_x1.get(),_y2.get()-_y1.get(),sourceClipRgn);
}

