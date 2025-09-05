// ActivationBarList.h: interface for the ActivationBarList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTIVATIONBARLIST_H__172607E4_E773_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_ACTIVATIONBARLIST_H__172607E4_E773_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "List.h"

class ActivationBarList : public List  
{
	DECLARE_SERIAL(ActivationBarList)
public:
	ActivationBarList();
	virtual ~ActivationBarList();
	virtual void Serialize(CArchive& ar);
	void insert(ActivationBar* ptr);
	BOOL inList(ActivationBar* ptr);
	void remove(ActivationBar* ptr);
	ActivationBar* getFirst();
	ActivationBar* getNext();
	ActivationBar* getLast();
	ActivationBar* getBack();
};

#endif // !defined(AFX_ACTIVATIONBARLIST_H__172607E4_E773_11D3_BBC8_00A0C9BA6734__INCLUDED_)
