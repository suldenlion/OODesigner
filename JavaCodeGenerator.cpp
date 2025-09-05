// JavaCodeGenerator.cpp: implementation of the JavaCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "JavaCodeGenerator.h"
#include "CMainFrame.h"
#include "ClassContent.h"
#include "TextContent.h"
#include "TextLine.h"
#include "ClassTextLine.h"
#include "Text.h"
#include "ClassLibrary.h"

extern BOOL doesFileExist(const char* name);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

JavaCodeGenerator::JavaCodeGenerator()
: CodeGenerator()
{
	_languageName = "Java";
}

JavaCodeGenerator::JavaCodeGenerator(JavaCodeGenerator *from)
: CodeGenerator(from)
{
	_languageName = "Java";
}

JavaCodeGenerator::~JavaCodeGenerator()
{

}

void JavaCodeGenerator::printClassProperties()
{
	if (_classContent->visibility() == PUBLIC_ID) {
		fprintf(_targetFile,"public ");
	} else if (_classContent->visibility() == PROTECTED_ID) {
		fprintf(_targetFile,"protected ");
	} else if (_classContent->visibility() == PRIVATE_ID) {
		fprintf(_targetFile,"private ");
	}
	if (_classContent->abstractFlag()) {
		fprintf(_targetFile,"abstract ");
	}
	if (_classContent->staticFlag()) {
		fprintf(_targetFile,"static ");
	}
}

void JavaCodeGenerator::printSuperClassList()
{
	POSITION pos = _superClassNames.GetHeadPosition();
	if (pos == NULL) return;
	CString firstSuperClassName = _superClassNames.GetNext(pos);
	if (pos == NULL) {
		fprintf(_targetFile,"extends %s ",firstSuperClassName);
		return;
	} else {
		fprintf(_targetFile,"extends %s implements ",firstSuperClassName);
	}
	while (pos != NULL) {
		CString otherSuperClassName = _superClassNames.GetNext(pos);
		if (pos == NULL) {
			fprintf(_targetFile,"%s ",otherSuperClassName);
			return;
		} else {
			fprintf(_targetFile,"%s, ",otherSuperClassName);
		}
	}
}

void JavaCodeGenerator::checkTypeForAsterisk(CString &type,ClassTextLine *memberLine)
{
	if (type.Find('*') == -1 && type.Find('&') == -1) return;
	printMsg("warning: illegal type in ");
	printMsg(memberLine->ptrAt(0));
	printMsg(" was corrected by code generator\r\n");
	type = type.SpanExcluding( "*&");
}

void JavaCodeGenerator::printMemberFunctionModifiers(ClassTextLine *memberLine)
{
	if (memberLine->staticFlag() == TRUE && memberLine->abstractFlag() == TRUE) {
		fprintf(_targetFile,"static ");
		printMsg("warning: static member function should not be specified as abstract: ");
		printMsg(memberLine->ptrAt(0));
		printMsg("\r\n");
	} else if (memberLine->staticFlag() == TRUE) {
		fprintf(_targetFile,"static ");
	} else if (memberLine->abstractFlag() == TRUE) {
		fprintf(_targetFile,"abstract ");
	}
	if (memberLine->finalFlag() == TRUE) {
		fprintf(_targetFile,"final ");
	}
	if (memberLine->synchronizedFlag() == TRUE) {
		fprintf(_targetFile,"synchronized ");
	}
	if (memberLine->nativeFlag() == TRUE) {
		fprintf(_targetFile,"native ");
	}
}

void JavaCodeGenerator::printDataMemberModifiers(ClassTextLine *memberLine)
{
	if (memberLine->staticFlag() == TRUE && memberLine->transientFlag() == TRUE) {
		fprintf(_targetFile,"static ");
		printMsg("warning: static member should not be specified as transient: ");
		printMsg(memberLine->ptrAt(0));
		printMsg("\r\n");
	} else if (memberLine->staticFlag() == TRUE) {
		fprintf(_targetFile,"static ");
	} else if (memberLine->transientFlag() == TRUE) {
		fprintf(_targetFile,"transient ");
	}
	if (memberLine->finalFlag() == TRUE) {
		fprintf(_targetFile,"final ");
	}
}

void JavaCodeGenerator::printComment(ClassTextLine *memberLine)
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
		fprintf(_targetFile,"    %s\n",aLine);
	}
}

void JavaCodeGenerator::printDefaultValue(ClassTextLine *memberLine)
{
	if (memberLine->defaultValue().IsEmpty()) return;
	else if (memberLine->defaultValue().GetCount() == 1) {
		CString value = memberLine->defaultValue().GetHead();
		char checkBuffer[BUFSIZ];
		Text::strcpyCompact(checkBuffer,value,BUFSIZ);
		if (strlen(checkBuffer) == 0) {
			memberLine->defaultValue().RemoveAll();
			return;
		}
		int n = 0;
		while ((n = value.GetLength()) > 1) {
			if (value[n-1] == ' ') value = value.Left(n-1);
			else break;
		}
		fprintf(_targetFile," = %s",value);
		return;
	}

	CString valueToPrint = " = ";
	POSITION pos = memberLine->defaultValue().GetHeadPosition();
	while (pos != NULL) {
		CString value = memberLine->defaultValue().GetNext(pos);
		char checkBuffer[BUFSIZ];
		Text::strcpyCompact(checkBuffer,value,BUFSIZ);
		if (strlen(checkBuffer) >= 0) {
			int n = 0;
			while ((n = value.GetLength()) > 1) {
				if (value[n-1] == ' ') value = value.Left(n-1);
				else break;
			}
			valueToPrint = valueToPrint + value;
		}
		fprintf(_targetFile,"%s",valueToPrint);
		valueToPrint = "";
		if (pos != NULL) {
			fprintf(_targetFile,"\n");
		}
	}
}

