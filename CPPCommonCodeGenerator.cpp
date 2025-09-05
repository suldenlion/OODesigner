// CPPCommonCodeGenerator.cpp: implementation of the CPPCommonCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "CPPCommonCodeGenerator.h"
#include "CMainFrame.h"
#include "TextContent.h"
#include "ClassTextLine.h"
#include "RelationshipInfoTupleList.h"
#include "COODClassDoc.h"
#include "ArgumentList.h"
#include "ArgumentInfo.h"
#include "FixedNamesTable.h"
#include "ClassContent.h"
#include "ClassLibrary.h"
#include "CPPCodeGenerator.h"

extern BOOL doesFileExist(const char* name);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPPCommonCodeGenerator::CPPCommonCodeGenerator()
: CodeGenerator()
{
	_macroString = _T("");
	_templateTagAll = _T("");
	_templateTagArg = _T("");
}

CPPCommonCodeGenerator::CPPCommonCodeGenerator(CPPCommonCodeGenerator *from)
: CodeGenerator(from)
{
	_macroString = _T("");
	_templateTagAll = _T("");
	_templateTagArg = _T("");
}

CPPCommonCodeGenerator::~CPPCommonCodeGenerator()
{

}

void CPPCommonCodeGenerator::makeHFMacroString()
{
	_macroString = "_";
	CString extension = theAppPtr->projectHFExtension;
	extension = extension.Right(extension.GetLength()-1);
	_macroString = _macroString + _className + "_" + extension;
	_macroString.MakeUpper();
}

void CPPCommonCodeGenerator::outputHFIdentificationMacro()
{
	makeHFMacroString();
	fprintf(_targetFile,"#if !defined(%s)\n",_macroString);
	fprintf(_targetFile,"#define %s\n\n",_macroString);
}

void CPPCommonCodeGenerator::printSlashDelemeter()
{
	for (int i = 0; i < 70; i++) {
		fprintf(_targetFile,"/");
	}
	fprintf(_targetFile,"\n");
}

void CPPCommonCodeGenerator::printFrontDocumentOfSourceFile()
{
	fprintf(_targetFile,"//{{MODELER_SOURCE_DOCUMENT(%s) - DO NOT DELETE THIS LINE\n",_className);

	CStringList *currentDocument = _classContent->sourceFileFrontDocument();
	if (currentDocument->GetCount() == 0) {
		_classContent->resetDocument(currentDocument,SFFRONT);
	}
	POSITION pos = currentDocument->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = currentDocument->GetNext(pos);
		fprintf(_targetFile,"%s\n",aLine);
	}

	fprintf(_targetFile,"//}}MODELER_SOURCE_DOCUMENT\n\n");
}

void CPPCommonCodeGenerator::printEndDocumentOfClass()
{
	if (_classContent->mfcClassFlag() == FALSE) return;

	CStringList *currentDocument = _classContent->headerFileEndDocument();
	if (currentDocument->GetCount() == 0) {
		_classContent->resetDocument(currentDocument,HFEND);
	}
	POSITION pos = currentDocument->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = currentDocument->GetNext(pos);
		fprintf(_targetFile,"%s\n",aLine);
	}
}

void CPPCommonCodeGenerator::printSuperClassList()
{
	POSITION pos = _superClassNames.GetHeadPosition();
	if (pos == NULL) return;
	CString visibility = "public";
	CString firstSuperClassName = _superClassNames.GetNext(pos);
	if (theAppPtr->pCOODClassDoc != NIL)
		theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->getVisibilityFor(firstSuperClassName,_className,visibility);
	if (pos == NULL) {
		fprintf(_targetFile,": %s %s",visibility,firstSuperClassName);
		return;
	} else {
		fprintf(_targetFile,": %s %s, ",visibility,firstSuperClassName);
	}
	while (pos != NULL) {
		CString otherSuperClassName = _superClassNames.GetNext(pos);
		if (theAppPtr->pCOODClassDoc != NIL)
			theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->getVisibilityFor(otherSuperClassName,_className,visibility);
		if (pos == NULL) {
			fprintf(_targetFile,"%s %s",visibility,otherSuperClassName);
			return;
		} else {
			fprintf(_targetFile,"%s %s, ",visibility,otherSuperClassName);
		}
	}
}

