// ArgumentInfo.h: interface for the ArgumentInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARGUMENTINFO_H__66BEBAC2_144D_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_ARGUMENTINFO_H__66BEBAC2_144D_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"

class ArgumentInfo : public CObject  
{
public:
	CString argName;
	CString argType;
	CString defaultValue;
public:
	ArgumentInfo();
	virtual ~ArgumentInfo();
	void initialize();
};

#endif // !defined(AFX_ARGUMENTINFO_H__66BEBAC2_144D_11D4_AED4_00A0C9BA6734__INCLUDED_)
