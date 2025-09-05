// FixedNamesTable.cpp: implementation of the FixedNamesTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "FixedNamesTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FixedNamesTable::FixedNamesTable(int nTable,Names names[])
: CStringList()
{
	for (int i = 0; i < nTable; i++) {
		AddTail(names[i].name);
	}
}

FixedNamesTable::~FixedNamesTable()
{
	RemoveAll();
}

BOOL FixedNamesTable::haveName(const char *aName)
{
	if (Find(aName) == NULL) return FALSE;
	else return TRUE;
}