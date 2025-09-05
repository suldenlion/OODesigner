#include "stdafx.h"
/* YCoord.C */

#include "YCoord.h"
// Super Class : None

#include "common.h"
#include "KtgMacro.h"
#include "COODView.h" // Collaboration

IMPLEMENT_SERIAL(YCoord,CObject,1)

YCoord::YCoord()
: CObject()
{
	_controller = NIL;
	y = 0; 
}

YCoord::YCoord(COODView *controller)
: CObject()
{
	_controller = controller;
	y = 0; 
}

YCoord::YCoord(COODView *controller,int viewY)
: CObject()
{
	_controller = controller;
	y = viewY + _controller->originY(); 
}

YCoord::~YCoord()
{
	_controller = NIL;
}

void YCoord::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);   
	if (ar.IsStoring()) {
		ar << (LONG) y;
	} else {
		ar >> (LONG &) y;
	}
}

void YCoord::setController(COODView *controller)
{
	_controller = controller;
}

void YCoord::set(int viewY) 
{
	if (_controller == NIL) {
		y = viewY;
		return;
	}
	y = viewY + _controller->originY();
}

void YCoord::set(YCoord &c)
{
	_controller = c._controller;
	if (_controller == NIL) {
		y = c.y;
		return;
	}
	y = c.y;
}

int YCoord::get()
{
	if (_controller == NIL) {
		return y;
	}
	return y - _controller->originY();
}


