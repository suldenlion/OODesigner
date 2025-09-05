// Transition.cpp: implementation of the Transition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Transition.h"
#include "ConnectionInfoTuple.h"
#include "Line.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "ConnectionText.h"
#include "EventText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Transition,Connection,1)

Transition::Transition()
: Connection()
{
	_popup = theAppPtr->theTransitionPopup;
}

Transition::Transition(COODView *controller,Popup *popup,Line *aLine)
: Connection(controller,popup,aLine)
{
}

Transition::~Transition()
{
}

void Transition::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
}

Figure* Transition::born(Figure* ptr)
{
	Transition *copied;
	if (ptr == NIL) {
		copied = new Transition(NIL,NIL,NIL);
	} else {
		copied = (Transition *)ptr;
	}
	return (Connection::born((Figure *)copied));
}


UnsignedLong *Transition::whoAreYou()
{
	return IAMTRANSITION; 
}

BOOL Transition::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	int n = _nodeFigures->nOfList();
	if (n < 1) {
		return TRUE;
	} 
	if (n == 1) {
		Line *firstLine = _lines->getFirst()->line();
		int x1 = firstLine->getX1();
		int y1 = firstLine->getY1();
		ConnectionInfoTuple *aTuple = 
			new ConnectionInfoTuple(_nodeFigures->getFirst(),x1,y1);
		_infoTuples->insert(aTuple);
	}
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW2);
	int x = lastLine->getX2();
	int y = lastLine->getY2();
	ConnectionInfoTuple *aTuple = 
		new ConnectionInfoTuple(nodeFocus,x,y);
	_infoTuples->insert(aTuple);
	return FALSE;
}

void Transition::setModelSpecificSymbolAll()
{
	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		aNode->line()->setDir(NODIR,HEADNONE);
		aNode = _lines->getNext();
	}
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
}

EventText* Transition::selectOrCreateText()
{
	if (_text != NIL) {
		_focus = _text;
		return (EventText *)_text;
	}
	_text = new EventText(_controller,this,0,0,theAppPtr->theEditPopup);
	setTextPosition(-30,20,-10);
	return (EventText *)_text;
}
