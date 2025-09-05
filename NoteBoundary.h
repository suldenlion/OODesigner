// NoteBoundary.h: interface for the NoteBoundary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEBOUNDARY_H__6E699E40_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_NOTEBOUNDARY_H__6E699E40_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Box.h"
#define CORNER_GAP	(12)

class NoteBoundary : public Box  
{
	DECLARE_SERIAL(NoteBoundary)
public : // member functions
	virtual ~NoteBoundary();
	NoteBoundary();
	NoteBoundary(COODView *controller,int x,int y,Popup *popup);
	NoteBoundary(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup);
	virtual void Serialize(CArchive& ar);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual Figure* born(Figure* ptr = NIL);
};

#endif // !defined(AFX_NOTEBOUNDARY_H__6E699E40_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_)
