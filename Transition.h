// Transition.h: interface for the Transition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSITION_H__BDE60B68_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_TRANSITION_H__BDE60B68_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class Transition : public Connection  
{
	DECLARE_SERIAL(Transition)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	Transition();
	Transition(COODView *controller,Popup *popup,Line *aLine);
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a transition"; }
	virtual void setModelSpecificSymbolAll();
	virtual Figure* born(Figure* ptr = NIL);
	virtual ~Transition();
	virtual UnsignedLong* whoAreYou();
	virtual BOOL isSelfConnectionAllowable() { return TRUE; }
	EventText* selectOrCreateText();
};

#endif // !defined(AFX_TRANSITION_H__BDE60B68_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_)
