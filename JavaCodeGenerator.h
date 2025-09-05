// JavaCodeGenerator.h: interface for the JavaCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JAVACODEGENERATOR_H__1CEAA4CA_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_JAVACODEGENERATOR_H__1CEAA4CA_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CodeGenerator.h"

class JavaCodeGenerator : public CodeGenerator  
{
private:
	void printComment(ClassTextLine *memberLine);
	void printMemberFunctionModifiers(ClassTextLine *memberLine);
	void printDefaultValue(ClassTextLine *memberLine);
	void printDataMemberModifiers(ClassTextLine *memberLine);
	void printClassProperties();
	BOOL generateSourceFile();
	void printSuperClassList();
	void printDataMembers();
	void printMemberFunctions();
	void printConstructor(char *vis,ClassTextLine *memberLine);
	void printMethodBody(ClassTextLine *memberLine);
	void checkTypeForAsterisk(CString &type,ClassTextLine *memberLine);
public:
	JavaCodeGenerator();
	JavaCodeGenerator(JavaCodeGenerator *from);
	virtual ~JavaCodeGenerator();
	virtual BOOL generateCodeFor(ClassContent *pContent,BOOL calledFromView);
	virtual void printClassHeading();
};

#endif // !defined(AFX_JAVACODEGENERATOR_H__1CEAA4CA_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
