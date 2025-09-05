#include "stdafx.h"
/* LineNode.C */

#include "LineNode.h"
// Super Class : None

#include "COODView.h" // Collaboration
#include "LineNodeList.h"
#include "Line.h"

IMPLEMENT_SERIAL(LineNode,CObject,1)

LineNode::LineNode(Line *line,LineNode *before,LineNode *after)
: CObject()
{
	_beforeList = new LineNodeList();
	_afterList = new LineNodeList();
	_line = line;
	_mother = NIL;
	_borned = NIL;
	resetFlags();
	if (before != NIL) {
		before->insert(this,ATBEFORE);
		insertBefore(before);
	}
	if (after != NIL) {
		after->insert(this,ATAFTER);
		insertAfter(after);
	}
}

LineNode::~LineNode()
{
	delete _beforeList; _beforeList = NIL;
	delete _afterList; _afterList = NIL;
	_line = NIL;
	_mother = NIL;
	_borned = NIL;
}

void LineNode::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	_beforeList->Serialize(ar);
	_afterList->Serialize(ar);
	if (ar.IsStoring()) {
		ar << _line << _borned << _mother;
	} else {
		ar >> _line >> _borned >> _mother;
	}
}

void LineNode::insertObsoleteNode(LineNode *newNode)
{
	Line *line = newNode->_line;
	int where = _line->whereToMeet(line);
	if (where == ATBEFORE) {
		LineNode *node = _beforeList->getFirst();
		while(node != NIL) {
			where = node->_line->whereToMeet(line);
			if (where == ATBEFORE) {
				node->insertBefore(newNode);
			} else if (where == ATAFTER) {
				node->insertAfter(newNode);
			}
			newNode->insertBefore(node);
			node = _beforeList->getNext();
		}
		insertBefore(newNode);
	} else if (where == ATAFTER) {
		LineNode *node = _afterList->getFirst();
		while(node != NIL) {
			where = node->_line->whereToMeet(line);
			if (where == ATBEFORE) {
				node->insertBefore(newNode);
			} else if (where == ATAFTER) {
				node->insertAfter(newNode);
			}
			newNode->insertBefore(node);
			node = _afterList->getNext();
		}
		insertAfter(newNode);
	}
}

void LineNode::insert(LineNode *lineNode,int hot_spot)
{
	Line *line = lineNode->_line;
	int where = _line->whereToMeet(line);
	if (where == ATBEFORE) {
		LineNode *node = _beforeList->getFirst();
		while(node != NIL) {
			where = node->_line->whereToMeet(line);
			if (where == ATBEFORE) {
				node->insertBefore(lineNode);
			} else if (where == ATAFTER) {
				node->insertAfter(lineNode);
			}
			if (hot_spot == ATBEFORE) {
				lineNode->insertBefore(node);
			} else /* ATAFTER */ {
				lineNode->insertAfter(node);
			}
			node = _beforeList->getNext();
		}
		insertBefore(lineNode);
	} else if (where == ATAFTER) {
		LineNode *node = _afterList->getFirst();
		while(node != NIL) {
			where = node->_line->whereToMeet(line);
			if (where == ATBEFORE) {
				node->insertBefore(lineNode);
			} else if (where == ATAFTER) {
				node->insertAfter(lineNode);
			}
			if (hot_spot == ATBEFORE) {
				lineNode->insertBefore(node);
			} else /* ATAFTER */ {
				lineNode->insertAfter(node);
			}
			node = _afterList->getNext();
		}
		insertAfter(lineNode);
	}
}

LineNodeList *LineNode::beforeList()
{
	return _beforeList;
}

LineNodeList *LineNode::afterList()
{
	return _afterList;
}

Line* LineNode::line()
{
	return _line;
}

void LineNode::insertBefore(LineNode *lineNode)
{
	_beforeList->insert(lineNode);
}

void LineNode::insertAfter(LineNode *lineNode)
{
	_afterList->insert(lineNode);
}

void LineNode::removeBefore(LineNode *lineNode)
{
	_beforeList->remove(lineNode);
}

