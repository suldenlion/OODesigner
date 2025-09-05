/* List.h */

#ifndef _LIST_H
#define _LIST_H

#include "Classes.h"

class List : public CObject {
	DECLARE_SERIAL(List)
protected : // data members
	ListNode* _header;
	ListNode* _current;
	int _nOfList;
	List();
	virtual void Serialize(CArchive& ar);
	void push(CObject* ptr);
	CObject* pop();
	CObject* top();
	void enter(CObject* ptr);
	CObject* leave();
	CObject* front();
	CObject* rear();
	CObject* at(int pos);
	void insert(CObject* ptr,int tag = 0);
	void insertAt(CObject* ptr,int pos);
	void append(CObject* ptr);
	BOOL inList(CObject* ptr);
	BOOL replacePointer(CObject* from,CObject* to);
	void remove(CObject* ptr,int tag = 0);
	CObject *removeAt(int pos);
	CObject* getFirst();
	CObject* getLast();
	CObject* getNext();
	CObject* getBack();
	void setCurrentPointer(CObject* ptr);
public:
	virtual ~List();
	void clear();
	int nOfList();
	BOOL isEmpty();
	ListNode *header();
	void copy(List* from);
};

#endif
