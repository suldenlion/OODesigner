// UseCaseLink.h: interface for the UseCaseLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USECASELINK_H__25252362_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_USECASELINK_H__25252362_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SimpleConnection.h"

class UseCaseLink : public SimpleConnection  
{
	DECLARE_SERIAL(UseCaseLink)
public:
	UseCaseLink();
	UseCaseLink(COODView *controller,Popup *popup,Line *aLine);
	virtual void Serialize(CArchive& ar);
	virtual ~UseCaseLink();
	virtual char *connectionClassName() { return "an association"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
};

#endif // !defined(AFX_USECASELINK_H__25252362_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_)
