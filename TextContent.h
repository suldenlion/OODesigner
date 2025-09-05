// TextContent.h: interface for the TextContent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTCONTENT_H__577C4149_F7E8_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_TEXTCONTENT_H__577C4149_F7E8_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "List.h"
#include "Classes.h"

class TextContent : public List  
{
	DECLARE_SERIAL(TextContent)
	int _otherLinesMaxWidth;
public:
	TextContent();
	virtual ~TextContent();
	virtual void Serialize(CArchive& ar);
	int otherLinesMaxWidth() { return _otherLinesMaxWidth; }
	void setOtherLinesMaxWidth(int val) { _otherLinesMaxWidth = val; }
	int setOtherLinesMaxWidth(CDC *dcp,int n);
	int setAllLinesMaxWidth(CDC *dcp);
	int nOfLines();
	int stringWidth();
	TextContent *born();
	TextLine *lineAt(int n);
	void insertAt(TextLine* ptr,int n);
	void insertAtLast(TextLine* ptr);
	TextLine* newLineAt(int n,UnsignedLong *who);
	void removeLineAt(int n);
	TextLine* splitLineAt(int i,int j,UnsignedLong *who);
	void mergeLines(int pos1,int pos2);
	void setValueAt(char c,int i,int j);
	void delCharAt(int i,int j);
	char valueAt(int i,int j);
	char *ptrAt(int i,int j);
	int compactAsOneString(char *buffer,int bufSize);
	void clear();
	TextLine* getFirst();
	TextLine* getLast();
	TextLine* getNext();
	TextLine* getBack();
};

#endif // !defined(AFX_TEXTCONTENT_H__577C4149_F7E8_11D2_AC44_00008610434C__INCLUDED_)
