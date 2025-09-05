// CollaborationMainPopup.cpp: implementation of the CollaborationMainPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "resource.h"
#include "CollaborationMainPopup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CollaborationMainPopup::~CollaborationMainPopup()
{
	// Empty
}

CollaborationMainPopup::CollaborationMainPopup()
: Popup("Main Popup")
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_COLLABORATION_OBJECT,"Object");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_COLLABORATION_MULTI_OBJECT,"Multi Object");
	_popup_ptr->AppendMenu(MF_STRING,ID_CREATE_MESSAGE_FLOW,"Message Flow");
	_popup_ptr->AppendMenu(MF_SEPARATOR);
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT_PASTE,"Paste");
}
