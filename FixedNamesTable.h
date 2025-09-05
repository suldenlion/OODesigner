// FixedNamesTable.h: interface for the FixedNamesTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXEDNAMESTABLE_H__4516F4E2_A5D0_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_FIXEDNAMESTABLE_H__4516F4E2_A5D0_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "KtgMacro.h"

class FixedNamesTable : public CStringList  
{
public:
	FixedNamesTable(int nTable,Names names[]);
	virtual ~FixedNamesTable();
	BOOL haveName(const char *aName);
	BOOL haveName(CString &aName) {
		return haveName((LPCTSTR)aName);
	}
};

#endif // !defined(AFX_FIXEDNAMESTABLE_H__4516F4E2_A5D0_11D4_AED4_00A0C9BA6734__INCLUDED_)
