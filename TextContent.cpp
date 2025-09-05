// TextContent.cpp: implementation of the TextContent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "TextContent.h"
#include "ListNode.h"
#include "TextLine.h"
#include "Text.h"
#include "UnsignedLong.h"
#include "ClassTextLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(TextContent,List,1)

TextContent::TextContent()
: List()
{
	_otherLinesMaxWidth = 0;
}

TextContent::~TextContent()
{
	TextLine *aLine = getFirst();
	while (aLine != NIL) {
		delete aLine;
		aLine = getNext();
	}
}

void TextContent::Serialize(CArchive& ar)
{
	List::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _otherLinesMaxWidth;
	} else {
		ar >> (LONG &) _otherLinesMaxWidth;
	}
}


TextLine *TextContent::lineAt(int n)
{
	TextLine *aLine = getFirst();
	if (n == 0) return aLine;
	for (int i = 0; i < n; i++) {
		aLine = getNext();
	}
	return aLine;
}

void TextContent::insertAt(TextLine* ptr,int n) 
{
	List::insertAt((CObject*)ptr,n);
}

void TextContent::insertAtLast(TextLine* ptr) 
{
	int n = nOfLines();
	if (n == 1) {
		TextLine *aLine = getFirst();
		if (aLine->isEmpty()) {
			removeLineAt(0);
			List::insertAt((CObject*)ptr,0);
			return;
		}
	}
	List::insertAt((CObject*)ptr,n);
}

void TextContent::mergeLines(int pos1,int pos2)
{
	TextLine *thisLine = lineAt(pos1);
	TextLine *nextLine = lineAt(pos2);
	thisLine->merge(nextLine);
	removeLineAt(pos2);
}

TextLine* TextContent::splitLineAt(int i,int j,UnsignedLong *who)
{
	TextLine *thisLine = lineAt(j);
	TextLine *beforeLine = newLineAt(j,who);
	beforeLine->copy(thisLine);
	char *source = beforeLine->ptrAt(i);
	if (*source == '\0') {
		thisLine->clear();
	} else {
		char *target = thisLine->ptrAt(0);
		thisLine->clear();
		strcpy_s(target,LINEBUFSIZ,source);
		beforeLine->setNullFrom(i);
		thisLine->setLength();
		beforeLine->setLength();
	}
	return thisLine;
}

TextLine* TextContent::newLineAt(int n,UnsignedLong *who)
{
	TextLine *newLine = NIL;
	if (who->equals(IAMCLASSTEXT)) {
		newLine = new ClassTextLine();
	} else {
		newLine = new TextLine();
	}
	insertAt(newLine,n);
	return newLine;
}

int TextContent::setOtherLinesMaxWidth(CDC *dcp,int n)
{
	if (n < 0) return 0;
	if (n >= nOfLines()) return 0;
	_otherLinesMaxWidth = 0;
	int i = 0;
	TextLine *aLine = getFirst();
	while (aLine != NIL) {
		if (n != i) {
			CSize s = dcp->GetTextExtent(aLine->ptrAt(0),strlen(aLine->ptrAt(0)));
			int newx = s.cx;
			if (_otherLinesMaxWidth < newx) _otherLinesMaxWidth = newx;
		}
		i++;
		aLine = getNext();
	}
	return _otherLinesMaxWidth;
}

int TextContent::compactAsOneString(char *buffer,int bufSize)
{
	int len = 0;
	*buffer = '\0';
	TextLine *aLine = getFirst();
	while (aLine != NIL) {
		len = Text::strcpyCompact(buffer,aLine->ptrAt(0),bufSize);
		aLine = getNext();
	}
	return len;
}

int TextContent::setAllLinesMaxWidth(CDC *dcp)
{
	_otherLinesMaxWidth = 0;
	int i = 0;
	TextLine *aLine = getFirst();
	while (aLine != NIL) {
		CSize s = dcp->GetTextExtent(aLine->ptrAt(0),strlen(aLine->ptrAt(0)));
		int newx = s.cx;
		if (_otherLinesMaxWidth < newx) _otherLinesMaxWidth = newx;
		i++;
		aLine = getNext();
	}
	return _otherLinesMaxWidth;
}

int TextContent::stringWidth()
{
	int w = 0;
	TextLine *aLine = getFirst();
	while (aLine != NIL) {
		if (w < aLine->getLength()) {
			w = aLine->getLength();
		}
		aLine = getNext();
	}
	return w;
}

int TextContent::nOfLines()
{
	return nOfList();
}

void TextContent::removeLineAt(int pos)
{
	TextLine *aLine = (TextLine *)List::removeAt(pos);
	if (aLine != NIL) delete aLine;
}

TextContent *TextContent::born()
{
	TextContent *copied = new TextContent();
	TextLine *aLine = getFirst();
	while (aLine != NIL) {
		copied->insert(aLine->born());
		aLine = getNext();
	}
	copied->_otherLinesMaxWidth = _otherLinesMaxWidth;
	return copied;
}

void TextContent::setValueAt(char c,int i,int j)
{
	TextLine *aLine = lineAt(j);
	aLine->setValueAt(c,i);
}

char TextContent::valueAt(int i,int j)
{
	TextLine *aLine = lineAt(j);
	return aLine->valueAt(i);
}

void TextContent::delCharAt(int i,int j)
{
	TextLine *aLine = lineAt(j);
	aLine->delCharAt(i);
}

char *TextContent::ptrAt(int i,int j)
{
	TextLine *aLine = lineAt(j);
	return aLine->ptrAt(i);
}

void TextContent::clear()
{
	TextLine *aLine = getFirst();
	while (aLine != NIL) {
		delete aLine;
		aLine = getNext();
	}
	List::clear();
}

TextLine* TextContent::getFirst()
{
	return (TextLine*)List::getFirst();
}

TextLine* TextContent::getLast()
{
	return (TextLine*)List::getLast();
}

TextLine* TextContent::getNext()
{
	return (TextLine*)List::getNext();
}

TextLine* TextContent::getBack()
{
	return (TextLine*)List::getBack();
}
