// Association.cpp: implementation of the Association class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Association.h"
#include "AnytionInfoTuple.h"
#include "Line.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "ConnectionText.h"
#include "Diamond.h"
#include "AssociationPopup.h"
#include "ClassTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DIAMOND_WIDTH	(15)
#define DIAMOND_HEIGHT	(10)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Association,Connection,1)

Association::Association()
: Connection()
{
	_popup = theAppPtr->theAssociationPopup;

	_associationClassPtr = NIL;
	_canDoAssociationClass = FALSE;
}

Association::Association(COODView *controller,Popup *popup,Line *aLine)
: Connection(controller,popup,aLine)
{
	_associationClassPtr = NIL;
	_canDoAssociationClass = FALSE;
}

Association::~Association()
{
	if (_associationClassPtr != NIL) {
		_associationClassPtr->setAssociationPtr(NIL);
		_associationClassPtr = NIL;
	}
}

void Association::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _associationClassPtr;
	} else {
		ar >> _associationClassPtr;
	}
}

void Association::getCenterPosition(int &cx,int &cy)
{
	if (isLinearConnection(FALSE) == TRUE) {
		int nLines = _lines->nOfList();
		int where;
		LineNode *aLineNode = findABoundaryLineNode(where);
		if (aLineNode == NIL) {
			Lines::center(cx,cy);
			return;
		}
		int nLines_2 = nLines/2;
		if (2*nLines_2 == nLines) {
			for (int i = 0; i < nLines_2-1; i++) {
				aLineNode = findNextLineNode(aLineNode,where);
				if (aLineNode == NIL) {
					Lines::center(cx,cy);
					return;
				}
			}
			Line *aLine = aLineNode->line();
			if (where == ATBEFORE) {
				cx = aLine->getX2();
				cy = aLine->getY2();
			} else {
				cx = aLine->getX2();
				cy = aLine->getY2();
			}
			return;
		} else {
			for (int i = 0; i < nLines_2; i++) {
				aLineNode = findNextLineNode(aLineNode,where);
				if (aLineNode == NIL) {
					Lines::center(cx,cy);
					return;
				}
			}
			aLineNode->line()->center(cx,cy);
			return;
		}
	} else {
		CPoint point;
		getJointPoint(point);
		cx = point.x;
		cy = point.y;
		return;
	}
}

BOOL Association::getJointPoint(CPoint &aPoint)
{
	aPoint.x = -1;
	aPoint.y = -1;
	LineNode *aNode = _lines->getFirst();
	while (aNode != NIL) {
		int nOfListWithoutObsoleteLine = 0;
		LineNode *tmpNode = aNode->beforeList()->getFirst();
		while(tmpNode != NIL) {
			if (tmpNode->line()->isObsolete() == FALSE)
				nOfListWithoutObsoleteLine++;
			tmpNode = aNode->beforeList()->getNext();
		}
		if (nOfListWithoutObsoleteLine > 1) {
			aPoint.x = aNode->line()->getX1();
			aPoint.y = aNode->line()->getY1();
			return TRUE;
		}
		nOfListWithoutObsoleteLine = 0;
		tmpNode = aNode->afterList()->getFirst();
		while(tmpNode != NIL) {
			if (tmpNode->line()->isObsolete() == FALSE)
				nOfListWithoutObsoleteLine++;
			tmpNode = aNode->afterList()->getNext();
		}
		if (nOfListWithoutObsoleteLine > 1) {
			aPoint.x = aNode->line()->getX2();
			aPoint.y = aNode->line()->getY2();
			return TRUE;
		}
		aNode = _lines->getNext();
	}
	return FALSE;
}

Figure* Association::born(Figure* ptr)
{
	Association *copied;
	if (ptr == NIL) {
		copied = new Association(NIL,NIL,NIL);
	} else {
		copied = (Association *)ptr;
	}
	return (Connection::born((Figure *)copied));
}


UnsignedLong *Association::whoAreYou()
{
	return IAMASSOCIATION; 
}

void Association::popup(CPoint* event,BOOL flag)
{
	if (_associationClassPtr != NIL) {
		_canDoAssociationClass = FALSE;
	} else {
		_canDoAssociationClass = TRUE;
	}
	Connection::popup(event,flag);
}

void Association::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	Lines::draw(dcp);
	if (_text != NIL && 
		_text->isEmpty() == FALSE) {
		_text->draw(dcp);
	}
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		tuple->draw(dcp);
		tuple = _infoTuples->getNext();
	}
	if (_symbol != NIL) _symbol->draw(dcp);
}

void Association::doAcompanySymbol(NodeFigure *leader)
{
	if (_associationClassPtr) {
		_associationClassPtr->setAssociationPtr(NIL);
	}
	if (_symbol) {
		delete _symbol; _symbol = NIL;
	}
	_symbolMoveFlag = FALSE;
}

void Association::clearSymbolIfFirstLine()
{
	if (_symbol) {
		delete _symbol; _symbol = NIL;
	}
}

BOOL Association::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	int n = _nodeFigures->nOfList();
	if (n < 1) {
		return TRUE;
	} 
	if (n == 1) {
		Line *firstLine = _lines->getFirst()->line();
		int x1 = firstLine->getX1();
		int y1 = firstLine->getY1();
		AnytionInfoTuple *aTuple = 
			new AnytionInfoTuple(_nodeFigures->getFirst(),x1,y1);
		_infoTuples->insert(aTuple);
	}
	Line *lastLine = _lines->getLast()->line();
	int x = lastLine->getX2();
	int y = lastLine->getY2();
	AnytionInfoTuple *aTuple = 
		new AnytionInfoTuple(nodeFocus,x,y);
	_infoTuples->insert(aTuple);
	if (_infoTuples->nOfList() == 3) {
		makeTernarySymbol();
	}
	if (_associationClassPtr) {
		_associationClassPtr->setAssociationPtr(this);
	}
	return FALSE;
}

void Association::resizeProlog(NodeFigure* aNode)
{
	if (_associationClassPtr) {
		_associationClassPtr->setAssociationPtr(NIL);
	}
	Connection::resizeProlog(aNode);
}

BOOL Association::moveProlog(BOOL moveAllFlag)
{
	if (moveAllFlag == FALSE) {
		if (_associationClassPtr) {
			_associationClassPtr->setAssociationPtr(NIL);
		}
	}
	return Connection::moveProlog(moveAllFlag);
}

void Association::setModelSpecificSymbolAll()
{
	if (_infoTuples->nOfList() == 3) {
		makeTernarySymbol();
	}
	if (_associationClassPtr) {
		_associationClassPtr->setAssociationPtr(this);
	}
	Connection::setModelSpecificSymbolAll();
}

void Association::makeTernarySymbol()
{
	CPoint jointPoint;
	if (getJointPoint(jointPoint)) {
		// ternary association
		if (_symbol != NIL) {
			delete _symbol;
		}
		int x1 = jointPoint.x - DIAMOND_WIDTH;
		int y1 = jointPoint.y - DIAMOND_HEIGHT;
		int x2 = jointPoint.x + DIAMOND_WIDTH;
		int y2 = jointPoint.y + DIAMOND_HEIGHT;
		_symbol = new Diamond(_controller,x1,y1,x2,y2,NIL);
	}
}

