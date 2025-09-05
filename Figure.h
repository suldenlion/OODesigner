/* Figure.h */

#ifndef _FIGURE_H
#define _FIGURE_H

#include "Classes.h"

#include "XCoord.h"
#include "YCoord.h"

#include "common.h" 
#include "KtgMacro.h"
#include "figutil.h"
#define ShrinkMargin 	(50)

#define FIGUREMINW 	(5)
#define FIGUREMINH 	(5)
#define FIGUREMINL 	(5)
#define FIGUREREGLENGTH (10)
#define ROUNDBOXBGAP    (30)

#define REGIONLENGTH 			(4)
#define ARROWLENGTH				(20)

#define DOTSIZE		(6)

/*
#define POINTRADIUS 	(5)
*/

extern int sign(double x);
extern int sign(float x);
extern int sign(int x);

#define BK_BRUSH	(100)
#define RED_BRUSH	(101)

#define	SOLID 		(0)
#define	DASHED 		(1)
#define	DOTED 		(2)

class Figure : public CObject {
	DECLARE_SERIAL(Figure)
public:
	static Figure *BackUp;
protected : // data members
	COODView *_controller;
	POINT* _points;
	CRgn* _region;
	CRgn* _clip;
	BOOL _visited;
	BOOL _inCanvas;
	Figure *_borned;
	Popup *_popup;
	BOOL _dotedFlag;
	int _brushIndex;
	COLORREF _foreground;
	COLORREF _background;
	ExcludeRectList *_excludeRects;
	// These are used when expanding and shrinking	
	Figure(COODView *controller);
public : // member functions
	Figure();
	virtual ~Figure();
	Figure* borned();
	virtual void Serialize(CArchive& ar);
	void setBrushIndex(int index) { _brushIndex = index; }
	COLORREF foreground() { return _foreground; }
	void excludeRects(CDC *dcp);
	virtual COLORREF background() { return _background; }
	virtual void setForeground(COLORREF c) { _foreground = c; }
	virtual void setBackground(COLORREF c) { _background = c; }
	virtual void removeExcludeRect(Figure *ptr);
	virtual void removeAllExcludeRect();
	virtual void getAdditionalExcludeRects(ExcludeRectList *pList);
	virtual void addExcludeRect(ExcludeRect *ptr);
	virtual ExcludeRectList *getExcudeRects() { return _excludeRects; }
	virtual BOOL& visited();
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual BOOL& inCanvas();
	virtual BOOL checkInRegion(CRgn*);
	virtual void center(int&,int&);
	virtual void last(int&,int&);
	virtual BOOL checkNear(int,int);
	virtual void clear(CDC*);
	virtual void minMaxXY();
	virtual void getMinMaxXY(int &,int &,int &,int &);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual void drawBoundaryEx(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void drawWithNeighbors(CDC *dcp);
	virtual void drawing(CDC*,int,int);
	virtual BOOL onEnter(int x,int y);
	virtual void move(CDC*,int,int);
	virtual void moveCoord(int,int);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual int setHotXY(int,int);
	virtual BOOL wantToResize(int&,int&);
	virtual BOOL wantToMove(int,int);
	virtual void popup(CPoint* event,BOOL = FALSE);
	Popup *popupPointer();
	virtual Figure* born(Figure* ptr = NIL);
	virtual Figure* makeBackUp();
	virtual void bornFocus();
	virtual BOOL checkEntries(CRgn*);
	virtual CRgn*& region();
	virtual CRgn*& clip();
	virtual CRgn* clip(CDC *pDC);
	virtual UnsignedLong* whoAreYou();
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual Figure* container();
	virtual void remakeRegionForContainer();
	virtual void checkInlist(FigureList *alist);
	virtual void recalcWidthHeight(BOOL = FALSE);
	virtual BOOL checkMinWH();
	virtual int nOfFigures();
	virtual void epilog(BOOL skipflag = FALSE);
	virtual BOOL isObsolete();
	virtual void setFocus(int x = -OODMAXINT, int y = -OODMAXINT);
	virtual void resetFocus();
	virtual void setThisFocus(Figure *ptr);
	virtual void deleteFocusObject();
	virtual void bye();
	virtual Figure *focus();
	virtual void setXY1(int,int);
	virtual void setXY2(int,int);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void resizeProlog(NodeFigure* aNode = NIL);
	virtual void setModelSpecificSymbolAll();
	virtual void clearLists();
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void deleteNeighbors();
	virtual void invalidate();
	virtual void clearMeAndNeighbors(CDC *dcp);
	virtual void setController(COODView *ptr);
	virtual void setSpecificDataMembers();
	virtual BOOL isEditable();
	virtual BOOL isNeighborConnection(Figure *node);
	virtual void resetOneLineTextIfObsolete(Text *aText);
	virtual void getExclusiveClipRect(int &x1,int &y1,int &x2,int &y2);
	virtual BOOL startEdit();
	virtual BOOL containedWithin(int x1,int y1,int x2,int y2);
	virtual void setMoveAllFlag(BOOL flag);
	COODView *controller();
	void setPopupPointer(Popup *ptr);
	static void FillPolygon(CDC* dcp,POINT* points,int npoint);
	static void DrawLine(CDC* dcp,int x1,int y1,int x2,int y2,int thickness = 1,int style = SOLID);
	static int GetMax(int x,int y,int z = -OODMAXINT);
	static int GetMin(int x,int y,int z = OODMAXINT);
};

#endif
