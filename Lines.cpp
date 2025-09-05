#include "stdafx.h"
/* Lines.C */

#include "Lines.h"
// Super Class : Figure

#include "LineNodeList.h" // Aggregation
#include "LineNode.h" // Collaboration
#include "Line.h" // Collaboration
#include "COODView.h" // Collaboration

IMPLEMENT_SERIAL(Lines,Figure,1)

Lines::~Lines()
{
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *aLine = tmp->line();
		delete aLine;
		delete tmp;
		tmp = _lines->getNext();
	}
	delete _lines; _lines = NIL;
	_focusNode = NIL;
	_focus = NIL;
}

Lines::Lines()
: Figure()
{
	_focusNode = NIL;
	_focus = NIL;
	_type = 0;
	_moveAllFlag = TRUE;
	_lastx = -1;
	_lasty = -1;
	_style = SOLID;
	_lines = NIL;
}

Lines::Lines(COODView *controller,Popup* popup,int type,Line *line)
: Figure(controller)
{
	_popup = popup;
	_focusNode = NIL;
	_focus = NIL;
	_type = type;
	_moveAllFlag = TRUE;
	_lastx = -1;
	_lasty = -1;
	_style = SOLID;
	if (controller == NIL) return;
	_lines = new LineNodeList();
	if (line != NIL) {
		insertALine(line,TRUE);
	}
}

void Lines::Serialize(CArchive& ar)
{
	Figure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _type << (LONG) _style;
		ar << (BYTE) _moveAllFlag;
		ar << _lines;
	} else {
		ar >> (LONG&) _type >> (LONG&) _style;
		ar >> (BYTE&) _moveAllFlag;
		ar >> _lines;
	}
}

void Lines::resetHeadType()
{
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		node->line()->head() = HEADNONE;
		node = _lines->getNext();
	}
}

void Lines::getHotXY(int& hotX,int& hotY)
{
	hotX = -1;
	hotY = -1;
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		Line *line = node->line();
		if (line->hotX() != NIL) {
			hotX = line->hotX()->get();
		}
		if (line->hotY() != NIL) {
			hotY = line->hotY()->get();
		}
		node = _lines->getNext();
	}
}

void Lines::redrawForArrow()
{
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		if (node->line()->head() != HEADNONE) {
			_controller->clear(node->line());
			node->line()->setDir(NODIR,HEADNONE);
			_controller->lowlight(node->line());
		}
		node = _lines->getNext();
	}
}

int &Lines::style()
{
	return _style;
}

UnsignedLong *Lines::whoAreYou()
{
	return IAMLINES;
}

void Lines::center(int& x,int& y)
{
	if (_focusNode != NIL) {
		_focusNode->line()->center(x,y);
	} else {
		_lines->top()->line()->center(x,y);
	}
}

void Lines::last(int& x,int& y)
{
	if (_lines->nOfList() == 0) {
		x = _lastx;
		y = _lasty;
		return;
	}
	if (_focusNode != NIL) {
		_focusNode->line()->last(x,y);
	} else {
		_lines->rear()->line()->last(x,y);
	}
}

BOOL Lines::isForkable(int x,int y,int &newX,int &newY)
{
	BOOL value = FALSE;
	newX = -1;
	newY = -1;
	// 이거는 에러 방지를 위해 있어야 함
	_focus = NIL;
	// focusNode 는 delete line segment에서 사용해야 함
//	_focusNode = NIL;
//	if (Figure::onEnter(x,y) == FALSE) return FALSE;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		/* boundary에 있는지 check해야 함 */
		if (line->onEnter(x,y)) {
			value = TRUE;
			_focus = line;
			_focusNode = tmp;
			line->calcForkPoint(x,y,newX,newY);
			break;
		}
		tmp = _lines->getNext();
	}
	return value;
}

LineNode *Lines::insertALine(Line *newline,BOOL focusflag)
{
	LineNode *newnode = new LineNode(newline,_focusNode,NIL);
	_lines->insert(newnode);
	if (focusflag) {
		_focus = newline;
		_focusNode = newnode;
	}
	return newnode;
}

/*
void Lines::drawing(CDC* dcp)
{
	BOOL nocheck;
	if (_controller->currentLines() == NIL) {
		// resizing
		nocheck = TRUE;
	} else {
		// drawing
		nocheck = FALSE;
	}
	((Line *)_focus)->drawing(dcp);
	LineNodeList *afters = _focusNode->afterList();
	LineNode* ptr = afters->getFirst();
	while (ptr != NIL) {
		ptr->line()->drawing(dcp);
		ptr = afters->getNext();
	}
}
*/

void Lines::setXY2(int x,int y)
{
	((Line *)_focus)->setXY2(x,y);
	LineNodeList *afters = _focusNode->afterList();
	LineNode* ptr = afters->getFirst();
	while (ptr != NIL) {
		ptr->line()->setXY2(x,y);
		ptr = afters->getNext();
	}
}

void Lines::drawing(CDC* dcp,int dx,int dy)
{
	if (_focus != NIL) {
		// 만약 _focus 가 NIL 이 아니면 그림 그리는 중임
		_focus->drawing(dcp,dx,dy);
	} else if (_type == ORDINARY) {
		LineNode *tmp = _lines->getFirst();
		while (tmp != NIL) {
			Line *line = tmp->line();
			line->drawing(dcp,dx,dy);
			tmp = _lines->getNext();
		}
	} else {
		// 만약 _focus 가 NIL 이면 resizing 중임
		LineNode *tmp = _lines->getFirst();
		while (tmp != NIL) {
			Line *line = tmp->line();
			if (tmp->mark()) {
				int followPos = line->resizing(dcp,dx,dy);
				if (followPos == ATBEFORE) {
					LineNodeList *befores = tmp->beforeList();
					LineNode* ptr = befores->getFirst();
					while (ptr != NIL) {
						ptr->line()->drawing(dcp,dx,dy);
						ptr = befores->getNext();
					}
				} else if (followPos == ATAFTER) {
					LineNodeList *afters = tmp->afterList();
					LineNode* ptr = afters->getFirst();
					while (ptr != NIL) {
						ptr->line()->drawing(dcp,dx,dy);
						ptr = afters->getNext();
					}
				}
			} else if (tmp->move()) {
				/*     +------+ <- 요런 경우
				 *     |      |
				 *     |      |
				 */
				if (tmp->line()->orient() == NORTH) {
					tmp->line()->move(dcp,0,dy);
				} else { // EAST
					tmp->line()->move(dcp,dx,0);
				}
			}
			tmp = _lines->getNext();
		}
	}
}

void Lines::makeRegion(CRgn *sourceClipRgn)
{
	if (_region != NIL) delete _region;
	_region = createRegion();
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->makeRegion(sourceClipRgn);
		_region->CombineRgn(_region,line->region(),RGN_OR);
		tmp = _lines->getNext();
	}
}

void Lines::resetRegion()
{
	Figure::resetRegion();
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->resetRegion();
		tmp = _lines->getNext();
	}
}

void Lines::releaseRegion()
{
	Figure::releaseRegion();
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->releaseRegion();
		tmp = _lines->getNext();
	}
}

