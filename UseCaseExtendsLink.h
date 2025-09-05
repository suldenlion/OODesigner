// UseCaseExtendsLink.h: interface for the UseCaseExtendsLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USECASEEXTENDSLINK_H__9B8DEE01_D182_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_USECASEEXTENDSLINK_H__9B8DEE01_D182_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SimpleConnection.h"

class UseCaseExtendsLink : public SimpleConnection  
{
	DECLARE_SERIAL(UseCaseExtendsLink)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	UseCaseExtendsLink();
	UseCaseExtendsLink(COODView *controller,Popup *popup,Line *aLine);
	virtual ~UseCaseExtendsLink();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "an extends link"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual void setModelSpecificSymbolAll();
};

#endif // !defined(AFX_USECASEEXTENDSLINK_H__9B8DEE01_D182_11D3_BBC8_00A0C9BA6734__INCLUDED_)
