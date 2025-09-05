// FinalState.h: interface for the FinalState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINALSTATE_H__BDE60B67_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_FINALSTATE_H__BDE60B67_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

class FinalState : public NodeFigure  
{
	DECLARE_SERIAL(FinalState)
public:
	FinalState();
	FinalState(COODView *controller,int x,int y,Popup* popup);
	virtual ~FinalState();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual void setForeground(COLORREF c);
};

#endif // !defined(AFX_FINALSTATE_H__BDE60B67_CB18_11D3_BBC8_00A0C9BA6734__INCLUDED_)
