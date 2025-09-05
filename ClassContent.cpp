// ClassContent.cpp: implementation of the ClassContent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "ClassContent.h"
#include "ClassTemplate.h"
#include "TextContent.h"
#include "ClassTextLine.h"
#include "ClassText.h"
#include "Text.h"
#include "ArgumentList.h"
#include "CMainFrame.h"
#include "RelationshipInfoTupleList.h"
#include "COODClassDoc.h"
#include "FixedNamesTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ClassContent,CObject,1)

ClassContent::ClassContent()
: CObject()
{
	_visited = FALSE;
	_askedToDelete = FALSE;
	_templateFlag = FALSE;
	_abstractFlag = FALSE;
	_staticFlag = FALSE;
	_mfcClassFlag = FALSE;
	_serializableFlag = FALSE;
	_finalFlag = FALSE;
	_dynamicFlag = FALSE;
	_dyncreateFlag = FALSE;
	_generateCodeFlag = TRUE;
	_visibility = DEFAULT_ID;
	_employeedMap = 0;

	_outerClassName = _T("");
	_sourceFileName = _T("");
	_headerFileName = _T("");
	_targetDirectoryForCodeGeneration = _T("");
	_fileNameSpecified = _T("");
	_constraints.RemoveAll();

	_varContent = NIL;
	_methodContent = NIL;
	_className = _T("");
	_stereotype = _T("");
	_resourceID = _T("");
	_templateTagString = _T("");
	_headerFileFrontDocument.RemoveAll();
	_sourceFileFrontDocument.RemoveAll();
	_headerFileMiddleDocument.RemoveAll();
	_headerFileEndDocument.RemoveAll();
	_messageMap.RemoveAll();
	_interfaceMap.RemoveAll();
	_dispatchMap.RemoveAll();
	_olecmdMap.RemoveAll();
	_connectionMap.RemoveAll();
	_eventsinkMap.RemoveAll();
	_unspecifiedMaps.RemoveAll();
}

ClassContent::~ClassContent()
{
	if (_varContent != NIL) {
		delete _varContent; _varContent = NIL;
	}
	if (_methodContent != NIL) {
		delete _methodContent; _methodContent = NIL;
	}
	_constraints.RemoveAll();
	_headerFileFrontDocument.RemoveAll();
	_sourceFileFrontDocument.RemoveAll();
	_headerFileMiddleDocument.RemoveAll();
	_headerFileEndDocument.RemoveAll();
	_messageMap.RemoveAll();
	_interfaceMap.RemoveAll();
	_dispatchMap.RemoveAll();
	_olecmdMap.RemoveAll();
	_connectionMap.RemoveAll();
	_eventsinkMap.RemoveAll();
	_unspecifiedMaps.RemoveAll();
}