void Lines::clear(CDC* dcp)
{
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->clear(dcp);
		tmp = _lines->getNext();
	}
}

void Lines::setStyle(int style) 
{
	_style = style;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->style() = _style;
		tmp = _lines->getNext();
	}
}

BOOL Lines::containedWithin(int x1,int y1,int x2,int y2)
{
	_moveAllFlag = FALSE;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		if (line->containedWithin(x1,y1,x2,y2) == FALSE)
			return FALSE;
		tmp = _lines->getNext();
	}
	_moveAllFlag = TRUE;
	return TRUE;
}

LineNode *Lines::node(Line *line)
{
	if (line == _focus) return _focusNode;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		if (line == tmp->line())
			return tmp;
		tmp = _lines->getNext();
	}
	return NIL;
}

void Lines::minMaxXY()
{
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->minMaxXY();
		tmp = _lines->getNext();
	}
}

void Lines::setController(COODView *ptr)
{
	Figure::setController(ptr);
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->setController(ptr);
		tmp = _lines->getNext();
	}
}

void Lines::setInCanvas(BOOL flag)
{
	Figure::setInCanvas(flag);
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->setInCanvas(flag);
		tmp = _lines->getNext();
	}
}

BOOL Lines::checkInRegion(CRgn* someregion)
{
	BOOL flag = FALSE;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		flag = line->checkInRegion(someregion);
		if (flag) break;
		tmp = _lines->getNext();
	}
	return flag;
}

void Lines::eraseDots(CDC* dcp)
{
	if (_dotedFlag == FALSE) return;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->eraseDots(dcp);
		tmp = _lines->getNext();
	}
	_dotedFlag = FALSE;
}

int Lines::setHotXY(int x,int y)
{
	if (_focus != NIL) {
		_focus->setHotXY(x,y);
	} else if (_type == ORDINARY) {
		LineNode *tmp = _lines->getFirst();
		while (tmp != NIL) {
			Line *line = tmp->line();
			line->setHotXY(x,y);
			tmp = _lines->getNext();
		}
	} else {
		LineNode *tmp = _lines->getFirst();
		while (tmp != NIL) {
			Line *line = tmp->line();
			if (tmp->mark()) {
				int followPos = line->resizeCoord(x,y);
				int nx = line->notHotX()->get();
				int ny = line->notHotY()->get();
				if (followPos == ATBEFORE) {
					LineNodeList *befores = tmp->beforeList();
					LineNode* ptr = befores->getFirst();
					while (ptr != NIL) {
						ptr->line()->setSuperHotXY(nx,ny);
						ptr = befores->getNext();
					}
				} else {
					LineNodeList *afters = tmp->afterList();
					LineNode* ptr = afters->getFirst();
					while (ptr != NIL) {
						ptr->line()->setSuperHotXY(nx,ny);
						ptr = afters->getNext();
					}
				}
			}
			tmp = _lines->getNext();
		}
	}
	return 0;
}

BOOL Lines::wantToResize(int &x,int &y)
{
	BOOL want = FALSE;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		if (line->wantToResize(x,y)) {
			want = TRUE;
		}
		tmp = _lines->getNext();
	}
	return want;
}

void Lines::drawDots(CDC* dcp)
{
	_dotedFlag = TRUE;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->drawDots(dcp);
		tmp = _lines->getNext();
	}
}

void Lines::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->draw(dcp);
		tmp = _lines->getNext();
	}
}

void Lines::moveCoord(int dx,int dy)
{
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->moveCoord(dx,dy);
		tmp = _lines->getNext();
	}
}

void Lines::moveCoordForScroll(int dx,int dy)
{
	if (_moveAllFlag) {
		moveCoord(dx,dy);
	} else {
		_focus->moveCoord(dx,dy);
		LineNode *tmp = _lines->getFirst();
		while (tmp != NIL) {
			Line *line = tmp->line();
			if (tmp->mark()) {
				int followPos = line->resizeCoordDXY(dx,dy);
				int nx = line->notHotX()->get();
				int ny = line->notHotY()->get();
				if (followPos == ATBEFORE) {
					LineNodeList *befores = tmp->beforeList();
					LineNode* ptr = befores->getFirst();
					while (ptr != NIL) {
						ptr->line()->setSuperHotXY(nx,ny);
						ptr = befores->getNext();
					}
				} else {
					LineNodeList *afters = tmp->afterList();
					LineNode* ptr = afters->getFirst();
					while (ptr != NIL) {
						ptr->line()->setSuperHotXY(nx,ny);
						ptr = afters->getNext();
					}
				}
			}
			tmp = _lines->getNext();
		}
	}
}

void Lines::move(CDC* dcp,int dx,int dy)
{
	if (_moveAllFlag) {
		LineNode *tmp = _lines->getFirst();
		while (tmp != NIL) {
			Line *line = tmp->line();
			line->move(dcp,dx,dy);
			tmp = _lines->getNext();
		}
	} else if (_focus != NIL) {
		_focus->move(dcp,dx,dy);
		LineNode *tmp = _lines->getFirst();
		while (tmp != NIL) {
			Line *line = tmp->line();
			if (tmp->mark()) {
				int followPos = line->resizing(dcp,dx,dy);
				if (followPos == ATBEFORE) {
					LineNodeList *befores = tmp->beforeList();
					LineNode* ptr = befores->getFirst();
					while (ptr != NIL) {
						ptr->line()->drawing(dcp,dx,dy);
						ptr = befores->getNext();
					}
				} else {
					LineNodeList *afters = tmp->afterList();
					LineNode* ptr = afters->getFirst();
					while (ptr != NIL) {
						ptr->line()->drawing(dcp,dx,dy);
						ptr = afters->getNext();
					}
				}
			}
			tmp = _lines->getNext();
		}
	}
}

BOOL Lines::onEnter(int x,int y)
{
	BOOL value = FALSE;
	_focus = NIL;
	_focusNode = NIL;
//	if (Figure::onEnter(x,y) == FALSE) return FALSE;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		if (line->onEnter(x,y)) {
			value = TRUE;
			_focus = line;
			_focusNode = tmp;
			break;
		}
		tmp = _lines->getNext();
	}
	return value;
}

void Lines::insertALine(Line *aline)
{
	LineNode *newnode = new LineNode(aline,NIL,NIL);
	_lines->insert(newnode);
}

Figure *Lines::focus()
{
	return (Figure *)_focus;
}

int Lines::nOfFigures()
{
	return _lines->nOfList();
}

void Lines::getMinMaxXY(int &minX,int &minY,int &maxX,int &maxY)
{
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->getMinMaxXY(minX,minY,maxX,maxY);
		tmp = _lines->getNext();
	}
}


void Lines::doBreak()
{
	localDoBreak();	
}

void Lines::doDetach()
{
	localDoDetach();	
}

void Lines::doAttach()
{
	int popupX = _controller->popupX();
	int popupY = _controller->popupY();
	_focusNode->mark() = FALSE;
	_controller->clear(this);
	localDoAttach(popupX,popupY,(Line *)_focus,_focusNode,TRUE);	
	resetFocus();
	epilog();
	makeRegion(_controller->canvasRgn());
	_controller->lowlight(this);
}

