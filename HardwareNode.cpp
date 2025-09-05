// HardwareNode.cpp: implementation of the HardwareNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "HardwareNode.h"
#include "Box.h"
#include "COODView.h"
#include "Text.h"
#include "Line.h"
#include "FigureList.h"
#include "Connection.h"
#include "TextContent.h"
#include "ExcludeRect.h"
#include "ExcludeRectList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define GAP_FROM_NODE				(20)
#define INIT_HARDWARE_NODE_WIDTH	(200)
#define INIT_HARDWARE_NODE_HEIGHT	(200)

#define NAME_TEXT_DX (10)
#define NAME_TEXT_DY (10)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(HardwareNode,NodeFigure,1)

HardwareNode::HardwareNode()
: NodeFigure()
{
	_line1 = NIL;
	_line2 = NIL;
	_line3 = NIL;
	_line4 = NIL;
	_line5 = NIL;
	_savedX2 = -1;
	_savedY2 = -1;
	_nodeName = NIL;
}

HardwareNode::HardwareNode(COODView *controller,int ox,int oy,Popup *popup)
: NodeFigure(controller)
{
	_popup = popup;
	_savedX2 = -1;
	_savedY2 = -1;
	if (controller == NIL) return;
	_shape = new Box(controller,ox,oy,
						ox+INIT_HARDWARE_NODE_WIDTH,
						oy+INIT_HARDWARE_NODE_HEIGHT,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	NodeFigure::setBackground(theAppPtr->shapeBackgroundColor);
	_nodeName = new Text(controller,ox+NAME_TEXT_DX,oy+NAME_TEXT_DY,NIL);
	_nodeName->setAutoDelete(FALSE);
	_nodeName->setBoldFont(TRUE);
	_nodeName->setMaxLines(2);

	int x1 = _shape->getX1(); int y1 = _shape->getY1();
	int x2 = _shape->getX2(); int y2 = _shape->getY2();
	_line1 = new Line(controller,x1,y1,x1+GAP_FROM_NODE,y1-GAP_FROM_NODE,NIL,STRAIGHT);
	_line2 = new Line(controller,x1+GAP_FROM_NODE,y1-GAP_FROM_NODE,x2+GAP_FROM_NODE,y1-GAP_FROM_NODE,NIL,STRAIGHT);
	_line3 = new Line(controller,x2+GAP_FROM_NODE,y1-GAP_FROM_NODE,x2+GAP_FROM_NODE,y2-GAP_FROM_NODE,NIL,STRAIGHT);
	_line4 = new Line(controller,x2+GAP_FROM_NODE,y2-GAP_FROM_NODE,x2,y2,NIL,STRAIGHT);
	_line5 = new Line(controller,x2,y1,x2+GAP_FROM_NODE,y1-GAP_FROM_NODE,NIL,STRAIGHT);
	_decorations->insert(_line1);
	_decorations->insert(_line2);
	_decorations->insert(_line3);
	_decorations->insert(_line4);
	_decorations->insert(_line5);
}

HardwareNode::~HardwareNode()
{
	if (_nodeName != NIL) {
		delete _nodeName;
		_nodeName = NIL;
	}
}

void HardwareNode::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _line1 << _line2;
		ar << _line3 << _line4;
		ar << _line5 << _nodeName;
	} else {
		ar >> _line1 >> _line2;
		ar >> _line3 >> _line4;
		ar >> _line5 >> _nodeName;
	}
}

UnsignedLong* HardwareNode::whoAreYou()
{
	return IAMHARDWARENODE; 
}

Figure* HardwareNode::born(Figure* ptr)
{
	HardwareNode *copied;
	if (ptr == NIL) {
		copied = new HardwareNode(NIL,0,0,NIL);
	} else {
		copied = (HardwareNode *)ptr;
	}
	copied->_nodeName = (Text *)_nodeName->born(NIL);
	return (NodeFigure::born((Figure *)copied));
}

void HardwareNode::setSpecificDataMembers()
{
	_line1 = (Line *)_decorations->getFirst();
	_line2 = (Line *)_decorations->getNext();
	_line3 = (Line *)_decorations->getNext();
	_line4 = (Line *)_decorations->getNext();
	_line5 = (Line *)_decorations->getNext();
}

BOOL HardwareNode::wantToResize(int& x,int& y)
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

void HardwareNode::setInCanvas(BOOL flag)
{
	NodeFigure::setInCanvas(flag);
	_nodeName->setInCanvas(flag);
}

