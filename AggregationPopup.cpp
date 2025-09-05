#include "stdafx.h"
#include "resource.h"
/* AggregationPopup.C */

#include "AggregationPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

AggregationPopup::~AggregationPopup()
{
	// Empty
}

AggregationPopup::AggregationPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CONNECTION_NAME_EDIT,"Name");
    _popup_ptr->AppendMenu(MF_STRING,ID_EDIT_ROLE_NAME,"Role Name");
    _popup_ptr->AppendMenu(MF_STRING,ID_EDIT_MULTIPLICITY,"Multiplicity");
}


