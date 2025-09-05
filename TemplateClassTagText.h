// TemplateClassTagText.h: interface for the TemplateClassTagText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMPLATECLASSTAGTEXT_H__02A2F1C2_F376_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_TEMPLATECLASSTAGTEXT_H__02A2F1C2_F376_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SlaveryText.h"

#define IAMTEMPLATETAGNAME	(0)

class TemplateClassTagText : public SlaveryText  
{
	DECLARE_SERIAL(TemplateClassTagText)
protected:
	virtual BOOL doIHaveToProceed();
public:
	TemplateClassTagText();
	TemplateClassTagText(COODView *controller,TemplateClassTag *master,int whoAmI,int ox,int oy);
	virtual ~TemplateClassTagText();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual Figure *container();
	virtual void goUp();
};

#endif // !defined(AFX_TEMPLATECLASSTAGTEXT_H__02A2F1C2_F376_11D3_BBC8_00A0C9BA6734__INCLUDED_)
