// EditableFigure.cpp: implementation of the EditableFigure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "EditableFigure.h"
#include "LineList.h"
#include "SlaveryTextList.h"
#include "Line.h"
#include "SlaveryText.h"
#include "UnsignedLong.h"
#include "COODView.h"
#include "TextContent.h"
#include "Connection.h"
#include "ConnectionList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(EditableFigure,NodeFigure,1)

EditableFigure::EditableFigure()
: NodeFigure()
{
	_focus = NIL;
	_initWidth = INIT_WIDTH;
	_emptyGapX = 0;
	_moreGapAtTop = 0;
	_gapX = 0;
	_gapY = 0;
	_texts = NIL;
	_separators = NIL;
}

EditableFigure::EditableFigure(COODView *controller)
: NodeFigure(controller)
{
	_focus = NIL;
	_initWidth = INIT_WIDTH;
	_emptyGapX = 0;
	_moreGapAtTop = 0;
	if (controller == NIL) return;
	_texts = new SlaveryTextList();
	_separators = new LineList();
}

void EditableFigure::Serialize(CArchive& ar)
{
	NodeFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _initWidth << (LONG) _emptyGapX;
		ar << (LONG) _moreGapAtTop;
		ar << (LONG) _gapX << (LONG) _gapY;
		ar << _texts << _separators;
	} else {
		ar >> (LONG&) _initWidth >> (LONG&) _emptyGapX;
		ar >> (LONG&) _moreGapAtTop;
		ar >> (LONG&) _gapX >> (LONG&) _gapY;
		ar >> _texts >> _separators;
	}
}

EditableFigure::~EditableFigure()
{
	_focus = NIL;
	if (_texts != NIL) {
		SlaveryText *aText = _texts->getFirst();
		while (aText != NIL) {
			delete aText;
			aText = _texts->getNext();
		}
		_texts->clear();
		delete _texts; _texts = NIL;
	}
	if (_separators != NIL) {
		Line *aSeparator = _separators->getFirst();
		while (aSeparator != NIL) {
			delete aSeparator;
			aSeparator = _separators->getNext();
		}
		_separators->clear();
		delete _separators; _separators = NIL;
	}
}

Figure* EditableFigure::born(Figure* ptr)
{
	EditableFigure *copied;
	if (ptr == NIL) {
		copied = new EditableFigure(NIL);
	} else {
		copied = (EditableFigure *)ptr;
	}
	copied->_initWidth = _initWidth;
	copied->_emptyGapX = _emptyGapX;
	copied->_gapX = _gapX;
	copied->_gapY = _gapY;
	copied->_moreGapAtTop = _moreGapAtTop;
	copied->_focus = NIL;
	copied->_texts = new SlaveryTextList();
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		SlaveryText *newText = (SlaveryText *)aText->born();
		newText->setMaster(copied);
		copied->_texts->insert(newText);
		aText = _texts->getNext();
	}
	copied->_separators = new LineList();
	Line *aLine = _separators->getFirst();
	while(aLine != NIL) {
		copied->_separators->insert((Line *)aLine->born());
		aLine = _separators->getNext();
	}
	return (NodeFigure::born((Figure *)copied));
}

int EditableFigure::textMaxWidth(int skip)
{
	int maxW = 0;
	int count = 0;
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		int textW = aText->content()->otherLinesMaxWidth(); 
		if (count != skip && maxW <= textW) {
			maxW = textW;
		}
		count++;
		aText = _texts->getNext();
	}
	return maxW;
}

void EditableFigure::modifyWidthPlus(int lineDX,int index)
{
	int maxW = textMaxWidth();
	if (lineDX <= maxW) return;
	if (lineDX+2*_gapX+_emptyGapX <= _initWidth) return;
	if (_shape->isTroublesomeToModifyObject() == TRUE) {
		_controller->erase(_shape);
	}
	int x1 = getX2()-_gapX; int x2 = getX1()+_emptyGapX+2*_gapX+lineDX;
	int y1 = getY1(); int y2 = getY2();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CRect tmp(x1,y1,x2,y2);
	dcp->FillRect(tmp,COODView::ShapeEraseBrush);
	_controller->OODReleaseDC(dcp,TRUE);
	modifyWidth(x2);
	_controller->draw(this);
}