void Lines::localDoBreak()
{
	_controller->clear(_focus);
	int popupX = _controller->popupX();
	int popupY = _controller->popupY();
	int newx,newy;
	BOOL swaped;
	Line *newline = ((Line *)_focus)->calcBreakPoint(popupX,popupY,newx,newy,swaped);
	_controller->lowlight(_focus);
	_controller->lowlight(newline);
	LineNode *newnode = new LineNode(newline,NIL,NIL);
	newnode->afterList()->copy(_focusNode->afterList());
	newnode->beforeList()->insert(_focusNode);
	LineNodeList *alist = _focusNode->afterList();
	LineNode *node = alist->getFirst();
	while(node != NIL) {
		node->afterList()->replacePointer(_focusNode,newnode);
		node->beforeList()->replacePointer(_focusNode,newnode);
		node = alist->getNext();
	}
	alist->clear();
	alist->insert(newnode);
	_lines->insert(newnode);
	// protecting focus change
	Line *savedfocus = (Line *)_focus;
	LineNode *savednode = _focusNode;
	_controller->warpPointer(newx,newy);
	_focus = savedfocus;
	_focusNode = savednode;
	if (_type == STRAIGHT) {
		Line *newline2 = new Line(_controller,newx,newy,newx,newy,NIL,_type);	
		newline2->style() = _style;
		newline2->setOrient(Line::invertOrient(((Line *)_focus)->orient()));
		LineNode *newnode2 = new LineNode(newline2,NIL,NIL);
		newnode2->afterList()->insert(newnode);
		newnode2->beforeList()->insert(_focusNode);	
		_focusNode->afterList()->clear();
		_focusNode->afterList()->insert(newnode2);
		newnode->beforeList()->clear();
		newnode->beforeList()->insert(newnode2);
		_lines->insert(newnode2);
		if (swaped) {
			swaped = newline->checkNear(newx,newy);
			if (swaped) {
				newnode->swapBeforeAfter();
			}
			_focusNode = newnode;
			_focus = newline;
		} else {
			newnode2->swapBeforeAfter();
			swaped = newline->checkNear(newx,newy);
			if (swaped) {
				newnode->swapBeforeAfter();
			}
		}
//		_focusNode->makeCascadeFollow(_controller,_lines,_type);
	} else {
		BOOL swaped = newline->checkNear(newx,newy);
		if (swaped) {
			newnode->swapBeforeAfter();
		}
	}
	_controller->startResize();
}

BOOL Lines::cutLineAt(int x,int y,Line *focus,LineNode *focusNode)
{
	LineNodeList *copiedLines = new LineNodeList();
	copiedLines->copy(_lines);
	LineNode *aNode = copiedLines->getFirst();
	while(aNode != NIL) {
		Line *aLine = aNode->line();
		if (focus == aLine) {
			aNode = copiedLines->getNext();
			continue;
		}
		int x1 = aLine->getX1();
		int y1 = aLine->getY1();
		int x2 = aLine->getX2();
		int y2 = aLine->getY2();
		if (x == x1 && y == y1) {
			aNode = copiedLines->getNext();
			continue;
		}
		if (x == x2 && y == y2) {
			aNode = copiedLines->getNext();
			continue;
		}
		if (aLine->incl(x,y)) {
			Line *newLine = (Line *)aLine->born();
			aLine->setXY2(x,y);
			newLine->setXY1(x,y);
			LineNode *newNode = new LineNode(newLine);
			_lines->insert(newNode);
			delete copiedLines;
			return TRUE;
		}
		aNode = copiedLines->getNext();
	}
	delete copiedLines;
	return FALSE;
}

