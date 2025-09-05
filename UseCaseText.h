// UseCaseText.h: interface for the UseCaseText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USECASETEXT_H__C7F80BE2_CDAB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_USECASETEXT_H__C7F80BE2_CDAB_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "SlaveryText.h"

#define IAMUSECASENAME	(0)

class UseCaseText : public SlaveryText  
{
	DECLARE_SERIAL(UseCaseText)
public:
	UseCaseText();
	UseCaseText(COODView *controller,UseCase *master,int whoAmI,int ox,int oy);
	virtual void Serialize(CArchive& ar);
	virtual ~UseCaseText();
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual int insert(char* keypressed);
};

#endif // !defined(AFX_USECASETEXT_H__C7F80BE2_CDAB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