void EditableFigure::findCoordToClear(int lineDX,int index,int &x1,int &y1,int &x2,int &y2,int &maxW,int &newW)
{
	maxW = textMaxWidth(index);
	newW = getX1()+_emptyGapX+2*_gapX+lineDX;
	if (newW >= getX2()) return;
	x1 = getX1()+_emptyGapX+2*_gapX+lineDX; x2 = getX2();
	y1 = getY1(); y2 = getY2();
}

void EditableFigure::setXY2FromContent()
{
	int maxX2 = 0;
	int maxY2 = 0;

	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->recalcCoordFromXY1();
		int x2 = aText->getX2();
		if (x2 > maxX2) maxX2 = x2;
		int y2 = aText->getY2();
		if (y2 > maxY2) maxY2 = y2;
		aText = _texts->getNext();
	}
	_shape->_x2.set(maxX2+_gapX);
	_shape->_y2.set(maxY2+_gapY);
}

void EditableFigure::modifyWidthMinus(int lineDX,int index)
{
	if (_shape->isTroublesomeToModifyObject() == TRUE) {
		_controller->erase(_shape);
	}
	int x1,y1,x2,y2;
	int maxW,newW;
	findCoordToClear(lineDX,index,x1,y1,x2,y2,maxW,newW);
	if (x1 != x2) {
		CRect tmp(_shape->getX1(),_shape->getY1(),
			_shape->getX2()+1,_shape->getY2()+1);
		_controller->invalidateRect(&tmp,TRUE);
	}
	int candidate1OfX2 = newW;
	int candidate2OfX2 = getX1()+_emptyGapX+2*_gapX+maxW;
	int candidate3OfX2 = getX1()+_initWidth;
	modifyWidth(GetMax(candidate1OfX2,candidate2OfX2,candidate3OfX2));
	// Invalidate 시키기때문에 draw() 할필요 없음
}

void EditableFigure::modifyWidth(int x2)
{
	Line *aLine = _separators->getFirst();
	while(aLine != NIL) {
		aLine->_x2.set(x2);
		aLine = _separators->getNext();
	}
	_shape->_x2.set(x2);
}

void EditableFigure::modifyHeight(int dy,int originalIndex)
{
	int nText = _texts->nOfList();
	int nSeparator = _separators->nOfList();

	// 이거는 클래스의 data member가 supress될 때 경우다.
	int index = originalIndex;
	if (nText <= originalIndex) {
		index = nText - 1;
	}

	int count = 0;
	SlaveryText * aText = _texts->getFirst();
	Line * aLine = _separators->getFirst();
	while (count < index) {
		count++;
		aText = _texts->getNext();
		aLine = _separators->getNext();
	}
	int x1 = getX1(); int x2 = getX2();
	int y1 = aText->getY1();
	int y2;
	if (dy > 0) {
		y2 = getY2() + dy;
	} else {
		y2 = getY2();
	}
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_ERASING);
	_controller->OnPrepareDC(dcp);
	CRect tmp(x1,y1,x2,y2);
	dcp->FillRect(tmp,COODView::ShapeEraseBrush);
	_controller->OODReleaseDC(dcp,TRUE);
	while(aLine != NIL) {
		aText = _texts->getNext();
		if (aText != NIL) {
			aText->_y1.set(aText->getY1() + dy);
			aText->_y2.set(aText->getY2() + dy);
			aLine->_y1.set(aLine->getY1() + dy);
			aLine->_y2.set(aLine->getY2() + dy);
		} else if (aText == NIL &&
			index == originalIndex) {
	// 이거는 클래스의 member function이 supress될 때 경우다.
			aLine->_y1.set(aLine->getY1() + dy);
			aLine->_y2.set(aLine->getY2() + dy);
		}
		aLine = _separators->getNext();
	}
	_shape->_y2.set(getY2()+dy);
	if (dy > 0) {
		CRect aRect(_shape->_x1.get(),_shape->_y1.get(),
				_shape->_x2.get()+1,_shape->_y2.get()+1);
		_controller->invalidateRect(&aRect);
	} else {
		CRect aRect(_shape->_x1.get(),_shape->_y1.get(),
				_shape->_x2.get()+1,_shape->_y2.get()-dy+1);
		_controller->invalidateRect(&aRect);
	}
}

int EditableFigure::getX1ForCentering()
{
	return _shape->getX1() + _emptyGapX;
}

int EditableFigure::widthForCentering()
{
	return width() - _emptyGapX;
}

