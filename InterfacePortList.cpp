// InterfacePortList.cpp: implementation of the InterfacePortList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "InterfacePortList.h"
#include "KtgMacro.h"
#include "InterfacePort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(InterfacePortList,List,1)

InterfacePortList::InterfacePortList()
: List()
{
	// Empty
}

InterfacePortList::~InterfacePortList()
{
	InterfacePort *tmp = getFirst();
	while(tmp != NIL) {
		delete tmp;
		tmp = getNext();
	}
}

void InterfacePortList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void InterfacePortList::insert(InterfacePort* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

void InterfacePortList::append(InterfacePort* ptr)
{
	List::append((CObject*)ptr);
}

BOOL InterfacePortList::inList(InterfacePort* ptr)
{
	return List::inList((CObject*)ptr);
}

void InterfacePortList::remove(InterfacePort* ptr)
{
	List::remove((CObject*)ptr);
}

InterfacePort* InterfacePortList::getLast()
{
	return (InterfacePort *)List::getLast();
}

InterfacePort* InterfacePortList::getFirst()
{
	return (InterfacePort *)List::getFirst();
}

InterfacePort* InterfacePortList::getNext()
{
	return (InterfacePort *)List::getNext();
}

InterfacePort* InterfacePortList::findTupleFor(int x,int y)
{
	InterfacePort *tmp = getFirst();
    while (tmp != NIL) {
		if (tmp->getX() == x && tmp->getY() == y) {
			return tmp;
		}
		tmp = getNext();
	}
	return NIL;
}

InterfacePort* InterfacePortList::findTupleFor(NodeFigure *node)
{
	InterfacePort *tmp = getFirst();
    while (tmp != NIL) {
		if (tmp->nodeFigurePtr() == node) {
			return tmp;
		}
		tmp = getNext();
	}
	return NIL;
}

InterfacePort* InterfacePortList::findTupleFor(NodeFigure *node,int x,int y)
{
	InterfacePort *tmp = getFirst();
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

InterfacePort* InterfacePortList::getTupleForLine(Line* aline)
{
	InterfacePort *tmp = getFirst();
	while (tmp != NIL) {
		if (tmp->meet(aline)) {
			return tmp;
		}
		tmp = getNext();
	}
	return NIL;
}

void InterfacePortList::replaceNodeFigurePtr(NodeFigure* from,NodeFigure* to)
{
	InterfacePort *tmp = getFirst();
	while (tmp != NIL) {
		if (tmp->nodeFigurePtr() == from) {
			tmp->nodeFigurePtr() = to;
		}
		tmp = getNext();
	}
}

int InterfacePortList::getMaxY()
{
	int n = nOfList();
	if (n == 0) return 0;
	int max = 0;
	InterfacePort *tmp = getFirst();
	while (tmp != NIL) {
		int y = tmp->getY();
		if (y > max) max = y;
		tmp = getNext();
	}
	return max;
}

int InterfacePortList::getNextYPosition(int startY,int deltaY)
{
	int expectedY = startY+deltaY;
	int n = nOfList();
	if (n == 0) return expectedY;
	for (int i = 0; i < n; i++) {
		BOOL expectedFound;
		expectedFound = FALSE;
		InterfacePort *tmp = getFirst();
		while (tmp != NIL) {
			int y = tmp->getY();
			if (y == expectedY) {
				expectedFound = TRUE;
				break;
			}
			tmp = getNext();
		}
		if (expectedFound == FALSE) break;
		expectedY = expectedY + deltaY;
	}
	return expectedY;
}
