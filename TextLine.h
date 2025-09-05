// TextLine.h: interface for the TextLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTLINE_H__577C4148_F7E8_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_TEXTLINE_H__577C4148_F7E8_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define LINEBUFSIZ	(BUFSIZ)

class TextLine : public CObject  
{
	DECLARE_SERIAL(TextLine)
protected:
	int _length;
	char line[LINEBUFSIZ];

	void shiftLeft(int from);
	void shiftRight(int from);
public:
	TextLine();
	virtual ~TextLine();
	virtual void Serialize(CArchive& ar);
	void setLength();
	void setString(const char *str);
	int getLength() { return _length; }
	char valueAt(int i);
	void setValueAt(char c,int i);
	char *ptrAt(int i);
	void delCharAt(int i);
	void setNullFrom(int i);
	BOOL isEmpty();
	void merge(TextLine *aLine);
	virtual TextLine *born();
	void copyLineOnly(TextLine *from);
	virtual void copy(TextLine *from);
	virtual void clear();
};

#endif // !defined(AFX_TEXTLINE_H__577C4148_F7E8_11D2_AC44_00008610434C__INCLUDED_)
