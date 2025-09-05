// SynchronizationPopup.cpp: implementation of the SynchronizationPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SynchronizationPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SynchronizationPopup::SynchronizationPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT,"Condition");
}

SynchronizationPopup::~SynchronizationPopup()
{

}
