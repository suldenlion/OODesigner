// ActivationBarPopup.cpp: implementation of the ActivationBarPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ActivationBarPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ActivationBarPopup::ActivationBarPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_ACTIVATION_KILL_SIGN,"Kill Sign");
    _popup_ptr->AppendMenu(MF_STRING,ID_SEQUENCE_SELF_DELEGATION,"Self Delegation");
}

ActivationBarPopup::~ActivationBarPopup()
{

}

