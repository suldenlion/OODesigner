// CollaborationObjectMessageText.h: interface for the CollaborationObjectMessageText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLABORATIONOBJECTMESSAGETEXT_H__E7818E82_D4AB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_COLLABORATIONOBJECTMESSAGETEXT_H__E7818E82_D4AB_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Text.h"

class CollaborationObjectMessageText : public Text  
{
	DECLARE_SERIAL(CollaborationObjectMessageText)
	CollaborationObject *_master;
public:
	CollaborationObjectMessageText();
	CollaborationObjectMessageText(COODView *controller,CollaborationObject *master,int ox,int oy,Popup *popup);
	void setMaster(CollaborationObject *master) { _master = master; }
	virtual ~CollaborationObjectMessageText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void epilog(BOOL skipflag = FALSE);
	virtual Figure *container();
};

#endif // !defined(AFX_COLLABORATIONOBJECTMESSAGETEXT_H__E7818E82_D4AB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
