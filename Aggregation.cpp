// Aggregation.cpp: implementation of the Aggregation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Aggregation.h"
#include "Diamond.h"
#include "AnytionInfoTuple.h"
#include "Line.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "ConnectionText.h"
#include "NodeFigure.h"
#include "COODClassDoc.h"
#include "RelationshipInfoTupleList.h"
#include "UnsignedLong.h"
#include "ClassTemplate.h"

#define DIAMOND_LENGTH		(24)
#define DIAMOND_OFFSET		(8)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Aggregation,Connection,1)

Aggregation::Aggregation()
: Connection()
{
	_popup = theAppPtr->theAggregationPopup;

	_compositionFlag = FALSE;
}

Aggregation::Aggregation(COODView *controller,Popup *popup,Line *aLine)
: Connection(controller,popup,aLine)
{
	_compositionFlag = FALSE;
}

Aggregation::~Aggregation()
{
}

void Aggregation::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (BYTE) _compositionFlag;
	} else {
		ar >> (BYTE&) _compositionFlag;
	}
}

Figure* Aggregation::born(Figure* ptr)
{
	Aggregation *copied;
	if (ptr == NIL) {
		copied = new Aggregation(NIL,NIL,NIL);
	} else {
		copied = (Aggregation *)ptr;
	}
	copied->_compositionFlag = _compositionFlag;
	return (Connection::born((Figure *)copied));
}

UnsignedLong *Aggregation::whoAreYou()
{
	return IAMAGGREGATION; 
}

void Aggregation::setComposition()
{
	_compositionFlag = TRUE;
}

void Aggregation::draw(CDC *dcp)
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

BOOL Aggregation::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	int n = _nodeFigures->nOfList();
	if (n < 1) {
		return TRUE;
	} 
	Line *firstLine = _lines->getFirst()->line();
	NodeFigure *firstNode = _nodeFigures->getFirst();
	if (n == 1) {
		int x1 = firstLine->getX1();
		int y1 = firstLine->getY1();
		AnytionInfoTuple *aTuple = new AnytionInfoTuple(firstNode,x1,y1);
		_infoTuples->insert(aTuple);
	}
	Line *lastLine = _lines->getLast()->line();
	int x = lastLine->getX2();
	int y = lastLine->getY2();
	AnytionInfoTuple *aTuple = 
		new AnytionInfoTuple(nodeFocus,x,y);
	_infoTuples->insert(aTuple);

	if (n == 1) {
		int x1,y1,x2,y2;
		firstLine->coords(x1,y1,x2,y2);
		int endX,endY,startX,startY;
		if (firstNode->shape()->contains(x1,y1)) {
			endX = x1; endY = y1;
		} else {
			endX = x2; endY = y2;
		}
		firstLine->findDiamondEndCorners(endX,endY,startX,startY,DIAMOND_LENGTH,DIAMOND_OFFSET);
		if (_symbol != NIL) delete _symbol;
		_symbol = new Diamond(_controller,startX,startY,endX,endY,NIL);
		if (_compositionFlag == TRUE) {
			_symbol->filled() = TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

void Aggregation::setModelSpecificSymbolAll()
{
	NodeFigure *nodeFigure = _nodeFigures->getFirst();
	ConnectionInfoTuple *aTuple = _infoTuples->getFirst();
	if (aTuple == NIL) return;
	int x = aTuple->getX();
	int y = aTuple->getY();
	int where = -1;
	LineNode *aNode = _lines->getFirst();
	Line *firstLine = NIL;
	while(aNode != NIL) {
		where = aNode->line()->whereToMeet(x,y); 
		if (where == ATBEFORE || where == ATAFTER) {
			firstLine = aNode->line();
			break;
		}
		aNode = _lines->getNext();
	}
	if (firstLine == NIL) return;
	int x1,y1,x2,y2;
	firstLine->coords(x1,y1,x2,y2);
	int endX,endY,startX,startY;
	if (nodeFigure->shape()->contains(x1,y1)) {
		endX = x1; endY = y1;
	} else {
		endX = x2; endY = y2;
	}
	if (firstLine->isObsolete()) {
		int nx1,ny1,nx2,ny2;
		nodeFigure->shape()->coords(nx1,ny1,nx2,ny2);
		if (x1 == nx1 || x1 == nx2 || x2 == nx2-1) {
			startY = endY - DIAMOND_OFFSET;
			endY = endY + DIAMOND_OFFSET;
			if (nx1 >= endX-1) {
				startX = endX - DIAMOND_LENGTH;
			} else {
				startX = endX + DIAMOND_LENGTH;
			}
		} else {
			startX = endX + DIAMOND_OFFSET;
			endX = endX - DIAMOND_OFFSET;
			if (ny1 >= endY-1) {
				startY = endY - DIAMOND_LENGTH;
			} else {
				startY = endY + DIAMOND_LENGTH;
			}
		}
	} else {
		firstLine->findDiamondEndCorners(endX,endY,startX,startY,DIAMOND_LENGTH,DIAMOND_OFFSET);
	}
	if (_symbol != NIL) {
		_controller->erase(_symbol);
		delete _symbol;
	}
	_symbol = new Diamond(_controller,startX,startY,endX,endY,NIL);
	if (_compositionFlag == TRUE) {
		_symbol->filled() = TRUE;
	}
	Connection::setModelSpecificSymbolAll();
}

void Aggregation::registerAggregationInfoEx()
{
	NodeFigure *firstNode = _nodeFigures->getFirst();
	if (firstNode->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		return;
	}
	ClassTemplate *containerClass = (ClassTemplate *)firstNode;
	char containerClassName[BUFSIZ];
	containerClass->getName(containerClassName,BUFSIZ);
	NodeFigure *containedClassNode = _nodeFigures->getNext();
	while (containedClassNode != NIL) {
		if (containedClassNode->whoAreYou()->equals(IAMCLASSTEMPLATE) == TRUE) {
			ClassTemplate *containedClass = (ClassTemplate *)containedClassNode;
			char containedClassName[BUFSIZ];
			containedClass->getName(containedClassName,BUFSIZ);
			if (theAppPtr->pCOODClassDoc != NIL) {
				if (_compositionFlag == FALSE) {
					theAppPtr->pCOODClassDoc->getAggregationLibrary()->registerRelationshipInfo(containerClassName,containedClassName,"Aggregation");
				} else {
					theAppPtr->pCOODClassDoc->getAggregationLibrary()->registerRelationshipInfo(containerClassName,containedClassName,"Composition");
				}
			}
		}
		containedClassNode = _nodeFigures->getNext();
	}
}

void Aggregation::registerAggregationInfo()
{
	if (_controller->GetDocument()->IsEmbedded()) return;
	registerAggregationInfoEx();
}
