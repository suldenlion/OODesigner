// CollaborationObjectMessageText.cpp: implementation of the CollaborationObjectMessageText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "CollaborationObjectMessageText.h"
#include "CollaborationObject.h"
#include "COODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CollaborationObjectMessageText,Text,1)

CollaborationObjectMessageText::CollaborationObjectMessageText()
: Text()
{
	_master = NIL;
}

CollaborationObjectMessageText::CollaborationObjectMessageText(COODView *controller,CollaborationObject *master,int ox,int oy,Popup *popup)
: Text(controller,ox,oy,popup)
{
	_master = master;
}

CollaborationObjectMessageText::~CollaborationObjectMessageText()
{
	_master = NIL;
}

void CollaborationObjectMessageText::Serialize(CArchive& ar)
{
	Text::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _master;
	} else {
		ar >> _master;
	}
}

UnsignedLong *CollaborationObjectMessageText::whoAreYou()
{
	return IAMCOLOBJMESSAGETEXT; 
}

Figure* CollaborationObjectMessageText::born(Figure* ptr)
{
	CollaborationObjectMessageText *copied;
	if (ptr == NIL) {
		copied = new CollaborationObjectMessageText(NIL,NIL,0,0,NIL);
	} else {
		copied = (CollaborationObjectMessageText *)ptr;
	}
	return (Text::born((Figure *)copied));
}

BOOL CollaborationObjectMessageText::moveProlog(BOOL moveAllFlag)
{
	if (moveAllFlag) {
		return TRUE;
	}
	// Node 객체로 부터 링크를 잠시 끊는다.
	_master->setMessageText(NIL);
	return FALSE;
}

void CollaborationObjectMessageText::epilog(BOOL skipflag)
{
	if (skipflag) return;
	// Node 객체로 다시 연결한다.
	_master->setMessageText(this);
}

Figure *CollaborationObjectMessageText::container()
{
	return (Figure *)_master;
}


