// Note.h: interface for the Note class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTE_H__6E699E41_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_NOTE_H__6E699E41_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditableFigure.h"

#define NOTE_INIT_WIDTH	(80)
#define XGAP_NOTE		(15)
#define YGAP_NOTE		(10)

class Note : public EditableFigure  
{
private:
	BOOL _moveAllFlag;
	AnchorList *_anchors;
public:
	DECLARE_SERIAL(Note)
public:
	Note();
	Note(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual ~Note();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual BOOL needCentering();
	virtual void clear(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void drawBoundaryEx(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual void setFocus(int x = -OODMAXINT, int y = -OODMAXINT);
	virtual BOOL wantToResize(int &x,int &y);
	virtual BOOL wantToMove(int x,int y);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual BOOL onEnter(int x,int y);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void deleteFocusObject();
	virtual void setController(COODView *ptr);
	virtual BOOL containedWithin(int x1,int y1,int x2,int y2);
	virtual void epilog(BOOL skipflag = FALSE);
	virtual void bye();

	void addAnchor(Anchor *anchor);
};

#endif // !defined(AFX_NOTE_H__6E699E41_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_)
