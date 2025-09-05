// SequenceReturnMessage.cpp: implementation of the SequenceReturnMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SequenceReturnMessage.h"
#include "NodeFigureList.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "Line.h"
#include "NodeFigure.h"
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
IMPLEMENT_SERIAL(SequenceReturnMessage,SequenceSyncMessage,1)

SequenceReturnMessage::SequenceReturnMessage()
: SequenceSyncMessage()
{
	_style = DASHED;
}

SequenceReturnMessage::SequenceReturnMessage(COODView *controller,Popup *popup,Line *aLine)
: SequenceSyncMessage(controller,popup,aLine)
{
	_style = DASHED;
}

SequenceReturnMessage::~SequenceReturnMessage()
{

}

void SequenceReturnMessage::Serialize(CArchive& ar)
{
	SequenceSyncMessage::Serialize(ar);
	setStyle(DASHED); // 이 줄은 2005년도에는 없애도록 할 것
}

UnsignedLong *SequenceReturnMessage::whoAreYou()
{
	return IAMRETURNMESSAGE; 
}

Figure* SequenceReturnMessage::born(Figure* ptr)
{
	SequenceReturnMessage *copied;
	if (ptr == NIL) {
		copied = new SequenceReturnMessage(NIL,NIL,NIL);
	} else {
		copied = (SequenceReturnMessage *)ptr;
	}
	return (SequenceSyncMessage::born((Figure *)copied));
}

void SequenceReturnMessage::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	if (_text != NIL) _text->draw(dcp);
	Lines::draw(dcp);
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) return;
	if (_controller->ktgF_connectionDrawing) return;
	if (_controller->ktgF_simpleDrawing) return;
	if (_controller->ktgF_simpleMoving) return;
	LineNode *aNode = _lines->getFirst();
	while (aNode != NIL) {
		Line *aLine = aNode->line();
		int y1 = aLine->getY1();
		int y2 = aLine->getY2();
		if (y1 > y2) {
			_controller->highlight(aLine);
		}
		aNode = _lines->getNext();
	}
}

void SequenceReturnMessage::clear(CDC* dcp)
{
	Lines::clear(dcp);
}

void SequenceReturnMessage::drawing(CDC* dcp,int dx,int dy)
{
	Lines::drawing(dcp,dx,dy);
}

void SequenceReturnMessage::move(CDC* dcp,int dx,int dy)
{
	Lines::move(dcp,dx,dy);
	if (_moveAllFlag) {
		if (_text != NIL) _text->move(dcp,dx,dy);
	}
}

BOOL SequenceReturnMessage::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	int n = _nodeFigures->nOfList();
	if (n < 1) {
		return TRUE;
	} 
	/* 말로는 lastLine이지만 실제 라인은 하나밖에 없다. */
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW2);
	return FALSE;
}

void SequenceReturnMessage::setModelSpecificSymbolAll()
{
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW2);
}

