// ActivationBar.cpp: implementation of the ActivationBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ActivationBar.h"
#include "COODView.h" // Collaboration

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ActivationBar,Box,1)

ActivationBar::~ActivationBar()
{
	// Empty
}

ActivationBar::ActivationBar()
: Box()
{
	_popup = theAppPtr->theActivationBarPopup;
}

ActivationBar::ActivationBar(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup)
: Box(controller,x1,y1,x2,y2,popup)
{
	filled() = TRUE;
	setBackground(theAppPtr->shapeBackgroundColor);
}

void ActivationBar::Serialize(CArchive& ar)
{
	Box::Serialize(ar);
}

UnsignedLong* ActivationBar::whoAreYou()
{
	return IAMACTIVATIONBAR;
}

Figure* ActivationBar::born(Figure* ptr)
{
	ActivationBar *copied;
	if (ptr == NIL) {
		copied = new ActivationBar(NIL,0,0,0,0,NIL);
	} else {
		copied = (ActivationBar *)ptr;
	}
	return (Box::born((Figure *)copied));
}
