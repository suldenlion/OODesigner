/* ClassMainPopup.h */

#ifndef _CLASSMAINPOPUP_H
#define _CLASSMAINPOPUP_H

#include "Classes.h"
#include "Popup.h" // Generalization

class ClassMainPopup : public Popup {
private : // data members
	CMenu *_classPopup;
	CMenu *_genPopup;
	CMenu *_aggPopup;
public : // member functions
	virtual ~ClassMainPopup();
	ClassMainPopup();
};

#endif