void CPPCommonCodeGenerator::printClassHeading()
{
	BOOL templateFlag = FALSE;
	BOOL interfaceFlag = FALSE;

	templateFlag = _classContent->getTemplateFlag();
	interfaceFlag = _classContent->getInterfaceFlag();

	int i;
	for (i = 0; i < _nestLevel; i++) fprintf(_targetFile," ");
	if (templateFlag == TRUE) {
		ClassTextLine tagLine;
		char buffer[BUFSIZ];
		_classContent->getTemplateTagString(buffer,BUFSIZ);
		tagLine.setString(buffer);
		tagLine.convertAsCArgument(buffer);
		_templateTagAll = "<";
		_templateTagArg = "<";
		ArgumentList *theList = tagLine.arguments();
		ArgumentInfo *anArg = theList->getFirst();
		while (anArg != NIL) {
			if (anArg->argName.GetLength() == 0 &&
				anArg->argType.GetLength() == 0) {
				anArg = theList->getNext();
				continue;
			} else if (anArg->argName.GetLength() == 0 &&
				anArg->argType.GetLength() > 0) {
				_templateTagAll = _templateTagAll + "class " + anArg->argType;
				_templateTagArg = _templateTagArg + anArg->argType;
			} else if (anArg->argName.GetLength() > 0 &&
				anArg->argType.GetLength() == 0) {
				_templateTagAll = _templateTagAll + "class " + anArg->argName;
				_templateTagArg = _templateTagArg + anArg->argName;
			} else if (anArg->argName.GetLength() > 0 &&
				anArg->argType.GetLength() > 0) {
				_templateTagAll = _templateTagAll + anArg->argType + " " + anArg->argName;
				_templateTagArg = _templateTagArg + anArg->argName;
			}
			if (anArg->defaultValue.GetLength() > 0) {
				_templateTagAll = _templateTagAll + "=" + anArg->defaultValue;
			}
			anArg = theList->getNext();
			if (anArg != NIL) {
				_templateTagAll = _templateTagAll + ",";
				_templateTagArg = _templateTagArg + ",";
			}
		}
		_templateTagAll = _templateTagAll + ">";
		_templateTagArg = _templateTagArg + ">";
		fprintf(_targetFile,"template %s\n",_templateTagAll);
	}
	if (interfaceFlag == TRUE) {
		fprintf(_targetFile,"interface %s ",_className);
	} else {
		fprintf(_targetFile,"class %s ",_className);
	}
	printSuperClassList();
	fprintf(_targetFile,"\n");
	for (i = 0; i < _nestLevel; i++) fprintf(_targetFile," ");
	fprintf(_targetFile,"{\n");
}

void CPPCommonCodeGenerator::printfTemplateClassBody()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getMemberFunctionCount(nOfPrivates,nOfProtected,nOfPublic);
	if (nOfPrivates+nOfProtected+nOfPublic == 0) return;
	fprintf(_targetFile,"\n");
	
	TextContent *content = _classContent->getMethodContent();
	TextLine *aLine = content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		if (memberLine->virtualFlag() == TRUE &&
			memberLine->defaultValue().GetCount() > 0) {
			aLine = content->getNext();
			continue;
		}
		printComment(memberLine,"");
		fprintf(_targetFile,"template %s\n",_templateTagAll);
		if (memberLine->inlineFlag() == TRUE) {
			fprintf(_targetFile,"inline ");
		}
		if (_className.Compare(memberLine->name()) != 0 &&
			_destructorName.Compare(memberLine->name()) != 0) {
			if (memberLine->type().GetLength() == 0) {
				fprintf(_targetFile,"void ");
			} else {
				fprintf(_targetFile,"%s ",memberLine->type());
			}
		}
		fprintf(_targetFile,"%s%s::",_className,_templateTagArg);
		if (memberLine->name().GetLength() == 0) {
			fprintf(_targetFile,"noname()");
		} else {
			CString functionName = _T("");
			memberLine->getMethodSignatureString(functionName);
			fprintf(_targetFile,"%s",functionName);
		}
		if (memberLine->constFlag() == TRUE) {
			fprintf(_targetFile," const");
		}
		fprintf(_targetFile,"\n{\n");
		printMethodBody(memberLine);
		fprintf(_targetFile,"}\n\n");

		aLine = content->getNext();
	}
}

