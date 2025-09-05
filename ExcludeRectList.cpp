// ExcludeRectList.cpp: implementation of the ExcludeRectList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ExcludeRectList.h"
#include "ExcludeRect.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcludeRectList::ExcludeRectList()
{

}

ExcludeRectList::~ExcludeRectList()
{
	ExcludeRect *pRect = getFirst();
	while (pRect != NIL) {
		delete pRect;
		pRect = getNext();
	}
}

void ExcludeRectList::addTail(ExcludeRect* ptr)
{
	List::insert((CObject*)ptr,0);
}

void ExcludeRectList::remove(Figure* ptr)
{
	ExcludeRect *pRect = getFirst();
	while (pRect != NIL) {
		if (ptr == pRect->figurePtr()) {
			List::remove((CObject*)pRect);
			delete pRect;
			pRect = getFirst();
		} else {
			pRect = getNext();
		}
	}
}

ExcludeRect* ExcludeRectList::getFirst()
{
	return (ExcludeRect *)List::getFirst();
}

ExcludeRect* ExcludeRectList::getNext()
{
	return (ExcludeRect *)List::getNext();
}

