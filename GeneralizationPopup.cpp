#include "stdafx.h"
#include "resource.h"
/* GeneralizationPopup.C */

#include "GeneralizationPopup.h"
#include "KtgMacro.h"
// Super Class : Popup

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

GeneralizationPopup::~GeneralizationPopup()
{
	// Empty
}

GeneralizationPopup::GeneralizationPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CONNECTION_NAME_EDIT,"Name");
}


