// FontInfo.cpp: implementation of the FontInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "FontInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(FontInfo,CObject,1)

FontInfo::FontInfo()
: CObject()
{
	size = theAppPtr->currentFontSize;
	weight = theAppPtr->currentFontWeight;
	color = theAppPtr->currentFontColor;
	faceName = theAppPtr->currentFontFaceName;
	styleName = theAppPtr->currentFontStyleName;
	boldFlag = theAppPtr->currentFontBoldFlag;
	italicFlag = theAppPtr->currentFontItalicFlag;
	strikeOutFlag = theAppPtr->currentFontStrikeOutFlag;
	underlineFlag = theAppPtr->currentFontUnderlineFlag;
}

void FontInfo::resetFontInfo()
{
	size = theAppPtr->currentFontSize;
	weight = theAppPtr->currentFontWeight;
	color = theAppPtr->currentFontColor;
	faceName = theAppPtr->currentFontFaceName;
	styleName = theAppPtr->currentFontStyleName;
	boldFlag = theAppPtr->currentFontBoldFlag;
	italicFlag = theAppPtr->currentFontItalicFlag;
	strikeOutFlag = theAppPtr->currentFontStrikeOutFlag;
	underlineFlag = theAppPtr->currentFontUnderlineFlag;
}

FontInfo::~FontInfo()
{
	// empty
}

void FontInfo::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << faceName << styleName;
		ar << (LONG) size << (LONG) weight;
		ar << (LONG) color;
		ar << (BYTE) boldFlag << (BYTE) italicFlag;
		ar << (BYTE) strikeOutFlag << (BYTE) underlineFlag;
	} else {
		ar >> faceName >> styleName;
		ar >> (LONG&) size >> (LONG&) weight;
		ar >> (LONG&) color;
		ar >> (BYTE&) boldFlag >> (BYTE&) italicFlag;
		ar >> (BYTE&) strikeOutFlag >> (BYTE&) underlineFlag;
	}
}

void FontInfo::copy(FontInfo *from)
{
	size = from->size;
	weight = from->weight;
	color = from->color;
	faceName = from->faceName;
	styleName = from->styleName;
	boldFlag = from->boldFlag;
	italicFlag = from->italicFlag;
	strikeOutFlag = from->strikeOutFlag;
	underlineFlag = from->underlineFlag;
}

void FontInfo::setFontInfo(CFontDialog *fontDlg)
{
	size = fontDlg->GetSize()/10;
	weight = fontDlg->GetWeight();
	color = fontDlg->GetColor();
	faceName = fontDlg->GetFaceName();
	if (faceName.IsEmpty()) faceName = DEFAULT_FACE_NAME;
	styleName = fontDlg->GetStyleName();
	boldFlag = fontDlg->IsBold();
	italicFlag = fontDlg->IsItalic();
	strikeOutFlag = fontDlg->IsStrikeOut();
	underlineFlag = fontDlg->IsUnderline();

	theAppPtr->currentFontSize = size;
	theAppPtr->currentFontWeight = weight;
	theAppPtr->currentFontColor = color;
	theAppPtr->currentFontFaceName = faceName;
	theAppPtr->currentFontStyleName = styleName;
	theAppPtr->currentFontBoldFlag = boldFlag;
	theAppPtr->currentFontItalicFlag = italicFlag;
	theAppPtr->currentFontStrikeOutFlag = strikeOutFlag;
	theAppPtr->currentFontUnderlineFlag = underlineFlag;
}