// CITList.cpp: implementation of the CITList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "CITList.h"
#include "KtgMacro.h"
#include "ConnectionInfoTuple.h" // Aggregation

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CITList,List,1)

CITList::CITList()
: List()
{
	// Empty
}

CITList::~CITList()
{
	ConnectionInfoTuple *tmp = getFirst();
	while(tmp != NIL) {
		delete tmp;
		tmp = getNext();
	}
}

void CITList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void CITList::insert(ConnectionInfoTuple* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

void CITList::append(ConnectionInfoTuple* ptr)
{
	List::append((CObject*)ptr);
}

BOOL CITList::inList(ConnectionInfoTuple* ptr)
{
	return List::inList((CObject*)ptr);
}

void CITList::remove(ConnectionInfoTuple* ptr)
{
	List::remove((CObject*)ptr);
}

ConnectionInfoTuple* CITList::getLast()
{
	return (ConnectionInfoTuple *)List::getLast();
}

ConnectionInfoTuple* CITList::getFirst()
{
	return (ConnectionInfoTuple *)List::getFirst();
}

ConnectionInfoTuple* CITList::getNext()
{
	return (ConnectionInfoTuple *)List::getNext();
}

ConnectionInfoTuple* CITList::findTupleFor(int x,int y)
{
	ConnectionInfoTuple *tmp = getFirst();
    while (tmp != NIL) {
		if (tmp->getX() == x && tmp->getY() == y) {
			return tmp;
		}
		tmp = getNext();
	}
	return NIL;
}

ConnectionInfoTuple* CITList::findTupleFor(NodeFigure *node)
{
	ConnectionInfoTuple *tmp = getFirst();
    while (tmp != NIL) {
		if (tmp->nodeFigurePtr() == node) {
			return tmp;
		}
		tmp = getNext();
	}
	return NIL;
}

ConnectionInfoTuple* CITList::findTupleFor(NodeFigure *node,int x,int y)
{
	ConnectionInfoTuple *tmp = getFirst();
    while (tmp != NIL) {
		if (tmp->getX() == x && 
			tmp->getY() == y &&
			tmp->nodeFigurePtr() == node) {
			return tmp;
		}
		tmp = getNext();
	}
	return NIL;
}

ConnectionInfoTuple* CITList::getTupleForLine(Line* aline)
{
	ConnectionInfoTuple *tmp = getFirst();
	while (tmp != NIL) {
		if (tmp->meet(aline)) {
			return tmp;
		}
		tmp = getNext();
	}
	return NIL;
}

void CITList::replaceNodeFigurePtr(NodeFigure* from,NodeFigure* to)
{
	ConnectionInfoTuple *tmp = getFirst();
	while (tmp != NIL) {
		if (tmp->nodeFigurePtr() == from) {
			tmp->nodeFigurePtr() = to;
		}
		tmp = getNext();
	}
}
