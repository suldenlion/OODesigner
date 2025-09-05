// CSharpCodeGenerator.h: interface for the CSharpCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSHARPCODEGENERATOR_H__70C77080_8697_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_CSHARPCODEGENERATOR_H__70C77080_8697_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CodeGenerator.h"

class CSharpCodeGenerator : public CodeGenerator  
{
public:
	CSharpCodeGenerator();
	CSharpCodeGenerator(CSharpCodeGenerator *from);
	virtual ~CSharpCodeGenerator();
	virtual BOOL generateCodeFor(ClassContent *pContent,BOOL calledFromView) { return TRUE; }
	virtual void printClassHeading() {}

};

#endif // !defined(AFX_CSHARPCODEGENERATOR_H__70C77080_8697_11D5_A72B_0050DA2D4248__INCLUDED_)
