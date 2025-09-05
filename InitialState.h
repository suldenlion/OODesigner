// InitialState.h: interface for the InitialState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INITIALSTATE_H__BDE60B61_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_INITIALSTATE_H__BDE60B61_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

class InitialState : public NodeFigure  
{
	DECLARE_SERIAL(InitialState)
public:
	InitialState();
	InitialState(COODView *controller,int x,int y,Popup* popup);
	virtual ~InitialState();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual void setForeground(COLORREF c);
	virtual void setBackground(COLORREF c);
};

#endif // !defined(AFX_INITIALSTATE_H__BDE60B61_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_)
