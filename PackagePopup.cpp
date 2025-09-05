// PackagePopup.cpp: implementation of the PackagePopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "PackagePopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PackagePopup::PackagePopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT,"Edit");
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_OPEN_PACKAGE,"Open");
}

PackagePopup::~PackagePopup()
{

}
