#include "stdafx.h"
#include "resource.h"
/* ActivityMainPopup.C */

#include "ActivityMainPopup.h"
// Super Class : Popup

ActivityMainPopup::~ActivityMainPopup()
{
	// Empty
}

ActivityMainPopup::ActivityMainPopup()
: Popup("Main Popup")
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_ACTIVITY,"Activity");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_TRIGGER,"Trigger");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_SYNCHRONIZATION_BAR,"Sync Bar");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_BEGIN_ACTIVITY,"Begin");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_END_ACTIVITY,"End");
	_popup_ptr->AppendMenu(MF_SEPARATOR);
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT_PASTE,"Paste");
}


