// Communication.cpp: implementation of the Communication class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Communication.h"
#include "AnytionInfoTuple.h"
#include "Line.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "ConnectionText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Communication,Dependency,1)

Communication::Communication()
: Dependency()
{
}

Communication::Communication(COODView *controller,Popup *popup,Line *aLine)
: Dependency(controller,popup,aLine)
{
}

Communication::~Communication()
{
}

void Communication::Serialize(CArchive& ar)
{
	Dependency::Serialize(ar);
}

Figure* Communication::born(Figure* ptr)
{
	Communication *copied;
	if (ptr == NIL) {
		copied = new Communication(NIL,NIL,NIL);
	} else {
		copied = (Communication *)ptr;
	}
	return (Dependency::born((Figure *)copied));
}


UnsignedLong *Communication::whoAreYou()
{
	return IAMCOMMUNICATION; 
}

BOOL Communication::setModelSpecificSymbol(NodeFigure *nodeFocus)
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
		firstLine->setDir(INVERT_DIR,HEADARROW2);
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

void Communication::setModelSpecificSymbolAll()
{
	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		aNode->line()->setDir(NODIR,HEADNONE);
		aNode = _lines->getNext();
	}
	NodeFigure *firstNodeFigure = _nodeFigures->getFirst();
	ConnectionInfoTuple *firstTuple = _infoTuples->getFirst();
	if (firstTuple == NIL) return;
	int x = firstTuple->getX();
	int y = firstTuple->getY();
	int where = -1;
	Line *firstLine = NIL;
	aNode = _lines->getFirst();
	while(aNode != NIL) {
		where = aNode->line()->whereToMeet(x,y); 
		if (where == ATBEFORE || where == ATAFTER) {
			firstLine = aNode->line();
			break;
		}
		aNode = _lines->getNext();
	}
	if (firstLine == NIL) return;
	if (where == ATBEFORE) {
		firstLine->setDir(INVERT_DIR,HEADARROW2);	
	} else {
		firstLine->setDir(NORMAL_DIR,HEADARROW2);	
	}

	NodeFigure *nodeFigure = _nodeFigures->getLast();
	ConnectionInfoTuple *aTuple = _infoTuples->getLast();
	if (aTuple == NIL) return;
	x = aTuple->getX();
	y = aTuple->getY();
	where = -1;
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
	if (firstLine == lastLine) {
		lastLine->setDir(BIDIR,HEADARROW2);	
	} else if (where == ATBEFORE) {
		lastLine->setDir(INVERT_DIR,HEADARROW2);	
	} else {
		lastLine->setDir(NORMAL_DIR,HEADARROW2);	
	}
}
