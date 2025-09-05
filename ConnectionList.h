/* ConnectionList.h */

#ifndef _CONNECTIONLIST_H
#define _CONNECTIONLIST_H

#include "Classes.h"
#include "List.h" // Generalization

class ConnectionList : public List {
	DECLARE_SERIAL(ConnectionList)
public : // member functions
	ConnectionList();
	virtual ~ConnectionList();
	virtual void Serialize(CArchive& ar);
	void push(Connection* ptr);
	Connection* pop();
	Connection* top();
	void insert(Connection* ptr,int tag = 0);
	void append(Connection* ptr);
	BOOL inList(Connection* ptr);
	BOOL replacePointer(Connection* from,Connection* to);
	void remove(Connection* ptr);
	Connection* getFirst();
	Connection* getNext();
	Connection* getLast();
	Connection* getBack();
};

#endif
