// StateText.cpp: implementation of the StateText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "StateText.h"
#include "State.h"
#include "TextContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(StateText,SlaveryText,1)

StateText::~StateText()
{

}

StateText::StateText()
: SlaveryText()
{
}

StateText::StateText(COODView *controller,State *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{

}

void StateText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);
}

Figure* StateText::born(Figure* ptr)
{
	StateText *copied;
	if (ptr == NIL) {
		copied = new StateText(NIL,NIL,0,0,0);
	} else {
		copied = (StateText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

BOOL StateText::doIHaveToProceed()
{
	if (_whoAmI != IAMSTATENAME) return FALSE;
	if (nOfLines() >= 2) return TRUE;
	return FALSE;
}

UnsignedLong* StateText::whoAreYou()
{
	return IAMSTATETEXT;
}

int StateText::insert(char* keypressed)
{
	int lineDX = SlaveryText::insert(keypressed);
	if (_content->otherLinesMaxWidth() < lineDX) {
		_master->invalidate();
	}
	return lineDX;
}