// CITList.h: interface for the CITList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CITLIST_H__9FC36302_056E_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_CITLIST_H__9FC36302_056E_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "List.h" // Generalization

class CITList : public List {
	DECLARE_SERIAL(CITList)
public : // member functions
	CITList();
	virtual ~CITList();
	virtual void Serialize(CArchive& ar);
	void insert(ConnectionInfoTuple* ptr,int tag = 0);
	void append(ConnectionInfoTuple* ptr);
	BOOL inList(ConnectionInfoTuple* ptr);
	void remove(ConnectionInfoTuple* ptr);
	ConnectionInfoTuple* getFirst();
	ConnectionInfoTuple* getNext();
	ConnectionInfoTuple* getLast();
	ConnectionInfoTuple* findTupleFor(int x,int y);
	ConnectionInfoTuple* findTupleFor(NodeFigure *node);
	ConnectionInfoTuple* findTupleFor(NodeFigure *node,int x,int y);
	ConnectionInfoTuple* getTupleForLine(Line* aline);
	void replaceNodeFigurePtr(NodeFigure* from,NodeFigure* to);
};

#endif // !defined(AFX_CITLIST_H__9FC36302_056E_11D3_AC44_00008610434C__INCLUDED_)
