#include "stdafx.h"
/* Text.C */

#include "Text.h"
// Super Class : Box

/*oodB%Text*** Global Declarations and Stuffs ****/
#include "COODView.h" // Collaboration
#include "TextLine.h" // Collaboration
#include "TextContent.h" // Aggregation
#include "VTerm.h" // Aggregation
#include "FontInfo.h"
#include "UnsignedLong.h"
char Text::LeadByte = '\0';
/*oodE********************************************/

IMPLEMENT_SERIAL(Text,Box,1)

int Text::getCursorIndexBefore(CDC *dcp,int maxVal)
{
	char *s = currentLine.ptrAt(0);
	if (strlen(s) == 0) return 0;
	int index = 0;
	char saveChar = '\0';
	char *ptr = s;
	while (*ptr != '\0') {
		if (isLeadByte(*ptr)) {
			index = index+2;
			saveChar = *(ptr+2);
			*(ptr+2) = '\0';
			CSize sz = dcp->GetTextExtent(s,strlen(s));
			*(ptr+2) = saveChar;
			int newPos = sz.cx;
			if (newPos >= maxVal) {
				return (index-2);
			}
			ptr = ptr+2;
		} else {
			index++;
			saveChar = *(ptr+1);
			*(ptr+1) = '\0';
			CSize sz = dcp->GetTextExtent(s,strlen(s));
			*(ptr+1) = saveChar;
			int newPos = sz.cx;
			if (newPos >= maxVal) {
				return (index-1);
			}
			ptr++;
		}
	}
	return 0;
}

int Text::getCursorPosFrom0(CDC *dcp,int maxVal)
{
	_cursorX = 0;
	char *s = currentLine.ptrAt(0);
	if (strlen(s) == 0) return 0;
	int pos = 0;
	char saveChar = '\0';
	char *ptr = s;
	while (*ptr != '\0') {
		if (isLeadByte(*ptr)) {
			_cursorX = _cursorX+2;
			saveChar = *(ptr+2);
			*(ptr+2) = '\0';
			CSize sz = dcp->GetTextExtent(s,strlen(s));
			*(ptr+2) = saveChar;
			int newPos = sz.cx;
			if (newPos == maxVal) {
				return newPos;
			} else if (newPos > maxVal) {
				_cursorX = _cursorX-2;
				return pos;
			}
			pos = newPos;
			ptr = ptr+2;
		} else {
			_cursorX++;
			saveChar = *(ptr+1);
			*(ptr+1) = '\0';
			CSize sz = dcp->GetTextExtent(s,strlen(s));
			*(ptr+1) = saveChar;
			int newPos = sz.cx;
			if (newPos == maxVal) {
				return newPos;
			} else if (newPos > maxVal) {
				_cursorX--;
				return pos;
			}
			pos = newPos;
			ptr++;
		}
	}
	return pos;
}

int Text::getCursorPosFrom0ToEnd(CDC *dcp)
{
	CSize s = dcp->GetTextExtent(currentLine.ptrAt(0),strlen(currentLine.ptrAt(0)));
	int pos = s.cx;
	return pos;
}

void Text::setX2(CDC *dcp)
{
	CSize s = dcp->GetTextExtent(currentLine.ptrAt(0),strlen(currentLine.ptrAt(0)));
	int newdx = s.cx;
	if (_content->otherLinesMaxWidth() < newdx) {
		_x2.set(_x1.get()+newdx);
	}
}

void Text::setX2AsOtherLinesMaxWidth(CDC *dcp)
{
	int maxWidth = _content->setAllLinesMaxWidth(dcp);
	_x2.x = _x1.x + maxWidth;
}

void Text::setBoldFont(BOOL boldFlag)
{
	if (_fontInfo == NIL) return;
	_fontInfo->boldFlag = boldFlag;
	if (boldFlag == TRUE) {
		_fontInfo->weight = FW_BOLD;
	} else {
		_fontInfo->weight = FW_NORMAL;
	}
}

void Text::setItalicFont(BOOL italicFlag)
{
	if (_fontInfo == NIL) return;
	_fontInfo->italicFlag = italicFlag;
}

void Text::setUnderlineFont(BOOL underlineFlag)
{
	if (_fontInfo == NIL) return;
	_fontInfo->underlineFlag = underlineFlag;
}

