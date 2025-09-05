// SequenceMessageText.cpp: implementation of the SequenceMessageText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SequenceMessageText.h"
#include "COODView.h"
#include "SimpleConnection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SequenceMessageText,ConnectionText,1)

SequenceMessageText::SequenceMessageText()
: ConnectionText()
{
	_popup = theAppPtr->theEditPopup;
}

SequenceMessageText::SequenceMessageText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: ConnectionText(controller,connectionPtr,ox,oy,popup)
{
}

SequenceMessageText::~SequenceMessageText()
{
}

void SequenceMessageText::Serialize(CArchive& ar)
{
	ConnectionText::Serialize(ar);
}

UnsignedLong *SequenceMessageText::whoAreYou()
{
	return IAMSEQUENCEMESSAGETEXT; 
}

Figure* SequenceMessageText::born(Figure* ptr)
{
	SequenceMessageText *copied;
	if (ptr == NIL) {
		copied = new SequenceMessageText(NIL,NIL,0,0,NIL);
	} else {
		copied = (SequenceMessageText *)ptr;
	}
	return (ConnectionText::born((Figure *)copied));
}

void SequenceMessageText::epilog(BOOL skipflag)
{
	ConnectionText::epilog(skipflag);
	if (skipflag) return;
	SimpleConnection *connection = (SimpleConnection *)_connectionPtr;
	connection->setDeltaOfTextFromCenter(getX1(),getY1());
}