void LineNode::removeAfter(LineNode *lineNode)
{
	_afterList->remove(lineNode);
}

void LineNode::swapBeforeAfter()
{
	LineNodeList *tmp = _beforeList;
	_beforeList = _afterList;
	_afterList = tmp;	
}

void LineNode::merge(LineNode *node,LineNodeList *wheretoput)
{
	if (node->_afterList->inList(this)) {
		LineNode *ptr = node->_beforeList->getFirst();
		while(ptr != NIL) {
			wheretoput->insert(ptr);
			ptr->insertANodeForNodeToBeDeleted(this,node);
			ptr = node->_beforeList->getNext();
		}
	} else /* in _beforelist */ {
		LineNode *ptr = node->_afterList->getFirst();
		while(ptr != NIL) {
			wheretoput->insert(ptr);
			ptr->insertANodeForNodeToBeDeleted(this,node);
			ptr = node->_afterList->getNext();
		}
	}
}

void LineNode::insertANodeForNodeToBeDeleted(LineNode *me,LineNode *tobedelete)
{
	if (_afterList->inList(tobedelete)) {
		_afterList->insert(me);
	} else if (_beforeList->inList(tobedelete)) {
		_beforeList->insert(me);
	}
}

int LineNode::nOfNeigborNodes()
{
	return _afterList->nOfList() + _beforeList->nOfList();
}

BOOL LineNode::checkIfObsolete()
{
	if (_mark) return FALSE;
	_mark = TRUE;
	if (_line->isObsolete()) {
		LineNode* ptr = _afterList->getFirst();
		while (ptr != NIL) {
			LineNode* tmp = _beforeList->getFirst();
			while (tmp != NIL) {
				if (tmp->_beforeList->inList(this) &&
					(ptr != tmp)) {
					tmp->_beforeList->insert(ptr);
				} else if (tmp->_afterList->inList(this) &&
					(ptr != tmp)) {
					tmp->_afterList->insert(ptr);
				}
				tmp = _beforeList->getNext();
			}
			ptr = _afterList->getNext();
		}
		ptr = _beforeList->getFirst();
		while (ptr != NIL) {
			LineNode* tmp = _afterList->getFirst();
			while (tmp != NIL) {
				if (tmp->_beforeList->inList(this) &&
					(ptr != tmp)) {
					tmp->_beforeList->insert(ptr);
				} else if (tmp->_afterList->inList(this) &&
					(ptr != tmp)) {
					tmp->_afterList->insert(ptr);
				}
				tmp = _afterList->getNext();
			}
			ptr = _beforeList->getNext();
		}
		delete _line;
		return TRUE;
	} else {
		return FALSE;
	}
}

BOOL LineNode::checkToMerge(COODView *controller,LineNodeList *lines,BOOL rubberbandingFlag)
{
	if (_mark) return FALSE;
	BOOL changed = FALSE;
	_mark = TRUE;
	if (_line->isObsolete()) return FALSE;
	if (_afterList->nOfList() == 1) {
		// possible to merge
		LineNode *lineNode = _afterList->getFirst();
		Line *candidate = lineNode->_line;
		if (candidate->isObsolete() == FALSE &&
			lineNode->_mark == FALSE) {
			BOOL tomerge = _line->checkToMerge(candidate);
			if (tomerge) {
				controller->clear(_line);
				controller->clear(candidate);
				_line->merge(candidate);
				merge(lineNode,_afterList);
				if (rubberbandingFlag) {
					controller->rubberbanding(_line);
				} else {
					controller->draw(_line);
				}
				delete candidate;
				delete lineNode;
				lines->remove(lineNode,TRUE);
				changed = TRUE;
				_mark = FALSE;
			}
		}
		if (changed) return TRUE;
	}
	if (_beforeList->nOfList() == 1) {
		// possible to merge
		LineNode *lineNode = _beforeList->getFirst();
		Line *candidate = lineNode->_line;
		if (candidate->isObsolete()) return changed;
		if (lineNode->_mark == TRUE) return changed;
		BOOL tomerge = _line->checkToMerge(candidate);
		if (tomerge) {
			controller->clear(_line);
			controller->clear(candidate);
			_line->merge(candidate);
			merge(lineNode,_beforeList);
			if (rubberbandingFlag) {
				controller->rubberbanding(_line);
			} else {
				controller->draw(_line);
			}
			delete candidate;
			delete lineNode;
			lines->remove(lineNode,TRUE);
			changed = TRUE;
		}
	}
	return changed;
}