CFont* Text::createFont()
{
	if (_font != NIL) return _font;
	_font = new CFont();
	_font->CreateFont(_fontInfo->size,0,0,0,
		_fontInfo->weight,_fontInfo->italicFlag,
		_fontInfo->underlineFlag,_fontInfo->strikeOutFlag,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,_fontInfo->faceName);
	return _font;
}

void Text::releaseFont()
{
	if (_font != NIL) {
		delete _font; _font = NIL;
	}
}


void Text::setXY(int pointX,int pointY)
{
	int dx = pointX - _x1.get();
	int dy = pointY - _y1.get();
	_cursorY = dy / deltaV();
	_cursorX = 0;
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	currentLine.copy(_content->lineAt(_cursorY));
	int cursorDX = getCursorPosFrom0(dcp,dx);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
	_vterm->set(cursorDX,_cursorY*deltaV());
}

int Text::nOfLines()
{
	return _content->nOfLines();
}

int Text::textHeight() {
	// character dimension
	return nOfLines();
}

int Text::textWidth() {
	// character dimension
	return _content->stringWidth();
}

BOOL Text::checkBuffer()
{
	if (_cursorX >= LINEBUFSIZ-2) return KTGNOTOK;
	if (_content->lineAt(_cursorY)->getLength() >= LINEBUFSIZ-2) return KTGNOTOK;
	return KTGOK;
}

void Text::deleteTextContent()
{
	if (_content != NIL) {
		delete _content; _content = NIL;
	}
}

Text::~Text()
{
	if (_vterm != NIL) {
		delete _vterm;	_vterm = NIL;
	}
	if (_content != NIL) {
		delete _content; _content = NIL;
	}
	if (_fontInfo != NIL) {
		delete _fontInfo; _fontInfo = NIL;
	}
	if (_font != NIL) {
		delete _font; _font = NIL;
	}
}

Text::Text()
: Box()
{
	_cursorX = 0;
	_cursorY = 0;
	xscale = 1.0;
	yscale = 1.0;
	sxscale = -1.0;
	syscale = -1.0;
	_font = NIL;
	_maxLines = -1;
	_autoDelete = TRUE;
	_fontInfo = NIL;
	_fontHeight = 0;
	_content = NIL;
	_vterm = NIL;
}

Text::Text(COODView *controller,int ox,int oy,Popup *popup)
: Box(controller,ox,oy,popup)
{
	_cursorX = 0;
	_cursorY = 0;
	xscale = 1.0;
	yscale = 1.0;
	sxscale = -1.0;
	syscale = -1.0;
	_font = NIL;
	_maxLines = -1;
	_autoDelete = TRUE;
	_content = NIL;
	if (controller == NIL) return;
	_fontInfo = new FontInfo();
	_fontInfo->copy(controller->fontInfo());
	_fontHeight = controller->fontHeight();
	_content = new TextContent();
	_content->newLineAt(0,whoAreYou());
	_vterm = new VTerm(this);
	_x2.set(_x1.get());
	_y2.set(_y1.get() + _fontHeight);
}

void Text::Serialize(CArchive& ar)
{
	Box::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _cursorX << (LONG) _cursorY;
		ar << (DOUBLE) xscale << (DOUBLE) yscale;
		ar << (DOUBLE) sxscale << (DOUBLE) syscale;
		ar << (LONG) _maxLines << (BYTE) _autoDelete;
		ar << _fontInfo << (LONG) _fontHeight;
		ar << _content << _vterm;
	} else {
		ar >> (LONG&) _cursorX >> (LONG&) _cursorY;
		ar >> (DOUBLE&) xscale >> (DOUBLE&) yscale;
		ar >> (DOUBLE&) sxscale >> (DOUBLE&) syscale;
		ar >> (LONG&) _maxLines >> (BYTE&) _autoDelete;
		ar >> _fontInfo >> (LONG&) _fontHeight;
		ar >> _content >> _vterm;
	}
}

void Text::setTextContent(TextContent *newContent)
{
	if (newContent == NIL) return;
	_content = newContent;
}

void Text::setString(const char *str)
{
	if (_content == NIL) {
		_content = new TextContent();
	}
	TextLine *firstLine = NIL;
	if (_content->nOfLines() == 0) {
		firstLine = _content->newLineAt(0,whoAreYou());
	} else {
		firstLine = _content->lineAt(0);
	}
	firstLine->setString(str);
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	setX2AsOtherLinesMaxWidth(dcp);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
	_y2.set(_y1.get()+textHeight()*deltaV());
	makeRegion(_controller->canvasRgn());
}

