// OOD.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "OOD.h"

#include "Frames.h"
#include "COODCommonFrm.h"
#include "Views.h"
#include "COODCommonView.h"
#include "Documents.h"

#include "CResizeEditViewBarDocTemp.h"
#include "CResizableEditView.h"
#include "CResizableEditDoc.h"
#include "UnsignedLong.h"
#include "Popups.h"
#include "CodeGenerators.h"
#include "ClassPropDlg.h"
#include "MemberPropDlg.h"
#include "PackagePropDlg.h"
#include "RelationTraverseDlg.h"
#include "builtInClasses.h"
#include "FixedNamesTable.h"
#include "TipDialog.h"
#include "CInPlaceFrame.h"

extern BOOL doesFileExist(const char* name);

UnsignedLong *IAMFIGURE;
UnsignedLong *IAMBOX;
UnsignedLong *IAMTEXT;
UnsignedLong *IAMLINE;
UnsignedLong *IAMLINES;
UnsignedLong *IAMCLASSTEMPLATE;
UnsignedLong *IAMCLASSTEXT;
UnsignedLong *IAMPACKAGETEXT;
UnsignedLong *IAMTRIANGLE;
UnsignedLong *IAMDIAMOND;
UnsignedLong *IAMROUNDBOXA;
UnsignedLong *IAMROUNDBOXB;
UnsignedLong *IAMSTATE;
UnsignedLong *IAMSTATETEXT;
UnsignedLong *IAMDEPENDENCY;
UnsignedLong *IAMPACKAGETEMPLATE;
UnsignedLong *IAMGENERALIZATION;
UnsignedLong *IAMAGGREGATION;
UnsignedLong *IAMCIRCLE;
UnsignedLong *IAMINITIALSTATE;
UnsignedLong *IAMFINALSTATE;
UnsignedLong *IAMTRANSITION;
UnsignedLong *IAMACTIVITY;
UnsignedLong *IAMBEGINACTIVITY;
UnsignedLong *IAMENDACTIVITY;
UnsignedLong *IAMSYNCHRONIZATIONBAR;
UnsignedLong *IAMACTIVITYTEXT;
UnsignedLong *IAMTRIGGER;
UnsignedLong *IAMACTOR;
UnsignedLong *IAMACTORNAMETEXT;
UnsignedLong *IAMUSECASE;
UnsignedLong *IAMUSECASETEXT;
UnsignedLong *IAMCOLLABORATIONOBJECT;
UnsignedLong *IAMOBJECTTEXT;
UnsignedLong *IAMMESSAGEFLOW;
UnsignedLong *IAMUSECASEUSESLINK;
UnsignedLong *IAMUSECASELINK;
UnsignedLong *IAMUSECASEEXTENDSLINK;
UnsignedLong *IAMSTATICCONNECTIONTEXT;
UnsignedLong *IAMSYSTEMBOUNDARY;
UnsignedLong *IAMMESSAGETEXT;
UnsignedLong *IAMCOLOBJMESSAGETEXT;
UnsignedLong *IAMEVENTTEXT;
UnsignedLong *IAMTRIGGERTEXT;
UnsignedLong *IAMSYNCCONDITIONTEXT;
UnsignedLong *IAMHARDWARENODE;
UnsignedLong *IAMCOMPONENTTEXT;
UnsignedLong *IAMCOMPONENTTEMPLATE;
UnsignedLong *IAMHWCONNECTION;
UnsignedLong *IAMHWCONNECTIONTEXT;
UnsignedLong *IAMCOMMUNICATION;
UnsignedLong *IAMASSOCIATION;
UnsignedLong *IAMSEQUENCEOBJECT;
UnsignedLong *IAMACTIVATIONBAR;
UnsignedLong *IAMSYNCMESSAGE;
UnsignedLong *IAMSEQUENCEMESSAGETEXT;
UnsignedLong *IAMASYNCMESSAGE;
UnsignedLong *IAMRETURNMESSAGE;
UnsignedLong *IAMSEQUENCESELFDELEGATION;
UnsignedLong *IAMONELINETEXT;
UnsignedLong *IAMTEMPLATECLASSTAGTEXT;
UnsignedLong *IAMCONNECTIONTEXT;
UnsignedLong *IAMQUALIFICATIONTEXT;
UnsignedLong *IAMINTERFACEPORTTEXT;
UnsignedLong *IAMBUCKET;
UnsignedLong *IAMNOTE;
UnsignedLong *IAMNOTETEXT;
UnsignedLong *IAMANCHOR;
UnsignedLong *IAMWIDESTATE;
UnsignedLong *IAMWIDEPACKAGE;

UnsignedLong *WEARENODEOBJECTS;
UnsignedLong *WEAREEDITABLEOBJECTS;
UnsignedLong *WEARELINES;
UnsignedLong *WEARETEXTOBJECTS;
UnsignedLong *WEARECONNECTIONS;
UnsignedLong *WEARESIMPLECONNECTIONS;
UnsignedLong *WEARECLASSOBJECTS;
UnsignedLong *WEARESTATEOBJECTS;
UnsignedLong *WEAREACTIVITYOBJECTS;
UnsignedLong *WEAREUSECASEOBJECTS;
UnsignedLong *WEARECOLLABORATIONOBJECTS;
UnsignedLong *WEAREWIDEOBJECTS;
UnsignedLong *WEAREDEPLOYMENTOBJECTS;
UnsignedLong *WEAREFORKABLELINES;
UnsignedLong *WEARESEQUENCEOBJECTS;
UnsignedLong *WEAREONELINETEXTS;
UnsignedLong *WEARECLIPBOARDOBJECTS;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COODApp

BEGIN_MESSAGE_MAP(COODApp, CWinApp)
	//{{AFX_MSG_MAP(COODApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TIP_OF_THE_DAY, OnTipOfTheDay)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_WS1, ID_FILE_MRU_WS16, OnOpenRecentWorkspace)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODApp construction

void COODApp::deleteDocTemplates()
{
	if (pCOODClassDoc != NIL) {
		delete pCOODClassDoc; pCOODClassDoc = NIL; 
	}
	if (_resizableEditViewBarDocTemplate != NIL) {
		delete _resizableEditViewBarDocTemplate; _resizableEditViewBarDocTemplate = NIL;
	}
	/*
	if (pClassDocTemplate != NIL) {
		delete pClassDocTemplate; pClassDocTemplate = NIL;
	}
	if (pObjectDocTemplate != NIL) {
		delete pObjectDocTemplate; pObjectDocTemplate = NIL;
	}
	if (pStateDocTemplate != NIL) {
		delete pStateDocTemplate; pStateDocTemplate = NIL;
	}
	if (pUseCaseDocTemplate != NIL) {
		delete pUseCaseDocTemplate; pUseCaseDocTemplate = NIL;
	}
	if (pCollaborationDocTemplate != NIL) {
		delete pCollaborationDocTemplate; pCollaborationDocTemplate = NIL;
	}
	if (pSequenceDocTemplate != NIL) {
		delete pSequenceDocTemplate; pSequenceDocTemplate = NIL;
	}
	if (pActivityDocTemplate != NIL) {
		delete pActivityDocTemplate; pActivityDocTemplate = NIL;
	}
	if (pDeploymentDocTemplate != NIL) {
		delete pDeploymentDocTemplate; pDeploymentDocTemplate = NIL;
	}
	*/
}

