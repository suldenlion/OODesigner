// TemplateClassTagText.cpp: implementation of the TemplateClassTagText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "TemplateClassTagText.h"
#include "TemplateClassTag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(TemplateClassTagText,SlaveryText,1)

TemplateClassTagText::TemplateClassTagText()
: SlaveryText()
{
}

TemplateClassTagText::TemplateClassTagText(COODView *controller,TemplateClassTag *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{
	if (controller == NIL) return;
	setMaxLines(1);
	setBoldFont(FALSE);
}

TemplateClassTagText::~TemplateClassTagText()
{
}

void TemplateClassTagText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);   
}

Figure* TemplateClassTagText::born(Figure* ptr)
{
	TemplateClassTagText *copied;
	if (ptr == NIL) {
		copied = new TemplateClassTagText(NIL,NIL,0,0,0);
	} else {
		copied = (TemplateClassTagText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

UnsignedLong* TemplateClassTagText::whoAreYou()
{
	return IAMTEMPLATECLASSTAGTEXT;
}

Figure *TemplateClassTagText::container()
{
	return (Figure *)(((TemplateClassTag *)_master)->classPointer());
}

BOOL TemplateClassTagText::doIHaveToProceed()
{
	return TRUE;
}

void TemplateClassTagText::goUp()
{
	return;
}

