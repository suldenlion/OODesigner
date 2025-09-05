/* Triangle.h */

#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "TwoPointFigure.h" // Generalization

class Triangle : public TwoPointFigure {
	DECLARE_SERIAL(Triangle)
private:
	void initializePoints();
protected : // member functions
	void getMinMaxOfThis(int &minx,int &miny,int &maxx,int &maxy);
	void makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn);
public : // member functions
	virtual ~Triangle();
	BOOL checkMinWH();
	Triangle();
	Triangle(COODView *controller,int x,int y,Popup* popup);
	Triangle(COODView *controller,int x1,int y1,int x2,int y2,Popup* popup);
	virtual void Serialize(CArchive& ar);
	virtual BOOL checkNear(int,int);
	virtual void clear(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual BOOL wantToResize(int &x,int &y);
	virtual void center(int &x,int &y);
	virtual BOOL checkInRegion(CRgn* someregion);
	virtual void minMaxXY();
	virtual void getMinMaxXY(int &minX,int &minY,int &maxX,int &maxY);
	virtual void fill(CDC* dcp);
	virtual void invalidate();
};

#endif
