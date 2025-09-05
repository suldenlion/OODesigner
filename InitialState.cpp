// InitialState.cpp: implementation of the InitialState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "InitialState.h"
#include "Circle.h"

#define INITIAL_STATE_WIDTH		(20)
#define INITIAL_STATE_HEIGHT	(20)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(InitialState,NodeFigure,1)

InitialState::InitialState()
: NodeFigure()
{
}

InitialState::InitialState(COODView *controller,int x,int y,Popup* popup)
: NodeFigure(controller)
{
	_popup = popup;
	if (controller == NIL) return;
	_shape = new Circle(controller,
						x-INITIAL_STATE_WIDTH/2,y-INITIAL_STATE_HEIGHT/2,
						x+INITIAL_STATE_WIDTH/2,y+INITIAL_STATE_HEIGHT/2,
						NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeForegroundColor);
}

InitialState::~InitialState()
{

}

void InitialState::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
}

UnsignedLong* InitialState::whoAreYou()
{
	return IAMINITIALSTATE;
}

void InitialState::setForeground(COLORREF c)
{
	_shape->setBackground(c);
}

void InitialState::setBackground(COLORREF c)
{
	// do nothing
}
