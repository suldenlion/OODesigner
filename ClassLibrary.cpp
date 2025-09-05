// ClassLibrary.cpp: implementation of the ClassLibrary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ClassLibrary.h"
#include "KtgMacro.h"
#include "ClassContent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(ClassLibrary,List,1)

ClassLibrary::ClassLibrary()
: List()
{
	_packageName = "";
}

ClassLibrary::~ClassLibrary()
{
	ClassContent *aContent = getFirst();
	while (aContent != NIL) {
		delete aContent;
		aContent = getNext();
	}
}

void ClassLibrary::Serialize(CArchive& ar)
{
	List::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _packageName;
	} else {
		ar >> _packageName;
	}
}

ClassContent *ClassLibrary::registerClassContent(CString &className,ClassTemplate *aClass)
{
	ClassContent *aContent = new ClassContent();
	aContent->setName(className);
	aContent->setClassContentFrom(aClass);
	if (nOfList() <= 0) {
		insert(aContent);
	} else {
		int posToInsert = 0;
		ClassContent *pContent = getFirst();
		while (pContent != NIL) {
			if (className.CompareNoCase(pContent->className()) < 0)
				break;
			posToInsert++;
			pContent = getNext();
		}
		insertAt(aContent,posToInsert);
	}
	return aContent;
}

void ClassLibrary::registerClassContent(CString &className,ClassContent *aContent)
{
	if (nOfList() <= 0) {
		insert(aContent);
	} else {
		int posToInsert = 0;
		ClassContent *pContent = getFirst();
		while (pContent != NIL) {
			if (className.CompareNoCase(pContent->className()) < 0)
				break;
			posToInsert++;
			pContent = getNext();
		}
		insertAt(aContent,posToInsert);
	}
}

BOOL ClassLibrary::hasClassName(CString &className)
{
	ClassContent *aContent = getFirst();
	while (aContent != NIL) {
		if (aContent->hasEqualName(className)) return TRUE;
		aContent = getNext();
	}
	return FALSE;
}

ClassContent *ClassLibrary::getClassContentFor(CString &className)
{
	ClassContent *aContent = getFirst();
	while (aContent != NIL) {
		if (aContent->hasEqualName(className)) return aContent;
		aContent = getNext();
	}
	return NIL;
}

void ClassLibrary::insert(ClassContent* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

BOOL ClassLibrary::inList(ClassContent* ptr)
{
	return List::inList((CObject*)ptr);
}

void ClassLibrary::remove(ClassContent* ptr,int tag)
{
	List::remove((CObject*)ptr,tag);
}

ClassContent* ClassLibrary::getFirst()
{
	return (ClassContent *)List::getFirst();
}

ClassContent* ClassLibrary::getNext()
{
	return (ClassContent *)List::getNext();
}


