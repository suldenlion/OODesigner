// EndActivity.h: interface for the EndActivity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENDACTIVITY_H__A0CE3CE2_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_ENDACTIVITY_H__A0CE3CE2_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

class EndActivity : public NodeFigure  
{
	DECLARE_SERIAL(EndActivity)
public:
	EndActivity();
	EndActivity(COODView *controller,int x,int y,Popup* popup);
	virtual ~EndActivity();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual void setForeground(COLORREF c);
};

#endif // !defined(AFX_ENDACTIVITY_H__A0CE3CE2_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