void ClassContent::Serialize(CArchive& ar)
{
// used for generateCodeFlag -> BOOL reservedFlag0ClassContent = FALSE;
	BOOL reservedFlag1ClassContent = FALSE;
	BOOL reservedFlag2ClassContent = FALSE;
	BOOL reservedFlag3ClassContent = FALSE;
	BOOL reservedFlag4ClassContent = FALSE;
	UINT reservedInt0ClassContent = 0;
	UINT reservedInt1ClassContent = 0;
	UINT reservedInt2ClassContent = 0;
	UINT reservedInt3ClassContent = 0;
	UINT reservedInt4ClassContent = 0;
// used for targetDirectoryForCodeGeneration -> CString reservedString0ClassContent = _T("");
// used for fileName -> CString reservedString1ClassContent = _T("");
	CString reservedString2ClassContent = _T("");
	CString reservedString3ClassContent = _T("");
	CString reservedString4ClassContent = _T("");

	CObject::Serialize(ar);
	_constraints.Serialize(ar);
	_headerFileFrontDocument.Serialize(ar);
	_sourceFileFrontDocument.Serialize(ar);
	_headerFileMiddleDocument.Serialize(ar);
	_headerFileEndDocument.Serialize(ar);
	_messageMap.Serialize(ar);
	_interfaceMap.Serialize(ar);
	_dispatchMap.Serialize(ar);
	_olecmdMap.Serialize(ar);
	_connectionMap.Serialize(ar);
	_eventsinkMap.Serialize(ar);
	_unspecifiedMaps.Serialize(ar);
	if (ar.IsStoring()) {
		ar << (BYTE)_templateFlag;
		ar << (BYTE)_abstractFlag;
		ar << (BYTE)_staticFlag;
		ar << (BYTE)_mfcClassFlag;
		ar << (BYTE)_serializableFlag;
		ar << (BYTE)_finalFlag;
		ar << (BYTE)_dynamicFlag;
		ar << (BYTE)_dyncreateFlag;
		ar << (LONG)_visibility;
		ar << (LONG)_employeedMap;
		ar << _stereotype;
		ar << _outerClassName;
		ar << _resourceID ;
		ar << _templateTagString;
		ar << _className << _varContent << _methodContent;

		ar << (BYTE)_generateCodeFlag;
		ar << (BYTE)reservedFlag1ClassContent;
		ar << (BYTE)reservedFlag2ClassContent;
		ar << (BYTE)reservedFlag3ClassContent;
		ar << (BYTE)reservedFlag4ClassContent;
		ar << (LONG)reservedInt0ClassContent;
		ar << (LONG)reservedInt1ClassContent;
		ar << (LONG)reservedInt2ClassContent;
		ar << (LONG)reservedInt3ClassContent;
		ar << (LONG)reservedInt4ClassContent;
		ar << _targetDirectoryForCodeGeneration;
		ar << _fileNameSpecified;
		ar << reservedString2ClassContent;
		ar << reservedString3ClassContent;
		ar << reservedString4ClassContent;
	} else {
		ar >> (BYTE&)_templateFlag;
		ar >> (BYTE&)_abstractFlag;
		ar >> (BYTE&)_staticFlag;
		ar >> (BYTE&)_mfcClassFlag;
		ar >> (BYTE&)_serializableFlag;
		ar >> (BYTE&)_finalFlag;
		ar >> (BYTE&)_dynamicFlag;
		ar >> (BYTE&)_dyncreateFlag;
		ar >> (LONG&)_visibility;
		ar >> (LONG&)_employeedMap;
		ar >> _stereotype;
		ar >> _outerClassName;
		ar >> _resourceID;
		ar >> _templateTagString;
		ar >> _className >> _varContent >> _methodContent;

		ar >> (BYTE&)_generateCodeFlag;
		ar >> (BYTE&)reservedFlag1ClassContent;
		ar >> (BYTE&)reservedFlag2ClassContent;
		ar >> (BYTE&)reservedFlag3ClassContent;
		ar >> (BYTE&)reservedFlag4ClassContent;
		ar >> (LONG&)reservedInt0ClassContent;
		ar >> (LONG&)reservedInt1ClassContent;
		ar >> (LONG&)reservedInt2ClassContent;
		ar >> (LONG&)reservedInt3ClassContent;
		ar >> (LONG&)reservedInt4ClassContent;
		ar >> _targetDirectoryForCodeGeneration;
		ar >> _fileNameSpecified;
		ar >> reservedString2ClassContent;
		ar >> reservedString3ClassContent;
		ar >> reservedString4ClassContent;
		if (theAppPtr->fileVersionNo.CompareNoCase("0401") < 0) {
			_generateCodeFlag = TRUE;
		}
	}
}

void ClassContent::setEmployeedMap(unsigned int mapId)
{
	_employeedMap = _employeedMap | mapId;
}

void ClassContent::resetEmployeedMap(unsigned int mapId)
{
	_employeedMap = _employeedMap & (~mapId);
}

