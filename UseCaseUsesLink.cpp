// UseCaseUsesLink.cpp: implementation of the UseCaseUsesLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "COODView.h"
#include "UseCaseUsesLink.h"
#include "NodeFigureList.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "Line.h"
#include "StaticConnectionText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(UseCaseUsesLink,SimpleConnection,1)

UseCaseUsesLink::UseCaseUsesLink()
: SimpleConnection()
{
}

UseCaseUsesLink::UseCaseUsesLink(COODView *controller,Popup *popup,Line *aLine)
: SimpleConnection(controller,popup,aLine)
{
}

UseCaseUsesLink::~UseCaseUsesLink()
{

}

void UseCaseUsesLink::Serialize(CArchive& ar)
{
	SimpleConnection::Serialize(ar);
}

Figure* UseCaseUsesLink::born(Figure* ptr)
{
	UseCaseUsesLink *copied;
	if (ptr == NIL) {
		copied = new UseCaseUsesLink(NIL,NIL,NIL);
	} else {
		copied = (UseCaseUsesLink *)ptr;
	}
	return (SimpleConnection::born((Figure *)copied));
}

UnsignedLong *UseCaseUsesLink::whoAreYou()
{
	return IAMUSECASEUSESLINK; 
}

BOOL UseCaseUsesLink::setModelSpecificSymbol(NodeFigure *nodeFocus)
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
	setMyText(cx,cy,"<<uses>>");
	return FALSE;
}

void UseCaseUsesLink::setModelSpecificSymbolAll()
{
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW3);
	int cx,cy;
	lastLine->center(cx,cy);
	setMyText(cx,cy,"<<uses>>");
}

