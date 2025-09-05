// NoteBoundary.cpp: implementation of the NoteBoundary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "NoteBoundary.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(NoteBoundary,Box,1)

NoteBoundary::~NoteBoundary()
{
	// Empty
}

NoteBoundary::NoteBoundary()
: Box()
{
}

NoteBoundary::NoteBoundary(COODView *controller,int x,int y,Popup *popup)
: Box(controller,x,y,popup)
{
}

NoteBoundary::NoteBoundary(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup)
: Box(controller,x1,y1,x2,y2,popup)
{
}

void NoteBoundary::Serialize(CArchive& ar)
{
	Box::Serialize(ar);
}

void NoteBoundary::drawBoundary(CDC* dcp)
{
	draw(dcp);
}

void NoteBoundary::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int x1 = getX1();
	int y1 = getY1();
	int x2 = getX2();
	int y2 = getY2();
	Line::DrawLine(dcp,x1,y1,x1,y2);
	Line::DrawLine(dcp,x1,y2,x2+1,y2);
	Line::DrawLine(dcp,x1,y1,x2-CORNER_GAP,y1);
	Line::DrawLine(dcp,x2,y1+CORNER_GAP,x2,y2);
	Line::DrawLine(dcp,x2-CORNER_GAP,y1,x2,y1+CORNER_GAP);
	Line::DrawLine(dcp,x2-CORNER_GAP,y1,x2-CORNER_GAP,y1+CORNER_GAP);
	Line::DrawLine(dcp,x2-CORNER_GAP,y1+CORNER_GAP,x2,y1+CORNER_GAP);
}

Figure* NoteBoundary::born(Figure* ptr)
{
	NoteBoundary *copied;
	if (ptr == NIL) {
		copied = new NoteBoundary(NIL,0,0,NIL);
	} else {
		copied = (NoteBoundary *)ptr;
	}
	return (Box::born((Figure *)copied));
}

