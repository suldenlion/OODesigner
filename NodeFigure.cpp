// NodeFigure.cpp: implementation of the NodeFigure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Afxadv.h"
#include "OOD.h"
#include "NodeFigure.h"
#include "ConnectionList.h"
#include "FigureList.h"
#include "Connection.h"
#include "TwoPointFigure.h"
#include "Line.h"
#include "LineNode.h"
#include "LineNodeList.h"
#include "COODView.h"
#include "UnsignedLong.h"
#include "ExcludeRect.h"
#include "ExcludeRectList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(NodeFigure,Figure,1)

NodeFigure::NodeFigure()
: Figure()
{
	_popup = NIL;
	_shape = NIL;
	_connections = NIL;
	_decorations = NIL;
}

NodeFigure::NodeFigure(COODView *controller)
: Figure(controller)
{
	_popup = NIL;
	_shape = NIL;
	if (controller == NIL) return;
	_connections = new ConnectionList();
	_decorations = new FigureList();
}

NodeFigure::~NodeFigure()
{
	if (_connections != NIL) {
		_connections->clear(); 
		delete _connections; _connections = NIL;
	}
	if (_decorations != NIL) {
		Figure *aDecoration = _decorations->getFirst();
		while (aDecoration != NIL) {
			delete aDecoration;
			aDecoration = _decorations->getNext();
		}
		_decorations->clear();
		delete _decorations; _decorations = NIL;
	}
	if (_shape != NIL) {
		delete _shape; _shape = NIL;
	}
}

void NodeFigure::Serialize(CArchive& ar)
{
	Figure::Serialize(ar);
	CFile *pFile = ar.GetFile();
	if (ar.IsStoring()) {
		if (pFile->IsKindOf(RUNTIME_CLASS(CSharedFile))) {
			// 이 경우는 cut & paste 시에 시리얼라이즈 되는 경우임
			// 만약 undo 기능을 구현하고자 할 때는 주의 해야 함
			// 나중에 메인 뷰에서 커넥션 부분을 다시 설정하는 방식으로 ...
			ar << _shape << _decorations;
		} else {
			ar << _shape << _connections << _decorations;
		}
	} else {
		if (pFile->IsKindOf(RUNTIME_CLASS(CSharedFile))) {
			// 이 경우는 cut & paste 시에 시리얼라이즈 되는 경우임
			// 만약 undo 기능을 구현하고자 할 때는 주의 해야 함
			// 나중에 메인 뷰에서 커넥션 부분을 다시 설정하는 방식으로 ...
			ar >> _shape >> _decorations;
			if (_connections != NIL) delete _connections;
			_connections = new ConnectionList();
		} else {
			ar >> _shape >> _connections >> _decorations;
		}
	}
}

int NodeFigure::width() 
{
	if (_shape != NIL) {
		return _shape->width();
	} else {
		return 0;
	}
}

Figure* NodeFigure::born(Figure* ptr)
{
	NodeFigure *copied;
	if (ptr == NIL) {
		copied = new NodeFigure(NIL);
	} else {
		copied = (NodeFigure *)ptr;
	}
	copied->_shape = (TwoPointFigure *)_shape->born();
	copied->_connections = new ConnectionList();
	copied->_decorations = new FigureList();
	Figure *aDecoration = _decorations->getFirst();
	while(aDecoration != NIL) {
		copied->_decorations->insert(aDecoration->born());
		aDecoration = _decorations->getNext();
	}
	copied->setSpecificDataMembers();
	return (Figure::born((Figure *)copied));
}

BOOL& NodeFigure::inCanvas()
{
	if (_shape != NIL) {
		return _shape->inCanvas();
	}
	return _inCanvas;
}

CRgn*& NodeFigure::clip()
{
	if (_shape != NIL) {
		return _shape->clip();
	}
	return _clip;
}

CRgn* NodeFigure::clip(CDC *pDC)
{
	if (_shape != NIL) {
		return _shape->clip(pDC);
	}
	return Figure::clip(pDC);
}

void NodeFigure::removeExcludeRect(Figure *ptr)
{
	if (_shape != NIL) {
		_shape->removeExcludeRect(ptr);
		return;
	}
	Figure::removeExcludeRect(ptr);
}

