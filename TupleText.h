// TupleText.h: interface for the TupleText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TUPLETEXT_H__282F3581_F677_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_TUPLETEXT_H__282F3581_F677_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// 이 텍스트는 role name과 multiplicity를 처리하기 위한 거다.
#include "Classes.h"
#include "OneLineText.h"

#define ROLE_NAME_ID		(1)
#define MULTIPLICITY_ID		(2)
#define QUALIFICATION_ID	(3)

class TupleText : public OneLineText  
{
	DECLARE_SERIAL(TupleText)
protected:
	int _whichText;
	AnytionInfoTuple *_tuplePtr;
public:
	TupleText();
	TupleText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~TupleText();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	AnytionInfoTuple *getTuplePtr() { return _tuplePtr; }
	void setTuplePtr(AnytionInfoTuple *tuplePtr) {
		_tuplePtr = tuplePtr;
	}
	int getWhichText() { return _whichText; }
	void setWhichText(int whichText) {
		_whichText = whichText;
	}
};

#endif // !defined(AFX_TUPLETEXT_H__282F3581_F677_11D3_BBC8_00A0C9BA6734__INCLUDED_)
