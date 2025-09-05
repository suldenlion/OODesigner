// MessageTextPopup.cpp: implementation of the MessageTextPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "MessageTextPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MessageTextPopup::MessageTextPopup()
: Popup(NIL)
{
	_popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT,"Edit");
	_arrowPopup = new CMenu();
	_arrowPopup->CreatePopupMenu();
    _arrowPopup->AppendMenu(MF_STRING,ID_INVERT_ARROW_MESSAGE_TEXT,"Invert");
    _arrowPopup->AppendMenu(MF_STRING,ID_SHIFT_ARROW_MESSAGE_TEXT,"Shift");
	_popup_ptr->AppendMenu(MF_POPUP,(unsigned int)_arrowPopup->m_hMenu,"Arrow");
}

MessageTextPopup::~MessageTextPopup()
{
	if (_arrowPopup != NIL) {
		delete _arrowPopup; _arrowPopup = NIL;
	}
}
