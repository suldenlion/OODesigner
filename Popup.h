/* Popup.h */

#ifndef _POPUP_H
#define _POPUP_H

#include "Classes.h"

class Popup : public CObject {
protected : // data members
	CMenu *_popup_ptr;
	CMenu *_label;
public : // member functions
	virtual ~Popup();
	Popup(char* name);
	virtual void popup(CWnd *pWnd,CPoint* event,BOOL = FALSE);
	virtual void changeMenuItemName(char *name);
};

#endif
