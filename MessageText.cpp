// MessageText.cpp: implementation of the MessageText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "MessageText.h"
#include "Line.h"
#include "COODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MESSAGE_ARROW_LENGTH	(50)
#define ARROW_DELTA_FROM_TEXT	(8)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(MessageText,ConnectionText,1)

MessageText::MessageText()
: ConnectionText()
{
	_popup = theAppPtr->theMessageTextPopup;

	_arrow = NIL;
	_arrowAt = 0;
	_arrowDir = NORMAL_DIR;
}

MessageText::MessageText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: ConnectionText(controller,connectionPtr,ox,oy,popup)
{
	_arrow = NIL;
	if (controller == NIL) return;
	_arrow = new Line(controller,0,0,0,0,NIL,STRAIGHT);
	_arrowAt = 0;
	_arrowDir = NORMAL_DIR;
}

MessageText::~MessageText()
{
	if (_arrow != NIL) {
		delete _arrow; _arrow = NIL;
	}
}

void MessageText::Serialize(CArchive& ar)
{
	ConnectionText::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _arrowAt << (LONG) _arrowDir;
		ar << _arrow;
	} else {
		ar >> (LONG&) _arrowAt >> (LONG&) _arrowDir;
		ar >> _arrow;
	}
}

UnsignedLong *MessageText::whoAreYou()
{
	return IAMMESSAGETEXT; 
}

Figure* MessageText::born(Figure* ptr)
{
	MessageText *copied;
	if (ptr == NIL) {
		copied = new MessageText(NIL,NIL,0,0,NIL);
	} else {
		copied = (MessageText *)ptr;
	}
	copied->_arrow = (Line *)_arrow->born();
	copied->_arrowAt = _arrowAt;
	copied->_arrowDir = _arrowDir;
	return (ConnectionText::born((Figure *)copied));
}

void MessageText::epilog(BOOL skipflag)
{
	ConnectionText::epilog(skipflag);
	if (skipflag) return;
	recalcArrowCoord();
}

void MessageText::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	ConnectionText::draw(dcp);
	if (_arrow != NIL) _arrow->draw(dcp);
}

void MessageText::setController(COODView* ptr)
{
	ConnectionText::setController(ptr);
	if (_arrow != NIL) _arrow->setController(ptr);
}

void MessageText::bye()
{
	ConnectionText::bye();
	clearArrow();
	recalcArrowCoord();
}

void MessageText::recalcArrowCoord()
{
	int x1 = getX1(); int y1 = getY1();
	int x2 = getX2(); int y2 = getY2();
	if (_arrowAt == ARROW_AT_TOP) {
		int ax1 = x1 + (x2-x1)/2 - MESSAGE_ARROW_LENGTH/2;
		int ax2 = ax1 + MESSAGE_ARROW_LENGTH;
		int ay = y1 - ARROW_DELTA_FROM_TEXT;
		_arrow->setXY1(ax1,ay);
		_arrow->setXY2(ax2,ay);
	} else if (_arrowAt == ARROW_AT_RIGHT) {
		int ax = x2 + ARROW_DELTA_FROM_TEXT;
		int ay1 = y1 + (y2-y1)/2 - MESSAGE_ARROW_LENGTH/2;
		int ay2 = ay1 + MESSAGE_ARROW_LENGTH;
		_arrow->setXY1(ax,ay1);
		_arrow->setXY2(ax,ay2);
	} else if (_arrowAt == ARROW_AT_BOTTOM) {
		int ax1 = x1 + (x2-x1)/2 - MESSAGE_ARROW_LENGTH/2;
		int ax2 = ax1 + MESSAGE_ARROW_LENGTH;
		int ay = y2 + ARROW_DELTA_FROM_TEXT;
		_arrow->setXY1(ax1,ay);
		_arrow->setXY2(ax2,ay);
	} else { // ARROW_AT_LEFT
		int ax = x1 - ARROW_DELTA_FROM_TEXT;
		int ay1 = y1 + (y2-y1)/2 - MESSAGE_ARROW_LENGTH/2;
		int ay2 = ay1 + MESSAGE_ARROW_LENGTH;
		_arrow->setXY1(ax,ay1);
		_arrow->setXY2(ax,ay2);
	}
	_arrow->setDir(_arrowDir,HEADARROW1);
}

void MessageText::clear(CDC* dcp)
{
	ConnectionText::clear(dcp);
	clearArrow();
}

void MessageText::clearArrow()
{
	if (isEmpty()) return;
	int x1 = _arrow->getX1(); int y1 = _arrow->getY1();
	int x2 = _arrow->getX2(); int y2 = _arrow->getY2();
	if (x1 == x2) {
		CRect tmp(x1-10,y1,x2+10,y2);
		_controller->invalidateRect(&tmp);
	} else if (y1 == y2) {
		CRect tmp(x1,y1-10,x2,y2+10);
		_controller->invalidateRect(&tmp);
	}
}

void MessageText::invertArrow()
{
	clearArrow();
	_arrow->invertDir();
	if (_arrowDir == NORMAL_DIR)
		_arrowDir = INVERT_DIR;
	else
		_arrowDir = NORMAL_DIR;
	_controller->draw(_arrow);
}

void MessageText::shiftArrow()
{
	clearArrow();
	if (_arrowAt == ARROW_AT_TOP) {
		_arrowAt = ARROW_AT_RIGHT;
	} else if (_arrowAt == ARROW_AT_RIGHT) {
		_arrowAt = ARROW_AT_BOTTOM;
	} else if (_arrowAt == ARROW_AT_BOTTOM) {
		_arrowAt = ARROW_AT_LEFT;
	} else { // ARROW_AT_LEFT
		_arrowAt = ARROW_AT_TOP;
	}
	recalcArrowCoord();
	_controller->draw(_arrow);
}