BOOL EditableFigure::startEdit()
{
	if (_focus == NIL) return FALSE;
	if (_focus->whoAreYou()->isIn(WEARETEXTOBJECTS) == FALSE) return FALSE;
	_modifiedFlag = FALSE;
	((Text *)_focus)->startEdit();
	return TRUE;
}

void EditableFigure::setFocus(int x,int y)
{
	if (x == -OODMAXINT && y == -OODMAXINT) {
		_focus = _texts->getFirst();
		return;
	}
	int maxW = textMaxWidth() + _gapX + _emptyGapX;
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		CRgn *testRgn = _controller->makeRectRegion(aText->getX1(),aText->getY1(),maxW,aText->textHeight()*aText->deltaV());
		if (testRgn == NIL) break;
		if (!isEmptyRegion(testRgn) && testRgn->PtInRegion(x,y)) {
			delete testRgn;
			aText->setXY(x,y);
			_focus = aText;
			return;
		}
		delete testRgn;
		aText = _texts->getNext();
	}
	int x1 = getX1(); int y1 = getY1();
	int x2 = 0; int y2 = 0;
	int count = 0;
	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		x2 = aLine->getX2(); y2 = aLine->getY2();
		CRgn *testRgn = _controller->makeRectRegion(x1,y1,x2-x1,y2-y1);
		if (testRgn == NIL) break;
		if (!isEmptyRegion(testRgn) && testRgn->PtInRegion(x,y)) {
			delete testRgn;
			aText = _texts->at(count);
			_focus = aText;
			return;
		}
		delete testRgn;
		y1 = y2;
		count++;
		aLine = _separators->getNext();
	}
	_focus = _texts->getLast();
}

void EditableFigure::bye()
{
	if (_focus == NIL) return;
	if (_focus->whoAreYou()->isIn(WEARETEXTOBJECTS) == FALSE) return;
	((SlaveryText *)_focus)->bye();

	UnsignedLong *whoAmI = whoAreYou();
	if (whoAmI->equals(IAMSEQUENCEOBJECT)) return;

	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->extendToNodeFigure(this);
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->tailorEndLinesAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setModelSpecificSymbolAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->makeRegion(_controller->canvasRgn());
		ptr = _connections->getNext();
	}
	_controller->Invalidate();
}

SlaveryText *EditableFigure::nextText(SlaveryText* currentText)
{
	SlaveryText *aText = NIL;
	if (currentText == NIL) {
		aText = _texts->getFirst();
		_focus = (Figure *) aText;
		return aText;
	}
	SlaveryText *tmpText = _texts->getFirst();
	while (tmpText != NIL) {
		if (tmpText == currentText) {
			aText = _texts->getNext();
			break;
		}
		tmpText = _texts->getNext();
	}
	if (aText == NIL) {
		aText = _texts->getFirst();
	}
	_focus = (Figure *) aText;
	return aText;
}

SlaveryText *EditableFigure::prevText(SlaveryText* currentText)
{
	SlaveryText *aText = NIL;
	if (currentText == NIL) {
		aText = _texts->getFirst();
		_focus = (Figure *) aText;
		return aText;
	}
	SlaveryText *tmpText = _texts->getLast();
	while (tmpText != NIL) {
		if (tmpText == currentText) {
			aText = _texts->getBack();
			break;
		}
		tmpText = _texts->getBack();
	}
	if (aText == NIL) {
		aText = _texts->getLast();
	}
	_focus = (Figure *) aText;
	return aText;
}

void EditableFigure::drawBoundaryEx(CDC* dcp)
{
	NodeFigure::drawBoundary(dcp);
}

void EditableFigure::drawBoundary(CDC* dcp)
{
	if (_controller->currentFocus() == this &&
		_controller->editingTag() == TRUE) {
		NodeFigure::draw(dcp);
	} else {
		NodeFigure::draw(dcp);
	}

	CRect oldRect;
	if (!dcp->IsKindOf(RUNTIME_CLASS(CMetaFileDC))) {
		dcp->GetClipBox(&oldRect);
		dcp->IntersectClipRect(getX1(),getY1(),getX2(),getY2());
	}

	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->draw(dcp);
		aLine = _separators->getNext();
	}
	if (!dcp->IsKindOf(RUNTIME_CLASS(CMetaFileDC))) {
		dcp->SelectClipRgn(NULL,RGN_COPY);
		dcp->IntersectClipRect(&oldRect);
	}
}