BOOL ClassContent::getInterfaceFlag()
{
	if (_stereotype.CompareNoCase("interface") == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void ClassContent::setStereotype(const char *stype)
{
	_stereotype = stype;
}

void ClassContent::setOuterClassName(const char *oname)
{
	char buffer[BUFSIZ];
	buffer[0] = '\0';
	Text::strcpyCompact(buffer,oname,BUFSIZ);
	_outerClassName = buffer;
	if (_className.CompareNoCase(_outerClassName) == 0)
		_outerClassName = _T("");
}

void ClassContent::setFileNameSpecified(const char *fname)
{
	char buffer[BUFSIZ];
	buffer[0] = '\0';
	Text::strcpyCompact(buffer,fname,BUFSIZ);
	_fileNameSpecified = buffer;

	if (_fileNameSpecified.GetLength() == 0) {
		_fileNameSpecified = _className;
	}
}

BOOL ClassContent::isInnerClass()
{
	if (_className.CompareNoCase(_outerClassName) == 0)
		_outerClassName = _T("");
	if (_outerClassName.IsEmpty()) return FALSE;
	return TRUE;
}

BOOL ClassContent::getStereotype(char *stype)
{
	char buffer[BUFSIZ];
	if (Text::strcpyCompact(buffer,_stereotype,BUFSIZ) > 0) {
		strcpy_s(stype,BUFSIZ,"<<");
		strcat_s(stype,BUFSIZ,_stereotype);
		strcat_s(stype,BUFSIZ,">>");
		return TRUE;
	}
	return FALSE;
}

BOOL ClassContent::hasEqualName(CString &aName)
{
	if (_className.CompareNoCase(aName) == 0) return TRUE;
	return FALSE;
}

void ClassContent::parseMembers()
{
	TextLine *aLine = _varContent->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		memberLine->parseAsDataMember();
		aLine = _varContent->getNext();
	}
	aLine = _methodContent->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		memberLine->parseAsMemberFunction();
		aLine = _methodContent->getNext();
	}
}

void ClassContent::setClassContentFrom(ClassTemplate *fromClass)
{
	if (fromClass == NIL) {
		_varContent = new TextContent();
		_varContent->newLineAt(0,IAMCLASSTEXT);
		_methodContent = new TextContent();
		_methodContent->newLineAt(0,IAMCLASSTEXT);
		return;
	}
	char buffer[BUFSIZ];
	fromClass->getTemplateTagString(buffer,BUFSIZ);
	_templateTagString = buffer;
	_templateFlag = fromClass->getTemplateFlag();
	if (_varContent != NIL) delete _varContent;
	_varContent = fromClass->getVarContent();
	if (_methodContent != NIL) delete _methodContent;
	_methodContent = fromClass->getMethodContent();
}

TextContent *ClassContent::getVarContent()
{
	return _varContent;
}

TextContent *ClassContent::getMethodContent()
{
	return _methodContent;
}

void ClassContent::setVarContent(TextContent *ptr)
{
	_varContent = ptr;
}

void ClassContent::setMethodContent(TextContent *ptr)
{
	_methodContent = ptr;
}

TextContent *ClassContent::copyVarContent()
{
	return _varContent->born();
}

TextContent *ClassContent::copyMethodContent()
{
	return _methodContent->born();
}

int ClassContent::nOfMemberFunctions()
{
	if (_methodContent->nOfLines() == 1 && 
		_methodContent->valueAt(0,0) == '\0') return 0;
	return _methodContent->nOfLines();
}

int ClassContent::nOfDataMembers()
{
	if (_varContent->nOfLines() == 1 && 
		_varContent->valueAt(0,0) == '\0') return 0;
	return _varContent->nOfLines();
}

void ClassContent::getDataMemberBrowserString(int i,int &vis,CString &aLineString)
{
	TextLine *aLine = _varContent->lineAt(i);
	if (aLine == NIL) {
		// Error Case.
		aLineString = _T("");
		vis = 0;
		return;
	}
	if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
		// Error Case.
		aLineString = aLine->ptrAt(0);
		vis = 0;
		return;
	}
	ClassTextLine *memberLine = (ClassTextLine *)aLine;
	vis = memberLine->visibility();
	memberLine->getMemberBrowserString(aLineString);
}

