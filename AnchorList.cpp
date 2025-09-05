// AnchorList.cpp: implementation of the AnchorList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "AnchorList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(AnchorList,List,1)

AnchorList::AnchorList()
: List()
{
	// Empty
}

AnchorList::~AnchorList()
{
	// Empty
}

void AnchorList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void AnchorList::push(Anchor* ptr)
{
	List::push((CObject*)ptr);
}

Anchor* AnchorList::pop()
{
	return (Anchor *)List::pop();
}

Anchor* AnchorList::top()
{
	return (Anchor *)List::top();
}

void AnchorList::insert(Anchor* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

void AnchorList::append(Anchor* ptr)
{
	List::append((CObject*)ptr);
}

BOOL AnchorList::inList(Anchor* ptr)
{
	return List::inList((CObject*)ptr);
}

BOOL AnchorList::replacePointer(Anchor* from,Anchor* to)
{
	return List::replacePointer((CObject*)from,(CObject*)to);
}

void AnchorList::remove(Anchor* ptr)
{
	List::remove((CObject*)ptr);
}

Anchor* AnchorList::getFirst()
{
	return (Anchor*)List::getFirst();
}

Anchor* AnchorList::getNext()
{
	return (Anchor*)List::getNext();
}

Anchor* AnchorList::getLast()
{
	return (Anchor*)List::getLast();
}

Anchor* AnchorList::getBack()
{
	return (Anchor*)List::getBack();
}