BOOL Lines::localDoAttach(int popupX,int popupY,Line *focus,LineNode *focusNode,BOOL originalAttach)
{
	if (focusNode->mark()) return FALSE;
	if (focus->isObsolete()) {
		focusNode->mark() = TRUE;
		return FALSE;
	}
	BOOL swaped = focus->checkNear(popupX,popupY);
	if (swaped) {
		focusNode->swapBeforeAfter();
	}
	int newx,newy;
	focus->last(newx,newy);
	LineNode *foundNode = NIL;
	if (originalAttach) {
		LineNode *node = _lines->getFirst();
		while (node != NIL) {
			if (_type == ORDINARY) {
				if (node != focusNode &&
					node->line()->isObsolete() == FALSE &&
		    		focusNode->afterList()->inList(node) == FALSE &&
		    		node->line()->onEnter(newx,newy)) {
					foundNode = node;
					break;
				}
			} else /* STRAIGHT */ {
				if (node != focusNode &&
					node->line()->isObsolete() == FALSE &&
		    		focusNode->afterList()->inList(node) == FALSE &&
		    		node->line()->incl(newx,newy)) {
					foundNode = node;
					break;
				}
			}
			node = _lines->getNext();
		}
	} else {
		int oldx = newx; int oldy = newy;
		LineNode *node = _lines->getFirst();
		while (node != NIL) {
			if (node != focusNode &&
				node->line()->isObsolete() == FALSE &&
		    	focusNode->afterList()->inList(node) == FALSE &&
				node->line()->incl(focus,newx,newy)) {
				foundNode = node;
				break;
			}
			node = _lines->getNext();
		}
		if (oldx != newx || oldy != newy) {
			LineNode *node = focusNode->afterList()->getFirst();
			while(node != NIL) {
				node->line()->adjustXYValue(oldx,oldy,newx,newy);
				node = focusNode->afterList()->getNext();
			}
		}
	}
	if (foundNode == NIL) {
		return FALSE;
	}
	swaped = FALSE;
	int x = newx;
	int y = newy;
	Line *newline = foundNode->line()->calcForkPoint(x,y,newx,newy,swaped);
	if (newline != NIL) {
		LineNode *newnode = new LineNode(newline,NIL,NIL);
		newnode->afterList()->copy(foundNode->afterList());
		newnode->beforeList()->insert(foundNode);
		LineNodeList *alist = foundNode->afterList();
		LineNode *node = alist->getFirst();
		while(node != NIL) {
			node->afterList()->replacePointer(foundNode,newnode);
			node->beforeList()->replacePointer(foundNode,newnode);
			node = alist->getNext();
		}
		alist->clear();
		alist->insert(newnode);
		_lines->insert(newnode);
		LineNode *ptr = focusNode->afterList()->getFirst();
		while (ptr != NIL) {
			if (ptr->beforeList()->inList(focusNode)) {
				ptr->beforeList()->insert(foundNode);
				ptr->beforeList()->insert(newnode);
				if (originalAttach) {
					ptr->line()->setXY1(newx,newy);
				}
			} else if (ptr->afterList()->inList(focusNode)) {
				ptr->afterList()->insert(foundNode);
				ptr->afterList()->insert(newnode);
				if (originalAttach) {
					ptr->line()->setXY2(newx,newy);
				}
			}
			foundNode->afterList()->insert(ptr);
			newnode->beforeList()->insert(ptr);
			ptr = focusNode->afterList()->getNext();
		}
		foundNode->afterList()->insert(focusNode);
		newnode->beforeList()->insert(focusNode);
		focusNode->afterList()->insert(foundNode);
		focusNode->afterList()->insert(newnode);
		if (originalAttach) {
			focus->setXY2(newx,newy);
		}
	} else {
		if (swaped) {
			foundNode->swapBeforeAfter();
		}
		LineNode *ptr = foundNode->afterList()->getFirst();
		while (ptr != NIL) {
			if (ptr->beforeList()->inList(foundNode)) {
				ptr->beforeList()->insert(focusNode);
				LineNode *tmp = focusNode->afterList()->getFirst();
				while(tmp != NIL) {
					ptr->beforeList()->insert(tmp);
					tmp = focusNode->afterList()->getNext();
				}
			} else if (ptr->afterList()->inList(foundNode)) {
				ptr->afterList()->insert(focusNode);
				LineNode *tmp = focusNode->afterList()->getFirst();
				while(tmp != NIL) {
					ptr->afterList()->insert(tmp);
					tmp = focusNode->afterList()->getNext();
				}
			}
			focusNode->afterList()->insert(ptr);
			ptr = foundNode->afterList()->getNext();
		}
		ptr = focusNode->afterList()->getFirst();
		while (ptr != NIL) {
			if (ptr->beforeList()->inList(focusNode)) {
				ptr->beforeList()->insert(foundNode);
				if (originalAttach) {
					ptr->line()->setXY1(newx,newy);
				}
				LineNode *tmp = foundNode->afterList()->getFirst();
				while(tmp != NIL) {
					ptr->beforeList()->insert(tmp);
					tmp = foundNode->afterList()->getNext();
				}
			} else if (ptr->afterList()->inList(focusNode)) {
				ptr->afterList()->insert(foundNode);
				if (originalAttach) {
					ptr->line()->setXY2(newx,newy);
				}
				LineNode *tmp = foundNode->afterList()->getFirst();
				while(tmp != NIL) {
					ptr->afterList()->insert(tmp);
					tmp = foundNode->afterList()->getNext();
				}
			}
			foundNode->afterList()->insert(ptr);
			ptr = focusNode->afterList()->getNext();
		}
		focusNode->afterList()->insert(foundNode);
		foundNode->afterList()->insert(focusNode);
		if (originalAttach) {
			focus->setXY2(newx,newy);
		}
	}
	if (newline != NIL) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void Lines::localDoDetach()
{
	_controller->clear(_focus);
	int popupX = _controller->popupX();
	int popupY = _controller->popupY();
	BOOL swaped = ((Line *)_focus)->checkNear(popupX,popupY);
	if (swaped) {
		_focusNode->swapBeforeAfter();
	}
	LineNode *ptr = _focusNode->afterList()->getFirst();
	while (ptr != NIL) {
		ptr->beforeList()->remove(_focusNode);
		ptr->afterList()->remove(_focusNode);
		ptr = _focusNode->afterList()->getNext();
	}
	_focusNode->afterList()->clear();
	int newx,newy;
	((Line *)_focus)->last(newx,newy);
	// protecting focus change
	Line *savedfocus = (Line *)_focus;
	LineNode *savednode = _focusNode;
	_controller->warpPointer(newx,newy);
	_focus = savedfocus;
	_focusNode = savednode;
	if (_type == STRAIGHT) {
//		_focusNode->makeCascadeFollow(_controller,_lines,_type);
	}
	_controller->startResize();
}

void Lines::makeArrow(int dir_type)
{
	_controller->lowlight(this);
	Line *focus = (Line *)_focus;
	_controller->clear(focus);
	if (dir_type == ONEDIRECTION) {
		int x = _controller->popupX();
		int y = _controller->popupY();
		focus->toggleHead(TRUE,x,y);
	} else  { // BIDIRECTION 
		focus->toggleHead(FALSE);
	}
	_controller->lowlight(focus);
	_controller->resetCurrentFocus();
}

void Lines::deleteOneLine()
{
	if (nOfFigures() == 1) {
		_controller->deleteCurrentFigure();
		return;
	}
	if (_focus == NIL || _focusNode == NIL) {
		return;
	}
	_controller->lowlight(this);
	removeLineNode(_focusNode);
	resetFocus();
	epilog();
	makeRegion(_controller->canvasRgn());
	_controller->lowlight(this);
	_controller->resetCurrentFocus();
}

void Lines::removeLineNode(LineNode *focusNode)
{
	if (_controller != NIL) _controller->clear(focusNode->line());
	_lines->remove(focusNode,TRUE);
	Line *focusLine = focusNode->line();
	delete focusLine;
	delete focusNode;
}

void Lines::setFocus(int x,int y)
{
	_focus = NIL;
	_focusNode = NIL;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		if (line->doesMeet(x,y)) {
			_focus = line;
			_focusNode = tmp;
			return;
		}
		tmp = _lines->getNext();
	}
}

BOOL Lines::checkIfThereIsOverlapLine()
{
	if (_lines->nOfList() <= 1) return FALSE;
	LineNodeList *copiedList = new LineNodeList();
	copiedList->copy(_lines);
	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		Line *aLine = aNode->line();
		int x1 = aLine->getX1();
		int y1 = aLine->getY1();
		int x2 = aLine->getX2();
		int y2 = aLine->getY2();
		if (aNode->beforeList()->nOfList() == 0 ||
			aNode->afterList()->nOfList() == 0) {
			LineNode *bNode = copiedList->getFirst();
			while(bNode != NIL) {
				Line *bLine = bNode->line();
				if (aLine != bLine &&
					aLine->orient() == bLine->orient()) {
					if (bLine->incl(x1,y1) ||
						bLine->incl(x2,y2)) {
						copiedList->clear();
						delete copiedList;
						return TRUE;
					}
				}
				bNode = copiedList->getNext();
			}
		}
		aNode = _lines->getNext();
	}
	copiedList->clear();
	delete copiedList;
	return FALSE;
}

LineNode *Lines::findNodeFor(int x,int y)
{
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		int x1,y1,x2,y2;
		line->coords(x1,y1,x2,y2);
		if (x1 == x && y1 == y) {
			line->swapPoints();
			tmp->swapBeforeAfter();
			return tmp;
		}
		if (x2 == x && y2 == y) {
			return tmp;
		}
		tmp = _lines->getNext();
	}
	return NIL;
}

LineNode *Lines::findABoundaryLineNode(int &where)
{
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		if (tmp->beforeList()->isEmpty() == TRUE) {
			where = ATAFTER;
			return tmp;
		}
		if (tmp->afterList()->isEmpty() == TRUE) {
			where = ATBEFORE;
			return tmp;
		}
		tmp = _lines->getNext();
	}
	return NIL;
}