void ClassContent::getMemberFunctionBrowserString(int i,int &vis,CString &aLineString)
{
	TextLine *aLine = _methodContent->lineAt(i);
	if (aLine == NIL) {
		// Error Case.
		aLineString = _T("");
		vis = 0;
		return;
	}
	if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
		// Error Case.
		aLineString = aLine->ptrAt(0);
		vis = 0;
		return;
	}
	ClassTextLine *memberLine = (ClassTextLine *)aLine;
	vis = memberLine->visibility();
	memberLine->getMemberBrowserString(aLineString);
}

void ClassContent::deleteMemberFunction(int index)
{
	if (_methodContent->nOfLines() == 1) {
		_methodContent->lineAt(0)->clear();
		return;
	}
	_methodContent->removeLineAt(index);
}

ClassTextLine *ClassContent::getMemberFunctionLine(int index)
{
	TextLine *aLine = _methodContent->lineAt(index);
	if (aLine == NIL) {
		return NIL;
	}
	if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
		return NIL;
	}
	ClassTextLine *memberLine = (ClassTextLine *)aLine;
	CString aLineString;
	memberLine->getMemberBrowserString(aLineString);
	return memberLine;
}

ClassTextLine *ClassContent::getMemberFunctionLine(int index,CString &browserString)
{
	TextLine *aLine = _methodContent->lineAt(index);
	if (aLine == NIL) {
		return NIL;
	}
	if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
		return NIL;
	}
	ClassTextLine *memberLine = (ClassTextLine *)aLine;
	CString aLineString;
	memberLine->getMemberBrowserString(aLineString);
	if (browserString.CompareNoCase(aLineString) != 0) return NIL;
	return memberLine;
}

void ClassContent::deleteDataMember(int index)
{
	if (_varContent->nOfLines() == 1) {
		_varContent->lineAt(0)->clear();
		return;
	}
	_varContent->removeLineAt(index);
}

void ClassContent::getTemplateTagString(char *buffer,int size)
{
	strcpy_s(buffer,BUFSIZ,_templateTagString);
}

ClassTextLine *ClassContent::getDataMemberLine(int index)
{
	TextLine *aLine = _varContent->lineAt(index);
	if (aLine == NIL) {
		return NIL;
	}
	if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
		return NIL;
	}
	ClassTextLine *memberLine = (ClassTextLine *)aLine;
//	CString aLineString;
//	memberLine->getMemberBrowserString(aLineString);
	return memberLine;
}

ClassTextLine *ClassContent::getDataMemberLine(int index,CString &browserString)
{
	TextLine *aLine = _varContent->lineAt(index);
	if (aLine == NIL) {
		return NIL;
	}
	if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
		return NIL;
	}
	ClassTextLine *memberLine = (ClassTextLine *)aLine;
	CString aLineString;
	memberLine->getMemberBrowserString(aLineString);
	if (browserString.CompareNoCase(aLineString) != 0) return NIL;
	return memberLine;
}

void ClassContent::writeVisibility(CString &vis)
{
	if (vis.CompareNoCase("public") == 0) {
		_visibility = PUBLIC_ID;
	} else if (vis.CompareNoCase("protected") == 0) {
		_visibility = PROTECTED_ID;
	} else if (vis.CompareNoCase("private") == 0) {
		_visibility = PRIVATE_ID;
	} else {
		_visibility = DEFAULT_ID;
	}
}