BOOL &LineNode::mark()
{
	return _mark;
}

BOOL &LineNode::move()
{
	return _move;
}

BOOL &LineNode::cascade()
{
	return _cascade;
}

void LineNode::resetFlags()
{
	_mark = FALSE;
	_move = FALSE;
	_cascade = FALSE;
}

void LineNode::setFollowLinesOnNodeBoundary(LineNodeList *newLineNodes)
{
	int x = _line->notHotX()->get();
	int y = _line->notHotY()->get();
	int whereToFollow = _line->whereToFollow();
	if (whereToFollow == ATBEFORE) {
		if (_beforeList->isEmpty() == FALSE) return;
		Line *newLine = new Line(_line->controller(),x,y,NIL,STRAIGHT);
		newLine->setOrient(Line::invertOrient(_line->orient()));
		newLine->setFollowing2(x,y);
		LineNode *newNode = new LineNode(newLine);
		insertBefore(newNode);
		newNode->insertAfter(this);
		newLineNodes->insert(newNode);
	} else if (whereToFollow == ATAFTER) {
		if (_afterList->isEmpty() == FALSE) return;
		Line *newLine = new Line(_line->controller(),x,y,NIL,STRAIGHT);
		newLine->setOrient(Line::invertOrient(_line->orient()));
		newLine->setFollowing2(x,y);
		LineNode *newNode = new LineNode(newLine);
		insertAfter(newNode);
		newNode->insertAfter(this);
		newLineNodes->insert(newNode);
	}
}

void LineNode::setFollowLines(LineNodeList *newLineNodes)
{
	int x = _line->notHotX()->get();
	int y = _line->notHotY()->get();
	int whereToFollow = _line->whereToFollow();
	if (whereToFollow == ATBEFORE) {
		LineNode *node = _beforeList->getFirst();
		while (node != NIL) {
			Line *line = node->line();
			BOOL followed = line->setFollowing(x,y,_line->orient());
			if (followed && line->hotX() == NIL && line->hotY() == NIL) {
				Line *newLine = new Line(line->controller(),x,y,NIL,STRAIGHT);
				newLine->setFollowing2(x,y);
				newLine->setOrient(Line::invertOrient(_line->orient()));
				LineNode *newNode = new LineNode(newLine);
				newLineNodes->insert(newNode);
			}
			node = _beforeList->getNext();
		}
		LineNode *newNode = newLineNodes->getFirst();
		while (newNode != NIL) {
			insertObsoleteNode(newNode);
			newNode->insertBefore(this);
			newNode = newLineNodes->getNext();
		}
	} else if (whereToFollow == ATAFTER) {
		LineNode *node = _afterList->getFirst();
		while (node != NIL) {
			Line *line = node->line();
			BOOL followed = line->setFollowing(x,y,_line->orient());
			if (followed && line->hotX() == NIL && line->hotY() == NIL) {
				Line *newLine = new Line(line->controller(),x,y,NIL,STRAIGHT);
				newLine->setFollowing2(x,y);
				newLine->setOrient(Line::invertOrient(_line->orient()));
				LineNode *newNode = new LineNode(newLine);
				newLineNodes->insert(newNode);
			}
			node = _afterList->getNext();
		}
		LineNode *newNode = newLineNodes->getFirst();
		while (newNode != NIL) {
			insertObsoleteNode(newNode);
			newNode->insertBefore(this);
			newNode = newLineNodes->getNext();
		}
	}
}

BOOL LineNode::neighbor(LineNode *node)
{
	if (_beforeList->inList(node)) return TRUE;
	if (_afterList->inList(node)) return TRUE;
	return FALSE;
}

