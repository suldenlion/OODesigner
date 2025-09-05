// CollaborationMultiObject.cpp: implementation of the CollaborationMultiObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "CollaborationMultiObject.h"
#include "FigureList.h"
#include "Line.h"
#include "COODView.h"
#include "ExcludeRect.h"
#include "ExcludeRectList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define GAP_FROM_OBJECT (10)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CollaborationMultiObject,CollaborationObject,1)

CollaborationMultiObject::CollaborationMultiObject()
: CollaborationObject()
{
	_line1 = NIL;
	_line2 = NIL;
	_line3 = NIL;
	_line4 = NIL;
}

CollaborationMultiObject::CollaborationMultiObject(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: CollaborationObject(controller,ox,oy,deltaV,popup)
{
	if (controller == NIL) return;
	int x1 = getX1(); int y1 = getY1();
	int x2 = getX2(); int y2 = getY2();
	_line1 = new Line(controller,x1+GAP_FROM_OBJECT,y1,x1+GAP_FROM_OBJECT,y1-GAP_FROM_OBJECT,NIL,STRAIGHT);
	_line2 = new Line(controller,x1+GAP_FROM_OBJECT,y1-GAP_FROM_OBJECT,x2+GAP_FROM_OBJECT,y1-GAP_FROM_OBJECT,NIL,STRAIGHT);
	_line3 = new Line(controller,x2+GAP_FROM_OBJECT,y1-GAP_FROM_OBJECT,x2+GAP_FROM_OBJECT,y2-GAP_FROM_OBJECT,NIL,STRAIGHT);
	_line4 = new Line(controller,x2+GAP_FROM_OBJECT,y2-GAP_FROM_OBJECT,x2,y2-GAP_FROM_OBJECT,NIL,STRAIGHT);
	_decorations->insert(_line1);
	_decorations->insert(_line2);
	_decorations->insert(_line3);
	_decorations->insert(_line4);
}

CollaborationMultiObject::~CollaborationMultiObject()
{
}

void CollaborationMultiObject::Serialize(CArchive& ar)
{
	CollaborationObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _line1 << _line2;
		ar << _line3 << _line4;
	} else {
		ar >> _line1 >> _line2;
		ar >> _line3 >> _line4;
	}
}

UnsignedLong* CollaborationMultiObject::whoAreYou()
{
	return IAMCOLLABORATIONOBJECT;
}

Figure* CollaborationMultiObject::born(Figure* ptr)
{
	CollaborationMultiObject *copied;
	if (ptr == NIL) {
		copied = new CollaborationMultiObject(NIL,0,0,0,NIL);
	} else {
		copied = (CollaborationMultiObject *)ptr;
	}
	return (CollaborationObject::born((Figure *)copied));
}

void CollaborationMultiObject::setSpecificDataMembers()
{
	_line1 = (Line *)_decorations->getFirst();
	_line2 = (Line *)_decorations->getNext();
	_line3 = (Line *)_decorations->getNext();
	_line4 = (Line *)_decorations->getNext();
}

void CollaborationMultiObject::recalcDecorationsCoord()
{
	int x1 = getX1(); int y1 = getY1();
	int x2 = getX2(); int y2 = getY2();
	_line1->setXY1(x1+GAP_FROM_OBJECT,y1);
	_line1->setXY2(x1+GAP_FROM_OBJECT,y1-GAP_FROM_OBJECT);
	_line2->setXY1(x1+GAP_FROM_OBJECT,y1-GAP_FROM_OBJECT);
	_line2->setXY2(x2+GAP_FROM_OBJECT,y1-GAP_FROM_OBJECT);
	_line3->setXY1(x2+GAP_FROM_OBJECT,y1-GAP_FROM_OBJECT);
	_line3->setXY2(x2+GAP_FROM_OBJECT,y2-GAP_FROM_OBJECT);
	_line4->setXY1(x2+GAP_FROM_OBJECT,y2-GAP_FROM_OBJECT);
	_line4->setXY2(x2,y2-GAP_FROM_OBJECT);
}

