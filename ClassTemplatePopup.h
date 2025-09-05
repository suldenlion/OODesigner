/* ClassTemplatePopup.h */

#ifndef _CLASSTEMPLATEPOPUP_H
#define _CLASSTEMPLATEPOPUP_H

#include "Classes.h"
#include "Popup.h" // Generalization

class ClassTemplatePopup : public Popup {
private : // data members
	CMenu *_supressPopup;
public : // member functions
	virtual ~ClassTemplatePopup();
	ClassTemplatePopup();
	virtual void changeMenuItemName(char *name);
};

#endif
