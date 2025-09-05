// InterfacePort.cpp: implementation of the InterfacePort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "InterfacePort.h"
#include "Line.h"
#include "Circle.h"
#include "InterfacePortText.h"
#include "ClassTemplate.h"
#include "COODView.h"

#define TEXT_DY (-(INTERFACE_PORT_DELTA_Y-8))

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define LINE_LEN	(30)
#define HOLE_SIZE	(6)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(InterfacePort,ConnectionInfoTuple,1)

InterfacePort::InterfacePort()
: ConnectionInfoTuple()
{
	_interfaceName = NIL;
	_line = NIL;
	_hole = NIL;
}

InterfacePort::InterfacePort(COODView *controller,NodeFigure* config,int x,int y)
: ConnectionInfoTuple(config,x,y)
{
	_interfaceName = NIL;
	_line = NIL;
	_hole = NIL;
	_controller = controller;
	if (controller == NIL) return;
	_interfaceName = new InterfacePortText(controller,config,x-LINE_LEN/4,y+TEXT_DY,theAppPtr->theInterfacePortPopup);
	_line = new Line(controller,x-LINE_LEN,y,x,y,NIL,STRAIGHT);
	_hole = new Circle(controller,x-LINE_LEN-2*HOLE_SIZE,y-HOLE_SIZE,
								  x-LINE_LEN,y+HOLE_SIZE,theAppPtr->theInterfacePortPopup);
}


InterfacePort::~InterfacePort()
{
	if (_line != NIL) {
		delete _line;
		_line = NIL;
	}
	if (_hole != NIL) {
		delete _hole;
		_hole = NIL;
	}
	if (_interfaceName != NIL) {
		delete _interfaceName;
		_interfaceName = NIL;
	}
}

void InterfacePort::Serialize(CArchive& ar)
{
	ConnectionInfoTuple::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _interfaceName << _hole;
		ar << _line;
	} else {
		ar >> _interfaceName >> _hole;
		ar >> _line;
		if (_interfaceName != NIL) 
			_interfaceName->setPopupPointer(theAppPtr->theInterfacePortPopup);
		if (_hole != NIL) 
			_hole->setPopupPointer(theAppPtr->theInterfacePortPopup);
	}
}

void InterfacePort::moveCoord(int dx,int dy)
{
	ConnectionInfoTuple::moveCoord(dx,dy);
	if (_interfaceName != NIL) {
		_interfaceName->moveCoord(dx,dy);
	}
	if (_line != NIL) {
		_line->moveCoord(dx,dy);
	}
	if (_hole != NIL) {
		_hole->moveCoord(dx,dy);
	}
}

void InterfacePort::draw(CDC* dcp)
{
	if (_interfaceName != NIL && _interfaceName->isEmpty() == FALSE) {
		_interfaceName->draw(dcp);
	}
	if (_line != NIL) {
		_line->draw(dcp);
	}
	if (_hole != NIL) {
		_hole->draw(dcp);
	}
}

void InterfacePort::makeRegion(CRgn *sourceClipRgn)
{
	if (_interfaceName != NIL && _interfaceName->isEmpty() == FALSE) {
		_interfaceName->makeRegion(sourceClipRgn);
	}
	if (_line != NIL) {
		_line->makeRegion(sourceClipRgn);
	}
	if (_hole != NIL) {
		_hole->makeRegion(sourceClipRgn);
	}
}

void InterfacePort::resetRegion()
{
	if (_interfaceName != NIL) {
		_interfaceName->resetRegion();
	}
	if (_line != NIL) {
		_line->resetRegion();
	}
	if (_hole != NIL) {
		_hole->resetRegion();
	}
}

void InterfacePort::releaseRegion()
{
	if (_interfaceName != NIL) {
		_interfaceName->releaseRegion();
	}
	if (_line != NIL) {
		_line->releaseRegion();
	}
	if (_hole != NIL) {
		_hole->releaseRegion();
	}
}

void InterfacePort::move(CDC* dcp,int dx,int dy)
{
	ConnectionInfoTuple::moveCoord(dx,dy);
	if (_interfaceName != NIL) {
		if (_interfaceName->isEmpty()) {
			_interfaceName->moveCoord(dx,dy);
		} else {
			_interfaceName->move(dcp,dx,dy);
		}
	}
	if (_line != NIL) {
		_line->move(dcp,dx,dy);
	}
	if (_hole != NIL) {
		_hole->move(dcp,dx,dy);
	}
}

void InterfacePort::drawDots(CDC* dcp)
{
	if (_interfaceName != NIL && _interfaceName->isEmpty() == FALSE) {
		_interfaceName->drawDots(dcp);
	}
	if (_line != NIL) {
		_line->drawDots(dcp);
	}
	if (_hole != NIL) {
		_hole->drawDots(dcp);
	}
}

void InterfacePort::eraseDots(CDC* dcp)
{
	if (_interfaceName != NIL && _interfaceName->isEmpty() == FALSE) {
		_interfaceName->eraseDots(dcp);
	}
	if (_line != NIL) {
		_line->eraseDots(dcp);
	}
	if (_hole != NIL) {
		_hole->eraseDots(dcp);
	}
}

void InterfacePort::clear(CDC *dcp)
{
	if (_interfaceName != NIL) {
		_interfaceName->eraseDots(dcp);
	}
	if (_line != NIL) {
		_line->eraseDots(dcp);
	}
	if (_hole != NIL) {
		_hole->eraseDots(dcp);
	}
}

void InterfacePort::setController(COODView *ptr)
{
	ConnectionInfoTuple::setController(ptr);
	_controller = ptr;
	if (_interfaceName != NIL) {
		_interfaceName->setController(ptr);
	}
	if (_line != NIL) {
		_line->setController(ptr);
	}
	if (_hole != NIL) {
		_hole->setController(ptr);
	}
}

void InterfacePort::setInCanvas(BOOL flag)
{
	if (_interfaceName != NIL) {
		_interfaceName->setInCanvas(flag);
	}
	if (_line != NIL) {
		_line->setInCanvas(flag);
	}
	if (_hole != NIL) {
		_hole->setInCanvas(flag);
	}
}

Figure *InterfacePort::onEnter(int x,int y)
{
	if (_interfaceName != NIL &&
		_interfaceName->isEmpty() == FALSE &&
		_interfaceName->onEnter(x,y)) {
		return _interfaceName;
	}
	if (_hole != NIL &&
		_hole->onEnter(x,y)) {
		return _hole;
	}
	return NIL;
}

void InterfacePort::drawBoundary(CDC *dcp)
{
	if (_interfaceName != NIL && _interfaceName->isEmpty() == FALSE) {
		if (_controller->currentConnection() == NIL)
			_interfaceName->drawBoundary(dcp);
	}
	if (_line != NIL) {
		_line->drawBoundary(dcp);
	}
	if (_hole != NIL) {
		_hole->drawBoundary(dcp);
	}
}

void InterfacePort::removeFromTuple(Figure *fig)
{
	if (_interfaceName == fig) {
		_interfaceName = NIL;
	}
	if (_line == fig) {
		_line = NIL;
	}
	if (_hole == fig) {
		_hole = NIL;
	}
}