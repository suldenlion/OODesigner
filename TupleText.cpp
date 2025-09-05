// TupleText.cpp: implementation of the TupleText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "TupleText.h"
#include "AnytionInfoTuple.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(TupleText,OneLineText,1)

TupleText::TupleText()
: OneLineText()
{
	_tuplePtr = NIL;
	_whichText = 0;
}

TupleText::TupleText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: OneLineText(controller,connectionPtr,ox,oy,popup)
{
	_tuplePtr = NIL;
	_whichText = 0;
}

TupleText::~TupleText()
{

}

void TupleText::Serialize(CArchive& ar)
{
	OneLineText::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _tuplePtr << (LONG) _whichText;
	} else {
		ar >> _tuplePtr >> (LONG &) _whichText;
	}
}

Figure* TupleText::born(Figure* ptr)
{
	TupleText *copied;
	if (ptr == NIL) {
		copied = new TupleText(NIL,NIL,0,0,NIL);
	} else {
		copied = (TupleText *)ptr;
	}
	copied->_whichText = _whichText;
	return (OneLineText::born((Figure *)copied));
}
