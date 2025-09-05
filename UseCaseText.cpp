// UseCaseText.cpp: implementation of the UseCaseText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "UseCaseText.h"
#include "UseCase.h"
#include "TextContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(UseCaseText,SlaveryText,1)

UseCaseText::UseCaseText()
: SlaveryText()
{
}

UseCaseText::UseCaseText(COODView *controller,UseCase *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{

}

UseCaseText::~UseCaseText()
{

}

void UseCaseText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);
}

Figure* UseCaseText::born(Figure* ptr)
{
	UseCaseText *copied;
	if (ptr == NIL) {
		copied = new UseCaseText(NIL,NIL,0,0,0);
	} else {
		copied = (UseCaseText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

UnsignedLong* UseCaseText::whoAreYou()
{
	return IAMUSECASETEXT;
}

int UseCaseText::insert(char* keypressed)
{
	int lineDX = SlaveryText::insert(keypressed);
	if (_content->otherLinesMaxWidth() < lineDX) {
		_master->invalidate();
	}
	return lineDX;
}