void CPPCommonCodeGenerator::printConstructorSpec(ClassTextLine *memberLine,BOOL withBody)
{
	_nConstructors++;
	fprintf(_targetFile,"\t");
	if (memberLine->type().GetLength() > 0) {
		fprintf(_targetFile,"%s ",memberLine->type());
		printMsg("error: constructor with return type: ");
		printMsg(memberLine->ptrAt(0));
		printMsg("\r\n");
	}
	CString functionName = _T("");
	memberLine->getMemberBrowserString(functionName);
	if (withBody == FALSE) {
		fprintf(_targetFile,"%s;",functionName);
		fprintf(_targetFile,"\n");
	} else {
		fprintf(_targetFile,"%s ",functionName);

		CStringList *superInitValue = memberLine->baseClassInitialization();
		if (superInitValue->GetCount() == 0) {
			if (_superClassNames.GetCount() > 0) {
				fprintf(_targetFile,": ");
			}
			POSITION pos = _superClassNames.GetHeadPosition();
			while (pos != NULL) {
				CString superClassName = _superClassNames.GetNext(pos);
				if (pos == NULL) {
					fprintf(_targetFile,"%s() ",superClassName);
					break;
				} else {
					fprintf(_targetFile,"%s(), ",superClassName);
				}
			}
			fprintf(_targetFile," {\n");
		} else {
			fprintf(_targetFile,": ");
			POSITION pos = superInitValue->GetHeadPosition();
			while (pos != NULL) {
				CString aValueLine = superInitValue->GetNext(pos);
				fprintf(_targetFile,"%s\n",aValueLine);
			}
			fprintf(_targetFile,"\t{\n");
		}

		printMethodBody(memberLine);
		fprintf(_targetFile,"\t}\n");
	}
}

void CPPCommonCodeGenerator::printDestructorSpec(ClassTextLine *memberLine,BOOL withBody)
{
	_nDestructors++;
	if (_nDestructors > 1) {
		printMsg("error: too many destructors\r\n");
	}
	fprintf(_targetFile,"\t");
	if (memberLine->type().GetLength() > 0) {
		fprintf(_targetFile,"%s ",memberLine->type());
		printMsg("error: destructor with return type: ");
		printMsg(memberLine->ptrAt(0));
		printMsg("\r\n");
	}
	if (memberLine->hasArgument() == TRUE) {
		printMsg("error: destructor with argument: ");
		printMsg(memberLine->ptrAt(0));
		printMsg("\r\n");
	}
	CString functionName = _T("");
	memberLine->getMemberBrowserString(functionName);
	if (memberLine->virtualFlag()) {
		fprintf(_targetFile,"virtual ");
	}
	if (withBody == FALSE) {
		fprintf(_targetFile,"%s;",functionName);
		fprintf(_targetFile,"\n");
	} else {
		fprintf(_targetFile,"%s {\n",functionName);
		printMethodBody(memberLine);
		fprintf(_targetFile,"\t}\n");
	}
}

