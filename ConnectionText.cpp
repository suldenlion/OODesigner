// ConnectionText.cpp: implementation of the ConnectionText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ConnectionText.h"
#include "Connection.h"
#include "UnsignedLong.h"
#include "TupleText.h"
#include "AnytionInfoTuple.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ConnectionText,Text,1)

ConnectionText::ConnectionText()
: Text()
{
	_connectionPtr = NIL;
}

ConnectionText::ConnectionText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup)
: Text(controller,ox,oy,popup)
{
	_connectionPtr = connectionPtr;
	if (controller == NIL) return;
}

ConnectionText::~ConnectionText()
{
	_connectionPtr = NIL;
}

void ConnectionText::Serialize(CArchive& ar)
{
	Text::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _connectionPtr;
	} else {
		ar >> _connectionPtr;
	}
}

void ConnectionText::setConnectionPtr(Connection *ptr)
{
	_connectionPtr = ptr;
}

Connection *ConnectionText::connectionPtr()
{
	return _connectionPtr;
}

UnsignedLong* ConnectionText::whoAreYou()
{
	return IAMCONNECTIONTEXT;
}

Figure* ConnectionText::born(Figure* ptr)
{
	ConnectionText *copied;
	if (ptr == NIL) {
		copied = new ConnectionText(NIL,NIL,0,0,NIL);
	} else {
		copied = (ConnectionText *)ptr;
	}
	copied->_connectionPtr = _connectionPtr;
	return (Text::born((Figure *)copied));
}

Figure *ConnectionText::container()
{
	return (Figure *)_connectionPtr;
}

void ConnectionText::disconnectFromContainer()
{
	if (_connectionPtr == NIL) return;
	_connectionPtr->setText(NIL);
	_connectionPtr = NIL;
	return;
}

BOOL ConnectionText::moveProlog(BOOL moveAllFlag)
{
	if (moveAllFlag) {
		return TRUE;
	}
	// Connection 객체로 부터 링크를 잠시 끊는다.
	// move 시작 때 잔상을 없애기 위해 ...
	if (whoAreYou()->isIn(WEAREONELINETEXTS)) {
		// role name or multiplicity 경우임
		// qualification은 아님 : qualification은 움직이지 못하기 때문
		_connectionPtr->removeFromTupleList(this);
	} else {
		_connectionPtr->setText(NIL);
	}
	return FALSE;
}

void ConnectionText::epilog(BOOL skipflag)
{
	if (skipflag) return;
	// Connection 객체로 다시 연결한다.
	if (whoAreYou()->isIn(WEAREONELINETEXTS) == TRUE) {
		TupleText *asTupleText = (TupleText *)this;
		asTupleText->getTuplePtr()->setTupleText(asTupleText);
	} else {
		_connectionPtr->setText(this);
	}
}