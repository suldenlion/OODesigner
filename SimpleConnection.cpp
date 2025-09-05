// SimpleConnection.cpp: implementation of the SimpleConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SimpleConnection.h"
#include "CITList.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "Line.h"
#include "ConnectionInfoTuple.h"
#include "NodeFigure.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "ConnectionText.h"
#include "StaticConnectionText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SimpleConnection,Connection,1)

SimpleConnection::SimpleConnection()
: Connection()
{
	_dxOfTextFromCenter = INIT_DX_OF_TEXT_FROM_CENTER;
	_dyOfTextFromCenter = INIT_DY_OF_TEXT_FROM_CENTER;
}

SimpleConnection::SimpleConnection(COODView *controller,Popup* popup,Line *aLine)
: Connection(controller,popup,aLine)
{
	/* SimpleConnection에서는 _infoTuple을 이용할 일이 없다. */
	_type = ORDINARY;
	if (_infoTuples != NIL) {
		delete _infoTuples;	_infoTuples = NIL;
	}

	_dxOfTextFromCenter = INIT_DX_OF_TEXT_FROM_CENTER;
	_dyOfTextFromCenter = INIT_DY_OF_TEXT_FROM_CENTER;
}

SimpleConnection::~SimpleConnection()
{

}

void SimpleConnection::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _dxOfTextFromCenter << (LONG) _dyOfTextFromCenter;
	} else {
		ar >> (LONG&) _dxOfTextFromCenter >> (LONG&) _dyOfTextFromCenter;
	}
}

BOOL SimpleConnection::wantToResize(int &x,int &y)
{
	return Lines::wantToResize(x,y);
}

void SimpleConnection::setDeltaOfTextFromCenter(int x1OfText,int y1OfText)
{
	LineNode *aNode = _lines->getFirst();
	int cx,cy;
	aNode->line()->center(cx,cy);
	_dxOfTextFromCenter = x1OfText - cx;
	_dyOfTextFromCenter = y1OfText - cy;
}

void SimpleConnection::epilog(BOOL skipflag)
{
	if (_moveAllFlag) return;
	if (skipflag) return;
	tailorEndLinesAll();
	setModelSpecificSymbolAll();
	NodeFigure* nodeFigure = _nodeFigures->getFirst();
	while (nodeFigure != NIL) {
		_controller->draw(nodeFigure);
		nodeFigure = _nodeFigures->getNext();
	}
	makeRegion(_controller->canvasRgn());
}

void SimpleConnection::setModelSpecificSymbolAll()
{
	return;
}

void SimpleConnection::tailorEndLinesAll()
{
	return;
}

void SimpleConnection::tailorEndLines(NodeFigure *lastNode)
{
	return;
}

void SimpleConnection::letsGo(NodeFigure *leader)
{
	if (_moveAllFlag) return;

	_focusNode = NIL;
	_focus = NIL;
	resetHotXY();
	_nOfDeltaList = 0;

	LineNode *tmp = _lines->getFirst();
	if (tmp == NIL) return;
	Line *line = tmp->line();
	int lx1,ly1,lx2,ly2;
	lx1 = line->_x1.get();
	ly1 = line->_y1.get();
	lx2 = line->_x2.get();
	ly2 = line->_y2.get();
	if (_nodeFigures->getFirst() == leader) {
		line->wantToResizeExact(lx1,ly1);
		_deltaList[_nOfDeltaList].x = lx1 - leader->shape()->getX1();
		_deltaList[_nOfDeltaList].y = ly1 - leader->shape()->getY1();
		_nOfDeltaList++;
	} else {
		line->wantToResizeExact(lx2,ly2);
		_deltaList[_nOfDeltaList].x = lx2 - leader->shape()->getX1();
		_deltaList[_nOfDeltaList].y = ly2 - leader->shape()->getY1();
		_nOfDeltaList++;
	}
}

Figure* SimpleConnection::born(Figure* ptr)
{
	SimpleConnection *copied;
	if (ptr == NIL) {
		copied = new SimpleConnection(NIL,NIL,NIL);
	} else {
		copied = (SimpleConnection *)ptr;
	}
	copied->_nodeFigures = new NodeFigureList();
	copied->_activeLines = new LineNodeList();
	if (_text != NIL) {
		copied->_text = (ConnectionText *)_text->born();
		copied->_text->setConnectionPtr(copied);
	}
	copied->_dxOfTextFromCenter = _dxOfTextFromCenter;
	copied->_dyOfTextFromCenter = _dyOfTextFromCenter;
	if (_symbol != NIL) {
		copied->_symbol = (TwoPointFigure *)_symbol->born();
	}
	return(Lines::born((Figure *)copied));
}

BOOL SimpleConnection::wantToMove(int,int)
{
	return FALSE;
}

void SimpleConnection::clearSymbolIfFirstLine()
{
	return;
}

void SimpleConnection::resizeProlog(NodeFigure* nodeFigure)
{
}

void SimpleConnection::setMyText(int cx,int cy,char *fixedString)
{
	if (_text == NIL) {
		_text = new StaticConnectionText(_controller,this,
										 cx+_dxOfTextFromCenter,
										 cy+_dyOfTextFromCenter,
										 NIL);
		_text->setString(fixedString);
	} else {
		_controller->clear(_text);
		_text->recalcCoordFromXY1(cx+_dxOfTextFromCenter,
								  cy+_dyOfTextFromCenter);
	}
}

NodeFigure *SimpleConnection::getTargetNodeForResizing()
{
	Line *aLine = _lines->getLast()->line();
	if (aLine == NIL) return NIL;
	if (&(aLine->_x1) == aLine->hotX() &&
		&(aLine->_y1) == aLine->hotY()) {
		return _nodeFigures->getFirst();
	} else if (&(aLine->_x2) == aLine->hotX() &&
		&(aLine->_y2) == aLine->hotY()) {
		return _nodeFigures->getLast();
	}
	return NIL;
}


