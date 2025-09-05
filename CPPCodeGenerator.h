// CPPCodeGenerator.h: interface for the CPPCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPPCODEGENERATOR_H__1CEAA4C8_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPPCODEGENERATOR_H__1CEAA4C8_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CPPCommonCodeGenerator.h"

class CPPCodeGenerator : public CPPCommonCodeGenerator  
{
public:
	CPPCodeGenerator();
	CPPCodeGenerator(CPPCodeGenerator *from);
	virtual ~CPPCodeGenerator();
};

#endif // !defined(AFX_CPPCODEGENERATOR_H__1CEAA4C8_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
