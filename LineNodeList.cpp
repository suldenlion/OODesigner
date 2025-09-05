#include "stdafx.h"
/* LineNodeList.C */

#include "LineNodeList.h"
// Super Class : List

#include "ListNode.h" // collaboration
#include "LineNode.h" // collaboration

IMPLEMENT_SERIAL(LineNodeList,List,1)

LineNodeList::LineNodeList()
: List()
{
	// Empty
}

LineNodeList::~LineNodeList()
{
	// Empty
}

void LineNodeList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

LineNode* LineNodeList::top()
{
	return (LineNode*)List::top();
}

LineNode* LineNodeList::rear()
{
	return (LineNode*)List::rear();
}

void LineNodeList::insert(LineNode* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

void LineNodeList::append(LineNode* ptr)
{
	List::append((CObject*)ptr);
}

BOOL LineNodeList::inList(LineNode* ptr)
{
	return List::inList((CObject*)ptr);
}

BOOL LineNodeList::replacePointer(LineNode* from,LineNode* to)
{
	return List::replacePointer((CObject*)from,(CObject*)to);
}

void LineNodeList::remove(LineNode* ptr,BOOL vanish)
{
	if (vanish == FALSE) {
		List::remove((CObject*)ptr);
		return;
	}
	LineNode *tmp = getFirst();
	while(tmp != NIL) {
		if (tmp != ptr) {
			tmp->removeAfter(ptr);
			tmp->removeBefore(ptr);
		}
		tmp = getNext();
	}
	List::remove((CObject*)ptr);
}

LineNode* LineNodeList::getFirst()
{
	return (LineNode *)List::getFirst();
}

LineNode* LineNodeList::getNext()
{
	return (LineNode *)List::getNext();
}

LineNode* LineNodeList::getLast()
{
	return (LineNode *)List::getLast();
}

LineNode* LineNodeList::getBack()
{
	return (LineNode *)List::getBack();
}

