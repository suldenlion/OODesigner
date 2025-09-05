#include "stdafx.h"
/* NodeFigureList.C */

#include "NodeFigureList.h"
// Super Class : List
#include "List.h" // Collaboration

IMPLEMENT_SERIAL(NodeFigureList,List,1)

NodeFigureList::NodeFigureList()
: List()
{
	// Empty
}

NodeFigureList::~NodeFigureList()
{
	// Empty
}

void NodeFigureList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void NodeFigureList::push(NodeFigure* ptr)
{
	List::push((CObject*)ptr);
}

NodeFigure* NodeFigureList::pop()
{
	return (NodeFigure *)List::pop();
}

NodeFigure* NodeFigureList::top()
{
	return (NodeFigure *)List::top();
}

void NodeFigureList::insert(NodeFigure* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

void NodeFigureList::append(NodeFigure* ptr)
{
	List::append((CObject*)ptr);
}

BOOL NodeFigureList::inList(NodeFigure* ptr)
{
	return List::inList((CObject*)ptr);
}

BOOL NodeFigureList::replacePointer(NodeFigure* from,NodeFigure* to)
{
	return List::replacePointer((CObject*)from,(CObject*)to);
}

void NodeFigureList::remove(NodeFigure* ptr,int tag)
{
	List::remove((CObject*)ptr,tag);
}

NodeFigure* NodeFigureList::getFirst()
{
	return (NodeFigure *)List::getFirst();
}

NodeFigure* NodeFigureList::getNext()
{
	return (NodeFigure *)List::getNext();
}

NodeFigure* NodeFigureList::getLast()
{
	return (NodeFigure *)List::getLast();
}

NodeFigure* NodeFigureList::getBack()
{
	return (NodeFigure *)List::getBack();
}

