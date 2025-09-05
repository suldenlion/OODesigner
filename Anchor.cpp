// Anchor.cpp: implementation of the Anchor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Anchor.h"
#include "Note.h"
#include "COODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Anchor,Line,1)

Anchor::Anchor()
: Line()
{
	_note = NIL;
	_style = DOTED;
}

Anchor::Anchor(COODView *controller,Note *note,int x,int y,Popup* popup)
: Line(controller,x,y,popup,ORDINARY)
{
	_note = note;
	_style = DOTED;
}

Anchor::Anchor(COODView *controller,Note *note,int x1,int y1,int x2,int y2,Popup* popup)
: Line(controller,x1,y1,x2,y2,popup,ORDINARY)
{
	_note = note;
	_style = DOTED;
}

Anchor::~Anchor()
{
	_note = NIL;
}

void Anchor::Serialize(CArchive& ar)
{
	Line::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _note;
	} else {
		ar >> _note;
	}
	_style = DOTED; // 이 줄은 2005년도에는 없애도록 할 것
}

Figure* Anchor::born(Figure* ptr)
{
	Anchor *copied;
	if (ptr == NIL) {
		copied = new Anchor(NIL,NIL,0,0,NIL);
	} else {
		copied = (Anchor *)ptr;
	}
	copied->_note = _note;
	return (Line::born((Figure *)copied));
}

UnsignedLong *Anchor::whoAreYou()
{
	return IAMANCHOR; 
}

Figure *Anchor::container()
{
	return (Figure *)_note;
}

void Anchor::eraseDots(CDC* dcp)
{
	if (_dotedFlag == FALSE) return;
	drawDots(dcp);
	int x2 = _x2.get();
	int y2 = _y2.get();
	_controller->clearArea(x2-DOTSIZE/2,y2-DOTSIZE/2,DOTSIZE,DOTSIZE);
	_dotedFlag = FALSE;
}

void Anchor::drawDots(CDC* dcp)
{
	_dotedFlag = TRUE;
	int x2 = _x2.get();
	int y2 = _y2.get();
	dcp->Rectangle(x2-DOTSIZE/2,y2-DOTSIZE/2,x2+DOTSIZE/2,y2+DOTSIZE/2);
}

void Anchor::drawing(CDC* dcp,int dx,int dy)
{
	Line::drawing(dcp,dx,dy);
}

void Anchor::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	Line::draw(dcp);
}

BOOL Anchor::wantToResize(int &x,int &y)
{
	int x2 = _x2.get();
	int y2 = _y2.get();
	if (TwoPointFigure::wantToResize(x,y,x2,y2)) {
		_hotX = &_x2; _hotY = &_y2;
		x = _x2.get(); y = _y2.get();
		return TRUE;
	}
	_hotX = NIL; _hotY = NIL;
	return FALSE;
}