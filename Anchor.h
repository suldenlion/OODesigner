// Anchor.h: interface for the Anchor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANCHOR_H__A68C7F20_13ED_11D5_A80A_0050DA2D4248__INCLUDED_)
#define AFX_ANCHOR_H__A68C7F20_13ED_11D5_A80A_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Line.h"

class Anchor : public Line  
{
	DECLARE_SERIAL(Anchor)
private:
	Note *_note;
public:
	Anchor();
	Anchor(COODView *controller,Note *note,int x,int y,Popup* popup);
	Anchor(COODView *controller,Note *note,int x1,int y1,int x2,int y2,Popup* popup);
	virtual ~Anchor();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual Figure *container();
	virtual void draw(CDC* dcp);
	virtual void drawing(CDC* dcp,int dx,int dy);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual BOOL wantToResize(int &x,int &y);
	void setNote(Note *note) { _note = note; }
};

#endif // !defined(AFX_ANCHOR_H__A68C7F20_13ED_11D5_A80A_0050DA2D4248__INCLUDED_)
