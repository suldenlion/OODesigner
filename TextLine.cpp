// TextLine.cpp: implementation of the TextLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "TextLine.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(TextLine,CObject,1)

void TextLine::clear()
{
	_length = 0;
	for(int i = 0; i < LINEBUFSIZ; i++) {
		line[i] = '\0';
	}
}

void TextLine::setNullFrom(int i)
{
	for(int t = i; t < LINEBUFSIZ; t++) {
		line[t] = '\0';
	}
	setLength();
}

void TextLine::merge(TextLine *aLine)
{
	setLength();
	int i = _length;
	char *ptr = aLine->ptrAt(0);
	while (*ptr != '\0' && i < LINEBUFSIZ) {
		line[i] = *ptr;
		i++; ptr++;
	}
	line[i] = '\0';
	setLength();
}

void TextLine::setLength()
{
	_length = strlen(&line[0]);
}

TextLine::TextLine()
: CObject()
{
	clear();
}

TextLine::~TextLine()
{
}

void TextLine::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);   
	if (ar.IsStoring()) {
		ar << (LONG) _length;
		for(int i = 0; i <= _length; i++) {
			ar << (LONG) line[i];
		}
	} else {
		ar >> (LONG &) _length;
		for(int i = 0; i <= _length; i++) {
			ar >> (LONG &) line[i];
		}
	}
}

char TextLine::valueAt(int i) 
{
	return line[i];
}

void TextLine::delCharAt(int i)
{
	for (int tmp = i+1; tmp < LINEBUFSIZ; tmp++) {
		line[tmp-1] = line[tmp];
	}
	_length--;
}

void TextLine::setValueAt(char c,int i)
{
	if (line[i] == '\0') line[i] = c;
	else {
		for (int tmp = _length-1; tmp >= i; tmp--) {
			line[tmp+1] = line[tmp];
		}
		line[i] = c;
	}
	_length++;
}

BOOL TextLine::isEmpty()
{
	int i = 0;
	while (line[i] != '\0') {
		if (line[i] != ' ') return FALSE;
		i++;
	}
	return TRUE;
}

void TextLine::shiftLeft(int from)
{
	for (int tmp = from; tmp < LINEBUFSIZ; tmp++) {
		line[tmp-1] = line[tmp];
	}
	_length--;
}

void TextLine::shiftRight(int from)
{
	for (int tmp = _length-1; tmp >= from; tmp--) {
		line[tmp+1] = line[tmp];
	}
	_length++;
}

char *TextLine::ptrAt(int i)
{
	return &line[i];
}

void TextLine::copyLineOnly(TextLine *from)
{
	clear();
	for(int i = 0; i < LINEBUFSIZ; i++) {
		line[i] = from->line[i];
	}
	setLength();
}

void TextLine::copy(TextLine *from)
{
	copyLineOnly(from);
}

void TextLine::setString(const char *str)
{
	TextLine::clear();
	strcpy_s(line,LINEBUFSIZ,str);
	setLength();
}

TextLine *TextLine::born()
{
	TextLine *copied = new TextLine();
	copied->copy(this);
	return copied;
}
