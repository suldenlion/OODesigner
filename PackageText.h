// PackageText.h: interface for the PackageText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKAGETEXT_H__D5BAD0C1_C4F8_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_PACKAGETEXT_H__D5BAD0C1_C4F8_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SlaveryText.h"

#define IAMPACKAGENAME	(0)

class PackageText : public SlaveryText  
{
	DECLARE_SERIAL(PackageText)
public:
	PackageText();
	PackageText(COODView *controller,PackageTemplate *master,int whoAmI,int ox,int oy);
	virtual ~PackageText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
};

#endif // !defined(AFX_PACKAGETEXT_H__D5BAD0C1_C4F8_11D3_BBC8_00A0C9BA6734__INCLUDED_)
