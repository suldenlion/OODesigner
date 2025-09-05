// Activity.h: interface for the Activity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTIVITY_H__6839D646_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_ACTIVITY_H__6839D646_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditableFigure.h"

#define ACTIVITY_INIT_WIDTH		(80)
#define XGAP_ACTIVITY			(15)
#define YGAP_ACTIVITY			(15)

class Activity : public EditableFigure  
{
	DECLARE_SERIAL(Activity)
public:
	Activity();
	Activity(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual ~Activity();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void draw(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
};

#endif // !defined(AFX_ACTIVITY_H__6839D646_CC05_11D3_BBC8_00A0C9BA6734__INCLUDED_)
