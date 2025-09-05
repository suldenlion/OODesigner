// Bucket.cpp: implementation of the Bucket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Bucket.h"
#include "UnsignedLong.h"
#include "COODView.h"
#include "Lines.h"
#include "NodeFigure.h"
#include "Connection.h"
#include "ConnectionList.h"
#include "COODDoc.h"
#include "COODCntrlItem.h"

#define GRAY_RGB				(RGB(200,200,200))

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Bucket::Bucket(COODView *controller)
: Box(controller,0,0,0,0,NIL)
{
	_forWideFigure = FALSE;
}

Bucket::~Bucket()
{
}

UnsignedLong *Bucket::whoAreYou()
{
	return IAMBUCKET; 
}

BOOL Bucket::wantToResize(int &x,int &y)
{
	return FALSE;
}

void Bucket::resizeProlog(NodeFigure* nodeFigure)
{
	int x2 = getX2();
	int y2 = getY2();
	wantToResizeExact(x2,y2);
}

void Bucket::draw(CDC* dcp)
{
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->draw(dcp);
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->draw(_controller,dcp);
		selection = _oleItems.getNext();
	}
}

void Bucket::clear(CDC* dcp)
{
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->clear(dcp);
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->clear(_controller,dcp); 
		selection = _oleItems.getNext();
	}
}

void Bucket::drawBoundary(CDC* dcp)
{
	if (_figures.isEmpty() && _oleItems.isEmpty()) {
		CPen grayPen1(PS_SOLID,1,GRAY_RGB);
		CPen *oldPen = dcp->SelectObject(&grayPen1);
		Box::draw(dcp);
		dcp->SelectObject(oldPen);
		return;
	}
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->drawBoundary(dcp);
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->drawBoundary(_controller,dcp);
		selection = _oleItems.getNext();
	}
}

void Bucket::eraseDots(CDC* dcp)
{
	if (_figures.isEmpty() && _oleItems.isEmpty()) return;
	if (_x1.x == _x2.x && _y1.y == _y2.y) {
		_controller->Invalidate();
		return;
	}
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->drawDots(dcp);
		aFigure = _figures.getNext();
	}
	CRect tmp(getX1(),getY1(),getX2(),getY2());
	_controller->invalidateRect(&tmp);
}

void Bucket::drawDots(CDC* dcp)
{
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->drawDots(dcp);
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->drawAsSelected(_controller,dcp);
		selection = _oleItems.getNext();
	}
}

void Bucket::move(CDC* dcp,int dx,int dy)
{
	moveCoord(dx,dy);
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		if (aFigure->whoAreYou()->isIn(WEARENODEOBJECTS)) {
			NodeFigure *aNode = (NodeFigure *)aFigure;
			aNode->setConnectionMovedFlag(FALSE);
		}
		aFigure = _figures.getNext();
	}
	aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->move(dcp,dx,dy);
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->move(_controller,dx,dy);
		selection = _oleItems.getNext();
	}
}

void Bucket::moveCoordForScroll(int dx,int dy)
{
	moveCoord(dx,dy);
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		if (aFigure->whoAreYou()->isIn(WEARENODEOBJECTS)) {
			aFigure->moveCoordForScroll(dx,dy);
		}
		aFigure = _figures.getNext();
	}
}

void Bucket::makeRegion(CRgn *sourceClipRgn)
{
	Box::makeRegion(sourceClipRgn);
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->makeRegion(sourceClipRgn);
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->makeRegion(_controller);
		selection = _oleItems.getNext();
	}
}

void Bucket::releaseRegion()
{
	Box::releaseRegion();
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->releaseRegion();
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->releaseRegion(_controller);
		selection = _oleItems.getNext();
	}
}

void Bucket::resetRegion()
{
	Box::resetRegion();
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->resetRegion();
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->resetRegion(_controller);
		selection = _oleItems.getNext();
	}
}

BOOL Bucket::moveProlog(BOOL moveAllFlag)
{
	ConnectionList followConnections;

	Figure *aFigure = _figures.getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->isIn(WEARENODEOBJECTS)) {
			NodeFigure *aNode = (NodeFigure *)aFigure;
			ConnectionList *connections = aNode->connections();
			Connection *aConnection = connections->getFirst();
			while (aConnection != NIL) {
				if (aConnection->moveAllFlag() == FALSE) {
					followConnections.insert(aConnection);
				}
				aConnection = connections->getNext();
			}
		}
		aFigure = _figures.getNext();
	}

	Connection *aConnection = followConnections.getFirst();
	while (aConnection != NIL) {
		aConnection->initializeForMoveProlog();
		aConnection = followConnections.getNext();
	}

	aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->moveProlog(TRUE);
		aFigure->setInCanvas(TRUE);
		aFigure = _figures.getNext();
	}
	COODCntrlItem *selection = _oleItems.getFirst();
	while (selection != NIL) {
		selection->setInCanvas(TRUE);
		selection = _oleItems.getNext();
	}

	FigureList *theList = _controller->figures();
	aFigure = _figures.getFirst();
	while (aFigure != NIL) {
		theList->remove(aFigure);
		_controller->checkInList(aFigure);
		aFigure = _figures.getNext();
	}

	COODDoc *pDoc = _controller->GetDocument();
	if (pDoc == NIL) return FALSE;

	return FALSE;
}

