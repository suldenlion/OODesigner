// LinePopup.cpp: implementation of the LinePopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "KtgMacro.h"

#include "LinePopup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LinePopup::LinePopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_LINE_ARROW,"Arrow");

	_stylePopup = new CMenu();
	_stylePopup->CreatePopupMenu();
    _stylePopup->AppendMenu(MF_STRING,ID_LINE_STYLE_SOLID,"Solid");
    _stylePopup->AppendMenu(MF_STRING,ID_LINE_STYLE_DASH,"Dash");
    _stylePopup->AppendMenu(MF_STRING,ID_LINE_STYLE_DOT,"Dot");
	_popup_ptr->AppendMenu(MF_POPUP,(unsigned int)_stylePopup->m_hMenu,"Style");

	_thicknessPopup = new CMenu();
	_thicknessPopup->CreatePopupMenu();
    _thicknessPopup->AppendMenu(MF_STRING,ID_LINE_THICKNESS_1,"1");
    _thicknessPopup->AppendMenu(MF_STRING,ID_LINE_THICKNESS_2,"2");
    _thicknessPopup->AppendMenu(MF_STRING,ID_LINE_THICKNESS_3,"3");
    _thicknessPopup->AppendMenu(MF_STRING,ID_LINE_THICKNESS_4,"4");
	_popup_ptr->AppendMenu(MF_POPUP,(unsigned int)_thicknessPopup->m_hMenu,"Thickness");
}

LinePopup::~LinePopup()
{
	if (_stylePopup != NIL) {
		delete _stylePopup; _stylePopup = NIL;
	}
	if (_thicknessPopup != NIL) {
		delete _thicknessPopup; _thicknessPopup = NIL;
	}
}
