#include "stdafx.h"
/* ListNode.C */

#include "KtgMacro.h"
#include "common.h"
#include "ListNode.h"
#include "Figure.h"
// Super Class : CObject

IMPLEMENT_SERIAL(ListNode,CObject,1)

ListNode::ListNode()
: CObject()
{
	_pointer = NIL;
	_prev = this;
	_succ = this;
}

ListNode::~ListNode()
{
	_succ->_prev = _prev;
	_prev->_succ = _succ;
	_pointer = NIL;
	_prev = NIL;
	_succ = NIL;
}

ListNode::ListNode(CObject* ptr)
: CObject()
{
	_pointer = ptr;
	_prev = this;
	_succ = this;
}

void ListNode::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _pointer << _prev << _succ;
	} else {
		ar >> _pointer >> _prev >> _succ;
	}
}

ListNode* ListNode::succ()
{
	return _succ; 
}

ListNode* ListNode::prev()
{
	return _prev; 
}

void ListNode::insert(ListNode* node)
// order : --> this(inserted) --> node -->
{
	if (node == NIL) {
		return;
	}
	_prev = node->_prev;
	_succ = node;
	node->_prev->_succ = this;
	node->_prev = this;
}

void ListNode::append(ListNode* node)
// order : --> node --> this(appended) -->
{
	if (node == NIL) {
		return;
	}
	_prev = node;
	_succ = node->_succ;
	node->_succ->_prev = this;
	node->_succ = this;
}

CObject*& ListNode::pointer()
{
	return _pointer; 
}
