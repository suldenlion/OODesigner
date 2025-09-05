// State.h: interface for the State class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATE_H__40E9FAE1_0543_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_STATE_H__40E9FAE1_0543_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditableFigure.h"

#define STATE_INIT_WIDTH	(80)
#define XGAP_STATE			(ROUNDBOXBGAP/2)
#define YGAP_STATE			(6)

class State : public EditableFigure {
	DECLARE_SERIAL(State)
protected:
	Line *_savedSeparator;
	int _savedY1PosOfNameText;
	int _savedY2PosOfNameText;
public:
	State();
	State(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual ~State();
	virtual void Serialize(CArchive& ar);
	virtual void setController(COODView *ptr);
	virtual UnsignedLong* whoAreYou();
	virtual void bye();
	virtual BOOL startEdit();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void moveCoord(int dx,int dy);
	virtual void draw(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
};

#endif // !defined(AFX_STATE_H__40E9FAE1_0543_11D3_AC44_00008610434C__INCLUDED_)
