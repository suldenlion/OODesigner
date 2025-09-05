// VCPPCodeGenerator.cpp: implementation of the VCPPCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "VCPPCodeGenerator.h"
#include "CMainFrame.h"
#include "ClassContent.h"
#include "RelationshipInfoTupleList.h"
#include "COODClassDoc.h"
#include "TextContent.h"
#include "ClassTextLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VCPPCodeGenerator::VCPPCodeGenerator()
: CPPCommonCodeGenerator()
{
	_languageName = "Visual C++";
}

VCPPCodeGenerator::VCPPCodeGenerator(VCPPCodeGenerator *from)
: CPPCommonCodeGenerator(from)
{
	_languageName = "Visual C++";
}

VCPPCodeGenerator::~VCPPCodeGenerator()
{

}

void VCPPCodeGenerator::outputSFSpecialConstruct()
{
	CPPCommonCodeGenerator::outputSFSpecialConstruct();
	unsigned int employeedMap = _classContent->employeedMap();
	if (employeedMap == 0) return;
	if (employeedMap & KTG_MESSAGEMAP) {
		outputAMap("MESSAGE_MAP",_classContent->messageMap());
	} 
	if (employeedMap & KTG_INTERFACEMAP) {
		outputAMap("INTERFACE_MAP",_classContent->interfaceMap());
	} 
	if (employeedMap & KTG_DISPATCHMAP) {
		outputAMap("DISPATCH_MAP",_classContent->dispatchMap());
	} 
	if (employeedMap & KTG_OLECMDMAP) {
		outputAMap("OLECMD_MAP",_classContent->olecmdMap());
	} 
	if (employeedMap & KTG_CONNECTIONMAP) {
		outputAMap("CONNECTION_MAP",_classContent->connectionMap());
	} 
	if (employeedMap & KTG_EVENTSINKMAP) {
		outputAMap("EVENTSINK_MAP",_classContent->eventsinkMap());
	} 
	if (employeedMap & KTG_UNSPECIFIEDMAP) {
		outputAMap("unspecified maps",_classContent->unspecifiedMaps());
	} 
}

void VCPPCodeGenerator::outputAMap(const char *mapName,CStringList *currentMap)
{
	if (strcmp(mapName,"unspecified maps") != 0) {
		CStringList superClassNames;
		if (theAppPtr->pCOODClassDoc != NIL)
			theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->getMajorClassNames(_className,superClassNames);
		CString superClassName = "CCmdTarget";
		POSITION pos = superClassNames.GetHeadPosition();
		if (pos != NULL) {
			superClassName = superClassNames.GetNext(pos);
		}
		fprintf(_targetFile,"BEGIN_%s(%s,%s)\n",mapName,_className,superClassName);
		pos = currentMap->GetHeadPosition();
		while(pos != NULL) {
			CString aLine = currentMap->GetNext(pos);
			fprintf(_targetFile,"%s\n",aLine);
		}
		fprintf(_targetFile,"END_%s()\n\n",mapName);
	} else {
		POSITION pos = currentMap->GetHeadPosition();
		while(pos != NULL) {
			CString aLine = currentMap->GetNext(pos);
			fprintf(_targetFile,"%s\n",aLine);
		}
		fprintf(_targetFile,"\n");
	}
}

void VCPPCodeGenerator::outputSFSpecialMacro()
{
	CPPCommonCodeGenerator::outputSFSpecialMacro();

	CString superClassName = "CObject";
	POSITION pos = _superClassNames.GetHeadPosition();
	if (pos != NULL) {
		superClassName = _superClassNames.GetNext(pos);
	}
	
	if (_classContent->serializableFlag()) {
		fprintf(_targetFile,"IMPLEMENT_SERIAL(%s,%s,1)\n\n",_className,superClassName);
	}
	if (_classContent->dynamicFlag()) {
		fprintf(_targetFile,"IMPLEMENT_DYNAMIC(%s,%s)\n\n",_className,superClassName);
	}
	if (_classContent->dyncreateFlag()) {
		fprintf(_targetFile,"IMPLEMENT_DYNCREATE(%s,%s)\n\n",_className,superClassName);
	}
}

