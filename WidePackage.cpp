// WidePackage.cpp: implementation of the WidePackage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "WidePackage.h"
#include "Box.h"
#include "COODView.h"
#include "Text.h"
#include "Line.h"
#include "FigureList.h"
#include "Connection.h"
#include "TextContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define INIT_WIDE_PACKAGE_WIDTH		(300)
#define INIT_WIDE_PACKAGE_HEIGHT	(200)

#define NAME_TEXT_DX (10)
#define NAME_TEXT_DY (10)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(WidePackage,NodeFigure,1)

WidePackage::WidePackage()
: NodeFigure()
{
	_savedX2 = -1;
	_savedY2 = -1;
	_hatLeft = NIL;
	_hatUp = NIL;
	_hatRight = NIL;
	_packageName = NIL;
}

WidePackage::WidePackage(COODView *controller,int ox,int oy,Popup *popup)
: NodeFigure(controller)
{
	_popup = popup;
	_savedX2 = -1;
	_savedY2 = -1;
	if (controller == NIL) return;
	_shape = new Box(controller,ox,oy,
						ox+INIT_WIDE_PACKAGE_WIDTH,
						oy+INIT_WIDE_PACKAGE_HEIGHT,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	NodeFigure::setBackground(theAppPtr->shapeBackgroundColor);
	_packageName = new Text(controller,ox+NAME_TEXT_DX,oy+NAME_TEXT_DY,NIL);
	_packageName->setAutoDelete(FALSE);
	_packageName->setBoldFont(TRUE);
	_packageName->setMaxLines(2);

	// 주의 : _hatLeft,_hatUp,_hatRight를 이 클래스에서 destruction 시키면 안됨
	_hatLeft = new Line(controller,ox,oy-HAT_HEIGHT,ox,oy,NIL,STRAIGHT);
	_hatUp = new Line(controller,ox,oy-HAT_HEIGHT,ox+HAT_WIDTH,oy-HAT_HEIGHT,NIL,STRAIGHT);
	_hatRight = new Line(controller,ox+HAT_WIDTH,oy-HAT_HEIGHT,ox+HAT_WIDTH,oy,NIL,STRAIGHT);
	_decorations->insert(_hatLeft);
	_decorations->insert(_hatUp);
	_decorations->insert(_hatRight);
}

WidePackage::~WidePackage()
{
	if (_packageName != NIL) {
		delete _packageName;
		_packageName = NIL;
	}
}

void WidePackage::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _hatLeft << _hatUp;
		ar << _hatRight << _packageName;
	} else {
		ar >> _hatLeft >> _hatUp;
		ar >> _hatRight >> _packageName;
	}
}

UnsignedLong* WidePackage::whoAreYou()
{
	return IAMWIDEPACKAGE; 
}

Figure* WidePackage::born(Figure* ptr)
{
	WidePackage *copied;
	if (ptr == NIL) {
		copied = new WidePackage(NIL,0,0,NIL);
	} else {
		copied = (WidePackage *)ptr;
	}
	copied->_packageName = (Text *)_packageName->born(NIL);
	return (NodeFigure::born((Figure *)copied));
}

void WidePackage::setSpecificDataMembers()
{
	_hatLeft = (Line *)_decorations->getFirst();
	_hatUp = (Line *)_decorations->getNext();
	_hatRight = (Line *)_decorations->getNext();
}

BOOL WidePackage::wantToResize(int& x,int& y)
{
	if (_shape->wantToResize(x,y)) {
		_savedX2 = _shape->_x2.x;
		_savedY2 = _shape->_y2.y;
		return TRUE;
	}
	_savedX2 = -1;
	_savedY2 = -1;
	_shape->resetHotXY();
	return FALSE;
}

void WidePackage::setInCanvas(BOOL flag)
{
	NodeFigure::setInCanvas(flag);
	_packageName->setInCanvas(flag);
}

void WidePackage::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		int x,y;
		int width = HAT_WIDTH;
		int height = HAT_HEIGHT;
		x = _shape->_x1.get();
		y = _shape->_y1.get() - height;
		CRect rect(x,y,x+width+1,y+height+1);
		CBrush brush(background());
		dcp->FillRect(&rect,&brush);
	}
	NodeFigure::draw(dcp);
	if (_packageName->isEmpty()) return; 
	if (mode != R2_NOTXORPEN) {
		COLORREF oldColor = dcp->SetBkColor(background());
		_packageName->draw(dcp);
		dcp->SetBkColor(oldColor);
	}
}

void WidePackage::drawBoundary(CDC* dcp)
{
	NodeFigure::drawBoundary(dcp);
}

void WidePackage::move(CDC* dcp,int dx,int dy)
{
	NodeFigure::move(dcp,dx,dy);
	_packageName->moveCoord(dx,dy);
}

void WidePackage::moveCoord(int dx,int dy)
{
	NodeFigure::moveCoord(dx,dy);
	_packageName->moveCoord(dx,dy);
}

void WidePackage::setController(COODView *ptr)
{
	NodeFigure::setController(ptr);
	_packageName->setController(ptr);
}

BOOL WidePackage::startEdit()
{
	_focus = _packageName;
	_packageName->startEdit();
	return TRUE;
}

void WidePackage::bye()
{
	if (_focus == NIL) return;
	_packageName->bye();
	return;
}

void WidePackage::epilog(BOOL skipflag)
{
	if (_savedX2 == -1 && _savedY2 == -1) {
		NodeFigure::epilog(skipflag);
		_shape->arrangeXY12();
		_packageName->recalcCoordFromXY1(_shape->getX1()+NAME_TEXT_DX,
									_shape->getY1()+NAME_TEXT_DY);
		return;
	}
	if (_shape->hotX() == NIL || _shape->hotY() == NIL) {
		NodeFigure::epilog(skipflag);
		_shape->arrangeXY12();
		_packageName->recalcCoordFromXY1(_shape->getX1()+NAME_TEXT_DX,
									_shape->getY1()+NAME_TEXT_DY);
		return;
	}
	int nameW = _packageName->content()->otherLinesMaxWidth();
	int limitX = _hatLeft->_x1.x + nameW + 4;
	int limitY = _hatLeft->_y2.y + 20;
	int lastX = _shape->hotX()->x;
	int lastY = _shape->hotY()->y;
	if (lastX < limitX ||
		lastY < limitY) {
		_controller->beep("Resizing aborted.");
		_shape->_x1.x = _hatLeft->_x1.x;
		_shape->_y1.y = _hatLeft->_y2.y;
		_shape->_x2.x = _savedX2;
		_shape->_y2.y = _savedY2;
		_savedX2 = -1;
		_savedY2 = -1;
		_controller->Invalidate();
		return;
	}
	_savedX2 = -1;
	_savedY2 = -1;
	makeRegion(_controller->canvasRgn());
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->extendToNodeFigure(this);
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->tailorEndLinesAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setModelSpecificSymbolAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->makeRegion(_controller->canvasRgn());
		ptr = _connections->getNext();
	}
	_controller->Invalidate();
}


