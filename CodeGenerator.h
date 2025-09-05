// CodeGenerator.h: interface for the CodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEGENERATOR_H__1CEAA4C7_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CODEGENERATOR_H__1CEAA4C7_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
class CResizableEditDoc;
class CResizableEditView;

class CodeGenerator : public CObject 
{
protected:
	FILE *_targetFile;
	ClassContent *_classContent;
	CString _className;
	CString _fileNameSpecified;
	CString _destructorName;
	CString _fileName;
	CString _languageName;
	CStringList _superClassNames;
	CResizableEditDoc *_outputDoc;
	CResizableEditView *_outputView;
	ClassLibrary *_innerClassContents;
	int _nConstructors;
	int _nDestructors;
	BOOL _innerClassFlag;
	int _nestLevel;

	void collectInnerClassContents();
	BOOL askToContinueForOuterClass(ClassContent *pContent);
	void printMsg(const char *msg);
	void resetDataMembers();
	BOOL preGenerateCode();
	BOOL checkClassName(char *className);
	void makeFileName(BOOL sourceFlag);
	void getMemberFunctionCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic);
	void getDataMemberCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic);
	void printFrontDocumentOfClass();
	void printInDocumentOfClass();
public:
	CodeGenerator();
	CodeGenerator(CodeGenerator *from);
	virtual ~CodeGenerator();
	virtual BOOL generateCodeFor(ClassContent *pContent,BOOL calledFromView);
	virtual void printClassHeading() = 0;
	virtual void printClassTailing() {}
};

#endif // !defined(AFX_CODEGENERATOR_H__1CEAA4C7_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
