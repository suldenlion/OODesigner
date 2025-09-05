/* ListNode.h */

#ifndef _LISTNODE_H
#define _LISTNODE_H

#include "Classes.h"

class ListNode : public CObject {
	DECLARE_SERIAL(ListNode)
	friend class List;
private : // data members
	CObject* _pointer;
	ListNode* _prev;
	ListNode* _succ;
public : // member functions
	ListNode();
	virtual ~ListNode();
	ListNode(CObject* ptr);
	virtual void Serialize(CArchive& ar);
	ListNode* succ();
	ListNode* prev();
	void insert(ListNode* node);
	void append(ListNode* node);
	CObject* &pointer();
};

#endif
