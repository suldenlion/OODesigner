// NodeFigure.h: interface for the NodeFigure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODEFIGURE_H__9C23B742_01AE_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_NODEFIGURE_H__9C23B742_01AE_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Figure.h"

#define O_SIDE		(0)
#define I_SIDE		(1)
#define II_SIDE		(2)
#define III_SIDE	(3)
#define IV_SIDE		(4)
#define V_SIDE		(5)
#define	VI_SIDE		(6)
#define	VII_SIDE	(7)
#define VIII_SIDE	(8)

class NodeFigure : public Figure {
	DECLARE_SERIAL(NodeFigure)
protected:
	// _shape의 타입은 adjustLine() 함수와 관계있음 : 주의 
	TwoPointFigure *_shape; 
	// _decorations는 makeRegion() 등의 작업이 필요없음
	FigureList	*_decorations;
	ConnectionList *_connections;
	Figure *_focus;
protected:
	NodeFigure();
	NodeFigure(COODView *controller);
public:
	virtual void Serialize(CArchive& ar);
	TwoPointFigure *shape() { return _shape; } 
	virtual ~NodeFigure();
	virtual BOOL& inCanvas();
	virtual CRgn*& region();
	virtual CRgn*& clip();
	virtual CRgn* clip(CDC *pDC);
	int getX1();
	int getY1();
	int getX2();
	int getY2();
	virtual void setFocus(int x = -OODMAXINT, int y = -OODMAXINT);
	virtual void resetFocus();
	virtual void setThisFocus(Figure *ptr);
	virtual Figure *focus();
	virtual void epilog(BOOL = FALSE);
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual BOOL checkInRegion(CRgn* rgn);
	virtual void center(int& cx,int& cy);
	virtual void last(int& x,int& y);
	virtual void clear(CDC* dcp);
	virtual void clearMeAndNeighbors(CDC *dcp);
	virtual void minMaxXY();
	virtual void getMinMaxXY(int &x1,int &y1,int &x2,int &y2);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void drawWithNeighbors(CDC *dcp);
	virtual void drawing(CDC*,int dx,int dy);
	virtual BOOL onEnter(int x,int y);
	virtual void move(CDC*,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual int setHotXY(int x,int y);
	virtual BOOL wantToResize(int& x,int& y);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual Figure* born(Figure* ptr = NIL);
	virtual Figure* makeBackUp();
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void deleteNeighbors();
	virtual void setController(COODView *ptr);
	virtual void clearLists();
	virtual void invalidate();
	virtual BOOL adjustLine(Line *line,BOOL startPoint);
	virtual BOOL onBoundaryOrObsolete(LineNodeList *lines);
	virtual BOOL startEdit();
	virtual void bye();
	virtual void getExclusiveClipRect(int &x1,int &y1,int &x2,int &y2);
	virtual BOOL containedWithin(int x1,int y1,int x2,int y2);
	virtual void removeExcludeRect(Figure *ptr);
	virtual void addExcludeRect(ExcludeRect *ptr);
	virtual void removeAllExcludeRect();
	virtual ExcludeRectList *getExcudeRects();
	virtual COLORREF background();
	virtual void setBackground(COLORREF c);
	virtual BOOL containsOnTupleBound(int x,int y) {
		return containsOnLargeBound(x,y);
	}
	ConnectionList *connections() { 
		return _connections; 
	}
	void setConnectionMovedFlag(BOOL flag);
	int onWhichSideRegion(int x,int y);
	int width();
	void drawConnections(CDC *dcp);
	void insert(Connection *connection);
	void remove(Connection *connection);
	BOOL replacePointer(Connection *from,Connection *to);
	BOOL contains(LineNodeList *lines);
	BOOL contains(int x,int y);
	BOOL containsOnLargeBound(int x,int y);
	BOOL onBound(Line *aLine);
	void setOrientForObsoleteLine(Line *aLine);
};

#endif // !defined(AFX_NODEFIGURE_H__9C23B742_01AE_11D3_AC44_00008610434C__INCLUDED_)
