// HWConnectionText.h: interface for the HWConnectionText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HWCONNECTIONTEXT_H__32DA74E2_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_HWCONNECTIONTEXT_H__32DA74E2_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectionText.h"

class HWConnectionText : public ConnectionText  
{
	DECLARE_SERIAL(HWConnectionText)
public:
	HWConnectionText();
	HWConnectionText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~HWConnectionText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
};

#endif // !defined(AFX_HWCONNECTIONTEXT_H__32DA74E2_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_)