LineNode *Lines::findNextLineNode(LineNode *from,int &where)
{
	int sx = 0; int sy = 0;
	Line *fromLine = from->line();
	if (where == ATBEFORE) {
		sx = fromLine->getX1();
		sy = fromLine->getY1();
	} else {
		sx = fromLine->getX2();
		sy = fromLine->getY2();
	}
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *tmpLine = tmp->line();
		if (tmp != from && tmpLine->whereToMeet(sx,sy) == ATBEFORE) {
			where = ATAFTER;
			return tmp;
		} else if (tmp != from && tmpLine->whereToMeet(sx,sy) == ATAFTER) {
			where = ATBEFORE;
			return tmp;
		}
		tmp = _lines->getNext();
	}
	return NIL;
}

void Lines::retrySetFocus(int &x,int &y)
{
	if (_focus != NIL) return;
	int min_dist = 10000;
	int x1,y1,x2,y2;
	_focus = NIL;
	_focusNode = NIL;
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		line->coords(x1,y1,x2,y2);
		int d1 = distance(x,y,x1,y1);
		int d2 = distance(x,y,x2,y2);
		if (d1 < min_dist) {
			_focus = line;
			_focusNode = tmp;
			min_dist = d1;
		}
		if (d2 < min_dist) {
			_focus = line;
			_focusNode = tmp;
			min_dist = d2;
		}
		tmp = _lines->getNext();
	}
	if (_focus == NIL) return;
	((Line *)_focus)->coords(x1,y1,x2,y2);
	int d1 = distance(x,y,x1,y1);
	int d2 = distance(x,y,x2,y2);
	if (d1 < d2) {
		x = x1; y = y1;
	} else {
		x = x2; y = y2;
	}
}

BOOL Lines::checkNear(int x,int y)
{
	if (_focus == NIL || _focusNode == NIL) {
		return FALSE;
	}
	BOOL swaped = ((Line *)_focus)->checkNear(x,y);
	if (swaped) {
		_focusNode->swapBeforeAfter();
	}
	int endx,endy;
	((Line *)_focus)->last(endx,endy);
	LineNodeList *afters = _focusNode->afterList();
	LineNode* ptr = afters->getFirst();
	while (ptr != NIL) {
		BOOL local_swaped = ptr->line()->checkNear(endx,endy);
		if (local_swaped) {
			ptr->swapBeforeAfter();
		}
		ptr = afters->getNext();
	}
	return swaped;
}

BOOL Lines::isLinearConnection(BOOL abortionFlag)
{
	return FALSE;
}

void Lines::epilogForLinearAndSelfConnection()
{
	int n = _lines->nOfList();
	if (n <= 3) return;
	
	if (n == 4) {
		int obsoleteCount = 0;
		LineNode *aNode = _lines->getFirst();
		while(aNode != NIL) {
			if (aNode->line()->isObsolete()) obsoleteCount++;
			aNode = _lines->getNext();
		}
		if (obsoleteCount >= 2) return;
	}


	int loopCount = 0;
	BOOL satisfied = FALSE;
	while (!satisfied) {
		if (loopCount > 10) {
			return;
		}
		loopCount++;
		satisfied = TRUE;
		resetMark();
		LineNode *node = _lines->getFirst();
		while(node != NIL) {
			BOOL obsolete;
			obsolete = node->checkIfObsolete();
			if (obsolete) {
				delete node;
				_lines->remove(node,TRUE);
				node = _lines->getFirst();
				satisfied = FALSE;
			} else {
				node = _lines->getNext();
			}
			if (_lines->nOfList() <= 3) return;
		}
		resetMark();
		node = _lines->getFirst();
		while(node != NIL) {
			BOOL changed;
			changed = node->checkToMerge(_controller,_lines,FALSE);
			if (changed) {
				satisfied = FALSE;
				node = _lines->getFirst();
			} else {
				node = _lines->getNext();
			}
			if (_lines->nOfList() <= 3) return;
		}
		resetFlags(); 
	}
}

void Lines::epilogForLinearConnection()
{
	// 일단 점은 없애고 
	int loopCount = 0;
	BOOL satisfied = FALSE;
	while (!satisfied) {
		if (loopCount > 10) {
			return;
		}
		loopCount++;
		satisfied = TRUE;
		resetMark();
		LineNode *node = _lines->getFirst();
		while(node != NIL) {
			BOOL obsolete;
			obsolete = node->checkIfObsolete();
			if (obsolete) {
				delete node;
				_lines->remove(node,TRUE);
				node = _lines->getFirst();
				satisfied = FALSE;
			} else {
				node = _lines->getNext();
			}
			if (_lines->nOfList() == 1) return;
		}
		resetMark();
		node = _lines->getFirst();
		while(node != NIL) {
			BOOL changed;
			changed = node->checkToMerge(_controller,_lines,FALSE);
			if (changed) {
				satisfied = FALSE;
				node = _lines->getFirst();
			} else {
				node = _lines->getNext();
			}
			if (_lines->nOfList() == 1) return;
		}
		resetFlags(); 
	}
}

CPoint *Lines::collectTuplePoints(int &nPoints)
{
	nPoints = 0;
	return NIL;
}

CPoint *Lines::collectEndPoints(int &nPoints)
{
	int n = 0;
	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		if (aNode->beforeList()->isEmpty()) {
			n++;
		}
		if (aNode->afterList()->isEmpty()) {
			n++;
		}
		aNode = _lines->getNext();
	}
	nPoints = n;
	if (nPoints == 0) return NIL;
	CPoint *points = new CPoint[nPoints];
	n = 0;
	aNode = _lines->getFirst();
	while(aNode != NIL) {
		Line * aLine = aNode->line();
		if (aNode->beforeList()->isEmpty()) {
			points[n].x = aLine->getX1();
			points[n].y = aLine->getY1();
			n++;
		}
		if (aNode->afterList()->isEmpty()) {
			points[n].x = aLine->getX2();
			points[n].y = aLine->getY2();
			n++;
		}
		aNode = _lines->getNext();
	}
	return points;
}

LineNode *Lines::removeCycle()
{
	LineNode *startNode = _lines->getFirst();
	LineNode *nodeToRemove = startNode->removeCycle();
	return nodeToRemove;
}

