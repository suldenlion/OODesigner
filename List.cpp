#include "stdafx.h"
/* List.C */

#include "List.h"
// Super Class : None

#include "KtgMacro.h"
#include "common.h"
#include "ListNode.h" // Aggregation

IMPLEMENT_SERIAL(List,CObject,1)

List::List()
: CObject()
{
	_header = new ListNode(NIL);
	_current = _header;
	_nOfList = 0;
}

List::~List()
{
	clear();
	delete _header; _header = NIL;
}

void List::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _header << (LONG)_nOfList;
	} else {
		clear(); delete _header; _header = NIL;
		ar >> _header >> (LONG &)_nOfList;
	}
}

void List::push(CObject* ptr)
{
	append(ptr);
}

CObject* List::pop()
{
	if (isEmpty()) {
		return NIL;
	}
	ListNode *tmp = _header->_succ;
	CObject* value = tmp->_pointer;
	delete tmp;
	_nOfList--;
	return(value);
}

CObject* List::top()
{
 	if (!isEmpty()) return(_header->_succ->_pointer); 
	else return(NIL);
}

void List::enter(CObject* ptr)
{
	insert(ptr); 
}

CObject* List::leave()
{
	return pop(); 
}

CObject* List::front()
{
	return top(); 
}

CObject* List::rear()
{
	if (!isEmpty()) return(_header->_prev->_pointer);
	else return(NIL);
}

void List::insertAt(CObject* ptr,int pos)
{
	_nOfList++;
	if (pos >= _nOfList) {
		ListNode *node = new ListNode(ptr);
		node->insert(_header);
		return;
	}
	ListNode *node = new ListNode(ptr);
	ListNode *tmp = _header->_succ;
	for (int i = 0; i < pos; i++) {
		tmp = tmp->_succ;
	}
	node->insert(tmp);
}

void List::insert(CObject* ptr,int tag)
{
	if (tag != ABSOLUTELY && inList(ptr)) return;
	ListNode *node = new ListNode(ptr);
	node->insert(_header);
	_nOfList++;
}

void List::append(CObject* ptr)
{
	if (inList(ptr)) return;
	ListNode *node = new ListNode(ptr);
	node->append(_header);
	_nOfList++;
}

BOOL List::inList(CObject* ptr)
{
	BOOL found = FALSE;
	ListNode *tmp = _header->_succ;
	while (tmp != _header) {
		if (tmp->_pointer == ptr) {
			found = TRUE;
			break;
		}
		tmp = tmp->_succ;
	}
	return(found);
}

CObject *List::at(int pos)
{
	if (pos < 0) return _header->_succ; // something wrong
	if (pos >= _nOfList) return _header->_succ; // something wrong
	ListNode *tmp = _header->_succ;
	for (int i = 0; i < pos; i++) {
		tmp = tmp->_succ;
	}
	if (tmp == _header) return _header->_succ; // something wrong
	CObject *ptr = tmp->_pointer;
	return ptr;
}

CObject *List::removeAt(int pos)
{
	if (pos < 0) return NIL;
	if (pos >= _nOfList) return NIL;
	ListNode *tmp = _header->_succ;
	for (int i = 0; i < pos; i++) {
		tmp = tmp->_succ;
	}
	if (tmp == _header) return NIL; // something wrong
	CObject *ptr = tmp->_pointer;
	delete tmp;
	_nOfList--;
	return ptr;
}

void List::remove(CObject* ptr,int tag)
{
	ListNode *tmp = _header->_succ;
	while (tmp != _header) {
		if (tmp->_pointer == ptr) {
			delete tmp;
			_nOfList--;
			if (tag == 0) {
				return;
			}
			tmp = _header->_succ;
			continue;
		}
		tmp = tmp->_succ;
	}
}

BOOL List::isEmpty()
{
	if (_header->_succ == _header) return TRUE;
	else return FALSE;
}

void List::clear()
{
	ListNode *tmp = _header;
	while (tmp->_succ != _header) {
		ListNode *ptr = tmp->_succ;
		delete ptr;
	}
	_nOfList = 0;
}

int List::nOfList()
{
	return _nOfList; 
}

CObject* List::getFirst()
{
	_current = _header->_succ;
	if (_current == _header) return NIL;
	return(_current->_pointer);
}

CObject* List::getLast()
{
	_current = _header->_prev;
	if (_current == _header) return NIL;
	return(_current->_pointer);
}

CObject* List::getNext()
{
	_current = _current->_succ;
	if (_current == _header) return NIL;
	return(_current->_pointer);
}

CObject* List::getBack()
{
	_current = _current->_prev;
	if (_current == _header) return NIL;
	return(_current->_pointer);
}

void List::setCurrentPointer(CObject* ptr)
{
	_current->_pointer = ptr;
}

ListNode *List::header()
{
	return _header;
}

BOOL List::replacePointer(CObject* from,CObject* to)
{
	BOOL replaced = FALSE;
	ListNode *tmp = _header->_succ;
	while (tmp != _header) {
		if (tmp->_pointer == from) {
			tmp->_pointer = to;
			replaced = TRUE;
		}
		tmp = tmp->_succ;
	}
	return replaced;
}

void List::copy(List* from)
{
	clear();
	ListNode *tmp = from->_header->_succ;
	while(tmp != from->_header) {
		List::insert(tmp->_pointer,ABSOLUTELY);
		tmp = tmp->_succ;
	}
}