void HardwareNode::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		int x1 = _shape->getX1(); int y1 = _shape->getY1();
		int x2 = _shape->getX2(); int y2 = _shape->getY2();
		POINT data[6];
		data[0].x = x1;
		data[0].y = y1;
		data[1].x = x1 + GAP_FROM_NODE;
		data[1].y = y1 - GAP_FROM_NODE;
		data[2].x = x2 + GAP_FROM_NODE;
		data[2].y = y1 - GAP_FROM_NODE;
		data[3].x = x2 + GAP_FROM_NODE;
		data[3].y = y2 - GAP_FROM_NODE;
		data[4].x = x2;
		data[4].y = y2;
		data[5].x = x2;
		data[5].y = y1;
		UINT color = background();
		color = color - 0x001f1f1f;
		CBrush brush(color); 
		CBrush *oldBrush = dcp->SelectObject(&brush);
		FillPolygon(dcp,data,6);
		dcp->SelectObject(oldBrush);
	}
	NodeFigure::draw(dcp);
	if (_nodeName->isEmpty()) return; 
	if (mode != R2_NOTXORPEN) {
		COLORREF oldColor = dcp->SetBkColor(background());
		_nodeName->draw(dcp);
		dcp->SetBkColor(oldColor);
	}
}

void HardwareNode::drawBoundary(CDC* dcp)
{
	NodeFigure::drawBoundary(dcp);
}

void HardwareNode::move(CDC* dcp,int dx,int dy)
{
	NodeFigure::move(dcp,dx,dy);
	_nodeName->moveCoord(dx,dy);
}

void HardwareNode::moveCoord(int dx,int dy)
{
	NodeFigure::moveCoord(dx,dy);
	_nodeName->moveCoord(dx,dy);
}

void HardwareNode::setController(COODView *ptr)
{
	NodeFigure::setController(ptr);
	_nodeName->setController(ptr);
}

BOOL HardwareNode::startEdit()
{
	_focus = _nodeName;
	_nodeName->startEdit();
	return TRUE;
}

void HardwareNode::bye()
{
	if (_focus == NIL) return;
	_nodeName->bye();
	return;
}

void HardwareNode::epilog(BOOL skipflag)
{
	if (_savedX2 == -1 && _savedY2 == -1) {
		NodeFigure::epilog(skipflag);
		_shape->arrangeXY12();
		_nodeName->recalcCoordFromXY1(_shape->getX1()+NAME_TEXT_DX,
									_shape->getY1()+NAME_TEXT_DY);
		recalcDecorationsCoord();
		return;
	}
	if (_shape->hotX() == NIL || _shape->hotY() == NIL) {
		NodeFigure::epilog(skipflag);
		_shape->arrangeXY12();
		_nodeName->recalcCoordFromXY1(_shape->getX1()+NAME_TEXT_DX,
									_shape->getY1()+NAME_TEXT_DY);
		recalcDecorationsCoord();
		return;
	}
	int nameW = _nodeName->content()->otherLinesMaxWidth();
	int limitX = _line1->_x1.x + 20;
	int limitY = _line1->_y1.y + 20;
	int lastX = _shape->hotX()->x;
	int lastY = _shape->hotY()->y;
	if (lastX < limitX ||
		lastY < limitY) {
		_controller->beep("Resizing aborted.");
		_shape->_x1.x = _line1->_x1.x;
		_shape->_y1.y = _line1->_y1.y;
		_shape->_x2.x = _savedX2;
		_shape->_y2.y = _savedY2;
		recalcDecorationsCoord();
		_savedX2 = -1;
		_savedY2 = -1;
		_controller->Invalidate();
		return;
	}
	recalcDecorationsCoord();
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

void HardwareNode::drawing(CDC* dcp,int dx,int dy)
{
	drawDecoLines(dcp);
	_shape->drawing(dcp,dx,dy);
	recalcDecorationsCoord();
	drawDecoLines(dcp);
}

void HardwareNode::drawDecoLines(CDC* dcp)
{
	_line1->draw(dcp);
	_line2->draw(dcp);
	_line3->draw(dcp);
	_line4->draw(dcp);
	_line5->draw(dcp);
}

void HardwareNode::recalcDecorationsCoord()
{
	int x1 = _shape->getX1(); int y1 = _shape->getY1();
	int x2 = _shape->getX2(); int y2 = _shape->getY2();
	_line1->setXY1(x1,y1);
	_line1->setXY2(x1+GAP_FROM_NODE,y1-GAP_FROM_NODE);
	_line2->setXY1(x1+GAP_FROM_NODE,y1-GAP_FROM_NODE);
	_line2->setXY2(x2+GAP_FROM_NODE,y1-GAP_FROM_NODE);
	_line3->setXY1(x2+GAP_FROM_NODE,y1-GAP_FROM_NODE);
	_line3->setXY2(x2+GAP_FROM_NODE,y2-GAP_FROM_NODE);
	_line4->setXY1(x2+GAP_FROM_NODE,y2-GAP_FROM_NODE);
	_line4->setXY2(x2,y2);
	_line5->setXY1(x2,y1);
	_line5->setXY2(x2+GAP_FROM_NODE,y1-GAP_FROM_NODE);
}


