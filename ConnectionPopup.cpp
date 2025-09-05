// ConnectionPopup.cpp: implementation of the ConnectionPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ConnectionPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConnectionPopup::ConnectionPopup(char *textName)
: Popup(NIL)
{
	_popup_ptr->AppendMenu(MF_STRING,ID_DELETE_FIGURE,"Delete");
	_popup_ptr->AppendMenu(MF_STRING,ID_CONNECTION_NAME_EDIT,textName);
}

ConnectionPopup::~ConnectionPopup()
{

}