void VCPPCodeGenerator::printClassHeading()
{
	CPPCommonCodeGenerator::printClassHeading();
	if (_classContent->serializableFlag()) {
		fprintf(_targetFile,"\tDECLARE_SERIAL(%s)\n",_className);
	}
	if (_classContent->dynamicFlag()) {
		fprintf(_targetFile,"\tDECLARE_DYNAMIC(%s)\n",_className);
	}
	if (_classContent->dyncreateFlag()) {
		fprintf(_targetFile,"\tDECLARE_DYNCREATE(%s)\n",_className);
	}
}

void VCPPCodeGenerator::printClassTailing()
{
	unsigned int employeedMap = _classContent->employeedMap();
	if (employeedMap == 0) return;
	if (employeedMap & KTG_MESSAGEMAP) {
		fprintf(_targetFile,"\tDECLARE_MESSAGE_MAP()\n");
	} 
	if (employeedMap & KTG_INTERFACEMAP) {
		fprintf(_targetFile,"\tDECLARE_INTERFACE_MAP()\n");
	} 
	if (employeedMap & KTG_DISPATCHMAP) {
		fprintf(_targetFile,"\tDECLARE_DISPATCH_MAP()\n");
	} 
	if (employeedMap & KTG_OLECMDMAP) {
		fprintf(_targetFile,"\tDECLARE_OLECMD_MAP()\n");
	} 
	if (employeedMap & KTG_CONNECTIONMAP) {
		fprintf(_targetFile,"\tDECLARE_CONNECTION_MAP()\n");
	} 
	if (employeedMap & KTG_EVENTSINKMAP) {
		fprintf(_targetFile,"\tDECLARE_EVENTSINK_MAP()\n");
	} 
}

void VCPPCodeGenerator::printClassMemberSpecs()
{
	printDataMembers();
	printMemberFunctionSpecs();
	printAfxDataMembers();
	printAfxFieldMembers();
	printAfxVirtualMemberFunctionSpecs();
	printAfxMsgMemberFunctionSpecs();
}

void VCPPCodeGenerator::getGeneralDataMemberCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic)
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
		if (memberLine->afxDataFlag() == FALSE &&
			memberLine->afxFieldFlag() == FALSE) {
			int vis = memberLine->visibility();
			if (vis == PROTECTED_ID) {
				nOfProtected++;
			} else if (vis == PRIVATE_ID) {
				nOfPrivates++;
			} else {
				nOfPublic++;
			}
		}
		aLine = content->getNext();
	}
}

void VCPPCodeGenerator::getAfxDataMemberCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic)
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
		if (memberLine->afxDataFlag() == TRUE) {
			int vis = memberLine->visibility();
			if (vis == PROTECTED_ID) {
				nOfProtected++;
			} else if (vis == PRIVATE_ID) {
				nOfPrivates++;
			} else {
				nOfPublic++;
			}
		}
		aLine = content->getNext();
	}
}

void VCPPCodeGenerator::getAfxFieldMemberCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic)
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
		if (memberLine->afxFieldFlag() == TRUE) {
			int vis = memberLine->visibility();
			if (vis == PROTECTED_ID) {
				nOfProtected++;
			} else if (vis == PRIVATE_ID) {
				nOfPrivates++;
			} else {
				nOfPublic++;
			}
		}
		aLine = content->getNext();
	}
}

void VCPPCodeGenerator::getAfxMsgMemberFunctionCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic)
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
		if (memberLine->afxMsgFlag() == TRUE) {
			int vis = memberLine->visibility();
			if (vis == PROTECTED_ID) {
				nOfProtected++;
			} else if (vis == PRIVATE_ID) {
				nOfPrivates++;
			} else {
				nOfPublic++;
			}
		}
		aLine = content->getNext();
	}
}

void VCPPCodeGenerator::getAfxVirtualMemberFunctionCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic)
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
		if (memberLine->afxVirtualFlag() == TRUE) {
			int vis = memberLine->visibility();
			if (vis == PROTECTED_ID) {
				nOfProtected++;
			} else if (vis == PRIVATE_ID) {
				nOfPrivates++;
			} else {
				nOfPublic++;
			}
		}
		aLine = content->getNext();
	}
}

