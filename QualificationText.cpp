// QualificationText.cpp: implementation of the QualificationText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "QualificationText.h"
#include "Box.h"
#include "Association.h"
#include "COODView.h"
#include "Line.h"
#include "AnytionInfoTuple.h"
#include "TextContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define BOX_GAP_X	(5)
#define BOX_GAP_Y	(2)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(QualificationText,TupleText,1)

QualificationText::QualificationText()
: TupleText()
{
	_whichSide = 0;
	_boundary = NIL;
}

QualificationText::QualificationText(COODView *controller,Connection *connectionPtr,int whichSide,int ox,int oy,Popup *popup)
: TupleText(controller,connectionPtr,ox,oy,popup)
{
	_whichSide = whichSide;
	_boundary = NIL;
	if (controller == NIL) return;
	int height = controller->fontHeight();
	if (_whichSide == NORTH) {
		_x1.set(ox);
		_y1.set(oy-height-BOX_GAP_Y);
		_x2.set(ox);
		_y2.set(oy-BOX_GAP_Y);
		_boundary = new Box(controller,ox-BOX_GAP_X,oy-height-2*BOX_GAP_Y,
									   ox+BOX_GAP_X,oy,NIL);
	} else if (_whichSide == EAST) {
		_x1.set(ox+BOX_GAP_X);
		_y1.set(oy-height/2);
		_x2.set(ox+BOX_GAP_X);
		_y2.set(oy+height/2);
		_boundary = new Box(controller,ox,oy-height/2-BOX_GAP_Y,
									   ox+2*BOX_GAP_X,oy+height/2+BOX_GAP_Y,NIL);
	} else if (_whichSide == SOUTH) {
		_x1.set(ox);
		_y1.set(oy+BOX_GAP_Y);
		_x2.set(ox);
		_y2.set(oy+height+BOX_GAP_Y);
		_boundary = new Box(controller,ox-BOX_GAP_X,oy,
									   ox+BOX_GAP_X,oy+height+2*BOX_GAP_Y,NIL);
	} else if (_whichSide == WEST) {
		_x1.set(ox-BOX_GAP_X);
		_y1.set(oy-height/2);
		_x2.set(ox-BOX_GAP_X);
		_y2.set(oy+height/2);
		_boundary = new Box(controller,ox-2*BOX_GAP_X,oy-height/2-BOX_GAP_Y,
									   ox,oy+height/2+BOX_GAP_Y,NIL);
	}
	if (_boundary != NIL) {
		_boundary->filled() = TRUE;
		_boundary->setBackground(theAppPtr->shapeBackgroundColor);
		_boundary->invalidate();
	}
}

QualificationText::~QualificationText()
{
	if (_boundary != NIL) {
		delete _boundary; _boundary = NIL;
	}
}

void QualificationText::Serialize(CArchive& ar)
{
	TupleText::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _whichSide << _boundary;
	} else {
		ar >> (LONG&) _whichSide >> _boundary;
	}
}

Figure* QualificationText::born(Figure* ptr)
{
	QualificationText *copied;
	if (ptr == NIL) {
		copied = new QualificationText(NIL,NIL,0,0,0,NIL);
	} else {
		copied = (QualificationText *)ptr;
	}
	copied->_whichSide = _whichSide;
	return (TupleText::born((Figure *)copied));
}

UnsignedLong *QualificationText::whoAreYou()
{
	// 이거는 OneLineText 부류에 넣으면 절대 안된다. 
	return IAMQUALIFICATIONTEXT; 
}

void QualificationText::recalcCoordFromTuplePointXY(int tupleX,int tupleY)
{
	int width = _x2.get() - _x1.get();
	int height = _y2.get() - _y1.get();
	if (_whichSide == NORTH) {
		_x1.set(tupleX-width/2);
		_y1.set(tupleY-height-BOX_GAP_Y);
		recalcCoordFromXY1();
	} else if (_whichSide == EAST) {
		_x1.set(tupleX+BOX_GAP_X);
		_y1.set(tupleY-height/2);
		recalcCoordFromXY1();
	} else if (_whichSide == SOUTH) {
		_x1.set(tupleX-width/2);
		_y1.set(tupleY+BOX_GAP_Y);
		recalcCoordFromXY1();
	} else if (_whichSide == WEST) {
		_x1.set(tupleX-width-BOX_GAP_X);
		_y1.set(tupleY-height/2);
		recalcCoordFromXY1();
	}
	_boundary->_x1.x = _x1.x - BOX_GAP_X;
	_boundary->_y1.y = _y1.y - BOX_GAP_Y;
	_boundary->_x2.x = _x2.x + BOX_GAP_X;
	_boundary->_y2.y = _y2.y + BOX_GAP_Y;
	makeRegion(_controller->canvasRgn());
}

void QualificationText::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	if (_boundary != NIL) {
		_boundary->draw(dcp);
	}
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) return;
	TupleText::draw(dcp);
}

void QualificationText::drawBoundary(CDC* dcp)
{
	if (_boundary != NIL) {
		_boundary->drawBoundary(dcp);
	}
}

void QualificationText::eraseDots(CDC* dcp)
{
	if (_boundary != NIL) {
		_boundary->eraseDots(dcp);
	}
}

void QualificationText::drawDots(CDC* dcp)
{
	if (_boundary != NIL) {
		_boundary->drawDots(dcp);
	}
}

void QualificationText::clear(CDC* dcp)
{
	if (_boundary != NIL) {
		_boundary->clear(dcp);
	}
}

