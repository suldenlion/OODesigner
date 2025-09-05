// WidePackage.h: interface for the WidePackage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIDEPACKAGE_H__30307B03_237F_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_WIDEPACKAGE_H__30307B03_237F_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

class WidePackage : public NodeFigure  
{
	DECLARE_SERIAL(WidePackage)
private:
	// 이 데이타 멤버들은 NodeFigure 클래스에 의해 관리되기 때문에
	// 이 클래스에서 destruction 시킬 필요가 없다.
	Line *_hatLeft;
	Line *_hatUp;
	Line *_hatRight;
	/* 이 좌표 값들은 origin을 고려하지 않은 절대값 들이다. */ 
	int _savedX2;
	int _savedY2;
	Text *_packageName;
public:
	WidePackage();
	WidePackage(COODView *controller,int ox,int oy,Popup *popup);
	virtual ~WidePackage();
	virtual void Serialize(CArchive& ar);
	Text *packageName() { return _packageName; }
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
	virtual void setSpecificDataMembers();
};

#endif // !defined(AFX_WIDEPACKAGE_H__30307B03_237F_11D5_A72B_0050DA2D4248__INCLUDED_)
