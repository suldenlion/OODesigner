// Trigger.h: interface for the Trigger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIGGER_H__6839D647_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_TRIGGER_H__6839D647_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class Trigger : public Connection  
{
	DECLARE_SERIAL(Trigger)
protected:
	int getJointPoints(CPoint*& points);
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	Trigger();
	Trigger(COODView *controller,Popup *popup,Line *aLine);
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a trigger"; }
	virtual void setModelSpecificSymbolAll();
	virtual Figure* born(Figure* ptr = NIL);
	virtual ~Trigger();
	virtual UnsignedLong* whoAreYou();
	virtual void draw(CDC *dcp);
	TriggerText* selectOrCreateText();
};

#endif // !defined(AFX_TRIGGER_H__6839D647_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_)