void CPPCommonCodeGenerator::printMemberFunctionSpecs(BOOL withBody)
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getMemberFunctionCount(nOfPrivates,nOfProtected,nOfPublic);
	if (nOfPrivates+nOfProtected+nOfPublic == 0) return;
	fprintf(_targetFile,"// Operations\n");
	if (nOfPrivates > 0) {
		fprintf(_targetFile,"private:\n");
		TextContent *content = _classContent->getMethodContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			// 첫번째 블럭에서는 생성자 먼저 프린트 ...
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() == PRIVATE_ID &&
				_className.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printConstructorSpec(memberLine,withBody);
			} else if (memberLine->visibility() == PRIVATE_ID &&
				_destructorName.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printDestructorSpec(memberLine,withBody);
			}
			aLine = content->getNext();
		}
		aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() == PRIVATE_ID &&
				_className.Compare(memberLine->name()) != 0 &&
				_destructorName.Compare(memberLine->name()) != 0) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\t");
				if (memberLine->staticFlag() == TRUE) {
					fprintf(_targetFile,"static ");
				} else if (memberLine->virtualFlag() == TRUE) {
					fprintf(_targetFile,"virtual ");
				}
				if (memberLine->type().GetLength() == 0) {
					fprintf(_targetFile,"void ");
				} else {
					fprintf(_targetFile,"%s ",memberLine->type());
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"noname()");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					CString functionName = _T("");
					memberLine->getMemberBrowserString(functionName);
					fprintf(_targetFile,"%s",functionName);
				}
				if (memberLine->constFlag() == TRUE) {
					fprintf(_targetFile," const");
				}
				if (memberLine->virtualFlag() == TRUE &&
					memberLine->defaultValue().GetCount() > 0) {
					fprintf(_targetFile," = 0;\n");
				} else if (withBody == TRUE) {
					fprintf(_targetFile," {\n");
					printMethodBody(memberLine);
					fprintf(_targetFile,"    }\n");
				} else {
					fprintf(_targetFile,";\n");
				}
			}
			aLine = content->getNext();
		}
	}
	if (nOfProtected > 0) {
		fprintf(_targetFile,"protected:\n");
		TextContent *content = _classContent->getMethodContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			// 첫번째 블럭에서는 생성자 먼저 프린트 ...
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() == PROTECTED_ID &&
				_className.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printConstructorSpec(memberLine,withBody);
			} else if (memberLine->visibility() == PROTECTED_ID &&
				_destructorName.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printDestructorSpec(memberLine,withBody);
			}
			aLine = content->getNext();
		}
		aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() == PROTECTED_ID &&
				_className.Compare(memberLine->name()) != 0 &&
				_destructorName.Compare(memberLine->name()) != 0) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\t");
				if (memberLine->staticFlag() == TRUE) {
					fprintf(_targetFile,"static ");
				} else if (memberLine->virtualFlag() == TRUE) {
					fprintf(_targetFile,"virtual ");
				}
				if (memberLine->type().GetLength() == 0) {
					fprintf(_targetFile,"void ");
				} else {
					fprintf(_targetFile,"%s ",memberLine->type());
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"noname()");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					CString functionName = _T("");
					memberLine->getMemberBrowserString(functionName);
					fprintf(_targetFile,"%s",functionName);
				}
				if (memberLine->constFlag() == TRUE) {
					fprintf(_targetFile," const");
				}
				if (memberLine->virtualFlag() == TRUE &&
					memberLine->defaultValue().GetCount() > 0) {
					fprintf(_targetFile," = 0;\n");
				} else if (withBody == TRUE) {
					fprintf(_targetFile," {\n");
					printMethodBody(memberLine);
					fprintf(_targetFile,"    }\n");
				} else {
					fprintf(_targetFile,";\n");
				}
			}
			aLine = content->getNext();
		}
	}
	if (nOfPublic > 0) {
		fprintf(_targetFile,"public:\n");
		TextContent *content = _classContent->getMethodContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			// 첫번째 블럭에서는 생성자 먼저 프린트 ...
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() != PRIVATE_ID &&
				memberLine->visibility() != PROTECTED_ID &&
				_className.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printConstructorSpec(memberLine,withBody);
			} else if (memberLine->visibility() != PRIVATE_ID &&
				memberLine->visibility() != PROTECTED_ID &&
				_destructorName.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printDestructorSpec(memberLine,withBody);
			}
			aLine = content->getNext();
		}
		aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() != PRIVATE_ID &&
				memberLine->visibility() != PROTECTED_ID &&
				_className.Compare(memberLine->name()) != 0 &&
				_destructorName.Compare(memberLine->name()) != 0) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\t");
				if (memberLine->staticFlag() == TRUE) {
					fprintf(_targetFile,"static ");
				} else if (memberLine->virtualFlag() == TRUE) {
					fprintf(_targetFile,"virtual ");
				}
				if (memberLine->type().GetLength() == 0) {
					fprintf(_targetFile,"void ");
				} else {
					fprintf(_targetFile,"%s ",memberLine->type());
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"noname()");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					CString functionName = _T("");
					memberLine->getMemberBrowserString(functionName);
					fprintf(_targetFile,"%s",functionName);
				}
				if (memberLine->constFlag() == TRUE) {
					fprintf(_targetFile," const");
				}
				if (memberLine->virtualFlag() == TRUE &&
					memberLine->defaultValue().GetCount() > 0) {
					fprintf(_targetFile," = 0;\n");
				} else if (withBody == TRUE) {
					fprintf(_targetFile," {\n");
					printMethodBody(memberLine);
					fprintf(_targetFile,"    }\n");
				} else {
					fprintf(_targetFile,";\n");
				}
			}
			aLine = content->getNext();
		}
	}
}