void Text::recalcCoordFromRealXY1(COODView* controller)
{
	int x = _x1.x;
	int y = _y1.y;
	recalcCoordFromRealXY1(controller,x,y);
}

void Text::recalcCoordFromRealXY1(COODView* controller,int x,int y)
{
	if (controller == NIL) return;
	_x1.x = x; _y1.y = y;
	createFont();
	CDC *dcp = controller->GetDC();
	controller->setDrawingContext(KTG_DRAWING);
	controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	setX2AsOtherLinesMaxWidth(dcp);
	dcp->SelectObject(oldFont);
	controller->OODReleaseDC(dcp,TRUE);
	_y2.y = _y1.y + textHeight()*deltaV();
	makeRegion(_controller->canvasRgn());
}

void Text::recalcCoordFromXY1()
{
	int x = _x1.get();
	int y = _y1.get();
	recalcCoordFromXY1(x,y);
}

void Text::recalcCoordFromXY1(int x,int y)
{
	_x1.set(x); _y1.set(y);
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	setX2AsOtherLinesMaxWidth(dcp);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
	_y2.set(_y1.get()+textHeight()*deltaV());
	makeRegion(_controller->canvasRgn());
}

void Text::normalize()
{
	xscale = 1.0;
	yscale = 1.0;
}

BOOL Text::isEmpty()
{
	if (textHeight() == 1 && _content->valueAt(0,0) == '\0') return TRUE;
	return FALSE;
}

BOOL Text::isObsolete()
{
	return (_autoDelete && isEmpty());
}

void Text::setScale(double fx,double fy)
{
}

BOOL Text::checkNear(int,int)
{
	return FALSE;
}

void Text::clear(CDC* dcp)
{
	int w = _x2.get() - _x1.get();
	int h = _y2.get() - _y1.get();
	if (w == 0 || h == 0) return;
	_controller->clearArea(_x1.get(),_y1.get(),w,h);
}

void Text::drawLinesFrom(CDC* dcp,int lineNo)
{
	int x = getX1();
	int y = getY1();
	TextLine *aLine = _content->getFirst();
	for (int i = 0; i < lineNo; i++) {
		y = y + _fontHeight;
		aLine = _content->getNext();
	}
	while(aLine != NIL) {
		char *ptr = aLine->ptrAt(0);
		dcp->TextOut(x,y,ptr,strlen(ptr));
		y = y + _fontHeight;
		aLine = _content->getNext();
	}
}

void Text::drawBoundary(CDC* dcp)
{
	Box::draw(dcp);
}

void Text::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	createFont();
	CFont *oldFont = dcp->SelectObject(_font);
	drawLinesFrom(dcp,0);
	dcp->SelectObject(oldFont);
	releaseFont();
}

void Text::recalcWidthHeight(BOOL setCarretWH)
{
}

BOOL Text::shouldBeDeleted()
{
	return FALSE;
}

BOOL Text::isLeadByte(char c)
{ 
	BOOL leadByteFlag = IsDBCSLeadByteEx(CP_OEMCP,c);
	return leadByteFlag;
}

int Text::delEmptyLines()
{
	int nLines = _content->nOfLines();
	if (nLines <= 1) return 0;
	int *delLines = new int[nLines];
	int delCount = 0;
	int index = 0;
	TextLine *aLine = _content->getFirst();
	while (aLine != NIL) {
		if (aLine->valueAt(0) == '\0') {
			delLines[delCount] = index;
			delCount++;
		}
		index++;
		aLine = _content->getNext();
	}
	if (nLines == delCount) delCount--;
	for (int i = delCount-1; i >= 0; i--) {
		_content->removeLineAt(delLines[i]);
	}
	delete [] delLines;
	if (delCount == 0) {
		return 0;
	}
	return delCount;
}

