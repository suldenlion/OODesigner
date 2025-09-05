// ArgumentList.cpp: implementation of the ArgumentList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ArgumentList.h"
#include "KtgMacro.h"
#include "ArgumentInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArgumentList::ArgumentList()
:List ()
{

}

ArgumentList::~ArgumentList()
{
	ArgumentInfo *anArg = getFirst();
	while (anArg != NIL) {
		delete anArg;
		anArg = getNext();
	}
	clear();
}

void ArgumentList::getArgumentString(CString &arg)
{
	arg = _T("");
	ArgumentInfo *anArg = getFirst();
	while (anArg != NIL) {
		if (anArg->argName.GetLength() == 0 &&
			anArg->argType.GetLength() == 0) {
			anArg = getNext();
			continue;
		} else if (anArg->argName.GetLength() == 0 &&
			anArg->argType.GetLength() > 0) {
			arg = arg + anArg->argType;
		} else if (anArg->argName.GetLength() > 0 &&
			anArg->argType.GetLength() == 0) {
			anArg->argType = anArg->argName;
			anArg->argName = _T("");
			arg = arg + anArg->argType;
		} else if (anArg->argName.GetLength() > 0 &&
			anArg->argType.GetLength() > 0) {
			arg = arg + anArg->argName + ":" + anArg->argType;
		}
		if (anArg->defaultValue.GetLength() > 0) {
			arg = arg + "=" + anArg->defaultValue;
		}
		anArg = getNext();
		if (anArg != NIL) {
			arg = arg + ",";
		}
	}
}

void ArgumentList::getAsCArgument(CString &arg,BOOL withDefaultArgFlag)
{
	arg = _T("");
	ArgumentInfo *anArg = getFirst();
	while (anArg != NIL) {
		if (anArg->argName.GetLength() == 0 &&
			anArg->argType.GetLength() == 0) {
			anArg = getNext();
			continue;
		} else if (anArg->argName.GetLength() == 0 &&
			anArg->argType.GetLength() > 0) {
			arg = arg + anArg->argType;
		} else if (anArg->argName.GetLength() > 0 &&
			anArg->argType.GetLength() == 0) {
			anArg->argType = anArg->argName;
			anArg->argName = _T("");
			arg = arg + anArg->argType;
		} else if (anArg->argName.GetLength() > 0 &&
			anArg->argType.GetLength() > 0) {
			arg = arg + anArg->argType + " " + anArg->argName;
		}
		if (withDefaultArgFlag == TRUE &&
			anArg->defaultValue.GetLength() > 0) {
			arg = arg + "=" + anArg->defaultValue;
		}
		anArg = getNext();
		if (anArg != NIL) {
			arg = arg + ",";
		}
	}
}

void ArgumentList::insert(ArgumentInfo* ptr,int tag)
{
	List::insert((CObject*)ptr,tag);
}

BOOL ArgumentList::inList(ArgumentInfo* ptr)
{
	return List::inList((CObject*)ptr);
}

void ArgumentList::remove(ArgumentInfo* ptr,int tag)
{
	List::remove((CObject*)ptr,tag);
}

ArgumentInfo* ArgumentList::getFirst()
{
	return (ArgumentInfo *)List::getFirst();
}

ArgumentInfo* ArgumentList::getNext()
{
	return (ArgumentInfo *)List::getNext();
}
