// PackageLibrary.cpp: implementation of the PackageLibrary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "PackageLibrary.h"
#include "ClassLibrary.h"
#include "KtgMacro.h"
#include "ClassContent.h"
#include "CMainFrame.h"
#include "CResizableTreeBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(PackageLibrary,List,1)

PackageLibrary::PackageLibrary()
: List()
{
	// Empty
}

PackageLibrary::~PackageLibrary()
{
	ClassLibrary *aLibrary = getFirst();
	while (aLibrary != NIL) {
		delete aLibrary;
		aLibrary = getNext();
	}
}

void PackageLibrary::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

void PackageLibrary::deletePackage(CString &packageName)
{
	ClassLibrary *aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			remove(aLibrary);
			delete aLibrary;
			return;
		}
		aLibrary = getNext();
	}
}

void PackageLibrary::registerPackage(CString &packageName)
{
	ClassLibrary *aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			return;
		}
		aLibrary = getNext();
	}
	aLibrary = new ClassLibrary();
	aLibrary->setName(packageName);
	if (nOfList() <= 0) {
		insert(aLibrary);
	} else {
		int posToInsert = 0;
		ClassLibrary *pLibrary = getFirst();
		while (pLibrary != NIL) {
			if (packageName.CompareNoCase(pLibrary->packageName()) < 0)
				break;
			posToInsert++;
			pLibrary = getNext();
		}
		insertAt(aLibrary,posToInsert);
	}
	mainFramePtr->m_wndTreeBar.insertPackage(packageName);
}

void PackageLibrary::deleteClassContent(CString &packageName,CString &className)
{
	ClassLibrary *aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			ClassContent *aContent = aLibrary->getClassContentFor(className);
			if (aContent == NIL) return;
			aLibrary->remove(aContent);
			delete aContent;
		}
		aLibrary = getNext();
	}
}

ClassContent *PackageLibrary::registerClassContent(CString &packageName,CString &className,ClassTemplate *aClass)
{
	ClassContent *aContent = getClassContentFor(className);
	if (aContent != NIL) {
		aContent->setClassContentFrom(aClass);
		return aContent;
	}
	ClassLibrary *aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			aContent = aLibrary->registerClassContent(className,aClass);
			return aContent;
		}
		aLibrary = getNext();
	}
	aLibrary = new ClassLibrary();
	aLibrary->setName(packageName);
	aContent = aLibrary->registerClassContent(className,aClass);
	if (nOfList() <= 0) {
		insert(aLibrary);
	} else {
		int posToInsert = 0;
		ClassLibrary *pLibrary = getFirst();
		while (pLibrary != NIL) {
			if (packageName.CompareNoCase(pLibrary->packageName()) < 0)
				break;
			posToInsert++;
			pLibrary = getNext();
		}
		insertAt(aLibrary,posToInsert);
	}
	return aContent;
}

ClassLibrary* PackageLibrary::getPackage(CString &packageName)
{
	ClassLibrary *aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			return aLibrary;
		}
		aLibrary = getNext();
	}
	return NIL;
}

void PackageLibrary::getPackageNameFor(CString &className,CString &packageName)
{
	ClassLibrary *aLibrary = getFirst();
	while (aLibrary != NIL) {
		
		if (aLibrary->hasClassName(className) == TRUE) {
			packageName = aLibrary->packageName();
			return;
		}
		aLibrary = getNext();
	}
	packageName = "Unknown";
	return;
}

ClassContent *PackageLibrary::getClassContentFor(CString &className)
{
	ClassLibrary *aLibrary = getFirst();
	while (aLibrary != NIL) {
		ClassContent *aContent = aLibrary->getClassContentFor(className);
		if (aContent != NIL) return aContent;
		aLibrary = getNext();
	}
	return NIL;
}

void PackageLibrary::insert(ClassLibrary* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

BOOL PackageLibrary::inList(ClassLibrary* ptr)
{
	return List::inList((CObject*)ptr);
}

void PackageLibrary::remove(ClassLibrary* ptr,int tag)
{
	List::remove((CObject*)ptr,tag);
}

ClassLibrary* PackageLibrary::getFirst()
{
	return (ClassLibrary *)List::getFirst();
}

ClassLibrary* PackageLibrary::getNext()
{
	return (ClassLibrary *)List::getNext();
}

