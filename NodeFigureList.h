/* NodeFigureList.h */

#ifndef _NODEFIGURELIST_H
#define _NODEFIGURELIST_H

#include "Classes.h"
#include "List.h" // Generalization

class NodeFigureList : public List {
	DECLARE_SERIAL(NodeFigureList)
public : // member functions
	NodeFigureList();
	virtual ~NodeFigureList();
	virtual void Serialize(CArchive& ar);
	void push(NodeFigure* ptr);
	NodeFigure* pop();
	NodeFigure* top();
	void insert(NodeFigure* ptr,int tag = 0);
	void append(NodeFigure* ptr);
	BOOL inList(NodeFigure* ptr);
	BOOL replacePointer(NodeFigure* from,NodeFigure* to);
	void remove(NodeFigure* ptr,int tag = 0);
	NodeFigure* getFirst();
	NodeFigure* getNext();
	NodeFigure* getLast();
	NodeFigure* getBack();
};

#endif
