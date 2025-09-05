// Note.cpp: implementation of the Note class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Note.h"
#include "COODView.h"
#include "NoteBoundary.h"
#include "NoteText.h"
#include "SlaveryTextList.h"
#include "AnchorList.h"
#include "Line.h"
#include "Anchor.h"
#include "UnsignedLong.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(Note,EditableFigure,1)

Note::Note()
: EditableFigure()
{
	_anchors = NIL;
	_moveAllFlag = FALSE;
}

Note::Note(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	if (controller == NIL) return;
	_moveAllFlag = FALSE;
	_popup = popup;
	_initWidth = NOTE_INIT_WIDTH;
	_gapX = XGAP_NOTE;
	_gapY = YGAP_NOTE;
	_shape = new NoteBoundary(controller,ox,oy,ox+_initWidth,oy+2*_gapY+deltaV,NIL);
//	_shape->filled() = TRUE;
	setBackground(theAppPtr->shapeBackgroundColor);
	_texts->insert(new NoteText(controller,this,IAMNOTENAME,ox+_gapX,oy+_gapY));
	_anchors = new AnchorList();
}

Note::~Note()
{
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		delete anchor;
		anchor = _anchors->getNext();
	}
	_anchors->clear();
	delete _anchors;
}

void Note::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _anchors;
	} else {
		ar >> _anchors;
	}
}

UnsignedLong* Note::whoAreYou()
{
	return IAMNOTE;
}

Figure* Note::born(Figure* ptr)
{
	Note *copied;
	if (ptr == NIL) {
		copied = new Note(NIL,0,0,0,NIL);
	} else {
		copied = (Note *)ptr;
	}
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		Anchor *newAnchor = (Anchor *)anchor->born(NIL);
		newAnchor->setNote(copied);
		copied->_anchors->insert(newAnchor);
		anchor = _anchors->getNext();
	}
	return (EditableFigure::born((Figure *)copied));
}

BOOL Note::needCentering()
{
	return FALSE;
}

void Note::clear(CDC* dcp)
{
	EditableFigure::clear(dcp);
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->clear(dcp);
		anchor = _anchors->getNext();
	}
}

void Note::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int x1,y1,x2,y2;
	x1 = _shape->_x1.get();
	y1 = _shape->_y1.get();
	x2 = _shape->_x2.get();
	y2 = _shape->_y2.get();
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(clip(dcp),RGN_COPY);
		excludeRects(dcp);

		CPoint pt[5];
		pt[0].x = x1;
		pt[0].y = y1;
		pt[1].x = x2 - CORNER_GAP;
		pt[1].y = y1;
		pt[2].x = x2;
		pt[2].y = y1 + CORNER_GAP;
		pt[3].x = x2;
		pt[3].y = y2;
		pt[4].x = x1;
		pt[4].y = y2;
		CBrush brush(background());
		CBrush *oldBrush = dcp->SelectObject(&brush);
		dcp->Polygon(pt,5);
		dcp->SelectObject(oldBrush);
	}
	EditableFigure::draw(dcp);
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(NULL,RGN_COPY);

		getExclusiveClipRect(x1,y1,x2,y2);
		dcp->ExcludeClipRect(x1,y1,x2,y2);
	}
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->draw(dcp);
		anchor = _anchors->getNext();
	}
}

void Note::drawOnMetaFile(CDC* dcp)
{
	if (!_inCanvas) return;

	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->drawOnMetaFile(dcp);
		anchor = _anchors->getNext();
	}
	
	int x1,y1,x2,y2;
	x1 = _shape->_x1.get();
	y1 = _shape->_y1.get();
	x2 = _shape->_x2.get();
	y2 = _shape->_y2.get();

	CPoint pt[5];
	pt[0].x = x1;
	pt[0].y = y1;
	pt[1].x = x2 - CORNER_GAP;
	pt[1].y = y1;
	pt[2].x = x2;
	pt[2].y = y1 + CORNER_GAP;
	pt[3].x = x2;
	pt[3].y = y2;
	pt[4].x = x1;
	pt[4].y = y2;
	CBrush brush(background());
	CBrush *oldBrush = dcp->SelectObject(&brush);
	dcp->Polygon(pt,5);
	dcp->SelectObject(oldBrush);

	EditableFigure::drawOnMetaFile(dcp);
}

void Note::drawBoundary(CDC* dcp)
{
	EditableFigure::drawBoundary(dcp);
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->drawBoundary(dcp);
		anchor = _anchors->getNext();
	}
}

void Note::drawBoundaryEx(CDC* dcp)
{
	drawBoundary(dcp);
}

