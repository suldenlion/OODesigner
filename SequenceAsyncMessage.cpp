// SequenceAsyncMessage.cpp: implementation of the SequenceAsyncMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SequenceAsyncMessage.h"
#include "NodeFigureList.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "Line.h"
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
IMPLEMENT_SERIAL(SequenceAsyncMessage,SequenceSyncMessage,1)

SequenceAsyncMessage::SequenceAsyncMessage()
: SequenceSyncMessage()
{
}

SequenceAsyncMessage::SequenceAsyncMessage(COODView *controller,Popup *popup,Line *aLine)
: SequenceSyncMessage(controller,popup,aLine)
{
}

SequenceAsyncMessage::~SequenceAsyncMessage()
{

}

void SequenceAsyncMessage::Serialize(CArchive& ar)
{
	SequenceSyncMessage::Serialize(ar);
}

UnsignedLong *SequenceAsyncMessage::whoAreYou()
{
	return IAMASYNCMESSAGE; 
}

Figure* SequenceAsyncMessage::born(Figure* ptr)
{
	SequenceAsyncMessage *copied;
	if (ptr == NIL) {
		copied = new SequenceAsyncMessage(NIL,NIL,NIL);
	} else {
		copied = (SequenceAsyncMessage *)ptr;
	}
	return (SequenceSyncMessage::born((Figure *)copied));
}

BOOL SequenceAsyncMessage::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	int n = _nodeFigures->nOfList();
	if (n < 1) {
		return TRUE;
	} 
	/* 말로는 lastLine이지만 실제 라인은 하나밖에 없다. */
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW4);
	return FALSE;
}

void SequenceAsyncMessage::setModelSpecificSymbolAll()
{
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW4);
}

