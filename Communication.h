// Communication.h: interface for the Communication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMUNICATION_H__1B2EC721_D7D6_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_COMMUNICATION_H__1B2EC721_D7D6_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Dependency.h"

class Communication : public Dependency  
{
	DECLARE_SERIAL(Communication)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	Communication();
	Communication(COODView *controller,Popup *popup,Line *aLine);
	virtual ~Communication();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a communication"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual void setModelSpecificSymbolAll();
};

#endif // !defined(AFX_COMMUNICATION_H__1B2EC721_D7D6_11D3_BBC8_00A0C9BA6734__INCLUDED_)
