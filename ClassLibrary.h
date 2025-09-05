// ClassLibrary.h: interface for the ClassLibrary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSTEMPLATELIST_H__99727921_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CLASSTEMPLATELIST_H__99727921_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "List.h"

class ClassLibrary : public List  
{
private:
	CString _packageName;
public:
	DECLARE_SERIAL(ClassLibrary)
public : // member functions
	ClassLibrary();
	virtual ~ClassLibrary();
	virtual void Serialize(CArchive& ar);
	void setName(CString &s) { _packageName = s; }
	CString &packageName() { return _packageName; }
	BOOL hasClassName(CString &className);
	ClassContent *getClassContentFor(CString &className);
	ClassContent *registerClassContent(CString &className,ClassTemplate *aClass);
	void registerClassContent(CString &className,ClassContent *aContent);
	void insert(ClassContent* ptr,int tag = 0);
	BOOL inList(ClassContent* ptr);
	void remove(ClassContent* ptr,int tag = 0);
	ClassContent* getFirst();
	ClassContent* getNext();
};

#endif // !defined(AFX_CLASSTEMPLATELIST_H__99727921_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_)
