// UseCaseLink.cpp: implementation of the UseCaseLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "UseCaseLink.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(UseCaseLink,SimpleConnection,1)

UseCaseLink::UseCaseLink()
: SimpleConnection()
{
}

UseCaseLink::UseCaseLink(COODView *controller,Popup *popup,Line *aLine)
: SimpleConnection(controller,popup,aLine)
{

}

void UseCaseLink::Serialize(CArchive& ar)
{
	SimpleConnection::Serialize(ar);
}

UseCaseLink::~UseCaseLink()
{

}

Figure* UseCaseLink::born(Figure* ptr)
{
	UseCaseLink *copied;
	if (ptr == NIL) {
		copied = new UseCaseLink(NIL,NIL,NIL);
	} else {
		copied = (UseCaseLink *)ptr;
	}
	return (SimpleConnection::born((Figure *)copied));
}

UnsignedLong *UseCaseLink::whoAreYou()
{
	return IAMUSECASELINK; 
}
