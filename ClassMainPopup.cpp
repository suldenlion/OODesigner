#include "stdafx.h"
#include "resource.h"
/* ClassMainPopup.C */

#include "ClassMainPopup.h"
#include "KtgMacro.h"
// Super Class : Popup

ClassMainPopup::~ClassMainPopup()
{
	if (_classPopup != NIL) {
		delete _classPopup; _classPopup = NIL;
	}
	if (_genPopup != NIL) {
		delete _genPopup; _genPopup = NIL;
	}
	if (_aggPopup != NIL) {
		delete _aggPopup; _aggPopup = NIL;
	}
}

ClassMainPopup::ClassMainPopup()
: Popup("Main Popup")
{
	_classPopup = new CMenu();
	_classPopup->CreatePopupMenu();
    _classPopup->AppendMenu(MF_STRING,ID_CREATE_CLASSTEMPLATE,"Class");
    _classPopup->AppendMenu(MF_STRING,ID_CRETAE_TEMPLATECLASS,"Template");
    _classPopup->AppendMenu(MF_STRING,ID_CREATE_INTERFACE,"Interface");
    _classPopup->AppendMenu(MF_STRING,ID_CREATE_UTILITY,"Utility");
	_popup_ptr->AppendMenu(MF_POPUP,(unsigned int)_classPopup->m_hMenu,"Class");

	_popup_ptr->AppendMenu(MF_STRING,ID_CREATE_PACKAGETEMPLATE,"Package");

	_genPopup = new CMenu();
	_genPopup->CreatePopupMenu();
    _genPopup->AppendMenu(MF_STRING,ID_CREATE_GENERALIZATION,"Generalization");
    _genPopup->AppendMenu(MF_STRING,ID_CREATE_REFINEMENT,"Refinement");
	_popup_ptr->AppendMenu(MF_POPUP,(unsigned int)_genPopup->m_hMenu,"Generalization");

	_aggPopup = new CMenu();
	_aggPopup->CreatePopupMenu();
    _aggPopup->AppendMenu(MF_STRING,ID_CREATE_AGGREGATION,"Aggregation");
    _aggPopup->AppendMenu(MF_STRING,ID_CREATE_COMPOSITION,"Composition");
	_popup_ptr->AppendMenu(MF_POPUP,(unsigned int)_aggPopup->m_hMenu,"Aggregation");

	_popup_ptr->AppendMenu(MF_STRING,ID_CREATE_DEPENDENCY,"Dependency");

    _popup_ptr->AppendMenu(MF_STRING,ID_CREATE_ASSOCIATION,"Association");

	_popup_ptr->AppendMenu(MF_STRING,ID_CREATE_WIDEPACKAGE,"Wide Package");

	_popup_ptr->AppendMenu(MF_SEPARATOR);
    _popup_ptr->AppendMenu(MF_STRING,ID_POPUP_EDIT_PASTE,"Paste");
}


