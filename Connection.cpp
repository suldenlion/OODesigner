// Connection.cpp: implementation of the Connection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Connection.h"
#include "COODView.h"
#include "Figures.h"
#include "LineNode.h"
#include "UnsignedLong.h"
#include "NodeFigureList.h" // Aggregation
#include "LineNodeList.h" // Aggregation
#include "CITList.h" // Aggregation
#include "OneLineText.h"
#include "ConnectionInfoTuple.h" // Collaboration
#include "AnytionInfoTuple.h"

extern int getRandom(int low,int high);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Connection,Lines,1)

Connection::Connection()
: Lines()
{
	_symbol = NIL;
	_text = NIL;
	_nodeFigures = NIL;
	_activeLines = NIL;
	_infoTuples = NIL;
}

Connection::Connection(COODView *controller,Popup* popup,Line *aLine)
: Lines(controller,popup,STRAIGHT,aLine)
{
	_symbol = NIL;
	_text = NIL;
	_nodeFigures = NIL;
	_activeLines = NIL;
	_infoTuples = NIL;
	if (controller == NIL) return;
	_nodeFigures = new NodeFigureList();
	_activeLines = new LineNodeList();
	/* _infoTuples는 SimpleConnection에서 NIL로 set 된다. */
	_infoTuples = new CITList();
}

void Connection::Serialize(CArchive& ar)
{
	Lines::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _symbol << _text;
		ar << _nodeFigures << _activeLines << _infoTuples;
	} else {
		ar >> _symbol >> _text;
		ar >> _nodeFigures >> _activeLines >> _infoTuples;
	}
}

Connection::~Connection()
{
	if (_symbol != NIL) {
		delete _symbol; _symbol = NIL;
	}
	if (_text != NIL) {
		delete _text; _text = NIL;
	}
	if (_nodeFigures != NIL) {
		NodeFigure *tmp = _nodeFigures->getFirst();
		while (tmp != NIL) {
			tmp->remove(this);
			tmp = _nodeFigures->getNext();
		}
		delete _nodeFigures; _nodeFigures = NIL;
	}
	if (_infoTuples != NIL) {
		delete _infoTuples; _infoTuples = NIL;
	}
	if (_activeLines != NIL) {
		delete _activeLines; _activeLines = NIL;
	}
}

NodeFigureList *Connection::nodeFigures()
{
	return _nodeFigures;
}

void Connection::clearLists()
{
	_nodeFigures->clear();
}

BOOL Connection::containedWithin(int x1,int y1,int x2,int y2)
{
	_moveAllFlag = FALSE;
	BOOL val = Lines::containedWithin(x1,y1,x2,y2);
	if (val == FALSE) return FALSE;
	NodeFigure *aNode = _nodeFigures->getFirst();
	while (aNode != NIL) {
		if (aNode->containedWithin(x1,y1,x2,y2) == FALSE) {
			_moveAllFlag = FALSE;
			return FALSE;
		}
		aNode = _nodeFigures->getNext();
	}
	_moveAllFlag = TRUE;
	return TRUE;
}

BOOL Connection::checkEntries(CRgn* reg)
{
	if (_visited) return TRUE;
	CRgn *tmp = createRegion();
	tmp->CombineRgn(reg,_region,RGN_OR);
	if (!reg->EqualRgn(tmp)) {
		delete tmp;
		return FALSE;
	}
	delete tmp;
	tmp = createRegion();
	NodeFigure *nodeFigure = _nodeFigures->getFirst();
	while (nodeFigure != NIL) {
		tmp->CombineRgn(tmp,nodeFigure->region(),RGN_OR);
		nodeFigure = _nodeFigures->getNext();
	}
	tmp->CombineRgn(reg,tmp,RGN_OR);
	if (!reg->EqualRgn(tmp)) {
		delete tmp;
		return FALSE;
	}
	delete tmp;
	_visited = TRUE;
	BOOL flag;
	nodeFigure = _nodeFigures->getFirst();
	while (nodeFigure != NIL) {
		flag = nodeFigure->checkEntries(reg);
		if (flag == FALSE) {
			_visited = FALSE;
			return FALSE;
		}
		nodeFigure = _nodeFigures->getNext();
	}
	return TRUE;
}

void Connection::remove(NodeFigure *nodeFigure)
{
	_nodeFigures->remove(nodeFigure,ABSOLUTELY);
}

void Connection::insert(NodeFigure *nodeFigure)
{
	_nodeFigures->insert(nodeFigure,ABSOLUTELY);
}

BOOL Connection::valid(NodeFigure *aNodeFigure)
{
	if (isSelfConnectionAllowable() == FALSE &&
		_nodeFigures->inList(aNodeFigure)) 
		return FALSE;
	return TRUE;
}

void Connection::minMaxXY()
{
	Lines::minMaxXY();
	if (_text != NIL) _text->minMaxXY();
}

void Connection::getMinMaxXY(int &minX,int &minY,int &maxX,int &maxY)
{
	Lines::getMinMaxXY(minX,minY,maxX,maxY);
	if (_text != NIL) _text->getMinMaxXY(minX,minY,maxX,maxY);
}

void Connection::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	Lines::draw(dcp);
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN &&
		_text != NIL && 
		_text->isEmpty() == FALSE) {
		_text->draw(dcp);
	}
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->draw(dcp);
			tuple = _infoTuples->getNext();
		}
	}
	if (_symbol != NIL) _symbol->draw(dcp);
}

void Connection::drawBoundary(CDC *dcp)
{
	Lines::draw(dcp);
	if (_text != NIL && 
		_text->isEmpty() == FALSE) {
		if (_moveAllFlag) {
			_text->drawBoundary(dcp);
		} else {
			_text->draw(dcp);
		}
	}
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			if (tuple->mark()) tuple->drawBoundary(dcp);
			else tuple->draw(dcp);
			tuple = _infoTuples->getNext();
		}
	}
	if (_symbol != NIL) _symbol->drawBoundary(dcp);
}

void Connection::drawDots(CDC* dcp)
{
	Lines::drawDots(dcp);
	if (_text != NIL && _text->isEmpty() == FALSE) _text->drawDots(dcp);
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->drawDots(dcp);
			tuple = _infoTuples->getNext();
		}
	}
}

void Connection::eraseDots(CDC* dcp)
{
	Lines::eraseDots(dcp);
	if (_text != NIL && _text->isEmpty() == FALSE) _text->eraseDots(dcp);
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->eraseDots(dcp);
			tuple = _infoTuples->getNext();
		}
	}
}

void Connection::comeOn(CDC* dcp,int dx,int dy)
{
	if (_moveAllFlag) {
		if (_controller->currentFocus()->whoAreYou()->equals(IAMBUCKET) == FALSE)
			move(dcp,dx,dy);
		return;
	}

	if (_movedFlag == TRUE) return;
	if (_controller->currentFocus()->whoAreYou()->equals(IAMBUCKET))
		_movedFlag = TRUE;

	drawing(dcp,dx,dy);
	if (_symbolMoveFlag && _symbol) {
		_symbol->move(dcp,dx,dy);
	}
}

void Connection::drawing(CDC* dcp,int dx,int dy)
{
	Lines::drawing(dcp,dx,dy);
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			if (tuple->mark()) tuple->move(dcp,dx,dy);
			tuple = _infoTuples->getNext();
		}
	}
}

void Connection::move(CDC *dcp,int dx,int dy)
{
	Lines::move(dcp,dx,dy);
	if (_moveAllFlag) {
		if (_infoTuples != NIL) {
			ConnectionInfoTuple *tuple = _infoTuples->getFirst();
			while(tuple != NIL) {
				tuple->move(dcp,dx,dy);
				tuple = _infoTuples->getNext();
			}
		}
		if (_text != NIL) _text->move(dcp,dx,dy);
		if (_symbol != NIL) _symbol->move(dcp,dx,dy);
	}
}

void Connection::moveCoord(int dx,int dy)
{
	Lines::moveCoord(dx,dy);
	if (_moveAllFlag) {
		if (_infoTuples != NIL) {
			ConnectionInfoTuple *tuple = _infoTuples->getFirst();
			while(tuple != NIL) {
				tuple->moveCoord(dx,dy);
				tuple = _infoTuples->getNext();
			}
		}
		if (_text != NIL) _text->moveCoord(dx,dy);
		if (_symbol != NIL) _symbol->moveCoord(dx,dy);
	}
}

void Connection::clear(CDC *dcp)
{
	Lines::clear(dcp);
	if (_text != NIL) _text->clear(dcp);
	if (_symbol != NIL) _symbol->clear(dcp);
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->clear(dcp);
			tuple = _infoTuples->getNext();
		}
	}
}

