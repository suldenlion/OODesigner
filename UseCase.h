// UseCase.h: interface for the UseCase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USECASE_H__C7F80BE1_CDAB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_USECASE_H__C7F80BE1_CDAB_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "EditableFigure.h"

#define USECASE_INIT_WIDTH		(80)
#define XGAP_USECASE			(15)
#define YGAP_USECASE			(15)

class UseCase : public EditableFigure  
{
	DECLARE_SERIAL(UseCase)
public:
	UseCase();
	UseCase(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual void Serialize(CArchive& ar);
	virtual ~UseCase();
	virtual UnsignedLong* whoAreYou();
	virtual void draw(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual Figure* born(Figure* ptr = NIL);
};

#endif // !defined(AFX_USECASE_H__C7F80BE1_CDAB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
