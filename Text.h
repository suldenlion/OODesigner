/* Text.h */

#ifndef _TEXT_H
#define _TEXT_H

#include "TextLine.h"
#include "Box.h" // Generalization

class Text : public Box {
	DECLARE_SERIAL(Text)
protected : // data members
	static char LeadByte;
	VTerm* _vterm;
	CFont *_font;
	int _fontHeight;
	FontInfo *_fontInfo;
	TextContent *_content;
	int _cursorX;
	int _cursorY;
	int _maxLines;
	BOOL _autoDelete;
public:
	TextLine currentLine;
	double xscale;
	double yscale;
	double sxscale;
	double syscale;

protected : // member functions
	virtual int delEmptyLines();
	BOOL checkBuffer();
	void setX2(CDC*);
	int getCursorIndexBefore(CDC *dcp,int maxVal);
	int getCursorPosFrom0(CDC *dcp,int maxVal);
	int getCursorPosFrom0ToEnd(CDC *dcp);
	void setX2AsOtherLinesMaxWidth(CDC *);
	BOOL isLeadByte(char c); 
	static void SetLeadByte(char c) { LeadByte = c; }
	static void ResetLeadByte() { LeadByte = '\0'; }
public : // member functions
	virtual ~Text();
	Text();
	Text(COODView *controller,int ox,int oy,Popup *popup);
	virtual void Serialize(CArchive& ar);
	void setAutoDelete(BOOL flag) { _autoDelete = flag; }
	CFont* font() { return _font; }
	CFont* createFont();
	void setMaxLines(int n);
	void releaseFont();
	void setBoldFont(BOOL boldFlag);
	void setItalicFont(BOOL italicFlag);
	void setUnderlineFont(BOOL underlineFlag);
	int deltaV(); 
	int deltaH(CDC*,char*);
	int cursorX() { return _cursorX; }
	int cursorY() { return _cursorY; }
	int fontHeight() { return _fontHeight; }
	virtual BOOL startEdit();
	virtual BOOL wantToResize(int& x,int& y);
	virtual BOOL isObsolete();
	virtual BOOL checkNear(int,int);
	virtual void drawBoundary(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void drawLinesFrom(CDC* dcp,int lineNo);
	virtual void clear(CDC* dcp);
	virtual void goHome();
	virtual void goEnd();
	virtual void goLeft();
	virtual void goRight();
	virtual void goUp();
	virtual void goDown();
	virtual int insert(char* keypressed);
	virtual void goNextLine();
	virtual BOOL delLine();
	virtual BOOL delChar();
	virtual BOOL delCharBack();
	virtual void bye();
	virtual void adjustScale();
	virtual void setController(COODView *ptr);
	virtual VTerm* vterm();
	virtual Figure* born(Figure* ptr = NIL);
	virtual int nOfLines();
	virtual BOOL checkMinWH();
	virtual UnsignedLong* whoAreYou();
	virtual void recalcWidthHeight(BOOL = FALSE);
	virtual BOOL shouldBeDeleted();
	virtual void setScale(double fx,double fy);
	virtual TextContent* content();
	virtual int getName(char *buf,int bufSize);
	virtual BOOL isEditable();
	virtual void disconnectFromContainer();
	void recalcCoordFromXY1(int x,int y);
	void recalcCoordFromXY1();
	void recalcCoordFromRealXY1(COODView *controller,int x,int y);
	void recalcCoordFromRealXY1(COODView *controller);
	BOOL isEmpty();
	void centering(CDC* dcp,int startX,int w);
	void normalize();
	void setXY(int x,int y);
	void setString(const char *str);
	void setTextContent(TextContent *newContent);
	void deleteTextContent();
	int textWidth();
	int textHeight();
	static int strcpyCompact(char *to,const char *from,int bufSize);
	static int strcatCompact(char *to,const char *from,int bufSize);
};

#endif