BOOL Connection::tryToDeleteOneLineSegment(NodeFigure *aNodeFigure)
{
	if (_infoTuples == NIL) return FALSE;
	ConnectionInfoTuple *aTuple = _infoTuples->findTupleFor(aNodeFigure);
	int x = aTuple->getX();
	int y = aTuple->getY();
	LineNode *aNode = _lines->getFirst();
	while (aNode != NIL) {
		Line *aLine = aNode->line();
		if (aLine->getX1() == x && aLine->getY1() == y) {
			_focusNode = aNode;
			break;
		} else if (aLine->getX2() == x && aLine->getY2() == y) {
			_focusNode = aNode;
			break;
		}
		aNode = _lines->getNext();
	}
	return tryToDeleteOneLineSegment();
}

BOOL Connection::tryToDeleteOneLineSegment()
{
	if (isLinearConnection(FALSE)) return FALSE;
	if (whoAreYou()->equals(IAMASSOCIATION)) return FALSE;
	if (_focusNode == NIL) return FALSE;
	_focus = _focusNode->line();
	if (_focusNode->beforeList()->isEmpty() == FALSE &&
		_focusNode->afterList()->isEmpty() == FALSE)
		return FALSE;
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	int startX = tuple->getX();
	int startY = tuple->getY();
	int x1 = ((Line *)_focus)->getX1();
	int y1 = ((Line *)_focus)->getY1();
	int x2 = ((Line *)_focus)->getX2();
	int y2 = ((Line *)_focus)->getY2();
	if (startX == x1 && startY == y1) return FALSE;
	if (startX == x2 && startY == y2) return FALSE;
	int where;
	if (_focusNode->beforeList()->isEmpty() == TRUE) {
		where = ATAFTER;
		ConnectionInfoTuple *aTuple = 
			_infoTuples->findTupleFor(x1,y1);
		NodeFigure *aNodeFigure = aTuple->nodeFigurePtr();
		_nodeFigures->remove(aNodeFigure);
		aNodeFigure->remove(this);
		_infoTuples->remove(aTuple);
		delete aTuple;
	} else {
		where = ATBEFORE;
		ConnectionInfoTuple *aTuple = 
			_infoTuples->findTupleFor(x2,y2);
		NodeFigure *aNodeFigure = aTuple->nodeFigurePtr();
		_nodeFigures->remove(aNodeFigure);
		aNodeFigure->remove(this);
		_infoTuples->remove(aTuple);
		delete aTuple;
	}
	LineNode *aLineNode = _focusNode;
	LineNode *nextNode = NIL;
	do {
		nextNode = findNextLineNode(aLineNode,where);
		int beforeCount = aLineNode->beforeList()->nOfList();
		int afterCount = aLineNode->afterList()->nOfList();
		removeLineNode(aLineNode);
		if (where == ATBEFORE &&
			beforeCount > 1) 
			break;
		if (where == ATAFTER &&
			afterCount > 1) 
			break;
		aLineNode = nextNode;
	} while (aLineNode != NIL);
	_focus = NIL;
	_focusNode = NIL;
	return TRUE;
}

void Connection::deleteFocusObject()
{
	if (_focus == _text) {
		delete _text; _text = NIL;
		_focus = NIL;
	} else if (_focus->whoAreYou()->isIn(WEAREONELINETEXTS)) {
		removeFromTupleList((Text *)_focus); delete _focus;
		_focus = NIL;
	} else if (_focus->whoAreYou()->equals(IAMQUALIFICATIONTEXT)) {
		removeFromTupleList((Text *)_focus); delete _focus;
		_focus = NIL;
	}
}

void Connection::resetOneLineTextIfObsolete(Text *text)
{
	if (text->whoAreYou()->isIn(WEAREONELINETEXTS) == FALSE) return;
	if (text->isObsolete() == FALSE) return;
	removeFromTupleList(text);
	delete text;
	_focus = NIL;
}

void Connection::removeFromTupleList(Text *text)
{
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->removeFromTuple(text);
			tuple = _infoTuples->getNext();
		}
	}
}

void Connection::makeRegion(CRgn *sourceClipRgn)
{
	Lines::makeRegion(sourceClipRgn);
	if (_text != NIL) {
		_text->makeRegion(sourceClipRgn);
	}
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->makeRegion(sourceClipRgn);
			tuple = _infoTuples->getNext();
		}
	}
}

void Connection::resetRegion()
{
	Lines::resetRegion();
	if (_text != NIL) {
		_text->resetRegion();
	}
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->resetRegion();
			tuple = _infoTuples->getNext();
		}
	}
}

void Connection::releaseRegion()
{
	Lines::releaseRegion();
	if (_text != NIL) {
		_text->releaseRegion();
	}
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->releaseRegion();
			tuple = _infoTuples->getNext();
		}
	}
}

BOOL Connection::onEnter(int x,int y)
{
	// 아래 조건 체크는 최악의 경우에 이벤트 처리가 얽혀서 생기는 문제를 방지하기 위함
	if (_controller->editingTag() == FALSE) _focus = NIL;
	if (_text != NIL && _text->onEnter(x,y)) {
		_focus = _text;
		return TRUE;
	}
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			_focus = tuple->onEnter(x,y);
			if (_focus != NIL) {
				return TRUE;
			}
			tuple = _infoTuples->getNext();
		}
	}
	return Lines::onEnter(x,y);
}

void Connection::setInCanvas(BOOL flag)
{
	Lines::setInCanvas(flag);
	if (_text != NIL) _text->setInCanvas(flag);
	if (_symbol != NIL) _symbol->setInCanvas(flag);
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->setInCanvas(flag);
			tuple = _infoTuples->getNext();
		}
	}
}

void Connection::setController(COODView *ptr)
{
	Lines::setController(ptr);
	if (_text != NIL) _text->setController(ptr);
	if (_symbol != NIL) _symbol->setController(ptr);
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->setController(ptr);
			tuple = _infoTuples->getNext();
		}
	}
}

BOOL Connection::checkInRegion(CRgn* someregion)
{
	if (Lines::checkInRegion(someregion)) return TRUE;
	if (_text != NIL && _text->checkInRegion(someregion)) return TRUE;
	if (_symbol != NIL && _symbol->checkInRegion(someregion)) return TRUE;
	return FALSE;
}

ConnectionInfoTuple* Connection::findTheNearestTuple(int x,int y,BOOL includeFirstTuple)
{
	int minDistance = OODMAXINT;
	ConnectionInfoTuple *foundTuple = NIL;
	if (_infoTuples == NIL) return NIL;
	ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
	if (includeFirstTuple == FALSE) {
		aTuple = _infoTuples->getNext();
	}
	while (aTuple != NIL) {
		int tupleX = aTuple->getX();
		int tupleY = aTuple->getY();
		int dist = distance(x,y,tupleX,tupleY);
		if (minDistance > dist) {
			minDistance = dist;
			foundTuple = aTuple;
		}
		aTuple = _infoTuples->getNext();
	}
	return foundTuple;
}

QualificationText *Connection::selectOrCreateQualification(int x,int y)
{
	ConnectionInfoTuple *aTuple = NIL;
	if (whoAreYou()->equals(IAMASSOCIATION)) {
		aTuple = findTheNearestTuple(x,y,TRUE);
	} else {
		return NIL;
	}
	if (aTuple == NIL) return NIL;
	AnytionInfoTuple *theTuple = (AnytionInfoTuple *)aTuple;
	QualificationText *theText = theTuple->selectOrCreateQualification(this);
	if (theText != NIL) {
		_focus = theText;
		return (QualificationText *)theText;
	}
	_focus = NIL;
	return NIL;
}

OneLineText *Connection::selectOrCreateMultiplicity(int x,int y)
{
	ConnectionInfoTuple *aTuple = NIL;
	if (whoAreYou()->equals(IAMASSOCIATION)) {
		aTuple = findTheNearestTuple(x,y,TRUE);
	} else {
		aTuple = findTheNearestTuple(x,y,FALSE);
	}
	if (aTuple == NIL) return NIL;
	AnytionInfoTuple *theTuple = (AnytionInfoTuple *)aTuple;
	OneLineText *theText = theTuple->selectOrCreateMultiplicity(this);
	if (theText != NIL) {
		_focus = theText;
		return (OneLineText *)theText;
	}
	_focus = NIL;
	return NIL;
}

OneLineText *Connection::selectOrCreateRoleName(int x,int y)
{
	ConnectionInfoTuple *aTuple = NIL;
	if (whoAreYou()->equals(IAMASSOCIATION) ||
		whoAreYou()->equals(IAMCOMMUNICATION)) {
		aTuple = findTheNearestTuple(x,y,TRUE);
	} else {
		aTuple = findTheNearestTuple(x,y,FALSE);
	}
	if (aTuple == NIL) return NIL;
	AnytionInfoTuple *theTuple = (AnytionInfoTuple *)aTuple;
	OneLineText *theText = theTuple->selectOrCreateRoleName(this);
	if (theText != NIL) {
		_focus = theText;
		return (OneLineText *)theText;
	}
	_focus = NIL;
	return NIL;
}