void Note::move(CDC* dcp,int dx,int dy)
{
	EditableFigure::move(dcp,dx,dy);
	if (_moveAllFlag == TRUE) {
		Anchor *anchor = _anchors->getFirst();
		while (anchor != NIL) {
			anchor->move(dcp,dx,dy);
			anchor = _anchors->getNext();
		}
	} else {
		int cx,cy;
		center(cx,cy);
		Anchor *anchor = _anchors->getFirst();
		while (anchor != NIL) {
			anchor->draw(dcp);
			anchor->setXY1(cx,cy);
			anchor->draw(dcp);
			anchor = _anchors->getNext();
		}
	}
}

void Note::moveCoord(int dx,int dy)
{
	EditableFigure::moveCoord(dx,dy);
	int cx,cy;
	center(cx,cy);
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->setXY1(cx,cy);
		anchor = _anchors->getNext();
	}
}

void Note::moveCoordForScroll(int dx,int dy)
{
	EditableFigure::moveCoordForScroll(dx,dy);
	int cx,cy;
	center(cx,cy);
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->setXY1(cx,cy);
		anchor = _anchors->getNext();
	}
}

void Note::setFocus(int x,int y)
{
	EditableFigure::setFocus(x,y);
}

BOOL Note::wantToResize(int &x,int &y)
{
	if (_focus != NIL &&
		_focus->whoAreYou()->equals(IAMANCHOR)) {
		return ((Anchor *)_focus)->wantToResize(x,y);
	}
	return EditableFigure::wantToResize(x,y);
}

BOOL Note::wantToMove(int x,int y)
{
	if (_focus != NIL &&
		_focus->whoAreYou()->equals(IAMANCHOR))
		return FALSE;
	return EditableFigure::wantToMove(x,y);
}

void Note::makeRegion(CRgn *sourceClipRgn)
{
	EditableFigure::makeRegion(sourceClipRgn);
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->makeRegion(sourceClipRgn);
		anchor = _anchors->getNext();
	}
}

void Note::resetRegion()
{
	EditableFigure::resetRegion();
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->resetRegion();
		anchor = _anchors->getNext();
	}
}

void Note::releaseRegion()
{
	EditableFigure::releaseRegion();
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->releaseRegion();
		anchor = _anchors->getNext();
	}
}

BOOL Note::onEnter(int x,int y)
{
	BOOL flag = EditableFigure::onEnter(x,y);
	if (flag) {
		// À§¿¡¼­ _focus = _shape; °¡ µÊ
		return TRUE;
	}
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		if (anchor->onEnter(x,y)) {
			_focus = anchor;
			return TRUE;
		}
		anchor = _anchors->getNext();
	}
	return FALSE;
}

void Note::eraseDots(CDC* dcp)
{
	if (_focus == NIL) {
		EditableFigure::eraseDots(dcp);
		return;
	}
	if (_focus->whoAreYou()->equals(IAMANCHOR)) {
		_focus->eraseDots(dcp);
	} else {
		EditableFigure::eraseDots(dcp);
	}
}

void Note::drawDots(CDC* dcp)
{
	if (_focus == NIL) {
		EditableFigure::drawDots(dcp);
		return;
	}
	if (_focus->whoAreYou()->equals(IAMANCHOR)) {
		_focus->drawDots(dcp);
	} else {
		EditableFigure::drawDots(dcp);
	}
}

void Note::deleteFocusObject()
{
	if (_focus != NIL &&
		_focus->whoAreYou()->equals(IAMANCHOR)) {
		_anchors->remove((Anchor *)_focus);
		delete _focus;
		_focus = NIL;
	} else {
		EditableFigure::deleteFocusObject();
	}
	/*
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->resetRegion();
		anchor = _anchors->getNext();
	}
	*/
}

void Note::bye()
{
	EditableFigure::bye();
	int cx,cy;
	center(cx,cy);
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->setXY1(cx,cy);
		anchor = _anchors->getNext();
	}
}

void Note::setController(COODView *ptr)
{
	EditableFigure::setController(ptr);
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		anchor->setController(ptr);
		anchor = _anchors->getNext();
	}
}

BOOL Note::containedWithin(int x1,int y1,int x2,int y2)
{
	_moveAllFlag = FALSE;
	BOOL val = EditableFigure::containedWithin(x1,y1,x2,y2);
	if (val == FALSE) return FALSE;
	Anchor *anchor = _anchors->getFirst();
	while (anchor != NIL) {
		if (anchor->containedWithin(x1,y1,x2,y2) == FALSE) {
			_moveAllFlag = FALSE;
			return TRUE;
		}
		anchor = _anchors->getNext();
	}
	_moveAllFlag = TRUE;
	return TRUE;
}

void Note::epilog(BOOL abortionFlag)
{
	EditableFigure::epilog(abortionFlag);
	_moveAllFlag = FALSE;
}

void Note::addAnchor(Anchor *anchor)
{
	_anchors->insert(anchor);
}
