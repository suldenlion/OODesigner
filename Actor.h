// Actor.h: interface for the Actor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTOR_H__9AACF121_CCD2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_ACTOR_H__9AACF121_CCD2_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

#define NAMETEXTGAP (10)

class Actor : public NodeFigure  
{
	DECLARE_SERIAL(Actor)
	ActorNameText *_actorName;
public:
	Actor();
	Actor(COODView *controller,int x,int y,Popup* popup);
	virtual ~Actor();
	virtual void Serialize(CArchive& ar);
	ActorNameText *actorName() { return _actorName; }
	virtual void setFocus(int x = -OODMAXINT, int y = -OODMAXINT);
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual void clear(CDC* dcp);
	virtual BOOL onEnter(int x,int y);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void drawing(CDC*,int dx,int dy);
	virtual void move(CDC*,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual Figure* born(Figure* ptr = NIL);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void setController(COODView *ptr);
	virtual BOOL adjustLine(Line *line,BOOL startPoint);
	virtual UnsignedLong* whoAreYou();
	virtual BOOL onBoundaryOrObsolete(LineNodeList *lines);
	virtual void drawBoundary(CDC* dcp);
	virtual BOOL startEdit();
	virtual void bye();
};

#endif // !defined(AFX_ACTOR_H__9AACF121_CCD2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
