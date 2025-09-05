// SyncConditionText.h: interface for the SyncConditionText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCCONDITIONTEXT_H__FF8A8D4B_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SYNCCONDITIONTEXT_H__FF8A8D4B_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Text.h"

class SyncConditionText : public Text  
{
	DECLARE_SERIAL(SyncConditionText)
private:
	SynchronizationBar *_master;
	void adjustXY1Coord();
public:
	SyncConditionText();
	SyncConditionText(COODView *controller,SynchronizationBar *master,int ox,int oy,Popup *popup);
	virtual void Serialize(CArchive& ar);
	void setMaster(SynchronizationBar *master) { _master = master; }
	virtual ~SyncConditionText();
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual Figure *container();
	virtual void goNextLine();
	virtual BOOL delLine();
	virtual BOOL delChar();
	virtual BOOL delCharBack();
};

#endif // !defined(AFX_SYNCCONDITIONTEXT_H__FF8A8D4B_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_)