COODApp::~COODApp()
{
	cppHeaderFileAbsMacros.RemoveAll();
	cppSourceFileAbsMacros.RemoveAll();
	vcppHeaderFileAbsMacros.RemoveAll();
	vcppSourceFileAbsMacros.RemoveAll();

	delete IAMFIGURE;
	delete IAMBOX;
	delete IAMTEXT;
	delete IAMLINE;
	delete IAMLINES;
	delete IAMCLASSTEMPLATE;
	delete IAMCLASSTEXT;
	delete IAMPACKAGETEXT;
	delete IAMTRIANGLE;
	delete IAMDIAMOND;
	delete IAMROUNDBOXA;
	delete IAMROUNDBOXB;
	delete IAMSTATE;
	delete IAMSTATETEXT;
	delete IAMDEPENDENCY;
	delete IAMPACKAGETEMPLATE;
	delete IAMGENERALIZATION;
	delete IAMAGGREGATION;
	delete IAMCIRCLE;
	delete IAMINITIALSTATE;
	delete IAMFINALSTATE;
	delete IAMTRANSITION;
	delete IAMACTIVITY;
	delete IAMBEGINACTIVITY;
	delete IAMENDACTIVITY;
	delete IAMSYNCHRONIZATIONBAR;
	delete IAMACTIVITYTEXT;
	delete IAMTRIGGER;
	delete IAMACTOR;
	delete IAMACTORNAMETEXT;
	delete IAMUSECASE;
	delete IAMUSECASETEXT;
	delete IAMCOLLABORATIONOBJECT;
	delete IAMOBJECTTEXT;
	delete IAMMESSAGEFLOW;
	delete IAMUSECASEUSESLINK;
	delete IAMUSECASELINK;
	delete IAMUSECASEEXTENDSLINK;
	delete IAMSTATICCONNECTIONTEXT;
	delete IAMSYSTEMBOUNDARY;
	delete IAMMESSAGETEXT;
	delete IAMCOLOBJMESSAGETEXT;
	delete IAMEVENTTEXT;
	delete IAMTRIGGERTEXT;
	delete IAMSYNCCONDITIONTEXT;
	delete IAMHARDWARENODE;
	delete IAMCOMPONENTTEXT;
	delete IAMCOMPONENTTEMPLATE;
	delete IAMHWCONNECTION;
	delete IAMHWCONNECTIONTEXT;
	delete IAMCOMMUNICATION;
	delete IAMASSOCIATION;
	delete IAMSEQUENCEOBJECT;
	delete IAMACTIVATIONBAR;
	delete IAMSYNCMESSAGE;
	delete IAMSEQUENCEMESSAGETEXT;
	delete IAMASYNCMESSAGE;
	delete IAMRETURNMESSAGE;
	delete IAMSEQUENCESELFDELEGATION;
	delete IAMONELINETEXT;
	delete IAMTEMPLATECLASSTAGTEXT;
	delete IAMCONNECTIONTEXT;
	delete IAMQUALIFICATIONTEXT;
	delete IAMINTERFACEPORTTEXT;
	delete IAMBUCKET;
	delete IAMNOTE;
	delete IAMNOTETEXT;
	delete IAMANCHOR;
	delete IAMWIDESTATE;
	delete IAMWIDEPACKAGE;

	delete WEARENODEOBJECTS;
	delete WEAREEDITABLEOBJECTS;
	delete WEARELINES;
	delete WEARETEXTOBJECTS;
	delete WEARECONNECTIONS;
	delete WEARESIMPLECONNECTIONS;
	delete WEARECLASSOBJECTS;
	delete WEARESTATEOBJECTS;
	delete WEAREACTIVITYOBJECTS;
	delete WEAREUSECASEOBJECTS;
	delete WEARECOLLABORATIONOBJECTS;
	delete WEAREWIDEOBJECTS;
	delete WEAREDEPLOYMENTOBJECTS;
	delete WEAREFORKABLELINES;
	delete WEARESEQUENCEOBJECTS;
	delete WEAREONELINETEXTS;
	delete WEARECLIPBOARDOBJECTS;

	delete theCPPCodeGenerator;
	delete theVCPPCodeGenerator;
	delete theCSharpCodeGenerator;
	delete theJavaCodeGenerator;
	
	delete theCPPClassPropertyDlg;
	delete theVCPPClassPropertyDlg;
	delete theCSharpClassPropertyDlg;
	delete theJavaClassPropertyDlg;

	delete theCPPMethodPropertyDlg;
	delete theVCPPMethodPropertyDlg;
	delete theCSharpMethodPropertyDlg;
	delete theJavaMethodPropertyDlg;

	delete theCPPVarPropertyDlg;
	delete theVCPPVarPropertyDlg;
	delete theCSharpVarPropertyDlg;
	delete theJavaVarPropertyDlg;

	delete thePackagePropDlg;
	delete theRelationTraverseDlg;

	delete theActivityMainPopup;
	delete theClassMainPopup;
	delete theDeploymentMainPopup;
	delete theCollaborationMainPopup;
	delete theSequenceMainPopup;
	delete theStateMainPopup;
	delete theUseCaseMainPopup;
	delete theClassTemplatePopup;
	delete theGeneralizationPopup;
	delete theAggregationPopup;
	delete theDependencyPopup;
	delete theAssociationPopup;
	delete theMessageFlowPopup;
	delete theMessageTextPopup;
	delete theCollaborationObjectPopup;
	delete theSequenceObjectPopup;
	delete theSequenceLanePopup;
	delete theStatePopup;
	delete theTransitionPopup;
	delete theTriggerPopup;
	delete theHWConnectionPopup;
	delete theMessagePopup;
	delete theSynchronizationPopup;
	delete theEditPopup;
	delete theActivationBarPopup;
	delete theInterfacePortPopup;
	delete thePackagePopup;
	delete theLinePopup;

	delete cppBIClassNames;
	delete vcppBIClassNames;
	delete csharpBIClassNames;
	delete javaBIClassNames;

	if (COODView::PlainPen != NIL) {
		delete COODView::PlainPen; COODView::PlainPen = NIL;
	}
	if (COODView::RubberbandPen != NIL) {
		delete COODView::RubberbandPen; COODView::RubberbandPen = NIL;
	}
	if (COODView::HighlightPen != NIL) {
		delete COODView::HighlightPen; COODView::HighlightPen = NIL;
	}
	if (COODView::ErasePen != NIL) {
		delete COODView::ErasePen; COODView::ErasePen = NIL;
	}

	if (COODView::PlainBrush != NIL) {
		delete COODView::PlainBrush; COODView::PlainBrush = NIL;
	}
	if (COODView::RubberbandBrush != NIL) {
		delete COODView::RubberbandBrush; COODView::RubberbandBrush = NIL;
	}
	if (COODView::HighlightBrush != NIL) {
		delete COODView::HighlightBrush; COODView::HighlightBrush = NIL;
	}
	if (COODView::EraseBrush != NIL) {
		delete COODView::EraseBrush; COODView::EraseBrush = NIL;
	}
	if (COODView::ShapeEraseBrush != NIL) {
		delete COODView::ShapeEraseBrush; COODView::ShapeEraseBrush = NIL;
	}
	deleteDocTemplates();
/*
	이거는 도큐먼트 템플리트 "리스트" 객체가 직접 죽인다.
	위에 템플리트들도 만약 리스트에 첨가하면 이거 빼라.
	if (pTextDocTemplate != NIL) {
		delete pTextDocTemplate; pTextDocTemplate = NIL;
	}
*/
}

void COODApp::initializeAbsMacros()
{
	vcppHeaderFileAbsMacros.AddTail("#if _MSC_VER >= 1000");
	vcppHeaderFileAbsMacros.AddTail("#pragma once");
	vcppHeaderFileAbsMacros.AddTail("#endif // _MSC_VER >= 1000");

	vcppSourceFileAbsMacros.AddTail("#ifdef _DEBUG");
	vcppSourceFileAbsMacros.AddTail("#define new DEBUG_NEW");
	vcppSourceFileAbsMacros.AddTail("#undef THIS_FILE");
	vcppSourceFileAbsMacros.AddTail("static char THIS_FILE[] = __FILE__;");
	vcppSourceFileAbsMacros.AddTail("#endif");
}

