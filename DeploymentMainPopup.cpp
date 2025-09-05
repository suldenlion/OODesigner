#include "stdafx.h"
#include "resource.h"
/* DeploymentMainPopup.C */

#include "DeploymentMainPopup.h"
// Super Class : Popup

DeploymentMainPopup::~DeploymentMainPopup()
{
	// Empty
}

DeploymentMainPopup::DeploymentMainPopup()
: Popup("Main Popup")
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_HARDWARE_NODE,"H/W Node");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_COMPONENT_TEMPLATE,"Component");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_HWCONNECTION,"H/W Connection");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_COMMUNICATION,"Communication");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_DEPENDENCY,"Dependency");
	_popup_ptr->AppendMenu(MF_SEPARATOR);
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT_PASTE,"Paste");
}


