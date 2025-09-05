// CollaborationObjectPopup.h: interface for the CollaborationObjectPopup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLABORATIONOBJECTPOPUP_H__E7818E81_D4AB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_COLLABORATIONOBJECTPOPUP_H__E7818E81_D4AB_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Popup.h"

class CollaborationObjectPopup : public Popup  
{
public:
	CollaborationObjectPopup();
	virtual ~CollaborationObjectPopup();
	virtual void changeMenuItemName(char *name);
};

#endif // !defined(AFX_COLLABORATIONOBJECTPOPUP_H__E7818E81_D4AB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