int Text::insert(char* keypressed)
{
	if (checkBuffer() != KTGOK) {
		_controller->beep("Text::insert(char* keypressed)");
		return -1;
	}
	char c = *keypressed;
	char keyBuffer[3];
	keyBuffer[0] = '\0';
	keyBuffer[1] = '\0';
	keyBuffer[2] = '\0';

	TextLine tmpLine;
	tmpLine.copy(&currentLine);
	tmpLine.setValueAt('\0',_cursorX);
	
	BOOL leadByteFlag = isLeadByte(c);
	if (leadByteFlag && LeadByte == '\0') {
		LeadByte = c;
		return -1;
	} else if (leadByteFlag == FALSE && LeadByte == '\0') {
		_content->setValueAt(c,_cursorX,_cursorY);
		currentLine.setValueAt(c,_cursorX);
		tmpLine.setValueAt(c,_cursorX);
		_cursorX++;
		keyBuffer[0] = c;
	} else { // LeadByte != '\0'
		_content->setValueAt(LeadByte,_cursorX,_cursorY);
		currentLine.setValueAt(LeadByte,_cursorX);
		tmpLine.setValueAt(LeadByte,_cursorX);
		_cursorX++;
		_content->setValueAt(c,_cursorX,_cursorY);
		currentLine.setValueAt(c,_cursorX);
		tmpLine.setValueAt(c,_cursorX);
		_cursorX++;
		keyBuffer[0] = LeadByte;
		keyBuffer[1] = c;
	}	
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);

	setX2(dcp);
	tmpLine.setValueAt('\0',_cursorX);
	char *ptr = tmpLine.ptrAt(0);
	int x = getX1();
	int y = getY1() + _fontHeight * _cursorY;
	int newDxFromStartToCurrent = deltaH(dcp,tmpLine.ptrAt(0));
	ptr = currentLine.ptrAt(0);
	_vterm->insert(newDxFromStartToCurrent);
	COLORREF oldColor;
	if (_controller->currentFocus() != NIL &&
		whoAreYou()->equals(IAMCOLOBJMESSAGETEXT) == FALSE &&
		whoAreYou()->equals(IAMSYNCCONDITIONTEXT) == FALSE &&
		_controller->currentFocus()->whoAreYou()->isIn(WEARENODEOBJECTS)) {
		oldColor = dcp->SetBkColor(_controller->currentFocus()->background());
	}
	dcp->TextOut(x,y,ptr,strlen(ptr));
	if (_controller->currentFocus() != NIL &&
		whoAreYou()->equals(IAMCOLOBJMESSAGETEXT) == FALSE &&
		whoAreYou()->equals(IAMSYNCCONDITIONTEXT) == FALSE &&
		_controller->currentFocus()->whoAreYou()->isIn(WEARENODEOBJECTS)) {
		dcp->SetBkColor(oldColor);
	}
	int dx = deltaH(dcp,currentLine.ptrAt(0));
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
	LeadByte = '\0';
	return dx;
}

void Text::goNextLine()
{
	if (_maxLines > 0 && textHeight() >= _maxLines) {
		return;
	}
	int oldX2 = _x2.get();
	TextLine *nextLine = _content->splitLineAt(_cursorX,_cursorY,whoAreYou());
	currentLine.copy(nextLine);
	_cursorY++;
	_cursorX = 0;
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	setX2AsOtherLinesMaxWidth(dcp);
	_y2.set(_y2.get()+deltaV());
	_vterm->goNextLine(deltaV()*_cursorY);
	CRect tmp(_x1.get(),_y1.get()+(_cursorY-1)*deltaV(),oldX2,_y2.get());
	_controller->invalidateRect(&tmp,TRUE);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
}

void Text::goHome()
{
	if (_cursorX == 0) return;

	_cursorX = 0;
	_vterm->goHome();

	// 이거해야 커서 잔상이 없어지네 그랴 ...
	int x1 = getX1()+_vterm->cursorX() - 1;
	int y1 = getY1()+_vterm->cursorY();
	int x2 = x1 + 2;
	int y2 = y1 + deltaV();
	CRect tmp(x1,y1,x2,y2);
	_controller->invalidateRect(&tmp,TRUE);
}

void Text::goEnd()
{
	if (currentLine.valueAt(_cursorX) == '\0') 	return;
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	int dx = getCursorPosFrom0ToEnd(dcp);
	_cursorX = currentLine.getLength();

	_vterm->goEnd(dx);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);

	// 이거해야 커서 잔상이 없어지네 그랴 ...
	int x1 = getX1()+_vterm->cursorX() - 1;
	int y1 = getY1()+_vterm->cursorY();
	int x2 = x1 + 2;
	int y2 = y1 + deltaV();
	CRect tmp(x1,y1,x2,y2);
	_controller->invalidateRect(&tmp,TRUE);
}

