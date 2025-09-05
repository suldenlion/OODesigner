/* Box.h */

#ifndef _BOX_H
#define _BOX_H

#include "TwoPointFigure.h" // Generalization

class Box : public TwoPointFigure {
	DECLARE_SERIAL(Box)
protected : // member functions
	void makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn);
public : // member functions
	virtual ~Box();
	Box();
	Box(COODView *controller,int x,int y,Popup *popup);
	Box(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup);
	virtual void Serialize(CArchive& ar);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void makeRegion(CRgn *sourceClipRgn);
	void highlightEntries(FigureList *figures,FigureList *containee = NIL);
	BOOL setFollowing2(int x,int y);
};

#endif