void EditableFigure::makeRegion(CRgn *sourceClipRgn)
{
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->makeRegion(sourceClipRgn);
		aText = _texts->getNext();
	}
	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->makeRegion(sourceClipRgn);
		aLine = _separators->getNext();
	}
	NodeFigure::makeRegion(sourceClipRgn);
}

void EditableFigure::resetRegion()
{
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->resetRegion();
		aText = _texts->getNext();
	}
	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->resetRegion();
		aLine = _separators->getNext();
	}
	NodeFigure::resetRegion();
}

void EditableFigure::releaseRegion()
{
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->releaseRegion();
		aText = _texts->getNext();
	}
	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->releaseRegion();
		aLine = _separators->getNext();
	}
	NodeFigure::releaseRegion();
}

BOOL EditableFigure::needCentering()
{
	if (_controller->editingTag() == TRUE &&
		_controller->currentFocus() == this &&
		_texts->inList((SlaveryText *)_focus) == TRUE) {
		return FALSE;
	} else {
		return TRUE;
	}
}

void EditableFigure::setController(COODView *ptr)
{
	NodeFigure::setController(ptr);

	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->setController(ptr);
		aText = _texts->getNext();
	}

	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->setController(ptr);
		aLine = _separators->getNext();
	}
}

void EditableFigure::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	if (_controller->currentFocus() == this &&
		_controller->editingTag() == TRUE) {
		NodeFigure::draw(dcp);
	} else {
		NodeFigure::draw(dcp);
	}

	CRect oldRect;
	if (!dcp->IsKindOf(RUNTIME_CLASS(CMetaFileDC))) { 
		dcp->GetClipBox(&oldRect);
		dcp->IntersectClipRect(getX1(),getY1(),getX2(),getY2());
	}
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->draw(dcp);
		aText = _texts->getNext();
	}

	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->draw(dcp);
		aLine = _separators->getNext();
	}
	if (!dcp->IsKindOf(RUNTIME_CLASS(CMetaFileDC))) {
		dcp->SelectClipRgn(NULL,RGN_COPY);
		dcp->IntersectClipRect(&oldRect);
	}
}

void EditableFigure::drawOnMetaFile(CDC* dcp)
{
	if (!_inCanvas) return;
	NodeFigure::draw(dcp);

	CRect oldRect;
	dcp->GetClipBox(&oldRect);
	int nSavedDC = dcp->SaveDC();
	dcp->IntersectClipRect(getX1(),getY1(),getX2(),getY2());

	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->draw(dcp);
		aText = _texts->getNext();
	}

	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->draw(dcp);
		aLine = _separators->getNext();
	}
	dcp->RestoreDC(nSavedDC);
}

void EditableFigure::move(CDC* dcp,int dx,int dy)
{
	int x1 = getX1();
	int y1 = getY1();
	int x2 = getX2();
	int y2 = getY2();

	NodeFigure::move(dcp,dx,dy);
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->moveCoord(dx,dy);
		aText = _texts->getNext();
	}

	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		int cx,cy;
		aLine->center(cx,cy);
		if (cx < x2 && cx > x1 && cy < y2 && cy > y1) {
			aLine->move(dcp,dx,dy);
		} else {
			aLine->moveCoord(dx,dy);
		}
		aLine = _separators->getNext();
	}
}

void EditableFigure::moveCoord(int dx,int dy)
{
	NodeFigure::moveCoord(dx,dy);
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->moveCoord(dx,dy);
		aText = _texts->getNext();
	}
	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->moveCoord(dx,dy);
		aLine = _separators->getNext();
	}
}

void EditableFigure::moveCoordForScroll(int dx,int dy)
{
	NodeFigure::moveCoordForScroll(dx,dy);
	SlaveryText *aText = _texts->getFirst();
	while (aText != NIL) {
		aText->moveCoord(dx,dy);
		aText = _texts->getNext();
	}
	Line *aLine = _separators->getFirst();
	while (aLine != NIL) {
		aLine->moveCoord(dx,dy);
		aLine = _separators->getNext();
	}
}

int EditableFigure::getName(char *buffer,int bufSize)
{
	if (_texts->getFirst() == NIL) return 0;
	return _texts->getFirst()->getName(buffer,bufSize);
}