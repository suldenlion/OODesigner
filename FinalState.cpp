// FinalState.cpp: implementation of the FinalState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "FinalState.h"
#include "Circle.h"
#include "COODView.h"
#include "FigureList.h"

#define FINAL_STATE_WIDTH		(30)
#define FINAL_STATE_HEIGHT		(30)
#define INNER_CIRCLE_WIDTH		(20)
#define INNER_CIRCLE_HEIGHT		(20)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(FinalState,NodeFigure,1)

FinalState::FinalState()
: NodeFigure()
{
}

FinalState::FinalState(COODView *controller,int x,int y,Popup* popup)
: NodeFigure(controller)
{
	_popup = popup;
	if (controller == NIL) return;
	_shape = new Circle(controller,
						x-FINAL_STATE_WIDTH/2,y-FINAL_STATE_HEIGHT/2,
						x+FINAL_STATE_WIDTH/2,y+FINAL_STATE_HEIGHT/2,
						NIL);
	Circle *innerCircle = new Circle(controller,
						x-INNER_CIRCLE_WIDTH/2,y-INNER_CIRCLE_HEIGHT/2,
						x+INNER_CIRCLE_WIDTH/2,y+INNER_CIRCLE_HEIGHT/2,
						NIL);
	innerCircle->filled() = TRUE;
	innerCircle->setBackground(theAppPtr->shapeForegroundColor);
	_decorations->insert(innerCircle);
}

FinalState::~FinalState()
{

}

void FinalState::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
}

UnsignedLong* FinalState::whoAreYou()
{
	return IAMFINALSTATE;
}

void FinalState::setForeground(COLORREF c)
{
	Figure *ptr = _decorations->getFirst();
	if (ptr != NIL) ptr->setBackground(c);
}

