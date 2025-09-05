// HardwareNode.h: interface for the HardwareNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDWARENODE_H__BC2C6EC1_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_HARDWARENODE_H__BC2C6EC1_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

class HardwareNode : public NodeFigure  
{
	DECLARE_SERIAL(HardwareNode)
private:
	Line *_line1;
	Line *_line2;
	Line *_line3;
	Line *_line4;
	Line *_line5;
	/* 이 좌표 값들은 origin을 고려하지 않은 절대값 들이다. */ 
	int _savedX2;
	int _savedY2;
	Text *_nodeName;
	void recalcDecorationsCoord();
	void drawDecoLines(CDC* dcp);
public:
	HardwareNode();
	HardwareNode(COODView *controller,int ox,int oy,Popup *popup);
	virtual ~HardwareNode();
	virtual void Serialize(CArchive& ar);
	Text *nodeName() { return _nodeName; }
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
	virtual void drawing(CDC* dcp,int dx,int dy);
};

#endif // !defined(AFX_HARDWARENODE_H__BC2C6EC1_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_)
