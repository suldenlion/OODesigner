#include "stdafx.h"
#include "resource.h"
/* UseCaseMainPopup.C */

#include "UseCaseMainPopup.h"
// Super Class : Popup

/*oodB%UseCaseMainPopup*** Global Declarations and Stuffs ****/
/*oodE**********************************************************/

UseCaseMainPopup::~UseCaseMainPopup()
{
	// Empty
}

UseCaseMainPopup::UseCaseMainPopup()
: Popup("Main Popup")
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_ACTOR,"Actor");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_USECASE,"Use Case");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_USECASELINK,"Associates");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_USECASEUSESLINK,"Uses");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_USECASEEXTENDSLINK,"Extends");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_SYSTEMBOUNDARY,"System");
	_popup_ptr->AppendMenu(MF_SEPARATOR);
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT_PASTE,"Paste");
}


