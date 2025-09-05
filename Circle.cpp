// Circle.cpp: implementation of the Circle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Circle.h"
#include "FigureList.h" // Collaboration
#include "COODView.h" // Collaboration
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Circle,TwoPointFigure,1)

BOOL Circle::setFollowing2(int x,int y)  // 2014 danger
{
	_hotX = &_x2;
	_hotY = &_y2;
	return TRUE;
}

Circle::~Circle()
{

}

void Circle::makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn)
{
	if (_region) delete _region;
    _region = _controller->makeRectRegion(x,y,w,h);
	if (_clip) delete _clip;
//    _clip = _controller->makeRectRegion(x,y,w+1,h+1);
	_clip = createRegion();
	_clip->CopyRgn(sourceClipRgn);
}

Circle::Circle()
: TwoPointFigure()
{
}

Circle::Circle(COODView *controller,int x,int y,Popup *popup)
: TwoPointFigure(controller,x,y)
{
	_popup = popup;
}

Circle::Circle(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup)
: TwoPointFigure(controller,x1,y1,x2,y2)
{
	_popup = popup;
}

void Circle::Serialize(CArchive& ar)
{
	TwoPointFigure::Serialize(ar);
}

void Circle::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = abs(_x2.get() - _x1.get());
	int height = abs(_y2.get() - _y1.get());
	if (_x1.get() > _x2.get()) x = _x2.get();
	else x = _x1.get();
	if (_y1.get() > _y2.get() ) y = _y2.get();
	else y = _y1.get();

	int cx = x + width/2;
	int cy = y + height/2;

	CPoint centerPoint(cx,cy);
	CPoint scaledWH(width,height);
	dcp->LPtoDP(&scaledWH);

	CPoint oldViewportOrg;
	CPoint oldWindowOrg;
	if (dcp->IsKindOf(RUNTIME_CLASS(CPaintDC))) {
		dcp->LPtoDP(&centerPoint);
		oldViewportOrg = dcp->SetViewportOrg(centerPoint.x,centerPoint.y);
	}
	width = scaledWH.x;
	height = scaledWH.y;
	if (_filled == TRUE) {
		CBrush brush(_background);
		CBrush *oldBrush; 
		int mode = dcp->GetROP2();
		if (mode != R2_NOTXORPEN)
			oldBrush = dcp->SelectObject(&brush);
		if (dcp->IsKindOf(RUNTIME_CLASS(CPaintDC))) {
			dcp->Ellipse(-width/2,-height/2,width/2,height/2);
		} else if (!dcp->IsKindOf(RUNTIME_CLASS(CClientDC)) &&
				!dcp->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) &&
				!dcp->IsKindOf(RUNTIME_CLASS(CWindowDC))) { // print DC
			dcp->DPtoLP(&scaledWH);
			dcp->Ellipse(centerPoint.x-scaledWH.x/2,centerPoint.y-scaledWH.y/2,
				centerPoint.x+scaledWH.x/2,centerPoint.y+scaledWH.y/2);
		} else { 
			dcp->Ellipse(centerPoint.x-width/2,centerPoint.y-height/2,
				centerPoint.x+width/2,centerPoint.y+height/2);
		}
		if (mode != R2_NOTXORPEN)
			dcp->SelectObject(oldBrush);
	} else {
		if (dcp->IsKindOf(RUNTIME_CLASS(CPaintDC))) {
			dcp->Ellipse(-width/2,-height/2,width/2,height/2);
		} else if (!dcp->IsKindOf(RUNTIME_CLASS(CClientDC)) &&
				!dcp->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) &&
				!dcp->IsKindOf(RUNTIME_CLASS(CWindowDC))) { // print DC
			dcp->DPtoLP(&scaledWH);
			dcp->Ellipse(centerPoint.x-scaledWH.x/2,centerPoint.y-scaledWH.y/2,
				centerPoint.x+scaledWH.x/2,centerPoint.y+scaledWH.y/2);
		} else { 
			dcp->Ellipse(centerPoint.x-width/2,centerPoint.y-height/2,
				centerPoint.x+width/2,centerPoint.y+height/2);
		}
	}
	if (dcp->IsKindOf(RUNTIME_CLASS(CPaintDC))) {
		dcp->SetViewportOrg(oldViewportOrg);
	}
}

void Circle::drawBoundary(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = abs(_x2.get() - _x1.get());
	int height = abs(_y2.get() - _y1.get());
	if (_x1.get() > _x2.get()) x = _x2.get();
	else x = _x1.get();
	if (_y1.get() > _y2.get() ) y = _y2.get();
	else y = _y1.get();

	int cx = x + width/2;
	int cy = y + height/2;
	CPoint centerPoint(cx,cy);
	CPoint scaledWH(width,height);
	dcp->LPtoDP(&scaledWH);

	CPoint oldViewportOrg;
	CPoint oldWindowOrg;
	if (dcp->IsKindOf(RUNTIME_CLASS(CPaintDC))) {
		dcp->LPtoDP(&centerPoint);
		oldViewportOrg = dcp->SetViewportOrg(centerPoint.x,centerPoint.y);
	}
	width = scaledWH.x;
	height = scaledWH.y;
	if (dcp->IsKindOf(RUNTIME_CLASS(CPaintDC))) {
		dcp->Ellipse(-width/2,-height/2,width/2,height/2);
	} else if (!dcp->IsKindOf(RUNTIME_CLASS(CClientDC)) &&
			!dcp->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) &&
			!dcp->IsKindOf(RUNTIME_CLASS(CWindowDC))) { // print DC
		dcp->DPtoLP(&scaledWH);
		dcp->Ellipse(centerPoint.x-scaledWH.x/2,centerPoint.y-scaledWH.y/2,
			centerPoint.x+scaledWH.x/2,centerPoint.y+scaledWH.y/2);
	} else { 
		dcp->Ellipse(centerPoint.x-width/2,centerPoint.y-height/2,
			centerPoint.x+width/2,centerPoint.y+height/2);
	}
	if (dcp->IsKindOf(RUNTIME_CLASS(CPaintDC))) {
		dcp->SetViewportOrg(oldViewportOrg);
	}
}

UnsignedLong *Circle::whoAreYou()
{
	return IAMCIRCLE; 
}

Figure* Circle::born(Figure* ptr)
{
	Circle *copied;
	if (ptr == NIL) {
		copied = new Circle(NIL,0,0,NIL);
	} else {
		copied = (Circle *)ptr;
	}
	return (TwoPointFigure::born((Figure *)copied));
}

void Circle::makeRegion(CRgn *sourceClipRgn)
{
	makeRegion(_x1.get(),_y1.get(),_x2.get()-_x1.get(),_y2.get()-_y1.get(),sourceClipRgn);
}

BOOL Circle::isTroublesomeToModifyObject()
{
	return TRUE;
}

