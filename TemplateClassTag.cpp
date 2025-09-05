// TemplateClassTag.cpp: implementation of the TemplateClassTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "TemplateClassTag.h"
#include "Box.h"
#include "TemplateClassTagText.h"
#include "SlaveryTextList.h"
#include "ClassTemplate.h"
#include "ClassText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(TemplateClassTag,EditableFigure,1)

TemplateClassTag::TemplateClassTag()
: EditableFigure()
{
	_classPointer = NIL;
}

TemplateClassTag::TemplateClassTag(COODView *controller,ClassTemplate *classPointer,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	_classPointer = classPointer;
	_popup = popup;
	if (controller == NIL) return;
	_initWidth = TEMPLATE_TAG_INIT_WIDTH;
	_gapX = XGAP_TEMPLATE_TAG;
	_gapY = YGAP_TEMPLATE_TAG;
	_shape = new Box(controller,ox,oy,ox+_initWidth,oy+2*_gapY+deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	setBackground(theAppPtr->shapeBackgroundColor);
	_texts->insert(new TemplateClassTagText(controller,this,IAMTEMPLATETAGNAME,ox+_gapX,oy+_gapY));
}

TemplateClassTag::~TemplateClassTag()
{
	_classPointer = NIL;
}

void TemplateClassTag::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);   
	if (ar.IsStoring()) {
		ar << _classPointer;
	} else {
		ar >> _classPointer;
	}
}

ClassTemplate *TemplateClassTag::classPointer()
{
	return _classPointer;
}

SlaveryText *TemplateClassTag::nextText(SlaveryText *currentText)
{
	return _classPointer->nextText(NIL);
}

TemplateClassTagText *TemplateClassTag::tagText()
{
	return (TemplateClassTagText *)_texts->getFirst();
}

Figure* TemplateClassTag::born(Figure* ptr)
{
	TemplateClassTag *copied;
	if (ptr == NIL) {
		copied = new TemplateClassTag(NIL,NIL,0,0,0,NIL);
	} else {
		copied = (TemplateClassTag *)ptr;
	}
	return (EditableFigure::born((Figure *)copied));
}

BOOL TemplateClassTag::needCentering()
{
	return FALSE;
}

void TemplateClassTag::getTemplateTagString(char *buffer,int size)
{
	tagText()->getName(buffer,size);
}

void TemplateClassTag::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	CPen *oldPen = dcp->GetCurrentPen();
	LOGPEN logpen;
	oldPen->GetLogPen(&logpen);
	CPen penDash(PS_DOT,1,logpen.lopnColor);
	oldPen = dcp->SelectObject(&penDash);
	EditableFigure::draw(dcp);
	dcp->SelectObject(oldPen);
}

void TemplateClassTag::drawBoundary(CDC* dcp)
{
	CPen *oldPen = dcp->GetCurrentPen();
	LOGPEN logpen;
	oldPen->GetLogPen(&logpen);
	CPen penDash(PS_DOT,1,logpen.lopnColor);
	oldPen = dcp->SelectObject(&penDash);
	EditableFigure::drawBoundary(dcp);
	dcp->SelectObject(oldPen);
}

void TemplateClassTag::move(CDC* dcp,int dx,int dy)
{
	CPen *oldPen = dcp->GetCurrentPen();
	LOGPEN logpen;
	oldPen->GetLogPen(&logpen);
	CPen penDash(PS_DOT,1,logpen.lopnColor);
	oldPen = dcp->SelectObject(&penDash);
	EditableFigure::move(dcp,dx,dy);
	dcp->SelectObject(oldPen);
}
