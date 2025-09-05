// RelationshipInfoTupleList.h: interface for the RelationshipInfoTupleList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELATIONSHIPINFOTUPLELIST_H__1EF0A104_20DB_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_RELATIONSHIPINFOTUPLELIST_H__1EF0A104_20DB_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "List.h"

class RelationshipInfoTupleList : public List  
{
	DECLARE_SERIAL(RelationshipInfoTupleList)
public : // member functions
	RelationshipInfoTupleList();
	virtual ~RelationshipInfoTupleList();
	virtual void Serialize(CArchive& ar);
	void getVisibilityFor(CString &superClassName,CString &subClassName,CString &visibility);
	void getMajorClassNames(CString &minorClassName,CStringList &majorClassNames);
	void getMinorClassNames(CString &majorClassName,CStringList &minorClassNames);
	BOOL doesTupleExist(char *superClassName,char *subClassName,char *generalizationName);
	void removeRelationshipInfo(char *superClassName,char *subClassName);
	void removeRelationshipInfo(CString className);
	void registerRelationshipInfo(char *majorClassName,char *minorClassName,char *relationshipName);
	void insert(RelationshipInfoTuple* ptr,int tag = 0);
	BOOL inList(RelationshipInfoTuple* ptr);
	void remove(RelationshipInfoTuple* ptr,int tag = 0);
	RelationshipInfoTuple* getFirst();
	RelationshipInfoTuple* getNext();
};

#endif // !defined(AFX_RELATIONSHIPINFOTUPLELIST_H__1EF0A104_20DB_11D4_AED4_00A0C9BA6734__INCLUDED_)
