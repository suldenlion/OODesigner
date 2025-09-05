#include "stdafx.h"
/* RoundBoxA.C */

#include "RoundBoxA.h"
// Super Class : TwoPointFigure

#include "COODView.h" // Collaboration

IMPLEMENT_SERIAL(RoundBoxA,TwoPointFigure,1)

BOOL RoundBoxA::setFollowing2(int x,int y)  // 2014 danger
{
	_hotX = &_x2;
	_hotY = &_y2;
	return TRUE;
}

RoundBoxA::~RoundBoxA()
{
	// Empty
}

void RoundBoxA::Serialize(CArchive& ar)
{
	TwoPointFigure::Serialize(ar);
}

void RoundBoxA::makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn)
{
	if (_region) delete _region;
    _region = _controller->makeRectRegion(x,y,w,h);
	if (_clip) delete _clip;
//    _clip = _controller->makeRectRegion(x,y,w+1,h+1);
	_clip = createRegion();
	_clip->CopyRgn(sourceClipRgn);
}

RoundBoxA::RoundBoxA()
: TwoPointFigure()
{
}

RoundBoxA::RoundBoxA(COODView *controller,int x,int y,Popup* popup)
: TwoPointFigure(controller,x,y)
{
	_popup = popup;
}

RoundBoxA::RoundBoxA(COODView *controller,int x1,int y1,int x2,int y2,Popup* popup)
: TwoPointFigure(controller,x1,y1,x2,y2)
{
	_popup = popup;
}

void RoundBoxA::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = abs(_x2.get() - _x1.get());
	int height = abs(_y2.get() - _y1.get());
	if (_x1.get() > _x2.get()) x = _x2.get();
	else x = _x1.get();
	if (_y1.get() > _y2.get() ) y = _y2.get();
	else y = _y1.get();
	if (_filled == TRUE) {
		int mode = dcp->GetROP2();
		if (mode != R2_NOTXORPEN) {
			CBrush brush(_background);
			CBrush *oldBrush = dcp->SelectObject(&brush);
			dcp->RoundRect(x,y,x+width+1,y+height+1,height,height);
			dcp->SelectObject(oldBrush);
		} else {
			dcp->RoundRect(x,y,x+width+1,y+height+1,height,height);
		}
	} else {
		dcp->RoundRect(x,y,x+width+1,y+height+1,height,height);
	}
}

void RoundBoxA::drawBoundary(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = abs(_x2.get() - _x1.get());
	int height = abs(_y2.get() - _y1.get());
	if (_x1.get() > _x2.get()) x = _x2.get();
	else x = _x1.get();
	if (_y1.get() > _y2.get() ) y = _y2.get();
	else y = _y1.get();
	dcp->RoundRect(x,y,x+width+1,y+height+1,height,height);
}

UnsignedLong *RoundBoxA::whoAreYou()
{
	return IAMROUNDBOXA; 
}

Figure* RoundBoxA::born(Figure* ptr)
{
	RoundBoxA *copied;
	if (ptr == NIL) {
		copied = new RoundBoxA(NIL,0,0,NIL);
	} else {
		copied = (RoundBoxA *)ptr;
	}
	return (TwoPointFigure::born((Figure *)copied));
}

void RoundBoxA::makeRegion(CRgn *sourceClipRgn)
{
	makeRegion(_x1.get(),_y1.get(),_x2.get()-_x1.get(),_y2.get()-_y1.get(),sourceClipRgn);
}

BOOL RoundBoxA::isTroublesomeToModifyObject()
{
	return TRUE;
}