void VCPPCodeGenerator::getGeneralMemberFunctionCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic)
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
		if (memberLine->afxMsgFlag() == FALSE &&
			memberLine->afxVirtualFlag() == FALSE) {
			int vis = memberLine->visibility();
			if (vis == PROTECTED_ID) {
				nOfProtected++;
			} else if (vis == PRIVATE_ID) {
				nOfPrivates++;
			} else {
				nOfPublic++;
			}
		}
		aLine = content->getNext();
	}
}

void VCPPCodeGenerator::printDataMembers()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getGeneralDataMemberCount(nOfPrivates,nOfProtected,nOfPublic);
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
			if (memberLine->visibility() == PRIVATE_ID &&
				memberLine->afxDataFlag() == FALSE &&
				memberLine->afxFieldFlag() == FALSE) {
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
			if (memberLine->visibility() == PROTECTED_ID &&
				memberLine->afxDataFlag() == FALSE &&
				memberLine->afxFieldFlag() == FALSE) {
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
				memberLine->visibility() != PROTECTED_ID &&
				memberLine->afxDataFlag() == FALSE &&
				memberLine->afxFieldFlag() == FALSE) {
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

void VCPPCodeGenerator::printMemberFunctionSpecs()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getGeneralMemberFunctionCount(nOfPrivates,nOfProtected,nOfPublic);
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
				printConstructorSpec(memberLine,FALSE);
			} else if (memberLine->visibility() == PRIVATE_ID &&
				_destructorName.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printDestructorSpec(memberLine,FALSE);
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
				memberLine->afxVirtualFlag() == FALSE &&
				memberLine->afxMsgFlag() == FALSE &&
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
					fprintf(_targetFile," = 0");
				}
				fprintf(_targetFile,";\n");
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
				printConstructorSpec(memberLine,FALSE);
			} else if (memberLine->visibility() == PROTECTED_ID &&
				_destructorName.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printDestructorSpec(memberLine,FALSE);
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
				memberLine->afxVirtualFlag() == FALSE &&
				memberLine->afxMsgFlag() == FALSE &&
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
					fprintf(_targetFile," = 0");
				}
				fprintf(_targetFile,";\n");
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
				printConstructorSpec(memberLine,FALSE);
			} else if (memberLine->visibility() != PRIVATE_ID &&
				memberLine->visibility() != PROTECTED_ID &&
				_destructorName.Compare(memberLine->name()) == 0) { 
				printComment(memberLine,"\t");
				printDestructorSpec(memberLine,FALSE);
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
				memberLine->afxVirtualFlag() == FALSE &&
				memberLine->afxMsgFlag() == FALSE &&
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
					fprintf(_targetFile," = 0");
				}
				fprintf(_targetFile,";\n");
			}
			aLine = content->getNext();
		}
	}
}

void VCPPCodeGenerator::printAfxDataMembers()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getAfxDataMemberCount(nOfPrivates,nOfProtected,nOfPublic);
	if (nOfPrivates+nOfProtected+nOfPublic == 0) {
		if (_classContent->mfcClassFlag() == FALSE) return;
		CString idString = _classContent->resourceID();
		idString.TrimLeft();
		if (idString.IsEmpty()) return;
		fprintf(_targetFile,"\n\t//{{AFX_DATA(%s)\n",_className);
		fprintf(_targetFile,"\tenum { IDD = %s };\n",idString);
		fprintf(_targetFile,"\t//}}AFX_DATA\n\n");
		return;
	}
	fprintf(_targetFile,"\n\t//{{AFX_DATA(%s)\n",_className);
	CString idString = _classContent->resourceID();
	idString.TrimLeft();
	if (!idString.IsEmpty()) {
		fprintf(_targetFile,"\tenum { IDD = %s };\n",idString);
	}
	// afx data 경우에는 visibility를 무시함. (왜? 대개 그러니깐)
	TextContent *content = _classContent->getVarContent();
	TextLine *aLine = content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		if (memberLine->afxDataFlag() == TRUE) {
			printComment(memberLine,"\t");
			fprintf(_targetFile,"\t");
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
	fprintf(_targetFile,"\t//}}AFX_DATA\n\n");
}

