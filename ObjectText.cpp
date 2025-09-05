// ObjectText.cpp: implementation of the ObjectText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ObjectText.h"
#include "TextContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ObjectText,SlaveryText,1)

ObjectText::~ObjectText()
{

}

ObjectText::ObjectText()
: SlaveryText()
{

}

ObjectText::ObjectText(COODView *controller,EditableFigure *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{
	setUnderlineFont(TRUE);
	setBoldFont(FALSE);
	setMaxLines(3);
}

void ObjectText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);
}

Figure* ObjectText::born(Figure* ptr)
{
	ObjectText *copied;
	if (ptr == NIL) {
		copied = new ObjectText(NIL,NIL,0,0,0);
	} else {
		copied = (ObjectText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

UnsignedLong* ObjectText::whoAreYou()
{
	return IAMOBJECTTEXT;
}

int ObjectText::getName(char *buffer,int bufSize)
{
	*buffer = '\0';
	TextLine * aLine = _content->getFirst();
	int count = 0;
	while (aLine != NIL) {
		if (count == 0) {
			strcpy_s(buffer,BUFSIZ,aLine->ptrAt(0));
			count = strlen(buffer);
		} else {
			strcat_s(buffer,BUFSIZ," ");
			strcat_s(buffer,BUFSIZ,aLine->ptrAt(0));
			count = strlen(buffer);
		}
		aLine = _content->getNext();
	}
	return count;
}
