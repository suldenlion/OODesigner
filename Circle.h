// Circle.h: interface for the Circle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLE_H__BDE60B62_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_CIRCLE_H__BDE60B62_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TwoPointFigure.h"

class Circle : public TwoPointFigure  
{
	DECLARE_SERIAL(Circle)
protected : // member functions
	void makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn);
public : // member functions
	virtual ~Circle();
	Circle();
	Circle(COODView *controller,int x,int y,Popup *popup);
	Circle(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup);
	virtual void Serialize(CArchive& ar);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual BOOL isTroublesomeToModifyObject();
	BOOL setFollowing2(int x,int y);
};

#endif // !defined(AFX_CIRCLE_H__BDE60B62_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_)
