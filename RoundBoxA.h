/* RoundBoxA.h */

#ifndef _ROUNDBOXA_H
#define _ROUNDBOXA_H

#include "TwoPointFigure.h" // Generalization

class RoundBoxA : public TwoPointFigure {
	DECLARE_SERIAL(RoundBoxA)
protected : // member functions
	void makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn);
public : // member functions
	virtual ~RoundBoxA();
	RoundBoxA();
	RoundBoxA(COODView *controller,int x,int y,Popup* popup);
	RoundBoxA(COODView *controller,int x1,int y1,int x2,int y2,Popup* popup);
	virtual void Serialize(CArchive& ar);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC *dcp);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual BOOL isTroublesomeToModifyObject();
	BOOL setFollowing2(int x,int y);
};

#endif
