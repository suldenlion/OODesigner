// InterfacePortList.h: interface for the InterfacePortList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERFACEPORTLIST_H__3C2BBC20_FFE1_11D3_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_INTERFACEPORTLIST_H__3C2BBC20_FFE1_11D3_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "List.h"

class InterfacePortList : public List  
{
	DECLARE_SERIAL(InterfacePortList)
public:
	InterfacePortList();
	virtual ~InterfacePortList();
	virtual void Serialize(CArchive& ar);
	void insert(InterfacePort* ptr,int tag = 0);
	void append(InterfacePort* ptr);
	BOOL inList(InterfacePort* ptr);
	void remove(InterfacePort* ptr);
	InterfacePort* getFirst();
	InterfacePort* getNext();
	InterfacePort* getLast();
	InterfacePort* findTupleFor(int x,int y);
	InterfacePort* findTupleFor(NodeFigure *node);
	InterfacePort* findTupleFor(NodeFigure *node,int x,int y);
	InterfacePort* getTupleForLine(Line* aline);
	void replaceNodeFigurePtr(NodeFigure* from,NodeFigure* to);
	int getNextYPosition(int startY,int deltaY);
	int getMaxY();
};

#endif // !defined(AFX_INTERFACEPORTLIST_H__3C2BBC20_FFE1_11D3_AED4_00A0C9BA6734__INCLUDED_)
