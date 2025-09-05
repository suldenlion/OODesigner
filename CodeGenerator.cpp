// CodeGenerator.cpp: implementation of the CodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "CodeGenerator.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "ClassTemplate.h"
#include "CResizableEditDoc.h"
#include "CResizableEditView.h"
#include "TextContent.h"
#include "ClassTextLine.h"
#include "RelationshipInfoTupleList.h"
#include "COODClassDoc.h"
#include "ClassContent.h"
#include "PackageLibrary.h"
#include "ClassLibrary.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CodeGenerator::CodeGenerator()
{
	_innerClassFlag = FALSE;
	_innerClassContents = new ClassLibrary();
	resetDataMembers();
	_languageName = _T("");
}

CodeGenerator::CodeGenerator(CodeGenerator *from)
{
	_innerClassFlag = TRUE;
	_innerClassContents = new ClassLibrary();
	resetDataMembers();
	_nestLevel = from->_nestLevel + 1;
	_targetFile = from->_targetFile;
	_fileName = from->_fileName;
	_outputView = from->_outputView;
	_outputDoc = from->_outputDoc;
}

CodeGenerator::~CodeGenerator()
{
	_innerClassContents->clear(); delete _innerClassContents;
}

void CodeGenerator::resetDataMembers()
{
	_targetFile = NIL;
	_classContent = NIL;
	_className = _T("");
	_fileNameSpecified = _T("");
	_destructorName = _T("");
	_fileName = _T("");
	_superClassNames.RemoveAll();
	_outputView = NIL;
	_outputDoc = NIL;
	_nConstructors = 0;
	_nDestructors = 0;
	_innerClassContents->clear();
	_nestLevel = 0;
}

void CodeGenerator::getDataMemberCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic)
{
	nOfPrivates = 0;
	nOfProtected = 0;
	nOfPublic = 0;
	if (_classContent->nOfDataMembers() == 0) return;
	TextContent *content = _classContent->getVarContent();
	TextLine *aLine = content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		int vis = memberLine->visibility();
		if (vis == PROTECTED_ID) {
			nOfProtected++;
		} else if (vis == PRIVATE_ID) {
			nOfPrivates++;
		} else {
			nOfPublic++;
		}
		aLine = content->getNext();
	}
}

void CodeGenerator::getMemberFunctionCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic)
{
	nOfPrivates = 0;
	nOfProtected = 0;
	nOfPublic = 0;
	if (_classContent->nOfMemberFunctions() == 0) return;
	TextContent *content = _classContent->getMethodContent();
	TextLine *aLine = content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		int vis = memberLine->visibility();
		if (vis == PROTECTED_ID) {
			nOfProtected++;
		} else if (vis == PRIVATE_ID) {
			nOfPrivates++;
		} else {
			nOfPublic++;
		}
		aLine = content->getNext();
	}
}

void CodeGenerator::printMsg(const char *msg)
{
	CEdit &outputCtrl = _outputView->GetEditCtrl();
	outputCtrl.ReplaceSel(msg);
}

BOOL CodeGenerator::checkClassName(char *className)
{
	_className = className;
	if (strlen(className) == 0) {
		printMsg("error: invalid class name\r\n");
		printMsg("code generation fails\r\n");
		return FALSE;
	}
	if ((*className >= 'a' && *className <= 'z') ||
		(*className >= 'A' && *className <= 'Z') ||
		(*className == '_')) {
		_destructorName = "~";
		_destructorName = _destructorName+_className;

		if (theAppPtr->pCOODClassDoc != NIL) {
			theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->getMajorClassNames(_className,_superClassNames);
		}
		return TRUE;
	}
	printMsg("error: invalid class name ");
	printMsg(_className);
	printMsg("\r\ncode generation fails\r\n");
	return FALSE;
}

BOOL CodeGenerator::preGenerateCode()
{
	if (_innerClassFlag) return TRUE;

	theAppPtr->showOutputBar(TRUE);
	_outputDoc = theAppPtr->getOutputTextDoc();
	if (_outputDoc == NIL) {
		ErrorMsg("Code generation fails.\nDocument for output was not found.");
		return FALSE;
	}
	if (!_outputDoc->IsKindOf(RUNTIME_CLASS(CResizableEditDoc))) {
		ErrorMsg("Code generation fails.\nDocument for output was not found.");
		return FALSE;
	}
	_outputView = _outputDoc->getFirstView();
	if (_outputView == NIL) {
		ErrorMsg("Code generation fails.\nView for output was not found.");
		return FALSE;
	}
	if (!_outputView->IsKindOf(RUNTIME_CLASS(CResizableEditView))) {
		ErrorMsg("Code generation fails.\nView for output was not found.");
		return FALSE;
	}
	CEdit &outputCtrl = _outputView->GetEditCtrl();
	outputCtrl.SetSel(0,-1); 
	outputCtrl.ReplaceSel("");
	return TRUE;
}

