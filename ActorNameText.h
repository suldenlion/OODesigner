// ActorNameText.h: interface for the ActorNameText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTORNAMETEXT_H__63F85921_CD0F_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_ACTORNAMETEXT_H__63F85921_CD0F_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Text.h"

class ActorNameText : public Text  
{
	DECLARE_SERIAL(ActorNameText)
private:
	Actor *_master;
	void adjustXY1Coord();
public:
	ActorNameText();
	ActorNameText(COODView *controller,Actor *master,int ox,int oy,Popup *popup);
	virtual void Serialize(CArchive& ar);
	void setMaster(Actor *master) { _master = master; }
	virtual ~ActorNameText();
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual BOOL shouldBeDeleted();
	virtual int insert(char* keypressed);
	virtual void goNextLine();
	virtual BOOL delLine();
	virtual BOOL delChar();
	virtual BOOL delCharBack();
	virtual void bye();
	virtual void draw(CDC* dcp);
};

#endif // !defined(AFX_ACTORNAMETEXT_H__63F85921_CD0F_11D3_BBC8_00A0C9BA6734__INCLUDED_)