void Lines::epilogForMovingAndResizing()
{
	/* 이 밑의 함수 내용은 지저분하게 반복되기도 하지만 
	그냥두는게 신상에 좋을 것 같다. */
	int nPoints = 0;
	CPoint *endPoints = collectEndPoints(nPoints);
	
	int loopCount = 0;
	BOOL doThisOneMore = FALSE;
	BOOL satisfied = FALSE;
	while(!satisfied || doThisOneMore) {
		if (loopCount > 10) {
			remake();
			if (endPoints) delete []endPoints;
			return;
		}
		loopCount++;
		satisfied = TRUE;
		resetMark(); 
		LineNode *aNode = _lines->getFirst();
		while(aNode != NIL) {
			// 없애면 안되는 obsolete point들을 마킹한다. 
			Line *aLine = aNode->line();
			BOOL obsolete = aLine->isObsolete();
			if (obsolete) {
				int x = aLine->getX1();
				int y = aLine->getY1();
				for(int i = 0; i < nPoints; i++) {
					if (endPoints[i].x == x &&
						endPoints[i].y == y &&
						aNode->nOfNeigborNodes() > 1) {
						aNode->mark() = TRUE;
						break;
					}
				}
			}
			aNode = _lines->getNext();
		}
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			BOOL obsolete;
			obsolete = aNode->checkIfObsolete();
			if (obsolete) {
				satisfied = FALSE;
				delete aNode;
				_lines->remove(aNode,TRUE);
				aNode = _lines->getFirst();
			} else {
				aNode = _lines->getNext();
			}
			if (_lines->nOfList() == 1) {
				if (endPoints) delete []endPoints;
				return;
			}
		}
		// first merge before attach
		resetMark();
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			// 머지하면 안되는 라인 노드들을 마킹한다. 
			Line *aLine = aNode->line();
			int x = aLine->getX1();
			int y = aLine->getY1();
			int i;
			for(i = 0; i < nPoints; i++) {
				if (endPoints[i].x == x &&
					endPoints[i].y == y &&
					aNode->nOfNeigborNodes() > 1) {
					aNode->mark() = TRUE;
					break;
				}
			}
			x = aLine->getX2();
			y = aLine->getY2();
			for(i = 0; i < nPoints; i++) {
				if (endPoints[i].x == x &&
					endPoints[i].y == y &&
					aNode->nOfNeigborNodes() > 1) {
					aNode->mark() = TRUE;
					break;
				}
			}
			aNode = _lines->getNext();
		}
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			BOOL changed;
			changed = aNode->checkToMerge(_controller,_lines,FALSE);
			if (changed) {
				satisfied = FALSE;
				aNode = _lines->getFirst();
			} else {
				aNode = _lines->getNext();
			}
			if (_lines->nOfList() == 1) {
				if (endPoints) delete []endPoints;
				return;
			}
		}
		resetMark();
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			// 없애면 안되는 obsolete point들을 마킹한다. 
			Line *aLine = aNode->line();
			BOOL obsolete = aLine->isObsolete();
			if (obsolete) {
				int x = aLine->getX1();
				int y = aLine->getY1();
				for(int i = 0; i < nPoints; i++) {
					if (endPoints[i].x == x &&
						endPoints[i].y == y &&
						aNode->nOfNeigborNodes() > 1) {
						aNode->mark() = TRUE;
						break;
					}
				}
			}
			aNode = _lines->getNext();
		}
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			// 머지하고나면 한바퀴돌고 난 obsolete point 가 생길 수도 있다. 
			BOOL obsolete;
			obsolete = aNode->checkIfObsolete();
			if (obsolete) {
				satisfied = FALSE;
				delete aNode;
				_lines->remove(aNode,TRUE);
				aNode = _lines->getFirst();
			} else {
				aNode = _lines->getNext();
			}
			if (_lines->nOfList() == 1) {
				if (endPoints) delete []endPoints;
				return;
			}
		}
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			// Ordinary Line 경우를 대비해서, 그러나 효과가 있을지는 의문이다.
			aNode->line()->slope();
			aNode = _lines->getNext();
		}
		BOOL everChanged = FALSE;
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			Line *line = aNode->line();
			BOOL changed = FALSE;
			if (line->isObsolete() == FALSE) {
				int x1,y1,x2,y2;
				line->coords(x1,y1,x2,y2);
				changed = cutLineAt(x1,y1,line,aNode);
				if (changed) {
					everChanged = TRUE;
					satisfied = FALSE;
					// cutLineAt() 함수가 불완전하기 때문에 remake() 호출함.
					remake();
					aNode = _lines->getFirst();
				} else {
					changed = cutLineAt(x2,y2,line,aNode);
					if (changed) {
						everChanged = TRUE;
						satisfied = FALSE;
						// cutLineAt() 함수가 불완전하기 때문에 remake() 호출함.
						remake();
						aNode = _lines->getFirst();
					} else {
						aNode = _lines->getNext();
					}
				}
			} else {
				int x1,y1,x2,y2;
				line->coords(x1,y1,x2,y2);
				changed = cutLineAt(x1,y1,line,aNode);
				if (changed) {
					everChanged = TRUE;
					satisfied = FALSE;
					// cutLineAt() 함수가 불완전하기 때문에 remake() 호출함.
					remake();
				}
				aNode = _lines->getNext();
			}
		}
		if (satisfied == FALSE &&
			everChanged == TRUE) 
			remake();
		LineNodeList *copied = new LineNodeList();
		copied->copy(_lines);
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			LineNode *tmp = copied->getFirst();
			BOOL same = FALSE;
			while(tmp != NIL) {
				if ((aNode != tmp) && 
					(aNode->line()->checkIfSame(tmp->line()))) {
					Line *tmpline = tmp->line();
					delete tmpline;
					delete tmp;
					_lines->remove(tmp,TRUE);
					same = TRUE;
					break;
				}
				tmp = copied->getNext();
			}
			if (same) {
				satisfied = FALSE;
				copied->clear();
				copied->copy(_lines);
				aNode = _lines->getFirst();
			} else {
				aNode = _lines->getNext();
			}
			if (_lines->nOfList() == 1) {
				if (endPoints) delete []endPoints;
				delete copied;
				return;
			}
		}
		delete copied;
		// second merge after attach
		resetMark();
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			// 머지하면 안되는 라인 노드들을 마킹한다. 
			Line *aLine = aNode->line();
			int x = aLine->getX1();
			int y = aLine->getY1();
			int i;
			for(i = 0; i < nPoints; i++) {
				if (endPoints[i].x == x &&
					endPoints[i].y == y &&
					aNode->nOfNeigborNodes() > 1) {
					aNode->mark() = TRUE;
					break;
				}
			}
			x = aLine->getX2();
			y = aLine->getY2();
			for(i = 0; i < nPoints; i++) {
				if (endPoints[i].x == x &&
					endPoints[i].y == y &&
					aNode->nOfNeigborNodes() > 1) {
					aNode->mark() = TRUE;
					break;
				}
			}
			aNode = _lines->getNext();
		}
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			BOOL changed;
			changed = aNode->checkToMerge(_controller,_lines,FALSE);
			if (changed) {
				satisfied = FALSE;
				aNode = _lines->getFirst();
			} else {
				aNode = _lines->getNext();
			}
			if (_lines->nOfList() == 1) {
				if (endPoints) delete []endPoints;
				return;
			}
		}
		resetMark();
		LineNode *nodeToRemove = removeCycle();
		if (nodeToRemove != NIL) {
			satisfied = FALSE;
			delete nodeToRemove;
			_lines->remove(nodeToRemove,TRUE);
		}
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			BOOL deleteFlag = FALSE;
			if (aNode->beforeList()->isEmpty()) {
				deleteFlag = TRUE;
				int x = aNode->line()->getX1();
				int y = aNode->line()->getY1();
				for(int i = 0; i < nPoints; i++) {
					if (x == endPoints[i].x &&
						y == endPoints[i].y) {
						deleteFlag = FALSE;
						break;
					}
				}
			} else if (aNode->afterList()->isEmpty()) {
				deleteFlag = TRUE;
				int x = aNode->line()->getX2();
				int y = aNode->line()->getY2();
				for(int i = 0; i < nPoints; i++) {
					if (x == endPoints[i].x &&
						y == endPoints[i].y) {
						deleteFlag = FALSE;
						break;
					}
				}
			}
			if (deleteFlag == TRUE) {
				satisfied = FALSE;
				delete aNode->line();
				delete aNode;
				_lines->remove(aNode,TRUE);
				aNode = _lines->getFirst();
			} else {
				aNode = _lines->getNext();
			}
		}
		remake();
		if (satisfied == TRUE && doThisOneMore == TRUE) {
			// exit loop
			satisfied = TRUE;
			doThisOneMore = FALSE;
		} else if (satisfied == TRUE && doThisOneMore == FALSE) {
			doThisOneMore = TRUE;
		} else if (satisfied == FALSE && doThisOneMore == TRUE) {
			// exit loop
			satisfied = TRUE;
			doThisOneMore = FALSE;
		}
	}
	if (endPoints) delete []endPoints;
	nPoints = 0;
	endPoints = collectTuplePoints(nPoints);
	if (endPoints != NIL) {
		remake(endPoints,nPoints);
	} else {
		remake();
	}
	if (endPoints) delete []endPoints;
}