void CollaborationMultiObject::bye()
{
	EditableFigure::bye();
	recalcDecorationsCoord();
}

void CollaborationMultiObject::modifyHeight(int dy,int index)
{
	CollaborationObject::modifyHeight(dy,index);
	clearDecoLines();
	recalcDecorationsCoord();
}

void CollaborationMultiObject::modifyWidthMinus(int lineDX,int index)
{
	CollaborationObject::modifyWidthMinus(lineDX,index);
	clearDecoLines();
	recalcDecorationsCoord();
	drawDecoLines();
}

void CollaborationMultiObject::modifyWidthPlus(int lineDX,int index)
{
	CollaborationObject::modifyWidthPlus(lineDX,index);
	clearDecoLines();
	recalcDecorationsCoord();
	drawDecoLines();
}

void CollaborationMultiObject::clearDecoLines()
{
	_controller->clear(_line1);
	_controller->clear(_line2);
	_controller->clear(_line3);
	_controller->clear(_line4);
}

void CollaborationMultiObject::drawDecoLines()
{
	_controller->draw(_line1);
	_controller->draw(_line2);
	_controller->draw(_line3);
	_controller->draw(_line4);
}

void CollaborationMultiObject::makeRegion(CRgn *sourceClipRgn)
{
	CollaborationObject::makeRegion(sourceClipRgn);

	if (_shape->clip()) delete _shape->clip();
	/*
	int x1 = _shape->getX1();
 	int y1 = _shape->getY1();
	int x2 = _shape->getX2();
 	int y2 = _shape->getY2();
	int x = x1;
	int y = y1 - GAP_FROM_OBJECT;
	int w = x2 - x1 + GAP_FROM_OBJECT;
	int h = y2 - y1 + GAP_FROM_OBJECT;
	_shape->clip() = _controller->makeRectRegion(x,y,w+1,h+1);
	*/
	_shape->clip() = createRegion();
	_shape->clip()->CopyRgn(sourceClipRgn);
}

void CollaborationMultiObject::getAdditionalExcludeRects(ExcludeRectList *pList)
{
	int x1 = _shape->getX1();
 	int y1 = _shape->getY1();
	int x2 = _shape->getX2();
 	int y2 = _shape->getY2();
	int x = x1 + GAP_FROM_OBJECT;
	int y = y1 - GAP_FROM_OBJECT;
	int w = x2 - x1;
	int h = y2 - y1;
	ExcludeRect *rect = new ExcludeRect(this,x,y,x+w+1,y+h+1);
	pList->addTail(rect);
}

void CollaborationMultiObject::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(clip(dcp),RGN_COPY);
		excludeRects(dcp);
		int x1 = _shape->getX1();
 		int y1 = _shape->getY1();
		int x2 = _shape->getX2();
 		int y2 = _shape->getY2();
		int x = x1 + GAP_FROM_OBJECT;
		int y = y1 - GAP_FROM_OBJECT;
		int w = x2 - x1;
		int h = y2 - y1;
		CRect rect(x,y,x+w,y+h);
		CBrush brush(background());
		dcp->FillRect(&rect,&brush);
		dcp->SelectClipRgn(NULL,RGN_COPY);
	}
	CollaborationObject::draw(dcp);
}

void CollaborationMultiObject::drawOnMetaFile(CDC *dcp)
{
	if (!_inCanvas) return;
	int x1 = _shape->getX1();
	int y1 = _shape->getY1();
	int x2 = _shape->getX2();
	int y2 = _shape->getY2();
	int x = x1 + GAP_FROM_OBJECT;
	int y = y1 - GAP_FROM_OBJECT;
	int w = x2 - x1;
	int h = y2 - y1;
	CRect rect(x,y,x+w,y+h);
	CBrush brush(background());
	dcp->FillRect(&rect,&brush);
	CollaborationObject::drawOnMetaFile(dcp);
}

