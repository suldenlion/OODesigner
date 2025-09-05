// State.cpp: implementation of the State class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "State.h"
#include "COODView.h"
#include "RoundBoxB.h"
#include "Line.h"
#include "LineList.h"
#include "StateText.h"
#include "SlaveryTextList.h"
#include "UnsignedLong.h"
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
IMPLEMENT_SERIAL(State,EditableFigure,1)

State::State()
: EditableFigure()
{
	_popup = theAppPtr->theStatePopup;

	_savedSeparator = NIL;
	_savedY1PosOfNameText = -OODMAXINT;
	_savedY2PosOfNameText = -OODMAXINT;
}

State::State(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	_savedSeparator = NIL;
	_savedY1PosOfNameText = -OODMAXINT;
	_savedY2PosOfNameText = -OODMAXINT;
	_popup = popup;
	_initWidth = STATE_INIT_WIDTH;
	_gapX = XGAP_STATE;
	_gapY = YGAP_STATE;
	if (controller == NIL) return;
	_shape = new RoundBoxB(controller,ox,oy,ox+_initWidth,oy+4*_gapY+2*deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	setBackground(theAppPtr->shapeBackgroundColor);
	_texts->insert(new StateText(controller,this,IAMSTATENAME,ox+_gapX,oy+_gapY));
	_texts->insert(new StateText(controller,this,IAMACTIVITYSTRING,ox+_gapX,oy+3*_gapY+deltaV));
	_separators->insert(new Line(controller,ox,oy+2*_gapY+deltaV,ox+_initWidth,oy+2*_gapY+deltaV,NIL,STRAIGHT));
}

State::~State()
{
	if (_savedSeparator != NIL) {
		delete _savedSeparator;
		_savedSeparator = NIL;
	}
}

void State::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);   
	if (ar.IsStoring()) {
		ar << _savedSeparator;
		ar << (LONG) _savedY1PosOfNameText << (LONG) _savedY2PosOfNameText;
	} else {
		ar >> _savedSeparator;
		ar >> (LONG&) _savedY1PosOfNameText >> (LONG&) _savedY2PosOfNameText;
	}
}

Figure* State::born(Figure* ptr)
{
	State *copied;
	if (ptr == NIL) {
		copied = new State(NIL,0,0,0,NIL);
	} else {
		copied = (State *)ptr;
	}
	copied->_savedY1PosOfNameText = _savedY1PosOfNameText;
	copied->_savedY2PosOfNameText = _savedY2PosOfNameText;
	return (EditableFigure::born((Figure *)copied));
}

BOOL State::startEdit()
{
	if (_focus == NIL) return FALSE;
	if (_focus->whoAreYou()->isIn(WEARETEXTOBJECTS) == FALSE) return FALSE;
	_modifiedFlag = FALSE;
	if (_savedSeparator != NIL) {
		_separators->insert(_savedSeparator);
		_savedSeparator = NIL;
		SlaveryText *nameText = _texts->getFirst();
		nameText->_y1.y = _savedY1PosOfNameText;
		nameText->_y2.y = _savedY2PosOfNameText;
		_savedY1PosOfNameText = -OODMAXINT;
		_savedY2PosOfNameText = -OODMAXINT;
		_controller->clear(this);
	}
	((StateText *)_focus)->startEdit();
	return TRUE;
}

void State::bye()
{
	if (_focus == NIL) return;
	if (_focus->whoAreYou()->isIn(WEARETEXTOBJECTS) == FALSE) return;
	if (_texts->nOfList() <= 1) return;
	((StateText *)_focus)->bye();
	SlaveryText *activityText = _texts->getFirst();
	activityText = _texts->getNext();
	if (activityText->textHeight() == 1 &&
		activityText->content()->valueAt(0,0) == '\0') {
		_savedSeparator = _separators->getFirst();
		_separators->clear();
		SlaveryText *nameText = _texts->getFirst();
		_savedY1PosOfNameText = nameText->_y1.y;
		_savedY2PosOfNameText = nameText->_y2.y;
		int nameHeight = nameText->textHeight() * nameText->deltaV();
		int thisHeight = _shape->_y2.get() - _shape->_y1.get();
		int newY = _shape->_y1.get() + (thisHeight - nameHeight) / 2;
		nameText->_y1.set(newY);
		nameText->_y2.set(newY);
	}
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

UnsignedLong* State::whoAreYou()
{
	return IAMSTATE;
}

void State::moveCoord(int dx,int dy)
{
	EditableFigure::moveCoord(dx,dy);
	if (_savedSeparator != NIL) {
		_savedSeparator->moveCoord(dx,dy);
		_savedY1PosOfNameText = _savedY1PosOfNameText + dy;
		_savedY2PosOfNameText = _savedY2PosOfNameText + dy;
	}
}

void State::setController(COODView *ptr)
{
	EditableFigure::setController(ptr);
	if (_savedSeparator != NIL) {
		_savedSeparator->setController(ptr);
	}
}

void State::move(CDC* dcp,int dx,int dy)
{
	EditableFigure::move(dcp,dx,dy);
	if (_savedSeparator != NIL) {
		_savedSeparator->moveCoord(dx,dy);
		_savedY1PosOfNameText = _savedY1PosOfNameText + dy;
		_savedY2PosOfNameText = _savedY2PosOfNameText + dy;
	}
}

void State::draw(CDC* dcp)
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

void State::drawOnMetaFile(CDC* dcp)
{
	if (!_inCanvas) return;
	EditableFigure::drawOnMetaFile(dcp);
}