void JavaCodeGenerator::printDataMembers()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getDataMemberCount(nOfPrivates,nOfProtected,nOfPublic);
	if (nOfPrivates+nOfProtected+nOfPublic == 0) return;
	fprintf(_targetFile,"// Attributes\n");
	if (nOfPrivates > 0) {
		TextContent *content = _classContent->getVarContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() == PRIVATE_ID) {
				printComment(memberLine);
				fprintf(_targetFile,"    ");
				fprintf(_targetFile,"private ");
				printDataMemberModifiers(memberLine);
				CString type = memberLine->type();
				if (type.GetLength() == 0) {
					fprintf(_targetFile,"Object ");
				} else {
					checkTypeForAsterisk(type,memberLine);
					fprintf(_targetFile,"%s ",type);
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"unknown");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					fprintf(_targetFile,"%s",memberLine->name());
				}
				printDefaultValue(memberLine);
				fprintf(_targetFile,";");
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
	if (nOfProtected > 0) {
		TextContent *content = _classContent->getVarContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() == PROTECTED_ID) {
				printComment(memberLine);
				fprintf(_targetFile,"    ");
				fprintf(_targetFile,"protected ");
				printDataMemberModifiers(memberLine);
				CString type = memberLine->type();
				if (type.GetLength() == 0) {
					fprintf(_targetFile,"Object ");
				} else {
					checkTypeForAsterisk(type,memberLine);
					fprintf(_targetFile,"%s ",type);
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"unknown");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					fprintf(_targetFile,"%s",memberLine->name());
				}
				printDefaultValue(memberLine);
				fprintf(_targetFile,";");
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
	if (nOfPublic > 0) {
		TextContent *content = _classContent->getVarContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() != PRIVATE_ID &&
				memberLine->visibility() != PROTECTED_ID) {
				printComment(memberLine);
				fprintf(_targetFile,"    ");
				CString type = memberLine->type();
				if (memberLine->visibility() == PUBLIC_ID) {
					fprintf(_targetFile,"public ");
					printDataMemberModifiers(memberLine);
					if (type.GetLength() == 0) {
						fprintf(_targetFile,"Object ");
					} else {
						fprintf(_targetFile,"%s ",type);
					}
				} else {
					printDataMemberModifiers(memberLine);
					if (type.GetLength() == 0) {
						fprintf(_targetFile,"Object ");
					} else {
						checkTypeForAsterisk(type,memberLine);
						fprintf(_targetFile,"%s ",type);
					}
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"unknown");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else {
					fprintf(_targetFile,"%s",memberLine->name());
				}
				printDefaultValue(memberLine);
				fprintf(_targetFile,";");
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
}

void JavaCodeGenerator::printMethodBody(ClassTextLine *memberLine)
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

void JavaCodeGenerator::printConstructor(char *vis,ClassTextLine *memberLine)
{
	_nConstructors++;
	if (strlen(vis) == 0) {
		fprintf(_targetFile,"    ");
	} else {
		fprintf(_targetFile,"    %s ",vis);
	}
	CString type = memberLine->type();
	if (type.GetLength() > 0) {
		fprintf(_targetFile,"%s ",type);
		printMsg("error: constructor with return type: ");
		printMsg(memberLine->ptrAt(0));
		printMsg("\r\n");
	}
	CString functionName = _T("");
	memberLine->getMethodSignatureString(functionName);
	fprintf(_targetFile,"%s {\n",functionName);
	printMethodBody(memberLine);
	fprintf(_targetFile,"    }\n");
}

