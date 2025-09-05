// MessageFlowPopup.cpp: implementation of the MessageFlowPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
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

MessageFlowPopup::MessageFlowPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_MESSAGE_MESSAGE_FLOW,"Message");
}

MessageFlowPopup::~MessageFlowPopup()
{
	
}
