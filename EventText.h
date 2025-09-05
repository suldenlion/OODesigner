// EventText.h: interface for the EventText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTTEXT_H__FF8A8D47_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_EVENTTEXT_H__FF8A8D47_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectionText.h"

class EventText : public ConnectionText  
{
	DECLARE_SERIAL(EventText)
public:
	EventText();
	EventText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~EventText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
};

#endif // !defined(AFX_EVENTTEXT_H__FF8A8D47_D570_11D3_BBC8_00A0C9BA6734__INCLUDED_)
