// Dependency.cpp: implementation of the Dependency class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Dependency.h"
#include "AnytionInfoTuple.h"
#include "Line.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "ConnectionText.h"
#include "COODClassDoc.h"
#include "RelationshipInfoTupleList.h"
#include "UnsignedLong.h"
#include "ClassTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Dependency,Connection,1)

Dependency::Dependency()
: Connection()
{
	_popup = theAppPtr->theDependencyPopup;
	_style = DASHED;
}

Dependency::Dependency(COODView *controller,Popup *popup,Line *aLine)
: Connection(controller,popup,aLine)
{
	_style = DASHED;
}

Dependency::~Dependency()
{
}

void Dependency::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
	setStyle(DASHED); // 이 줄은 2005년도에는 없애도록 할 것
}

Figure* Dependency::born(Figure* ptr)
{
	Dependency *copied;
	if (ptr == NIL) {
		copied = new Dependency(NIL,NIL,NIL);
	} else {
		copied = (Dependency *)ptr;
	}
	return (Connection::born((Figure *)copied));
}


UnsignedLong *Dependency::whoAreYou()
{
	return IAMDEPENDENCY; 
}

void Dependency::drawBoundary(CDC *dcp)
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

void Dependency::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	if (_text != NIL) _text->draw(dcp);
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		tuple->draw(dcp);
		tuple = _infoTuples->getNext();
	}
	Lines::draw(dcp);
}

void Dependency::clear(CDC* dcp)
{
	/*
	if (_text != NIL) _text->clear(dcp);
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		tuple->clear(dcp);
		tuple = _infoTuples->getNext();
	}
	*/
	Lines::clear(dcp);
}

void Dependency::drawing(CDC* dcp,int dx,int dy)
{
	Lines::drawing(dcp,dx,dy);
	ConnectionInfoTuple *tuple = _infoTuples->getFirst();
	while(tuple != NIL) {
		if (tuple->mark()) tuple->move(dcp,dx,dy);
		tuple = _infoTuples->getNext();
	}
}

void Dependency::move(CDC* dcp,int dx,int dy)
{
	Lines::move(dcp,dx,dy);
	if (_moveAllFlag) {
		if (_text != NIL) _text->move(dcp,dx,dy);
		ConnectionInfoTuple *tuple = _infoTuples->getFirst();
		while(tuple != NIL) {
			tuple->move(dcp,dx,dy);
			tuple = _infoTuples->getNext();
		}
	}
}

BOOL Dependency::setModelSpecificSymbol(NodeFigure *nodeFocus)
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
	lastLine->setDir(NORMAL_DIR,HEADARROW2);
	int x = lastLine->getX2();
	int y = lastLine->getY2();
	AnytionInfoTuple *aTuple = 
		new AnytionInfoTuple(nodeFocus,x,y);
	_infoTuples->insert(aTuple);
	return FALSE;
}

void Dependency::setModelSpecificSymbolAll()
{
	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		aNode->line()->setDir(NODIR,HEADNONE);
		aNode = _lines->getNext();
	}
	NodeFigure *nodeFigure = _nodeFigures->getFirst();
	nodeFigure = _nodeFigures->getNext();
	while (nodeFigure != NIL) {
		ConnectionInfoTuple *aTuple = _infoTuples->findTupleFor(nodeFigure);
		int x = aTuple->getX();
		int y = aTuple->getY();
		Line *foundLine = NIL;
		int where;
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			where = aNode->line()->whereToMeet(x,y); 
			if (where == ATBEFORE || where == ATAFTER) {
				foundLine = aNode->line();
				break;
			}
			aNode = _lines->getNext();
		}
		if (foundLine != NIL) {
			if (where == ATBEFORE) {
				foundLine->setDir(INVERT_DIR,HEADARROW2);	
			} else {
				foundLine->setDir(NORMAL_DIR,HEADARROW2);	
			}
		}
		nodeFigure = _nodeFigures->getNext();
	}
	Connection::setModelSpecificSymbolAll();
	/*
	NodeFigure *nodeFigure = _nodeFigures->getLast();
	ConnectionInfoTuple *aTuple = _infoTuples->getLast();
	if (aTuple == NIL) return;
	int x = aTuple->getX();
	int y = aTuple->getY();
	int where = -1;
	Line *lastLine = NIL;
	aNode = _lines->getFirst();
	while(aNode != NIL) {
		where = aNode->line()->whereToMeet(x,y); 
		if (where == ATBEFORE || where == ATAFTER) {
			lastLine = aNode->line();
			break;
		}
		aNode = _lines->getNext();
	}
	if (lastLine == NIL) return;
	if (where == ATBEFORE) {
		lastLine->setDir(INVERT_DIR,HEADARROW2);	
	} else {
		lastLine->setDir(NORMAL_DIR,HEADARROW2);	
	}
	*/
}

void Dependency::registerDependencyInfo()
{
	if (_controller->GetDocument()->IsEmbedded()) return;
	registerDependencyInfoEx();
}

void Dependency::registerDependencyInfoEx()
{
	NodeFigure *firstNode = _nodeFigures->getFirst();
	if (firstNode->whoAreYou()->equals(IAMCLASSTEMPLATE) == FALSE) {
		return;
	}
	ClassTemplate *callerClass = (ClassTemplate *)firstNode;
	char callerClassName[BUFSIZ];
	callerClass->getName(callerClassName,BUFSIZ);
	NodeFigure *calledClassNode = _nodeFigures->getNext();
	while (calledClassNode != NIL) {
		if (calledClassNode->whoAreYou()->equals(IAMCLASSTEMPLATE) == TRUE) {
			ClassTemplate *calledClass = (ClassTemplate *)calledClassNode;
			char calledClassName[BUFSIZ];
			calledClass->getName(calledClassName,BUFSIZ);
			if (theAppPtr->pCOODClassDoc != NIL) {
				theAppPtr->pCOODClassDoc->getDependencyLibrary()->registerRelationshipInfo(callerClassName,calledClassName,"Dependency");
			}
		}
		calledClassNode = _nodeFigures->getNext();
	}
}
