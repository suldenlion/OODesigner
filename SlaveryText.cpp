// SlaveryText.cpp: implementation of the SlaveryText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SlaveryText.h"
#include "TextContent.h"
#include "TextLine.h"
#include "COODView.h"
#include "EditableFigure.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SlaveryText,Text,1)

SlaveryText::SlaveryText()
: Text()
{
	_master = NIL;
	_whoAmI = 0;
}

SlaveryText::SlaveryText(COODView *controller,EditableFigure *master,int whoAmI,int ox,int oy)
: Text(controller,ox,oy,NIL)
{
	_master = master;
	_whoAmI = whoAmI;
	if(_whoAmI == 0) {
		setBoldFont(TRUE);
	}
}

SlaveryText::~SlaveryText()
{
	_master = NIL;
}

void SlaveryText::Serialize(CArchive& ar)
{
	Text::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _whoAmI << _master;
	} else {
		ar >> (LONG&) _whoAmI >> _master;
	}
}

Figure* SlaveryText::born(Figure* ptr)
{
	SlaveryText *copied;
	if (ptr == NIL) {
		copied = new SlaveryText(NIL,NIL,0,0,0);
	} else {
		copied = (SlaveryText *)ptr;
	}
	copied->_master = NIL;
	copied->_whoAmI = _whoAmI;
	return (Text::born((Figure *)copied));
}

void SlaveryText::bye()
{
	Text::bye();
	delEmptyLines();
}

BOOL SlaveryText::doIHaveToProceed()
{
	return FALSE;
}

void SlaveryText::activateNextText()
{
	bye();
	SlaveryText *nextText = _master->nextText(this);
	nextText->startEdit();
	return;
}

void SlaveryText::activatePrevText()
{
	bye();
	SlaveryText *nextText = _master->prevText(this);
	nextText->startEdit();
	return;
}

void SlaveryText::goUp()
{
	if (_cursorY == 0) {
		activatePrevText();
		return;
	}
	Text::goUp();
}

void SlaveryText::goDown()
{
	if (_cursorY >= textHeight()-1) {
		activateNextText();
		return;
	}
	Text::goDown();
}

void SlaveryText::goNextLine()
{
	if (doIHaveToProceed()) {
		activateNextText();
		return;
	}
	if (_maxLines > 0 && textHeight() >= _maxLines) {
		return;
	}
	_master->setModifiedFlag(TRUE);
	Text::goNextLine();
	_master->modifyHeight(deltaV(),_whoAmI);
	int lineDX = _content->otherLinesMaxWidth();
	_master->modifyWidthMinus(lineDX,_whoAmI);
}

BOOL SlaveryText::delLine()
{
	if (textHeight() == 1 && _content->valueAt(0,0) == '\0') {
		 return TRUE;
	}
	_master->setModifiedFlag(TRUE);
	if (Text::delLine()) {
		_master->modifyWidthMinus(0,_whoAmI);
		return TRUE;
	}
	_master->modifyHeight(-deltaV(),_whoAmI);
	int lineDX = _content->otherLinesMaxWidth();
	_master->modifyWidthMinus(lineDX,_whoAmI);
	return FALSE;
}

BOOL SlaveryText::delChar()
{
	if (_content->valueAt(_cursorX,_cursorY) == '\0') return TRUE;
	_master->setModifiedFlag(TRUE);
	if (Text::delChar()) return TRUE;
	int lineDX = _content->otherLinesMaxWidth();
	_master->modifyWidthMinus(lineDX,_whoAmI);
	return FALSE;
}

BOOL SlaveryText::delCharBack()
{
	if (_cursorX == 0) return TRUE;
	_master->setModifiedFlag(TRUE);
	if (Text::delCharBack()) return TRUE;
	int lineDX = _content->otherLinesMaxWidth();
	_master->modifyWidthMinus(lineDX,_whoAmI);
	return FALSE;
}

int SlaveryText::insert(char* keypressed)
{
	_master->setModifiedFlag(TRUE);
	int lineDX = Text::insert(keypressed);
	if (lineDX == -1) return 0;
	if (_content->otherLinesMaxWidth() < lineDX) {
		_master->modifyWidthPlus(lineDX,_whoAmI);
	}
	return lineDX;
}

int SlaveryText::delEmptyLines()
{
	int delCount = Text::delEmptyLines();
	_master->modifyHeight(-delCount*deltaV(),_whoAmI);
	return delCount;
}

int SlaveryText::getName(char *buffer,int bufSize)
{
	*buffer = '\0';
	TextLine * aLine = _content->getFirst();
	int count = 0;
	while (aLine != NIL) {
		if (count == 0) {
			count = strcpyCompact(buffer,aLine->ptrAt(0),bufSize);
		} else {
			count = strcatCompact(buffer,aLine->ptrAt(0),bufSize);
		}
		aLine = _content->getNext();
	}
	return count;
}

void SlaveryText::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	if (_whoAmI > 0) {
		COLORREF oldBkColor = dcp->SetBkColor(_master->background());
		Text::draw(dcp);
		dcp->SetBkColor(oldBkColor);
		return;
	}
	if (_master->needCentering() == FALSE) {
		COLORREF oldBkColor = dcp->SetBkColor(_master->background());
		Text::draw(dcp);
		dcp->SetBkColor(oldBkColor);
		return;
	}
	COLORREF oldBkColor = dcp->SetBkColor(_master->background());
	centering(dcp,_master->getX1ForCentering(),_master->widthForCentering());
	dcp->SetBkColor(oldBkColor);
}