void NodeFigure::removeAllExcludeRect()
{
	if (_shape != NIL) {
		_shape->removeAllExcludeRect();
		return;
	}
	Figure::removeAllExcludeRect();
}

void NodeFigure::addExcludeRect(ExcludeRect *ptr)
{
	if (_shape != NIL) {
		_shape->addExcludeRect(ptr);
		Figure *fig = ptr->figurePtr();
		ExcludeRectList *pList = new ExcludeRectList();
		fig->getAdditionalExcludeRects(pList);
		ExcludeRect *pRect = pList->getFirst();
		while(pRect != NIL) {
			_shape->addExcludeRect(pRect);
			pRect = pList->getNext();
		}
		pList->clear();
		delete pList;
		return;
	}
	Figure::addExcludeRect(ptr);
}

COLORREF NodeFigure::background()
{
	if (_shape != NIL) {
		return _shape->background();
	}
	return Figure::background();
}

void NodeFigure::setBackground(COLORREF c)
{
	if (_shape != NIL) {
		_shape->setBackground(c);
		return;
	}
	Figure::setBackground(c);
}

ExcludeRectList* NodeFigure::getExcudeRects()
{
	if (_shape != NIL) {
		return _shape->getExcudeRects();
	}
	return Figure::getExcudeRects();
}

CRgn*& NodeFigure::region()
{
	if (_shape != NIL) {
		return _shape->region();
	}
	return _region;
}

void NodeFigure::setInCanvas(BOOL flag)
{
	if (_shape != NIL) {
		_shape->setInCanvas(flag);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->setInCanvas(flag);
		aDecoration = _decorations->getNext();
	}
	Figure::setInCanvas(flag);
}

BOOL NodeFigure::checkInRegion(CRgn* rgn)
{
	if (_shape != NIL) {
		return _shape->checkInRegion(rgn);
	}
	return FALSE;
}

void NodeFigure::invalidate()
{
	if (_shape != NIL) {
		_shape->invalidate();
	} else {
		Figure::invalidate();
	}
}

void NodeFigure::center(int& cx,int& cy)
{ 
	if (_shape != NIL) {
		_shape->center(cx,cy);
	}
}

void NodeFigure::getExclusiveClipRect(int &x1,int &y1,int &x2,int &y2)
{
	if (_shape != NIL) {
		_shape->getExclusiveClipRect(x1,y1,x2,y2);
	}
}

void NodeFigure::last(int& x,int& y)
{
	if (_shape != NIL) {
		_shape->last(x,y);
	}
}

void NodeFigure::clear(CDC* dcp)
{
	if (_shape != NIL) {
		_shape->clear(dcp);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->clear(dcp);
		aDecoration = _decorations->getNext();
	}
}

void NodeFigure::clearMeAndNeighbors(CDC *dcp)
{
	clear(dcp);
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->clearMeAndNeighbors(dcp);
		ptr = _connections->getNext();
	}
}

void NodeFigure::minMaxXY()
{
	if (_shape != NIL) {
		_shape->minMaxXY();
	}
}

void NodeFigure::getMinMaxXY(int &x1,int &y1,int &x2,int &y2)
{
	if (_shape != NIL) {
		_shape->getMinMaxXY(x1,y1,x2,y2);
	}
}

void NodeFigure::eraseDots(CDC* dcp)
{
	if (_shape != NIL) {
		_shape->eraseDots(dcp);
	}
}

void NodeFigure::drawDots(CDC* dcp)
{
	if (_shape != NIL) {
		_shape->drawDots(dcp);
	}
}

BOOL NodeFigure::adjustLine(Line *line,BOOL startPoint)
{
	if (_shape != NIL) {
		return _shape->adjustLine(line,startPoint);
	}
	return FALSE;
}

void NodeFigure::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	if (_shape != NIL) {
		_shape->draw(dcp);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->draw(dcp);
		aDecoration = _decorations->getNext();
	}
}

void NodeFigure::drawWithNeighbors(CDC *dcp)
{
	draw(dcp);
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->draw(dcp);
		ptr = _connections->getNext();
	}
}

void NodeFigure::drawing(CDC* dcp,int dx,int dy)
{
	if (_shape != NIL) {
		_shape->drawing(dcp,dx,dy);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->drawing(dcp,dx,dy);
		aDecoration = _decorations->getNext();
	}
}

