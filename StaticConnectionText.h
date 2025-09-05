// StaticConnectionText.h: interface for the StaticConnectionText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATICCONNECTIONTEXT_H__542FE3E1_D1CA_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_STATICCONNECTIONTEXT_H__542FE3E1_D1CA_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectionText.h"

class StaticConnectionText : public ConnectionText  
{
	DECLARE_SERIAL(StaticConnectionText)
public:
	StaticConnectionText();
	StaticConnectionText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~StaticConnectionText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual BOOL isEditable();
	virtual void epilog(BOOL skipflag = FALSE);
};

#endif // !defined(AFX_STATICCONNECTIONTEXT_H__542FE3E1_D1CA_11D3_BBC8_00A0C9BA6734__INCLUDED_)
