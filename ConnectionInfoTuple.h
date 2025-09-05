// ConnectionInfoTuple.h: interface for the ConnectionInfoTuple class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTIONINFOTUPLE_H__9FC36301_056E_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_CONNECTIONINFOTUPLE_H__9FC36301_056E_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "Figure.h"

#include "XCoord.h"
#include "YCoord.h"

class ConnectionInfoTuple : public CObject {
	DECLARE_SERIAL(ConnectionInfoTuple)
public:
	XCoord _x;
	YCoord _y;
protected : // data members
	NodeFigure* _nodeFigurePtr;
	XCoord _sx;
	YCoord _sy;
	BOOL _mark;
public : // member functions
	virtual ~ConnectionInfoTuple();
	ConnectionInfoTuple();
	ConnectionInfoTuple(NodeFigure* config,int x,int y);
	ConnectionInfoTuple(ConnectionInfoTuple* from);
	virtual void Serialize(CArchive& ar);
	NodeFigure*& nodeFigurePtr();
	int getX();
	int getY();
	BOOL& mark();
	void setX(int x);
	void setY(int y);
	void setXY(int x,int y);
	BOOL meet(Line* aline);
	BOOL meet(int x,int y);
	virtual void setController(COODView *ptr);
	virtual void moveCoord(int dx,int dy);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void locateTupleTextOnProperPosition(Connection *connection) {}
	virtual void draw(CDC* dcp) {}
	virtual void makeRegion(CRgn *sourceClipRgn) {}
	virtual void resetRegion() {}
	virtual void releaseRegion() {}
	virtual void eraseDots(CDC* dcp) {}
	virtual void drawDots(CDC* dcp) {}
	virtual void clear(CDC* dcp) {}
	virtual void setInCanvas(BOOL flag = TRUE) {}
	virtual Figure* onEnter(int x,int y) { return NIL; }
	virtual void drawBoundary(CDC* dcp) {}
	virtual void removeFromTuple(Figure *fig) {}
};

#endif // !defined(AFX_CONNECTIONINFOTUPLE_H__9FC36301_056E_11D3_AC44_00008610434C__INCLUDED_)
