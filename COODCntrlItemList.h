// COODCntrlItemList.h: interface for the COODCntrlItemList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COODCNTRLITEMLIST_H__7EB5CB1C_2AF3_4324_AD09_783A69EF32C9__INCLUDED_)
#define AFX_COODCNTRLITEMLIST_H__7EB5CB1C_2AF3_4324_AD09_783A69EF32C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Classes.h"
#include "List.h"

class COODCntrlItemList : public List  
{
public:
	COODCntrlItemList();
	virtual ~COODCntrlItemList();
	void addTail(COODCntrlItem* ptr);
	BOOL inList(COODCntrlItem* ptr);
	COODCntrlItem* getFirst();
	COODCntrlItem* getNext();
};

#endif // !defined(AFX_COODCNTRLITEMLIST_H__7EB5CB1C_2AF3_4324_AD09_783A69EF32C9__INCLUDED_)
