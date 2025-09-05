// SynchronizationBar.h: interface for the SynchronizationBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCHRONIZATIONBAR_H__A0CE3CE3_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SYNCHRONIZATIONBAR_H__A0CE3CE3_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

#define INIT_SYNC_BAR_WIDTH		(100)
#define SYNC_BAR_THICKNESS		(4)
#define CONDITION_DX_FROM_X2	(10)

class SynchronizationBar : public NodeFigure  
{
	DECLARE_SERIAL(SynchronizationBar)
private:
	SyncConditionText* _conditionText;
public:
	SynchronizationBar();
	SynchronizationBar(COODView *controller,int x,int y,Popup* popup);
	virtual ~SynchronizationBar();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual BOOL adjustLine(Line *line,BOOL startPoint);
	virtual void setFocus(int x = -OODMAXINT, int y = -OODMAXINT);
	virtual BOOL startEdit();
	virtual void clear(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual BOOL onEnter(int x,int y);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void move(CDC*,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual void bye();
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void setController(COODView *ptr);
};

#endif // !defined(AFX_SYNCHRONIZATIONBAR_H__A0CE3CE3_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
