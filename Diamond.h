/* Diamond.h */

#ifndef _DIAMOND_H
#define _DIAMOND_H

#include "TwoPointFigure.h" // Generalization

class Diamond : public TwoPointFigure {
	DECLARE_SERIAL(Diamond)
protected : // member functions
	void makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn);
public : // member functions
	virtual ~Diamond();
	Diamond();
	Diamond(COODView *controller,int x,int y,Popup *popup);
	Diamond(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup);
	virtual void Serialize(CArchive& ar);
	virtual void draw(CDC* dcp);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void makeRegion(CRgn *sourceClipRgn);
};

#endif
