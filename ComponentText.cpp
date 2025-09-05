// ComponentText.cpp: implementation of the ComponentText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ComponentText.h"
#include "ComponentTemplate.h"
#include "TextContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ComponentText,SlaveryText,1)

ComponentText::ComponentText()
: SlaveryText()
{
}

ComponentText::ComponentText(COODView *controller,ComponentTemplate *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{
	setBoldFont(FALSE);
}

ComponentText::~ComponentText()
{

}

void ComponentText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);
}

int ComponentText::delEmptyLines()
{
	// don't delete on this case
	return 0;
}

Figure* ComponentText::born(Figure* ptr)
{
	ComponentText *copied;
	if (ptr == NIL) {
		copied = new ComponentText(NIL,NIL,0,0,0);
	} else {
		copied = (ComponentText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

UnsignedLong* ComponentText::whoAreYou()
{
	return IAMCOMPONENTTEXT;
}

void ComponentText::goNextLine()
{
	if (_maxLines > 0 && textHeight() >= _maxLines) {
		return;
	}
	Text::goNextLine();
	if (textHeight() > DEFAULT_NO_OF_LINES) {
		_master->modifyHeight(deltaV(),_whoAmI);
	}
	int lineDX = _content->otherLinesMaxWidth();
	_master->modifyWidthMinus(lineDX,_whoAmI);
}

BOOL ComponentText::delLine()
{
	if (textHeight() == 1 && _content->valueAt(0,0) == '\0') {
		 return TRUE;
	}
	if (Text::delLine()) {
		_master->modifyWidthMinus(0,_whoAmI);
		return TRUE;
	}
	if (textHeight() >= DEFAULT_NO_OF_LINES) {
		_master->modifyHeight(-deltaV(),_whoAmI);
	}
	int lineDX = _content->otherLinesMaxWidth();
	_master->modifyWidthMinus(lineDX,_whoAmI);
	return FALSE;
}
