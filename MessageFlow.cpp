// MessageFlow.cpp: implementation of the MessageFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "MessageFlow.h"
#include "ConnectionInfoTuple.h"
#include "Line.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "ConnectionText.h"
#include "NodeFigure.h"
#include "MessageText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(MessageFlow,Connection,1)

MessageFlow::MessageFlow()
: Connection()
{
	_popup = theAppPtr->theMessageFlowPopup;
}

MessageFlow::MessageFlow(COODView *controller,Popup *popup,Line *aLine)
: Connection(controller,popup,aLine)
{
	if (controller == NIL) return;
	_text = new MessageText(controller,this,0,0,theAppPtr->theMessageTextPopup);
}

MessageFlow::~MessageFlow()
{
}

void MessageFlow::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
}

MessageText* MessageFlow::selectOrCreateText()
{
	if (_text != NIL) {
		_focus = _text;
		return (MessageText *)_text;
	}
	_text = new MessageText(_controller,this,0,0,theAppPtr->theMessageTextPopup);
	setTextPosition(-30,20,-10);
	return (MessageText *)_text;
}


Figure* MessageFlow::born(Figure* ptr)
{
	MessageFlow *copied;
	if (ptr == NIL) {
		copied = new MessageFlow(NIL,NIL,NIL);
	} else {
		copied = (MessageFlow *)ptr;
	}
	return (Connection::born((Figure *)copied));
}

UnsignedLong *MessageFlow::whoAreYou()
{
	return IAMMESSAGEFLOW; 
}

BOOL MessageFlow::setModelSpecificSymbol(NodeFigure *nodeFocus)
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
		ConnectionInfoTuple *aTuple = new ConnectionInfoTuple(firstNode,x1,y1);
		_infoTuples->insert(aTuple);
	}
	Line *lastLine = _lines->getLast()->line();
	int x = lastLine->getX2();
	int y = lastLine->getY2();
	ConnectionInfoTuple *aTuple = 
		new ConnectionInfoTuple(nodeFocus,x,y);
	_infoTuples->insert(aTuple);

	return FALSE;
}

void MessageFlow::setTextPosition(int d1,int d2,int d3)
{
	Connection::setTextPosition(d1,d2,d3);
	LineNode *aNode = _lines->getFirst();
	if (aNode == NIL) return;
	Line *aLine = aNode->line();
	if (aLine->orient() == EAST) {
		((MessageText *)_text)->setArrowAt(ARROW_AT_BOTTOM);
	} else {
		((MessageText *)_text)->setArrowAt(ARROW_AT_LEFT);
	}
}

