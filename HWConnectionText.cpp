// HWConnectionText.cpp: implementation of the HWConnectionText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "HWConnectionText.h"
#include "COODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(HWConnectionText,ConnectionText,1)

HWConnectionText::HWConnectionText()
: ConnectionText()
{
}

HWConnectionText::HWConnectionText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: ConnectionText(controller,connectionPtr,ox,oy,popup)
{
}

HWConnectionText::~HWConnectionText()
{
}

void HWConnectionText::Serialize(CArchive& ar)
{
	ConnectionText::Serialize(ar);
}

UnsignedLong *HWConnectionText::whoAreYou()
{
	return IAMHWCONNECTIONTEXT; 
}

Figure* HWConnectionText::born(Figure* ptr)
{
	HWConnectionText *copied;
	if (ptr == NIL) {
		copied = new HWConnectionText(NIL,NIL,0,0,NIL);
	} else {
		copied = (HWConnectionText *)ptr;
	}
	return (ConnectionText::born((Figure *)copied));
}