ConnectionText* Connection::selectOrCreateText()
{
	if (_text != NIL) {
		_focus = _text;
		return (ConnectionText *)_text;
	}
	_text = new ConnectionText(_controller,this,0,0,theAppPtr->theEditPopup);
	setTextPosition(-30,20,-10);
	return (ConnectionText *)_text;
}

Figure* Connection::born(Figure* ptr)
{
	Connection *copied;
	if (ptr == NIL) {
		copied = new Connection(NIL,NIL,NIL);
	} else {
		copied = (Connection *)ptr;
	}
	copied->_nodeFigures = new NodeFigureList();
	copied->_infoTuples = new CITList();
	copied->_activeLines = new LineNodeList();
	if (_text != NIL) {
		copied->_text = (ConnectionText *)_text->born();
		copied->_text->setConnectionPtr(copied);
	}
	if (_symbol != NIL) {
		copied->_symbol = (TwoPointFigure *)_symbol->born();
	}
	/*
	ConnectionInfoTuple *tmp = _infoTuples->getFirst();
	while (tmp != NIL) {
		ConnectionInfoTuple *ptr = new ConnectionInfoTuple(tmp);
		copied->_infoTuples->insert(ptr);
		tmp = _infoTuples->getNext();
	}
	*/
	return(Lines::born((Figure *)copied));
}

void Connection::replaceNodeFigurePtr(NodeFigure *from,NodeFigure *to)
{
	_nodeFigures->replacePointer(from,to);
	if (_infoTuples != NIL) {
		_infoTuples->replaceNodeFigurePtr(from,to);
	}
}

void Connection::resetMark()
{
	Lines::resetMark();
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while (tuple != NIL) {
			tuple->mark() = FALSE;
			tuple = _infoTuples->getNext();
		}
	}
}

BOOL Connection::amISink(NodeFigure *ptr)
{
	NodeFigure *tmp = _nodeFigures->getFirst();
	if (tmp == NIL) return FALSE;
	tmp = _nodeFigures->getNext();
	while(tmp != NIL) {
		if (tmp == ptr) return TRUE;
		tmp = _nodeFigures->getNext();
	}
	return FALSE;
}

BOOL Connection::amISource(NodeFigure *ptr)
{
	if (_nodeFigures->top() == ptr) return TRUE;
	return FALSE;
}

BOOL Connection::isSelfConnectionAllowable()
{
	// 일반적으로는 false고 assocation, transition 정도가 true 다.
	return FALSE;
}

BOOL Connection::ifAllConstraintSatisfied(NodeFigure *nodeFocus)
{
	if (_lines->nOfList() == 1 &&
		_nodeFigures->nOfList() == 1 &&
		_nodeFigures->getFirst() == nodeFocus) return FALSE;
	return TRUE;
}

BOOL Connection::isNeighborConnection(Figure *node)
{
	return _nodeFigures->inList((NodeFigure *)node);
}

BOOL Connection::abortDraw(BOOL printMsgFlag)
{
	if (printMsgFlag == TRUE) {
		char buffer[BUFSIZ];
		strcpy_s(buffer,BUFSIZ,"Wrong connection : Drawing ");
		strcat_s(buffer,BUFSIZ,connectionClassName());
		strcat_s(buffer,BUFSIZ," is aborted.");
		_controller->beep(buffer);
	} else {
		char buffer[BUFSIZ];
		strcpy_s(buffer,BUFSIZ,"Drawing ");
		strcat_s(buffer,BUFSIZ,connectionClassName());
		strcat_s(buffer,BUFSIZ," is aborted.");
		_controller->userMsg(buffer);
	}
	clearActiveLines();
	LineNode *tmp = _activeLines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		delete line;
		delete tmp;
		_lines->remove(tmp,TRUE);
		tmp = _activeLines->getNext();
	}
	_activeLines->clear();
	if (_lines->nOfList() == 0) {
		_controller->checkInList(this);
		_controller->remove(this);
		NodeFigure *ptr = _nodeFigures->getFirst();
		while (ptr != NIL) {
			ptr->remove(this);
			ptr = _nodeFigures->getNext();
		}
		return TRUE;
	} else {
		resetFocus();
		Lines::epilog(TRUE);
		makeRegion(_controller->canvasRgn());
		_controller->lowlightDraw(this);
		return FALSE;
	}
}

void Connection::continueDraw()
{
	_focusNode = _lines->getLast();
	_focus = _focusNode->line();
	if (_focus == NIL || _focusNode == NIL) {
		ErrorMsg("Connection::continueDraw()");
		return;
	}
	int x = ((Line *)_focus)->getX2();
	int y = ((Line *)_focus)->getY2();
	Line *aLine = new Line(_controller,x,y,NIL,STRAIGHT);
	Lines::insertALine(aLine,TRUE);
	LineNode *aNode = node(aLine);
	_activeLines->insert(aNode);
	aLine->setOrient(Line::invertOrient(_controller->currentOrient));
	aLine->setFollowing2(x,y);
	aLine->style() = _style;
}

BOOL Connection::stopDraw(CPoint point,NodeFigure *nodeFocus)
{
	// Abort를 원하면 TRUE를 리턴 
	int x = point.x;
	int y = point.y;
	if (_focus->whoAreYou()->equals(IAMLINE) == FALSE) {
		_focus = NIL;
		return TRUE;
	}
	Line *fLine = (Line *)_focus;
	fLine->setOrient();
	_controller->currentOrient = fLine->orient();
	resetHotXY();
	if (nodeFocus == NIL) return FALSE;
	if (ifAllConstraintSatisfied(nodeFocus) == FALSE) {
		return TRUE;  
	}
	// normal stopping procedure 
	_controller->lowlightDraw(nodeFocus);
	clearActiveLines();
	if (valid(nodeFocus) == FALSE) {
		return TRUE;
	}

	tailorEndLines(nodeFocus);
	if (setModelSpecificSymbol(nodeFocus)) {
		return TRUE;
	}
	_activeLines->clear();
	resetFocus();

	Lines::epilog(FALSE);

	nodeFocus->insert(this);
	insert(nodeFocus);
	makeRegion(_controller->canvasRgn());
	_controller->insert(this);
	_controller->lowlightDraw(this);
	_controller->Invalidate();
	return FALSE;
}

void Connection::setHotXYUsingDelta(int ox,int oy,int dx,int dy)
{
	if (_moveAllFlag) return;

	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			if (tuple->mark()) {
				tuple->moveCoord(dx,dy);
			}
			tuple = _infoTuples->getNext();
		}
	}
	if (_symbolMoveFlag && _symbol) _symbol->moveCoord(dx,dy);
	//  이 함수는 나중에 association을 위해 변경되어야 함
	if (_nOfDeltaList == 0) return;
	int newX = ox + _deltaList[0].x;
	int newY = oy + _deltaList[0].y;
	setHotXY(newX,newY);
}

BOOL Connection::connectedToOnlyOneNodeFigure(NodeFigure *leader)
{
	NodeFigure *aNode = _nodeFigures->getFirst();
	while(aNode != NIL) {
		if (aNode != leader) return FALSE;
		aNode = _nodeFigures->getNext();
	}
	return TRUE;
}

void Connection::initializeForMoveProlog()
{
	if (_moveAllFlag) return;
	if (whoAreYou()->isIn(WEARESIMPLECONNECTIONS)) return;

	_symbolMoveFlag = FALSE;

	_focusNode = NIL;
	_focus = NIL;
	resetHotXY();
	_nOfDeltaList = 0;

	ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
	while (aTuple != NIL) {
		aTuple->mark() = FALSE;
		aTuple = _infoTuples->getNext();
	}
	resetFlags();
}

void Connection::letsGoWithBucket(NodeFigure *leader)
{
	if (_moveAllFlag) return;

	int whereToMeet = -1;
	ConnectionInfoTuple *aTuple = _infoTuples->findTupleFor(leader);
	if (aTuple == NIL) {
		_moveAllFlag = TRUE;
		return;
	}
	aTuple->mark() = TRUE;
	int x = aTuple->getX();
	int y = aTuple->getY();
	LineNode *aNode = _lines->getFirst();
	while (aNode != NIL) {
		Line *line = aNode->line();
		int x1,y1,x2,y2;
		line->coords(x1,y1,x2,y2);
		if (x1 == x && y1 == y) {
			whereToMeet = ATBEFORE;
			break;
		}
		if (x2 == x && y2 == y) {
			whereToMeet = ATAFTER;
			break;
		}
		aNode = _lines->getNext();
	}
	if (aNode == NIL) {
		_moveAllFlag = TRUE;
		return;
	}
	Line *aLine = aNode->line();
	aLine->wantToResizeExact(x,y);
	Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
	newLine->setFollowing2(x,y);
	newLine->setOrient(Line::invertOrient(aLine->orient()));
	newLine->style() = _style;
	LineNode *newNode = new LineNode(newLine);
	newNode->mark() = TRUE;
	if (whereToMeet == ATBEFORE) {
		aNode->insertBefore(newNode);
		newNode->insertBefore(aNode);
	} else if (whereToMeet == ATAFTER) {
		aNode->insertAfter(newNode);
		newNode->insertBefore(aNode);
	} else {
		_moveAllFlag = TRUE;
		return;
	}
	_lines->insert(newNode);

/*
	_nOfDeltaList = 0;
	aTuple = _infoTuples->getFirst();
	while (aTuple != NIL) {
		if (aTuple->nodeFigurePtr() == leader) {
			int x = aTuple->getX();
			int y = aTuple->getY();
			_deltaList[_nOfDeltaList].x = x - leader->shape()->getX1();
			_deltaList[_nOfDeltaList].y = y - leader->shape()->getY1();
			_nOfDeltaList++;
		}
		aTuple = _infoTuples->getNext();
	}
*/
	_symbolMoveFlag = _symbolMoveFlag | amISource(leader);
}

