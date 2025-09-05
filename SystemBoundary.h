// SystemBoundary.h: interface for the SystemBoundary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMBOUNDARY_H__F2FBDB21_D268_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SYSTEMBOUNDARY_H__F2FBDB21_D268_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

class SystemBoundary : public NodeFigure  
{
	DECLARE_SERIAL(SystemBoundary)
	Text *_systemName;
public:
	SystemBoundary();
	SystemBoundary(COODView *controller,int ox,int oy,Popup *popup);
	virtual ~SystemBoundary();
	virtual void Serialize(CArchive& ar);
	Text *systemName() { return _systemName; }
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

#endif // !defined(AFX_SYSTEMBOUNDARY_H__F2FBDB21_D268_11D3_BBC8_00A0C9BA6734__INCLUDED_)
