// SyncConditionText.cpp: implementation of the SyncConditionText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SyncConditionText.h"
#include "SynchronizationBar.h"
#include "COODView.h"
#include "VTerm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SyncConditionText,Text,1)

SyncConditionText::SyncConditionText()
: Text()
{
	_master = NIL;
}

SyncConditionText::SyncConditionText(COODView *controller,SynchronizationBar *master,int ox,int oy,Popup *popup)
: Text(controller,ox,oy,popup)
{
	_master = master;
}

SyncConditionText::~SyncConditionText()
{
	_master = NIL;
}

void SyncConditionText::Serialize(CArchive& ar)
{
	Text::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _master;
	} else {
		ar >> _master;
	}
}

UnsignedLong *SyncConditionText::whoAreYou()
{
	return IAMSYNCCONDITIONTEXT;
}

Figure* SyncConditionText::born(Figure* ptr)
{
	SyncConditionText *copied;
	if (ptr == NIL) {
		copied = new SyncConditionText(NIL,NIL,0,0,NIL);
	} else {
		copied = (SyncConditionText *)ptr;
	}
	return (Text::born((Figure *)copied));
}

Figure *SyncConditionText::container()
{
	return (Figure *)_master;
}

void SyncConditionText::adjustXY1Coord()
{
	_controller->clear(this);
	int x1 = getX1();
	int y1 = getY1();
	int x2 = getX2();
	int y2 = getY2();
	int height = y2-y1;
	int newX1 = _master->shape()->getX2() + CONDITION_DX_FROM_X2;
	int newY1 = _master->shape()->getY2() - height/2;
	recalcCoordFromXY1(newX1,newY1);
	_controller->draw(this);
	_vterm->activate();
}

void SyncConditionText::goNextLine()
{
	Text::goNextLine();
	adjustXY1Coord();
}

BOOL SyncConditionText::delLine()
{
	if (Text::delLine()) return TRUE;
	adjustXY1Coord();
	return FALSE;
}

BOOL SyncConditionText::delChar()
{
	int oldY2 = getY2();
	BOOL returnVal = Text::delChar();
	if (oldY2 == getY2()) return returnVal;
	adjustXY1Coord();
	return returnVal;
}

BOOL SyncConditionText::delCharBack()
{
	int oldY2 = getY2();
	BOOL returnVal = Text::delCharBack();
	if (oldY2 == getY2()) return returnVal;
	adjustXY1Coord();
	return returnVal;
}