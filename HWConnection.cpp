// HWConnection.cpp: implementation of the HWConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "HWConnection.h"
#include "ConnectionInfoTuple.h"
#include "Line.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "HWConnectionText.h"
#include "NodeFigure.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(HWConnection,Connection,1)

HWConnection::HWConnection()
: Connection()
{
	_popup = theAppPtr->theHWConnectionPopup;
}

HWConnection::HWConnection(COODView *controller,Popup *popup,Line *aLine)
: Connection(controller,popup,aLine)
{
	if (controller == NIL) return;
	_text = new HWConnectionText(controller,this,0,0,theAppPtr->theEditPopup);
}

HWConnection::~HWConnection()
{
}

void HWConnection::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
}

HWConnectionText* HWConnection::selectOrCreateText()
{
	if (_text != NIL) {
		_focus = _text;
		return (HWConnectionText *)_text;
	}
	_text = new HWConnectionText(_controller,this,0,0,theAppPtr->theEditPopup);
	setTextPosition(-30,20,-10);
	return (HWConnectionText *)_text;
}


Figure* HWConnection::born(Figure* ptr)
{
	HWConnection *copied;
	if (ptr == NIL) {
		copied = new HWConnection(NIL,NIL,NIL);
	} else {
		copied = (HWConnection *)ptr;
	}
	return (Connection::born((Figure *)copied));
}

UnsignedLong *HWConnection::whoAreYou()
{
	return IAMHWCONNECTION; 
}

BOOL HWConnection::setModelSpecificSymbol(NodeFigure *nodeFocus)
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

