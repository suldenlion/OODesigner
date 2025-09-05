// StaticConnectionText.cpp: implementation of the StaticConnectionText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "StaticConnectionText.h"
#include "SimpleConnection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(StaticConnectionText,ConnectionText,1)

StaticConnectionText::StaticConnectionText()
: ConnectionText()
{
}

StaticConnectionText::StaticConnectionText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: ConnectionText(controller,connectionPtr,ox,oy,popup)
{

}

StaticConnectionText::~StaticConnectionText()
{

}

void StaticConnectionText::Serialize(CArchive& ar)
{
	ConnectionText::Serialize(ar);
}

UnsignedLong *StaticConnectionText::whoAreYou()
{
	return IAMSTATICCONNECTIONTEXT; 
}

Figure* StaticConnectionText::born(Figure* ptr)
{
	StaticConnectionText *copied;
	if (ptr == NIL) {
		copied = new StaticConnectionText(NIL,NIL,0,0,NIL);
	} else {
		copied = (StaticConnectionText *)ptr;
	}
	return (ConnectionText::born((Figure *)copied));
}

BOOL StaticConnectionText::isEditable()
{
	return FALSE;
}

void StaticConnectionText::epilog(BOOL skipflag)
{
	ConnectionText::epilog(skipflag);
	// Connection 객체로 다시 연결한다.
	if (skipflag) return;
	((SimpleConnection *)_connectionPtr)->setDeltaOfTextFromCenter(_x1.get(),_y1.get());
}
