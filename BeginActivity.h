// BeginActivity.h: interface for the BeginActivity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEGINACTIVITY_H__A0CE3CE1_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_BEGINACTIVITY_H__A0CE3CE1_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

class BeginActivity : public NodeFigure  
{
	DECLARE_SERIAL(BeginActivity)
public:
	BeginActivity();
	BeginActivity(COODView *controller,int x,int y,Popup* popup);
	virtual ~BeginActivity();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual void setForeground(COLORREF c);
	virtual void setBackground(COLORREF c);
};

#endif // !defined(AFX_BEGINACTIVITY_H__A0CE3CE1_CBEB_11D3_BBC8_00A0C9BA6734__INCLUDED_)