void QualificationText::makeRegion(CRgn *sourceClipRgn)
{
	if (_boundary != NIL) {
		_boundary->makeRegion(sourceClipRgn);
	}
	TupleText::makeRegion(sourceClipRgn);
}

void QualificationText::resetRegion()
{
	if (_boundary != NIL) {
		_boundary->resetRegion();
	}
	TupleText::resetRegion();
}

void QualificationText::releaseRegion()
{
	if (_boundary != NIL) {
		_boundary->releaseRegion();
	}
	TupleText::releaseRegion();
}

void QualificationText::moveCoord(int dx,int dy)
{
	if (_boundary != NIL) {
		_boundary->moveCoord(dx,dy);
	}
	TupleText::moveCoord(dx,dy);
}

void QualificationText::move(CDC* dcp,int dx,int dy)
{
	if (_boundary != NIL) {
		_boundary->move(dcp,dx,dy);
	}
	TupleText::moveCoord(dx,dy);
}

void QualificationText::setInCanvas(BOOL flag)
{
	if (_boundary != NIL) {
		_boundary->setInCanvas(flag);
	}
	TupleText::setInCanvas(flag);
}

void QualificationText::setController(COODView *ptr)
{
	TupleText::setController(ptr);
	if (_boundary != NIL) {
		_boundary->setController(ptr);
	}
}

BOOL QualificationText::onEnter(int x,int y)
{
	if (_boundary != NIL) {
		return _boundary->onEnter(x,y);
	}
	return TupleText::onEnter(x,y);
}

BOOL QualificationText::wantToMove(int,int)
{
	return FALSE;
}

void QualificationText::adjustXCoord(int newWidth)
{
	int ox = _tuplePtr->getX();
	int oy = _tuplePtr->getY();
	// 바운더리가 작아지는 경우
	_boundary->invalidate();
	if (_whichSide == NORTH) {
		_x1.set(ox-newWidth/2);
		_x2.set(ox+newWidth/2);
	} else if (_whichSide == EAST) {
		_x1.set(ox+BOX_GAP_X);
		_x2.set(ox+BOX_GAP_X+newWidth);
	} else if (_whichSide == SOUTH) {
		_x1.set(ox-newWidth/2);
		_x2.set(ox+newWidth/2);
	} else if (_whichSide == WEST) {
		_x1.set(ox-BOX_GAP_X-newWidth);
		_x2.set(ox-BOX_GAP_X);
	}
	_boundary->_x1.x = _x1.x - BOX_GAP_X;
	_boundary->_x2.x = _x2.x + BOX_GAP_X;
	// 바운더리가 커지는 경우
	_boundary->invalidate();
}

void QualificationText::adjustYCoord(int newHeight)
{
	int ox = _tuplePtr->getX();
	int oy = _tuplePtr->getY();
	// 바운더리가 작아지는 경우
	_boundary->invalidate();
	if (_whichSide == NORTH) {
		_y1.set(oy-BOX_GAP_Y-newHeight);
		_y2.set(oy-BOX_GAP_Y);
	} else if (_whichSide == EAST) {
		_y1.set(oy-newHeight/2);
		_y2.set(oy+newHeight/2);
	} else if (_whichSide == SOUTH) {
		_y1.set(oy+BOX_GAP_Y);
		_y2.set(oy+newHeight+BOX_GAP_Y);
	} else if (_whichSide == WEST) {
		_y1.set(oy-newHeight/2);
		_y2.set(oy+newHeight/2);
	}
	_boundary->_y1.y = _y1.y - BOX_GAP_Y;
	_boundary->_y2.y = _y2.y + BOX_GAP_Y;
	_boundary->invalidate();
}

int QualificationText::insert(char* keypressed)
{
	int lineDX = TupleText::insert(keypressed);
	if (lineDX == -1) return 0;
	if (_content->otherLinesMaxWidth() < lineDX) {
		adjustXCoord(lineDX);
	}
	return lineDX;
}

void QualificationText::goNextLine()
{
	if (_maxLines > 0 && textHeight() >= _maxLines) {
		return;
	}
	TupleText::goNextLine();
	adjustYCoord(textHeight()*deltaV());
	int lineDX = _content->otherLinesMaxWidth();
	adjustXCoord(lineDX);
}

BOOL QualificationText::delChar()
{
	if (_content->valueAt(_cursorX,_cursorY) == '\0') return TRUE;
	if (Text::delChar()) return TRUE;
	int lineDX = _content->otherLinesMaxWidth();
	adjustXCoord(lineDX);
	return FALSE;
}

BOOL QualificationText::delLine()
{
	if (textHeight() == 1 && _content->valueAt(0,0) == '\0') {
		 return TRUE;
	}
	if (Text::delLine()) {
		adjustXCoord(0);
		return TRUE;
	}
	adjustYCoord(textHeight()*deltaV());
	int lineDX = _content->otherLinesMaxWidth();
	adjustXCoord(lineDX);
	return FALSE;
}

BOOL QualificationText::delCharBack()
{
	if (_cursorX == 0) return TRUE;
	if (Text::delCharBack()) return TRUE;
	int lineDX = _content->otherLinesMaxWidth();
	adjustXCoord(lineDX);
	return FALSE;
}

void QualificationText::bye()
{
	Text::bye();
	delEmptyLines();
	_boundary->invalidate();
}

int QualificationText::delEmptyLines()
{
	TupleText::delEmptyLines();
	adjustYCoord(textHeight()*deltaV());
	int lineDX = _content->otherLinesMaxWidth();
	adjustXCoord(lineDX);
	return 0;
}
