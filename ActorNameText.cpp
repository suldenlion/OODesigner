// ActorNameText.cpp: implementation of the ActorNameText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ActorNameText.h"
#include "Actor.h"
#include "COODView.h"
#include "VTerm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ActorNameText,Text,1)

ActorNameText::ActorNameText()
: Text()
{
	_master = NIL;
}

ActorNameText::ActorNameText(COODView *controller,Actor *master,int ox,int oy,Popup *popup)
: Text(controller,ox,oy,popup)
{
	_master = master;
	setBoldFont(TRUE);
	setMaxLines(2);
}

ActorNameText::~ActorNameText()
{
	_master = NIL;
}

void ActorNameText::Serialize(CArchive& ar)
{
	Text::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _master;
	} else {
		ar >> _master;
	}
}

UnsignedLong *ActorNameText::whoAreYou()
{
	return IAMACTORNAMETEXT; 
}

Figure* ActorNameText::born(Figure* ptr)
{
	ActorNameText *copied;
	if (ptr == NIL) {
		copied = new ActorNameText(NIL,NIL,0,0,NIL);
	} else {
		copied = (ActorNameText *)ptr;
	}
	return (Text::born((Figure *)copied));
}

BOOL ActorNameText::shouldBeDeleted()
{
	return FALSE;
}

void ActorNameText::bye()
{
	Text::bye();
	int masterCx,masterCy;
	int thisCx,thisCy;
	_master->center(masterCx,masterCy);
	center(thisCx,thisCy);
	CRect tmp(_x1.get(),_y1.get(),_x2.get()+1,_y2.get()+1);
	_controller->invalidateRect(&tmp,TRUE);
	int delta = masterCx - thisCx;
	moveCoord(delta,0);
	makeRegion(_controller->canvasRgn());
}

void ActorNameText::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	if (_controller->editingTag() == TRUE &&
		_controller->currentFocus() == _master) {
		Text::draw(dcp);
		return;
	}
	centering(dcp,_x1.get(),abs(_x2.get()-_x1.get()));
}

void ActorNameText::adjustXY1Coord()
{
	_controller->clear(this);
	int x1 = getX1();
	int y1 = getY1();
	int x2 = getX2();
	int y2 = getY2();
	int width = x2-x1;
	int cx,cy;
	_master->shape()->center(cx,cy);
	int newX1 = cx - width/2;
	int newY1 = _master->shape()->getY2() + NAMETEXTGAP;
	recalcCoordFromXY1(newX1,newY1);
	_controller->draw(this);
	_vterm->activate();
}

BOOL ActorNameText::delChar()
{
	int oldX2 = getX2();
	BOOL returnVal = Text::delChar();
	if (oldX2 == getX2()) return returnVal;
	adjustXY1Coord();
	return returnVal;
}

BOOL ActorNameText::delCharBack()
{
	int oldX2 = getX2();
	BOOL returnVal = Text::delCharBack();
	if (oldX2 == getX2()) return returnVal;
	adjustXY1Coord();
	return returnVal;
}

BOOL ActorNameText::delLine()
{
	int oldX2 = getX2();
	BOOL returnVal = Text::delLine();
	if (oldX2 == getX2()) return returnVal;
	adjustXY1Coord();
	return returnVal;
}

void ActorNameText::goNextLine()
{
	int oldX2 = getX2();
	Text::goNextLine();
	if (oldX2 == getX2()) return;
	adjustXY1Coord();
}

int ActorNameText::insert(char* keypressed)
{
	int oldX2 = getX2();
	int returnVal = Text::insert(keypressed);
	if (oldX2 == getX2()) return returnVal;
	adjustXY1Coord();
	return returnVal;
}
