/* SlaveryTextList.h */

#ifndef _SLAVERYTEXTLIST_H
#define _SLAVERYTEXTLIST_H

#include "Classes.h"
#include "List.h" // Generalization

class SlaveryTextList : public List {
	DECLARE_SERIAL(SlaveryTextList)
public : // member functions
	SlaveryTextList();
	virtual ~SlaveryTextList();
	virtual void Serialize(CArchive& ar);
	void push(SlaveryText* ptr);
	SlaveryText* pop();
	SlaveryText* top();
	void insert(SlaveryText* ptr,int tag = 0);
	void append(SlaveryText* ptr);
	BOOL inList(SlaveryText* ptr);
	BOOL replacePointer(SlaveryText* from,SlaveryText* to);
	void remove(SlaveryText* ptr);
	SlaveryText* at(int pos);
	SlaveryText* getFirst();
	SlaveryText* getNext();
	SlaveryText* getLast();
	SlaveryText* getBack();
};

#endif
