// MessageTextPopup.h: interface for the MessageTextPopup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGETEXTPOPUP_H__8BB21C01_D3C5_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_MESSAGETEXTPOPUP_H__8BB21C01_D3C5_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Popup.h"

class MessageTextPopup : public Popup  
{
private:
	CMenu *_arrowPopup;
public:
	MessageTextPopup();
	virtual ~MessageTextPopup();

};

#endif // !defined(AFX_MESSAGETEXTPOPUP_H__8BB21C01_D3C5_11D3_BBC8_00A0C9BA6734__INCLUDED_)
