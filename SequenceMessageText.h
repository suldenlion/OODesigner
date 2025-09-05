// SequenceMessageText.h: interface for the SequenceMessageText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCEMESSAGETEXT_H__EE496041_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SEQUENCEMESSAGETEXT_H__EE496041_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectionText.h"

class SequenceMessageText : public ConnectionText  
{
	DECLARE_SERIAL(SequenceMessageText)
public:
	SequenceMessageText();
	SequenceMessageText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~SequenceMessageText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void epilog(BOOL skipflag = FALSE);
};

#endif // !defined(AFX_SEQUENCEMESSAGETEXT_H__EE496041_EB7A_11D3_BBC8_00A0C9BA6734__INCLUDED_)
