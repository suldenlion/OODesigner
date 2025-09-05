/* LineList.h */

#ifndef _LINELIST_H
#define _LINELIST_H

#include "Classes.h"
#include "List.h" // Generalization

class LineList : public List {
	DECLARE_SERIAL(LineList)
public : // member functions
	LineList();
	virtual ~LineList();
	virtual void Serialize(CArchive& ar);
	void push(Line* ptr);
	Line* pop();
	Line* top();
	void insert(Line* ptr,int tag = 0);
	void append(Line* ptr);
	BOOL inList(Line* ptr);
	BOOL replacePointer(Line* from,Line* to);
	void remove(Line* ptr);
	Line* getFirst();
	Line* getNext();
	Line* getLast();
	Line* getBack();
};

#endif
