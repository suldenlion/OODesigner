// RelationshipInfoTupleList.cpp: implementation of the RelationshipInfoTupleList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "RelationshipInfoTupleList.h"
#include "RelationshipInfoTuple.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(RelationshipInfoTupleList,List,1)

RelationshipInfoTupleList::RelationshipInfoTupleList()
: List()
{
}

RelationshipInfoTupleList::~RelationshipInfoTupleList()
{
	RelationshipInfoTuple *aTuple = getFirst();
	while (aTuple != NIL) {
		delete aTuple;
		aTuple = getNext();
	}
}

void RelationshipInfoTupleList::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void RelationshipInfoTupleList::removeRelationshipInfo(CString className)
{
	RelationshipInfoTuple *aTuple = getFirst();
	while (aTuple != NIL) {
		CString superName = aTuple->majorClassName();
		CString subName = aTuple->minorClassName();
		if (superName.CompareNoCase(className) == 0 ||
			subName.CompareNoCase(className) == 0) {
			remove(aTuple);
			delete aTuple;
			aTuple = getFirst();
		} else {
			aTuple = getNext();
		}
	}
}

void RelationshipInfoTupleList::removeRelationshipInfo(char *superClassName,char *subClassName)
{
	RelationshipInfoTuple *aTuple = getFirst();
	while (aTuple != NIL) {
		CString superName = aTuple->majorClassName();
		CString subName = aTuple->minorClassName();
		if (superName.CompareNoCase(superClassName) == 0 &&
			subName.CompareNoCase(subClassName) == 0) {
			remove(aTuple);
			delete aTuple;
			return;
		}
		aTuple = getNext();
	}
}

BOOL RelationshipInfoTupleList::doesTupleExist(char *superClassName,char *subClassName,char *generalizationName)
{
	RelationshipInfoTuple *aTuple = getFirst();
	while (aTuple != NIL) {
		CString superName = aTuple->majorClassName();
		CString subName = aTuple->minorClassName();
		CString genString = aTuple->relationshipString();
		if (superName.CompareNoCase(superClassName) == 0 &&
			subName.CompareNoCase(subClassName) == 0 &&
			genString.CompareNoCase(generalizationName) == 0)
			return TRUE;
		aTuple = getNext();
	}
	return FALSE;
}

void RelationshipInfoTupleList::getVisibilityFor(CString &superClassName,CString &subClassName,CString &visibility)
{
	visibility = _T("");
	RelationshipInfoTuple *aTuple = getFirst();
	while (aTuple != NIL) {
		CString superName = aTuple->majorClassName();
		CString subName = aTuple->minorClassName();
		if (superName.CompareNoCase(superClassName) == 0 &&
			subName.CompareNoCase(subClassName) == 0) {
			visibility = aTuple->visibility();
			return;
		}
		aTuple = getNext();
	}
}

void RelationshipInfoTupleList::getMajorClassNames(CString &minorClassName,CStringList &majorClassNames)
{
	RelationshipInfoTuple *aTuple = getFirst();
	while (aTuple != NIL) {
		CString majorName = aTuple->majorClassName();
		CString minorName = aTuple->minorClassName();
		CString genString = aTuple->relationshipString();
		if (minorName.CompareNoCase(minorClassName) == 0) {
			if (genString.Compare("Generalization") == 0) {
				majorClassNames.AddHead(majorName);
			} else {
				// interfaces or other case
				majorClassNames.AddTail(majorName);
			}
		}
		aTuple = getNext();
	}
}

void RelationshipInfoTupleList::getMinorClassNames(CString &majorClassName,CStringList &minorClassNames)
{
	RelationshipInfoTuple *aTuple = getFirst();
	while (aTuple != NIL) {
		CString majorName = aTuple->majorClassName();
		CString minorName = aTuple->minorClassName();
		CString genString = aTuple->relationshipString();
		if (majorName.CompareNoCase(majorClassName) == 0) {
			minorClassNames.AddTail(minorName);
		}
		aTuple = getNext();
	}
}

void RelationshipInfoTupleList::registerRelationshipInfo(char *majorClassName,char *minorClassName,char *relationshipName)
{
	if (doesTupleExist(majorClassName,minorClassName,relationshipName) == TRUE) 
		return;
	RelationshipInfoTuple *newTuple = new RelationshipInfoTuple(majorClassName,minorClassName,relationshipName);
	insert(newTuple);
}

void RelationshipInfoTupleList::insert(RelationshipInfoTuple* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

BOOL RelationshipInfoTupleList::inList(RelationshipInfoTuple* ptr)
{
	return List::inList((CObject*)ptr);
}

void RelationshipInfoTupleList::remove(RelationshipInfoTuple* ptr,int tag)
{
	List::remove((CObject*)ptr,tag);
}

RelationshipInfoTuple* RelationshipInfoTupleList::getFirst()
{
	return (RelationshipInfoTuple *)List::getFirst();
}

RelationshipInfoTuple* RelationshipInfoTupleList::getNext()
{
	return (RelationshipInfoTuple *)List::getNext();
}