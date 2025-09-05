// PackageText.cpp: implementation of the PackageText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "PackageText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(PackageText,SlaveryText,1)

PackageText::PackageText()
: SlaveryText()
{

}

PackageText::PackageText(COODView *controller,PackageTemplate *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{
	setMaxLines(3);
}

PackageText::~PackageText()
{

}

void PackageText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);
}

Figure* PackageText::born(Figure* ptr)
{
	PackageText *copied;
	if (ptr == NIL) {
		copied = new PackageText(NIL,NIL,0,0,0);
	} else {
		copied = (PackageText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

UnsignedLong* PackageText::whoAreYou()
{
	return IAMPACKAGETEXT;
}
