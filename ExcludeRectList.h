// ExcludeRectList.h: interface for the ExcludeRectList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCLUDERECTLIST_H__BCE8070E_184B_48E9_A391_17DF4CE080B3__INCLUDED_)
#define AFX_EXCLUDERECTLIST_H__BCE8070E_184B_48E9_A391_17DF4CE080B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "List.h"

class ExcludeRectList : public List  
{
public:
	ExcludeRectList();
	virtual ~ExcludeRectList();
	void addTail(ExcludeRect* ptr);
	void remove(Figure* ptr);
	ExcludeRect* getFirst();
	ExcludeRect* getNext();
};

#endif // !defined(AFX_EXCLUDERECTLIST_H__BCE8070E_184B_48E9_A391_17DF4CE080B3__INCLUDED_)
