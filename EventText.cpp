// EventText.cpp: implementation of the EventText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "EventText.h"
#include "COODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(EventText,ConnectionText,1)

EventText::EventText()
: ConnectionText()
{
	_popup = theAppPtr->theEditPopup;
}

EventText::EventText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: ConnectionText(controller,connectionPtr,ox,oy,popup)
{
}

EventText::~EventText()
{
}

void EventText::Serialize(CArchive& ar)
{
	ConnectionText::Serialize(ar);
}

UnsignedLong *EventText::whoAreYou()
{
	return IAMEVENTTEXT; 
}

Figure* EventText::born(Figure* ptr)
{
	EventText *copied;
	if (ptr == NIL) {
		copied = new EventText(NIL,NIL,0,0,NIL);
	} else {
		copied = (EventText *)ptr;
	}
	return (ConnectionText::born((Figure *)copied));
}