BOOL NodeFigure::onEnter(int x,int y)
{
	_focus = _shape;
	if (_shape != NIL) {
		return _shape->onEnter(x,y);
	}
	return FALSE;
}

void NodeFigure::move(CDC* dcp,int dx,int dy)
{
	if (_shape != NIL) {
		_shape->move(dcp,dx,dy);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->move(dcp,dx,dy);
		aDecoration = _decorations->getNext();
	}
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->comeOn(dcp,dx,dy);
		ptr = _connections->getNext();
	}
}

void NodeFigure::moveCoord(int dx,int dy)
{
	if (_shape != NIL) {
		_shape->moveCoord(dx,dy);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->moveCoord(dx,dy);
		aDecoration = _decorations->getNext();
	}
}

void NodeFigure::moveCoordForScroll(int dx,int dy)
{
	if (_shape ==  NIL) return;
	_shape->moveCoord(dx,dy);
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->moveCoord(dx,dy);
		aDecoration = _decorations->getNext();
	}
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setHotXYUsingDelta(_shape->getX1(),_shape->getY1(),dx,dy);
		ptr = _connections->getNext();
	}
}

int NodeFigure::setHotXY(int x,int y)
{
	if (_shape != NIL) {
		_shape->setHotXY(x,y);
	}
	return 0;
}

BOOL NodeFigure::wantToResize(int& x,int& y)
{
	return FALSE;
}

void NodeFigure::clearLists()
{
	_connections->clear();
}

void NodeFigure::makeRegion(CRgn *sourceClipRgn)
{
	if (_region != NIL) delete _region;
	_region = createRegion();
	if (_shape != NIL) {
		_shape->makeRegion(sourceClipRgn);
		_region->CombineRgn(_region,_shape->region(),RGN_OR);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->makeRegion(sourceClipRgn);
		aDecoration = _decorations->getNext();
	}
}

void NodeFigure::resetRegion()
{
	if (_shape != NIL) {
		_shape->resetRegion();
	}
}

void NodeFigure::releaseRegion()
{
	if (_shape != NIL) {
		_shape->releaseRegion();
	}
}

void NodeFigure::deleteNeighbors()
{
	ConnectionList *copiedList = new ConnectionList();
	copiedList->copy(_connections);
	Connection *aConnection = copiedList->getFirst();
	while (aConnection != NIL) {
		BOOL segmentDeleted = 
			aConnection->tryToDeleteOneLineSegment(this);
		if (segmentDeleted == FALSE) {
			_controller->remove(aConnection);
			_controller->checkInList(aConnection);
			_controller->erase(aConnection);
			delete aConnection;
		}
		aConnection = copiedList->getNext();
	}
	_connections->clear();
	delete copiedList;
}

Figure* NodeFigure::makeBackUp()
{
	NodeFigure *copied = (NodeFigure*)born();
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		copied->_decorations->insert(aDecoration->born());
		aDecoration = _decorations->getNext();
	}
	Connection *aConnection = _connections->getFirst();
	while (aConnection != NIL) {
		copied->_connections->insert((Connection*)aConnection->born());
		aConnection = _connections->getNext();
	}
	return copied;
}

void NodeFigure::setController(COODView *ptr)
{
	Figure::setController(ptr);
	if (_shape != NIL) {
		_shape->setController(ptr);
	}
	Figure *aDecoration = _decorations->getFirst();
	while (aDecoration != NIL) {
		aDecoration->setController(ptr);
		aDecoration = _decorations->getNext();
	}
}

void NodeFigure::drawConnections(CDC *dcp)
{
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->draw(dcp);
		ptr = _connections->getNext();
	}
}

void NodeFigure::epilog(BOOL skipflag)
{
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->epilog();
		ptr = _connections->getNext();
	}
	return;
}

void NodeFigure::setConnectionMovedFlag(BOOL flag)
{
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setConnectionMovedFlag(flag);
		ptr = _connections->getNext();
	}
}

BOOL NodeFigure::moveProlog(BOOL moveAllFlag)
{
	if (moveAllFlag) {
		int n = _connections->nOfList();
		if (n > 0) {
			Connection *ptr = _connections->getFirst();
			while (ptr != NIL) {
				if (ptr->isLinearConnection(FALSE) == TRUE) {
					ptr->letsGo(this);
				} else if (ptr->whoAreYou()->equals(IAMASSOCIATION)) {
					ptr->letsGo(this);
				} else {
					ptr->letsGoWithBucket(this);
				}
				ptr = _connections->getNext();
			}
		}
		return TRUE;
	}
	int n = _connections->nOfList();
	if (n > 0) {
		Connection *ptr = _connections->getFirst();
		while (ptr != NIL) {
			ptr->letsGo(this);
			ptr = _connections->getNext();
		}
	}
	return FALSE;
}

