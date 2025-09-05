// CPPCodeGenerator.cpp: implementation of the CPPCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "CPPCodeGenerator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPPCodeGenerator::CPPCodeGenerator()
: CPPCommonCodeGenerator()
{
	_languageName = "C++";
}

CPPCodeGenerator::CPPCodeGenerator(CPPCodeGenerator *from)
: CPPCommonCodeGenerator(from)
{
	_languageName = "C++";
}

CPPCodeGenerator::~CPPCodeGenerator()
{

}