void CPPCommonCodeGenerator::printComment(ClassTextLine *memberLine,const char *blanks)
{
	CStringList *commentLines = memberLine->comment();
	int nOfLines = commentLines->GetCount();
	if (nOfLines == 0) return;
	if (nOfLines == 2) {
		POSITION pos = commentLines->GetHeadPosition();
		CString aLine = commentLines->GetNext(pos);
		CString bLine = commentLines->GetNext(pos);
		if (aLine.CompareNoCase("/**") == 0 &&
			bLine.CompareNoCase(" */") == 0)
			return;
	}
	POSITION pos = commentLines->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = commentLines->GetNext(pos);
		fprintf(_targetFile,"%s%s\n",blanks,aLine);
	}
}

void CPPCommonCodeGenerator::printClassMemberSpecs()
{
	printDataMembers();
	printMemberFunctionSpecs(_innerClassFlag);
}

void CPPCommonCodeGenerator::printDataMembers()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getDataMemberCount(nOfPrivates,nOfProtected,nOfPublic);
	if (nOfPrivates+nOfProtected+nOfPublic == 0) return;
	fprintf(_targetFile,"// Attributes\n");
	if (nOfPrivates > 0) {
		fprintf(_targetFile,"private:\n");
		TextContent *content = _classContent->getVarContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() == PRIVATE_ID) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\t");
				if (memberLine->staticFlag() == TRUE) {
					fprintf(_targetFile,"static ");
				}
				if (memberLine->type().GetLength() == 0) {
					fprintf(_targetFile,"unspecified ");
				} else {
					fprintf(_targetFile,"%s ",memberLine->type());
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"unknown;");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					fprintf(_targetFile,"%s;",memberLine->name());
				}
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
	if (nOfProtected > 0) {
		fprintf(_targetFile,"protected:\n");
		TextContent *content = _classContent->getVarContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() == PROTECTED_ID) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\t");
				if (memberLine->staticFlag() == TRUE) {
					fprintf(_targetFile,"static ");
				}
				if (memberLine->type().GetLength() == 0) {
					fprintf(_targetFile,"unspecified ");
				} else {
					fprintf(_targetFile,"%s ",memberLine->type());
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"unknown;");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					fprintf(_targetFile,"%s;",memberLine->name());
				}
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
	if (nOfPublic > 0) {
		fprintf(_targetFile,"public:\n");
		TextContent *content = _classContent->getVarContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() != PRIVATE_ID &&
				memberLine->visibility() != PROTECTED_ID) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\t");
				if (memberLine->staticFlag() == TRUE) {
					fprintf(_targetFile,"static ");
				}
				if (memberLine->type().GetLength() == 0) {
					fprintf(_targetFile,"unspecified ");
				} else {
					fprintf(_targetFile,"%s ",memberLine->type());
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"unknown;");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					fprintf(_targetFile,"%s;",memberLine->name());
				}
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
}

BOOL CPPCommonCodeGenerator::generateHeaderFile()
{
	if (_innerClassFlag == FALSE) {
		if (doesFileExist(_fileName)) {
			theAppPtr->removeFileAndBackingUp(_fileName);
		}
		fopen_s(&_targetFile,_fileName,"w+");
		if (_targetFile == NULL) {
			printMsg("error: file can't be open\r\n");
			printMsg("code generation fails\r\n");
			return FALSE;
		}
	
		outputHFIdentificationMacro();
//		fprintf(_targetFile,"// %s%s : header file\n//\n\n",_className,theAppPtr->projectHFExtension);
		fprintf(_targetFile,"// %s%s : header file\n//\n\n",_fileNameSpecified,theAppPtr->projectHFExtension);

		printSlashDelemeter();
		fprintf(_targetFile,"\n");
		printFrontDocumentOfClass();
	}

	printClassHeading();

	ClassContent *pContent = _innerClassContents->getFirst();
	while(pContent != NIL) {
		// inner class 는 무조건 generic class 취급
		CPPCodeGenerator newGenerator((CPPCodeGenerator*)this);
		if (newGenerator.generateCodeFor(pContent,FALSE) == FALSE)
			return FALSE;
		pContent = _innerClassContents->getNext();
	}

	printInDocumentOfClass();
	
	printClassMemberSpecs();

	printClassTailing();

	for (int i = 0; i < _nestLevel; i++) fprintf(_targetFile," ");
	fprintf(_targetFile,"};\n");

	if (_innerClassFlag == FALSE) {
		if (_classContent->getTemplateFlag() == TRUE)
			printfTemplateClassBody();
		else
			printInlineFunctions();

		printEndDocumentOfClass();

		fprintf(_targetFile,"\n#endif // !defined(%s)\n",_macroString);
		fclose(_targetFile);
	}
	return TRUE;
}

