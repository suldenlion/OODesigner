// ComponentTemplate.cpp: implementation of the ComponentTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ComponentTemplate.h"
#include "COODView.h"
#include "Box.h"
#include "Circle.h"
#include "ComponentText.h"
#include "SlaveryTextList.h"
#include "FigureList.h"
#include "ExcludeRect.h"
#include "ExcludeRectList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define EMPTY_GAP_ON_LEFT	(16)
#define PORT_WIDTH			(16)
#define PORT_UNIT_HEIGHT	(14)
#define PORT_HEIGHT			(8)
#define PORT_GAP			(PORT_UNIT_HEIGHT-(PORT_HEIGHT))

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ComponentTemplate,EditableFigure,1)

ComponentTemplate::ComponentTemplate()
: EditableFigure()
{
	_port1 = NIL;
	_port2 = NIL;
	_port3 = NIL;
}

ComponentTemplate::ComponentTemplate(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	if (controller == NIL) return;
	_popup = popup;
	_initWidth = COMPONENTTEMPLATE_INIT_WIDTH;
	_emptyGapX = EMPTY_GAP_ON_LEFT;
	_gapX = XGAP_COMPONENTTEMPLATE;
	_gapY = YGAP_COMPONENTTEMPLATE;
	_shape = new Box(controller,ox,oy,
				ox+_initWidth,oy+2*_gapY+DEFAULT_NO_OF_LINES*deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	EditableFigure::setBackground(theAppPtr->shapeBackgroundColor);
	ComponentText *aText = 
		new ComponentText(controller,this,IAMCOMPONENTNAME,ox+_emptyGapX+_gapX,oy+_gapY);
	_texts->insert(aText);

	_port1 = new Circle(controller,ox-PORT_WIDTH,oy+PORT_GAP,
						ox+PORT_WIDTH,oy+PORT_UNIT_HEIGHT,NIL);
	_port1->filled() = TRUE;
	_port1->setBackground(theAppPtr->shapeBackgroundColor);
	_port2 = new Box(controller,ox-PORT_WIDTH,oy+PORT_UNIT_HEIGHT+PORT_GAP,
						ox+PORT_WIDTH,oy+2*PORT_UNIT_HEIGHT,NIL);
	_port2->filled() = TRUE;
	_port2->setBackground(theAppPtr->shapeBackgroundColor);
	_port3 = new Box(controller,ox-PORT_WIDTH,oy+2*PORT_UNIT_HEIGHT+PORT_GAP,
						ox+PORT_WIDTH,oy+3*PORT_UNIT_HEIGHT,NIL);
	_port3->filled() = TRUE;
	_port3->setBackground(theAppPtr->shapeBackgroundColor);
	_decorations->insert(_port1);
	_decorations->insert(_port2);
	_decorations->insert(_port3);
}

ComponentTemplate::~ComponentTemplate()
{
}

void ComponentTemplate::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _port1 << _port2;
		ar << _port3;
	} else {
		ar >> _port1 >> _port2;
		ar >> _port3;
	}
}

UnsignedLong* ComponentTemplate::whoAreYou()
{
	return IAMCOMPONENTTEMPLATE;
}

Figure* ComponentTemplate::born(Figure* ptr)
{
	ComponentTemplate *copied;
	if (ptr == NIL) {
		copied = new ComponentTemplate(NIL,0,0,0,NIL);
	} else {
		copied = (ComponentTemplate *)ptr;
	}
	return (EditableFigure::born((Figure *)copied));
}

void ComponentTemplate::setSpecificDataMembers()
{
	_port1 = (Circle *)_decorations->getFirst();
	_port2 = (Box *)_decorations->getNext();
	_port3 = (Box *)_decorations->getNext();
}

void ComponentTemplate::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(clip(dcp),RGN_COPY);
		excludeRects(dcp);
	}
	EditableFigure::draw(dcp);
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(NULL,RGN_COPY);
	}
	// _decorations 를 통해 그리기는 하지만 클립때문에 안그려짐
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(_port1->clip(dcp),RGN_COPY);
		excludeRects(dcp);
		_port1->draw(dcp);
		dcp->SelectClipRgn(_port2->clip(dcp),RGN_COPY);
		excludeRects(dcp);
		_port2->draw(dcp);
		dcp->SelectClipRgn(_port3->clip(dcp),RGN_COPY);
		excludeRects(dcp);
		_port3->draw(dcp);
		dcp->SelectClipRgn(NULL,RGN_COPY);
	}
}

void ComponentTemplate::drawOnMetaFile(CDC* dcp)
{
	if (!_inCanvas) return;
	EditableFigure::draw(dcp);
	_port1->drawOnMetaFile(dcp);
	_port2->drawOnMetaFile(dcp);
	_port3->drawOnMetaFile(dcp);
}

void ComponentTemplate::setBackground(COLORREF c)
{
	EditableFigure::setBackground(c);
	_port1->setBackground(c);
	_port2->setBackground(c);
	_port3->setBackground(c);
}

void ComponentTemplate::getAdditionalExcludeRects(ExcludeRectList *pList)
{
	int x1 = _port1->_x1.get();
	int y1 = _port1->_y1.get();
	int x2 = _port1->_x2.get();
	int y2 = _port1->_y2.get();
	ExcludeRect *rect = new ExcludeRect(this,x1,y1,x2+1,y2+1);
	pList->addTail(rect);

	x1 = _port2->_x1.get();
	y1 = _port2->_y1.get();
	x2 = _port2->_x2.get();
	y2 = _port2->_y2.get();
	rect = new ExcludeRect(this,x1,y1,x2+1,y2+1);
	pList->addTail(rect);

	x1 = _port3->_x1.get();
	y1 = _port3->_y1.get();
	x2 = _port3->_x2.get();
	y2 = _port3->_y2.get();
	rect = new ExcludeRect(this,x1,y1,x2+1,y2+1);
	pList->addTail(rect);
}
