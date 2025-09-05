// PackageLibrary.h: interface for the PackageLibrary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKAGELIBRARY_H__99727923_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_PACKAGELIBRARY_H__99727923_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "List.h"

class PackageLibrary : public List  
{
public:
	DECLARE_SERIAL(PackageLibrary)
public : // member functions
	PackageLibrary();
	virtual ~PackageLibrary();
	virtual void Serialize(CArchive& ar);
	ClassContent *getClassContentFor(CString &className);
	void getPackageNameFor(CString &className,CString &packageName);
	ClassLibrary* getPackage(CString &packageName);
	void registerPackage(CString &packageName);
	void deletePackage(CString &packageName);
	void deleteClassContent(CString &packageName,CString &className);
	ClassContent *registerClassContent(CString &packageName,CString &className,ClassTemplate *aClass);
	void insert(ClassLibrary* ptr,int tag = 0);
	BOOL inList(ClassLibrary* ptr);
	void remove(ClassLibrary* ptr,int tag = 0);
	ClassLibrary* getFirst();
	ClassLibrary* getNext();
};

#endif // !defined(AFX_PACKAGELIBRARY_H__99727923_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_)
