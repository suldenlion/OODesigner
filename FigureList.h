/* FigureList.h */

#ifndef _FIGURELIST_H
#define _FIGURELIST_H

#include "Classes.h"
#include "List.h" // Generalization

class FigureList : public List {
	DECLARE_SERIAL(FigureList)
public : // member functions
	FigureList();
	virtual ~FigureList();
	virtual void Serialize(CArchive& ar);
	void push(Figure* ptr);
	Figure* pop();
	Figure* top();
	void enter(Figure* ptr);
	Figure* leave();
	Figure* front();
	Figure* rear();
	void insert(Figure* ptr,int tag = 0);
	void append(Figure* ptr);
	void addTail(Figure* ptr);
	void addFront(Figure* ptr);
	BOOL replacePointer(Figure* from,Figure* to);
	BOOL inList(Figure* ptr);
	void remove(Figure* ptr);
	Figure* getFirst();
	Figure* getNext();
	Figure* getLast();
	Figure* getBack();
};

#endif
