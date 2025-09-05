// UseCase.cpp: implementation of the UseCase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "UseCase.h"
#include "UseCaseText.h"
#include "Circle.h"
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
IMPLEMENT_SERIAL(UseCase,EditableFigure,1)

UseCase::UseCase()
: EditableFigure()
{
}

UseCase::UseCase(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	if (controller == NIL) return;
	_popup = popup;
	_initWidth = USECASE_INIT_WIDTH;
	_gapX = XGAP_USECASE;
	_gapY = YGAP_USECASE;
	_shape = new Circle(controller,ox,oy,ox+_initWidth,oy+2*_gapY+deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	setBackground(theAppPtr->shapeBackgroundColor);
	_texts->insert(new UseCaseText(controller,this,IAMUSECASENAME,ox+_gapX,oy+_gapY));
}

void UseCase::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);
}

UseCase::~UseCase()
{
}

UnsignedLong* UseCase::whoAreYou()
{
	return IAMUSECASE;
}

void UseCase::draw(CDC* dcp)
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

void UseCase::drawOnMetaFile(CDC* dcp)
{
	if (!_inCanvas) return;
	EditableFigure::drawOnMetaFile(dcp);
}

Figure* UseCase::born(Figure* ptr)
{
	UseCase *copied;
	if (ptr == NIL) {
		copied = new UseCase(NIL,0,0,0,NIL);
	} else {
		copied = (UseCase *)ptr;
	}
	return (EditableFigure::born((Figure *)copied));
}