void Text::goLeft()
{
	if (_cursorX == 0) return;
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);

	_cursorX = getCursorIndexBefore(dcp,_vterm->cursorX());
	TextLine tmpLine;
	tmpLine.copy(&currentLine);
	tmpLine.setValueAt('\0',_cursorX);
	int dxFromStartToCurrent = deltaH(dcp,tmpLine.ptrAt(0));

	_vterm->goLeft(dxFromStartToCurrent);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);

	// 이거해야 커서 잔상이 없어지네 그랴 ...
	int x1 = getX1()+_vterm->cursorX() - 1;
	int y1 = getY1()+_vterm->cursorY();
	int x2 = x1 + 2;
	int y2 = y1 + deltaV();
	CRect tmp(x1,y1,x2,y2);
	_controller->invalidateRect(&tmp,TRUE);
}

void Text::goRight()
{
	char c = currentLine.valueAt(_cursorX);
	if (c == '\0') return;

	TextLine tmpLine;
	tmpLine.copy(&currentLine);

	if (isLeadByte(c)) {
		_cursorX = _cursorX+2;
	} else {
		_cursorX++;
	}
	tmpLine.setValueAt('\0',_cursorX);
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	int dxFromStartToCurrent = deltaH(dcp,tmpLine.ptrAt(0));
	_vterm->goRight(dxFromStartToCurrent);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);

	// 이거해야 커서 잔상이 없어지네 그랴 ...
	int x1 = getX1()+_vterm->cursorX() - 1;
	int y1 = getY1()+_vterm->cursorY();
	int x2 = x1 + 2;
	int y2 = y1 + deltaV();
	CRect tmp(x1,y1,x2,y2);
	_controller->invalidateRect(&tmp,TRUE);
}

void Text::goUp()
{
	if (_cursorY == 0) return;
	_cursorY--;
	TextLine *newLine = _content->lineAt(_cursorY);
	currentLine.copy(newLine);
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	int dx = getCursorPosFrom0(dcp,_vterm->cursorX());
	_vterm->goUp(dx);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);

	// 이거해야 커서 잔상이 없어지네 그랴 ...
	int x1 = getX1()+_vterm->cursorX() - 1;
	int y1 = getY1()+_vterm->cursorY();
	int x2 = x1 + 2;
	int y2 = y1 + deltaV();
	CRect tmp(x1,y1,x2,y2);
	_controller->invalidateRect(&tmp,TRUE);
}

void Text::goDown()
{
	if (_cursorY >= textHeight()-1) return;
	_cursorY++;
	TextLine *newLine = _content->lineAt(_cursorY);
	currentLine.copy(newLine);
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	int dx = getCursorPosFrom0(dcp,_vterm->cursorX());
	_vterm->goDown(dx);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);

	// 이거해야 커서 잔상이 없어지네 그랴 ...
	int x1 = getX1()+_vterm->cursorX() - 1;
	int y1 = getY1()+_vterm->cursorY();
	int x2 = x1 + 2;
	int y2 = y1 + deltaV();
	CRect tmp(x1,y1,x2,y2);
	_controller->invalidateRect(&tmp,TRUE);
}

BOOL Text::delLine()
{
	if (textHeight() == 1) {
		_content->lineAt(0)->clear();
		currentLine.clear();
		_cursorX = 0; _cursorY = 0;
		_vterm->delFirstLine();
		CRect tmp(_x1.get(),_y1.get(),_x2.get(),_y2.get());
		_controller->invalidateRect(&tmp);
		_content->setOtherLinesMaxWidth(0);
		_x2.set(0);
		return TRUE;
	}
	if (_cursorY == textHeight()-1) {
		_content->removeLineAt(_cursorY);
		_cursorY--;
	} else {
		_content->removeLineAt(_cursorY);
	}
	currentLine.copy(_content->lineAt(_cursorY));
	_cursorX = 0;
	_vterm->delLine(_cursorY*deltaV(),TRUE);

	CRect tmp(_x1.get(),_y1.get()+_cursorY*deltaV(),
		      _x2.get()+1,_y2.get()+1);
	_controller->invalidateRect(&tmp);

	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);

	setX2AsOtherLinesMaxWidth(dcp);
	_y2.set(_y2.get()-deltaV());
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
	return FALSE;
}