BOOL ClassContent::tryToInsertSerializationFunction()
{
	BOOL repaintFlag = tryToInsertDefaultConstructor();

	TextLine *aLine = _methodContent->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		char nameBuffer[BUFSIZ];
		Text::strcpyCompact(nameBuffer,memberLine->name(),BUFSIZ);
		char typeBuffer[BUFSIZ];
		Text::strcpyCompact(typeBuffer,memberLine->type(),BUFSIZ);
		if (strcmp(nameBuffer,"Serialize") == 0 &&
			(strcmp(typeBuffer,"void") == 0 || strlen(typeBuffer) == 0)&&
			memberLine->virtualFlag() == TRUE) {
			return repaintFlag;
		}
		aLine = _methodContent->getNext();
	}
	ClassTextLine *theLine = new ClassTextLine();
	_methodContent->insertAt(theLine,nOfMemberFunctions());
	CString newString = "+Serialize(ar:CArchive &):void {virtual}";
	theLine->setString(newString);
	theLine->parseAsMemberFunction();
	return TRUE;
}

BOOL ClassContent::tryToInsertDefaultConstructor()
{
	TextLine *aLine = _methodContent->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		char nameBuffer[BUFSIZ];
		Text::strcpyCompact(nameBuffer,memberLine->name(),BUFSIZ);
		char thisClassName[BUFSIZ];
		Text::strcpyCompact(thisClassName,_className,BUFSIZ);
		if (strcmp(nameBuffer,_className) == 0 &&
			memberLine->arguments()->nOfList() == 0) {
			return FALSE;
		}
		aLine = _methodContent->getNext();
	}
	ClassTextLine *theLine = new ClassTextLine();
	_methodContent->insertAt(theLine,0);
	CString newString = _className + "()";
	theLine->setString(newString);
	theLine->parseAsMemberFunction();
	makeDefaultConstructorBody(theLine);
	return TRUE;
}

void ClassContent::makeDefaultConstructorBody(ClassTextLine *theConstructor)
{
	CStringList &functionBody = theConstructor->functionBody();
	functionBody.RemoveAll(); 

	TextLine *aLine = _varContent->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		if (memberLine->staticFlag() == FALSE) {
			CString lineBuffer;
			lineBuffer = "\t";
			lineBuffer = lineBuffer + memberLine->name();
			lineBuffer = lineBuffer + " = ";
			char defaultValueBuffer[BUFSIZ];
			defaultValueBuffer[0] = '\0';
			if (memberLine->defaultValue().GetCount() > 0) {
				strcpy_s(defaultValueBuffer,BUFSIZ,memberLine->defaultValue().GetHead());
				lineBuffer = lineBuffer + defaultValueBuffer;
				lineBuffer.TrimRight();
			} else {
				char typeBuffer[BUFSIZ];
				Text::strcpyCompact(typeBuffer,memberLine->type(),BUFSIZ);
				int nType = strlen(typeBuffer);
				if (nType == 0) {
					lineBuffer = lineBuffer + "0";
				} else if (typeBuffer[nType-1] == '*') {
					lineBuffer = lineBuffer + "NULL";
				} else if (strcmp("CString",typeBuffer) == 0) {
					lineBuffer = lineBuffer + "\"\"";
				} else {
					lineBuffer = lineBuffer + "0";
				}
			}
			lineBuffer = lineBuffer + ";";
			functionBody.AddTail(lineBuffer);
		}
		aLine = _varContent->getNext();
	}
}

