// InterfacePort.h: interface for the InterfacePort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERFACEPORT_H__B71DA060_FFD7_11D3_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_INTERFACEPORT_H__B71DA060_FFD7_11D3_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "ConnectionInfoTuple.h"

class InterfacePort : public ConnectionInfoTuple  
{
	DECLARE_SERIAL(InterfacePort)
private:
	COODView *_controller;
	InterfacePortText *_interfaceName;
	Line *_line;
	Circle *_hole;
public:
	InterfacePort();
	InterfacePort(COODView *controller,NodeFigure* config,int x,int y);
	virtual ~InterfacePort();
	virtual void Serialize(CArchive& ar);
	virtual void moveCoord(int dx,int dy);
	virtual void draw(CDC* dcp);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void clear(CDC* dcp);
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual void setController(COODView *ptr);
	virtual Figure* onEnter(int x,int y);
	virtual void drawBoundary(CDC* dcp);
	virtual void removeFromTuple(Figure *fig);
	InterfacePortText *interfaceName() { return _interfaceName; }
	Circle *hole() { return _hole; }
};

#endif // !defined(AFX_INTERFACEPORT_H__B71DA060_FFD7_11D3_AED4_00A0C9BA6734__INCLUDED_)
