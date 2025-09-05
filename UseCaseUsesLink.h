// UseCaseUsesLink.h: interface for the UseCaseUsesLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USECASEUSESLINK_H__25252363_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_USECASEUSESLINK_H__25252363_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SimpleConnection.h"

class UseCaseUsesLink : public SimpleConnection  
{
	DECLARE_SERIAL(UseCaseUsesLink)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	UseCaseUsesLink();
	UseCaseUsesLink(COODView *controller,Popup *popup,Line *aLine);
	virtual ~UseCaseUsesLink();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "an uses link"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual void setModelSpecificSymbolAll();
};

#endif // !defined(AFX_USECASEUSESLINK_H__25252363_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_)
