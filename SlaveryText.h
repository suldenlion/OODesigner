// SlaveryText.h: interface for the SlaveryText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLAVERYTEXT_H__9C23B745_01AE_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_SLAVERYTEXT_H__9C23B745_01AE_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Text.h"

class SlaveryText : public Text {
	DECLARE_SERIAL(SlaveryText)
protected:
	int _whoAmI;
	EditableFigure *_master;
protected:
	SlaveryText();
	SlaveryText(COODView *controller,EditableFigure *master,int whoAmI,int ox,int oy);
	virtual int delEmptyLines();
	virtual BOOL doIHaveToProceed();
public:
	virtual ~SlaveryText();
	virtual void Serialize(CArchive& ar);
	virtual void activateNextText();
	virtual void activatePrevText();
	EditableFigure *master() { return _master; }
	void setMaster(EditableFigure *master) { _master = master; }
	int whoAmI() { return _whoAmI; }
	virtual BOOL isObsolete() { return FALSE; }
	virtual void bye();
	virtual BOOL delLine();
	virtual BOOL delChar();
	virtual BOOL delCharBack();
	virtual void goUp();
	virtual void goDown();
	virtual void goNextLine();
	virtual int insert(char* keypressed);
	virtual Figure* born(Figure* ptr = NIL);
	virtual int getName(char *buf,int bufSize);
	virtual void draw(CDC* dcp);
};

#endif // !defined(AFX_SLAVERYTEXT_H__9C23B745_01AE_11D3_AC44_00008610434C__INCLUDED_)