BOOL Text::delChar()
{
	char c = _content->valueAt(_cursorX,_cursorY);
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	if (c == '\0') {
		if (_cursorY == textHeight()-1) {
			dcp->SelectObject(oldFont);
			return TRUE;
		} else {
			_content->mergeLines(_cursorY,_cursorY+1);
			_vterm->delLine(_cursorY*deltaV(),FALSE);
			CRect tmp(_x1.get(),_y1.get()+_cursorY*deltaV(),
					  _x2.get()+1,_y2.get()+1);
			_controller->invalidateRect(&tmp);
			_y2.set(_y2.get()-deltaV());
		}
	} else {
		if (isLeadByte(c)) {
			_content->delCharAt(_cursorX,_cursorY);
			_content->delCharAt(_cursorX,_cursorY);
		} else {
			_content->delCharAt(_cursorX,_cursorY);
		}
		_vterm->delChar();
		CRect tmp(_x1.get(),_y1.get()+_cursorY*deltaV(),
				  _x2.get()+1,_y1.get()+(_cursorY+1)*deltaV());
		_controller->invalidateRect(&tmp);
	}
	currentLine.copy(_content->lineAt(_cursorY));
	setX2AsOtherLinesMaxWidth(dcp);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
	return FALSE;
}

BOOL Text::delCharBack()
{
	createFont();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	CFont *oldFont = dcp->SelectObject(_font);
	if (_cursorX == 0) {
		if (_cursorY == 0) {
			dcp->SelectObject(oldFont);
			return TRUE;
		} else {
			_cursorY--;
			char *ptr = _content->ptrAt(0,_cursorY);
			int dH = deltaH(dcp,ptr);
			_cursorX = strlen(ptr);
			_content->mergeLines(_cursorY,_cursorY+1);
			_vterm->delCharBackLine(dH,_cursorY*deltaV());
			CRect tmp(_x1.get(),_y1.get()+_cursorY*deltaV(),
					  _x2.get(),_y2.get());
			_controller->invalidateRect(&tmp);
			_y2.set(_y2.get()-deltaV());
		}
	} else {
		_cursorX = getCursorIndexBefore(dcp,_vterm->cursorX());

		char c = currentLine.valueAt(_cursorX);
		char charBuffer[3];
		charBuffer[0] = c;
		charBuffer[1] = '\0';
		charBuffer[2] = '\0';
		if (isLeadByte(c)) {
			charBuffer[1] = currentLine.valueAt(_cursorX+1);
			_content->delCharAt(_cursorX,_cursorY);
			_content->delCharAt(_cursorX,_cursorY);
		} else {
			_content->delCharAt(_cursorX,_cursorY);
		}

		TextLine tmpLine;
		tmpLine.copy(&currentLine);
		tmpLine.setValueAt('\0',_cursorX);
		int dxFromStartToCurrent = deltaH(dcp,tmpLine.ptrAt(0));

		_vterm->delCharBack(dxFromStartToCurrent);
		CRect tmp(_x1.get(),_y1.get()+_cursorY*deltaV(),
				  _x2.get()+1,_y1.get()+(_cursorY+1)*deltaV());
		_controller->invalidateRect(&tmp);
	}
	currentLine.copy(_content->lineAt(_cursorY));
	setX2AsOtherLinesMaxWidth(dcp);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
	return FALSE;
}

BOOL Text::startEdit()
{
	ResetLeadByte();
	createFont();
	int dV = deltaV() * _controller->zoomRatioY() / 100;
	_controller->CreateSolidCaret(1,dV);
	_vterm->activate();
	_controller->ShowCaret();
	currentLine.copy(_content->lineAt(_cursorY));
	return TRUE;
}

BOOL Text::wantToResize(int& x,int& y)
{
	return FALSE;
}