void Connection::letsGo(NodeFigure *leader)
{
	if (_moveAllFlag) return;
	_focusNode = NIL;
	_focus = NIL;
	resetHotXY();
	_nOfDeltaList = 0;

	if (connectedToOnlyOneNodeFigure(leader) &&
		_nodeFigures->nOfList() >= 3) {
		_moveAllFlag = TRUE;
		ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
		while (aTuple != NIL) {
			aTuple->mark() = TRUE;
			aTuple = _infoTuples->getNext();
		}
		return;
	}

	ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
	while (aTuple != NIL) {
		aTuple->mark() = FALSE;
		aTuple = _infoTuples->getNext();
	}
	resetFlags();
	if (_lines->nOfList() == 1 &&
		_lines->getFirst()->line()->isObsolete() == TRUE) {
		// 약간 특수한 경우
		LineNode *aNode = _lines->getFirst();
		aNode->mark() = TRUE;
		Line *aLine = aNode->line();
		aLine->wantToResizeExact(aLine->getX1(),aLine->getY1());
		aTuple = _infoTuples->findTupleFor(leader,aLine->getX1(),aLine->getY1());
		if (aTuple != NIL) aTuple->mark() = TRUE;
		leader->setOrientForObsoleteLine(aLine);
		int x = aLine->notHotX()->get();
		int y = aLine->notHotY()->get();
		Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
		newLine->setFollowing2(x,y);
		newLine->setOrient(Line::invertOrient(aLine->orient()));
	    newLine->style() = _style;
		LineNode *newNode = new LineNode(newLine);
		aNode->insertAfter(newNode);
		aLine->setAbsoluteFollowPos(ATAFTER);
		newNode->insertBefore(aNode);
		_lines->insert(newNode);

		doAcompanySymbol(leader);
		return;
	} 
	TwoPointFigure *shape = leader->shape();
	if (shape != NIL) {
		LineNode *aNode = _lines->getFirst();
		while (aNode != NIL) {
			Line *aLine = aNode->line();
			if (aLine->isObsolete() &&
				shape->onBound(aLine) &&
				aNode->beforeList()->isEmpty()) {
				LineNode *bNode = aNode->afterList()->getFirst();
				if (bNode != NIL) {
					aNode->mark() = TRUE;
					aLine->setOrient(Line::invertOrient(bNode->line()->orient()));
				}
			} else if (aLine->isObsolete() &&
				shape->onBound(aLine) &&
				aNode->afterList()->isEmpty()) {
				LineNode *bNode = aNode->beforeList()->getFirst();
				if (bNode != NIL) {
					aNode->mark() = TRUE;
					aLine->setOrient(Line::invertOrient(bNode->line()->orient()));
				}
			}
			aNode = _lines->getNext();
		}
	}

	aTuple = _infoTuples->getFirst();
	while (aTuple != NIL) {
		if (aTuple->nodeFigurePtr() == leader) {
			int x = aTuple->getX();
			int y = aTuple->getY();
			_deltaList[_nOfDeltaList].x = x - leader->shape()->getX1();
			_deltaList[_nOfDeltaList].y = y - leader->shape()->getY1();
			_nOfDeltaList++;
			LineNode *tmp = _lines->getFirst();
			while (tmp != NIL) {
				Line *line = tmp->line();
				if (line->hotX() == NIL && line->hotY() == NIL) {
					if (tmp->beforeList()->isEmpty() ||
						tmp->afterList()->isEmpty()) {
						BOOL ok = line->wantToResizeExact(x,y);
						// 아래 검사는 특수한 경우임, obsolete point옆의 라인과 관련 ...
						int otherSideX = line->notHotX()->get();
						int otherSideY = line->notHotY()->get();
						NodeFigure *aNodeFigure = _nodeFigures->getFirst();
						while(aNodeFigure != NIL) {
							if (ok == TRUE &&
								aNodeFigure != leader &&
								aNodeFigure->shape() != NIL &&
								aNodeFigure->shape()->contains(otherSideX,otherSideY) &&
								tmp->hasObsoletePointNeighborAt(line->hotX()->get(),line->hotY()->get())) {
								line->resetHotXY();
								break;
							}
							aNodeFigure = _nodeFigures->getNext();
						}
					}
				}
				tmp = _lines->getNext();
			}
			aTuple->mark() = TRUE;
		}
		aTuple = _infoTuples->getNext();
	}
	
	resizeProlog(leader);

	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		aNode->move() = FALSE;
		aNode = _lines->getNext();
	}

	aNode = _lines->getFirst();
	while (aNode != NIL) {
		Line *aLine = aNode->line();
		int x1 = aLine->getX1();
		int y1 = aLine->getY1();
		int x2 = aLine->getX2();
		int y2 = aLine->getY2();
		if (aNode->beforeList()->isEmpty() == FALSE &&
			aNode->afterList()->isEmpty() == FALSE) {
			LineNode *bNode = aNode->beforeList()->getFirst();
			while (bNode != NIL) {
				Line *bLine = bNode->line();
				if (aLine != bLine &&
					bNode->mark() == TRUE &&
					bLine->hotX() != NIL &&
					bLine->hotY() != NIL) {
						int otherSideX = bLine->notHotX()->get();
						int otherSideY = bLine->notHotY()->get();
						if (x1 == otherSideX &&
							y1 == otherSideY) {
							aNode->move() = TRUE;
						}
				}
				bNode = aNode->beforeList()->getNext();
			}
			if (aNode->move() == TRUE) {
				bNode = aNode->afterList()->getFirst();
				while (bNode != NIL) {
					Line *bLine = bNode->line();
					if (aLine != bLine &&
						bNode->mark() == TRUE &&
						bLine->hotX() != NIL &&
						bLine->hotY() != NIL) {
							int otherSideX = bLine->notHotX()->get();
							int otherSideY = bLine->notHotY()->get();
							if (x2 == otherSideX &&
								y2 == otherSideY) {
								aNode->move() = TRUE;
								aNode->mark() = FALSE;
								aLine->resetHotXY();
								break;
							} else {
								aNode->move() = FALSE;
							}
					} else {
						aNode->move() = FALSE;
					}
					bNode = aNode->afterList()->getNext();
				}
			}
		}
		aNode = _lines->getNext();
	}
	/*
	BOOL selfConnection = FALSE;
	if (_lines->nOfList() == 3) {
		int markCount = 0;
		aTuple = _infoTuples->getFirst();
		while (aTuple != NIL) {
			if (aTuple->mark()) {
				markCount++;
			}
			aTuple = _infoTuples->getNext();
		}
		if (markCount == 2) selfConnection = TRUE;
	}
	if (selfConnection) {
		LineNode *newNodes[2];
		newNodes[0] = NIL;
		newNodes[1] = NIL;
		int i = 0;
		LineNode *aNode = _lines->getFirst();
		while (aNode != NIL) {
			Line *aLine = aNode->line();
			if (aLine->hotX() != NIL && aLine->hotY() != NIL) {
				aNode->mark() = TRUE;
				int x = aLine->notHotX()->get();
				int y = aLine->notHotY()->get();
				Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
				newLine->setFollowing2(x,y);
				newLine->setOrient(Line::invertOrient(aLine->orient()));
				newLine->style() = _style;
				LineNode *newNode = new LineNode(newLine);
				aNode->insertObsoleteNode(newNode);
				newNode->insertBefore(aNode);
				newNodes[i] = newNode;
				i++;
			}
			aNode = _lines->getNext();
		}
		if (newNodes[0] != NIL) _lines->insert(newNodes[0]);
		if (newNodes[1] != NIL)  _lines->insert(newNodes[1]);
	} else {
		resizeProlog(leader);
	}
	*/

	if (_lines->nOfList() == 1) {
		LineNode *aNode = _lines->getFirst();
		Line *aLine = aNode->line();
		int x = aLine->notHotX()->get();
		int y = aLine->notHotY()->get();
		Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
		newLine->setFollowing2(x,y);
		newLine->setOrient(Line::invertOrient(aLine->orient()));
		newLine->style() = _style;
		LineNode *newNode = new LineNode(newLine);
		aNode->insertObsoleteNode(newNode);
		newNode->insertBefore(aNode);
		_lines->insert(newNode);
	}
	doAcompanySymbol(leader);
}