void CPPCommonCodeGenerator::printConstructorsAndDestructors()
{
	if (_nConstructors+_nDestructors == 0) return;

	printSlashDelemeter();
	fprintf(_targetFile,"// Construction/Destruction\n");
	printSlashDelemeter();
	fprintf(_targetFile,"\n");
	TextContent *content = _classContent->getMethodContent();
	TextLine *aLine = content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		if (_className.Compare(memberLine->name()) == 0) { 
			printComment(memberLine,"");
			fprintf(_targetFile,"%s::",_className);
			CString functionName = _T("");
			memberLine->getMethodSignatureString(functionName);
			fprintf(_targetFile,"%s\n",functionName);

			CStringList *superInitValue = memberLine->baseClassInitialization();
			if (superInitValue->GetCount() == 0) {
				if (_superClassNames.GetCount() > 0) {
					fprintf(_targetFile,": ");
				}
				POSITION pos = _superClassNames.GetHeadPosition();
				while (pos != NULL) {
					CString superClassName = _superClassNames.GetNext(pos);
					if (pos == NULL) {
						fprintf(_targetFile,"%s()\n",superClassName);
						break;
					} else {
						fprintf(_targetFile,"%s(), ",superClassName);
					}
				}
			} else {
				fprintf(_targetFile,": ");
				POSITION pos = superInitValue->GetHeadPosition();
				while (pos != NULL) {
					CString aValueLine = superInitValue->GetNext(pos);
					fprintf(_targetFile,"%s\n",aValueLine);
				}
			}

			fprintf(_targetFile,"{\n");
			printMethodBody(memberLine);
			fprintf(_targetFile,"}\n\n");
		} else if (_destructorName.Compare(memberLine->name()) == 0) {
			printComment(memberLine,"");
			fprintf(_targetFile,"%s::",_className);
			CString functionName = _T("");
			memberLine->getMethodSignatureString(functionName);
			fprintf(_targetFile,"%s",functionName);
			fprintf(_targetFile,"\n{\n");
			printMethodBody(memberLine);
			fprintf(_targetFile,"}\n\n");
		}
		aLine = content->getNext();
	}
}

void CPPCommonCodeGenerator::printMethodBody(ClassTextLine *memberLine)
{
	CStringList &body = memberLine->functionBody();
	if (body.GetCount() == 0) {
        fprintf(_targetFile,"\n");
		return;
	}
	POSITION pos = body.GetHeadPosition();
	while(pos != NULL) {
		CString aLine = body.GetNext(pos);
		if (pos != NULL) {
               fprintf(_targetFile,"%s\n",aLine);
		} else if (aLine.GetLength() > 0) {
               fprintf(_targetFile,"%s\n",aLine);
		}
	}
}

void CPPCommonCodeGenerator::printInlineFunctions()
{
	BOOL firstFlag = TRUE;

	TextContent *content = _classContent->getMethodContent();
	TextLine *aLine = content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		if (memberLine->inlineFlag() == TRUE) {
			if (_className.Compare(memberLine->name()) != 0 &&
				_destructorName.Compare(memberLine->name()) != 0) { 
				if (firstFlag == TRUE) {
					firstFlag = FALSE;
					fprintf(_targetFile,"\n");
				}
				if (memberLine->type().GetLength() == 0) {
					fprintf(_targetFile,"inline void ");
				} else {
					fprintf(_targetFile,"inline %s ",memberLine->type());
				}
				fprintf(_targetFile,"%s::",_className);
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"noname()");
				} else {
					CString functionName = _T("");
					memberLine->getMethodSignatureString(functionName);
					fprintf(_targetFile,"%s",functionName);
				}
				if (memberLine->constFlag() == TRUE) {
					fprintf(_targetFile," const");
				}
				fprintf(_targetFile,"\n{\n");
				printMethodBody(memberLine);
				fprintf(_targetFile,"}\n\n");
			}
		}
		aLine = content->getNext();
	}
}

