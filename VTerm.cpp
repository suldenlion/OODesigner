#include "stdafx.h"
/* VTerm.C */

#include "VTerm.h"
// Super Class : None

/*oodB%VTerm*** Global Declarations and Stuffs ****/
#include "Text.h" // Collaboration
#include "TextContent.h" // Collaboration
#include "COODView.h" // Collaboration
/*oodE*********************************************/

IMPLEMENT_SERIAL(VTerm,CObject,1)

VTerm::~VTerm()
{
	// empty
}

void VTerm::drawScaledString(int x,int y,char* str,int len)
{
}

VTerm::VTerm(Text *aText)
: CObject()
{
	_text = aText;
	_cursorX = 0;
	_cursorY = 0;
}

VTerm::VTerm()
:CObject()
{
	_text = NIL;
	_cursorX = 0;
	_cursorY = 0;
}

void VTerm::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);   
	if (ar.IsStoring()) {
		ar << _text << (LONG)_cursorX << (LONG)_cursorY;
	} else {
		ar >> _text >> (LONG&)_cursorX >> (LONG&)_cursorY;
	}
}

COODView *VTerm::controller()
{
	return _text->controller();
}

int VTerm::startX()
{
	return _text->getX1();
}

int VTerm::startY()
{
	return _text->getY1();
}

void VTerm::activate()
{
	int newx = startX() + _cursorX;
	int newy = startY() + _cursorY;
	BOOL moved = controller()->checkLimitForFigure(newx,newy);
	if (moved) {
		newx = startX() + _cursorX;
		newy = startY() + _cursorX;
	}
	controller()->setCaretXY(newx,newy);
}

void VTerm::set(int newx,int newy)
{
	_cursorX = newx; _cursorY = newy;
}

void VTerm::goRel(int dx,int dy)
{
	set(_cursorX+dx,_cursorY+dy);
	activate();
}

void VTerm::goAbs(int x,int y)
{
	set(x,y);
	activate();
}

void VTerm::insert(int newx)
{
	goAbs(newx,_cursorY);
}

void VTerm::goNextLine(int y)
{
	goAbs(0,y);
}

void VTerm::goHome()
{
	goAbs(0,_cursorY);
}

void VTerm::goEnd(int dxfrom0)
{
	goAbs(dxfrom0,_cursorY);
}

void VTerm::goLeft(int dx)
{
	goAbs(dx,_cursorY);
}

void VTerm::goRight(int dx)
{
	goAbs(dx,_cursorY);
}

void VTerm::goUp(int dxfrom0)
{
	goAbs(dxfrom0,_cursorY-_text->deltaV());
}

void VTerm::goDown(int dxfrom0)
{
	goAbs(dxfrom0,_cursorY+_text->deltaV());
}

void VTerm::delChar()
{
	goRel(0,0);
}

void VTerm::delCharBack(int dx)
{
	goAbs(dx,_cursorY);
}

void VTerm::delFirstLine()
{
	goAbs(0,0);
}

void VTerm::delCharBackLine(int dxfrom0,int dyfrom0)
{
	goAbs(dxfrom0,dyfrom0);
}

void VTerm::delLine(int dyfrom0,BOOL moveCaret)
{
	if (moveCaret) goAbs(0,dyfrom0);
	else goRel(0,0);
}

VTerm* VTerm::born()
{
	VTerm *copied = new VTerm(NIL);
	copied->_cursorX = _cursorX;
	copied->_cursorY = _cursorY;
	return copied;
}

void VTerm::setTextPtr(Text *ptr)
{
	_text = ptr;
}
