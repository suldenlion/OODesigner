#include "stdafx.h"
#include "resource.h"
/* StateMainPopup.C */

#include "StateMainPopup.h"
// Super Class : Popup

/*oodB%StateMainPopup*** Global Declarations and Stuffs ****/
/*oodE**********************************************************/

StateMainPopup::~StateMainPopup()
{
	// Empty
}

StateMainPopup::StateMainPopup()
: Popup("Main Popup")
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_STATE,"State");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_TRANSITION,"Transition");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_INITIAL_STATE,"Initial State");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_FINAL_STATE,"Final State");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_WIDE_STATE,"Wide State");
	_popup_ptr->AppendMenu(MF_SEPARATOR);
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT_PASTE,"Paste");
}