void VCPPCodeGenerator::printAfxFieldMembers()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getAfxFieldMemberCount(nOfPrivates,nOfProtected,nOfPublic);
	if (nOfPrivates+nOfProtected+nOfPublic == 0) return;

	CStringList superClassNames;
	if (theAppPtr->pCOODClassDoc != NIL)
		theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->getMajorClassNames(_className,superClassNames);
	CString superClassName = "CRecordset";
	POSITION pos = superClassNames.GetHeadPosition();
	if (pos != NULL) {
		superClassName = superClassNames.GetNext(pos);
	}

	fprintf(_targetFile,"// Field/Param Data\n");
	fprintf(_targetFile,"\t//{{AFX_FIELD(%s,%s)\n",_className,superClassName);
	// afx data 경우에는 visibility를 무시함. (왜? 대개 그러니깐)
	TextContent *content = _classContent->getVarContent();
	TextLine *aLine = content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		if (memberLine->afxFieldFlag() == TRUE) {
			printComment(memberLine,"\t");
			fprintf(_targetFile,"\t");
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
	fprintf(_targetFile,"\t//}}AFX_FIELD\n\n");
}

void VCPPCodeGenerator::printAfxVirtualMemberFunctionSpecs()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getAfxVirtualMemberFunctionCount(nOfPrivates,nOfProtected,nOfPublic);

	unsigned int employeedMap = _classContent->employeedMap();

	if (_classContent->mfcClassFlag() == TRUE ||
		(employeedMap & KTG_MESSAGEMAP) || 
		(nOfPrivates+nOfProtected+nOfPublic > 0)) {
		fprintf(_targetFile,"// Overrides\n");
		fprintf(_targetFile,"\t// ClassWizard generated virtual function overrides\n");
		fprintf(_targetFile,"\t//{{AFX_VIRTUAL(%s)\n",_className);
	} else {
		return;
	}
	if (nOfPublic > 0) {
		fprintf(_targetFile,"\tpublic:\n");
		TextContent *content = _classContent->getMethodContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->visibility() != PRIVATE_ID &&
				memberLine->visibility() != PROTECTED_ID &&
				memberLine->afxVirtualFlag() == TRUE) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\tvirtual ");
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
				fprintf(_targetFile,";\n");
			}
			aLine = content->getNext();
		}
	}
	if (nOfPrivates > 0 || nOfProtected > 0) {
		// afx virtual 함수는 무조건 private 가 없음
		fprintf(_targetFile,"\tprotected:\n");
		TextContent *content = _classContent->getMethodContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if ((memberLine->visibility() == PROTECTED_ID ||
				memberLine->visibility() == PRIVATE_ID) &&
				memberLine->afxVirtualFlag() == TRUE) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\tvirtual ");
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
				fprintf(_targetFile,";\n");
			}
			aLine = content->getNext();
		}
	}
	fprintf(_targetFile,"\t//}}AFX_VIRTUAL\n\n");
}

void VCPPCodeGenerator::printAfxMsgMemberFunctionSpecs()
{
	int nOfPrivates = 0;
	int nOfProtected = 0;
	int nOfPublic = 0;
	getAfxVirtualMemberFunctionCount(nOfPrivates,nOfProtected,nOfPublic);

	unsigned int employeedMap = _classContent->employeedMap();

	if ((employeedMap & KTG_MESSAGEMAP) || 
		(nOfPrivates+nOfProtected+nOfPublic > 0)) {
		fprintf(_targetFile,"// Generated message map functions\n");
		fprintf(_targetFile,"protected:\n");
		fprintf(_targetFile,"\t//{{AFX_MSG(%s)\n",_className);
	} else {
		return;
	}
	if (nOfPublic+nOfPrivates+nOfProtected > 0) {
		// afx message 함수는 무조건 protected로 간주함 
		TextContent *content = _classContent->getMethodContent();
		TextLine *aLine = content->getFirst();
		while (aLine != NIL) {
			if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
				break;
			}
			ClassTextLine *memberLine = (ClassTextLine *)aLine;
			if (memberLine->afxMsgFlag() == TRUE) {
				printComment(memberLine,"\t");
				fprintf(_targetFile,"\tafx_msg ");
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
				fprintf(_targetFile,";\n");
			}
			aLine = content->getNext();
		}
	}
	fprintf(_targetFile,"\t//}}AFX_MSG\n\n");
}

