// AnchorList.h: interface for the AnchorList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANCHORLIST_H__A68C7F21_13ED_11D5_A80A_0050DA2D4248__INCLUDED_)
#define AFX_ANCHORLIST_H__A68C7F21_13ED_11D5_A80A_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "List.h"

class AnchorList : public List  
{
	DECLARE_SERIAL(AnchorList)
public : // member functions
	AnchorList();
	virtual ~AnchorList();
	virtual void Serialize(CArchive& ar);
	void push(Anchor* ptr);
	Anchor* pop();
	Anchor* top();
	void insert(Anchor* ptr,int tag = 0);
	void append(Anchor* ptr);
	BOOL inList(Anchor* ptr);
	BOOL replacePointer(Anchor* from,Anchor* to);
	void remove(Anchor* ptr);
	Anchor* getFirst();
	Anchor* getNext();
	Anchor* getLast();
	Anchor* getBack();
};

#endif // !defined(AFX_ANCHORLIST_H__A68C7F21_13ED_11D5_A80A_0050DA2D4248__INCLUDED_)
