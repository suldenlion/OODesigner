// Activity.cpp: implementation of the Activity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Activity.h"
#include "ActivityText.h"
#include "RoundBoxA.h"
#include "SlaveryTextList.h"
#include "FigureList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Activity,EditableFigure,1)

Activity::Activity()
: EditableFigure()
{
}

Activity::Activity(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	if (controller == NIL) return;
	_popup = popup;
	_initWidth = ACTIVITY_INIT_WIDTH;
	_gapX = XGAP_ACTIVITY;
	_gapY = YGAP_ACTIVITY;
	_shape = new RoundBoxA(controller,ox,oy,ox+_initWidth,oy+2*_gapY+deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	setBackground(theAppPtr->shapeBackgroundColor);
	_texts->insert(new ActivityText(controller,this,IAMACTIVITYNAME,ox+_gapX,oy+_gapY));
}

Activity::~Activity()
{
}

void Activity::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);
}

UnsignedLong* Activity::whoAreYou()
{
	return IAMACTIVITY;
}

Figure* Activity::born(Figure* ptr)
{
	Activity *copied;
	if (ptr == NIL) {
		copied = new Activity(NIL,0,0,0,NIL);
	} else {
		copied = (Activity *)ptr;
	}
	return (EditableFigure::born((Figure *)copied));
}

void Activity::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(clip(dcp),RGN_COPY);
		excludeRects(dcp);
	}
	EditableFigure::draw(dcp);
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(NULL,RGN_COPY);
	}
}

void Activity::drawOnMetaFile(CDC* dcp)
{
	if (!_inCanvas) return;
	EditableFigure::drawOnMetaFile(dcp);
}