LineNode *LineNode::removeCycle()
{
	_mark = TRUE;
	if (_beforeList->isEmpty()) {
		LineNode *aNode = _afterList->getFirst();
		BOOL allMarked = TRUE;
		while(aNode != NIL) {
			if (aNode->mark() == FALSE) {
				allMarked = FALSE;
				break;
			}
			aNode = _afterList->getNext();
		}
		if (allMarked) return NIL;
	}
	if (_afterList->isEmpty()) {
		LineNode *aNode = _beforeList->getFirst();
		BOOL allMarked = TRUE;
		while(aNode != NIL) {
			if (aNode->mark() == FALSE) {
				allMarked = FALSE;
				break;
			}
			aNode = _beforeList->getNext();
		}
		if (allMarked) return NIL;
	}
	LineNode *aNode = _afterList->getFirst();
	BOOL afterMark = FALSE;
	while(aNode != NIL) {
		if (aNode->mark() == TRUE) {
			afterMark = TRUE;
			break;
		}
		aNode = _afterList->getNext();
	}
	aNode = _beforeList->getFirst();
	BOOL beforeMark = FALSE;
	while(aNode != NIL) {
		if (aNode->mark() == TRUE) {
			beforeMark = TRUE;
			break;
		}
		aNode = _beforeList->getNext();
	}
	if (beforeMark && afterMark) return this;
	aNode = _afterList->getFirst();
	while(aNode != NIL) {
		if (aNode->mark() == FALSE) {
			LineNode *nodeToRemove = aNode->removeCycle();
			if (nodeToRemove != NIL) return nodeToRemove;
		}
		aNode = _afterList->getNext();
	}
	aNode = _beforeList->getFirst();
	while(aNode != NIL) {
		if (aNode->mark() == FALSE) {
			LineNode *nodeToRemove = aNode->removeCycle();
			if (nodeToRemove != NIL) return nodeToRemove;
			break;
		}
		aNode = _beforeList->getNext();
	}
	return NIL;
}

BOOL LineNode::hasObsoletePointNeighborAt(int x,int y)
{
	int x1 = _line->getX1();
	int y1 = _line->getY1();
	int x2 = _line->getX2();
	int y2 = _line->getY2();
	if (x == x1 && y == y1) {
		LineNode *aNode = _beforeList->getFirst();
		while (aNode != NIL) {
			if (aNode->line()->isObsolete()) return TRUE;
			aNode = _beforeList->getNext();
		}
	} else if (x == x2 && y == y2) {
		LineNode *aNode = _afterList->getFirst();
		while (aNode != NIL) {
			if (aNode->line()->isObsolete()) return TRUE;
			aNode = _afterList->getNext();
		}
	}
	return FALSE;
}

int LineNode::nOfVisitedLinesFromANode()
{
	// 이 함수는 reachability를 체크하는 거과 같다.
	_mark = TRUE;
	int count = 1;
	LineNodeList *copiedBeforeList = new LineNodeList();
	copiedBeforeList->copy(_beforeList);
	if (copiedBeforeList->isEmpty() == FALSE) {
		LineNode *aNode = copiedBeforeList->getFirst();
		while(aNode != NIL) {
			if (aNode->mark() == FALSE) {
				count = count + aNode->nOfVisitedLinesFromANode();
			}
			aNode = copiedBeforeList->getNext();
		}
	}
	copiedBeforeList->clear();
	delete copiedBeforeList;
	LineNodeList *copiedAfterList = new LineNodeList();
	copiedAfterList->copy(_afterList);
	if(copiedAfterList->isEmpty() == FALSE) {
		LineNode *aNode = copiedAfterList->getFirst();
		while(aNode != NIL) {
			if (aNode->mark() == FALSE) {
				count = count + aNode->nOfVisitedLinesFromANode();
			}
			aNode = copiedAfterList->getNext();
		}
	}
	copiedAfterList->clear();
	delete copiedAfterList;
	return count;
}
