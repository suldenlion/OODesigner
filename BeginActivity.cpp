// BeginActivity.cpp: implementation of the BeginActivity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "BeginActivity.h"
#include "Circle.h"

#define BEGIN_ACTIVITY_WIDTH		(20)
#define BEGIN_ACTIVITY_HEIGHT		(20)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(BeginActivity,NodeFigure,1)

BeginActivity::BeginActivity()
: NodeFigure()
{
}

BeginActivity::BeginActivity(COODView *controller,int x,int y,Popup* popup)
: NodeFigure(controller)
{
	_popup = popup;
	if (controller == NIL) return;
	_shape = new Circle(controller,
						x-BEGIN_ACTIVITY_WIDTH/2,y-BEGIN_ACTIVITY_HEIGHT/2,
						x+BEGIN_ACTIVITY_WIDTH/2,y+BEGIN_ACTIVITY_HEIGHT/2,
						NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeForegroundColor);
}

BeginActivity::~BeginActivity()
{

}

void BeginActivity::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
}

UnsignedLong* BeginActivity::whoAreYou()
{
	return IAMBEGINACTIVITY;
}

void BeginActivity::setForeground(COLORREF c)
{
	_shape->setBackground(c);
}

void BeginActivity::setBackground(COLORREF c)
{
	// do nothing
}