void JavaCodeGenerator::printMemberFunctions()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getMemberFunctionCount(nOfPrivates,nOfProtected,nOfPublic);
	if (nOfPrivates+nOfProtected+nOfPublic == 0) return;
	fprintf(_targetFile,"\n// Operations\n");
	if (nOfPrivates > 0) {
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
				printComment(memberLine);
				printConstructor("private",memberLine);
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
				_className.Compare(memberLine->name()) != 0) {
				printComment(memberLine);
				fprintf(_targetFile,"    ");
				fprintf(_targetFile,"private ");
				printMemberFunctionModifiers(memberLine);
				CString type = memberLine->type();
				if (type.GetLength() == 0) {
					fprintf(_targetFile,"void ");
				} else {
					checkTypeForAsterisk(type,memberLine);
					fprintf(_targetFile,"%s ",type);
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"noname();");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else if (memberLine->abstractFlag() == TRUE) {
					CString functionName = _T("");
					memberLine->getMethodSignatureString(functionName);
					fprintf(_targetFile,"%s;",functionName);
				} else {
					CString functionName = _T("");
					memberLine->getMethodSignatureString(functionName);
					fprintf(_targetFile,"%s {\n",functionName);
					printMethodBody(memberLine);
					fprintf(_targetFile,"    }");
				}
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
	if (nOfProtected > 0) {
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
				printComment(memberLine);
				printConstructor("protected",memberLine);
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
				_className.Compare(memberLine->name()) != 0) {
				printComment(memberLine);
				fprintf(_targetFile,"    ");
				fprintf(_targetFile,"protected ");
				printMemberFunctionModifiers(memberLine);
				CString type = memberLine->type();
				if (type.GetLength() == 0) {
					fprintf(_targetFile,"void ");
				} else {
					checkTypeForAsterisk(type,memberLine);
					fprintf(_targetFile,"%s ",type);
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"noname();");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else if (memberLine->abstractFlag() == TRUE) {
					CString functionName = _T("");
					memberLine->getMethodSignatureString(functionName);
					fprintf(_targetFile,"%s;",functionName);
				} else {
					CString functionName = _T("");
					memberLine->getMethodSignatureString(functionName);
					fprintf(_targetFile,"%s {\n",functionName);
					printMethodBody(memberLine);
					fprintf(_targetFile,"    }");
				}
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
	if (nOfPublic > 0) {
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
				printComment(memberLine);
				if (memberLine->visibility() == PUBLIC_ID) {
					printConstructor("public",memberLine);
				} else {
					printConstructor("",memberLine);
				}
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
				_className.Compare(memberLine->name()) != 0) {
				printComment(memberLine);
				fprintf(_targetFile,"    ");
				CString type = memberLine->type();
				if (memberLine->visibility() == PUBLIC_ID) {
					fprintf(_targetFile,"public ");
					printMemberFunctionModifiers(memberLine);
					if (type.GetLength() == 0) {
						fprintf(_targetFile,"void ");
					} else {
						checkTypeForAsterisk(type,memberLine);
						fprintf(_targetFile,"%s ",type);
					}
				} else {
					printMemberFunctionModifiers(memberLine);
					if (type.GetLength() == 0) {
						fprintf(_targetFile,"void ");
					} else {
						checkTypeForAsterisk(type,memberLine);
						fprintf(_targetFile,"%s ",type);
					}
				}
				if (memberLine->name().GetLength() == 0) {
					fprintf(_targetFile,"noname();");
					printMsg("error: ");
					printMsg(memberLine->ptrAt(0));
					printMsg("\r\n");
				} else if (memberLine->abstractFlag() == TRUE) {
					CString functionName = _T("");
					memberLine->getMethodSignatureString(functionName);
					fprintf(_targetFile,"%s;",functionName);
				} else {
					CString functionName = _T("");
					memberLine->getMethodSignatureString(functionName);
					fprintf(_targetFile,"%s {\n",functionName);
					printMethodBody(memberLine);
					fprintf(_targetFile,"    }");
				}
				fprintf(_targetFile,"\n");
			}
			aLine = content->getNext();
		}
	}
}

void JavaCodeGenerator::printClassHeading()
{
	BOOL interfaceFlag = FALSE;

	interfaceFlag = _classContent->getInterfaceFlag();
	
	int i;
	for (i = 0; i < _nestLevel; i++) fprintf(_targetFile," ");
	printClassProperties();
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

BOOL JavaCodeGenerator::generateSourceFile()
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
	
		fprintf(_targetFile,"// %s%s\n\n",_fileNameSpecified,theAppPtr->projectSFExtension);
	}
	printFrontDocumentOfClass();

	printClassHeading();

	printInDocumentOfClass();

	printDataMembers();
	printMemberFunctions();

	ClassContent *pContent = _innerClassContents->getFirst();
	while(pContent != NIL) {
		JavaCodeGenerator newGenerator(this);
		if (newGenerator.generateCodeFor(pContent,FALSE) == FALSE)
			return FALSE;
		pContent = _innerClassContents->getNext();
	}

	for (int i = 0; i < _nestLevel; i++) fprintf(_targetFile," ");
	fprintf(_targetFile,"}\n");

	if (_innerClassFlag == FALSE) {
		fclose(_targetFile);
	}
	return TRUE;
}

BOOL JavaCodeGenerator::generateCodeFor(ClassContent *pContent,BOOL calledFromView)
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
		makeFileName(TRUE);
		printMsg("Generating ...\r\n");
		printMsg(_fileName);
		printMsg("\r\n");
	}

	if (generateSourceFile() == FALSE) return FALSE;


	if (_innerClassFlag == FALSE && calledFromView == TRUE) {
		CString viewName = _className + theAppPtr->projectSFExtension;
		mainFramePtr->closeTextFile(viewName);
		mainFramePtr->openTextFile(_fileName,viewName);
	}

	resetDataMembers();
	return TRUE;
}

