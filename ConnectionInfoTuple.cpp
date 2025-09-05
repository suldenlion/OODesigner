// ConnectionInfoTuple.cpp: implementation of the ConnectionInfoTuple class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ConnectionInfoTuple.h"

#include "Line.h" // Collaboration
#include "NodeFigure.h" // Collaboration
#include "COODView.h" // Collaboration

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ConnectionInfoTuple,CObject,1)

ConnectionInfoTuple::~ConnectionInfoTuple()
{
	_nodeFigurePtr = NIL;
}

void ConnectionInfoTuple::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	_x.Serialize(ar);
	_y.Serialize(ar);
	_sx.Serialize(ar);
	_sy.Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _mark;
		ar << _nodeFigurePtr;
	} else {
		ar >> (LONG&) _mark;
		ar >> _nodeFigurePtr;
	}
}

ConnectionInfoTuple::ConnectionInfoTuple()
: CObject()
{
	_nodeFigurePtr = NIL;
	_mark = FALSE;
}

ConnectionInfoTuple::ConnectionInfoTuple(NodeFigure* nodePtr,int x,int y)
: CObject()
{
	_nodeFigurePtr = nodePtr;
	_mark = FALSE;
	if (nodePtr == NIL) return;
	COODView *controller = nodePtr->controller();
	if (controller == NIL) return;
	_x.setController(controller);
	_y.setController(controller);
	_x.set(x);
	_y.set(y);
	_sx.set(_x);
	_sy.set(_y);
}

ConnectionInfoTuple::ConnectionInfoTuple(ConnectionInfoTuple* from)
: CObject()
{
	_nodeFigurePtr = from->_nodeFigurePtr;
	_x.set(from->_x);
	_y.set(from->_y);
	_sx.set(_x);
	_sy.set(_y);
	_mark = FALSE;
}

NodeFigure*& ConnectionInfoTuple::nodeFigurePtr()
{
	return _nodeFigurePtr;
}

void ConnectionInfoTuple::setController(COODView *ptr)
{
	_x.setController(ptr);
	_y.setController(ptr);
	_sx.setController(ptr);
	_sy.setController(ptr);
}

int ConnectionInfoTuple::getX()
{
	return _x.get();
}

int ConnectionInfoTuple::getY()
{
	return _y.get();
}

BOOL& ConnectionInfoTuple::mark()
{
	return _mark;
}

void ConnectionInfoTuple::setX(int x)
{
	_x.set(x);
}

void ConnectionInfoTuple::setY(int y)
{
	_y.set(y);
}

void ConnectionInfoTuple::setXY(int x,int y)
{
	_x.set(x); _y.set(y);
}

BOOL ConnectionInfoTuple::meet(Line* aline)
{
	int x1,y1,x2,y2;
	aline->coords(x1,y1,x2,y2);
	if (x1 == _x.get() && y1 == _y.get()) return TRUE;
	if (x2 == _x.get() && y2 == _y.get()) return TRUE;
	return FALSE;
}

BOOL ConnectionInfoTuple::meet(int x,int y)
{
	if (x == _x.get() && y == _y.get()) return TRUE;
	return FALSE;
}

void ConnectionInfoTuple::moveCoord(int dx,int dy)
{
	_x.x = _x.x + dx; _y.y = _y.y + dy;
}

void ConnectionInfoTuple::move(CDC* dcp,int dx,int dy)
{
	moveCoord(dx,dy);
}

