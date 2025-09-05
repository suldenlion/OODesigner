// ActivationBar.h: interface for the ActivationBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTIVATIONBAR_H__172607E3_E773_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_ACTIVATIONBAR_H__172607E3_E773_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Box.h"

class ActivationBar : public Box  
{
	DECLARE_SERIAL(ActivationBar)
public:
	virtual ~ActivationBar();
	ActivationBar();
	ActivationBar(COODView *controller,int x1,int y1,int x2,int y2,Popup *popup);
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
};

#endif // !defined(AFX_ACTIVATIONBAR_H__172607E3_E773_11D3_BBC8_00A0C9BA6734__INCLUDED_)