void Text::bye()
{
	ResetLeadByte();
	CDC *dcp = _controller->GetDC();
	_controller->setDrawingContext(KTG_DRAWING);
	_controller->OnPrepareDC(dcp);
	createFont();
	CFont *oldFont = dcp->SelectObject(_font);
	setX2AsOtherLinesMaxWidth(dcp);
	dcp->SelectObject(oldFont);
	_controller->OODReleaseDC(dcp,TRUE);
	releaseFont();
	_controller->HideCaret();
	
//	int x1 = getX1()+_vterm->cursorX() - 1;
//	int y1 = getY1()+_vterm->cursorY();
//	int x2 = x1 + 2;
//	int y2 = y1 + deltaV();
//	CRect tmp(x1,y1,x2,y2);
//	_controller->invalidateRect(&tmp,TRUE);

	_vterm->set(0,0);
	_cursorX = 0;
	_cursorY = 0;
}

void Text::setMaxLines(int n)
{
	_maxLines = n;
}

void Text::adjustScale()
{
}

VTerm* Text::vterm()
{
	return _vterm; 
}

void Text::disconnectFromContainer()
{
	return;
}

Figure* Text::born(Figure* ptr)
{
	Text *copied;
	if (ptr == NIL) {
		copied = new Text(NIL,0,0,NIL);
	} else {
		copied = (Text *)ptr;
	}
	copied->_cursorX = _cursorX;
	copied->_cursorY = _cursorY;
	copied->xscale = xscale;
	copied->yscale = yscale;
	copied->_autoDelete = _autoDelete;
	copied->_fontInfo = new FontInfo();
	copied->_fontInfo->copy(_fontInfo);
	copied->_font = NIL;
	copied->_fontHeight = _fontHeight;
	copied->_content = _content->born();
	copied->_maxLines = _maxLines;
	copied->_vterm = _vterm->born();
	copied->_vterm->setTextPtr(copied);
	return (Box::born((Figure *)copied));
}

BOOL Text::checkMinWH()
{
	return FALSE;
}

UnsignedLong *Text::whoAreYou()
{
	return IAMTEXT;
}

TextContent *Text::content() 
{
	return _content;
}

void Text::setController(COODView *ptr)
{
	TwoPointFigure::setController(ptr);
}

BOOL Text::isEditable()
{
	return TRUE;
}

int Text::deltaV()
{
	return _fontHeight;
}

int Text::deltaH(CDC* dcp,char* ch)
{
	CSize s = dcp->GetTextExtent(ch,strlen(ch));
	return s.cx;
}

int Text::getName(char *buffer,int bufSize)
{
	*buffer = '\0';
	return (_content->compactAsOneString(buffer,bufSize));
}

int Text::strcpyCompact(char *to,const char *from,int bufSize)
{
	char *toPtr = to;
	const char *fromPtr = from;
	int count = 0;
	while (*fromPtr != '\0') {
		char c = *fromPtr;
		if (c != ' ' && c != '\t'&& c != '\n') {
			*toPtr = c;
			toPtr++;
			count++;
			if (count+2 > bufSize) {
				*toPtr = '\0';
				return count;
			}
		}
		fromPtr++;
	}
	*toPtr = '\0';
	return count;
}

int Text::strcatCompact(char *to,const char *from,int bufSize)
{
	char *toPtr = to;
	const char *fromPtr = from;
	int count = 0;
	while(*toPtr != '\0') {
		count++; toPtr++;
	}
	if (count >= bufSize - 1) return count;
	while (*fromPtr != '\0') {
		char c = *fromPtr;
		if (c != ' ' && c != '\t'&& c != '\n') {
			*toPtr = c;
			toPtr++;
			count++;
			if (count >= bufSize-1) {
				*toPtr = '\0';
				return count;
			}
		}
		fromPtr++;
	}
	*toPtr = '\0';
	return count;
}

void Text::centering(CDC* dcp,int startX,int w)
{
	CRect tmp(_x1.get(),_y1.get(),_x2.get(),_y2.get());
	dcp->FillRect(tmp,COODView::ShapeEraseBrush);
	createFont();
	CFont *oldFont = dcp->SelectObject(_font);
	int y = getY1();
	TextLine *aLine = _content->getFirst();
	while(aLine != NIL) {
		char *ptr = aLine->ptrAt(0);
		CSize s = dcp->GetTextExtent(ptr,strlen(ptr));
		int textWidth = s.cx;
		int x = startX + (w-textWidth)/2;
		dcp->TextOut(x,y,ptr,strlen(ptr));
		y = y + _fontHeight;
		aLine = _content->getNext();
	}
	dcp->SelectObject(oldFont);
	releaseFont();
}