void Connection::doAcompanySymbol(NodeFigure *leader)
{
	_symbolMoveFlag = amISource(leader);
}

BOOL Connection::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	return FALSE;
}

void Connection::tailorEndLines(NodeFigure *lastNode)
{
	if (_lines->nOfList() == _activeLines->nOfList()) {
		// 처음 그리는 경우
		NodeFigure *majorNode = _nodeFigures->getFirst();
		Line *startLine = _activeLines->getFirst()->line();
		majorNode->adjustLine(startLine,TRUE);
		Line *lastLine = _activeLines->getLast()->line();
		if (lastNode->adjustLine(lastLine,FALSE)) {
			// obsolete case
			lastLine->setXY2(lastLine->getX1(),lastLine->getY1());
		}
	} else {
		// fork 시키는 경우
		Line *lastLine = _activeLines->getLast()->line();
		if (lastNode->adjustLine(lastLine,FALSE)) {
			// obsolete case
			lastLine->setXY2(lastLine->getX1(),lastLine->getY1());
		}
	}
}

void Connection::clearActiveLines()
{
	LineNode *tmp = _activeLines->getFirst();
	while (tmp != NIL) {
		_controller->clear(tmp->line());
		tmp = _activeLines->getNext();
	}
}

int Connection::getBoundaryLineOrient(int x,int y)
{
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		if (tmp->afterList()->nOfList() == 0) {
			Line * aLine = tmp->line();
			int x2 = aLine->getX2();
			int y2 = aLine->getY2();
			if (x == x2 && y == y2) {
				if (aLine->isObsolete()) return NORTH;
				return aLine->orient();
			}
		}
		if (tmp->beforeList()->nOfList() == 0) {
			Line * aLine = tmp->line();
			int x1 = aLine->getX1();
			int y1 = aLine->getY1();
			if (x == x1 && y == y1) {
				if (aLine->isObsolete()) return NORTH;
				return aLine->orient();
			}
		}
		tmp = _lines->getNext();
	}
	return NORTH;
}

BOOL Connection::containJointPointIn(NodeFigure *nodeFigure,LineNodeList *lines)
{
	TwoPointFigure *shape = nodeFigure->shape();
	if (shape == NIL) return FALSE;
	LineNode *aNode = lines->getFirst();
	while(aNode != NIL) {
		if (aNode->beforeList()->nOfList() > 1) {
			int x = aNode->line()->getX1();
			int y = aNode->line()->getY1();
			if (shape->contains(x,y)) return TRUE;
		} else if (aNode->afterList()->nOfList() > 1) {
			int x = aNode->line()->getX2();
			int y = aNode->line()->getY2();
			if (shape->contains(x,y)) return TRUE;
		}
		aNode = lines->getNext();
	}
	return FALSE;
}

LineNode* Connection::extendLineToNodeFigure(int whichSide,ConnectionInfoTuple *aTuple,
									LineNode *aNode,NodeFigure *aNodeFigure)
{
	if (whichSide == I_SIDE) return NIL;
	if (whichSide == II_SIDE) return NIL;
	if (whichSide == VI_SIDE) return NIL;
	if (whichSide == VII_SIDE) return NIL;
	if (whichSide == VIII_SIDE) return NIL;
	int tupleX = aTuple->getX();
	int tupleY = aTuple->getY();
	int x1,y1,x2,y2;
	Line *aLine = aNode->line();
	int orient = aLine->orient();
	if (orient == UNDEFINED) return NIL;
	aLine->coords(x1,y1,x2,y2);
	if (aNodeFigure->shape() == NIL) return NIL;
	int boxX1 = aNodeFigure->shape()->getX1();
	int boxY1 = aNodeFigure->shape()->getY1();
	int boxX2 = aNodeFigure->shape()->getX2();
	int boxY2 = aNodeFigure->shape()->getY2();
	if (x1 == tupleX && y1 == tupleY && 
		aNode->beforeList()->isEmpty()) {
		if (whichSide == III_SIDE && orient == NORTH) {
			aTuple->setX(boxX2);
			Line *newLine = new Line(_controller,x1,y1,boxX2,y1,NIL,STRAIGHT);
			newLine->setOrient(EAST);
			newLine->style() = _style;
			LineNode *newNode = new LineNode(newLine);
			aNode->insertBefore(newNode);
			newNode->insertBefore(aNode);
			return newNode;
		} else if (whichSide == III_SIDE && orient == EAST) {
			aTuple->setX(boxX2);
			aLine->_x1.set(boxX2);
			return NIL;
		} else if (whichSide == IV_SIDE && orient == NORTH) {
			int newY = getRandom(boxY1,boxY2);
			aLine->_y1.set(newY);
			aTuple->setXY(boxX2,newY);
			Line *newLine = new Line(_controller,x1,newY,boxX2,newY,NIL,STRAIGHT);
			newLine->setOrient(EAST);
			newLine->style() = _style;
			LineNode *newNode = new LineNode(newLine);
			aNode->insertBefore(newNode);
			newNode->insertBefore(aNode);
			return newNode;
		} else if (whichSide == IV_SIDE && orient == EAST) {
			int newX = getRandom(boxX1,boxX2);
			aLine->_x1.set(newX);
			aTuple->setXY(newX,boxY2);
			Line *newLine = new Line(_controller,newX,y1,newX,boxY2,NIL,STRAIGHT);
			newLine->setOrient(NORTH);
			newLine->style() = _style;
			LineNode *newNode = new LineNode(newLine);
			aNode->insertBefore(newNode);
			newNode->insertBefore(aNode);
			return newNode;
		} else if (whichSide == V_SIDE && orient == NORTH) {
			aTuple->setY(boxY2);
			aLine->_y1.set(boxY2);
			return NIL;
		} else if (whichSide == V_SIDE && orient == EAST) {
			aTuple->setY(boxY2);
			Line *newLine = new Line(_controller,x1,y1,x1,boxY2,NIL,STRAIGHT);
			newLine->setOrient(NORTH);
			newLine->style() = _style;
			LineNode *newNode = new LineNode(newLine);
			aNode->insertBefore(newNode);
			newNode->insertBefore(aNode);
			return newNode;
		} 
	} else if (x2 == tupleX && y2 == tupleY && 
		aNode->afterList()->isEmpty()) {
		if (whichSide == III_SIDE && orient == NORTH) {
			aTuple->setX(boxX2);
			Line *newLine = new Line(_controller,x2,y2,boxX2,y2,NIL,STRAIGHT);
			newLine->setOrient(EAST);
			newLine->style() = _style;
			LineNode *newNode = new LineNode(newLine);
			aNode->insertAfter(newNode);
			newNode->insertBefore(aNode);
			return newNode;
		} else if (whichSide == III_SIDE && orient == EAST) {
			aTuple->setX(boxX2);
			aLine->_x2.set(boxX2);
			return NIL;
		} else if (whichSide == IV_SIDE && orient == NORTH) {
			int newY = getRandom(boxY1,boxY2);
			aLine->_y2.set(newY);
			aTuple->setXY(boxX2,newY);
			Line *newLine = new Line(_controller,x2,newY,boxX2,newY,NIL,STRAIGHT);
			newLine->setOrient(EAST);
			newLine->style() = _style;
			LineNode *newNode = new LineNode(newLine);
			aNode->insertAfter(newNode);
			newNode->insertBefore(aNode);
			return newNode;
		} else if (whichSide == IV_SIDE && orient == EAST) {
			int newX = getRandom(boxX1,boxX2);
			aLine->_x2.set(newX);
			aTuple->setXY(newX,boxY2);
			Line *newLine = new Line(_controller,newX,y2,newX,boxY2,NIL,STRAIGHT);
			newLine->setOrient(NORTH);
			newLine->style() = _style;
			LineNode *newNode = new LineNode(newLine);
			aNode->insertAfter(newNode);
			newNode->insertBefore(aNode);
			return newNode;
		} else if (whichSide == V_SIDE && orient == NORTH) {
			aTuple->setY(boxY2);
			aLine->_y2.set(boxY2);
			return NIL;
		} else if (whichSide == V_SIDE && orient == EAST) {
			aTuple->setY(boxY2);
			Line *newLine = new Line(_controller,x2,y2,x2,boxY2,NIL,STRAIGHT);
			newLine->setOrient(NORTH);
			newLine->style() = _style;
			LineNode *newNode = new LineNode(newLine);
			aNode->insertAfter(newNode);
			newNode->insertBefore(aNode);
			return newNode;
		} 
	}
	return NIL;
}

