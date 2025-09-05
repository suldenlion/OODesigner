// ComponentText.h: interface for the ComponentText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPONENTTEXT_H__BC2C6EC3_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_COMPONENTTEXT_H__BC2C6EC3_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SlaveryText.h"

#define IAMCOMPONENTNAME	(0)

#define DEFAULT_NO_OF_LINES	(3)

class ComponentText : public SlaveryText  
{
	DECLARE_SERIAL(ComponentText)
protected:
	virtual int delEmptyLines();
public:
	ComponentText();
	ComponentText(COODView *controller,ComponentTemplate *master,int whoAmI,int ox,int oy);
	virtual ~ComponentText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void goNextLine();
	virtual BOOL delLine();
};

#endif // !defined(AFX_COMPONENTTEXT_H__BC2C6EC3_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_)
