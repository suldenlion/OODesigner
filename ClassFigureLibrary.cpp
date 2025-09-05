// ClassFigureLibrary.cpp: implementation of the ClassFigureLibrary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "ClassFigureLibrary.h"
#include "FigureLibrary.h"
#include "FigureList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(ClassFigureLibrary,List,1)

ClassFigureLibrary::ClassFigureLibrary()
: List()
{
	// Empty
}

ClassFigureLibrary::~ClassFigureLibrary()
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		delete aLibrary;
		aLibrary = getNext();
	}
}

void ClassFigureLibrary::Serialize(CArchive& ar)
{
	List::Serialize(ar);
}

BOOL ClassFigureLibrary::hasRelationshipYet(UnsignedLong *identity,char *major,char *minor,CString &packName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (aLibrary->hasRelationshipYet(identity,major,minor,packName) == TRUE) {
			return TRUE;
		}
		aLibrary = getNext();
	}
	return FALSE;
}

BOOL ClassFigureLibrary::hasClassTemplate(CString &className,CString &packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		BOOL exists =
			aLibrary->hasClassTemplate(className,packageName);
		if (exists == TRUE) return TRUE;
		aLibrary = getNext();
	}
	return FALSE;
}

void ClassFigureLibrary::replaceFieldTextContent(CString &packageName,CString &className,ClassTemplate *aClass,COODView *aView)
{
	ClassFigureLibrary *copiedLibrary = new ClassFigureLibrary();
    copiedLibrary->copy(this);
	FigureLibrary* aLibrary = copiedLibrary->getFirst();
	while (aLibrary != NIL) {
		aLibrary->replaceFieldTextContent(packageName,className,aClass,aView);
		aLibrary = copiedLibrary->getNext();
	}
	copiedLibrary->clear();
	delete copiedLibrary;
}

void ClassFigureLibrary::deletePackage(CString &packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			remove(aLibrary);
			delete aLibrary;
			return;
		}
		aLibrary = getNext();
	}
}

FigureLibrary* ClassFigureLibrary::clearPackage(CString &packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {			
			return aLibrary->clearPackage();;
		}
		aLibrary = getNext();
	}
	return NIL;
}

FigureLibrary *ClassFigureLibrary::getPackage(CString &packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			return aLibrary;
		}
		aLibrary = getNext();
	}
	return NIL;
}

FigureList *ClassFigureLibrary::figures(CString &packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			return aLibrary->figures();
		}
		aLibrary = getNext();
	}
	FigureLibrary *newLibrary = addPackage(packageName);
	return newLibrary->figures();
}

FigureLibrary *ClassFigureLibrary::addPackage(CString &packageName)
{
	FigureLibrary *newLibrary = new FigureLibrary(packageName);
	insert(newLibrary);
	return newLibrary;
}

int ClassFigureLibrary::zoomRatioX(CString& packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			return aLibrary->zoomRatioX();
		}
		aLibrary = getNext();
	}
	return 100;
}

int ClassFigureLibrary::zoomRatioY(CString& packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			return aLibrary->zoomRatioY();
		}
		aLibrary = getNext();
	}
	return 100;
}

void ClassFigureLibrary::setZoomRatioX(CString& packageName,int zoomX)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			aLibrary->setZoomRatioX(zoomX);
			return;
		}
		aLibrary = getNext();
	}
	FigureLibrary *newLibrary = addPackage(packageName);
	newLibrary->setZoomRatioX(zoomX);
	return;
}

void ClassFigureLibrary::setZoomRatioY(CString& packageName,int zoomY)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			aLibrary->setZoomRatioY(zoomY);
			return;
		}
		aLibrary = getNext();
	}
	FigureLibrary *newLibrary = addPackage(packageName);
	newLibrary->setZoomRatioY(zoomY);
	return;
}

int ClassFigureLibrary::originX(CString& packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			return aLibrary->originX();
		}
		aLibrary = getNext();
	}
	return 0;
}

int ClassFigureLibrary::originY(CString& packageName)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			return aLibrary->originY();
		}
		aLibrary = getNext();
	}
	return 0;
}

void ClassFigureLibrary::setOriginX(CString& packageName,int x)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			aLibrary->setOriginX(x);
			return;
		}
		aLibrary = getNext();
	}
	FigureLibrary *newLibrary = addPackage(packageName);
	newLibrary->setOriginX(x);
	return;
}

void ClassFigureLibrary::setOriginY(CString& packageName,int y)
{
	FigureLibrary* aLibrary = getFirst();
	while (aLibrary != NIL) {
		if (packageName.CompareNoCase(aLibrary->packageName()) == 0) {
			aLibrary->setOriginY(y);
			return;
		}
		aLibrary = getNext();
	}
	FigureLibrary *newLibrary = addPackage(packageName);
	newLibrary->setOriginY(y);
	return;
}

void ClassFigureLibrary::insert(FigureLibrary* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

BOOL ClassFigureLibrary::inList(FigureLibrary* ptr)
{
	return List::inList((CObject*)ptr);
}

void ClassFigureLibrary::remove(FigureLibrary* ptr,int tag)
{
	List::remove((CObject*)ptr,tag);
}

FigureLibrary* ClassFigureLibrary::getFirst()
{
	return (FigureLibrary *)List::getFirst();
}

FigureLibrary* ClassFigureLibrary::getNext()
{
	return (FigureLibrary *)List::getNext();
}

