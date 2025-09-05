// Bucket.h: interface for the Bucket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUCKET_H__B81B31A2_0A48_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_BUCKET_H__B81B31A2_0A48_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Box.h"
#include "FigureList.h"
#include "COODCntrlItemList.h"

class Bucket : public Box  
{
private:
	FigureList _figures;
	COODCntrlItemList _oleItems;
	BOOL _forWideFigure;
public:
	Bucket(COODView *controller);
	virtual ~Bucket();
	virtual UnsignedLong* whoAreYou();
	virtual void draw(CDC* dcp);
	virtual void clear(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual BOOL wantToResize(int &x,int &y);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void epilog(BOOL skipflag = FALSE);
	virtual void resizeProlog(NodeFigure* aNode = NIL);
	void insert(Figure *ptr);
	BOOL hasFigure(Figure *ptr);
	BOOL hasSelection(COODCntrlItem *ptr);
	void clearList();
	BOOL isEmpty();
	FigureList &getFigures() { return _figures; }
	COODCntrlItemList &getOleItems() { return _oleItems; }
	void restoreFigures(FigureList *theList);
	void restoreOleItems(COODDoc *pDoc);
	void setCoord(int x1,int y1,int x2,int y2);
	void collectContainedFigures(FigureList *theList);
	void collectContainedOleItems(COODDoc *pDoc,COODView *pView);
	void copyContainedFigures(FigureList *theList);
	void copyContainedOleItems(COODDoc *pDoc,COODView *pView);
	void copyAllFigures(FigureList *theList);
	void copyAllOleItems(COODDoc *pDoc,COODView *pView);
	BOOL forWideFigure() { return _forWideFigure; }
};

#endif // !defined(AFX_BUCKET_H__B81B31A2_0A48_11D4_AED4_00A0C9BA6734__INCLUDED_)
