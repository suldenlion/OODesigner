// ConnectionPopup.h: interface for the ConnectionPopup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTIONPOPUP_H__32DA74E4_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_CONNECTIONPOPUP_H__32DA74E4_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Popup.h"

class ConnectionPopup : public Popup  
{
public:
	ConnectionPopup(char *textName);
	virtual ~ConnectionPopup();

};

#endif // !defined(AFX_CONNECTIONPOPUP_H__32DA74E4_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_)
