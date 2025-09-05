// TriggerText.h: interface for the TriggerText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIGGERTEXT_H__FF8A8D49_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_TRIGGERTEXT_H__FF8A8D49_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectionText.h"

class TriggerText : public ConnectionText  
{
	DECLARE_SERIAL(TriggerText)
public:
	TriggerText();
	TriggerText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~TriggerText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
};

#endif // !defined(AFX_TRIGGERTEXT_H__FF8A8D49_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_)