void Connection::extendToNodeFigure(NodeFigure *aNodeFigure)
{
	if (_infoTuples == NIL) return;
	LineNodeList *newNodes = new LineNodeList();

	ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
	while(aTuple != NIL) {
		if (aTuple->nodeFigurePtr() == aNodeFigure) {
			int tx = aTuple->getX();
			int ty = aTuple->getY();
			Line *theLine = NIL;
			LineNode *aNode = _lines->getFirst();
			while(aNode != NIL) {
				int x1,y1,x2,y2;
				Line *aLine = aNode->line();
				aLine->coords(x1,y1,x2,y2);
				if (x1 == tx && y1 == ty &&
					aNode->beforeList()->isEmpty()) {
					theLine = aLine;
					break;
				} else if (x2 == tx && y2 == ty &&
					aNode->afterList()->isEmpty()) {
					theLine = aLine;
					break;
				}
				aNode = _lines->getNext();
			}
			if (theLine != NIL &&
				aNodeFigure->contains(theLine->getX1(),theLine->getY1()) &&
				aNodeFigure->contains(theLine->getX2(),theLine->getY2()) &&
				aNodeFigure->shape() != NIL) {
				int boxX1 = aNodeFigure->shape()->getX1();
				int boxY1 = aNodeFigure->shape()->getY1();
				int boxX2 = aNodeFigure->shape()->getX2();
				int boxY2 = aNodeFigure->shape()->getY2();
				LineNode *aNode = _lines->getFirst();
				while(aNode != NIL) {
					int x1,y1,x2,y2;
					Line *aLine = aNode->line();
					int orient = aLine->orient();
					if (orient == UNDEFINED) break;
					aLine->coords(x1,y1,x2,y2);
					if (x1 == tx && y1 == ty &&
						aNode->beforeList()->isEmpty()) {
						if (orient == NORTH) {
							aTuple->setY(boxY2);
							aLine->_y1.set(boxY2);
						} else if (orient == EAST) {
							aTuple->setX(boxX2);
							aLine->_x1.set(boxX2);
						}
					} else if (x2 == tx && y2 == ty &&
						aNode->afterList()->isEmpty()) {
						if (orient == NORTH) {
							aTuple->setY(boxY2);
							aLine->_y2.set(boxY2);
						} else if (orient == EAST) {
							aTuple->setX(boxX2);
							aLine->_x2.set(boxX2);
						}
					}
					aNode = _lines->getNext();
				}
			} else if (aNodeFigure->contains(tx,ty) == FALSE) {
				int whichSide = aNodeFigure->onWhichSideRegion(tx,ty);
				if (whichSide != O_SIDE) {
					LineNode *aNode = _lines->getFirst();
					while(aNode != NIL) {
						LineNode *newNode =
							extendLineToNodeFigure(whichSide,aTuple,aNode,aNodeFigure);
						if (newNode != NIL) {
							newNodes->insert(newNode);
						}
						aNode = _lines->getNext();
					}
				}
			}
		}
		aTuple = _infoTuples->getNext();
	}
	LineNode *newNode = newNodes->getFirst();
	while(newNode != NIL) {
		_lines->insert(newNode);
		newNode = newNodes->getNext();
	}
	newNodes->clear();
	delete newNodes;
}

void Connection::tailorEndLinesAll()
{
	if (_lines->nOfList() <= 0) return;
	if (_lines->nOfList() == 1) {
		Line *aLine = _lines->getFirst()->line();
		if (aLine->isObsolete()) return;
	}
	NodeFigure *nodeFigure = _nodeFigures->getFirst();
	while(nodeFigure != NIL) {
		if (nodeFigure->contains(_lines)) return;
		nodeFigure = _nodeFigures->getNext();
	}
	BOOL breakflag = FALSE;
	nodeFigure = _nodeFigures->getFirst();
	while(nodeFigure != NIL) {
		LineNode *aNode = _lines->getFirst();
		while(aNode != NIL) {
			int x1,y1,x2,y2;
			BOOL obsolete;
			Line *aLine = aNode->line();
			aLine->coords(x1,y1,x2,y2);
			TwoPointFigure *shape = nodeFigure->shape();
			if (shape != NIL &&
				aLine->isObsolete() == TRUE &&
				shape->onBound(aLine) == TRUE) {
				aNode = _lines->getNext();
				continue;
			}
			LineNodeList *copiedLines = new LineNodeList();
			copiedLines->copy(_lines);
			if (nodeFigure->contains(x1,y1) &&
					aNode->beforeList()->isEmpty() &&
					containJointPointIn(nodeFigure,copiedLines) == FALSE) {
				ConnectionInfoTuple *tuple = _infoTuples->findTupleFor(nodeFigure,x1,y1);
				if (tuple) {
					obsolete = nodeFigure->adjustLine(aLine,TRUE);
					int a1,b1,a2,b2;
					aLine->coords(a1,b1,a2,b2);
					if (obsolete) {
						tuple->setXY(a2,b2);
					} else {
						tuple->setXY(a1,b1);
					}
					if (obsolete) {
						if (_lines->nOfList() == 1) {
							aLine->_x1.set(a2);
							aLine->_y1.set(b2);
							tuple->setXY(a2,b2);
							delete copiedLines;
							return;
						}
						removeLineNode(aNode);
						breakflag = TRUE;
						delete copiedLines;
						break;
					}
				}
			} 
			delete copiedLines;
			copiedLines = new LineNodeList();
			copiedLines->copy(_lines);
			if (nodeFigure->contains(x2,y2) && 
					aNode->afterList()->isEmpty() &&
					containJointPointIn(nodeFigure,copiedLines) == FALSE) {
				ConnectionInfoTuple *tuple = _infoTuples->findTupleFor(nodeFigure,x2,y2);
				if (tuple) {
					obsolete = nodeFigure->adjustLine(aLine,FALSE);
					int a1,b1,a2,b2;
					aLine->coords(a1,b1,a2,b2);
					if (obsolete) {
						tuple->setXY(a1,b1);
					} else {
						tuple->setXY(a2,b2);
					}
					if (obsolete) {
						if (_lines->nOfList() == 1) {
							aLine->_x2.set(a1);
							aLine->_y2.set(b1);
							tuple->setXY(a1,b1);
							delete copiedLines;
							return;
						}
						removeLineNode(aNode);
						breakflag = TRUE;
						delete copiedLines;
						break;
					}
				}
			}
			delete copiedLines;
			aNode = _lines->getNext();
		}
		if (breakflag) {
			breakflag = FALSE;
			nodeFigure = _nodeFigures->getFirst();
		} else {
			nodeFigure = _nodeFigures->getNext();
		}
	}
}

void Connection::setModelSpecificSymbolAll()
{
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		tuple->locateTupleTextOnProperPosition(this);
		tuple = _infoTuples->getNext();
	}
}

BOOL Connection::wantToResize(int &x,int &y)
{
	if (_infoTuples != NIL) {
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			int px = tuple->getX();
			int py = tuple->getY();
			if (TwoPointFigure::wantToResize(x,y,px,py) == TRUE)
				return FALSE; // 끝에 꼭지점은 절대 resize하면 안됨 
			tuple = _infoTuples->getNext();
		}
	}
	return Lines::wantToResize(x,y);
}

BOOL Connection::moveProlog(BOOL moveAllFlag)
{
	if (Lines::moveProlog(moveAllFlag)) return TRUE;
	if (_focusNode == NIL || _focus == NIL) return TRUE;
	int x,y;
	if (_focusNode->beforeList()->isEmpty()) {
		x = ((Line *)_focus)->getX1();
		y = ((Line *)_focus)->getY1();

		Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
		newLine->setOrient(Line::invertOrient(((Line *)_focus)->orient()));
		newLine->setFollowing2(x,y);
		newLine->style() = _style;
		LineNode *newNodeA = new LineNode(newLine);
		newNodeA->mark() = TRUE;
		_focusNode->insertBefore(newNodeA);
		newNodeA->insertAfter(_focusNode);
		_lines->insert(newNodeA);
	}
	if (_focusNode->afterList()->isEmpty()) {
		x = ((Line *)_focus)->getX2();
		y = ((Line *)_focus)->getY2();

		Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
		newLine->setOrient(Line::invertOrient(((Line *)_focus)->orient()));
		newLine->setFollowing2(x,y);
		newLine->style() = _style;
		LineNode *newNodeA = new LineNode(newLine);
		newNodeA->mark() = TRUE;
		_focusNode->insertAfter(newNodeA);
		newNodeA->insertAfter(_focusNode);
		_lines->insert(newNodeA);
	}

	LineNodeList *allNewLineNodes = new LineNodeList();
	LineNodeList *newLineNodes = new LineNodeList();
	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		// 노드에 붙어야할 cascade follow line 만들기
		Line *aLine = aNode->line();
		if (aNode->mark() && aLine != _focus) {
			aNode->setFollowLinesOnNodeBoundary(newLineNodes);
			LineNode *newNode = newLineNodes->getFirst();
			while (newNode != NIL) {
				allNewLineNodes->insert(newNode);
				newNode = newLineNodes->getNext();
			}
			newLineNodes->clear();
		}
		aNode = _lines->getNext();		
	}

	LineNode *newNode = allNewLineNodes->getFirst();
	while (newNode != NIL) {
		_lines->insert(newNode);
		newNode = allNewLineNodes->getNext();
	}
    delete allNewLineNodes;
	delete newLineNodes;
	clearSymbolIfFirstLine();
	return FALSE;
}

