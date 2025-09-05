// SequenceAsyncMessage.h: interface for the SequenceAsyncMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCEASYNCMESSAGE_H__EE496042_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SEQUENCEASYNCMESSAGE_H__EE496042_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SequenceSyncMessage.h"

class SequenceAsyncMessage : public SequenceSyncMessage  
{
	DECLARE_SERIAL(SequenceAsyncMessage)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	SequenceAsyncMessage();
	SequenceAsyncMessage(COODView *controller,Popup *popup,Line *aLine);
	virtual ~SequenceAsyncMessage();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a async message"; }
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void setModelSpecificSymbolAll();
};

#endif // !defined(AFX_SEQUENCEASYNCMESSAGE_H__EE496042_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_)
