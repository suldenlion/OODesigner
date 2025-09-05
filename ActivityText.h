// ActivityText.h: interface for the ActivityText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTIVITYTEXT_H__6839D645_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_ACTIVITYTEXT_H__6839D645_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SlaveryText.h"

#define IAMACTIVITYNAME	(0)

class ActivityText : public SlaveryText  
{
	DECLARE_SERIAL(ActivityText)
public:
	ActivityText();
	ActivityText(COODView *controller,Activity *master,int whoAmI,int ox,int oy);
	virtual ~ActivityText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual int insert(char* keypressed);
};

#endif // !defined(AFX_ACTIVITYTEXT_H__6839D645_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_)
