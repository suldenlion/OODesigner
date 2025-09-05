// OOD.h : main header file for the OOD application
//
#if !defined(AFX_OOD_H__91AA8C05_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_OOD_H__91AA8C05_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "common.h"
#include "Classes.h"
/////////////////////////////////////////////////////////////////////////////
// COODApp:
// See OOD.cpp for the implementation of this class
//

class COODClassDoc;
class CInPlaceFrame;

//#define DEFAULT_FACE_NAME "Times New Roman"
#define DEFAULT_FACE_NAME "HY°ß°íµñ"

class COODApp : public CWinApp
{
private:
	CResizableEditDoc* _pOutputTextDoc;
	CMultiDocTemplate* _resizableEditViewBarDocTemplate;
	CString _selectedServerDiagram;

	void openRecentWorkspace();
	void initializeUnsignedLongVariables();
	void initializePopups();
	void initializeGraphicObjects();
	void initializeCodeGenerators();
	void initializeMemberPropDlgs();
	void initializeCurrentFontInfo();
	void constructFixedNameTables();
	void loadOODProfileSettings();
	void writeOODProfileSettings();
	void initializeAbsMacros();
	void resizeMemberPropDlgsIfNeeded();

public:
	virtual ~COODApp();
	COODApp();

	COleTemplateServer m_server;
	BOOL runAsServerFlag;
	BOOL classDelYesAlwaysFlag;
	BOOL classDelNoAlwaysFlag;

	CMultiDocTemplate* pClassDocTemplate; 
	CMultiDocTemplate* pObjectDocTemplate; 
	CMultiDocTemplate* pStateDocTemplate; 
	CMultiDocTemplate* pTextDocTemplate;
	CMultiDocTemplate* pUseCaseDocTemplate;
	CMultiDocTemplate* pCollaborationDocTemplate;
	CMultiDocTemplate* pSequenceDocTemplate;
	CMultiDocTemplate* pActivityDocTemplate;
	CMultiDocTemplate* pDeploymentDocTemplate;

	COODClassDoc* pCOODClassDoc; 

	CodeGenerator* theCPPCodeGenerator;
	CodeGenerator* theVCPPCodeGenerator;
	CodeGenerator* theCSharpCodeGenerator;
	CodeGenerator* theJavaCodeGenerator;

	ClassPropDlg* theCPPClassPropertyDlg;
	ClassPropDlg* theVCPPClassPropertyDlg;
	ClassPropDlg* theCSharpClassPropertyDlg;
	ClassPropDlg* theJavaClassPropertyDlg;

	MemberPropDlg* theCPPMethodPropertyDlg;
	MemberPropDlg* theVCPPMethodPropertyDlg;
	MemberPropDlg* theCSharpMethodPropertyDlg;
	MemberPropDlg* theJavaMethodPropertyDlg;

	MemberPropDlg* theCPPVarPropertyDlg;
	MemberPropDlg* theVCPPVarPropertyDlg;
	MemberPropDlg* theCSharpVarPropertyDlg;
	MemberPropDlg* theJavaVarPropertyDlg;

	PackagePropDlg* thePackagePropDlg;

	RelationTraverseDlg *theRelationTraverseDlg;

	Popup *theActivityMainPopup;
	Popup *theClassMainPopup;
	Popup *theDeploymentMainPopup;
	Popup *theCollaborationMainPopup;
	Popup *theSequenceMainPopup;
	Popup *theStateMainPopup;
	Popup *theUseCaseMainPopup;
	Popup *theClassTemplatePopup;
	Popup *theGeneralizationPopup;
	Popup *theAggregationPopup;
	Popup *theDependencyPopup;
	Popup *theAssociationPopup;
	Popup *theMessageFlowPopup;
	Popup *theMessageTextPopup;
	Popup *theCollaborationObjectPopup;
	Popup *theSequenceObjectPopup;
	Popup *theSequenceLanePopup;
	Popup *theStatePopup;
	Popup *theTransitionPopup;
	Popup *theTriggerPopup;
	Popup *theHWConnectionPopup;
	Popup *theMessagePopup;
	Popup *theSynchronizationPopup;
	Popup *theEditPopup;
	Popup *theActivationBarPopup;
	Popup *theInterfacePortPopup;
	Popup *thePackagePopup;
	Popup *theLinePopup;

	FixedNamesTable *cppBIClassNames;
	FixedNamesTable *vcppBIClassNames;
	FixedNamesTable *csharpBIClassNames;
	FixedNamesTable *javaBIClassNames;

	int currentFontSize;
	int currentFontWeight;
	COLORREF currentFontColor;
	CString currentFontFaceName;
	CString currentFontStyleName;
	BOOL currentFontBoldFlag;
	BOOL currentFontItalicFlag;
	BOOL currentFontStrikeOutFlag;
	BOOL currentFontUnderlineFlag;

	BOOL showTipsFlag;
	BOOL setGridFlag;
	COLORREF paperColor;
	COLORREF textColor;
	COLORREF shapeForegroundColor;
	COLORREF shapeBackgroundColor;
	CString versionNo;
	CString fileVersionNo;

	CString workspaceName;
	CString workspaceDir;
	CString projectLanguage;
	CString projectHFExtension;
	CString projectSFExtension;
	CString projectInheritanceTreeOrient;
	CString projectCodegenTargetDir;
	CString projectReverseSourceDir;
	CString projectAuthor;
	CString projectOrganization;
	BOOL projectDrawInheritanceTreeFlag;
	CStringList cppHeaderFileAbsMacros;
	CStringList cppSourceFileAbsMacros;
	CStringList vcppHeaderFileAbsMacros;
	CStringList vcppSourceFileAbsMacros;

// member fuctions
public:
	FixedNamesTable *getBuiltInClassTable();
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);  // add to MRU
	void addToWorkspaceList(LPCTSTR lpszPathName);
	void endOfSession();
	void showOutputBar(BOOL bShow);
	void deleteDocTemplates();
	void removeFileAndBackingUp(CString &fileName);
	void setFileExtension();
	CString selectedServerDiagram() {
		return _selectedServerDiagram;
	}
	CStringList &getHeaderFileAbsMacros(CString &language);
	CStringList &getSourceFileAbsMacros(CString &language);
	CodeGenerator *getActiveCodeGenerator();
	MemberPropDlg *getActiveMethodPropDlg();
	MemberPropDlg *getActiveVarPropDlg();
	ClassPropDlg *getActiveClassPropDlg();
	void deactivateMemberPropertyDlgs();
	void deactivateClassPropertyDlgs();
	void deactivateAllPropertyDlgs();
	CResizableEditDoc* getOutputTextDoc() {
		return _pOutputTextDoc;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COODApp)
	afx_msg void OnAppAbout();
	afx_msg void OnTipOfTheDay();
	//}}AFX_MSG
	BOOL OnOpenRecentWorkspace(UINT nID);
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OOD_H__91AA8C05_7A3E_11D2_AC44_00008610434C__INCLUDED_)

