#include "stdafx.h"
/* LineList.C */

#include "LineList.h"
// Super Class : List
#include "List.h" // Collaboration

IMPLEMENT_SERIAL(LineList,List,1)

LineList::LineList()
: List()
{
	// Empty
}

LineList::~LineList()
{
	// Empty
}

void LineList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void LineList::push(Line* ptr)
{
	List::push((CObject*)ptr);
}

Line* LineList::pop()
{
	return (Line *)List::pop();
}

Line* LineList::top()
{
	return (Line *)List::top();
}

void LineList::insert(Line* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

void LineList::append(Line* ptr)
{
	List::append((CObject*)ptr);
}

BOOL LineList::inList(Line* ptr)
{
	return List::inList((CObject*)ptr);
}

BOOL LineList::replacePointer(Line* from,Line* to)
{
	return List::replacePointer((CObject*)from,(CObject*)to);
}

void LineList::remove(Line* ptr)
{
	List::remove((CObject*)ptr);
}

Line* LineList::getFirst()
{
	return (Line*)List::getFirst();
}

Line* LineList::getNext()
{
	return (Line*)List::getNext();
}

Line* LineList::getLast()
{
	return (Line*)List::getLast();
}

Line* LineList::getBack()
{
	return (Line*)List::getBack();
}

