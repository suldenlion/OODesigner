// NoteText.cpp: implementation of the NoteText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "NoteText.h"
#include "Note.h"
#include "TextContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(NoteText,SlaveryText,1)

NoteText::NoteText()
: SlaveryText()
{

}

NoteText::NoteText(COODView *controller,Note *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{
	setBoldFont(FALSE);
}

NoteText::~NoteText()
{

}

void NoteText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);
}

Figure* NoteText::born(Figure* ptr)
{
	NoteText *copied;
	if (ptr == NIL) {
		copied = new NoteText(NIL,NIL,0,0,0);
	} else {
		copied = (NoteText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

UnsignedLong* NoteText::whoAreYou()
{
	return IAMNOTETEXT;
}

int NoteText::insert(char* keypressed)
{
	int lineDX = SlaveryText::insert(keypressed);
	if (_content->otherLinesMaxWidth() < lineDX) {
		_master->invalidate();
	}
	return lineDX;
}