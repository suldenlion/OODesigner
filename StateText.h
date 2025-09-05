// StateText.h: interface for the StateText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATETEXT_H__40E9FAE2_0543_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_STATETEXT_H__40E9FAE2_0543_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SlaveryText.h"

// 다음 매크로의 숫자는 인덱스로 사용됨 
#define	IAMSTATENAME	(0)
#define IAMACTIVITYSTRING 	(1)

class StateText : public SlaveryText {
	DECLARE_SERIAL(StateText)
protected:
	virtual BOOL doIHaveToProceed();
public:
	StateText();
	StateText(COODView *controller,State *master,int whoAmI,int ox,int oy);
	virtual ~StateText();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual int insert(char* keypressed);
};

#endif // !defined(AFX_STATETEXT_H__40E9FAE2_0543_11D3_AC44_00008610434C__INCLUDED_)
