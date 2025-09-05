// ArgumentList.h: interface for the ArgumentList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARGUMENTLIST_H__66BEBAC3_144D_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_ARGUMENTLIST_H__66BEBAC3_144D_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "List.h"

class ArgumentList : public List  
{
public:
	ArgumentList();
	virtual ~ArgumentList();
	// 이 함수는 default argument 를 포함하는 경우 ...
	void getAsCArgument(CString &arg,BOOL withDefaultArgFlag);
	void getArgumentString(CString &arg);
	void insert(ArgumentInfo* ptr,int tag = 0);
	BOOL inList(ArgumentInfo* ptr);
	void remove(ArgumentInfo* ptr,int tag = 0);
	ArgumentInfo* getFirst();
	ArgumentInfo* getNext();
};

#endif // !defined(AFX_ARGUMENTLIST_H__66BEBAC3_144D_11D4_AED4_00A0C9BA6734__INCLUDED_)
