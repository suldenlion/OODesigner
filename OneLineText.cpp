// OneLineText.cpp: implementation of the OneLineText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "OneLineText.h"
#include "Connection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(OneLineText,ConnectionText,1)

OneLineText::OneLineText()
: ConnectionText()
{
}

OneLineText::OneLineText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: ConnectionText(controller,connectionPtr,ox,oy,popup)
{
}

OneLineText::~OneLineText()
{

}

void OneLineText::Serialize(CArchive& ar)
{
	ConnectionText::Serialize(ar);
}

Figure* OneLineText::born(Figure* ptr)
{
	OneLineText *copied;
	if (ptr == NIL) {
		copied = new OneLineText(NIL,NIL,0,0,NIL);
	} else {
		copied = (OneLineText *)ptr;
	}
	return (ConnectionText::born((Figure *)copied));
}

UnsignedLong *OneLineText::whoAreYou()
{
	return IAMONELINETEXT;
}

void OneLineText::disconnectFromContainer()
{
	if (_connectionPtr == NIL) return;
	_connectionPtr->removeFromTupleList(this);
	_connectionPtr = NIL;
	return;
}

