// CollaborationObjectPopup.cpp: implementation of the CollaborationObjectPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "CollaborationObjectPopup.h"
#include "MessageFlowPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CollaborationObjectPopup::CollaborationObjectPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT,"Edit");
    _popup_ptr->AppendMenu(MF_STRING,ID_SELF_DELEGATION_COLLABORATION_OBJECT,"Self Delegation");
}

CollaborationObjectPopup::~CollaborationObjectPopup()
{

}

void CollaborationObjectPopup::changeMenuItemName(char *name)
{
	if (strcmp(name,"Delete") == 0) {
		_popup_ptr->ModifyMenu(1,MF_BYPOSITION,ID_SELF_DELEGATION_DELETE,name);
	} else if (strcmp(name,"Self Delegation") == 0) {
		_popup_ptr->ModifyMenu(1,MF_BYPOSITION,ID_SELF_DELEGATION_COLLABORATION_OBJECT,name);
	}
}

