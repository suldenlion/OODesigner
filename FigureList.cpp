#include "stdafx.h"
/* FigureList.C */

#include "FigureList.h"
// Super Class : List
#include "List.h" // Collaboration
#include "KtgMacro.h"
#include "UnsignedLong.h"
#include "Figure.h"

IMPLEMENT_SERIAL(FigureList,List,1)

FigureList::FigureList()
: List()
{
	// Empty
}

FigureList::~FigureList()
{
	// Empty
}

void FigureList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void FigureList::push(Figure* ptr)
{
	List::push((CObject*)ptr);
}

Figure* FigureList::pop()
{
	return (Figure *)List::pop();
}

Figure* FigureList::top()
{
	return (Figure *)List::top();
}

void FigureList::enter(Figure* ptr)
{
	List::enter((CObject*)ptr);
}

Figure* FigureList::leave()
{
	return (Figure *)List::leave();
}

Figure* FigureList::front()
{
	return (Figure *)List::front();
}

Figure* FigureList::rear()
{
	return (Figure *)List::rear();
}

void FigureList::insert(Figure* ptr,int tag)
{
	if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS)) {
		List::insert((CObject*)ptr,tag);
	} else {
		if (tag != ABSOLUTELY && inList(ptr)) return;
		List::insertAt((CObject*)ptr,0);
//		List::insert((CObject*)ptr,tag);
	}
}

void FigureList::append(Figure* ptr)
{
	List::append((CObject*)ptr);
}

void FigureList::addTail(Figure* ptr)
{
	List::insert((CObject*)ptr,0);
}

void FigureList::addFront(Figure* ptr)
{
	List::insertAt((CObject*)ptr,0);
}

BOOL FigureList::inList(Figure* ptr)
{
	return List::inList((CObject*)ptr);
}

BOOL FigureList::replacePointer(Figure* from,Figure* to)
{
	return List::replacePointer((CObject*)from,(CObject*)to);
}

void FigureList::remove(Figure* ptr)
{
	List::remove((CObject*)ptr);
}

Figure* FigureList::getFirst()
{
	return (Figure *)List::getFirst();
}

Figure* FigureList::getNext()
{
	return (Figure *)List::getNext();
}

Figure* FigureList::getLast()
{
	return (Figure *)List::getLast();
}

Figure* FigureList::getBack()
{
	return (Figure *)List::getBack();
}

