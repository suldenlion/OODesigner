// PackageTemplate.cpp: implementation of the PackageTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "COODView.h"
#include "COODDoc.h"
#include "PackageTemplate.h"
#include "Box.h"
#include "Line.h"
#include "LineList.h"
#include "PackageText.h"
#include "SlaveryTextList.h"
#include "FigureList.h"
#include "Popup.h"
#include "ExcludeRect.h"
#include "ExcludeRectList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(PackageTemplate,EditableFigure,1)

PackageTemplate::PackageTemplate()
: EditableFigure()
{
	_popup = theAppPtr->thePackagePopup;
}

PackageTemplate::PackageTemplate(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	if (controller == NIL) return;
	_popup = popup;
	_initWidth = PACKAGETEMPLATE_INIT_WIDTH;
	_gapX = XGAP_PACKAGETEMPLATE;
	_gapY = YGAP_PACKAGETEMPLATE;
	_shape = new Box(controller,ox,oy,ox+_initWidth,oy+2*_gapY+deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	setBackground(theAppPtr->shapeBackgroundColor);
	_texts->insert(new PackageText(controller,this,IAMPACKAGENAME,ox+_gapX,oy+_gapY));

	// 주의 : _hatLeft,_hatUp,_hatRight를 이 클래스에서 destruction 시키면 안됨
	_hatLeft = new Line(controller,ox,oy-HAT_HEIGHT,ox,oy,NIL,STRAIGHT);
	_hatUp = new Line(controller,ox,oy-HAT_HEIGHT,ox+HAT_WIDTH,oy-HAT_HEIGHT,NIL,STRAIGHT);
	_hatRight = new Line(controller,ox+HAT_WIDTH,oy-HAT_HEIGHT,ox+HAT_WIDTH,oy,NIL,STRAIGHT);
	_decorations->insert(_hatLeft);
	_decorations->insert(_hatUp);
	_decorations->insert(_hatRight);
}

PackageTemplate::~PackageTemplate()
{
}

void PackageTemplate::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _hatLeft << _hatUp;
		ar << _hatRight;
	} else {
		ar >> _hatLeft >> _hatUp;
		ar >> _hatRight;
	}
}

void PackageTemplate::getAdditionalExcludeRects(ExcludeRectList *pList)
{
	int width = HAT_WIDTH;
	int height = HAT_HEIGHT;
	int x = _shape->_x1.get();
	int y = _shape->_y1.get() - height;
	ExcludeRect *rect = new ExcludeRect(this,x,y,x+width+1,y+height+1);
	pList->addTail(rect);
}

void PackageTemplate::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = HAT_WIDTH;
	int height = HAT_HEIGHT;
	x = _shape->_x1.get();
	y = _shape->_y1.get() - height;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		CRgn *clipRgn = clip(dcp);
		if (clipRgn != NULL) {
			CRgn hatRgn;
			hatRgn.CreateRectRgn(x,y,x+width+1,y+height+1);
			CRgn tmpRgn;
			tmpRgn.CreateRectRgn(0,0,0,0);
			tmpRgn.CombineRgn(clipRgn,&hatRgn,RGN_OR);
			dcp->SelectClipRgn(&tmpRgn,RGN_COPY);
		} else { // NULL
			dcp->SelectClipRgn(NULL,RGN_COPY);
		}
		excludeRects(dcp);

		CRect rect(x,y,x+width+1,y+height+1);
		CBrush brush(background());
		dcp->FillRect(&rect,&brush);
	}
	EditableFigure::draw(dcp);
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(NULL,RGN_COPY);
	}
}

void PackageTemplate::drawOnMetaFile(CDC* dcp)
{
	if (!_inCanvas) return;
	int x,y;
	int width = HAT_WIDTH;
	int height = HAT_HEIGHT;
	x = _shape->_x1.get();
	y = _shape->_y1.get() - height;
	CRect rect(x,y,x+width+1,y+height+1);
	CBrush brush(background());
	dcp->FillRect(&rect,&brush);

	EditableFigure::drawOnMetaFile(dcp);
}

UnsignedLong* PackageTemplate::whoAreYou()
{
	return IAMPACKAGETEMPLATE;
}

Figure* PackageTemplate::born(Figure* ptr)
{
	PackageTemplate *copied;
	if (ptr == NIL) {
		copied = new PackageTemplate(NIL,0,0,0,NIL);
	} else {
		copied = (PackageTemplate *)ptr;
	}
	return (EditableFigure::born((Figure *)copied));
}

void PackageTemplate::setSpecificDataMembers()
{
	_hatLeft = (Line *)_decorations->getFirst();
	_hatUp = (Line *)_decorations->getNext();
	_hatRight = (Line *)_decorations->getNext();
}

void PackageTemplate::popup(CPoint* event,BOOL)
{
	Figure::popup(event);
}
