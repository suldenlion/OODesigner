#include "stdafx.h"
/* SlaveryTextList.C */

#include "SlaveryTextList.h"
// Super Class : List
#include "List.h" // Collaboration
IMPLEMENT_SERIAL(SlaveryTextList,List,1)

SlaveryTextList::SlaveryTextList()
: List()
{
	// Empty
}

SlaveryTextList::~SlaveryTextList()
{
	// Empty
}


void SlaveryTextList::Serialize(CArchive& ar)
{
	List::Serialize(ar);   
}

void SlaveryTextList::push(SlaveryText* ptr)
{
	List::push((CObject*)ptr);
}

SlaveryText* SlaveryTextList::pop()
{
	return (SlaveryText *)List::pop();
}

SlaveryText* SlaveryTextList::top()
{
	return (SlaveryText *)List::top();
}

SlaveryText* SlaveryTextList::at(int pos)
{
	return (SlaveryText *)List::at(pos);
}

void SlaveryTextList::insert(SlaveryText* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

void SlaveryTextList::append(SlaveryText* ptr)
{
	List::append((CObject*)ptr);
}

BOOL SlaveryTextList::inList(SlaveryText* ptr)
{
	return List::inList((CObject*)ptr);
}

BOOL SlaveryTextList::replacePointer(SlaveryText* from,SlaveryText* to)
{
	return List::replacePointer((CObject*)from,(CObject*)to);
}

void SlaveryTextList::remove(SlaveryText* ptr)
{
	List::remove((CObject*)ptr);
}

SlaveryText* SlaveryTextList::getFirst()
{
	return (SlaveryText*)List::getFirst();
}

SlaveryText* SlaveryTextList::getNext()
{
	return (SlaveryText*)List::getNext();
}

SlaveryText* SlaveryTextList::getLast()
{
	return (SlaveryText*)List::getLast();
}

SlaveryText* SlaveryTextList::getBack()
{
	return (SlaveryText*)List::getBack();
}

