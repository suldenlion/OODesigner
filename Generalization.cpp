// Generalization.cpp: implementation of the Generalization class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "Generalization.h"
#include "Triangle.h"
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
#include "UnsignedLong.h"
#include "ClassTemplate.h"
#include "RelationshipInfoTupleList.h"

#define TRIANGLE_LENGTH		(20)
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Generalization,Connection,1)

Generalization::Generalization()
: Connection()
{
	_popup = theAppPtr->theGeneralizationPopup;

	_refinementFlag = FALSE;
}

Generalization::Generalization(COODView *controller,Popup *popup,Line *aLine)
: Connection(controller,popup,aLine)
{
	_refinementFlag = FALSE;
}

Generalization::~Generalization()
{
}

void Generalization::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (BYTE) _refinementFlag;
	} else {
		ar >> (BYTE&) _refinementFlag;
	}
	if (_refinementFlag) setStyle(DASHED); // 이 줄은 2005년도에는 없애도록 할 것
}

Figure* Generalization::born(Figure* ptr)
{
	Generalization *copied;
	if (ptr == NIL) {
		copied = new Generalization(NIL,NIL,NIL);
	} else {
		copied = (Generalization *)ptr;
	}
	copied->_refinementFlag = _refinementFlag;
	return (Connection::born((Figure *)copied));
}

UnsignedLong *Generalization::whoAreYou()
{
	return IAMGENERALIZATION; 
}

void Generalization::setRefinement()
{
	_refinementFlag = TRUE;
	_style = DASHED;
}

void Generalization::draw(CDC *dcp)
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

void Generalization::drawBoundary(CDC *dcp)
{
	Lines::draw(dcp);
	if (_text != NIL && 
		_text->isEmpty() == FALSE) {
		_text->draw(dcp);
	}
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		if (tuple->mark()) tuple->drawBoundary(dcp);
		else tuple->draw(dcp);
		tuple = _infoTuples->getNext();
	}
	if (_symbol != NIL) _symbol->drawBoundary(dcp);
}

void Generalization::clear(CDC* dcp)
{
	/*
	if (_text != NIL) _text->clear(dcp);
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		tuple->clear(dcp);
		tuple = _infoTuples->getNext();
	}
	*/
	if (_refinementFlag == TRUE) {
		if (_text != NIL) _text->clear(dcp);
		Lines::clear(dcp);
	} else {
		Connection::clear(dcp);
	}
}

void Generalization::drawing(CDC* dcp,int dx,int dy)
{
	if (_refinementFlag == TRUE) {
		Lines::drawing(dcp,dx,dy);
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			if (tuple->mark()) tuple->move(dcp,dx,dy);
			tuple = _infoTuples->getNext();
		}
	} else {
		Connection::drawing(dcp,dx,dy);
	}
}

void Generalization::move(CDC* dcp,int dx,int dy)
{
	if (_refinementFlag == TRUE) {
		Lines::move(dcp,dx,dy);
		if (_moveAllFlag) {
			if (_text != NIL && 
				_text->isEmpty() == FALSE) {
				_text->move(dcp,dx,dy);
			}
			ConnectionInfoTuple *tuple = _infoTuples->getFirst();
			while(tuple != NIL) {
				tuple->move(dcp,dx,dy);
				tuple = _infoTuples->getNext();
			}
			if (_symbol != NIL) _symbol->move(dcp,dx,dy);
		}
	} else {
		Connection::move(dcp,dx,dy);
	}
}

void Generalization::setModelSpecificSymbolAll()
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
	int endX,endY,startX,startY;
	endX = x;
	endY = y;
	if (firstLine == NIL) return;
	if (firstLine->isObsolete()) {
		int cx,cy;
		nodeFigure->shape()->center(cx,cy);
		startX = endX;
		if (cy > endY) {
			startY = endY - TRIANGLE_LENGTH;
		} else {
			startY = endY + TRIANGLE_LENGTH;
		}
	} else {
		firstLine->findTriangleStartPoints(endX,endY,startX,startY,TRIANGLE_LENGTH);
	}
	if (_symbol != NIL) {
		_controller->erase(_symbol);
		delete _symbol;
	}
	_symbol = new Triangle(_controller,startX,startY,endX,endY,NIL);
	Connection::setModelSpecificSymbolAll();
}

BOOL Generalization::setModelSpecificSymbol(NodeFigure *nodeFocus)
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
		firstLine->findTriangleStartPoints(endX,endY,startX,startY,TRIANGLE_LENGTH);
		if (_symbol != NIL) delete _symbol;
		_symbol = new Triangle(_controller,startX,startY,endX,endY,NIL);
		return FALSE;
	} 
	return FALSE;
}

void Generalization::registerGeneralizationInfo()
{
	if (_controller->GetDocument()->IsEmbedded()) return;
	registerGeneralizationInfoEx();
}

void Generalization::registerGeneralizationInfoEx()
{
	NodeFigure *firstNode = _nodeFigures->getFirst();
	if (firstNode->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		return;
	}
	ClassTemplate *superClass = (ClassTemplate *)firstNode;
	char superClassName[BUFSIZ];
	superClass->getName(superClassName,BUFSIZ);
	NodeFigure *childClassNode = _nodeFigures->getNext();
	while (childClassNode != NIL) {
		if (childClassNode->whoAreYou()->equals(IAMCLASSTEMPLATE) == TRUE) {
			ClassTemplate *subClass = (ClassTemplate *)childClassNode;
			char subClassName[BUFSIZ];
			subClass->getName(subClassName,BUFSIZ);
			if (theAppPtr->pCOODClassDoc != NIL) {
				if (_refinementFlag == FALSE) {
					theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->registerRelationshipInfo(superClassName,subClassName,"Generalization");
				} else {
					theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->registerRelationshipInfo(superClassName,subClassName,"Refinement");
				}
			}
		}
		childClassNode = _nodeFigures->getNext();
	}
}
