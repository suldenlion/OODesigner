// ObjectText.h: interface for the ObjectText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTTEXT_H__57FE27E2_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_OBJECTTEXT_H__57FE27E2_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SlaveryText.h"

#define	IAMOBJECTNAME	(0)

class ObjectText : public SlaveryText  
{
	DECLARE_SERIAL(ObjectText)
public:
	ObjectText();
	ObjectText(COODView *controller,EditableFigure *master,int whoAmI,int ox,int oy);
	virtual ~ObjectText();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual int getName(char *buf,int bufSize);
};

#endif // !defined(AFX_OBJECTTEXT_H__57FE27E2_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
