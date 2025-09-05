// UseCaseExtendsLink.cpp: implementation of the UseCaseExtendsLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "UseCaseExtendsLink.h"
#include "NodeFigureList.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(UseCaseExtendsLink,SimpleConnection,1)

UseCaseExtendsLink::UseCaseExtendsLink()
: SimpleConnection()
{

}

UseCaseExtendsLink::UseCaseExtendsLink(COODView *controller,Popup *popup,Line *aLine)
: SimpleConnection(controller,popup,aLine)
{

}

UseCaseExtendsLink::~UseCaseExtendsLink()
{

}

void UseCaseExtendsLink::Serialize(CArchive& ar)
{
	SimpleConnection::Serialize(ar);
}


Figure* UseCaseExtendsLink::born(Figure* ptr)
{
	UseCaseExtendsLink *copied;
	if (ptr == NIL) {
		copied = new UseCaseExtendsLink(NIL,NIL,NIL);
	} else {
		copied = (UseCaseExtendsLink *)ptr;
	}
	return (SimpleConnection::born((Figure *)copied));
}

UnsignedLong *UseCaseExtendsLink::whoAreYou()
{
	return IAMUSECASEEXTENDSLINK; 
}

BOOL UseCaseExtendsLink::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	int n = _nodeFigures->nOfList();
	if (n < 1) {
		return TRUE;
	} 
	/* 말로는 lastLine이지만 실제 라인은 하나밖에 없다. */
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW3);
	int cx,cy;
	lastLine->center(cx,cy);
	setMyText(cx,cy,"<<extends>>");
	return FALSE;
}

void UseCaseExtendsLink::setModelSpecificSymbolAll()
{
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW3);
	int cx,cy;
	lastLine->center(cx,cy);
	setMyText(cx,cy,"<<extends>>");
}

