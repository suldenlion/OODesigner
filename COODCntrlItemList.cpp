// COODCntrlItemList.cpp: implementation of the COODCntrlItemList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "COODCntrlItemList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COODCntrlItemList::COODCntrlItemList()
{

}

COODCntrlItemList::~COODCntrlItemList()
{

}

void COODCntrlItemList::addTail(COODCntrlItem* ptr)
{
	List::insert((CObject*)ptr,0);
}

BOOL COODCntrlItemList::inList(COODCntrlItem* ptr)
{
	return List::inList((CObject*)ptr);
}

COODCntrlItem* COODCntrlItemList::getFirst()
{
	return (COODCntrlItem *)List::getFirst();
}

COODCntrlItem* COODCntrlItemList::getNext()
{
	return (COODCntrlItem *)List::getNext();
}