void Connection::resizeProlog(NodeFigure* nodeFigure)
{
	if (_type == ORDINARY) return;
	BOOL deleteSymbol = FALSE;
	if (_lines->nOfList() == 1) deleteSymbol = TRUE;
	Lines::resizeProlog();
	if (nodeFigure == NIL) { // ordinary case
		LineNodeList *newNodes = new LineNodeList();
		LineNode *aNode = _lines->getFirst();
		while(aNode != NIL) {
			if (aNode->mark()) {
				Line *aLine = aNode->line();
				int x,y;
				if (aNode->beforeList()->isEmpty()) {
					x = aLine->getX1();
					y = aLine->getY1();
					Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
					newLine->setFollowing2(x,y);
					newLine->setOrient(Line::invertOrient(aLine->orient()));
					newLine->style() = _style;
					LineNode *newNode = new LineNode(newLine);
					aNode->insertBefore(newNode);
					newNode->insertAfter(aNode);
					newNodes->insert(newNode);
				} else if (aNode->afterList()->isEmpty()) {
					x = aLine->getX2();
					y = aLine->getY2();
					Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
					newLine->setFollowing2(x,y);
					newLine->setOrient(Line::invertOrient(aLine->orient()));
					newLine->style() = _style;
					LineNode *newNode = new LineNode(newLine);
					aNode->insertAfter(newNode);
					newNode->insertAfter(aNode); // 이거 맞음
					newNodes->insert(newNode);
				}
			}
			aNode = _lines->getNext();
		}
		LineNode *newNode = newNodes->getFirst();
		while (newNode != NIL) {
			_lines->insert(newNode);
			newNode = newNodes->getNext();
		}
		delete newNodes;
	}
	if (nodeFigure && _nodeFigures->getFirst() == nodeFigure) {
		return;
	}
	if (deleteSymbol && _symbol != NIL) {
		_controller->clear(_symbol);
		delete _symbol;
		_symbol = NIL;
		return;
	}
	clearSymbolIfFirstLine();
}

void Connection::clearSymbolIfFirstLine()
{
	ConnectionInfoTuple *firstTuple = _infoTuples->getFirst();
	int x = firstTuple->getX();
	int y = firstTuple->getY();
	LineNode *aLineNode = _lines->getFirst();
	while (aLineNode != NIL) {
		Line *aLine = aLineNode->line();
		if (aLine->hotX() != NIL && aLine->hotY() != NIL) {
			int hX = aLine->hotX()->get();
			int hY = aLine->hotY()->get();
			if (hX == x && hY == y) {
				if (_symbol != NIL) {
					_controller->clear(_symbol);
					delete _symbol;
					_symbol = NIL;
				}
				return;
			}
		}
		aLineNode = _lines->getNext();
	}
}

BOOL Connection::isLinearConnection(BOOL abortionFlag)
{
	if (abortionFlag == TRUE &&
		_nodeFigures->nOfList() == 2) {
		return TRUE;
	} else if (abortionFlag == TRUE &&
		_nodeFigures->nOfList() != 2) {
		return FALSE;
	}
	if (_controller->currentConnection() == NIL && 
		_nodeFigures->nOfList() == 2) {
		// NodeFigure를 움직이는 중
		return TRUE;
	} 
	if (_controller->currentConnection() != NIL &&
		_nodeFigures->nOfList() == 1) {
		// Connection을 그리는 중
		return TRUE;
	} 
	return FALSE;
}

void Connection::getPreferedPointOnNodeFigureVertex(int &preferedX,int &preferedY,NodeFigure *nodeFigure)
{
	// 가능하면 모서리쪽의 좌표를 구하기 위한 함수다.
	if (nodeFigure->shape() == NIL) return;
	TwoPointFigure *aShape = nodeFigure->shape();
	preferedX = aShape->getX1(); preferedY = aShape->getY1();
	ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
	while (aTuple != NIL) {
		if (aTuple->getX() == preferedX &&
			aTuple->getY() == preferedY) 
			return;
		aTuple = _infoTuples->getNext();
	}
	preferedX = aShape->getX2(); preferedY = aShape->getY1();
	aTuple = _infoTuples->getFirst();
	while (aTuple != NIL) {
		if (aTuple->getX() == preferedX &&
			aTuple->getY() == preferedY) 
			return;
		aTuple = _infoTuples->getNext();
	}
	preferedX = aShape->getX1(); preferedY = aShape->getY2();
	aTuple = _infoTuples->getFirst();
	while (aTuple != NIL) {
		if (aTuple->getX() == preferedX &&
			aTuple->getY() == preferedY) 
			return;
		aTuple = _infoTuples->getNext();
	}
	preferedX = aShape->getX2(); preferedY = aShape->getY2();
	aTuple = _infoTuples->getFirst();
	while (aTuple != NIL) {
		if (aTuple->getX() == preferedX &&
			aTuple->getY() == preferedY) 
			return;
		aTuple = _infoTuples->getNext();
	}
	preferedX = -1; preferedY = -1;
}

CPoint *Connection::collectTuplePoints(int &nPoints)
{
	nPoints = _infoTuples->nOfList();
	if (nPoints == 0) return NIL;
	CPoint *points = new CPoint[nPoints];
	ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
	int n = 0;
	while(aTuple != NIL) {
		points[n].x = aTuple->getX();
		points[n].y = aTuple->getY();
		n++;
		aTuple = _infoTuples->getNext();
	}
	return points;
}

void Connection::boundaryLineCheck()
{
	int nEndPoints = _infoTuples->nOfList();
	int nCount;
	BOOL satisfied = FALSE;
	while(!satisfied) {
		satisfied = TRUE;
		resetMark();
		nCount = 0;
		// mark되는 노드들은 tuple에 없는 endLine들이다. 지워야 한다.
		LineNode *aNode = _lines->getFirst();
		while (aNode != NIL) {
			Line *aLine = aNode->line();
			if (aNode->beforeList()->isEmpty()) {
				int x = aLine->getX1();
				int y = aLine->getY1();
				nCount++;
				aNode->mark() = TRUE;
				ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
				int n = 0;
				while(aTuple != NIL) {
					int tx = aTuple->getX();
					int ty = aTuple->getY();
					if (x == tx && y == ty) {
						// OK, matched ...
						aNode->mark() = FALSE;
						break;
					}
					aTuple = _infoTuples->getNext();
				}
			}
			if (aNode->afterList()->isEmpty()) {
				int x = aLine->getX2();
				int y = aLine->getY2();
				nCount++;
				aNode->mark() = TRUE;
				ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
				int n = 0;
				while(aTuple != NIL) {
					int tx = aTuple->getX();
					int ty = aTuple->getY();
					if (x == tx && y == ty) {
						// OK, matched ...
						aNode->mark() = FALSE;
						break;
					}
					aTuple = _infoTuples->getNext();
				}
			}
			aNode = _lines->getNext();
		}
		
		aNode = _lines->getFirst();
		while (aNode != NIL) {
			if (aNode->mark() == TRUE) {
				delete aNode->line();
				delete aNode;
				_lines->remove(aNode,TRUE);
				satisfied = FALSE;
				break;
			}
			aNode = _lines->getNext();
		}
	}
	if (nEndPoints == nCount) return;
}

BOOL Connection::isBoundOnOneObject()
{
	// 이 경우는 한 커넥션의 여러 라인이 한 노드에 붙는 경우다. 
	FigureList aList;
	NodeFigure *aNodeFigure = _nodeFigures->getFirst();
	while(aNodeFigure != NIL) {
		aList.insert(aNodeFigure);
		aNodeFigure = _nodeFigures->getNext();
	}
	if (aList.nOfList() == _nodeFigures->nOfList()) return FALSE;
	return TRUE;
}

BOOL Connection::severalLinesOnNodeFigureBoundary()
{
	NodeFigure *aNodeFigure = _nodeFigures->getFirst();
	while(aNodeFigure != NIL) {
		int count = 0;
		LineNode *aNode = _lines->getFirst();
		while(aNode != NIL) {
			Line *aLine = aNode->line();
			int x1 = aLine->getX1();
			int y1 = aLine->getY1();
			int x2 = aLine->getX2();
			int y2 = aLine->getY2();
			int len = aLine->length();
			if ((len <= 1 &&
				aNodeFigure->containsOnLargeBound(x1,y1)) ||
				(len <= 1 &&
				aNodeFigure->containsOnLargeBound(x2,y2)) ||
				aNodeFigure->onBound(aLine)) {
				count++;
			}
			aNode = _lines->getNext();
		}
		if (count > 1) {
			return TRUE;
		}
		aNodeFigure = _nodeFigures->getNext();
	}
	return FALSE;
}

