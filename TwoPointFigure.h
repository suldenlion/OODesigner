/* TwoPointFigure.h */

#ifndef _TWOPOINTFIGURE_H
#define _TWOPOINTFIGURE_H

#include "Figure.h" // Generalization

#ifndef sqr
#define sqr(x) (x)*(x)
#endif

extern void checkPoints(int& x1,int& y1,int& x2,int& y2);
extern void checkPoints(XCoord& x1,YCoord& y1,XCoord& x2,YCoord& y2);
extern int distance(int x1,int y1,int x2,int y2);

/*oodE******************************************************/
class TwoPointFigure : public Figure {
	DECLARE_SERIAL(TwoPointFigure)
protected : // data members
	BOOL _filled;
	XCoord *_hotX;
	YCoord *_hotY;
protected:
	TwoPointFigure();
	TwoPointFigure(COODView *controller,int x,int y);
	TwoPointFigure(COODView *controller,int x1,int y1,int x2,int y2);
	virtual void swapPoints();
public : // member functions
	virtual void Serialize(CArchive& ar);
	XCoord _x1;
	XCoord _x2;
	YCoord _y1;
	YCoord _y2;
	int getX1() { return _x1.get(); }
	int getY1() { return _y1.get(); }
	int getX2() { return _x2.get(); }
	int getY2() { return _y2.get(); }
	XCoord *hotX() { return _hotX; }
	YCoord *hotY() { return _hotY; }
	XCoord *notHotX();
	YCoord *notHotY();
	void resetHotXY() { _hotX = NIL; _hotY = NIL; }
	virtual ~TwoPointFigure();
	virtual BOOL wantToResize(int &x,int &y);
	virtual BOOL wantToResizeExact(int x,int y);
	virtual void clear(CDC* dcp);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void center(int& x,int& y);
	virtual void last(int& x,int& y);
	virtual void drawing(CDC* dcp,int dx,int dy);
	virtual BOOL checkNear(int x,int y);
	virtual BOOL checkInRegion(CRgn* someregion);
	virtual void minMaxXY();
	virtual void getMinMaxXY(int &minX,int &minY,int &maxX,int &maxY);
	virtual void moveCoord(int dx,int dy);
	virtual int setHotXY(int x,int y);
	virtual Figure* born(Figure* ptr = NIL);
	virtual void setController(COODView *ptr);  
	virtual BOOL checkMinWH();
	virtual void setXY1(int x,int y);
	virtual void setXY2(int x,int y);
	virtual void invalidate();
	virtual void adjustXYValue(int oldx,int oldy,int newx,int newy);
	virtual void fill(CDC* dcp);
	virtual BOOL isTroublesomeToModifyObject();
	virtual void getExclusiveClipRect(int &x1,int &y1,int &x2,int &y2);
	virtual BOOL containedWithin(int x1,int y1,int x2,int y2);
	BOOL &filled();
	int width();
	void coords(int& x1,int& y1,int& x2,int& y2);
	void setCoords(int x1,int y1,int x2,int y2);
	BOOL contains(int x,int y);
	BOOL containsOnLargeBound(int x,int y);
	BOOL onBound(Line *aLine);
	BOOL adjustLine(Line *line,BOOL startPoint);
	BOOL arrangeXY12();
	int onWhichSide(int x,int y);
	static BOOL wantToResize(int x,int y,int px,int py);
};

#endif
