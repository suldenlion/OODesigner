// QualificationText.h: interface for the QualificationText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUALIFICATIONTEXT_H__8C7CF281_F766_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_QUALIFICATIONTEXT_H__8C7CF281_F766_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "TupleText.h"

class QualificationText : public TupleText  
{
	DECLARE_SERIAL(QualificationText)
private:
	int _whichSide;
	Box *_boundary;
	void adjustXCoord(int newWidth);
	void adjustYCoord(int newHeight);
protected:
	virtual int delEmptyLines();
public:
	QualificationText();
	QualificationText(COODView *controller,Connection *connectionPtr,int whichSide,int ox,int oy,Popup *popup);
	virtual void Serialize(CArchive& ar);
	void setWhichSide(int side) { _whichSide = side; }
	void recalcCoordFromTuplePointXY(int tupleX,int tupleY);
	virtual ~QualificationText();
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual int insert(char* keypressed);
	virtual void goNextLine();
	virtual BOOL delChar();
	virtual BOOL delLine();
	virtual BOOL delCharBack();
	virtual void bye();
	virtual void draw(CDC* dcp);
	virtual void moveCoord(int dx,int dy);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void drawBoundary(CDC* dcp);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual BOOL wantToMove(int,int);
	virtual void clear(CDC* dcp);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual void setController(COODView *ptr);
	virtual BOOL onEnter(int x,int y);
};

#endif // !defined(AFX_QUALIFICATIONTEXT_H__8C7CF281_F766_11D3_BBC8_00A0C9BA6734__INCLUDED_)
