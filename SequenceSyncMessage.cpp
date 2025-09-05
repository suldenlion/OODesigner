// SequenceSyncMessage.cpp: implementation of the SequenceSyncMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SequenceSyncMessage.h"
#include "NodeFigureList.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "Line.h"
#include "SequenceMessageText.h"
#include "NodeFigure.h"
#include "COODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SequenceSyncMessage,SimpleConnection,1)

SequenceSyncMessage::SequenceSyncMessage()
: SimpleConnection()
{
	_popup = theAppPtr->theMessagePopup;
}

SequenceSyncMessage::SequenceSyncMessage(COODView *controller,Popup *popup,Line *aLine)
: SimpleConnection(controller,popup,aLine)
{
}

SequenceSyncMessage::~SequenceSyncMessage()
{

}

void SequenceSyncMessage::Serialize(CArchive& ar)
{
	SimpleConnection::Serialize(ar);
}

Figure* SequenceSyncMessage::born(Figure* ptr)
{
	SequenceSyncMessage *copied;
	if (ptr == NIL) {
		copied = new SequenceSyncMessage(NIL,NIL,NIL);
	} else {
		copied = (SequenceSyncMessage *)ptr;
	}
	return (SimpleConnection::born((Figure *)copied));
}

UnsignedLong *SequenceSyncMessage::whoAreYou()
{
	return IAMSYNCMESSAGE; 
}

BOOL SequenceSyncMessage::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	int n = _nodeFigures->nOfList();
	if (n < 1) {
		return TRUE;
	} 
	/* 말로는 lastLine이지만 실제 라인은 하나밖에 없다. */
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW1);
	return FALSE;
}

void SequenceSyncMessage::tailorEndLinesAll()
{
	NodeFigure *majorNode = _nodeFigures->getFirst();
	Line *startLine = _lines->getFirst()->line();
	_controller->clear(startLine);
	majorNode->adjustLine(startLine,TRUE);
	NodeFigure *lastNode = _nodeFigures->getLast();
	Line *lastLine = _lines->getLast()->line();
	if (lastNode->adjustLine(lastLine,FALSE)) {
		// obsolete case : 실제 이 경우는 없을 것이다.
		lastLine->setXY2(lastLine->getX1(),lastLine->getY1());
	}
	return;
}

void SequenceSyncMessage::tailorEndLines(NodeFigure *lastNode)
{
	NodeFigure *majorNode = _nodeFigures->getFirst();
	Line *startLine = _activeLines->getFirst()->line();
	majorNode->adjustLine(startLine,TRUE);
	Line *lastLine = _activeLines->getLast()->line();
	if (lastNode->adjustLine(lastLine,FALSE)) {
		// obsolete case : 실제 이 경우는 없을 것이다.
		lastLine->setXY2(lastLine->getX1(),lastLine->getY1());
	}
}

void SequenceSyncMessage::setModelSpecificSymbolAll()
{
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW1);
}

SequenceMessageText* SequenceSyncMessage::selectOrCreateText()
{
	if (_text != NIL) {
		_focus = _text;
		return (SequenceMessageText*)_text;
	}
	_text = new SequenceMessageText(_controller,this,0,0,theAppPtr->theEditPopup);
	setTextPosition(-20,20,-10);
	setDeltaOfTextFromCenter(_text->getX1(),_text->getY1());
	return (SequenceMessageText*)_text;
}

void SequenceSyncMessage::epilog(BOOL skipflag)
{
	SimpleConnection::epilog(skipflag);
	if (skipflag) return;
	if (_text != NIL) {
		Line *lastLine = _lines->getLast()->line();
		int cx,cy;
		lastLine->center(cx,cy);
		setMyText(cx,cy,NIL);
	}
	makeRegion(_controller->canvasRgn());
}

void SequenceSyncMessage::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	LineNode *aNode = _lines->getFirst();
	while (aNode != NIL) {
		Line *aLine = aNode->line();
		aLine->setBrushIndex(BLACK_BRUSH);
		aNode = _lines->getNext();
	}
	SimpleConnection::draw(dcp);
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) return;
	if (_controller->ktgF_connectionDrawing) return;
	if (_controller->ktgF_simpleDrawing) return;
	if (_controller->ktgF_simpleMoving) return;
	aNode = _lines->getFirst();
	while (aNode != NIL) {
		Line *aLine = aNode->line();
		int y1 = aLine->getY1();
		int y2 = aLine->getY2();
		if (y1 > y2) { 
			aLine->setBrushIndex(RED_BRUSH);
			_controller->highlight(aLine);
		} else {
			aLine->setBrushIndex(BLACK_BRUSH);
		}
		aNode = _lines->getNext();
	}
}

