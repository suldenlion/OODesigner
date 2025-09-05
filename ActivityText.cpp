// ActivityText.cpp: implementation of the ActivityText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ActivityText.h"
#include "TextContent.h"
#include "Activity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ActivityText,SlaveryText,1)

ActivityText::ActivityText()
: SlaveryText()
{

}

ActivityText::ActivityText(COODView *controller,Activity *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{

}

ActivityText::~ActivityText()
{

}

void ActivityText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);
}

Figure* ActivityText::born(Figure* ptr)
{
	ActivityText *copied;
	if (ptr == NIL) {
		copied = new ActivityText(NIL,NIL,0,0,0);
	} else {
		copied = (ActivityText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

UnsignedLong* ActivityText::whoAreYou()
{
	return IAMACTIVITYTEXT;
}

int ActivityText::insert(char* keypressed)
{
	int lineDX = SlaveryText::insert(keypressed);
	if (_content->otherLinesMaxWidth() < lineDX) {
		_master->invalidate();
	}
	return lineDX;
}
