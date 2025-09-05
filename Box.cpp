#include "stdafx.h"
/* Box.C */

#include "Box.h"
// Super Class : TwoPointFigure

#include "FigureList.h" // Collaboration
#include "COODView.h" // Collaboration

IMPLEMENT_SERIAL(Box,TwoPointFigure,1)

Box::~Box()
{
	// Empty
}

BOOL Box::setFollowing2(int x,int y)  // 2014 danger
{
	_hotX = &_x2;
	_hotY = &_y2;
	return TRUE;
}

void Box::makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn)
{
	if (_region) delete _region;
    _region = _controller->makeRectRegion(x,y,w,h);
	if (_clip) delete _clip;
//    _clip = _controller->makeRectRegion(x,y,w+1,h+1);
	_clip = createRegion();
	_clip->CopyRgn(sourceClipRgn);
}

Box::Box()
: TwoPointFigure()
{
}

Box::Box(COODView *controller,int x,int y,Popup *popup)
: TwoPointFigure(controller,x,y)
{
	_popup = popup;
}

Box::Box(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup)
: TwoPointFigure(controller,x1,y1,x2,y2)
{
	_popup = popup;
}

void Box::Serialize(CArchive& ar)
{
	TwoPointFigure::Serialize(ar);
}

void Box::draw(CDC* dcp)
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
			CRect rect(x,y,x+width+1,y+height+1);
			CBrush brush(_background);
			dcp->FillRect(&rect,&brush);
			dcp->Rectangle(x,y,x+width+1,y+height+1);
		} else {
			dcp->Rectangle(x,y,x+width+1,y+height+1);
		}
	} else {
		dcp->Rectangle(x,y,x+width+1,y+height+1);
	}
}

void Box::drawBoundary(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = abs(_x2.get() - _x1.get());
	int height = abs(_y2.get() - _y1.get());
	if (_x1.get() > _x2.get()) x = _x2.get();
	else x = _x1.get();
	if (_y1.get() > _y2.get() ) y = _y2.get();
	else y = _y1.get();
	dcp->Rectangle(x,y,x+width+1,y+height+1);
}

UnsignedLong *Box::whoAreYou()
{
	return IAMBOX; 
}

Figure* Box::born(Figure* ptr)
{
	Box *copied;
	if (ptr == NIL) {
		copied = new Box(NIL,0,0,NIL);
	} else {
		copied = (Box *)ptr;
	}
	return (TwoPointFigure::born((Figure *)copied));
}

void Box::makeRegion(CRgn *sourceClipRgn)
{
	if (_controller == NIL) return;
	makeRegion(_x1.get(),_y1.get(),_x2.get()-_x1.get(),_y2.get()-_y1.get(),sourceClipRgn);
}

void Box::highlightEntries(FigureList *figures,FigureList *containee)
{
	makeRegion(_controller->canvasRgn());
	FigureList *save = new FigureList();
	save->copy(figures);
	Figure *tmp = figures->getFirst();
	while(tmp != NIL) {
        CRgn* region = createRegion();
		region->CombineRgn(_region,tmp->region(),RGN_OR);
        if (_region->EqualRgn(region) && 
			isEmptyRegion(tmp->region()) == FALSE) {
			Figure *more = save->getFirst();
			while(more != NIL) {
				more->visited() = FALSE;
				more = save->getNext();
			}
			BOOL all_included = tmp->checkEntries(_region);
			if (all_included) {
				_controller->highlight(tmp);
				if (containee != NIL) {
					containee->insert(tmp);
				}
			} else {	
				_controller->lowlight(tmp);
			}
		} else {
			_controller->lowlight(tmp);
		}
		delete region;
		tmp = figures->getNext();
	}
	delete save;
}
