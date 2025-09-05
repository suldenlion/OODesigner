// SystemBoundary.cpp: implementation of the SystemBoundary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SystemBoundary.h"
#include "Box.h"
#include "COODView.h"
#include "Text.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define INIT_SYSTEM_BOUNDARY_WIDTH	(100)
#define INIT_SYSTEM_BOUNDARY_HEIGHT (150)

#define NAME_TEXT_DX (10)
#define NAME_TEXT_DY (10)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SystemBoundary,NodeFigure,1)

SystemBoundary::SystemBoundary()
: NodeFigure()
{
	_systemName = NIL;
}

SystemBoundary::SystemBoundary(COODView *controller,int ox,int oy,Popup *popup)
: NodeFigure(controller)
{
	_popup = popup;
	if (controller == NIL) return;
	_shape = new Box(controller,ox,oy,
						ox+INIT_SYSTEM_BOUNDARY_WIDTH,
						oy+INIT_SYSTEM_BOUNDARY_HEIGHT,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	NodeFigure::setBackground(theAppPtr->shapeBackgroundColor);
	_systemName = new Text(controller,ox+NAME_TEXT_DX,oy+NAME_TEXT_DY,NIL);
	_systemName->setAutoDelete(FALSE);
	_systemName->setBoldFont(TRUE);
	_systemName->setMaxLines(2);
}

SystemBoundary::~SystemBoundary()
{
	if (_systemName != NIL) {
		delete _systemName;
		_systemName = NIL;
	}
}

void SystemBoundary::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _systemName;
	} else {
		ar >> _systemName;
	}
}

UnsignedLong* SystemBoundary::whoAreYou()
{
	return IAMSYSTEMBOUNDARY; 
}

Figure* SystemBoundary::born(Figure* ptr)
{
	SystemBoundary *copied;
	if (ptr == NIL) {
		copied = new SystemBoundary(NIL,0,0,NIL);
	} else {
		copied = (SystemBoundary *)ptr;
	}
	copied->_systemName = (Text *)_systemName->born(NIL);
	return (NodeFigure::born((Figure *)copied));
}

BOOL SystemBoundary::wantToResize(int& x,int& y)
{
	return _shape->wantToResize(x,y);
}

void SystemBoundary::setInCanvas(BOOL flag)
{
	NodeFigure::setInCanvas(flag);
	_systemName->setInCanvas(flag);
}

void SystemBoundary::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	NodeFigure::draw(dcp);
	if (_systemName->isEmpty()) return; 
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		COLORREF oldColor = dcp->SetBkColor(background());
		_systemName->draw(dcp);
		dcp->SetBkColor(oldColor);
	}
}

void SystemBoundary::drawBoundary(CDC* dcp)
{
	NodeFigure::drawBoundary(dcp);
}

void SystemBoundary::move(CDC* dcp,int dx,int dy)
{
	NodeFigure::move(dcp,dx,dy);
	_systemName->moveCoord(dx,dy);
}

void SystemBoundary::moveCoord(int dx,int dy)
{
	NodeFigure::moveCoord(dx,dy);
	_systemName->moveCoord(dx,dy);
}

void SystemBoundary::setController(COODView *ptr)
{
	NodeFigure::setController(ptr);
	_systemName->setController(ptr);
}

BOOL SystemBoundary::startEdit()
{
	_focus = _systemName;
	_systemName->startEdit();
	return TRUE;
}

void SystemBoundary::bye()
{
	if (_focus == NIL) return;
	_systemName->bye();
	return;
}

void SystemBoundary::epilog(BOOL skipflag)
{
	if (skipflag) return;
	BOOL modified = _shape->arrangeXY12();
	_systemName->recalcCoordFromXY1(_shape->getX1()+NAME_TEXT_DX,
									_shape->getY1()+NAME_TEXT_DY);
}
