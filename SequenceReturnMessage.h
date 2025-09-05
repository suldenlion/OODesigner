// SequenceReturnMessage.h: interface for the SequenceReturnMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCERETURNMESSAGE_H__EE496043_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SEQUENCERETURNMESSAGE_H__EE496043_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SequenceSyncMessage.h"

class SequenceReturnMessage : public SequenceSyncMessage  
{
	DECLARE_SERIAL(SequenceReturnMessage)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	SequenceReturnMessage();
	SequenceReturnMessage(COODView *controller,Popup *popup,Line *aLine);
	virtual ~SequenceReturnMessage();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a async message"; }
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void draw(CDC* dcp);
	virtual void clear(CDC* dcp);
	virtual void drawing(CDC* dcp,int dx,int dy);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void setModelSpecificSymbolAll();
};

#endif // !defined(AFX_SEQUENCERETURNMESSAGE_H__EE496043_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_)