void Connection::epilog(BOOL abortionFlag)
{
	if (_moveAllFlag) return;
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		tuple->mark() = FALSE;
		tuple = _infoTuples->getNext();
	}
	BOOL boundOnOneObjectFlag = isBoundOnOneObject();
	BOOL linearConnection = isLinearConnection(abortionFlag);
	if (_lines->nOfList() > 1) {
		if (boundOnOneObjectFlag == FALSE &&
			linearConnection == FALSE) {
			epilogForMovingAndResizing();
		} else if (boundOnOneObjectFlag == FALSE &&
			linearConnection == TRUE) {
			epilogForLinearConnection();
			remake();
		} else if (boundOnOneObjectFlag == TRUE &&
			linearConnection == TRUE) {
			epilogForLinearAndSelfConnection();
			remake();
		} else if (boundOnOneObjectFlag == TRUE &&
			linearConnection == FALSE) {
			if (severalLinesOnNodeFigureBoundary() == FALSE) {
				epilogForMovingAndResizing();
			} else {
				if (checkIfThereIsOverlapLine() == FALSE) {
					remake();
				} else {
					// nothing to do, very strange shape
					setModelSpecificSymbolAll();
					return;
				}
			}
		}
	}
	if (_lines->nOfList() == 0) {
		// 아마 이 부분은 수행될 일이 거의 없을것이다.
		ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
		int x = aTuple->getX();
		int y = aTuple->getY();
		Line *newLine = new Line(_controller,x,y,x,y,NIL,STRAIGHT);
		newLine->setOrient(NORTH);
		newLine->style() = _style;
		LineNode *newNode = new LineNode(newLine);
		_lines->insert(newNode);
		aTuple = _infoTuples->getFirst();
		while (aTuple != NIL) {
			aTuple->setXY(x,y);
			aTuple = _infoTuples->getNext();
		}
	} 

	ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
	NodeFigure *nodeFigure = aTuple->nodeFigurePtr();
	if (boundOnOneObjectFlag == FALSE &&
		nodeFigure->onBoundaryOrObsolete(_lines)) {
		// remove all lines
		LineNode *tmp = _lines->getFirst();
		while (tmp != NIL) {
			Line *line = tmp->line();
			delete line;
			delete tmp;
			tmp = _lines->getNext();
		}
		_focusNode = NIL;
		_focus = NIL;
		_lines->clear();

		int preferedX = -1;
		int preferedY = -1;
		getPreferedPointOnNodeFigureVertex(preferedX,preferedY,nodeFigure);

		int x,y;
		if (preferedX != -1 && preferedY != -1) {
			x = preferedX;
			y = preferedY;
		} else {
			// 다음 줄을 getFirst()로 고치지 말것 
			// getLast()를 써야 모서리 좌표가 나올 가능성이 큼
			ConnectionInfoTuple *aTuple = _infoTuples->getLast();
			x = aTuple->getX();
			y = aTuple->getY();
		}
		Line *newLine = new Line(_controller,x,y,x,y,NIL,STRAIGHT);
		newLine->setOrient(NORTH);
		newLine->style() = _style;
		LineNode *newNode = new LineNode(newLine);
		_lines->insert(newNode);
		aTuple = _infoTuples->getFirst();
		while (aTuple != NIL) {
			aTuple->setXY(x,y);
			aTuple = _infoTuples->getNext();
		}
	}
	if (boundOnOneObjectFlag == FALSE) {
		tailorEndLinesAll();
	} else if (checkIfThereIsOverlapLine() == FALSE &&
		severalLinesOnNodeFigureBoundary() == FALSE) {
		tailorEndLinesAll();	
	}

	nodeFigure = _nodeFigures->getFirst();
	while (nodeFigure != NIL) {
		_controller->draw(nodeFigure);
		nodeFigure = _nodeFigures->getNext();
	}
	setModelSpecificSymbolAll();

	if (_lines->nOfList() <= 0) return;
	if (boundOnOneObjectFlag == FALSE) {
		boundaryLineCheck();
	} else if (whoAreYou()->equals(IAMASSOCIATION) &&
		_nodeFigures->nOfList() == 3) {
		boundaryLineCheck();
	}
	int nPoints = 0;
	CPoint *endPoints = collectTuplePoints(nPoints);
	remake(endPoints,nPoints);
	delete []endPoints;
	setOrientForObsoleteLines();
	makeRegion(_controller->canvasRgn());
	resetFlags();
	int nOfLines = _lines->nOfList();
	if (nOfLines != nOfVisitedLinesFromANode()) {
		_controller->wrongConnections.insert(this);
		return;
	}
	if (tuplePointsContainedInNodeFigures() == FALSE) {
		_controller->wrongConnections.insert(this);
		return;
	}
	if (tuplePointsConnectedAnyLine() == FALSE) {
		_controller->wrongConnections.insert(this);
		return;
	}
}

BOOL Connection::tuplePointsConnectedAnyLine()
{
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		int x = tuple->getX();
		int y = tuple->getY();
		BOOL connected = FALSE;
		LineNode *aNode = _lines->getFirst();
		while(aNode != NIL) {
			Line *aLine = aNode->line();
			int x1 = aLine->getX1();
			int y1 = aLine->getY1();
			int x2 = aLine->getX2();
			int y2 = aLine->getY2();
			if (x1 == x && y1 == y) connected = TRUE;
			if (x2 == x && y2 == y) connected = TRUE;
			aNode = _lines->getNext();
		}
		if (connected == FALSE) return FALSE;
		tuple = _infoTuples->getNext();
	}
	return TRUE;
}

BOOL Connection::tuplePointsContainedInNodeFigures()
{
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		int x = tuple->getX();
		int y = tuple->getY();
		NodeFigure *node = tuple->nodeFigurePtr();
		if (node->containsOnTupleBound(x,y) == FALSE)
				return FALSE;
		tuple = _infoTuples->getNext();
	}
	return TRUE;
}

int Connection::nOfVisitedLinesFromANode()
{
	// 이 함수는 reachability를 체크하는 거와 같다.
	LineNode *aNode = _lines->getFirst();
	return aNode->nOfVisitedLinesFromANode();
}

void Connection::setOrientForObsoleteLines()
{
	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		Line *aLine = aNode->line();
		if (aLine->isObsolete()) {
			ConnectionInfoTuple *aTuple = 
				_infoTuples->findTupleFor(aLine->getX1(),aLine->getY1());
			if (aTuple != NIL) {
				NodeFigure *aNodeFigure = aTuple->nodeFigurePtr();
				aNodeFigure->setOrientForObsoleteLine(aLine);
			}
		}
		aNode = _lines->getNext();
	}
}

void Connection::setTextPosition(int d1,int d2,int d3)
{
	LineNode *aNode = _lines->getFirst();
	if (aNode == NIL) return;
	int cx,cy;
	Line *aLine = aNode->line();
	aLine->center(cx,cy);
	aLine->setOrient();
	if (aLine->orient() == EAST) {
		int length = aLine->length();
		_text->recalcCoordFromXY1(cx-length/4,cy+d1);
	} else if (aLine->orient() == NORTH) {
		_text->recalcCoordFromXY1(cx+d2,cy+d3);
	} else {
		int length = abs(aLine->getX2() - aLine->getX1());
		_text->recalcCoordFromXY1(cx-length/4,cy+d1);
	}
	_focus = _text;
}

void Connection::bye()
{
	if (_focus == NIL) return;
	if (_focus->whoAreYou()->isIn(WEARETEXTOBJECTS) == FALSE) return;
	((ConnectionText *)_focus)->bye();
}

void Connection::popup(CPoint* event,BOOL)
{
	if (_focus != NIL && 
		_focus->whoAreYou()->isIn(WEARETEXTOBJECTS)) {
		_focus->popup(event);
		return;
	} else if (_focus != NIL && 
		_focus->whoAreYou()->isIn(WEAREEDITABLEOBJECTS)) {
		_focus->popup(event);
		return;
	}
	Figure::popup(event);
}

BOOL Connection::hasRelationshipYet(char *major,char *minor)
{
	NodeFigure *firstNode = _nodeFigures->getFirst();
	if (firstNode == NIL) return FALSE;
	if (firstNode->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		return FALSE;
	}
	ClassTemplate *majorClass = (ClassTemplate *)firstNode;
	char majorClassName[BUFSIZ];
	majorClass->getName(majorClassName,BUFSIZ);

	if (strcmp(majorClassName,major) != 0) return FALSE;

	NodeFigure *childClassNode = _nodeFigures->getNext();
	while (childClassNode != NIL) {
		if (childClassNode->whoAreYou()->equals(IAMCLASSTEMPLATE) == TRUE) {
			ClassTemplate *minorClass = (ClassTemplate *)childClassNode;
			char minorClassName[BUFSIZ];
			minorClass->getName(minorClassName,BUFSIZ);

			if (strcmp(minorClassName,minor) == 0) return TRUE;
		}
		childClassNode = _nodeFigures->getNext();
	}
	return FALSE;
}

