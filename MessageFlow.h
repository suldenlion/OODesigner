// MessageFlow.h: interface for the MessageFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEFLOW_H__57FE27E3_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_MESSAGEFLOW_H__57FE27E3_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class MessageFlow : public Connection  
{
	DECLARE_SERIAL(MessageFlow)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	MessageFlow();
	MessageFlow(COODView *controller,Popup *popup,Line *aLine);
	virtual ~MessageFlow();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a message flow"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual void setTextPosition(int d1,int d2,int d3);
	MessageText* selectOrCreateText();
};

#endif // !defined(AFX_MESSAGEFLOW_H__57FE27E3_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
