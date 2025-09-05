// TriggerText.cpp: implementation of the TriggerText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "TriggerText.h"
#include "COODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(TriggerText,ConnectionText,1)

TriggerText::TriggerText()
: ConnectionText()
{
	_popup = theAppPtr->theEditPopup;
}

TriggerText::TriggerText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: ConnectionText(controller,connectionPtr,ox,oy,popup)
{
}

TriggerText::~TriggerText()
{
}

void TriggerText::Serialize(CArchive& ar)
{
	ConnectionText::Serialize(ar);
}

UnsignedLong *TriggerText::whoAreYou()
{
	return IAMTRIGGERTEXT;  
}

Figure* TriggerText::born(Figure* ptr)
{
	TriggerText *copied;
	if (ptr == NIL) {
		copied = new TriggerText(NIL,NIL,0,0,NIL);
	} else {
		copied = (TriggerText *)ptr;
	}
	return (ConnectionText::born((Figure *)copied));
}
