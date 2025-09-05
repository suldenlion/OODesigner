// OneLineText.h: interface for the OneLineText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONELINETEXT_H__40E9FAE3_0543_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_ONELINETEXT_H__40E9FAE3_0543_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectionText.h"

/* 이 클래스는 주로 multiplicity와 role name을 처리하기 위한거다. */

class OneLineText : public ConnectionText {
	DECLARE_SERIAL(OneLineText)
public:
	OneLineText();
	OneLineText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~OneLineText();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual void disconnectFromContainer();
};

#endif // !defined(AFX_ONELINETEXT_H__40E9FAE3_0543_11D3_AC44_00008610434C__INCLUDED_)
