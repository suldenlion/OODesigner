// SequenceObjectPopup.cpp: implementation of the SequenceObjectPopup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SequenceObjectPopup.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SequenceObjectPopup::SequenceObjectPopup()
: Popup(NIL)
{
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT,"Edit");
}

SequenceObjectPopup::~SequenceObjectPopup()
{

}