void CodeGenerator::makeFileName(BOOL sourceFlag)
{
//	_fileName = theAppPtr->projectCodegenTargetDir + _className;
	_fileName = theAppPtr->projectCodegenTargetDir + _fileNameSpecified;
	if (sourceFlag == TRUE) {
		_fileName = _fileName + theAppPtr->projectSFExtension;
	} else {
		_fileName = _fileName + theAppPtr->projectHFExtension;
	}
}

void CodeGenerator::collectInnerClassContents()
{
	if (theAppPtr->pCOODClassDoc == NIL) return;
	PackageLibrary *allClassContents = theAppPtr->pCOODClassDoc->getAllClassContents();
	ClassLibrary *aLibrary = allClassContents->getFirst();
	while (aLibrary != NIL) {
		ClassContent *aContent = aLibrary->getFirst();
		while (aContent != NIL) {
			if (_className.CompareNoCase(aContent->outerClassName()) == 0) {
				_innerClassContents->insert(aContent);
			}
			aContent = aLibrary->getNext();
		}
		aLibrary = allClassContents->getNext();
	}
}

BOOL CodeGenerator::askToContinueForOuterClass(ClassContent *pContent)
{
	if (theAppPtr->pCOODClassDoc == NIL) return TRUE;
	char buffer[BUFSIZ];
	ClassContent *theContent = pContent;
	CString className = theContent->className();
	BOOL innerClassFlag = theContent->isInnerClass();
	while (innerClassFlag) {
		CString outerClassName = theContent->outerClassName();
		PackageLibrary *allClassContents = theAppPtr->pCOODClassDoc->getAllClassContents();
		theContent = 
			allClassContents->getClassContentFor(outerClassName);
		if (theContent == NIL) {
			sprintf_s(buffer,BUFSIZ,"The outmost container class %s of this inner class %s is not found.",
				outerClassName,className);
			ErrorMsg(buffer);
			return FALSE;
		}
		innerClassFlag = theContent->isInnerClass();
	}

	CString outerClassName = theContent->className();
	sprintf_s(buffer,BUFSIZ,"%s class is inner class of %s class.\r\nDo you want to generate code for %s ?",
		className,outerClassName,outerClassName);
	UINT ans = YesNoMsg(buffer);
	if (ans != IDYES) return FALSE;
	_classContent = theContent;
	return TRUE;
}

BOOL CodeGenerator::generateCodeFor(ClassContent *pContent,BOOL calledFromView)
{
	return FALSE;
}

void CodeGenerator::printFrontDocumentOfClass()
{
	fprintf(_targetFile,"//{{MODELER_BEFORE_CLASS(%s) - DO NOT DELETE THIS LINE\n",_className);

	CStringList *currentDocument = _classContent->headerFileFrontDocument();
	if (currentDocument->GetCount() == 0) {
		_classContent->resetDocument(currentDocument,HFFRONT);
	}
	POSITION pos = currentDocument->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = currentDocument->GetNext(pos);
		fprintf(_targetFile,"%s\n",aLine);
	}

	fprintf(_targetFile,"\n//}}MODELER_BEFORE_CLASS\n\n");
}

void CodeGenerator::printInDocumentOfClass()
{

	CStringList *currentDocument = _classContent->headerFileMiddleDocument();
	if (currentDocument->GetCount() == 0) {
		return;
	}
	if (currentDocument->GetCount() == 1) {
		CString aLine = currentDocument->GetHead();
		if (aLine.GetLength() > 2 && 
			aLine.GetAt(0) == '/' &&
			aLine.GetAt(1) == '/')
			return;
	}

	fprintf(_targetFile,"//{{MODELER_IN_CLASS(%s) - DO NOT DELETE THIS LINE\n",_className);
	POSITION pos = currentDocument->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = currentDocument->GetNext(pos);
		fprintf(_targetFile,"%s\n",aLine);
	}

	fprintf(_targetFile,"//}}MODELER_IN_CLASS\n\n");
}
