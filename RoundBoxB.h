/* RoundBoxB.h */

#ifndef _ROUNDBOXB_H
#define _ROUNDBOXB_H

#include "TwoPointFigure.h" // Generalization

class RoundBoxB : public TwoPointFigure {
	DECLARE_SERIAL(RoundBoxB)
protected : // member functions
	void drawRoundBox(CDC* dcp,int x,int y,int width,int height);
	void makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn);
public : // member functions
	virtual ~RoundBoxB();
	RoundBoxB();
	RoundBoxB(COODView *controller,int x,int y,Popup* popup);
	RoundBoxB(COODView *controller,int x1,int y1,int x2,int y2,Popup* popup);
	virtual void Serialize(CArchive& ar);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC *dcp);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void makeRegion(CRgn *sourceClipRgn);
	BOOL setFollowing2(int x,int y);
};

#endif
