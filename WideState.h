// WideState.h: interface for the WideState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIDESTATE_H__62AE4EC0_22A0_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_WIDESTATE_H__62AE4EC0_22A0_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

class WideState : public NodeFigure  
{
	DECLARE_SERIAL(WideState)
private:
	/* 이 좌표 값들은 origin을 고려하지 않은 절대값 들이다. */ 
	int _savedX1;
	int _savedY1;
	int _savedX2;
	int _savedY2;
	Text *_stateName;
	int _nOfSeperators;
	void drawSeparators(CDC *dcp);
public:
	WideState();
	WideState(COODView *controller,int ox,int oy,int nOfSeperators,Popup *popup);
	virtual ~WideState();
	virtual void Serialize(CArchive& ar);
	Text *stateName() { return _stateName; }
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual BOOL wantToResize(int& x,int& y);
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual void move(CDC*,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual void setController(COODView *ptr);
	virtual BOOL startEdit();
	virtual void bye();
	virtual void epilog(BOOL skipflag = FALSE);
};

#endif // !defined(AFX_WIDESTATE_H__62AE4EC0_22A0_11D5_A72B_0050DA2D4248__INCLUDED_)
