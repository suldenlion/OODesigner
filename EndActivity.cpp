// EndActivity.cpp: implementation of the EndActivity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "EndActivity.h"
#include "Circle.h"
#include "COODView.h"
#include "FigureList.h"

#define END_ACTIVITY_WIDTH		(30)
#define END_ACTIVITY_HEIGHT		(30)
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
IMPLEMENT_SERIAL(EndActivity,NodeFigure,1)

EndActivity::EndActivity()
: NodeFigure()
{
}

EndActivity::EndActivity(COODView *controller,int x,int y,Popup* popup)
: NodeFigure(controller)
{
	_popup = popup;
	if (controller == NIL) return;
	_shape = new Circle(controller,
						x-END_ACTIVITY_WIDTH/2,y-END_ACTIVITY_HEIGHT/2,
						x+END_ACTIVITY_WIDTH/2,y+END_ACTIVITY_HEIGHT/2,
						NIL);
	Circle *innerCircle = new Circle(controller,
						x-INNER_CIRCLE_WIDTH/2,y-INNER_CIRCLE_HEIGHT/2,
						x+INNER_CIRCLE_WIDTH/2,y+INNER_CIRCLE_HEIGHT/2,
						NIL);
	innerCircle->filled() = TRUE;
	innerCircle->setBackground(theAppPtr->shapeForegroundColor);
	_decorations->insert(innerCircle);
}

EndActivity::~EndActivity()
{

}

void EndActivity::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
}

UnsignedLong* EndActivity::whoAreYou()
{
	return IAMENDACTIVITY;
}

void EndActivity::setForeground(COLORREF c)
{
	Figure *ptr = _decorations->getFirst();
	if (ptr != NIL) ptr->setBackground(c);
}