void NodeFigure::insert(Connection *connection)
{
	_connections->insert(connection);
}

void NodeFigure::remove(Connection *connection)
{
	_connections->remove(connection);
}

BOOL NodeFigure::replacePointer(Connection *from,Connection *to)
{
	BOOL replaced = FALSE;
	replaced = _connections->replacePointer(from,to);
	return replaced;
}

int NodeFigure::getX1()
{
	return _shape->getX1();
}

int NodeFigure::getY1()
{
	return _shape->getY1();
}

int NodeFigure::getX2()
{
	return _shape->getX2();
}

int NodeFigure::getY2()
{
	return _shape->getY2();
}

BOOL NodeFigure::contains(int x,int y)
{
	return _shape->contains(x,y);
}

BOOL NodeFigure::containedWithin(int x1,int y1,int x2,int y2)
{
	return _shape->containedWithin(x1,y1,x2,y2);
}

BOOL NodeFigure::containsOnLargeBound(int x,int y)
{
	return _shape->containsOnLargeBound(x,y);
}

void NodeFigure::setOrientForObsoleteLine(Line *aLine)
{
	// default orient 를 북쪽으로 ...
	aLine->setOrient(NORTH);
	if (_shape == NIL) return;
	int where = _shape->onWhichSide(aLine->getX1(),aLine->getY1());
	if (where == NORTH || where == SOUTH) aLine->setOrient(NORTH);
	else if (where == EAST || where == WEST) aLine->setOrient(EAST);
	else aLine->setOrient(NORTH);
}

BOOL NodeFigure::onBound(Line *aLine)
{
	if (_shape == NIL) return FALSE;
	return _shape->onBound(aLine);
}

BOOL NodeFigure::onBoundaryOrObsolete(LineNodeList *lines)
{
	LineNode *aNode = lines->getFirst();
	while(aNode != NIL) {
		Line *aLine = aNode->line();
		if (aLine->isObsolete() == FALSE) {
			if (_shape->onBound(aLine) == FALSE) 
				return FALSE;
		}
		aNode = lines->getNext();
	}
	return TRUE;
}

BOOL NodeFigure::contains(LineNodeList *lines)
{
	LineNode *aNode = lines->getFirst();
	while(aNode != NIL) {
		Line *aLine = aNode->line();
		if (contains(aLine->getX1(),aLine->getY1()) == FALSE)
			return FALSE;
		if (contains(aLine->getX2(),aLine->getY2()) == FALSE)
			return FALSE;
		aNode = lines->getNext();
	}
	return TRUE;
}

BOOL NodeFigure::startEdit()
{
	return FALSE;
}

void NodeFigure::bye()
{
	// Empty
}

void NodeFigure::setFocus(int x,int y)
{
	// pure virtual function
	_focus = NIL;
}

void NodeFigure::resetFocus()
{
	_focus = NIL;
}

void NodeFigure::setThisFocus(Figure *ptr)
{
	_focus = ptr;
}

Figure *NodeFigure::focus()
{
	if (_focus == NIL) {
		_focus = this;
	}
	return _focus;
}

int NodeFigure::onWhichSideRegion(int x,int y)
{
	if (_shape == NIL) return O_SIDE;
	int x1 = _shape->getX1();
	int y1 = _shape->getY1();
	int x2 = _shape->getX2();
	int y2 = _shape->getY2();
	if (x < x1) {
		// VI, VII, VIII
		if (y < y1) return VIII_SIDE;
		else if (y > y2) return VI_SIDE;
		else return VII_SIDE;
	} else if (x >= x1 && x <= x2) {
		// I, V
		if (y < y1) return I_SIDE;
		else if (y > y2) return V_SIDE;
	} else { // x > x2
		// II, III, IV
		if (y < y1) return II_SIDE;
		else if (y > y2) return IV_SIDE;
		else return III_SIDE;
	}
	return O_SIDE;
}
