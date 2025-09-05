// ActivationBarList.cpp: implementation of the ActivationBarList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ActivationBarList.h"
#include "KtgMacro.h"
#include "UnsignedLong.h"
#include "ActivationBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ActivationBarList,List,1)

ActivationBarList::ActivationBarList()
: List()
{
	// Empty
}

ActivationBarList::~ActivationBarList()
{

}

void ActivationBarList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

BOOL ActivationBarList::inList(ActivationBar* ptr)
{
	return List::inList((CObject*)ptr);
}


void ActivationBarList::remove(ActivationBar* ptr)
{
	List::remove((CObject*)ptr);
}

// 실제로 insertion 소트식으로 들어가야 한다.
void ActivationBarList::insert(ActivationBar* ptr)
{
	int indexToInsert = 0;
	int yToInsert = ptr->getY1();
	ActivationBar *aBar = getFirst();
	while(aBar != NIL) {
		if (yToInsert < aBar->getY1()) break;
		indexToInsert++;
		aBar = getNext();
	}
	List::insertAt((CObject*)ptr,indexToInsert);
}

ActivationBar* ActivationBarList::getFirst()
{
	return (ActivationBar *)List::getFirst();
}

ActivationBar* ActivationBarList::getNext()
{
	return (ActivationBar *)List::getNext();
}

ActivationBar* ActivationBarList::getLast()
{
	return (ActivationBar *)List::getLast();
}

ActivationBar* ActivationBarList::getBack()
{
	return (ActivationBar *)List::getBack();
}

