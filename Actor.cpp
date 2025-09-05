// Actor.cpp: implementation of the Actor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Actor.h"
#include "ActorNameText.h"
#include "FigureList.h"
#include "TwoPointFigure.h"
#include "Box.h"
#include "Line.h"
#include "Circle.h"
#include "ConnectionList.h"
#include "Connection.h"
#include "COODView.h"

#define HEADSIZE	(14)
#define BODYLENGTH	(26)
#define ARMSIZE		(12)
#define ARMDELTA	(5)
#define FOOTWIDTH	(12)
#define FOOTHEIGHT	(15)
#define NAMETEXTGAP (10)

#define ACTORHEIGHT	(HEADSIZE+BODYLENGTH+FOOTHEIGHT)
#define ACTORWIDTH	(ARMSIZE)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Actor,NodeFigure,1)

Actor::~Actor()
{
	delete _actorName; _actorName = NIL;
}

Actor::Actor()
: NodeFigure()
{
	_actorName = NIL;
}

Actor::Actor(COODView *controller,int x,int y,Popup* popup)
: NodeFigure(controller)
{
	if (controller == NIL) return;
	_shape = new Box(controller,x-ACTORWIDTH,y-ACTORHEIGHT/2,
								x+ACTORWIDTH,y+ACTORHEIGHT/2,NIL);
	_actorName = new ActorNameText(controller,this,x,y+ACTORHEIGHT/2+NAMETEXTGAP,NIL);
	_actorName->setAutoDelete(FALSE);
	_actorName->makeRegion(_controller->canvasRgn());
	Circle *head = new Circle(controller,x-HEADSIZE/2,y-ACTORHEIGHT/2,
										 x+HEADSIZE/2,y-ACTORHEIGHT/2+HEADSIZE,NIL);
	Line *body = new Line(controller,x,y-ACTORHEIGHT/2+HEADSIZE,
									 x,y-ACTORHEIGHT/2+HEADSIZE+BODYLENGTH,NIL,STRAIGHT);
	Line *arm = new Line(controller,x-ARMSIZE,y-ARMDELTA,
									x+ARMSIZE,y-ARMDELTA,NIL,STRAIGHT);
	Line *footLeft = new Line(controller,x,y-ACTORHEIGHT/2+HEADSIZE+BODYLENGTH,
										 x-FOOTWIDTH,y-ACTORHEIGHT/2+HEADSIZE+BODYLENGTH+FOOTHEIGHT,NIL,ORDINARY);
	Line *footRight = new Line(controller,x,y-ACTORHEIGHT/2+HEADSIZE+BODYLENGTH,
										 x+FOOTWIDTH,y-ACTORHEIGHT/2+HEADSIZE+BODYLENGTH+FOOTHEIGHT,NIL,ORDINARY);
	_decorations->insert(head);
	_decorations->insert(body);
	_decorations->insert(arm);
	_decorations->insert(footLeft);
	_decorations->insert(footRight);
}

void Actor::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _actorName;
	} else {
		ar >> _actorName;
	}
}

Figure* Actor::born(Figure* ptr)
{
	Actor *copied;
	if (ptr == NIL) {
		copied = new Actor(NIL,0,0,NIL);
	} else {
		copied = (Actor *)ptr;
	}
	copied->_actorName = (ActorNameText *)_actorName->born();
	copied->_actorName->setMaster(this);
	return (NodeFigure::born((Figure *)copied));
}

void Actor::setInCanvas(BOOL flag)
{
	NodeFigure::setInCanvas(flag);
	_actorName->setInCanvas(flag);
}

void Actor::clear(CDC* dcp)
{
	if (_shape != NIL) {
		_shape->clear(dcp);
	}
	if (_actorName->isEmpty() == FALSE) {
		_actorName->clear(dcp);
	}
}

BOOL Actor::adjustLine(Line *line,BOOL startPoint)
{
	// adjustLine 이 의미없음
	return TRUE;
}

BOOL Actor::onEnter(int x,int y)
{
	if (_actorName->isEmpty() == FALSE && 
		_actorName->onEnter(x,y)) {
		_focus = _actorName;
		return TRUE;
	}
	return NodeFigure::onEnter(x,y);
}

void Actor::eraseDots(CDC* dcp)
{
	NodeFigure::eraseDots(dcp);
	if (_actorName->isEmpty() == FALSE) {
		_actorName->eraseDots(dcp);
	}
}

void Actor::drawDots(CDC* dcp)
{
	NodeFigure::drawDots(dcp);
	if (_actorName->isEmpty() == FALSE) {
		_actorName->drawDots(dcp);
	}
}

void Actor::setFocus(int x,int y)
{
	NodeFigure::setFocus(x,y);
	_actorName->setXY(x,y);
}

void Actor::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->draw(dcp);
		aDecoration = _decorations->getNext();
	}
	if (_actorName->isEmpty()) return; 
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		_actorName->draw(dcp);
	}
}

void Actor::drawing(CDC* dcp,int dx,int dy)
{
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->drawing(dcp,dx,dy);
		aDecoration = _decorations->getNext();
	}
	_actorName->drawing(dcp,dx,dy);
}

void Actor::moveCoordForScroll(int dx,int dy)
{
	NodeFigure::moveCoordForScroll(dx,dy);
	_actorName->moveCoord(dx,dy);
}

void Actor::moveCoord(int dx,int dy)
{
	NodeFigure::moveCoord(dx,dy);
	_actorName->moveCoord(dx,dy);
}

void Actor::move(CDC* dcp,int dx,int dy)
{
	if (_shape != NIL) {
		_shape->moveCoord(dx,dy);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->move(dcp,dx,dy);
		aDecoration = _decorations->getNext();
	}
	if (_actorName->isEmpty()) {
		_actorName->moveCoord(dx,dy);
	} else {
		_actorName->move(dcp,dx,dy);
	}
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->comeOn(dcp,dx,dy);
		ptr = _connections->getNext();
	}
}

void Actor::makeRegion(CRgn *sourceClipRgn)
{
	NodeFigure::makeRegion(sourceClipRgn);
	_actorName->makeRegion(sourceClipRgn);
}

void Actor::resetRegion()
{
	NodeFigure::resetRegion();
	_actorName->resetRegion();
}

void Actor::releaseRegion()
{
	NodeFigure::releaseRegion();
	_actorName->releaseRegion();
}

void Actor::setController(COODView *ptr)
{
	NodeFigure::setController(ptr);
	_actorName->setController(ptr);
}

BOOL Actor::onBoundaryOrObsolete(LineNodeList *lines)
{
	return FALSE;
}

UnsignedLong *Actor::whoAreYou()
{
	return IAMACTOR; 
}

BOOL Actor::startEdit()
{
	_focus = _actorName;
	_actorName->startEdit();
	return TRUE;
}

void Actor::bye()
{
	if (_focus == NIL) return;
	_actorName->bye();
	_controller->clear(_actorName);
	int x1 = _actorName->getX1();
	int y1 = _actorName->getY1();
	int x2 = _actorName->getX2();
	int y2 = _actorName->getY2();
	int width = x2-x1;
	int cx,cy;
	_shape->center(cx,cy);
	int newX1 = cx - width/2;
	int newY1 = _shape->getY2() + NAMETEXTGAP;
	_actorName->recalcCoordFromXY1(newX1,newY1);
	_controller->draw(_actorName);
	return;
}

void Actor::drawBoundary(CDC* dcp)
{
	NodeFigure::drawBoundary(dcp);
	if (_actorName->isEmpty()) return; 
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) {
		_actorName->drawBoundary(dcp);
	}
}


