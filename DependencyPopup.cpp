#include "stdafx.h"
#include "resource.h"
/* DependencyPopup.C */

#include "DependencyPopup.h"
#include "KtgMacro.h"
// Super Class : Popup

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

DependencyPopup::~DependencyPopup()
{
	// Empty
}

DependencyPopup::DependencyPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CONNECTION_NAME_EDIT,"Name");
    _popup_ptr->AppendMenu(MF_STRING,ID_EDIT_ROLE_NAME,"Role Name");
}


