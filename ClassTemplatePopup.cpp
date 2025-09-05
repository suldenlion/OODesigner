#include "stdafx.h"
#include "resource.h"
#include "KtgMacro.h"
/* ClassTemplatePopup.C */

#include "ClassTemplatePopup.h"
// Super Class : Popup

ClassTemplatePopup::~ClassTemplatePopup()
{
	if (_supressPopup != NIL) {
		delete _supressPopup; _supressPopup = NIL;
	}
}

ClassTemplatePopup::ClassTemplatePopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT,"Edit");
    _popup_ptr->AppendMenu(MF_STRING,ID_CLASSTEMPLATE_SIZE,"Minimize");
	_supressPopup = new CMenu();
	_supressPopup->CreatePopupMenu();
    _supressPopup->AppendMenu(MF_STRING,ID_SUPRESS_DATA_MEMBERS,"Data Members");
    _supressPopup->AppendMenu(MF_STRING,ID_SUPRESS_MEMBER_FUNCTIONS,"Member Functions");
	_popup_ptr->AppendMenu(MF_POPUP,(unsigned int)_supressPopup->m_hMenu,"Supress");

    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_INTERFACE_PORT,"Interface Port");
	_popup_ptr->AppendMenu(MF_STRING,ID_CLASS_PROPERTIES,"Properties");
    _popup_ptr->AppendMenu(MF_STRING,ID_GENERATE_CODE,"Generate Code");
}

void ClassTemplatePopup::changeMenuItemName(char *name)
{
	if (strcmp(name,"Minimize") == 0 ||
		strcmp(name,"Normal Size") == 0) {
		_popup_ptr->ModifyMenu(1,MF_BYPOSITION,ID_CLASSTEMPLATE_SIZE,name);
	}
}