void CPPCommonCodeGenerator::printMemberFunctions()
{
	printSlashDelemeter();
	fprintf(_targetFile,"// Methods\n");
	printSlashDelemeter();
	fprintf(_targetFile,"\n");

	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getMemberFunctionCount(nOfPrivates,nOfProtected,nOfPublic);
	if (nOfPrivates+nOfProtected+nOfPublic == 0) return;
	
	TextContent *content = _classContent->getMethodContent();
	TextLine *aLine = content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		if (memberLine->inlineFlag() == FALSE) {
			if (_className.Compare(memberLine->name()) != 0 &&
				_destructorName.Compare(memberLine->name()) != 0) { 
				if (memberLine->virtualFlag() == TRUE &&
					memberLine->defaultValue().GetCount() > 0) {
					aLine = content->getNext();
					continue;
				}
				printComment(memberLine,"");
				if (memberLine->type().GetLength() == 0) {
					fprintf(_targetFile,"void ");
				} else {
					fprintf(_targetFile,"%s ",memberLine->type());
				}
				fprintf(_targetFile,"%s::",_className);
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"noname()");
				} else {
					CString functionName = _T("");
					memberLine->getMethodSignatureString(functionName);
					fprintf(_targetFile,"%s",functionName);
				}
				if (memberLine->constFlag() == TRUE) {
					fprintf(_targetFile," const");
				}
				fprintf(_targetFile,"\n{\n");
				printMethodBody(memberLine);
				fprintf(_targetFile,"}\n\n");
			}
		}
		aLine = content->getNext();
	}
}

BOOL CPPCommonCodeGenerator::generateSourceFile()
{
	if (doesFileExist(_fileName)) {
		theAppPtr->removeFileAndBackingUp(_fileName);
	}
	fopen_s(&_targetFile,_fileName,"w+");
	if (_targetFile == NULL) {
		printMsg("error: file can't be open\r\n");
		printMsg("code generation fails\r\n");
		return FALSE;
	}
	
//	fprintf(_targetFile,"// %s%s : implementation file\n",_className,theAppPtr->projectSFExtension);
	fprintf(_targetFile,"// %s%s : implementation file\n",_fileNameSpecified,theAppPtr->projectSFExtension);
	fprintf(_targetFile,"//\n\n");
	if (_languageName.CompareNoCase("Visual C++") == 0) {
		fprintf(_targetFile,"#include \"stdafx.h\"\n");
	}
	fprintf(_targetFile,"#include \"%s%s\"\n\n",_fileNameSpecified,theAppPtr->projectHFExtension);
	printFrontDocumentOfSourceFile();
	outputSFSpecialMacro();

	printConstructorsAndDestructors();
	outputSFSpecialConstruct();
	printMemberFunctions();

	fclose(_targetFile);
	return TRUE;
}

BOOL CPPCommonCodeGenerator::generateCodeFor(ClassContent *pContent,BOOL calledFromView)
{
	if (calledFromView && pContent->isInnerClass()) {
		if (askToContinueForOuterClass(pContent)== FALSE) return FALSE;
		// _classContent is set for outer class content
	} else {
		_classContent = pContent;
	}

	_classContent->parseMembers();
	if (preGenerateCode() == FALSE) return FALSE;
	if (_innerClassFlag == FALSE) {
		printMsg("---------------Configuration: ");
		printMsg(_languageName);
		printMsg(" Code Generator---------------\r\n");
	}

	char buffer[BUFSIZ];
	strcpy_s(buffer,BUFSIZ,_classContent->className());
	if (checkClassName(buffer) == FALSE) return FALSE;
	_fileNameSpecified = _classContent->fileNameSpecified();
	
	collectInnerClassContents();

	if (_innerClassFlag == FALSE) {
		makeFileName(FALSE);
		printMsg("Generating ...\r\n");
		printMsg(_fileName);
		printMsg("\r\n");
	}

	if (generateHeaderFile() == FALSE) return FALSE;

	if (_innerClassFlag == FALSE && calledFromView == TRUE) {
		if (_nConstructors == 0) {
			printMsg("warning: this class has no constructor\r\n");
		}
		CString viewName = _className + theAppPtr->projectHFExtension;
		mainFramePtr->closeTextFile(viewName);
		mainFramePtr->openTextFile(_fileName,viewName);

		if (_classContent->getTemplateFlag() == TRUE) return TRUE;

		makeFileName(TRUE);
		printMsg("Generating ...\r\n");
		printMsg(_fileName);
		printMsg("\r\n");

		if (generateSourceFile() == FALSE) return FALSE;
		viewName = _className + theAppPtr->projectSFExtension;
		mainFramePtr->closeTextFile(viewName);
		mainFramePtr->openTextFile(_fileName,viewName);
	}

	resetDataMembers();
	return TRUE;
}

