/* LineNodeList.h */

#ifndef _LINENODELIST_H
#define _LINENODELIST_H

#include "Classes.h"
#include "List.h" // Generalization

class LineNodeList : public List {
	DECLARE_SERIAL(LineNodeList)
public : // member functions
	LineNodeList();
	virtual ~LineNodeList();
	virtual void Serialize(CArchive& ar);
	LineNode* top();
	LineNode* rear();
	void insert(LineNode* ptr,int tag = 0);
	void append(LineNode* ptr);
	BOOL inList(LineNode* ptr);
	BOOL replacePointer(LineNode* from,LineNode* to);
	void remove(LineNode* ptr,BOOL vanish = FALSE);
	LineNode* getFirst();
	LineNode* getNext();
	LineNode* getLast();
	LineNode* getBack();
};

#endif
