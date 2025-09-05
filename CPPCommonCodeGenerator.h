// CPPCommonCodeGenerator.h: interface for the CPPCommonCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPPCOMMONCODEGENERATOR_H__1CEAA4CD_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CPPCOMMONCODEGENERATOR_H__1CEAA4CD_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CodeGenerator.h"

class CPPCommonCodeGenerator : public CodeGenerator  
{
private:
	CString _macroString;
	CString _templateTagAll;
	CString _templateTagArg;

	BOOL generateSourceFile();
	BOOL generateHeaderFile();
	void makeHFMacroString();
	void printSlashDelemeter();
	void printFrontDocumentOfSourceFile();
	void printEndDocumentOfClass();
	void printfTemplateClassBody();
	void printSuperClassList();
	void printDataMembers();
	void printMemberFunctionSpecs(BOOL withBody);
	void printConstructorsAndDestructors();
	void printMemberFunctions();
	void printMethodBody(ClassTextLine *memberLine);
	void printInlineFunctions();
	void outputHFIdentificationMacro();
protected:
	void printComment(ClassTextLine *memberLine,const char* blanks);
	void printConstructorSpec(ClassTextLine *memberLine,BOOL withBody);
	void printDestructorSpec(ClassTextLine *memberLine,BOOL withBody);
public:
	CPPCommonCodeGenerator();
	CPPCommonCodeGenerator(CPPCommonCodeGenerator *from);
	virtual ~CPPCommonCodeGenerator();
	virtual BOOL generateCodeFor(ClassContent *pContent,BOOL calledFromView);
	virtual void outputSFSpecialMacro() {}
	virtual void outputSFSpecialConstruct() {}
	virtual void printClassHeading();
	virtual void printClassMemberSpecs();
};

#endif // !defined(AFX_CPPCOMMONCODEGENERATOR_H__1CEAA4CD_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