void ClassContent::resetDocument(CStringList *aDocument,int which)
{ 
	aDocument->RemoveAll();
	char buffer[BUFSIZ];
	CString className = _className;
	CString language = theAppPtr->projectLanguage;
	CStringList superClassNames;
	if (theAppPtr->pCOODClassDoc != NIL)
		theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->getMajorClassNames(className,superClassNames);
	if (which == HFFRONT) { 
		if (language.CompareNoCase("Java") == 0) {
			aDocument->AddTail("//OODesigner will reverse the code here.");
			aDocument->AddTail("");

			sprintf_s(buffer,BUFSIZ,"//Organization: %s",theAppPtr->projectOrganization);
			aDocument->AddTail(buffer);
			sprintf_s(buffer,BUFSIZ,"//Author: %s",theAppPtr->projectAuthor);
			aDocument->AddTail(buffer);
			CTime currentTime = CTime::GetCurrentTime();
			sprintf_s(buffer,BUFSIZ,"//Date: %s",currentTime.Format("%A, %B %d, %Y"));
			aDocument->AddTail(buffer);

			CString superClassNamesComment = "//Super class: ";
			POSITION pos = superClassNames.GetHeadPosition();
			while (pos != NULL) {
				CString superClassName = superClassNames.GetNext(pos);
				if (pos == NULL) {
					superClassNamesComment = superClassNamesComment + superClassName;
					break;
				} else {
					superClassNamesComment = superClassNamesComment + superClassName + ", ";
				}
			}
			aDocument->AddTail(superClassNamesComment);
			sprintf_s(buffer,BUFSIZ,"//Purpose of %s class:",className);
			aDocument->AddTail(buffer);
			aDocument->AddTail("/**");
			aDocument->AddTail("*/");
		} else {
			aDocument->AddTail("//OODesigner will reverse the code here.");
			aDocument->AddTail("");

			CStringList &macros = theAppPtr->getHeaderFileAbsMacros(language);
			int nOfLines = macros.GetCount();
			if (nOfLines > 0) {
				aDocument->AddTail(&macros);
				aDocument->AddTail("");
			}
			BOOL everPrinted = FALSE;
			POSITION pos = superClassNames.GetHeadPosition();
			while (pos != NULL) {
				CString superClassName = superClassNames.GetNext(pos);
				if (theAppPtr->getBuiltInClassTable()->haveName(superClassName) == FALSE) {
					everPrinted = TRUE;
					sprintf_s(buffer,BUFSIZ,"#include \"%s%s\"",superClassName,theAppPtr->projectHFExtension);
					aDocument->AddTail(buffer);
				}
				if (pos == NULL && everPrinted == TRUE) {
					aDocument->AddTail("");
					break;
				}
			}
			aDocument->AddTail("typedef int unspecified;");
			aDocument->AddTail("");
			sprintf_s(buffer,BUFSIZ,"//Organization: %s",theAppPtr->projectOrganization);
			aDocument->AddTail(buffer);
			sprintf_s(buffer,BUFSIZ,"//Author: %s",theAppPtr->projectAuthor);
			aDocument->AddTail(buffer);
			CTime currentTime = CTime::GetCurrentTime();
			sprintf_s(buffer,BUFSIZ,"//Date: %s",currentTime.Format("%A, %B %d, %Y"));
			aDocument->AddTail(buffer);

			CString superClassNamesComment = "//Super class: ";
			pos = superClassNames.GetHeadPosition();
			while (pos != NULL) {
				CString superClassName = superClassNames.GetNext(pos);
				if (pos == NULL) {
					superClassNamesComment = superClassNamesComment + superClassName;
					break;
				} else {
					superClassNamesComment = superClassNamesComment + superClassName + ", ";
				}
			}
			aDocument->AddTail(superClassNamesComment);
			sprintf_s(buffer,BUFSIZ,"//Purpose of %s class:",className);
			aDocument->AddTail(buffer);
			aDocument->AddTail("/**");
			aDocument->AddTail("*/");
		}
	} else if (which == SFFRONT) {
		if (language.CompareNoCase("Java") != 0) {
			sprintf_s(buffer,BUFSIZ,"//Organization: %s",theAppPtr->projectOrganization);
			aDocument->AddTail(buffer);
			sprintf_s(buffer,BUFSIZ,"//Author: %s",theAppPtr->projectAuthor);
			aDocument->AddTail(buffer);
			CTime currentTime = CTime::GetCurrentTime();
			sprintf_s(buffer,BUFSIZ,"//Date: %s",currentTime.Format("%A, %B %d, %Y"));
			aDocument->AddTail(buffer);

			CString superClassNamesComment = "//Super class: ";
			POSITION pos = superClassNames.GetHeadPosition();
			while (pos != NULL) {
				CString superClassName = superClassNames.GetNext(pos);
				if (pos == NULL) {
					superClassNamesComment = superClassNamesComment + superClassName;
					break;
				} else {
					superClassNamesComment = superClassNamesComment + superClassName + ", ";
				}
			}
			aDocument->AddTail(superClassNamesComment);
			aDocument->AddTail("/**");
			aDocument->AddTail("*/");
			aDocument->AddTail("");

			// static variable definition
			BOOL staticVarExist = FALSE;
			TextLine *aLine = _varContent->getFirst();
			while (aLine != NIL) {
				if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
					break;
				}
				ClassTextLine *memberLine = (ClassTextLine *)aLine;
				if (memberLine->staticFlag()) {
					if (staticVarExist == FALSE) {
						staticVarExist = TRUE;
						aDocument->AddTail("// static data member definitions");
					}
					CString lineBuffer = "";
					if (memberLine->type().GetLength() > 0) {
						lineBuffer = lineBuffer + memberLine->type();
					} else {
						lineBuffer = lineBuffer + "unspecified";
					}
					lineBuffer = lineBuffer + " " + _className + "::" + memberLine->name() + " = ";
					if (memberLine->defaultValue().GetCount() > 0) {
						POSITION pos = memberLine->defaultValue().GetHeadPosition();
						while(pos != NULL) {
							CString aLine = memberLine->defaultValue().GetNext(pos);
							lineBuffer = lineBuffer + aLine;
							lineBuffer.TrimRight();
							if (pos == NULL) {
								lineBuffer = lineBuffer + ";";
								aDocument->AddTail(lineBuffer);
							} else {
								aDocument->AddTail(lineBuffer);
								lineBuffer = "";
							}
						}
					} else {
						char typeBuffer[BUFSIZ];
						Text::strcpyCompact(typeBuffer,memberLine->type(),BUFSIZ);
						int nType = strlen(typeBuffer);
						if (nType == 0) {
							lineBuffer = lineBuffer + "0";
						} else if (typeBuffer[nType-1] == '*') {
							lineBuffer = lineBuffer + "NULL";
						} else if (strcmp("CString",typeBuffer) == 0) {
							lineBuffer = lineBuffer + "\"\"";
						} else {
							lineBuffer = lineBuffer + "0";
						}
						lineBuffer = lineBuffer + ";";
						aDocument->AddTail(lineBuffer);
					}
				}
				aLine = _varContent->getNext();
			}
			if (staticVarExist == TRUE) {
				aDocument->AddTail("");
			}		

			CStringList &macros = theAppPtr->getSourceFileAbsMacros(language);
			int nOfLines = macros.GetCount();
			if (nOfLines > 0) {
				aDocument->AddTail(&macros);
				aDocument->AddTail("");
			}
		}
	} else if (which == HFMIDDLE) {
		aDocument->AddTail("// specify non-UML syntax constructs within class definition:");
	} else if (which == HFEND) {
		if (language.CompareNoCase("Visual C++") == 0) {
			aDocument->AddTail("");
			aDocument->AddTail("//{{AFX_INSERT_LOCATION}}");	
			aDocument->AddTail("// Microsoft Developer Studio will insert additional declarations immediately before the previous line.");	
		}
	}
}

CString &ClassContent::fileNameSpecified() 
{ 
	if (_fileNameSpecified.GetLength() == 0) {
		_fileNameSpecified = _className;
	}
	return _fileNameSpecified; 
}

CString &ClassContent::targetDirectoryForCodeGeneration() 
{ 
	if (_targetDirectoryForCodeGeneration.GetLength() == 0) {
		_targetDirectoryForCodeGeneration = theAppPtr->projectCodegenTargetDir;
	}
	return _targetDirectoryForCodeGeneration; 
}