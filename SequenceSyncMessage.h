// SequenceSyncMessage.h: interface for the SequenceSyncMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCESYNCMESSAGE_H__AF496601_E7BB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SEQUENCESYNCMESSAGE_H__AF496601_E7BB_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "SimpleConnection.h"

class SequenceSyncMessage : public SimpleConnection  
{
	DECLARE_SERIAL(SequenceSyncMessage)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	SequenceSyncMessage();
	SequenceSyncMessage(COODView *controller,Popup *popup,Line *aLine);
	virtual ~SequenceSyncMessage();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a sync message"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual void setModelSpecificSymbolAll();
	virtual void tailorEndLines(NodeFigure *lastNode);
	virtual void tailorEndLinesAll();
	virtual void epilog(BOOL skipflag = FALSE);
	virtual void draw(CDC* dcp);
	SequenceMessageText* selectOrCreateText();
};

#endif // !defined(AFX_SEQUENCESYNCMESSAGE_H__AF496601_E7BB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
