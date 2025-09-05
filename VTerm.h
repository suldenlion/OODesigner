/* VTerm.h */

#ifndef _VTERM_H
#define _VTERM_H

#include "Classes.h"

#include "XCoord.h" // Aggregation
#include "YCoord.h" // Aggregation

class VTerm : public CObject {
	DECLARE_SERIAL(VTerm)
private : // data members
	Text *_text;
	int _cursorX;
	int _cursorY;
protected : // member functions
	COODView* controller();
	int startX();
	int startY();
	void drawScaledString(int x,int y,char* str,int len);
public : // member functions
	VTerm();
	VTerm(Text *aText);
	virtual ~VTerm();
	virtual void Serialize(CArchive& ar);
	void setTextPtr(Text *ptr);
	int cursorX() { return _cursorX; }
	int cursorY() { return _cursorY; }
	void activate();
	void set(int newx,int newy);
	void goRel(int dx,int dy);
	void goAbs(int x,int y);
	void insert(int newx);
	void goNextLine(int y);
	void goHome();
	void goEnd(int dxfrom0);
	void goLeft(int dx);
	void goRight(int dx);
	void goUp(int dxfrom0);
	void goDown(int dxfrom0);
	void delChar();
	void delCharBack(int dx);
	void delCharBackLine(int dx,int dy);
	void delLine(int dyfrom0,BOOL moveCaret);
	void delFirstLine();
	VTerm* born();
};

#endif