ClassPropDlg* COODApp::getActiveClassPropDlg()
{
	if (projectLanguage.CompareNoCase("Visual C++") == 0) {
		if ((theCPPClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPClassPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpClassPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaClassPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theVCPPClassPropertyDlg;
	} else if (projectLanguage.CompareNoCase("Generic C++") == 0) {
		if ((theVCPPClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPClassPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpClassPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaClassPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theCPPClassPropertyDlg;
	} else if (projectLanguage.CompareNoCase("C#") == 0) {
		if ((theCPPClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPClassPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theVCPPClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPClassPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaClassPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theCSharpClassPropertyDlg;
	} else if (projectLanguage.CompareNoCase("Java") == 0) {
		if ((theCPPClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPClassPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theVCPPClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPClassPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpClassPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theJavaClassPropertyDlg;
	}
	return NIL;
}

CStringList &COODApp::getHeaderFileAbsMacros(CString &language)
{
	if (language.CompareNoCase("Visual C++") == 0) {
		return vcppHeaderFileAbsMacros;
	} else {
		return cppHeaderFileAbsMacros;
	}
}

CStringList &COODApp::getSourceFileAbsMacros(CString &language)
{
	if (language.CompareNoCase("Visual C++") == 0) {
		return vcppSourceFileAbsMacros;
	} else {
		return cppSourceFileAbsMacros;
	}
}

MemberPropDlg* COODApp::getActiveMethodPropDlg()
{
	if (projectLanguage.CompareNoCase("Visual C++") == 0) {
		if ((theCPPMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPMethodPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpMethodPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaMethodPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theVCPPMethodPropertyDlg;
	} else if (projectLanguage.CompareNoCase("Generic C++") == 0) {
		if ((theVCPPMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPMethodPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpMethodPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaMethodPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theCPPMethodPropertyDlg;
	} else if (projectLanguage.CompareNoCase("C#") == 0) {
		if ((theCPPMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPMethodPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theVCPPMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPMethodPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaMethodPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theCSharpMethodPropertyDlg;
	} else if (projectLanguage.CompareNoCase("Java") == 0) {
		if ((theCPPMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPMethodPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theVCPPMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPMethodPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpMethodPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theJavaMethodPropertyDlg;
	}
	return NIL;
}

void COODApp::deactivateClassPropertyDlgs()
{
	if ((theCPPClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theCPPClassPropertyDlg->deactivate();
	} 
	if ((theVCPPClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theVCPPClassPropertyDlg->deactivate();
	} 
	if ((theCSharpClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theCSharpClassPropertyDlg->deactivate();
	} 
	if ((theJavaClassPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theJavaClassPropertyDlg->deactivate();
	} 
}

void COODApp::deactivateAllPropertyDlgs()
{
	deactivateMemberPropertyDlgs();
	deactivateClassPropertyDlgs();
}

void COODApp::deactivateMemberPropertyDlgs()
{
	if ((theCPPMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theCPPMethodPropertyDlg->deactivate();
	} 
	if ((theVCPPMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theVCPPMethodPropertyDlg->deactivate();
	} 
	if ((theCSharpMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theCSharpMethodPropertyDlg->deactivate();
	} 
	if ((theJavaMethodPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theJavaMethodPropertyDlg->deactivate();
	} 

	if ((theCPPVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theCPPVarPropertyDlg->deactivate();
	} 
	if ((theVCPPVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theVCPPVarPropertyDlg->deactivate();
	} 
	if ((theCSharpVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theCSharpVarPropertyDlg->deactivate();
	}
	if ((theJavaVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
		theJavaVarPropertyDlg->deactivate();
	}
}

MemberPropDlg* COODApp::getActiveVarPropDlg()
{
	if (projectLanguage.CompareNoCase("Visual C++") == 0) {
		if ((theCPPVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPVarPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpVarPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaVarPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theVCPPVarPropertyDlg;
	} else if (projectLanguage.CompareNoCase("Generic C++") == 0) {
		if ((theVCPPVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPVarPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpVarPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaVarPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theCPPVarPropertyDlg;
	} else if (projectLanguage.CompareNoCase("C#") == 0) {
		if ((theCPPVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPVarPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theVCPPVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPVarPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theJavaVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theJavaVarPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theCSharpVarPropertyDlg;
	} else if (projectLanguage.CompareNoCase("Java") == 0) {
		if ((theCPPVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCPPVarPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theVCPPVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theVCPPVarPropertyDlg->ShowWindow(SW_HIDE);
		} else if ((theCSharpVarPropertyDlg->GetStyle() & WS_VISIBLE) != 0) {
			theCSharpVarPropertyDlg->ShowWindow(SW_HIDE);
		}
		return theJavaVarPropertyDlg;
	}
	return NIL;
}

CodeGenerator* COODApp::getActiveCodeGenerator()
{
	if (projectLanguage.CompareNoCase("Visual C++") == 0) {
		return theVCPPCodeGenerator;
	} else if (projectLanguage.CompareNoCase("Generic C++") == 0) {
		return theCPPCodeGenerator;
	} else if (projectLanguage.CompareNoCase("C#") == 0) {
		return theCSharpCodeGenerator;
	} else if (projectLanguage.CompareNoCase("Java") == 0) {
		return theJavaCodeGenerator;
	}
	return NIL;
}


/* 이 함수는 CNewWSDlg에서만 사용되어야 함 */
void COODApp::setFileExtension()
{
	if (projectLanguage.CompareNoCase("Java") == 0) {
		projectSFExtension = _T(".java");
	} else {
		projectHFExtension = _T(".h");
		projectSFExtension = _T(".cpp");
	}
}

void COODApp::removeFileAndBackingUp(CString &fileName)
{ 
	CString backUpName = workspaceDir + "\\backup\\";
	CString nameOnly = fileName;
	while(TRUE) {
		int i = nameOnly.Find('\\');
		if (i <= -1) break;
		nameOnly = nameOnly.Right(nameOnly.GetLength()-i-1);
	}
	backUpName = backUpName + nameOnly;

	TRY
	{
		if (doesFileExist(backUpName)) CFile::Remove(backUpName);
		if (doesFileExist(fileName)) CFile::Rename(fileName,backUpName);
	}
	CATCH( CFileException, e )
	{
		ErrorMsg("Can't remove file.");
	}
	END_CATCH		
}

COODApp::COODApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	versionNo = _T("0401");
	fileVersionNo = "";
	pCOODClassDoc = NIL;
	_selectedServerDiagram = "Class Diagram";
	runAsServerFlag = FALSE;
	classDelYesAlwaysFlag = FALSE;
	classDelNoAlwaysFlag = FALSE;

	_pOutputTextDoc = NULL;
	pClassDocTemplate = NULL; 
	pObjectDocTemplate = NULL; 
	pStateDocTemplate = NULL; 
	pTextDocTemplate = NULL;
	pUseCaseDocTemplate = NULL;
	pCollaborationDocTemplate = NULL;
	pSequenceDocTemplate = NULL;
	pActivityDocTemplate = NULL;
	pDeploymentDocTemplate = NULL;

	theCPPCodeGenerator = NIL;
	theVCPPCodeGenerator = NIL;
	theCSharpCodeGenerator = NIL;
	theJavaCodeGenerator = NIL;

	workspaceName = _T("");
	workspaceDir = _T("");
	projectLanguage = _T("Generic C++");
	projectHFExtension = _T(".h");
	projectSFExtension = _T(".cpp");
	projectInheritanceTreeOrient = _T("Horizontal");
	projectDrawInheritanceTreeFlag = TRUE;
	projectCodegenTargetDir = _T("");
	projectReverseSourceDir = _T("");
	projectAuthor = _T("");
	projectOrganization = _T("");

	cppHeaderFileAbsMacros.RemoveAll();
	cppSourceFileAbsMacros.RemoveAll();

	vcppHeaderFileAbsMacros.RemoveAll();
	vcppSourceFileAbsMacros.RemoveAll();
	initializeAbsMacros();

	constructFixedNameTables();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COODApp object

COODApp theApp;
// {01167588-C585-4E6E-B93A-A2100BF04560}
static const CLSID clsid =
{ 0x1167588, 0xc585, 0x4e6e, { 0xb9, 0x3a, 0xa2, 0x10, 0xb, 0xf0, 0x45, 0x60 } };

/*
// {3241A0A0-64CE-11d5-A72B-0050DA2D4248}
static const CLSID clsid =
{ 0x3241a0a0, 0x64ce, 0x11d5, { 0xa7, 0x2b, 0x0, 0x50, 0xda, 0x2d, 0x42, 0x48 } };
*/

/////////////////////////////////////////////////////////////////////////////
// COODApp initialization

FixedNamesTable *COODApp::getBuiltInClassTable()
{
	if (projectLanguage.CompareNoCase("Visual C++") == 0) {
		return vcppBIClassNames;
	} else if (projectLanguage.CompareNoCase("Java") == 0) {
		return javaBIClassNames;
	} else if (projectLanguage.CompareNoCase("C#") == 0) {
		return csharpBIClassNames;
	} else {
		return cppBIClassNames;
	}
}

void COODApp::constructFixedNameTables()
{
	cppBIClassNames = new FixedNamesTable(NTABLE(cppBuiltInClassNames),cppBuiltInClassNames);
	vcppBIClassNames = new FixedNamesTable(NTABLE(vcppBuiltInClassNames),vcppBuiltInClassNames);
	csharpBIClassNames = new FixedNamesTable(NTABLE(csharpBuiltInClassNames),csharpBuiltInClassNames);
	javaBIClassNames = new FixedNamesTable(NTABLE(javaBuiltInClassNames),javaBuiltInClassNames);
}

void COODApp::initializeCurrentFontInfo()
{
	currentFontSize = 17;
	currentFontWeight = FW_NORMAL;
	currentFontColor = 0x00000000;
	currentFontFaceName = DEFAULT_FACE_NAME;
	currentFontStyleName = "";
	currentFontBoldFlag = FALSE;
	currentFontItalicFlag = FALSE;
	currentFontStrikeOutFlag = FALSE;
	currentFontUnderlineFlag = FALSE;
}

void COODApp::initializeUnsignedLongVariables()
{
	IAMFIGURE = new UnsignedLong(KTG_FIGURE);
	IAMBOX = new UnsignedLong(KTG_BOX);
	IAMTEXT = new UnsignedLong(KTG_TEXT);
	IAMLINE = new UnsignedLong(KTG_LINE);
	IAMLINES = new UnsignedLong(KTG_LINES);
	IAMCLASSTEMPLATE = new UnsignedLong(KTG_CLASSTEMPLATE);
	IAMCLASSTEXT = new UnsignedLong(KTG_CLASSTEXT);
	IAMPACKAGETEXT = new UnsignedLong(KTG_PACKAGETEXT);
	IAMTRIANGLE = new UnsignedLong(KTG_TRIANGLE);
	IAMDIAMOND = new UnsignedLong(KTG_DIAMOND);
	IAMROUNDBOXA = new UnsignedLong(KTG_ROUNDBOXA);
	IAMROUNDBOXB = new UnsignedLong(KTG_ROUNDBOXB);
	IAMSTATE = new UnsignedLong(KTG_STATE);
	IAMSTATETEXT = new UnsignedLong(KTG_STATETEXT);
	IAMDEPENDENCY = new UnsignedLong(KTG_DEPENDENCY);
	IAMPACKAGETEMPLATE = new UnsignedLong(KTG_PACKAGETEMPLATE);
	IAMGENERALIZATION = new UnsignedLong(KTG_GENERALIZATION);
	IAMAGGREGATION = new UnsignedLong(KTG_AGGREGATION);
	IAMCIRCLE = new UnsignedLong(KTG_CIRCLE);
	IAMINITIALSTATE = new UnsignedLong(KTG_INITIALSTATE);
	IAMFINALSTATE = new UnsignedLong(KTG_FINALSTATE);
	IAMTRANSITION = new UnsignedLong(KTG_TRANSITION);
	IAMACTIVITY = new UnsignedLong(KTG_ACTIVITY);
	IAMBEGINACTIVITY = new UnsignedLong(KTG_BEGINACTIVITY);
	IAMENDACTIVITY = new UnsignedLong(KTG_ENDACTIVITY);
	IAMSYNCHRONIZATIONBAR = new UnsignedLong(KTG_SYNCHRONIZATIONBAR);
	IAMACTIVITYTEXT = new UnsignedLong(KTG_ACTIVITYTEXT);
	IAMTRIGGER = new UnsignedLong(KTG_TRIGGER);
	IAMACTOR = new UnsignedLong(KTG_ACTOR);
	IAMACTORNAMETEXT = new UnsignedLong(KTG_ACTORNAMETEXT);
	IAMUSECASE = new UnsignedLong(KTG_USECASE);
	IAMUSECASETEXT = new UnsignedLong(KTG_USECASETEXT);
	IAMCOLLABORATIONOBJECT = new UnsignedLong(KTG_COLLABORATIONOBJECT);
	IAMOBJECTTEXT = new UnsignedLong(KTG_OBJECTTEXT);
	IAMMESSAGEFLOW = new UnsignedLong(KTG_MESSAGEFLOW);
	IAMUSECASELINK = new UnsignedLong(KTG_USECASELINK);
	IAMUSECASEUSESLINK = new UnsignedLong(KTG_USECASEUSESLINK);
	IAMUSECASEEXTENDSLINK = new UnsignedLong(KTG_USECASEEXTENDSLINK);
	IAMSTATICCONNECTIONTEXT = new UnsignedLong(KTG_STATICCONNECTIONTEXT);
	IAMSYSTEMBOUNDARY = new UnsignedLong(KTG_SYSTEMBOUNDARY);
	IAMMESSAGETEXT = new UnsignedLong(KTG_MESSAGETEXT);
	IAMCOLOBJMESSAGETEXT = new UnsignedLong(KTG_COLOBJMESSAGETEXT);
	IAMEVENTTEXT = new UnsignedLong(KTG_EVENTTEXT);
	IAMTRIGGERTEXT = new UnsignedLong(KTG_TRIGGERTEXT);
	IAMSYNCCONDITIONTEXT = new UnsignedLong(KTG_SYNCCONDITIONTEXT);
	IAMHARDWARENODE = new UnsignedLong(KTG_HARDWARENODE);
	IAMCOMPONENTTEXT = new UnsignedLong(KTG_COMPONENTTEXT);
	IAMCOMPONENTTEMPLATE = new UnsignedLong(KTG_COMPONENTTEMPLATE);
	IAMHWCONNECTION = new UnsignedLong(KTG_HWCONNECTION);
	IAMHWCONNECTIONTEXT = new UnsignedLong(KTG_HWCONNECTIONTEXT);
	IAMCOMMUNICATION = new UnsignedLong(KTG_COMMUNICATION);
	IAMASSOCIATION = new UnsignedLong(KTG_ASSOCIATION);
	IAMSEQUENCEOBJECT = new UnsignedLong(KTG_SEQUENCEOBJECT);
	IAMACTIVATIONBAR = new UnsignedLong(KTG_ACTIVATIONBAR);
	IAMSYNCMESSAGE = new UnsignedLong(KTG_SYNCMESSAGE);
	IAMSEQUENCEMESSAGETEXT = new UnsignedLong(KTG_SEQUENCEMESSAGETEXT);
	IAMASYNCMESSAGE = new UnsignedLong(KTG_ASYNCMESSAGE);
	IAMRETURNMESSAGE = new UnsignedLong(KTG_RETURNMESSAGE);
	IAMSEQUENCESELFDELEGATION = new UnsignedLong(KTG_SEQUENCESELFDELEGATION);
	IAMONELINETEXT = new UnsignedLong(KTG_ONELINETEXT);
	IAMTEMPLATECLASSTAGTEXT = new UnsignedLong(KTG_TEMPLATECLASSTAGTEXT);
	IAMCONNECTIONTEXT = new UnsignedLong(KTG_CONNECTIONTEXT);
	IAMQUALIFICATIONTEXT = new UnsignedLong(KTG_QUALIFICATIONTEXT);
	IAMINTERFACEPORTTEXT = new UnsignedLong(KTG_INTERFACEPORTTEXT);
	IAMBUCKET = new UnsignedLong(KTG_BUCKET);
	IAMNOTE = new UnsignedLong(KTG_NOTE);
	IAMNOTETEXT = new UnsignedLong(KTG_NOTETEXT);
	IAMANCHOR = new UnsignedLong(KTG_ANCHOR);
	IAMWIDESTATE = new UnsignedLong(KTG_WIDESTATE);
	IAMWIDEPACKAGE = new UnsignedLong(KTG_WIDEPACKAGE);

	WEAREWIDEOBJECTS = (new UnsignedLong(KTG_SYSTEMBOUNDARY))
						->oring(IAMHARDWARENODE)
						->oring(IAMWIDESTATE)
						->oring(IAMWIDEPACKAGE);

	WEARECLASSOBJECTS = (new UnsignedLong(KTG_CLASSTEMPLATE))
							->oring(IAMPACKAGETEMPLATE)
							->oring(IAMWIDEPACKAGE);

	WEARESTATEOBJECTS = (new UnsignedLong(KTG_STATE))
							->oring(IAMWIDESTATE)
							->oring(IAMINITIALSTATE)
							->oring(IAMFINALSTATE);

	WEAREACTIVITYOBJECTS = (new UnsignedLong(KTG_ACTIVITY))
							->oring(IAMSYNCHRONIZATIONBAR)
							->oring(IAMBEGINACTIVITY)
							->oring(IAMENDACTIVITY);

	WEAREUSECASEOBJECTS	= (new UnsignedLong(KTG_ACTOR))
							->oring(IAMUSECASE);

	WEARECOLLABORATIONOBJECTS = new UnsignedLong(KTG_COLLABORATIONOBJECT);

	WEARESEQUENCEOBJECTS = new UnsignedLong(KTG_SEQUENCEOBJECT);

	WEAREDEPLOYMENTOBJECTS = (new UnsignedLong(KTG_HARDWARENODE))
								->oring(IAMCOMPONENTTEMPLATE);

	WEARENODEOBJECTS = (new UnsignedLong(KTG_SEQUENCEOBJECT))
						->oring(WEARECLASSOBJECTS)
						->oring(WEARESTATEOBJECTS)
						->oring(WEAREACTIVITYOBJECTS)
						->oring(WEAREUSECASEOBJECTS)
						->oring(WEARECOLLABORATIONOBJECTS)
						->oring(WEAREDEPLOYMENTOBJECTS)
						->oring(IAMNOTE)
						->oring(IAMSYSTEMBOUNDARY);

	WEAREEDITABLEOBJECTS = (new UnsignedLong(KTG_TEXT))
							->oring(WEARECLASSOBJECTS)
							->oring(IAMSTATE)
							->oring(IAMACTIVITY)
							->oring(IAMACTOR)
							->oring(IAMUSECASE)
							->oring(IAMCOLLABORATIONOBJECT)
							->oring(IAMSYSTEMBOUNDARY)
							->oring(IAMSYNCHRONIZATIONBAR)
							->oring(IAMHARDWARENODE)
							->oring(IAMCOMPONENTTEMPLATE)
							->oring(IAMSEQUENCEOBJECT)
							->oring(IAMNOTE)
							->oring(IAMWIDESTATE)
							->oring(IAMWIDEPACKAGE);

	WEAREONELINETEXTS = new UnsignedLong(KTG_ONELINETEXT);

	WEARETEXTOBJECTS = (new UnsignedLong(KTG_TEXT))
						->oring(IAMCLASSTEXT)
						->oring(IAMPACKAGETEXT)
						->oring(IAMACTIVITYTEXT)
						->oring(IAMSTATETEXT)
						->oring(IAMACTORNAMETEXT)
						->oring(IAMUSECASETEXT)
						->oring(IAMOBJECTTEXT)
						->oring(IAMSTATICCONNECTIONTEXT)
						->oring(IAMMESSAGETEXT)
						->oring(IAMCOLOBJMESSAGETEXT)
						->oring(IAMEVENTTEXT)
						->oring(IAMTRIGGERTEXT)
						->oring(IAMCONNECTIONTEXT)
						->oring(IAMSYNCCONDITIONTEXT)
						->oring(IAMCOMPONENTTEXT)
						->oring(IAMHWCONNECTIONTEXT)
						->oring(IAMSEQUENCEMESSAGETEXT)
						->oring(IAMTEMPLATECLASSTAGTEXT)
						->oring(IAMQUALIFICATIONTEXT)
						->oring(IAMINTERFACEPORTTEXT)
						->oring(WEAREONELINETEXTS)
						->oring(IAMNOTETEXT);

	WEARESIMPLECONNECTIONS = (new UnsignedLong(KTG_USECASELINK))
						->oring(IAMUSECASEUSESLINK)
						->oring(IAMUSECASEEXTENDSLINK)
						->oring(IAMSYNCMESSAGE)
						->oring(IAMASYNCMESSAGE)
						->oring(IAMRETURNMESSAGE);

	WEAREFORKABLELINES = (new UnsignedLong(KTG_DEPENDENCY))
						->oring(IAMAGGREGATION)
						->oring(IAMGENERALIZATION)
						->oring(IAMASSOCIATION)
						->oring(IAMTRIGGER);

	WEARECONNECTIONS = (new UnsignedLong(KTG_DEPENDENCY))
						->oring(WEARESIMPLECONNECTIONS)
						->oring(IAMAGGREGATION)
						->oring(IAMASSOCIATION)
						->oring(IAMGENERALIZATION)
						->oring(IAMTRANSITION)
						->oring(IAMTRIGGER)
						->oring(IAMMESSAGEFLOW)
						->oring(IAMHWCONNECTION)
						->oring(IAMCOMMUNICATION)
						->oring(IAMSEQUENCESELFDELEGATION);

	WEARELINES = (new UnsignedLong(KTG_LINE))
					->oring(IAMANCHOR)
					->oring(IAMLINES)
					->oring(WEARECONNECTIONS);

	WEARECLIPBOARDOBJECTS = (new UnsignedLong(KTG_ACTIVITY))
		                    ->oring(IAMBOX)                              // 2014 danger
		                    ->oring(IAMCIRCLE)                              // 2014 danger
		                    ->oring(IAMROUNDBOXA)                              // 2014 danger
							->oring(IAMACTOR)
							->oring(IAMBEGINACTIVITY)
							->oring(IAMCOLLABORATIONOBJECT)
							->oring(IAMCOMPONENTTEMPLATE)
							->oring(IAMENDACTIVITY)
							->oring(IAMFINALSTATE)
							->oring(IAMHARDWARENODE)
							->oring(IAMINITIALSTATE)
							->oring(IAMNOTE)
							->oring(IAMTEXT)
							->oring(IAMSTATE)
							->oring(IAMSYNCHRONIZATIONBAR)
							->oring(IAMSYSTEMBOUNDARY)
							->oring(IAMUSECASE)
							->oring(IAMWIDESTATE)
							->oring(IAMWIDEPACKAGE);
}

void COODApp::resizeMemberPropDlgsIfNeeded()
{
	theCPPMethodPropertyDlg->resizeIfNeededOnCreate();
	theVCPPMethodPropertyDlg->resizeIfNeededOnCreate();
	theCSharpMethodPropertyDlg->resizeIfNeededOnCreate();
	theJavaMethodPropertyDlg->resizeIfNeededOnCreate();

	theCPPVarPropertyDlg->resizeIfNeededOnCreate();
	theVCPPVarPropertyDlg->resizeIfNeededOnCreate();
	theCSharpVarPropertyDlg->resizeIfNeededOnCreate();
	theJavaVarPropertyDlg->resizeIfNeededOnCreate();
}

void COODApp::initializeMemberPropDlgs()
{
	theCPPClassPropertyDlg = new ClassPropDlg("C++",GetMainWnd());
	theVCPPClassPropertyDlg = new ClassPropDlg("Visual C++",GetMainWnd());
	theCSharpClassPropertyDlg = new ClassPropDlg("C#",GetMainWnd());
	theJavaClassPropertyDlg = new ClassPropDlg("Java",GetMainWnd());

	theCPPMethodPropertyDlg = new MemberPropDlg(MEMBER_FUNCTION,"C++",GetMainWnd());
	theVCPPMethodPropertyDlg = new MemberPropDlg(MEMBER_FUNCTION,"Visual C++",GetMainWnd());
	theCSharpMethodPropertyDlg = new MemberPropDlg(MEMBER_FUNCTION,"C#",GetMainWnd());
	theJavaMethodPropertyDlg = new MemberPropDlg(MEMBER_FUNCTION,"Java",GetMainWnd());

	theCPPVarPropertyDlg = new MemberPropDlg(DATA_MEMBER,"C++",GetMainWnd());
	theVCPPVarPropertyDlg = new MemberPropDlg(DATA_MEMBER,"Visual C++",GetMainWnd());
	theCSharpVarPropertyDlg = new MemberPropDlg(DATA_MEMBER,"C#",GetMainWnd());
	theJavaVarPropertyDlg = new MemberPropDlg(DATA_MEMBER,"Java",GetMainWnd());

	thePackagePropDlg = new PackagePropDlg(GetMainWnd());

	theRelationTraverseDlg = new RelationTraverseDlg(GetMainWnd());

	theCPPClassPropertyDlg->Create(IDD_CLASS_PROP_DLG);
	theVCPPClassPropertyDlg->Create(IDD_CLASS_PROP_DLG);
	theCSharpClassPropertyDlg->Create(IDD_CLASS_PROP_DLG);
	theJavaClassPropertyDlg->Create(IDD_CLASS_PROP_DLG);

	theCPPMethodPropertyDlg->Create(IDD_MEMBER_PROP_DLG);
	theVCPPMethodPropertyDlg->Create(IDD_MEMBER_PROP_DLG);
	theCSharpMethodPropertyDlg->Create(IDD_MEMBER_PROP_DLG);
	theJavaMethodPropertyDlg->Create(IDD_MEMBER_PROP_DLG);

	theCPPVarPropertyDlg->Create(IDD_MEMBER_PROP_DLG);
	theVCPPVarPropertyDlg->Create(IDD_MEMBER_PROP_DLG);
	theCSharpVarPropertyDlg->Create(IDD_MEMBER_PROP_DLG);
	theJavaVarPropertyDlg->Create(IDD_MEMBER_PROP_DLG);

	thePackagePropDlg->Create(IDD_PACKAGE_PROP_DLG);

	theRelationTraverseDlg->Create(IDD_RELATION_TRAVERSE_DLG);

	theCPPClassPropertyDlg->CenterWindow();
	theVCPPClassPropertyDlg->CenterWindow();
	theCSharpClassPropertyDlg->CenterWindow();
	theJavaClassPropertyDlg->CenterWindow();

	theCPPMethodPropertyDlg->CenterWindow();
	theVCPPMethodPropertyDlg->CenterWindow();
	theCSharpMethodPropertyDlg->CenterWindow();
	theJavaMethodPropertyDlg->CenterWindow();

	theCPPVarPropertyDlg->CenterWindow();
	theVCPPVarPropertyDlg->CenterWindow();
	theCSharpVarPropertyDlg->CenterWindow();
	theJavaVarPropertyDlg->CenterWindow();

	thePackagePropDlg->CenterWindow();

	theRelationTraverseDlg->CenterWindow();
}

void COODApp::initializeCodeGenerators()
{
	theCPPCodeGenerator = new CPPCodeGenerator();
	theVCPPCodeGenerator = new VCPPCodeGenerator();
	theJavaCodeGenerator = new JavaCodeGenerator();
	theCSharpCodeGenerator = new CSharpCodeGenerator();
}

void COODApp::initializePopups()
{
	theActivityMainPopup = new ActivityMainPopup();
	theClassMainPopup = new ClassMainPopup();
	theDeploymentMainPopup = new DeploymentMainPopup();
	theCollaborationMainPopup = new CollaborationMainPopup();
	theSequenceMainPopup = new SequenceMainPopup();
	theStateMainPopup = new StateMainPopup();
	theUseCaseMainPopup = new UseCaseMainPopup();
	theClassTemplatePopup = new ClassTemplatePopup();
	theGeneralizationPopup = new GeneralizationPopup();
	theAggregationPopup = new AggregationPopup();
	theDependencyPopup = new DependencyPopup();
	theAssociationPopup = new AssociationPopup();
	theMessageFlowPopup = new MessageFlowPopup();
	theMessageTextPopup = new MessageTextPopup();
	theCollaborationObjectPopup = new CollaborationObjectPopup();
	theSequenceObjectPopup = new SequenceObjectPopup();
	theSequenceLanePopup = new SequenceLanePopup();
	theStatePopup = new StatePopup();
	theTransitionPopup = new ConnectionPopup("Event");
	theTriggerPopup = new ConnectionPopup("Guard");
	theHWConnectionPopup = new ConnectionPopup("Protocol");
	theMessagePopup = new ConnectionPopup("Message");
	theSynchronizationPopup = new SynchronizationPopup();
	theEditPopup = new EditPopup();
	theActivationBarPopup = new ActivationBarPopup();
	theInterfacePortPopup = new InterfacePortPopup();
	thePackagePopup = new PackagePopup();
	theLinePopup = new LinePopup();
}

void COODApp::initializeGraphicObjects()
{
	COODView::PlainPen = new CPen(PS_SOLID,1,RGB(0,0,0));
	COODView::RubberbandPen = new CPen(PS_SOLID,1,RGB(0,0,0));
	COODView::HighlightPen = new CPen(PS_SOLID,1,RGB(255,0,0));
	COODView::ErasePen = new CPen(PS_SOLID,1,RGB(255,255,255));

	COODView::PlainBrush = new CBrush(RGB(0,0,0));
	COODView::RubberbandBrush = new CBrush(RGB(0,0,0));
	COODView::HighlightBrush = new CBrush(RGB(255,0,0));
	COODView::EraseBrush = new CBrush(RGB(255,255,255));
	COODView::ShapeEraseBrush = new CBrush(RGB(255,255,255));
}

void COODApp::openRecentWorkspace()
{
	ASSERT_VALID(this);
	if (m_pRecentFileList == NULL) return;
	
	if ((UINT)m_pRecentFileList->GetSize() == 0) return;
	if ((*m_pRecentFileList)[0].GetLength() == 0) return;

	if (doesFileExist((*m_pRecentFileList)[0]) == FALSE) {
		return;
	}

	TRACE2("MRU: open file (%d) '%s'.\n", (0) + 1,
			(LPCTSTR)(*m_pRecentFileList)[0]);

	if (mainFramePtr->onFileOpenWorkspace((*m_pRecentFileList)[0]) == FALSE)
		m_pRecentFileList->Remove(0);
}

void COODApp::loadOODProfileSettings()
{
	showTipsFlag = GetProfileInt("OODesigner Values","showTipsAtStartup",TRUE);
	int width;
	int height;
	width = GetProfileInt("OODesigner Values","widthCPPMethodPropertyDlg",0);
	height = GetProfileInt("OODesigner Values","heightCPPMethodPropertyDlg",0);
	theCPPMethodPropertyDlg->setInitialWidth(width);
	theCPPMethodPropertyDlg->setInitialHeight(height);

	width = GetProfileInt("OODesigner Values","widthVCPPMethodPropertyDlg",0);
	height = GetProfileInt("OODesigner Values","heightVCPPMethodPropertyDlg",0);
	theVCPPMethodPropertyDlg->setInitialWidth(width);
	theVCPPMethodPropertyDlg->setInitialHeight(height);

	width = GetProfileInt("OODesigner Values","widthCSharpMethodPropertyDlg",0);
	height = GetProfileInt("OODesigner Values","heightCSharpMethodPropertyDlg",0);
	theCSharpMethodPropertyDlg->setInitialWidth(width);
	theCSharpMethodPropertyDlg->setInitialHeight(height);

	width = GetProfileInt("OODesigner Values","widthJavaMethodPropertyDlg",0);
	height = GetProfileInt("OODesigner Values","heightJavaMethodPropertyDlg",0);
	theJavaMethodPropertyDlg->setInitialWidth(width);
	theJavaMethodPropertyDlg->setInitialHeight(height);

	width = GetProfileInt("OODesigner Values","widthCPPVarPropertyDlg",0);
	height = GetProfileInt("OODesigner Values","heightCPPVarPropertyDlg",0);
	theCPPVarPropertyDlg->setInitialWidth(width);
	theCPPVarPropertyDlg->setInitialHeight(height);

	width = GetProfileInt("OODesigner Values","widthVCPPVarPropertyDlg",0);
	height = GetProfileInt("OODesigner Values","heightVCPPVarPropertyDlg",0);
	theVCPPVarPropertyDlg->setInitialWidth(width);
	theVCPPVarPropertyDlg->setInitialHeight(height);

	width = GetProfileInt("OODesigner Values","widthCSharpVarPropertyDlg",0);
	height = GetProfileInt("OODesigner Values","heightCSharpVarPropertyDlg",0);
	theCSharpVarPropertyDlg->setInitialWidth(width);
	theCSharpVarPropertyDlg->setInitialHeight(height);

	width = GetProfileInt("OODesigner Values","widthJavaVarPropertyDlg",0);
	height = GetProfileInt("OODesigner Values","heightJavaVarPropertyDlg",0);
	theJavaVarPropertyDlg->setInitialWidth(width);
	theJavaVarPropertyDlg->setInitialHeight(height);
}

void COODApp::writeOODProfileSettings()
{
	WriteProfileInt("OODesigner Values","showTipsAtStartup",showTipsFlag);

	int width;
	int height;
	width = theCPPMethodPropertyDlg->getInitialWidth();
	height = theCPPMethodPropertyDlg->getInitialHeight();
	WriteProfileInt("OODesigner Values","widthCPPMethodPropertyDlg",width);
	WriteProfileInt("OODesigner Values","heightCPPMethodPropertyDlg",height);

	width = theVCPPMethodPropertyDlg->getInitialWidth();
	height = theVCPPMethodPropertyDlg->getInitialHeight();
	WriteProfileInt("OODesigner Values","widthVCPPMethodPropertyDlg",width);
	WriteProfileInt("OODesigner Values","heightVCPPMethodPropertyDlg",height);

	width = theCSharpMethodPropertyDlg->getInitialWidth();
	height = theCSharpMethodPropertyDlg->getInitialHeight();
	WriteProfileInt("OODesigner Values","widthCSharpMethodPropertyDlg",width);
	WriteProfileInt("OODesigner Values","heightCSharpMethodPropertyDlg",height);

	width = theJavaMethodPropertyDlg->getInitialWidth();
	height = theJavaMethodPropertyDlg->getInitialHeight();
	WriteProfileInt("OODesigner Values","widthJavaMethodPropertyDlg",width);
	WriteProfileInt("OODesigner Values","heightJavaMethodPropertyDlg",height);

	width = theCPPVarPropertyDlg->getInitialWidth();
	height = theCPPVarPropertyDlg->getInitialHeight();
	WriteProfileInt("OODesigner Values","widthCPPVarPropertyDlg",width);
	WriteProfileInt("OODesigner Values","heightCPPVarPropertyDlg",height);

	width = theVCPPVarPropertyDlg->getInitialWidth();
	height = theVCPPVarPropertyDlg->getInitialHeight();
	WriteProfileInt("OODesigner Values","widthVCPPVarPropertyDlg",width);
	WriteProfileInt("OODesigner Values","heightVCPPVarPropertyDlg",height);

	width = theCSharpVarPropertyDlg->getInitialWidth();
	height = theCSharpVarPropertyDlg->getInitialHeight();
	WriteProfileInt("OODesigner Values","widthCSharpVarPropertyDlg",width);
	WriteProfileInt("OODesigner Values","heightCSharpVarPropertyDlg",height);

	width = theJavaVarPropertyDlg->getInitialWidth();
	height = theJavaVarPropertyDlg->getInitialHeight();
	WriteProfileInt("OODesigner Values","widthJavaVarPropertyDlg",width);
	WriteProfileInt("OODesigner Values","heightJavaVarPropertyDlg",height);
}

BOOL COODApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	showTipsFlag = TRUE;
	setGridFlag = FALSE;
	paperColor = RGB(255,255,255);
	textColor = RGB(0,0,0);
	shapeForegroundColor = RGB(0,0,0);
	shapeBackgroundColor = RGB(255,255,255);
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
// 2014 OODesigner 수정 	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("OODesigner: The CASE Tool"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	pUseCaseDocTemplate = new CMultiDocTemplate(
		IDR_USECASEFRAME,
		RUNTIME_CLASS(COODCommonDoc),
		RUNTIME_CLASS(CUseCaseFrm), // custom MDI child frame
		RUNTIME_CLASS(CUseCaseView));
	pUseCaseDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	AddDocTemplate(pUseCaseDocTemplate);

	pSequenceDocTemplate = new CMultiDocTemplate(
		IDR_SEQUENCEFRAME,
		RUNTIME_CLASS(COODCommonDoc),
		RUNTIME_CLASS(CSequenceFrm), // custom MDI child frame
		RUNTIME_CLASS(CSequenceView));
	pSequenceDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	AddDocTemplate(pSequenceDocTemplate);

	pCollaborationDocTemplate = new CMultiDocTemplate(
		IDR_COLLABORATIONFRAME,
		RUNTIME_CLASS(COODCommonDoc),
		RUNTIME_CLASS(CCollaborationFrm), // custom MDI child frame
		RUNTIME_CLASS(CCollaborationView));
	pCollaborationDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	AddDocTemplate(pCollaborationDocTemplate);

	pStateDocTemplate = new CMultiDocTemplate(
		IDR_STATEFRAME,
		RUNTIME_CLASS(COODCommonDoc),
		RUNTIME_CLASS(CStateFrm), // custom MDI child frame
		RUNTIME_CLASS(CStateView));
	pStateDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	AddDocTemplate(pStateDocTemplate);

	pActivityDocTemplate = new CMultiDocTemplate(
		IDR_ACTIVITYFRAME,
		RUNTIME_CLASS(COODCommonDoc),
		RUNTIME_CLASS(CActivityFrm), // custom MDI child frame
		RUNTIME_CLASS(CActivityView));
	pActivityDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	AddDocTemplate(pActivityDocTemplate);

	pDeploymentDocTemplate = new CMultiDocTemplate(
		IDR_DEPLOYMENTFRAME,
		RUNTIME_CLASS(COODCommonDoc),
		RUNTIME_CLASS(CDeploymentFrm), // custom MDI child frame
		RUNTIME_CLASS(CDeploymentView));
	pDeploymentDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	AddDocTemplate(pDeploymentDocTemplate);

	pObjectDocTemplate = new CMultiDocTemplate(
		IDR_OBJECTFRAME,
		RUNTIME_CLASS(COODCommonDoc),
		RUNTIME_CLASS(CObjectFrm), // custom MDI child frame
		RUNTIME_CLASS(CObjectView));
	pObjectDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	AddDocTemplate(pObjectDocTemplate);

	pClassDocTemplate = new CMultiDocTemplate(
		IDR_CLASSFRAME,
		RUNTIME_CLASS(COODClassDoc),
		RUNTIME_CLASS(CClassFrm), // custom MDI child frame
		RUNTIME_CLASS(CClassView));
	pClassDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	AddDocTemplate(pClassDocTemplate);

	pTextDocTemplate = new CMultiDocTemplate(
		IDR_TEXTFRAME,
		RUNTIME_CLASS(CTextDoc),
		RUNTIME_CLASS(CTextFrm), // custom MDI child frame
		RUNTIME_CLASS(CTextView));
	// 다른 도큐먼트 템플리트는 절대로 add 하지 말것 ...
	// 시멕틱이 틀림 ... 마음을 바꿨음
	AddDocTemplate(pTextDocTemplate);

	// 이 아래 템플리트는 어프리케이션에서 절대로 사용되지 않음
	// 단지 서버용 공용 템플리트이다.
	CMultiDocTemplate *pServerDocTemplate = new CMultiDocTemplate(
		IDR_COMMONFRAME,
		RUNTIME_CLASS(COODCommonDoc),
		RUNTIME_CLASS(COODCommonFrm), // custom MDI child frame
		RUNTIME_CLASS(COODCommonView));
	pServerDocTemplate->SetContainerInfo(IDR_OOD_CNTR_IP);
	pServerDocTemplate->SetServerInfo(
		IDR_OOD_SRVR_EMB,IDR_OOD_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pServerDocTemplate);

	// Seed the random-number generator with current time 
	srand((unsigned)time(NULL));

	_resizableEditViewBarDocTemplate = new CResizableEditViewBarDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CResizableEditDoc),
		NULL,
		RUNTIME_CLASS(CResizableEditView));

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.

	// 단지 템플리트의 m_pAttachedFactory 필드에 m_server의 주소를 셋팅하는 의미만 있다.
	// 그리고 마지막 플랙은 매우 중요한데 ... 이게 투루면 OLE 서버 객체 하나당 app 하나씩 생성된다.
	// 그런데 이걸 투루로 놓으면 오엘이 링크시에 파일 공유 엑세스 에러가 발생한다.
	m_server.ConnectTemplate(clsid,pServerDocTemplate,FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	// 이 아래 문장은 도큐먼트 템플리트와 관계가 멀다.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(FALSE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CDocument *pDoc = _resizableEditViewBarDocTemplate->OpenDocumentFile(NULL);
	if (pDoc != NULL && pDoc->IsKindOf(RUNTIME_CLASS(CResizableEditDoc))) {
		_pOutputTextDoc = (CResizableEditDoc *)pDoc;
		_pOutputTextDoc->showControlFrame(FALSE);
		pDoc->SetTitle("Output");
		_pOutputTextDoc->pBar()->SetWindowText(pDoc->GetTitle());
	} else {
		TRACE0("Warning : Something goes wrong in COODApp::InitInstance");
	}

	initializeUnsignedLongVariables();
	initializePopups();
	initializeGraphicObjects();
	initializeCodeGenerators();
	initializeMemberPropDlgs();
	initializeCurrentFontInfo();

	loadOODProfileSettings();  // Load OODesigner INI file options

	resizeMemberPropDlgsIfNeeded();
	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		runAsServerFlag = TRUE;
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	// 이 아래 문장은 도큐먼트 템플리트와 관계가 매우 깊다.
	m_server.UpdateRegistry(OAT_INPLACE_SERVER);

	// 다음 문장은 처음 시작될 때 뷰가 생성되지 않도록하기 위해서 ...
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();
	if ((pMainFrame->m_wndTreeBar.GetStyle() & WS_VISIBLE) == 0) {
		pMainFrame->ShowControlBar(&pMainFrame->m_wndTreeBar,TRUE,FALSE);
	} 

	CString filePath = cmdInfo.m_strFileName;
	if (!filePath.IsEmpty()) {
		CString extension = filePath.Right(_EXT_LEN4); 
		if (extension.CompareNoCase(_OOD_EXT) != 0) {
			OpenDocumentFile(filePath);
		}
	}

//	openRecentWorkspace();
	if (showTipsFlag) {
		TipDialog tipDlg;
		tipDlg.DoModal();
	}
	return TRUE;
}

void COODApp::showOutputBar(BOOL bShow)
{
	_pOutputTextDoc->showControlFrame(bShow);
}

void COODApp::AddToRecentFileList(LPCTSTR lpszPathName)
{
	return;
}

void COODApp::addToWorkspaceList(LPCTSTR lpszPathName)
{
// 2014 OODesigner 수정 		CWinApp::AddToRecentFileList(lpszPathName);
}

BOOL COODApp::OnOpenRecentWorkspace(UINT nID)
{
	ASSERT_VALID(this);
	ASSERT(m_pRecentFileList != NULL);

	ASSERT(nID >= ID_FILE_MRU_WS1);
	ASSERT(nID < ID_FILE_MRU_WS1 + (UINT)m_pRecentFileList->GetSize());
	int nIndex = nID - ID_FILE_MRU_WS1;
	ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);

	TRACE2("MRU: open file (%d) '%s'.\n", (nIndex) + 1,
			(LPCTSTR)(*m_pRecentFileList)[nIndex]);

	if (workspaceName.GetLength() != 0) {
		CString currentFullName = workspaceDir + "\\" + workspaceName + _OOD_EXT;
		if (currentFullName.CompareNoCase((*m_pRecentFileList)[nIndex]) == 0) {
			WarningMsg("The workspace is already opened.");
			return TRUE;
		}
		BOOL canceled = mainFramePtr->onWindowCloseAll();
		if (canceled == TRUE) return TRUE;
	}
	mainFramePtr->m_wndTreeBar.clearContents();	
	
	if (mainFramePtr->onFileOpenWorkspace((*m_pRecentFileList)[nIndex]) == FALSE)
		m_pRecentFileList->Remove(nIndex);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CListBox	m_wishListCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_LIST_WISH, m_wishListCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void COODApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// COODApp commands

void COODApp::endOfSession()
{
	writeOODProfileSettings();
}

int COODApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	endOfSession();
	return CWinApp::ExitInstance();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_wishListCtrl.AddString("1. property editor for class (done)");
	m_wishListCtrl.AddString("2. some missing UML notations (done)");
	m_wishListCtrl.AddString("3. complete code generation for Visual C++ (done)");
	m_wishListCtrl.AddString("4. compound document support: OLE container/server (done)");
	m_wishListCtrl.AddString("5. reverse engineering for C++/VC++/Java");
	m_wishListCtrl.AddString("6. C# support");
	m_wishListCtrl.AddString("7. more language support like DDL, CORBA/IDL ...");
	m_wishListCtrl.AddString("8. XMI import/export");
	m_wishListCtrl.AddString("9. meta modeling");
	m_wishListCtrl.AddString("10. semantic actions for analyzing diagrams");
	m_wishListCtrl.AddString("11. color, font, etc ...");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COODApp::OnTipOfTheDay() 
{
	// TODO: Add your command handler code here
	
	TipDialog tipDlg;
	tipDlg.DoModal();
}


CDocument* COODApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (lpszFileName == NULL)
		return CWinApp::OpenDocumentFile(lpszFileName);
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	pMainFrame->SetActiveWindow();
	TCHAR szFileName[_MAX_PATH];
	strcpy_s(szFileName,BUFSIZ,lpszFileName);
	CString fileName = szFileName;
	CString extension = fileName.Right(_EXT_LEN4); 
	if (extension.CompareNoCase(_OOD_EXT) == 0) {
		BOOL canceled = pMainFrame->onWindowCloseAll();
		if (canceled == TRUE) {
			return NULL;
		}
		if (pMainFrame->onFileOpenWorkspace(fileName)) return pCOODClassDoc;
		return NIL;
	}
	extension = fileName.Right(_EXT_LEN5);
	if (extension.CompareNoCase(_PAK_EXT) == 0 ||
		extension.CompareNoCase(_USE_EXT) == 0 ||
		extension.CompareNoCase(_SEQ_EXT) == 0 ||
		extension.CompareNoCase(_COL_EXT) == 0 ||
		extension.CompareNoCase(_STA_EXT) == 0 ||
		extension.CompareNoCase(_ACT_EXT) == 0 ||
		extension.CompareNoCase(_DEP_EXT) == 0) {
		if ((pMainFrame->m_wndTreeBar.GetStyle() & WS_VISIBLE) != 0) {
			pMainFrame->ShowControlBar(&pMainFrame->m_wndTreeBar,FALSE,FALSE);
		} 
		return pMainFrame->openDocumentFile(fileName);
	}
	return NIL;
}
