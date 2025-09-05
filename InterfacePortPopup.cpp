// InterfacePortPopup.cpp: implementation of the InterfacePortPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "InterfacePortPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

InterfacePortPopup::InterfacePortPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT,"Edit");
    _popup_ptr->AppendMenu(MF_STRING,ID_DELETE_FIGURE,"Delete");
    _popup_ptr->AppendMenu(MF_STRING,ID_INTERFACE_PROPERTIES,"Properties");
}

InterfacePortPopup::~InterfacePortPopup()
{

}
