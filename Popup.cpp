#include "stdafx.h"
#include "resource.h"
/* Popup.C */

#include "Popup.h"
// Super Class : CObject

#include "KtgMacro.h"

Popup::~Popup()
{
	if (_popup_ptr != NIL) {
		delete _popup_ptr; _popup_ptr = NIL;
	}
}

Popup::Popup(char* name)
: CObject()
{
	_popup_ptr = new CMenu();
	_popup_ptr->CreatePopupMenu();
	_label = NIL;
	if (name != NIL) {
		_popup_ptr->AppendMenu(MF_STRING,0,name);
		_popup_ptr->AppendMenu(MF_SEPARATOR);
		_label = _popup_ptr->GetSubMenu(0);
	}
}

void Popup::popup(CWnd *pWnd,CPoint* event,BOOL)
{
	_popup_ptr->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,
			event->x,event->y,pWnd->GetParent(),NULL);
}

void Popup::changeMenuItemName(char *name)
{
	return;
}