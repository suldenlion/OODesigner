// ConnectionText.h: interface for the ConnectionText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTIONTEXT_H__40E9FAE4_0543_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_CONNECTIONTEXT_H__40E9FAE4_0543_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Text.h"

class ConnectionText : public Text {
	DECLARE_SERIAL(ConnectionText)
protected:
	Connection *_connectionPtr;
public:
	ConnectionText();
	ConnectionText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~ConnectionText();
	virtual void Serialize(CArchive& ar);
	Connection *connectionPtr();
	void setConnectionPtr(Connection *);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual Figure *container();
	virtual void disconnectFromContainer();
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void epilog(BOOL skipflag = FALSE);
};

#endif // !defined(AFX_CONNECTIONTEXT_H__40E9FAE4_0543_11D3_AC44_00008610434C__INCLUDED_)