void Bucket::epilog(BOOL skipflag)
{
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		aFigure->epilog(skipflag);
		aFigure = _figures.getNext();
	}
	
	ConnectionList followConnections;

	aFigure = _figures.getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->isIn(WEARENODEOBJECTS)) {
			NodeFigure *aNode = (NodeFigure *)aFigure;
			ConnectionList *connections = aNode->connections();
			Connection *aConnection = connections->getFirst();
			while (aConnection != NIL) {
				followConnections.insert(aConnection);
				aConnection = connections->getNext();
			}
		}
		aFigure = _figures.getNext();
	}

	Connection *aConnection = followConnections.getFirst();
	while (aConnection != NIL) {
		aConnection->setConnectionMovedFlag(FALSE);
		aConnection = followConnections.getNext();
	}
}

void Bucket::restoreOleItems(COODDoc *pDoc)
{
	// 실제로는 필요 없지만 모양상의 발란스를 맞추기 위해서
	if (_forWideFigure == FALSE) { 
		return;
	}
	clearList();
}

void Bucket::restoreFigures(FigureList *theList)
{
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		theList->insert(aFigure);
		aFigure = _figures.getNext();
	}
	if (_forWideFigure == FALSE) {
		return;
	}
	clearList();
}

void Bucket::setCoord(int x1,int y1,int x2,int y2)
{
	_x1.set(x1); _y1.set(y1);
	_x2.set(x2); _y2.set(y2);
}

void Bucket::insert(Figure *ptr)
{
	_figures.insert(ptr);
}

BOOL Bucket::hasFigure(Figure *ptr)
{
	return _figures.inList(ptr);
}

BOOL Bucket::hasSelection(COODCntrlItem *ptr)
{
	return _oleItems.inList(ptr);
}

BOOL Bucket::isEmpty() { 
	if (_figures.isEmpty() && _oleItems.isEmpty())
		return TRUE;
	else
		return FALSE;
}

void Bucket::clearList()
{
	Figure *aFigure = _figures.getFirst();
	while(aFigure != NIL) {
		if (aFigure->whoAreYou()->isIn(WEARELINES)) {
			aFigure->setMoveAllFlag(FALSE);
		}
		aFigure = _figures.getNext();
	}
	_figures.clear();
	_oleItems.clear();
}

void Bucket::collectContainedOleItems(COODDoc *pDoc,COODView *pView)
{
	int x1 = _x1.x;
	int y1 = _y1.y;
	int x2 = _x2.x;
	int y2 = _y2.y;
	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL && selection->containedWithin(pView,x1,y1,x2,y2)) {
			_oleItems.addTail(selection);
		}
	}
}

void Bucket::collectContainedFigures(FigureList *theList)
{
	_forWideFigure = TRUE;
	int x1 = _x1.x;
	int y1 = _y1.y;
	int x2 = _x2.x;
	int y2 = _y2.y;
	Figure *aFigure = theList->getFirst();
	while (aFigure != NIL) {
		if (aFigure->containedWithin(x1,y1,x2,y2)) {
			_figures.insert(aFigure);
		}
		aFigure = theList->getNext();
	}
	aFigure = _figures.getFirst();
	while (aFigure != NIL) {
		theList->remove(aFigure);
		_controller->checkInList(aFigure);
		aFigure = _figures.getNext();
	}
}

void Bucket::copyAllOleItems(COODDoc *pDoc,COODView *pView)
{
	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL && selection->getController() == pView) {
			_oleItems.addTail(selection);
		}
	}
}

void Bucket::copyAllFigures(FigureList *theList)
{
	_x1.x = 0;
	_y1.y = 0;
	_x2.x = 0;
	_y2.y = 0;
	Figure *aFigure = theList->getFirst();
	while (aFigure != NIL) {
		_figures.insert(aFigure);
		aFigure = theList->getNext();
	}
}

void Bucket::copyContainedOleItems(COODDoc *pDoc,COODView *pView)
{
	int x1 = _x1.x;
	int y1 = _y1.y;
	int x2 = _x2.x;
	int y2 = _y2.y;
	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL && selection->containedWithin(pView,x1,y1,x2,y2)) {
			_oleItems.addTail(selection);
		}
	}
}

void Bucket::copyContainedFigures(FigureList *theList)
{
	_forWideFigure = FALSE;
	int x1 = _x1.x;
	int y1 = _y1.y;
	int x2 = _x2.x;
	int y2 = _y2.y;
	Figure *aFigure = theList->getFirst();
	while (aFigure != NIL) {
		if (aFigure->containedWithin(x1,y1,x2,y2)) {
			_figures.insert(aFigure);
		}
		aFigure = theList->getNext();
	}
}