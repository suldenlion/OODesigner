// SequenceLanePopup.cpp: implementation of the SequenceLanePopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SequenceLanePopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SequenceLanePopup::SequenceLanePopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_ACTIVATION_SEQUENCE_OBJECT,"Activation");
    _popup_ptr->AppendMenu(MF_STRING,ID_SEQUENCE_SELF_DELEGATION,"Self Delegation");
}

SequenceLanePopup::~SequenceLanePopup()
{

}
