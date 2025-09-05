#include "stdafx.h"
/* XCoord.C */

#include "XCoord.h"
// Super Class : None

#include "common.h"
#include "KtgMacro.h"
#include "COODView.h" // Collaboration

IMPLEMENT_SERIAL(XCoord,CObject,1)

XCoord::XCoord()
: CObject()
{
	_controller = NIL;
	x = 0; 
}

XCoord::XCoord(COODView *controller)
: CObject()
{
	_controller = controller;
	x = 0; 
}

XCoord::XCoord(COODView *controller,int viewX)
: CObject()
{
	_controller = controller;
	x = viewX + _controller->originX(); 
}

XCoord::~XCoord()
{
	_controller = NIL;
}

void XCoord::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);   
	if (ar.IsStoring()) {
		ar << (LONG) x;
	} else {
		ar >> (LONG &) x;
	}
}

void XCoord::setController(COODView *controller)
{
	_controller = controller;
}

void XCoord::set(int viewX) 
{
	if (_controller == NIL) {
		x = viewX;
		return;
	}
	x = viewX + _controller->originX();
}

void XCoord::set(XCoord &c)
{
	_controller = c._controller;
	if (_controller == NIL) {
		x = c.x;
		return;
	}
	x = c.x;
}

int XCoord::get()
{
	if (_controller == NIL) {
		return x;
	}
	return x - _controller->originX();
}


