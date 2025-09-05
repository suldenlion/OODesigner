#include "stdafx.h"
/* ConnectionList.C */

#include "ConnectionList.h"
// Super Class : List
#include "List.h" // Collaboration
IMPLEMENT_SERIAL(ConnectionList,List,1)

ConnectionList::ConnectionList()
: List()
{
	// Empty
}

ConnectionList::~ConnectionList()
{
	// Empty
}

void ConnectionList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void ConnectionList::push(Connection* ptr)
{
	List::push((CObject*)ptr);
}

Connection* ConnectionList::pop()
{
	return (Connection *)List::pop();
}

Connection* ConnectionList::top()
{
	return (Connection *)List::top();
}

void ConnectionList::insert(Connection* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

void ConnectionList::append(Connection* ptr)
{
	List::append((CObject*)ptr);
}

BOOL ConnectionList::inList(Connection* ptr)
{
	return List::inList((CObject*)ptr);
}

BOOL ConnectionList::replacePointer(Connection* from,Connection* to)
{
	return List::replacePointer((CObject*)from,(CObject*)to);
}

void ConnectionList::remove(Connection* ptr)
{
	List::remove((CObject*)ptr);
}

Connection* ConnectionList::getFirst()
{
	return (Connection *)List::getFirst();
}

Connection* ConnectionList::getNext()
{
	return (Connection *)List::getNext();
}

Connection* ConnectionList::getLast()
{
	return (Connection *)List::getLast();
}

Connection* ConnectionList::getBack()
{
	return (Connection *)List::getBack();
}