void Lines::epilog(BOOL abortionFlag)
{
	if (_moveAllFlag) return;
	if (_focus == NIL || _focusNode == NIL) {
		if (_lines->nOfList() == 1) return;
		if (isLinearConnection(abortionFlag) == FALSE) {
			epilogForMovingAndResizing();
		} else {
			epilogForLinearConnection();
			remake();
		}
		return;
	}
	/* 아마 이 아래 부분은 그냥 Lines를 그리는 중에 수행되는 부분인데
		이 도구에서는 수행될 일이 없을 껄 ...
		Unix 버전 OODesigner에서나 이용되었던 걸꺼야. */
	int orient = ((Line *)_focus)->setOrient();
	_controller->currentOrient = orient;
	int x,y;
	((Line *)_focus)->last(x,y);
	// protecting focus change
	Line *savedfocus = (Line *)_focus;
	LineNode *savednode = _focusNode;
	_focus = savedfocus;
	_focusNode = savednode;
	if (((Line *)_focus)->isObsolete()) {
		((Line *)_focus)->last(_lastx,_lasty);
		LineNode *next_focusNode;
		if (_lines->nOfList() > 1) {
			next_focusNode = _focusNode->beforeList()->getFirst();
			if (next_focusNode == NIL) {
				next_focusNode = _focusNode->afterList()->getFirst();
				if (next_focusNode == NIL) {
					return;
				}
			}	
			BOOL swaped = next_focusNode->line()->checkNear(_lastx,_lasty);
			if (swaped) {
				next_focusNode->swapBeforeAfter();
			}
			_focusNode->mark() = FALSE;
			_focusNode->checkIfObsolete();
			delete _focusNode;
			_lines->remove(_focusNode,TRUE);
			_focusNode = next_focusNode;
			_focus = next_focusNode->line();
		} else {
			if (_controller->currentConnection() != NIL) {
				removeLineNode(_focusNode);
				resetFocus();
				return;
			}
		}
	} else {
		_focusNode->mark() = FALSE;
		BOOL obsolete = _focusNode->checkIfObsolete();
		if (obsolete) {
			delete _focusNode;
			_lines->remove(_focusNode,TRUE);
		} else {
			_focusNode->checkToMerge(_controller,_lines);
		}
	}
}

void Lines::calcForkPoint(int popupX,int popupY,int &newx,int &newy)
{
	if (_focus == NIL || _focusNode == NIL) {
		return;
	}
	BOOL swaped = FALSE;
	Line *newline = ((Line *)_focus)->calcForkPoint(popupX,popupY,newx,newy,swaped);
	if (newline != NIL) {
		_controller->currentOrient = newline->orient();
		LineNode *newnode = new LineNode(newline,NIL,NIL);
		newnode->afterList()->copy(_focusNode->afterList());
		newnode->beforeList()->insert(_focusNode);
		LineNodeList *alist = _focusNode->afterList();
		LineNode *node = alist->getFirst();
		while(node != NIL) {
			node->afterList()->replacePointer(_focusNode,newnode);
			node->beforeList()->replacePointer(_focusNode,newnode);
			node = alist->getNext();
		}
		alist->clear();
		alist->insert(newnode);
		_lines->insert(newnode);
	} else {
		_controller->currentOrient = UNDEFINED;
		if (swaped)
			_focusNode->swapBeforeAfter();
	}
	resetFlags();
}

void Lines::resetFocus()
{
	_focus = NIL;
	_focusNode = NIL;
}

void Lines::resetHotXY()
{
	_moveAllFlag = FALSE;
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		node->line()->resetHotXY();
		node = _lines->getNext();
	}
}

void Lines::resetMark()
{
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		node->mark() = FALSE;
		node = _lines->getNext();
	}
}

void Lines::resetFlags()
{
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		node->resetFlags();
		node->line()->setAbsoluteFollowPos(ATNOWHERE);
		node = _lines->getNext();
	}
}

BOOL Lines::moveProlog(BOOL moveAllFlag)
{
	_moveAllFlag = moveAllFlag;
	if (moveAllFlag) {
		return TRUE;
	}
	if (_focus == NIL || _focusNode == NIL) {
		_moveAllFlag = TRUE;
		return TRUE;
	}
	resetFlags();
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		node->line()->resetHotXY();
		node = _lines->getNext();		
	}
	int x1 = ((Line *)_focus)->getX1();
	int y1 = ((Line *)_focus)->getY1();
	int x2 = ((Line *)_focus)->getX2();
	int y2 = ((Line *)_focus)->getY2();
	node = _lines->getFirst();
	while(node != NIL) {
		// focus line 에 바로 따라오는 resizable 라인 찾기 
		Line *line = node->line();
		if (line != _focus) {
			if (line->setFollowing(x1,y1)) {
				node->mark() = TRUE;
			} else {
				if (line->setFollowing(x2,y2)) {
					node->mark() = TRUE;
				}
			}
		}
		node = _lines->getNext();		
	}
	LineNodeList *allNewLineNodes = new LineNodeList();
	LineNodeList *newLineNodes = new LineNodeList();
	node = _lines->getFirst();
	while(node != NIL) {
		// cascade follow line 찾기
		Line *line = node->line();
		if (node->mark() && line != _focus) {
			node->setFollowLines(newLineNodes);
			LineNode *newNode = newLineNodes->getFirst();
			while (newNode != NIL) {
				allNewLineNodes->insert(newNode);
				newNode = newLineNodes->getNext();
			}
			newLineNodes->clear();
		}
		node = _lines->getNext();		
	}
	LineNode *newNode = allNewLineNodes->getFirst();
	while (newNode != NIL) {
		_lines->insert(newNode);
		newNode = allNewLineNodes->getNext();
	}
    delete allNewLineNodes;
	delete newLineNodes;
	return FALSE;
}

