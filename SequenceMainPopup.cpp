// SequenceMainPopup.cpp: implementation of the SequenceMainPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "resource.h"
#include "SequenceMainPopup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SequenceMainPopup::SequenceMainPopup()
: Popup("Main Popup")
{
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_SEQUENCE_OBJECT,"Object");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_SYNC_MESSAGE,"Sync Message");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_ASYNC_MESSAGE,"Async Message");
    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_RETURN_MESSAGE,"Return Arrow");
	_popup_ptr->AppendMenu(MF_SEPARATOR);
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT_PASTE,"Paste");
}

SequenceMainPopup::~SequenceMainPopup()
{
	// Empty
}
