// AssociationPopup.cpp: implementation of the AssociationPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "AssociationPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AssociationPopup::AssociationPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CONNECTION_NAME_EDIT,"Name");
    _popup_ptr->AppendMenu(MF_STRING,ID_EDIT_ROLE_NAME,"Role Name");
    _popup_ptr->AppendMenu(MF_STRING,ID_EDIT_MULTIPLICITY,"Multiplicity");
    _popup_ptr->AppendMenu(MF_STRING,ID_EDIT_QUALIFICATION,"Qualification");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_ASSOCIATION_CLASS,"Association Class");
}

AssociationPopup::~AssociationPopup()
{
	// Empty
}