void Lines::bornFocus()
{
	resetFlags();
	Line *newline = (Line *)((Line *)_focus)->born();
	LineNode *newnode = new LineNode(newline,NIL,NIL);
	_lines->insert(newnode);
	_focus = newline;
	_focusNode = newnode;
	_moveAllFlag = FALSE;
	int x,y;
	((Line *)_focus)->center(x,y);
	Line *savedfocus = (Line *)_focus;
	LineNode *savednode = _focusNode;
	/*
	_controller->checkToGo(x,y,_controller->popupX(),_controller->popupY());
	_controller->warpPointer(x,y);
	*/
	_focus = savedfocus;
	_focusNode = savednode;
}

Figure* Lines::born(Figure* ptr)
{
	Lines *copied;
	if (ptr == NIL) {
		copied = new Lines(NIL,NIL,0,NIL);
	} else {
		copied = (Lines *)ptr;
	}
	copied->_focusNode = NIL;
	copied->_focus = NIL;
	copied->_type = _type;
	copied->_lastx = -1;
	copied->_lasty = -1;
	copied->_style = _style;
	copied->_moveAllFlag = TRUE;
	copied->_lines = new LineNodeList();
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		Line *copied_line = (Line *)node->line()->born();
		LineNode * copied_node = new LineNode(copied_line,NIL,NIL);	
		copied->_lines->insert(copied_node);
		if (_focusNode == node) {
			copied->_focusNode = copied_node;
			copied->_focus = copied_line;
		}
		node = _lines->getNext();		
	}
	copied->remake();
	return (Figure::born((Figure *)copied));
}

void Lines::resizeProlog(NodeFigure* aNode)
{
	resetFlags();
	if (_type == ORDINARY) return;
	LineNode *node = _lines->getFirst();
	while(node != NIL) {
		Line *line = node->line();
		if (line->hotX() != NIL && line->hotY() != NIL) {
			node->mark() = TRUE;
		}
		node = _lines->getNext();		
	}
	LineNodeList *newLineNodes = new LineNodeList(); 
	LineNodeList *allNewLineNodes = new LineNodeList(); 
	node = _lines->getFirst();
	while(node != NIL) {
		Line *line = node->line();
		if (node->mark()) {
			node->setFollowLines(newLineNodes);
			LineNode *newNode = newLineNodes->getFirst();
			while (newNode != NIL) {
				allNewLineNodes->insert(newNode);
				newNode = newLineNodes->getNext();
			}
			newLineNodes->clear();
		}
		node = _lines->getNext();		
	}
	LineNode *newNode = allNewLineNodes->getFirst();
	while (newNode != NIL) {
		_lines->insert(newNode);
		newNode = allNewLineNodes->getNext();
	}
    delete allNewLineNodes;
	delete newLineNodes;
}

void Lines::remake(CPoint endPoints[],int nPoints)
{
	LineNodeList *copied = new LineNodeList();
	copied->copy(_lines);
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		int x1,y1,x2,y2;
		tmp->line()->coords(x1,y1,x2,y2);
		int i;
		for(i = 0; i < nPoints; i++) {
			if (x1 == endPoints[i].x && 
				y1 == endPoints[i].y &&
				tmp->beforeList()->isEmpty()) {
				// 끝점은 연결하면 안됨
				x1 = -1; y1 = -1;
			}
			if (x2 == endPoints[i].x && 
				y2 == endPoints[i].y &&
				tmp->afterList()->isEmpty()) {
				// 끝점은 연결하면 안됨
				x2 = -1; y2 = -1;
			}
		}
		tmp->afterList()->clear();
		tmp->beforeList()->clear();
		LineNode *ptr1 = copied->getFirst();
		while(ptr1 != NIL) {
			if (ptr1 != tmp) {
				if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertAfter(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertAfter(ptr1);
				}
			}
			ptr1 = copied->getNext();
		}
		tmp = _lines->getNext();
	}
	delete copied;
	if (_type != STRAIGHT) return;
	BOOL *okFlags = new BOOL[nPoints];
	for (int i = 0; i < nPoints; i++) {
		okFlags[i] = FALSE;
	}
	tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		int x1 = line->getX1();
		int y1 = line->getY1();
		int x2 = line->getX2();
		int y2 = line->getY2();
		int i;
		for(i = 0; i < nPoints; i++) {
			if (x1 == endPoints[i].x && 
				y1 == endPoints[i].y &&
				tmp->beforeList()->isEmpty()) {
				okFlags[i] = TRUE;
			}
			if (x2 == endPoints[i].x && 
				y2 == endPoints[i].y &&
				tmp->afterList()->isEmpty()) {
				okFlags[i] = TRUE;
			}
		}
		tmp = _lines->getNext();
	}
	int i;;
	for (i = 0; i < nPoints; i++) {
		if (okFlags[i] == FALSE) {
			int x = endPoints[i].x;
			int y = endPoints[i].y;
			Line *newLine = new Line(_controller,x,y,NIL,STRAIGHT);
			newLine->setOrient(NORTH);
			LineNode *newNode = new LineNode(newLine);
			_lines->insert(newNode);
		}
	}
	delete []okFlags;
	copied = new LineNodeList();
	copied->copy(_lines);
	tmp = _lines->getFirst();
	while (tmp != NIL) {
		int x1,y1,x2,y2;
		tmp->line()->coords(x1,y1,x2,y2);
		for(int i = 0; i < nPoints; i++) {
			if (x1 == endPoints[i].x && 
				y1 == endPoints[i].y &&
				tmp->beforeList()->isEmpty()) {
				// 끝점은 연결하면 안됨
				x1 = -1; y1 = -1;
			}
			if (x2 == endPoints[i].x && 
				y2 == endPoints[i].y &&
				tmp->afterList()->isEmpty()) {
				// 끝점은 연결하면 안됨
				x2 = -1; y2 = -1;
			}
		}
		tmp->afterList()->clear();
		tmp->beforeList()->clear();
		LineNode *ptr1 = copied->getFirst();
		while(ptr1 != NIL) {
			if (ptr1 != tmp) {
				if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertAfter(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertAfter(ptr1);
				}
			}
			ptr1 = copied->getNext();
		}
		tmp = _lines->getNext();
	}
	delete copied;
}

void Lines::remake()
{
	LineNodeList *copied = new LineNodeList();
	copied->copy(_lines);
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		int x1,y1,x2,y2;
		tmp->line()->coords(x1,y1,x2,y2);
		tmp->afterList()->clear();
		tmp->beforeList()->clear();
		LineNode *ptr1 = copied->getFirst();
		while(ptr1 != NIL) {
			if (ptr1 != tmp) {
				if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x1,y1) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == TRUE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertAfter(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == TRUE) {
					tmp->insertBefore(ptr1);
				} else if (ptr1->line()->doesMeet(x2,y2) && 
					ptr1->line()->isObsolete() == FALSE &&
					tmp->line()->isObsolete() == FALSE) {
					tmp->insertAfter(ptr1);
				}
			}
			ptr1 = copied->getNext();
		}
		tmp = _lines->getNext();
	}
	delete copied;
}

/*
	_controller->clear(this);
	LineNode *tmp = _lines->getFirst();
	while (tmp != NIL) {
		Line *line = tmp->line();
		_controller->highlight(line);
		Sleep(1000);
		tmp = _lines->getNext();
	}
*/
