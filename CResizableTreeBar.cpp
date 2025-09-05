// CResizableTreeBar.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <io.h>
#include "OOD.h"
#include "COODClassDoc.h"
#include "PackageLibrary.h"
#include "CResizableTreeBar.h"
#include "CResizableFloatWnd.h"
#include "ClassTemplate.h"
#include "CMainFrame.h"
#include "ClassFigureLibrary.h"
#include "FigureLibrary.h"
#include "PackageLibrary.h"
#include "ClassContent.h"
#include "ClassLibrary.h"
#include "PropCommonDlg.h"
#include "MemberPropDlg.h"
#include "ClassPropDlg.h"
#include "ClassTextLine.h"
#include "FigureList.h"
#include "COODView.h"
#include "UnsignedLong.h"
#include "QueryTextDlg.h"
#include "TextContent.h"
#include "RelationTraverseDlg.h"
#include "PackagePropDlg.h"
#include "COODCommonDoc.h"
#include "CTextDoc.h"
#include "CClassMigrationDlg.h"

#define TREE_BAR_BK_COLOR	(RGB(230,230,230))
#define BITMAP_WIDTH		(15)
#define BITMAP_HEIGHT		(15)

#define CLASS_TREE_SEL		(0)
#define DIAGRAM_TREE_SEL	(1)
#define FILE_TREE_SEL		(2)
#define INFO_TREE_SEL		(3)

#define FILE_CLOSE_BM_ID				(0)
#define FILE_OPEN_BM_ID					(1)
#define FILE_CPP_BM_ID					(2)
#define FILE_H_BM_ID					(3)
#define FILE_JAVA_BM_ID					(4)
#define FILE_TEXT_BM_ID					(5)

#define PROJECT_BM_ID					(0)
#define PACKAGE_BM_ID					(1)
#define CLASS_BM_ID						(2)
#define PUBLIC_MEMBER_FUNCTION_BM_ID	(3)
#define PROTECTED_MEMBER_FUNCTION_BM_ID	(4)
#define PRIVATE_MEMBER_FUNCTION_BM_ID	(5)
#define PUBLIC_DATA_MEMBER_BM_ID		(6)
#define PROTECTED_DATA_MEMBER_BM_ID		(7)
#define PRIVATE_DATA_MEMBER_BM_ID		(8)

#define PROJECT_POPUP_ID				(0)
#define PACKAGE_POPUP_ID				(1)
#define CLASS_POPUP_ID					(2)
#define DATA_POPUP_ID					(3)
#define FUNCTION_POPUP_ID				(4)
#define DIAGRAM_TYPE_POPUP_ID			(5)
#define DIAGRAM_POPUP_ID				(6)
#define FILE_TYPE_POPUP_ID				(7)
#define FILE_POPUP_ID					(8)
#define RELATIONSHIP_POPUP_ID			(9)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizableTreeBar

CResizableTreeBar::CResizableTreeBar()
:CResizableControlBar()
{
	classTreeCtrl = NIL;
	diagramTreeCtrl = NIL;
	fileTreeCtrl = NIL;
	infoTreeCtrl = NIL;

	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;

	if (!_allPopupMenu.LoadMenu(IDR_BROWSER_POPUPS)) {
		TRACE0("Loading menu for tree bar fails");
	}
}

CResizableTreeBar::~CResizableTreeBar()
{
	_allPopupMenu.DestroyMenu();
}

BEGIN_MESSAGE_MAP(CResizableTreeBar, CResizableControlBar)
	//{{AFX_MSG_MAP(CResizableTreeBar)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DATA_PROPERTIES, OnDataProperties)
	ON_COMMAND(ID_FUNCTION_PROPERTIES, OnFunctionProperties)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_CLASS_GO_TO_DEFINITION, OnClassGoToDefinition)
	ON_COMMAND(ID_PACKAGE_NEW_CLASS, OnPackageNewClass)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_PACKAGE_OPEN, OnPackageOpen)
	ON_COMMAND(ID_CLASS_RELATED_CLASSES, OnClassRelatedClasses)
	ON_COMMAND(ID_DIAGRAM_TYPE_NEW_DIAGRAM, OnDiagramTypeNewDiagram)
	ON_COMMAND(ID_DIAGRAM_OPEN, OnDiagramOpen)
	ON_COMMAND(ID_DIAGRAM_DELETE, OnDiagramDelete)
	ON_COMMAND(ID_FILE_TYPE_NEW_FILE, OnFileTypeNewFile)
	ON_COMMAND(ID_FILE_MENU_OPEN, OnFileMenuOpen)
	ON_COMMAND(ID_FILE_MENU_DELETE, OnFileMenuDelete)
	ON_COMMAND(ID_PACKAGE_PROPERTIES, OnPackageProperties)
	ON_COMMAND(ID_CLASS_ROOT_NEW_PACKAGE, OnClassRootNewPackage)
	ON_COMMAND(ID_MEMBER_DELETE, OnMemberDelete)
	ON_COMMAND(ID_CLASS_DELETE, OnClassDelete)
	ON_COMMAND(ID_PACKAGE_DELETE, OnPackageDelete)
	ON_COMMAND(ID_CLASS_MIGRATE, OnClassMigrate)
	//}}AFX_MSG_MAP
    ON_NOTIFY(TCN_SELCHANGE,IDC_TREEBAR_TAB,OnTabChanged)
	ON_NOTIFY(TVN_ITEMEXPANDED,IDC_FILETREECTRL,OnItemExpendedAtFileTree)
	ON_NOTIFY(TVN_ITEMEXPANDED,IDC_DIAGRAMTREECTRL,OnItemExpendedAtDiagramTree)
	ON_NOTIFY(TVN_ITEMEXPANDED,IDC_INFOTREECTRL,OnItemExpendedAtInfoTree)
END_MESSAGE_MAP()

void CResizableTreeBar::clearContents()
{
	classTreeCtrl->DeleteAllItems();

	HTREEITEM hRoot = classTreeCtrl->InsertItem(_T("Classes"));
	classTreeCtrl->SetItemImage(hRoot,PROJECT_BM_ID,PROJECT_BM_ID);
	classTreeCtrl->SetItemData(hRoot,ROOT_ID);

	diagramTreeCtrl->DeleteAllItems();
	hRoot = diagramTreeCtrl->InsertItem(_T("Diagrams"));
	diagramTreeCtrl->SetItemImage(hRoot,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hRoot,-1);
	HTREEITEM hTmp = diagramTreeCtrl->InsertItem("Class Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Use Case Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Sequence Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Collaboration Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("State Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Activity Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Deployment Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);

	fileTreeCtrl->DeleteAllItems();
	hRoot = fileTreeCtrl->InsertItem(_T("Files"));
	fileTreeCtrl->SetItemImage(hRoot,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	fileTreeCtrl->SetItemData(hRoot,-1);
	hTmp = fileTreeCtrl->InsertItem("Source Files",hRoot);
	fileTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	fileTreeCtrl->SetItemData(hTmp,-1);
	hTmp = fileTreeCtrl->InsertItem("Header Files",hRoot);
	fileTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	fileTreeCtrl->SetItemData(hTmp,-1);
	hTmp = fileTreeCtrl->InsertItem("Text Files",hRoot);
	fileTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	fileTreeCtrl->SetItemData(hTmp,-1);
}

void CResizableTreeBar::registerClassContentFromPackageLibrary(PackageLibrary *allClassContents)
{
	HTREEITEM hRoot  = classTreeCtrl->GetRootItem();
	if (hRoot == NULL) return;
	ClassLibrary *aClassLibrary = allClassContents->getFirst();
	while (aClassLibrary != NIL) {
		CString packName = aClassLibrary->packageName();
		HTREEITEM hPackage = classTreeCtrl->InsertItem(packName,hRoot);
		classTreeCtrl->SetItemData(hPackage,PACKAGE_ID);
		classTreeCtrl->SetItemImage(hPackage,PACKAGE_BM_ID,PACKAGE_BM_ID);
		ClassContent *aClassContent = aClassLibrary->getFirst();
		while (aClassContent != NIL) {
			CString className = aClassContent->className();
			insertClass(hPackage,className,aClassContent);
			aClassContent = aClassLibrary->getNext();
		}
		aClassLibrary = allClassContents->getNext();
	}
	invalidateCurrentTabCtrl(classTreeCtrl);
}

void CResizableTreeBar::insertClass(HTREEITEM hPackage,CString &className,ClassContent *aClassContent)
{
	HTREEITEM hClass = classTreeCtrl->InsertItem(className,hPackage);
	classTreeCtrl->SetItemData(hClass,CLASS_ID);
	classTreeCtrl->SetItemImage(hClass,CLASS_BM_ID,CLASS_BM_ID);
	aClassContent->parseMembers();
	int nDataMembers = aClassContent->nOfDataMembers();
	int i = 0;
	CString aLineString = "";
	int vis = 0;
	for (i = 0; i < nDataMembers; i++) {
		aClassContent->getDataMemberBrowserString(i,vis,aLineString);
		HTREEITEM hMember = classTreeCtrl->InsertItem(aLineString,hClass);
		if (vis == PROTECTED_ID) {
			classTreeCtrl->SetItemData(hMember,DATAMEMBER_ID);
			classTreeCtrl->SetItemImage(hMember,PROTECTED_DATA_MEMBER_BM_ID,PROTECTED_DATA_MEMBER_BM_ID);
		} else if (vis == PRIVATE_ID) {
			classTreeCtrl->SetItemData(hMember,DATAMEMBER_ID);
			classTreeCtrl->SetItemImage(hMember,PRIVATE_DATA_MEMBER_BM_ID,PRIVATE_DATA_MEMBER_BM_ID);
		} else {
			classTreeCtrl->SetItemData(hMember,DATAMEMBER_ID);
			classTreeCtrl->SetItemImage(hMember,PUBLIC_DATA_MEMBER_BM_ID,PUBLIC_DATA_MEMBER_BM_ID);
		}
	}
	int nMemberFunctions = aClassContent->nOfMemberFunctions();
	i = 0;
	aLineString = "";
	vis = 0;
	for (i = 0; i < nMemberFunctions; i++) {
		aClassContent->getMemberFunctionBrowserString(i,vis,aLineString);
		HTREEITEM hMember = classTreeCtrl->InsertItem(aLineString,hClass);
		if (vis == PROTECTED_ID) {
			classTreeCtrl->SetItemData(hMember,MEMBERFUNCTION_ID);
			classTreeCtrl->SetItemImage(hMember,PROTECTED_MEMBER_FUNCTION_BM_ID,PROTECTED_MEMBER_FUNCTION_BM_ID);
		} else if (vis == PRIVATE_ID) {
			classTreeCtrl->SetItemData(hMember,MEMBERFUNCTION_ID);
			classTreeCtrl->SetItemImage(hMember,PRIVATE_MEMBER_FUNCTION_BM_ID,PRIVATE_MEMBER_FUNCTION_BM_ID);
		} else {
			classTreeCtrl->SetItemData(hMember,MEMBERFUNCTION_ID);
			classTreeCtrl->SetItemImage(hMember,PUBLIC_MEMBER_FUNCTION_BM_ID,PUBLIC_MEMBER_FUNCTION_BM_ID);
		}
	}
}

void CResizableTreeBar::registerClassDiagramFilesFromClassFigureLibrary(ClassFigureLibrary *classFiguresLibrary)
{
	FigureLibrary *aClassFiguresLibrary = classFiguresLibrary->getFirst();
	while (aClassFiguresLibrary != NIL) {
		CString dgmName = aClassFiguresLibrary->packageName();
		insertDiagramName(dgmName);
		aClassFiguresLibrary = classFiguresLibrary->getNext();
	}
}

void CResizableTreeBar::insertTextName(CString &txtName)
{
	CString language = theAppPtr->projectLanguage;

	CString sourceExtension = theAppPtr->projectSFExtension;
	int extensionLen = sourceExtension.GetLength() + 1;
	CString extension = txtName;
	if (extension.GetLength() >= extensionLen) {
		extension = extension.Right(extensionLen-1);
	}
	if (extension.CompareNoCase(sourceExtension) == 0) {
		HTREEITEM hRoot = fileTreeCtrl->GetRootItem();
		// source file
		HTREEITEM hFileType = fileTreeCtrl->GetChildItem(hRoot);
		HTREEITEM hFile = fileTreeCtrl->GetChildItem(hFileType);
		while (hFile != NULL) {
			if (fileTreeCtrl->GetItemText(hFile).CompareNoCase(txtName) == 0) {
				return;
			}
			hFile = fileTreeCtrl->GetNextSiblingItem(hFile);
		}
		hFile = fileTreeCtrl->InsertItem(txtName,hFileType);
		if (language.CompareNoCase("Java") == 0) {
			fileTreeCtrl->SetItemImage(hFile,FILE_JAVA_BM_ID,FILE_JAVA_BM_ID);
			fileTreeCtrl->SetItemData(hFile,FILE_JAVA_BM_ID);
		} else {
			fileTreeCtrl->SetItemImage(hFile,FILE_CPP_BM_ID,FILE_CPP_BM_ID);
			fileTreeCtrl->SetItemData(hFile,FILE_CPP_BM_ID);
		}
		fileTreeCtrl->SortChildren(hFileType);
		UINT state = fileTreeCtrl->GetItemState(hFileType,TVIF_STATE);
		if (state & TVIS_EXPANDED) {
			fileTreeCtrl->SetItemImage(hFileType,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
		} else {
			fileTreeCtrl->SetItemImage(hFileType,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
		}
		invalidateCurrentTabCtrl(fileTreeCtrl);
		return;
	}

	if (language.CompareNoCase("Java") != 0) {
		CString headerExtension = theAppPtr->projectHFExtension;
		extensionLen = headerExtension.GetLength() + 1;
		extension = txtName;
		if (extension.GetLength() >= extensionLen) {
			extension = extension.Right(extensionLen-1);
		}
		if (extension.CompareNoCase(headerExtension) == 0) {
			HTREEITEM hRoot = fileTreeCtrl->GetRootItem();
			// header file
			HTREEITEM hFileType = fileTreeCtrl->GetChildItem(hRoot);
			hFileType = fileTreeCtrl->GetNextSiblingItem(hFileType);
			HTREEITEM hFile = fileTreeCtrl->GetChildItem(hFileType);
			while (hFile != NULL) {
				if (fileTreeCtrl->GetItemText(hFile).CompareNoCase(txtName) == 0) {
					return;
				}
				hFile = fileTreeCtrl->GetNextSiblingItem(hFile);
			}
			hFile = fileTreeCtrl->InsertItem(txtName,hFileType);
			fileTreeCtrl->SetItemImage(hFile,FILE_H_BM_ID,FILE_H_BM_ID);
			fileTreeCtrl->SetItemData(hFile,FILE_H_BM_ID);
			fileTreeCtrl->SortChildren(hFileType);
			UINT state = fileTreeCtrl->GetItemState(hFileType,TVIF_STATE);
			if (state & TVIS_EXPANDED) {
				fileTreeCtrl->SetItemImage(hFileType,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
			} else {
				fileTreeCtrl->SetItemImage(hFileType,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
			}
			invalidateCurrentTabCtrl(fileTreeCtrl);
			return;
		}
	}

	HTREEITEM hRoot = fileTreeCtrl->GetRootItem();
	// text file
	HTREEITEM hFileType = fileTreeCtrl->GetChildItem(hRoot);
	hFileType = fileTreeCtrl->GetNextSiblingItem(hFileType);
	hFileType = fileTreeCtrl->GetNextSiblingItem(hFileType);
	HTREEITEM hFile = fileTreeCtrl->GetChildItem(hFileType);
	while (hFile != NULL) {
		if (fileTreeCtrl->GetItemText(hFile).CompareNoCase(txtName) == 0) {
			return;
		}
		hFile = fileTreeCtrl->GetNextSiblingItem(hFile);
	}
	hFile = fileTreeCtrl->InsertItem(txtName,hFileType);
	fileTreeCtrl->SetItemImage(hFile,FILE_TEXT_BM_ID,FILE_TEXT_BM_ID);
	fileTreeCtrl->SetItemData(hFile,FILE_TEXT_BM_ID);
	fileTreeCtrl->SortChildren(hFileType);
	UINT state = fileTreeCtrl->GetItemState(hFileType,TVIF_STATE);
	if (state & TVIS_EXPANDED) {
		fileTreeCtrl->SetItemImage(hFileType,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
	} else {
		fileTreeCtrl->SetItemImage(hFileType,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	}
	invalidateCurrentTabCtrl(fileTreeCtrl);
}

void CResizableTreeBar::registerTextFiles()
{
	char dirString[BUFSIZ];
	strcpy_s(dirString,BUFSIZ,theAppPtr->projectCodegenTargetDir);
	strcat_s(dirString,BUFSIZ,"*.*");
	registerTextFilesFrom(dirString);

/*
	strcpy(dirString,"*.*");
	registerTextFilesFrom(dirString);
*/
	Invalidate();
}

void CResizableTreeBar::registerTextFilesFrom(char *dirString)
{
	struct _finddata_t dir;
	long hFile;

	CStringList registeredFiles;

	CString language = theAppPtr->projectLanguage;
	// source file 처리 ...
	CString sourceExtension = theAppPtr->projectSFExtension;
	unsigned int extensionLen = sourceExtension.GetLength() + 1;
	HTREEITEM hRoot = fileTreeCtrl->GetRootItem();
	HTREEITEM hFileType = diagramTreeCtrl->GetChildItem(hRoot);

	if ((hFile = _findfirst(dirString,&dir)) == -1L) return;
	while (_findnext(hFile,&dir) == 0) {
		if ((dir.attrib & _A_HIDDEN) ||
			(dir.attrib & _A_RDONLY) ||
			(dir.attrib & _A_SUBDIR)) {
			continue;
		}
		char fileName[BUFSIZ];
		strcpy_s(fileName,BUFSIZ,dir.name);
		// source file check
		if (strlen(fileName) <= extensionLen) continue;
		CString extension = fileName;
		extension = extension.Right(extensionLen-1);
		if (extension.CompareNoCase(sourceExtension) == 0) {
			HTREEITEM hFile = fileTreeCtrl->GetChildItem(hFileType);
			while (hFile != NULL) {
				if (fileTreeCtrl->GetItemText(hFile).CompareNoCase(fileName) == 0) {
					goto nextLoop1;
				}
				hFile = diagramTreeCtrl->GetNextSiblingItem(hFile);
			}
			hFile = diagramTreeCtrl->InsertItem(fileName,hFileType);
			registeredFiles.AddTail(fileName);
			if (language.CompareNoCase("Java") == 0) {
				fileTreeCtrl->SetItemImage(hFile,FILE_JAVA_BM_ID,FILE_JAVA_BM_ID);
				fileTreeCtrl->SetItemData(hFile,FILE_JAVA_BM_ID);
			} else {
				fileTreeCtrl->SetItemImage(hFile,FILE_CPP_BM_ID,FILE_CPP_BM_ID);
				fileTreeCtrl->SetItemData(hFile,FILE_CPP_BM_ID);
			}
			fileTreeCtrl->SortChildren(hFileType);
		}
nextLoop1:
		extension = "";
	}
	_findclose(hFile);

	if (language.CompareNoCase("Java") != 0) {
		// header file 처리 ...
		CString headerExtension = theAppPtr->projectHFExtension;
		extensionLen = headerExtension.GetLength() + 1;
		hRoot = fileTreeCtrl->GetRootItem();
		hFileType = diagramTreeCtrl->GetChildItem(hRoot);
		hFileType = diagramTreeCtrl->GetNextSiblingItem(hFileType);

		if ((hFile = _findfirst(dirString,&dir)) == -1L) return;
		while (_findnext(hFile,&dir) == 0) {
			if ((dir.attrib & _A_HIDDEN) ||
				(dir.attrib & _A_RDONLY) ||
				(dir.attrib & _A_SUBDIR)) {
				continue;
			}
			char fileName[BUFSIZ];
			strcpy_s(fileName,BUFSIZ,dir.name);
			// header file check
			if (strlen(fileName) <= extensionLen) continue;
			CString extension = fileName;
			extension = extension.Right(extensionLen-1);
			if (extension.CompareNoCase(headerExtension) == 0) {
				HTREEITEM hFile = fileTreeCtrl->GetChildItem(hFileType);
				while (hFile != NULL) {
					if (fileTreeCtrl->GetItemText(hFile).CompareNoCase(fileName) == 0) {
						goto nextLoop2;
					}
					hFile = diagramTreeCtrl->GetNextSiblingItem(hFile);
				}
				registeredFiles.AddTail(fileName);
				hFile = diagramTreeCtrl->InsertItem(fileName,hFileType);
				fileTreeCtrl->SetItemImage(hFile,FILE_H_BM_ID,FILE_H_BM_ID);
				fileTreeCtrl->SetItemData(hFile,FILE_H_BM_ID);
				fileTreeCtrl->SortChildren(hFileType);
			}
	nextLoop2:
			extension = "";
		}
		_findclose(hFile);
	}

	// txt file 처리 ...
	hRoot = fileTreeCtrl->GetRootItem();
	hFileType = diagramTreeCtrl->GetChildItem(hRoot);
	hFileType = diagramTreeCtrl->GetNextSiblingItem(hFileType);
	hFileType = diagramTreeCtrl->GetNextSiblingItem(hFileType);

	if ((hFile = _findfirst(dirString,&dir)) == -1L) return;
	while (_findnext(hFile,&dir) == 0) {
		if ((dir.attrib & _A_HIDDEN) ||
			(dir.attrib & _A_RDONLY) ||
			(dir.attrib & _A_SUBDIR)) {
			continue;
		}
		char fileName[BUFSIZ];
		strcpy_s(fileName,BUFSIZ,dir.name);
		// text file check
		if (registeredFiles.Find(fileName) != NULL) {
			continue;
		}
		CString extension = fileName;
		if (strlen(fileName) <= _EXT_LEN5) {
			HTREEITEM hFile = fileTreeCtrl->GetChildItem(hFileType);
			while (hFile != NULL) {
				if (fileTreeCtrl->GetItemText(hFile).CompareNoCase(fileName) == 0) {
					goto nextLoop3;
				}
				hFile = diagramTreeCtrl->GetNextSiblingItem(hFile);
			}
			hFile = diagramTreeCtrl->InsertItem(fileName,hFileType);
			fileTreeCtrl->SetItemImage(hFile,FILE_TEXT_BM_ID,FILE_TEXT_BM_ID);
			fileTreeCtrl->SetItemData(hFile,FILE_TEXT_BM_ID);
			fileTreeCtrl->SortChildren(hFileType);
		} else {
			extension = extension.Right(_EXT_LEN5);
			if (extension.CompareNoCase(_OOD_EXT) != 0 &&
				extension.CompareNoCase(_PAK_EXT) != 0 &&
				extension.CompareNoCase(_USE_EXT) != 0 &&
				extension.CompareNoCase(_SEQ_EXT) != 0 &&
				extension.CompareNoCase(_COL_EXT) != 0 &&
				extension.CompareNoCase(_STA_EXT) != 0 &&
				extension.CompareNoCase(_ACT_EXT) != 0 &&
				extension.CompareNoCase(_DEP_EXT) != 0) {
				HTREEITEM hFile = fileTreeCtrl->GetChildItem(hFileType);
				while (hFile != NULL) {
					if (fileTreeCtrl->GetItemText(hFile).CompareNoCase(fileName) == 0) {
						goto nextLoop3;
					}
					hFile = diagramTreeCtrl->GetNextSiblingItem(hFile);
				}
				hFile = diagramTreeCtrl->InsertItem(fileName,hFileType);
				fileTreeCtrl->SetItemImage(hFile,FILE_TEXT_BM_ID,FILE_TEXT_BM_ID);
				fileTreeCtrl->SetItemData(hFile,FILE_TEXT_BM_ID);
				fileTreeCtrl->SortChildren(hFileType);
			}
		}
nextLoop3:
		extension = "";
	}
	_findclose(hFile);
}

void CResizableTreeBar::registerDiagramFilesFromCurrentDir()
{
	struct _finddata_t dir;
	long hFile;

	char dirString[BUFSIZ];
	strcpy_s(dirString,BUFSIZ,"*.*");

	if ((hFile = _findfirst(dirString,&dir)) == -1L) return;
	while (_findnext(hFile,&dir) == 0) {
		if ((dir.attrib & _A_HIDDEN) ||
			(dir.attrib & _A_RDONLY) ||
			(dir.attrib & _A_SUBDIR)) {
			continue;
		}
		char fileName[BUFSIZ];
		strcpy_s(fileName,BUFSIZ,dir.name);
		if (strlen(fileName) <= _EXT_LEN5) continue;
		CString extension = fileName;
		extension = extension.Right(_EXT_LEN5);
		if (extension.CompareNoCase(_USE_EXT) == 0 ||
			extension.CompareNoCase(_SEQ_EXT) == 0 ||
			extension.CompareNoCase(_COL_EXT) == 0 ||
			extension.CompareNoCase(_STA_EXT) == 0 ||
			extension.CompareNoCase(_ACT_EXT) == 0 ||
			extension.CompareNoCase(_DEP_EXT) == 0) {
			CString dgmName = fileName;
			insertDiagramName(dgmName);
		}
	}
	_findclose(hFile);
}

void CResizableTreeBar::insertDiagramName(CString &dgmName)
{
	CString extension = dgmName.Right(_EXT_LEN5);
	CString dgmType = _T("");
	int bmId = 0;
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		dgmType = "Class Diagram";
		bmId = CLASS_DIAGRAM_BM_ID;
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		dgmType = "Use Case Diagram";
		bmId = USE_CASE_DIAGRAM_BM_ID;
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		dgmType = "Sequence Diagram";
		bmId = SEQUENCE_DIAGRAM_BM_ID;
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		dgmType = "Collaboration Diagram";
		bmId = COLLABORATION_DIAGRAM_BM_ID;
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		dgmType = "State Diagram";
		bmId = STATE_DIAGRAM_BM_ID;
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		dgmType = "Activity Diagram";
		bmId = ACTIVITY_DIAGRAM_BM_ID;
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		dgmType = "Deployment Diagram";
		bmId = DEPLOYMENT_DIAGRAM_BM_ID;
	}
	HTREEITEM hRoot = diagramTreeCtrl->GetRootItem();
	HTREEITEM hDgmType = diagramTreeCtrl->GetChildItem(hRoot);
	while (hDgmType != NULL) {
		if (diagramTreeCtrl->GetItemText(hDgmType).CompareNoCase(dgmType) == 0) {
			HTREEITEM hDgm = diagramTreeCtrl->GetChildItem(hDgmType);
			while (hDgm != NULL) {
				if (diagramTreeCtrl->GetItemText(hDgm).CompareNoCase(dgmName) == 0) {
					return;
				}
				hDgm = diagramTreeCtrl->GetNextSiblingItem(hDgm);
			}
			hDgm = diagramTreeCtrl->InsertItem(dgmName,hDgmType);
			diagramTreeCtrl->SetItemImage(hDgm,bmId,bmId);
			diagramTreeCtrl->SetItemData(hDgm,bmId);
			UINT state = diagramTreeCtrl->GetItemState(hDgmType,TVIF_STATE);
			if (state & TVIS_EXPANDED) {
				diagramTreeCtrl->SetItemImage(hDgmType,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
			} else {
				diagramTreeCtrl->SetItemImage(hDgmType,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
			}
			invalidateCurrentTabCtrl(diagramTreeCtrl);
			return;
		}
		hDgmType = diagramTreeCtrl->GetNextSiblingItem(hDgmType);
	}
}

void CResizableTreeBar::insertPackage(CString &packageName)
{
	HTREEITEM hRoot = classTreeCtrl->GetRootItem();
	HTREEITEM hPackage = classTreeCtrl->InsertItem(packageName,hRoot);
	classTreeCtrl->SetItemData(hPackage,PACKAGE_ID);
	classTreeCtrl->SetItemImage(hPackage,PACKAGE_BM_ID,PACKAGE_BM_ID);
	classTreeCtrl->SortChildren(hRoot);
	invalidateCurrentTabCtrl(classTreeCtrl);
}

BOOL CResizableTreeBar::containsAnyClassInPackage(CString packageName)
{
	HTREEITEM hRoot = classTreeCtrl->GetRootItem();
	HTREEITEM hPackage = classTreeCtrl->GetChildItem(hRoot);
	while (hPackage != NULL) {
		if (classTreeCtrl->GetItemText(hPackage).CompareNoCase(packageName) == 0) {
			if (classTreeCtrl->ItemHasChildren(hPackage)) {
				return TRUE;
			} else {
				classTreeCtrl->DeleteItem(hPackage);
				return FALSE;
			}
		}
		hPackage = classTreeCtrl->GetNextSiblingItem(hPackage);
	}
	return FALSE;
}

void CResizableTreeBar::replaceClass(CString &packageName,CString &className,ClassContent *aContent)
{
	HTREEITEM hRoot = classTreeCtrl->GetRootItem();
	HTREEITEM hPackage = classTreeCtrl->GetChildItem(hRoot);
	while (hPackage != NULL) {
		if (classTreeCtrl->GetItemText(hPackage).CompareNoCase(packageName) == 0) {
			HTREEITEM hClass = classTreeCtrl->GetChildItem(hPackage);
			while (hClass != NULL) {
				if (classTreeCtrl->GetItemText(hClass).CompareNoCase(className) == 0) {
					BOOL hasChild = classTreeCtrl->ItemHasChildren(hClass);
					if (hasChild != FALSE) {
						deleteAllClassMember(hClass);
					}
					insertClassMember(hClass,NIL,aContent);
					invalidateCurrentTabCtrl(classTreeCtrl);
					return;
				}
				hClass = classTreeCtrl->GetNextSiblingItem(hClass);
			}
			return;
		}
		hPackage = classTreeCtrl->GetNextSiblingItem(hPackage);
	}
}

void CResizableTreeBar::deleteClass(CString &packageName,CString &className)
{
	HTREEITEM hRoot = classTreeCtrl->GetRootItem();
	HTREEITEM hPackage = classTreeCtrl->GetChildItem(hRoot);
	while (hPackage != NULL) {
		if (classTreeCtrl->GetItemText(hPackage).CompareNoCase(packageName) == 0) {
			HTREEITEM hClass = classTreeCtrl->GetChildItem(hPackage);
			while (hClass != NULL) {
				if (classTreeCtrl->GetItemText(hClass).CompareNoCase(className) == 0) {
					classTreeCtrl->DeleteItem(hClass);
					invalidateCurrentTabCtrl(classTreeCtrl);
					return;
				}
				hClass = classTreeCtrl->GetNextSiblingItem(hClass);
			}
			return;
		}
		hPackage = classTreeCtrl->GetNextSiblingItem(hPackage);
	}
}

void CResizableTreeBar::insertClass(CString &packageName,CString &className,ClassTemplate *aClass)
{
	HTREEITEM hRoot = classTreeCtrl->GetRootItem();
	HTREEITEM hPackage = classTreeCtrl->GetChildItem(hRoot);
	while (hPackage != NULL) {
		HTREEITEM hClass = classTreeCtrl->GetChildItem(hPackage);
		while (hClass != NULL) {
			if (classTreeCtrl->GetItemText(hClass).CompareNoCase(className) == 0) {
				// 이미 있는 경우, 자바 경우 코드를 다시 짜야될 것 ...
				BOOL hasChild = classTreeCtrl->ItemHasChildren(hClass);
				if (hasChild != FALSE) {
					deleteAllClassMember(hClass);
				}
				insertClassMember(hClass,aClass,NIL);
				UINT state = classTreeCtrl->GetItemState(hClass,TVIF_STATE);
				if ((state & TVIS_EXPANDED) || (hasChild == FALSE)) {
					invalidateCurrentTabCtrl(classTreeCtrl);
				}
				return;
			}
			hClass = classTreeCtrl->GetNextSiblingItem(hClass);
		}
		hPackage = classTreeCtrl->GetNextSiblingItem(hPackage);
	}

	hPackage = classTreeCtrl->GetChildItem(hRoot);
	while (hPackage != NULL) {
		if (classTreeCtrl->GetItemText(hPackage).CompareNoCase(packageName) == 0) {
			BOOL hasChild = classTreeCtrl->ItemHasChildren(hPackage);
			HTREEITEM hClass = classTreeCtrl->InsertItem(className,hPackage);
			classTreeCtrl->SetItemData(hClass,CLASS_ID);
			classTreeCtrl->SetItemImage(hClass,CLASS_BM_ID,CLASS_BM_ID);
			if (aClass != NIL) insertClassMember(hClass,aClass,NIL);
			classTreeCtrl->SortChildren(hPackage);
			UINT state = classTreeCtrl->GetItemState(hPackage,TVIF_STATE);
			if ((state & TVIS_EXPANDED) || (hasChild == FALSE)) {
				invalidateCurrentTabCtrl(classTreeCtrl);
			}
			return;
		}
		hPackage = classTreeCtrl->GetNextSiblingItem(hPackage);
	} 
	hRoot = classTreeCtrl->GetRootItem();
	hPackage = classTreeCtrl->InsertItem(packageName,hRoot);
	classTreeCtrl->SetItemData(hPackage,PACKAGE_ID);
	classTreeCtrl->SetItemImage(hPackage,PACKAGE_BM_ID,PACKAGE_BM_ID);
	HTREEITEM hClass = classTreeCtrl->InsertItem(className,hPackage);
	classTreeCtrl->SetItemData(hClass,CLASS_ID);
	classTreeCtrl->SetItemImage(hClass,CLASS_BM_ID,CLASS_BM_ID);
	insertClassMember(hClass,aClass,NIL);
	classTreeCtrl->SortChildren(hRoot);
	invalidateCurrentTabCtrl(classTreeCtrl);
}

void CResizableTreeBar::deleteADiagram(CString dgmName)
{
	HTREEITEM hRoot = diagramTreeCtrl->GetRootItem();
	HTREEITEM hDiagramType = diagramTreeCtrl->GetChildItem(hRoot);
	while (hDiagramType != NULL) {
		HTREEITEM hDiagram = diagramTreeCtrl->GetChildItem(hDiagramType);
		while (hDiagram != NULL) {
			if (dgmName.CompareNoCase(diagramTreeCtrl->GetItemText(hDiagram)) == 0) {
				diagramTreeCtrl->DeleteItem(hDiagram);
				return;
			}
			hDiagram = diagramTreeCtrl->GetNextSiblingItem(hDiagram);
		}
		hDiagramType = diagramTreeCtrl->GetNextSiblingItem(hDiagramType);
	};
}

void CResizableTreeBar::deleteAllClassMember(HTREEITEM hClass)
{
	do {
		HTREEITEM hMember = classTreeCtrl->GetChildItem(hClass);
		if (hMember == NULL) break;
		classTreeCtrl->DeleteItem(hMember);
	} while (TRUE);
}

void CResizableTreeBar::insertClassMember(HTREEITEM hClass,ClassTemplate *aClass,ClassContent *aContent)
{
	int nDataMembers;
	if (aClass != NIL) {
		nDataMembers = aClass->nOfDataMembers();
	} else if (aContent != NIL) {
		nDataMembers = aContent->nOfDataMembers();
	} else {
		return;
	}
	int i = 0;
	CString aLineString = "";
	int vis = 0;
	for (i = 0; i < nDataMembers; i++) {
		if (aClass != NIL) {
			aClass->getDataMemberBrowserString(i,vis,aLineString);
		} else if (aContent != NIL) {
			aContent->getDataMemberBrowserString(i,vis,aLineString);
		}
		HTREEITEM hMember = classTreeCtrl->InsertItem(aLineString,hClass);
		if (vis == PROTECTED_ID) {
			classTreeCtrl->SetItemData(hMember,DATAMEMBER_ID);
			classTreeCtrl->SetItemImage(hMember,PROTECTED_DATA_MEMBER_BM_ID,PROTECTED_DATA_MEMBER_BM_ID);
		} else if (vis == PRIVATE_ID) {
			classTreeCtrl->SetItemData(hMember,DATAMEMBER_ID);
			classTreeCtrl->SetItemImage(hMember,PRIVATE_DATA_MEMBER_BM_ID,PRIVATE_DATA_MEMBER_BM_ID);
		} else {
			classTreeCtrl->SetItemData(hMember,DATAMEMBER_ID);
			classTreeCtrl->SetItemImage(hMember,PUBLIC_DATA_MEMBER_BM_ID,PUBLIC_DATA_MEMBER_BM_ID);
		}
	}

	int nMemberFunctions;
	if (aClass != NIL) {
		nMemberFunctions = aClass->nOfMemberFunctions();
	} else if (aContent != NIL) {
		nMemberFunctions = aContent->nOfMemberFunctions();
	} else {
		return;
	}
	i = 0;
	aLineString = "";
	vis = 0;
	for (i = 0; i < nMemberFunctions; i++) {
		if (aClass != NIL) {
			aClass->getMemberFunctionBrowserString(i,vis,aLineString);
		} else if (aContent != NIL) {
			aContent->getMemberFunctionBrowserString(i,vis,aLineString);
		}
		HTREEITEM hMember = classTreeCtrl->InsertItem(aLineString,hClass);
		if (vis == PROTECTED_ID) {
			classTreeCtrl->SetItemData(hMember,MEMBERFUNCTION_ID);
			classTreeCtrl->SetItemImage(hMember,PROTECTED_MEMBER_FUNCTION_BM_ID,PROTECTED_MEMBER_FUNCTION_BM_ID);
		} else if (vis == PRIVATE_ID) {
			classTreeCtrl->SetItemData(hMember,MEMBERFUNCTION_ID);
			classTreeCtrl->SetItemImage(hMember,PRIVATE_MEMBER_FUNCTION_BM_ID,PRIVATE_MEMBER_FUNCTION_BM_ID);
		} else {
			classTreeCtrl->SetItemData(hMember,MEMBERFUNCTION_ID);
			classTreeCtrl->SetItemImage(hMember,PUBLIC_MEMBER_FUNCTION_BM_ID,PUBLIC_MEMBER_FUNCTION_BM_ID);
		}
	}
}

CWnd * CResizableTreeBar::GetTabWindow(int nTab)
{
    TC_ITEM TCI;
    TCI.mask = TCIF_PARAM; 
    m_TabCtrl.GetItem(nTab, &TCI);
    CWnd * pWnd = (CWnd *)TCI.lParam;
    ASSERT(pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
    return pWnd;
}

void CResizableTreeBar::invalidateCurrentTabCtrl(CTreeCtrl* ctrl)
{
    int nSel = m_TabCtrl.GetCurSel();   
    ASSERT(nSel != -1);
    
	CWnd *wnd = GetTabWindow(nSel);
	if (wnd == NULL) return;

    if ((wnd->GetStyle() & WS_VISIBLE) &&
		wnd == ctrl) {
		ctrl->Invalidate();
	}
}

void CResizableTreeBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
{
    CRect rect(0, 0, cx, cy);
    if (IsProbablyFloating())
        rect.InflateRect(-2, -2);       // give space around controls.
    else
        rect.InflateRect(-4, -4);       // give space around controls.

    // reposition the tab control.
    m_TabCtrl.MoveWindow(&rect);
    m_TabCtrl.AdjustRect(FALSE, &rect);

    for (int i = 0; i < m_TabCtrl.GetItemCount(); i++)
    {
        GetTabWindow(i)->MoveWindow(&rect);
    }
}


void CResizableTreeBar::OnTabChanged( NMHDR * pNM, LRESULT * pResult )
{
    ShowSelTabWindow();
    *pResult = TRUE;
}

void CResizableTreeBar::OnItemExpendedAtInfoTree(NMHDR * pNotifyStruct,LRESULT * pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNotifyStruct;

	HTREEITEM currentItem = pNMTreeView->itemNew.hItem;
	if (currentItem == NULL) return;

	if (infoTreeCtrl->ItemHasChildren(currentItem) == FALSE) return;

	UINT state = infoTreeCtrl->GetItemState(currentItem,TVIF_STATE);
	if (state & TVIS_EXPANDED) {
		infoTreeCtrl->SetItemImage(currentItem,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
	} else {
		infoTreeCtrl->SetItemImage(currentItem,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	}

    *pResult = 0;
}

void CResizableTreeBar::OnItemExpendedAtFileTree(NMHDR * pNotifyStruct,LRESULT * pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNotifyStruct;

	HTREEITEM currentItem = pNMTreeView->itemNew.hItem;
	if (currentItem == NULL) return;

	if (fileTreeCtrl->ItemHasChildren(currentItem) == FALSE) return;

	UINT state = fileTreeCtrl->GetItemState(currentItem,TVIF_STATE);
	if (state & TVIS_EXPANDED) {
		fileTreeCtrl->SetItemImage(currentItem,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
	} else {
		fileTreeCtrl->SetItemImage(currentItem,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	}

    *pResult = 0;
}

void CResizableTreeBar::OnItemExpendedAtDiagramTree(NMHDR * pNotifyStruct,LRESULT * pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNotifyStruct;

	HTREEITEM currentItem = pNMTreeView->itemNew.hItem;
	if (currentItem == NULL) return;

	if (diagramTreeCtrl->ItemHasChildren(currentItem) == FALSE) return;
	if (diagramTreeCtrl->GetItemData(currentItem) != -1) return;

	
	UINT state = diagramTreeCtrl->GetItemState(currentItem,TVIF_STATE);
	if (state & TVIS_EXPANDED) {
		diagramTreeCtrl->SetItemImage(currentItem,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
	} else {
		diagramTreeCtrl->SetItemImage(currentItem,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	}

    *pResult = 0;
}

void CResizableTreeBar::ShowSelTabWindow()
{    
    int nSel = m_TabCtrl.GetCurSel();   
    ASSERT(nSel != -1);
    
    for (int i = 0; i < m_TabCtrl.GetItemCount(); i++)
    {
        GetTabWindow(i)->ShowWindow(i == nSel ? SW_SHOW : SW_HIDE);
    }
}

////////////////////////////////////////////////////////////////////////////
// CResizableTreeBar message handlers

int CResizableTreeBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CResizableControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    CRect rect(0,0,0,0);
    // create a tab control with tree controls inside it....
    if (!m_TabCtrl.Create(WS_CHILD | WS_VISIBLE | TCS_BOTTOM | TCS_MULTILINE,
                        rect, this, IDC_TREEBAR_TAB))
    {
        TRACE("Failed to create Tab control\n");
        return -1;
    }

    m_ImgList.Create(IDR_TREEBAR_IMAGE, 17, 1, RGB(192, 192, 192));
    
    m_TabCtrl.SetFont(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT))); 
    m_TabCtrl.SetImageList(&m_ImgList);


    // populate the tab control ....
    static LPCTSTR szTabName[] = { _T("ClassView"), _T("DiagramView"), _T("FileView"), _T("InfoView") };
    DWORD dwStyle = WS_BORDER | WS_CHILD | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT ;

	// Class Tree Control
	classTreeCtrl = new CTreeCtrl;
	if (!classTreeCtrl->Create(dwStyle, rect, this, 0))
		return -1;      // failed to create tree control
	classTreeCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	TC_ITEM TCI_CLASS;
	TCI_CLASS.mask = TCIF_TEXT | TCIF_PARAM | TCIF_IMAGE;
	TCI_CLASS.pszText = (char *)szTabName[0];
	TCI_CLASS.lParam = (LPARAM)classTreeCtrl;
	TCI_CLASS.iImage = 0;
	VERIFY(m_TabCtrl.InsertItem(0, &TCI_CLASS) != -1);

	_classViewImageList.Create(IDR_WS_CLASSVIEW_BITMAP, 15, 1, RGB(255, 255, 255));
	classTreeCtrl->SetImageList(&_classViewImageList,TVSIL_NORMAL);
	classTreeCtrl->SetBkColor(TREE_BAR_BK_COLOR);

	HTREEITEM hRoot = classTreeCtrl->InsertItem(_T("Classes"));
	classTreeCtrl->SetItemImage(hRoot,PROJECT_BM_ID,PROJECT_BM_ID);
	classTreeCtrl->SetItemData(hRoot,ROOT_ID);

	// Diagram Tree Control
	diagramTreeCtrl = new CTreeCtrl;
	if (!diagramTreeCtrl->Create(dwStyle, rect, this, IDC_DIAGRAMTREECTRL))
		return -1;      // failed to create tree control
	diagramTreeCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	TC_ITEM TCI_DIAGRAM;
	TCI_DIAGRAM.mask = TCIF_TEXT | TCIF_PARAM | TCIF_IMAGE;
	TCI_DIAGRAM.pszText = (char *)szTabName[1];
	TCI_DIAGRAM.lParam = (LPARAM)diagramTreeCtrl;
	TCI_DIAGRAM.iImage = 1;
	VERIFY(m_TabCtrl.InsertItem(1, &TCI_DIAGRAM) != -1);

	_diagramViewImageList.Create(IDR_WS_DIAGRAMVIEW_BITMAP, 17, 1, RGB(255, 255, 255));
	diagramTreeCtrl->SetImageList(&_diagramViewImageList,TVSIL_NORMAL);
	diagramTreeCtrl->SetBkColor(TREE_BAR_BK_COLOR);

	hRoot = diagramTreeCtrl->InsertItem(_T("Diagrams"));
	diagramTreeCtrl->SetItemImage(hRoot,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hRoot,-1);
	HTREEITEM hTmp = diagramTreeCtrl->InsertItem("Class Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Use Case Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Sequence Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Collaboration Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("State Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Activity Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);
	hTmp = diagramTreeCtrl->InsertItem("Deployment Diagram",hRoot);
	diagramTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	diagramTreeCtrl->SetItemData(hTmp,-1);

	// File Tree Control
	fileTreeCtrl = new CTreeCtrl;
	if (!fileTreeCtrl->Create(dwStyle, rect, this, IDC_FILETREECTRL))
		return -1;      // failed to create tree control
	fileTreeCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	TC_ITEM TCI_FILE;
	TCI_FILE.mask = TCIF_TEXT | TCIF_PARAM | TCIF_IMAGE;
	TCI_FILE.pszText = (char *)szTabName[2];
	TCI_FILE.lParam = (LPARAM)fileTreeCtrl;
	TCI_FILE.iImage = 2;
	VERIFY(m_TabCtrl.InsertItem(2, &TCI_FILE) != -1);

	_fileViewImageList.Create(IDR_WS_FILEVIEW_BITMAP, 17, 1, RGB(255, 255, 255));
	fileTreeCtrl->SetImageList(&_fileViewImageList,TVSIL_NORMAL);
	fileTreeCtrl->SetBkColor(TREE_BAR_BK_COLOR);

	hRoot = fileTreeCtrl->InsertItem(_T("Files"));
	fileTreeCtrl->SetItemImage(hRoot,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	fileTreeCtrl->SetItemData(hRoot,-1);
	hTmp = fileTreeCtrl->InsertItem("Source Files",hRoot);
	fileTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	fileTreeCtrl->SetItemData(hTmp,-1);
	hTmp = fileTreeCtrl->InsertItem("Header Files",hRoot);
	fileTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	fileTreeCtrl->SetItemData(hTmp,-1);
	hTmp = fileTreeCtrl->InsertItem("Text Files",hRoot);
	fileTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	fileTreeCtrl->SetItemData(hTmp,-1);

	// Info Tree Control
	infoTreeCtrl = new CTreeCtrl;
	if (!infoTreeCtrl->Create(dwStyle, rect, this, IDC_INFOTREECTRL))
		return -1;      // failed to create tree control
	infoTreeCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	TC_ITEM TCI_INFO;
	TCI_INFO.mask = TCIF_TEXT | TCIF_PARAM | TCIF_IMAGE;
	TCI_INFO.pszText = (char *)szTabName[3];
	TCI_INFO.lParam = (LPARAM)infoTreeCtrl;
	TCI_INFO.iImage = 3;
	VERIFY(m_TabCtrl.InsertItem(3, &TCI_INFO) != -1);

	_infoViewImageList.Create(IDR_WS_INFOVIEW_BITMAP, 17, 1, RGB(255, 255, 255));
	infoTreeCtrl->SetImageList(&_infoViewImageList,TVSIL_NORMAL);
	infoTreeCtrl->SetBkColor(TREE_BAR_BK_COLOR);

	hRoot = infoTreeCtrl->InsertItem(_T("How to ..."));
	infoTreeCtrl->SetItemImage(hRoot,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	infoTreeCtrl->SetItemData(hRoot,-1);
	hTmp = infoTreeCtrl->InsertItem("draw diagrams",hRoot);
	infoTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	infoTreeCtrl->SetItemData(hTmp,-1);
	hTmp = infoTreeCtrl->InsertItem("generate code",hRoot);
	infoTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	infoTreeCtrl->SetItemData(hTmp,-1);
	hTmp = infoTreeCtrl->InsertItem("reverse code",hRoot);
	infoTreeCtrl->SetItemImage(hTmp,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	infoTreeCtrl->SetItemData(hTmp,-1);

    ShowSelTabWindow();
    
	return 0;
}

void CResizableTreeBar::OnDestroy() 
{
    // delete the CWnd object belonging to the child window
    for (int i = 0; i < m_TabCtrl.GetItemCount(); i++)
    {
        delete GetTabWindow(i);
    }
    
    CResizableControlBar::OnDestroy();
}

CMenu *CResizableTreeBar::getDeleteRelationshipMenu() {
	return _allPopupMenu.GetSubMenu(RELATIONSHIP_POPUP_ID);
}

void CResizableTreeBar::checkOrUncheckDockingMenu(CMenu *aMenu)
{
	DWORD dwDockStyle = m_dwDockStyle & CBRS_ALIGN_ANY;
	BOOL bMDIFloating = FALSE;
	CFrameWnd *pParentFrame = GetParentFrame();
	if (IsFloating())
	{
		if (pParentFrame != NULL && pParentFrame->IsKindOf(RUNTIME_CLASS(CResizableFloatWnd)))
		{
			bMDIFloating = TRUE;
		}
	}
	if (!bMDIFloating && (dwDockStyle != 0 || m_dwAllowDockingState != 0)) {
		if (dwDockStyle != 0) {
			aMenu->CheckMenuItem(ID_BAR_ALLOWDOCKING,MF_BYCOMMAND|MF_CHECKED);
		} else {
			aMenu->CheckMenuItem(ID_BAR_ALLOWDOCKING,MF_BYCOMMAND|MF_UNCHECKED);
		}
	} else {
		aMenu->CheckMenuItem(ID_BAR_ALLOWDOCKING,MF_BYCOMMAND|MF_UNCHECKED);
	}
}

void CResizableTreeBar::popupTreeBarMenu(CTreeCtrl* currentCtrl,HTREEITEM pItem,CPoint point)
{
	_selectedCtrlBeforePopup = currentCtrl;
	_selectedItemBeforePopup = pItem;

	if (currentCtrl == classTreeCtrl) {
		if (currentCtrl->GetItemData(pItem) == PROJECT_BM_ID) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(PROJECT_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			if (theAppPtr->workspaceName.GetLength() == 0) {
				subMenu->EnableMenuItem(ID_CLASS_ROOT_NEW_PACKAGE,MF_BYCOMMAND|MF_GRAYED);
			} else {
				subMenu->EnableMenuItem(ID_CLASS_ROOT_NEW_PACKAGE,MF_BYCOMMAND|MF_ENABLED);
			}
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		} else if (currentCtrl->GetItemData(pItem) == PACKAGE_ID) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(PACKAGE_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		} else if (currentCtrl->GetItemData(pItem) == CLASS_ID) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(CLASS_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		} else if (currentCtrl->GetItemData(pItem) == MEMBERFUNCTION_ID) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(FUNCTION_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		} else if (currentCtrl->GetItemData(pItem) == DATAMEMBER_ID) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(DATA_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		}
	} else if (currentCtrl == diagramTreeCtrl) {
		if (currentCtrl->GetRootItem() == currentCtrl->GetParentItem(pItem)) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(DIAGRAM_TYPE_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		} else if (pItem != NULL) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(DIAGRAM_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		}
	} else if (currentCtrl == fileTreeCtrl) {
		if (currentCtrl->GetRootItem() == currentCtrl->GetParentItem(pItem)) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(FILE_TYPE_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			CString language = theAppPtr->projectLanguage;
			CString itemName = currentCtrl->GetItemText(pItem);
			if (language.CompareNoCase("Java") == 0 &&
				itemName.CompareNoCase("Header Files") == 0) {
				UINT id = subMenu->GetMenuItemID(0);
				subMenu->EnableMenuItem(id,MF_GRAYED);
			} else {
				UINT id = subMenu->GetMenuItemID(0);
				subMenu->EnableMenuItem(id,MF_ENABLED);
			}
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		} else if (pItem != NULL &&
			pItem != currentCtrl->GetRootItem()) {
			CMenu *subMenu = _allPopupMenu.GetSubMenu(FILE_POPUP_ID);
			checkOrUncheckDockingMenu(subMenu);
			subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		}
	}
}

void CResizableTreeBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CTreeCtrl *currentCtrl = NIL;
	int currentSel = m_TabCtrl.GetCurSel();
	if (currentSel == CLASS_TREE_SEL) {
		currentCtrl = classTreeCtrl;
		HTREEITEM pItem = currentCtrl->GetFirstVisibleItem();
		while (pItem != NULL) {
			RECT tmpRect;
			currentCtrl->GetItemRect(pItem,&tmpRect,TRUE);
			CRect boundRect(tmpRect);
			CPoint testPoint(point);
			GetTabWindow(CLASS_TREE_SEL)->ScreenToClient(&testPoint);
			if (boundRect.PtInRect(testPoint)) {
				currentCtrl->SelectItem(pItem);
				popupTreeBarMenu(currentCtrl,pItem,point);
				return;
			}
			pItem = currentCtrl->GetNextVisibleItem(pItem);
		}
	} else if (currentSel == DIAGRAM_TREE_SEL) {
		currentCtrl = diagramTreeCtrl;
		HTREEITEM pItem = currentCtrl->GetFirstVisibleItem();
		while (pItem != NULL) {
			RECT tmpRect;
			currentCtrl->GetItemRect(pItem,&tmpRect,TRUE);
			CRect boundRect(tmpRect);
			CPoint testPoint(point);
			GetTabWindow(DIAGRAM_TREE_SEL)->ScreenToClient(&testPoint);
			if (boundRect.PtInRect(testPoint)) {
				currentCtrl->SelectItem(pItem);
				if (pItem == currentCtrl->GetRootItem()) {
					CResizableControlBar::OnContextMenu(pWnd,point);
				} else {
					popupTreeBarMenu(currentCtrl,pItem,point);
				}
				return;
			}
			pItem = currentCtrl->GetNextVisibleItem(pItem);
		}
	} else if (currentSel == FILE_TREE_SEL) {
		currentCtrl = fileTreeCtrl;
		HTREEITEM pItem = currentCtrl->GetFirstVisibleItem();
		while (pItem != NULL) {
			RECT tmpRect;
			currentCtrl->GetItemRect(pItem,&tmpRect,TRUE);
			CRect boundRect(tmpRect);
			CPoint testPoint(point);
			GetTabWindow(FILE_TREE_SEL)->ScreenToClient(&testPoint);
			if (boundRect.PtInRect(testPoint)) {
				currentCtrl->SelectItem(pItem);
				if (pItem == currentCtrl->GetRootItem()) {
					CResizableControlBar::OnContextMenu(pWnd,point);
				} else {
					popupTreeBarMenu(currentCtrl,pItem,point);
				}
				return;
			}
			pItem = currentCtrl->GetNextVisibleItem(pItem);
		}
	} 
	CResizableControlBar::OnContextMenu(pWnd,point);
}

void CResizableTreeBar::deleteClassMember(UINT id,HTREEITEM pItem)
{
	HTREEITEM hParent = classTreeCtrl->GetParentItem(pItem);
	CString className = classTreeCtrl->GetItemText(hParent);
	HTREEITEM hGrandParent = classTreeCtrl->GetParentItem(hParent);
	CString packageName = classTreeCtrl->GetItemText(hGrandParent);
	CString diagramName = packageName+_PAK_EXT;
	COODView *theView = mainFramePtr->getActiveCOODView();
	if (theView == NIL) {
		mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	}
	int index = 0;
	HTREEITEM pPrev = classTreeCtrl->GetPrevSiblingItem(pItem);
	while (pPrev != NULL) {
		if (classTreeCtrl->GetItemData(pPrev) != id) break;
		index++;
		pPrev = classTreeCtrl->GetPrevSiblingItem(pPrev);
	}
	ClassContent *theContent = 
		theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(className);
	if (id == MEMBERFUNCTION_ID) {
		theContent->deleteMemberFunction(index);
	} else if (id == DATAMEMBER_ID) {
		theContent->deleteDataMember(index);
	}
	classTreeCtrl->DeleteItem(pItem);
	invalidateCurrentTabCtrl(classTreeCtrl);
	theAppPtr->pCOODClassDoc->getClassFiguresLibrary()->replaceFieldTextContent(packageName,className,NIL,theView);
	theAppPtr->pCOODClassDoc->SetModifiedFlag();
	theAppPtr->pCOODClassDoc->UpdateAllViews((CView *)NIL);
	theAppPtr->deactivateAllPropertyDlgs();
}

BOOL CResizableTreeBar::tryToDeleteSelectedItem()
{
	int currentSel = m_TabCtrl.GetCurSel();
	if (currentSel == CLASS_TREE_SEL) {
		HTREEITEM pItem = classTreeCtrl->GetSelectedItem();
		if (pItem == NULL) return FALSE;
		CString itemName = classTreeCtrl->GetItemText(pItem);
		if (classTreeCtrl->GetItemData(pItem) == PACKAGE_ID) {
			if (classTreeCtrl->ItemHasChildren(pItem)) {
				char msg[BUFSIZ];
sprintf_s(msg,BUFSIZ,"%s could not be deleted.\r\n\
You must delete all classes\r\n\
before deleting the package.",itemName);
				WarningMsg(msg);
				return TRUE;
			}
			CString packageDiagramName = itemName + _PAK_EXT;
			ClassFigureLibrary *theLibrary = theAppPtr->pCOODClassDoc->getClassFiguresLibrary();
			FigureList * figures = theLibrary->figures(packageDiagramName);
			if (figures->nOfList() > 0) {
				char msg[BUFSIZ];
sprintf_s(msg,BUFSIZ,"%s could not be deleted.\r\n\
You must delete all graphic entities\r\n\
before deleting the package.",itemName);
				WarningMsg(msg);
				return TRUE;
			}
			theAppPtr->pCOODClassDoc->destroyClassFrameWindow(packageDiagramName);
			PackageLibrary *allContents = theAppPtr->pCOODClassDoc->getAllClassContents();
			CString packageName = itemName;
			allContents->deletePackage(packageName);
			classTreeCtrl->DeleteItem(pItem);
			deleteADiagram(packageDiagramName);
			invalidateCurrentTabCtrl(classTreeCtrl);
			theAppPtr->pCOODClassDoc->SetModifiedFlag();
		} else if (classTreeCtrl->GetItemData(pItem) == CLASS_ID) {
			CString packageName;
			ClassFigureLibrary *theLibrary = theAppPtr->pCOODClassDoc->getClassFiguresLibrary();
			BOOL exists = theLibrary->hasClassTemplate(itemName,packageName);
			if (exists == TRUE) {
				char msg[BUFSIZ];
sprintf_s(msg,BUFSIZ,"%s could not be deleted.\r\n\
%s is used in %s package.\r\n\
You must delete the class in %s diagram\r\n\
before deleting it on this browser.",itemName,itemName,packageName,packageName);
				WarningMsg(msg);
			} else {
				PackageLibrary *allContents = theAppPtr->pCOODClassDoc->getAllClassContents();
				packageName = classTreeCtrl->GetItemText(classTreeCtrl->GetParentItem(pItem));
				allContents->deleteClassContent(packageName,itemName);
				classTreeCtrl->DeleteItem(pItem);
				theAppPtr->pCOODClassDoc->deleteAllRelationshipWithClassName(itemName);
				invalidateCurrentTabCtrl(classTreeCtrl);
				theAppPtr->pCOODClassDoc->SetModifiedFlag();
			}
		} else if (classTreeCtrl->GetItemData(pItem) == MEMBERFUNCTION_ID) {
			deleteClassMember(MEMBERFUNCTION_ID,pItem);
		} else if (classTreeCtrl->GetItemData(pItem) == DATAMEMBER_ID) {
			deleteClassMember(DATAMEMBER_ID,pItem);
		}
		return TRUE;
	} else if (currentSel == DIAGRAM_TREE_SEL) {
		HTREEITEM pItem = diagramTreeCtrl->GetSelectedItem();
		if (pItem == NULL) return FALSE;
		if (diagramTreeCtrl->GetItemData(pItem) != -1) {
			_selectedCtrlBeforePopup = diagramTreeCtrl;
			_selectedItemBeforePopup = pItem;
			OnDiagramDelete();
			return TRUE;
		}
	} else if (currentSel == FILE_TREE_SEL) {
		HTREEITEM pItem = fileTreeCtrl->GetSelectedItem();
		if (pItem == NULL) return FALSE;
		if (fileTreeCtrl->GetItemData(pItem) != -1) {
			_selectedCtrlBeforePopup = fileTreeCtrl;
			_selectedItemBeforePopup = pItem;
			OnFileMenuDelete();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CResizableTreeBar::showClassPropDlg(CTreeCtrl* currentCtrl,HTREEITEM pItem)
{
	ClassPropDlg *classDlg = theAppPtr->getActiveClassPropDlg();
	if (classDlg == NIL) {
		return FALSE;
	}
	if ((classDlg->GetStyle() & WS_VISIBLE) == 0) {
		classDlg->ShowWindow(SW_SHOW);
	}
	HTREEITEM hParent = currentCtrl->GetParentItem(pItem);
	CString packageName = currentCtrl->GetItemText(hParent);
	CString className = currentCtrl->GetItemText(pItem);
	CString diagramName = packageName+_PAK_EXT;
	COODView *theView = mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	if (theView == NIL) return FALSE;
	ClassContent *theContent = 
		theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(className);
	classDlg->loadFromClassContent(theView,theContent,className,packageName);
	return TRUE;
}

BOOL CResizableTreeBar::showFunctionMemberPropDlg(CTreeCtrl* currentCtrl,HTREEITEM pItem)
{
	MemberPropDlg *memberDlg = theAppPtr->getActiveMethodPropDlg();
	if (memberDlg == NIL) {
		return FALSE;
	}
	if ((memberDlg->GetStyle() & WS_VISIBLE) == 0) {
		memberDlg->ShowWindow(SW_SHOW);
	}
	theAppPtr->deactivateClassPropertyDlgs();
	HTREEITEM hParent = currentCtrl->GetParentItem(pItem);
	CString className = currentCtrl->GetItemText(hParent);
	HTREEITEM hGrandParent = currentCtrl->GetParentItem(hParent);
	CString packageName = currentCtrl->GetItemText(hGrandParent);
	CString diagramName = packageName+_PAK_EXT;
	COODView *theView = mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	if (theView == NIL) return FALSE;
	CString browserString = currentCtrl->GetItemText(pItem);
	int index = 0;
	HTREEITEM pPrev = currentCtrl->GetPrevSiblingItem(pItem);
	while (pPrev != NULL) {
		if (currentCtrl->GetItemData(pPrev) != MEMBERFUNCTION_ID) break;
		index++;
		pPrev = currentCtrl->GetPrevSiblingItem(pPrev);
	}
	ClassContent *theContent = 
		theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(className);
	ClassTextLine *theLine = theContent->getMemberFunctionLine(index,browserString);
	memberDlg->loadFromClassTextLine(theView,theLine,index,theContent,className,packageName);
	return TRUE;
}

BOOL CResizableTreeBar::showDataMemberPropDlg(CTreeCtrl* currentCtrl,HTREEITEM pItem)
{
	MemberPropDlg *memberDlg = theAppPtr->getActiveVarPropDlg();
	if (memberDlg == NIL) {
		return FALSE;
	}
	if ((memberDlg->GetStyle() & WS_VISIBLE) == 0) {
		memberDlg->ShowWindow(SW_SHOW);
	}
	theAppPtr->deactivateClassPropertyDlgs();
	HTREEITEM hParent = currentCtrl->GetParentItem(pItem);
	CString className = currentCtrl->GetItemText(hParent);
	HTREEITEM hGrandParent = currentCtrl->GetParentItem(hParent);
	CString packageName = currentCtrl->GetItemText(hGrandParent);
	CString diagramName = packageName+_PAK_EXT;
	COODView *theView = mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	if (theView == NIL) return FALSE;
	CString browserString = currentCtrl->GetItemText(pItem);
	int index = 0;
	HTREEITEM pPrev = currentCtrl->GetPrevSiblingItem(pItem);
	while (pPrev != NULL) {
		if (currentCtrl->GetItemData(pPrev) != DATAMEMBER_ID) break;
		index++;
		pPrev = currentCtrl->GetPrevSiblingItem(pPrev);
	}
	ClassContent *theContent = 
		theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(className);
	ClassTextLine *theLine = theContent->getDataMemberLine(index,browserString);
	memberDlg->loadFromClassTextLine(theView,theLine,index,theContent,className,packageName);
	return TRUE;
}

BOOL CResizableTreeBar::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && (LOWORD(pMsg->wParam) == VK_DELETE)) {
		BOOL processed = tryToDeleteSelectedItem();
		if (processed == TRUE) {
			return -1;
		} else {
			return CResizableControlBar::PreTranslateMessage(pMsg);
		}
	} 
	if (pMsg->message != WM_LBUTTONDBLCLK) 
		return CResizableControlBar::PreTranslateMessage(pMsg);
	CPoint point = pMsg->pt;
	int currentSel = m_TabCtrl.GetCurSel();
	if (currentSel == CLASS_TREE_SEL) {
		HTREEITEM pItem = classTreeCtrl->GetFirstVisibleItem();
		while (pItem != NULL) {
			RECT tmpRect;
			classTreeCtrl->GetItemRect(pItem,&tmpRect,TRUE);
			CRect boundRect(tmpRect);
			CPoint testPoint(point);
			GetTabWindow(CLASS_TREE_SEL)->ScreenToClient(&testPoint);
			if (boundRect.PtInRect(testPoint)) {
				if (classTreeCtrl->GetItemData(pItem) == PACKAGE_ID) {
					/* 노드가 열린 상태인가를 알아보는 샘플 코드기 때문에 아까워서 남겨놈
					UINT state = diagramTreeCtrl->GetItemState(pItem,TVIF_STATE);
					if (!(state&TVIS_EXPANDED)) {
						mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramTreeCtrl->GetItemText(pItem)+".pac");
					}
					*/
					mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramTreeCtrl->GetItemText(pItem)+".pac");
					return -1;
				} else if (classTreeCtrl->GetItemData(pItem) == CLASS_ID) {
					if (showClassPropDlg(classTreeCtrl,pItem) == FALSE) {
						return CResizableControlBar::PreTranslateMessage(pMsg);
					}
					return -1;
				} else if (classTreeCtrl->GetItemData(pItem) == MEMBERFUNCTION_ID) {
					if (showFunctionMemberPropDlg(classTreeCtrl,pItem) == FALSE) {
						return CResizableControlBar::PreTranslateMessage(pMsg);
					}
					return -1;
				} else if (classTreeCtrl->GetItemData(pItem) == DATAMEMBER_ID) {
					if (showDataMemberPropDlg(classTreeCtrl,pItem) == FALSE) {
						return CResizableControlBar::PreTranslateMessage(pMsg);
					}
					return -1;
				}
			}
			pItem = classTreeCtrl->GetNextVisibleItem(pItem);
		}
	} else if (currentSel == DIAGRAM_TREE_SEL) {
		HTREEITEM pItem = diagramTreeCtrl->GetFirstVisibleItem();
		while (pItem != NULL) {
			RECT tmpRect;
			diagramTreeCtrl->GetItemRect(pItem,&tmpRect,TRUE);
			CRect boundRect(tmpRect);
			CPoint testPoint(point);
			GetTabWindow(DIAGRAM_TREE_SEL)->ScreenToClient(&testPoint);
			if (boundRect.PtInRect(testPoint)) {
				if (diagramTreeCtrl->GetItemData(pItem) == -1) {
					return CResizableControlBar::PreTranslateMessage(pMsg);
				} else {
					mainFramePtr->openNamedFile(diagramTreeCtrl->GetItemData(pItem),diagramTreeCtrl->GetItemText(pItem));
					return -1;
				}
			}
			pItem = diagramTreeCtrl->GetNextVisibleItem(pItem);
		}
	} else if (currentSel == FILE_TREE_SEL) {
		HTREEITEM pItem = fileTreeCtrl->GetFirstVisibleItem();
		while (pItem != NULL) {
			RECT tmpRect;
			fileTreeCtrl->GetItemRect(pItem,&tmpRect,TRUE);
			CRect boundRect(tmpRect);
			CPoint testPoint(point);
			GetTabWindow(FILE_TREE_SEL)->ScreenToClient(&testPoint);
			if (boundRect.PtInRect(testPoint)) {
				if (fileTreeCtrl->GetItemData(pItem) == -1) {
					return CResizableControlBar::PreTranslateMessage(pMsg);
				} else {
					CString itemName = fileTreeCtrl->GetItemText(pItem);
					CString fullName = theAppPtr->projectCodegenTargetDir + itemName;
					mainFramePtr->openTextFile(fullName,itemName);
					return -1;
				}
			}
			pItem = fileTreeCtrl->GetNextVisibleItem(pItem);
		}
	}
	return CResizableControlBar::PreTranslateMessage(pMsg);
}

void CResizableTreeBar::OnDataProperties() 
{
	// TODO: Add your command handler code here
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to show property dialog.");
		return;
	}
	showDataMemberPropDlg(_selectedCtrlBeforePopup,_selectedItemBeforePopup);
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnFunctionProperties() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to show property dialog.");
		return;
	}
	showFunctionMemberPropDlg(_selectedCtrlBeforePopup,_selectedItemBeforePopup);
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}


void CResizableTreeBar::OnClassProperties() 
{
	// TODO: Add your command handler code here
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to show property dialog.");
		return;
	}
	showClassPropDlg(_selectedCtrlBeforePopup,_selectedItemBeforePopup);
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnClassGoToDefinition() 
{
	// TODO: Add your command handler code here
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to find class.");
		return;
	}
	if (_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup) != CLASS_ID) {
		ErrorMsg("Something wrong to find class.");
		return;
	}
	HTREEITEM hParent = _selectedCtrlBeforePopup->GetParentItem(_selectedItemBeforePopup);
	CString packageName = _selectedCtrlBeforePopup->GetItemText(hParent);
	CString className = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString diagramName = packageName+_PAK_EXT;
	COODView *theView = mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	if (theView == NIL) {
		ErrorMsg("Something wrong to find class.");
		return;
	}
	ClassTemplate *pClass = NIL;
	FigureList *figures = theView->figures();
	Figure *aFigure = figures->getFirst();
	while(aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *clss = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			clss->getName(buffer,BUFSIZ);
			CString aName = buffer;
			if (className.CompareNoCase(aName) == 0) {
				pClass = clss;
				break;
			}
		}
		aFigure = figures->getNext();
	}
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;

	if (pClass == NIL) {
		char buffer[BUFSIZ];
		sprintf_s(buffer,BUFSIZ,"Can't find %s class in %s diagram.",className,diagramName);
		WarningMsg(buffer);
		return;
	}

	theView->showFigureOnCenterOfView(pClass);
}

void CResizableTreeBar::OnPackageNewClass() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to create a class.");
		return;
	}
	if (_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup) != PACKAGE_ID) {
		ErrorMsg("Something wrong to create a class.");
		return;
	}
	CString packageName = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString diagramName = packageName+_PAK_EXT;

	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;

	QueryTextDlg askDlg(FOR_CLASS,"Type class name:");
	UINT ans = askDlg.DoModal();
	if (ans == IDCANCEL) return;
	CString className = askDlg.m_editAnswer;
	if (className.IsEmpty()) return;

	PackageLibrary *allClassContents = theAppPtr->pCOODClassDoc->getAllClassContents();
	ClassContent *classContent = 
		allClassContents->getClassContentFor(className);
	if (classContent != NIL) {
		CString packName;
		theAppPtr->pCOODClassDoc->getAllClassContents()->getPackageNameFor(className,packName);
		char msg[BUFSIZ];
		sprintf_s(msg,BUFSIZ,"%s is already exists in %s package.",className,packName);
		WarningMsg(msg);
		return;
	}
	insertClass(packageName,className,NIL);
	classContent = 
		allClassContents->registerClassContent(packageName,className,NIL);
	theAppPtr->pCOODClassDoc->SetModifiedFlag();

	if (ans == IDOK) return;

	// Display properties dialog: ans == IDMORE
	ClassPropDlg *classDlg = theAppPtr->getActiveClassPropDlg();
	if (classDlg == NIL) {
		return;
	}
	if ((classDlg->GetStyle() & WS_VISIBLE) == 0) {
		classDlg->ShowWindow(SW_SHOW);
	}
	COODView *theView = mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	if (theView == NIL) return;
	classDlg->loadFromClassContent(theView,classContent,className,packageName);
}

void CResizableTreeBar::OnClassAddMemberVariable() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to add a data member.");
		return;
	}
	if (_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup) != CLASS_ID) {
		ErrorMsg("Something wrong to add a data member.");
		return;
	}

	HTREEITEM hParent = _selectedCtrlBeforePopup->GetParentItem(_selectedItemBeforePopup);
	CString packageName = _selectedCtrlBeforePopup->GetItemText(hParent);
	CString className = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString diagramName = packageName+_PAK_EXT;
	
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;

	QueryTextDlg askDlg(FOR_DATA_MEMBER,"Type a data member as UML syntax:");
	UINT ans = askDlg.DoModal();
	if (ans == IDCANCEL) return;
	CString memberString = askDlg.m_editAnswer;
	if (memberString.IsEmpty()) return;

	PackageLibrary *allClassContents = theAppPtr->pCOODClassDoc->getAllClassContents();
	ClassContent *classContent = 
		allClassContents->getClassContentFor(className);
	if (classContent == NIL) {
		ErrorMsg("Can't find class definition.");
		return;
	}
	ClassTextLine *aLine = new ClassTextLine();
	classContent->varContent()->insertAtLast(aLine);
	aLine->setString(memberString);
	aLine->parseAsDataMember();
	COODView *theView = mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	if (theView == NIL) return;
	theAppPtr->pCOODClassDoc->getClassFiguresLibrary()->replaceFieldTextContent(packageName,className,NIL,theView);
	theAppPtr->pCOODClassDoc->SetModifiedFlag();
	theAppPtr->pCOODClassDoc->UpdateAllViews((CView *)NIL);
	replaceClass(packageName,className,classContent);
	theAppPtr->deactivateMemberPropertyDlgs();

	if (ans == IDOK) return;
	// Display properties dialog: ans == IDMORE
	MemberPropDlg *memberDlg = theAppPtr->getActiveVarPropDlg();
	if (memberDlg == NIL) {
		return;
	}
	if ((memberDlg->GetStyle() & WS_VISIBLE) == 0) {
		memberDlg->ShowWindow(SW_SHOW);
	}
	theAppPtr->deactivateClassPropertyDlgs();
	int index = classContent->nOfDataMembers()-1;
	memberDlg->loadFromClassTextLine(theView,aLine,index,classContent,className,packageName);
}

void CResizableTreeBar::OnClassAddMemberFunction() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to add a member function.");
		return;
	}
	if (_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup) != CLASS_ID) {
		ErrorMsg("Something wrong to add a member function.");
		return;
	}

	HTREEITEM hParent = _selectedCtrlBeforePopup->GetParentItem(_selectedItemBeforePopup);
	CString packageName = _selectedCtrlBeforePopup->GetItemText(hParent);
	CString className = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString diagramName = packageName+_PAK_EXT;
	
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;

	QueryTextDlg askDlg(FOR_DATA_MEMBER,"Type a member function as UML syntax:");
	UINT ans = askDlg.DoModal();
	if (ans == IDCANCEL) return;
	CString memberString = askDlg.m_editAnswer;
	if (memberString.IsEmpty()) return;

	PackageLibrary *allClassContents = theAppPtr->pCOODClassDoc->getAllClassContents();
	ClassContent *classContent = 
		allClassContents->getClassContentFor(className);
	if (classContent == NIL) {
		ErrorMsg("Can't find class definition.");
		return;
	}
	ClassTextLine *aLine = new ClassTextLine();
	classContent->methodContent()->insertAtLast(aLine);
	aLine->setString(memberString);
	aLine->parseAsMemberFunction();
	COODView *theView = mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	if (theView == NIL) return;
	theAppPtr->pCOODClassDoc->getClassFiguresLibrary()->replaceFieldTextContent(packageName,className,NIL,theView);
	theAppPtr->pCOODClassDoc->SetModifiedFlag();
	theAppPtr->pCOODClassDoc->UpdateAllViews((CView *)NIL);
	replaceClass(packageName,className,classContent);
	theAppPtr->deactivateMemberPropertyDlgs();

	if (ans == IDOK) return;
	// Display properties dialog: ans == IDMORE
	MemberPropDlg *memberDlg = theAppPtr->getActiveMethodPropDlg();
	if (memberDlg == NIL) {
		return;
	}
	if ((memberDlg->GetStyle() & WS_VISIBLE) == 0) {
		memberDlg->ShowWindow(SW_SHOW);
	}
	theAppPtr->deactivateClassPropertyDlgs();
	int index = classContent->nOfMemberFunctions()-1;
	memberDlg->loadFromClassTextLine(theView,aLine,index,classContent,className,packageName);
}

void CResizableTreeBar::OnPackageOpen() 
{
	// TODO: Add your command handler code here
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to open package.");
		return;
	}
	if (_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup) != PACKAGE_ID) {
		ErrorMsg("Something wrong to open package.");
		return;
	}
	CString packageName = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString diagramName = packageName+_PAK_EXT;

	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;

	BOOL okFlag = mainFramePtr->createNewClassFrame(theAppPtr->pClassDocTemplate,(CDocument *)theAppPtr->pCOODClassDoc,packageName);
	if (okFlag == FALSE) { 
		ErrorMsg("File creation fails.\r\nPlease contact to the vendor.");
		return;
	}
	POSITION pos = theAppPtr->pCOODClassDoc->activeViewNames.Find(diagramName);
	if (pos == NULL) {
		theAppPtr->pCOODClassDoc->insertViewName(diagramName);
		insertDiagramName(diagramName);
	}
}

void CResizableTreeBar::OnClassRelatedClasses() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to find related classes.");
		return;
	}
	if (_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup) != CLASS_ID) {
		ErrorMsg("Something wrong to find related classes.");
		return;
	}

	HTREEITEM hParent = _selectedCtrlBeforePopup->GetParentItem(_selectedItemBeforePopup);
	CString packageName = _selectedCtrlBeforePopup->GetItemText(hParent);
	CString className = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);

	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
	theAppPtr->theRelationTraverseDlg->setNameAndLoadClassInfo(className,packageName);
	if ((theAppPtr->theRelationTraverseDlg->GetStyle() & WS_VISIBLE) == 0) {
		theAppPtr->theRelationTraverseDlg->ShowWindow(SW_SHOW);
	}
}

void CResizableTreeBar::OnDiagramTypeNewDiagram() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to create a new diagram.");
		return;
	}
	if (_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup) != -1) {
		ErrorMsg("Something wrong to create a new diagram.");
		return;
	}

	mainFramePtr->onFileNew(_selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup));

	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnDiagramOpen() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to open a diagram.");
		return;
	}

	mainFramePtr->openNamedFile(_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup),
		_selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup));

	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnDiagramDelete() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to delete a diagram.");
		return;
	}

	if (_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup) == CLASS_DIAGRAM_BM_ID) {
		CString packageDiagramName = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
		CString packageName = packageDiagramName.Left(packageDiagramName.GetLength()-_EXT_LEN5);
		if (containsAnyClassInPackage(packageName) == TRUE) {
			char msg[BUFSIZ];
sprintf_s(msg,BUFSIZ,"%s could not be deleted.\r\n\
You must delete all classes\r\n\
before deleting the package.",packageName);
			WarningMsg(msg);
			_selectedCtrlBeforePopup = NIL;
			_selectedItemBeforePopup = NIL;
			return;
		}
		ClassFigureLibrary *theLibrary = theAppPtr->pCOODClassDoc->getClassFiguresLibrary();
		FigureList * figures = theLibrary->figures(packageDiagramName);
		if (figures->nOfList() > 0) {
			char msg[BUFSIZ];
sprintf_s(msg,BUFSIZ,"%s could not be deleted.\r\n\
You must delete all graphic entities\r\n\
before deleting the package.",packageName);
			WarningMsg(msg);
			_selectedCtrlBeforePopup = NIL;
			_selectedItemBeforePopup = NIL;
			return;
		}
		theAppPtr->pCOODClassDoc->destroyClassFrameWindow(packageDiagramName);
		PackageLibrary *allContents = theAppPtr->pCOODClassDoc->getAllClassContents();
		allContents->deletePackage(packageName);
		HTREEITEM hParent = _selectedCtrlBeforePopup->GetParentItem(_selectedItemBeforePopup);
		_selectedCtrlBeforePopup->DeleteItem(_selectedItemBeforePopup);
		if (!_selectedCtrlBeforePopup->ItemHasChildren(hParent)) {
			_selectedCtrlBeforePopup->SetItemImage(hParent,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
		}
		theAppPtr->pCOODClassDoc->SetModifiedFlag();
	} else {
		mainFramePtr->openNamedFile(_selectedCtrlBeforePopup->GetItemData(_selectedItemBeforePopup),
			_selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup));
		char buffer[BUFSIZ];
		CString dgmName = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
		sprintf_s(buffer,BUFSIZ,"Are you sure to delete %s diagram from the workspace ?",dgmName);
		int ans = YesNoMsg(buffer);
		if (ans != IDYES) {
			_selectedCtrlBeforePopup = NIL;
			_selectedItemBeforePopup = NIL;
			return;
		}
		CDocument *pDoc = mainFramePtr->getNamedDocument(dgmName);
		if (pDoc == NIL) {
			ErrorMsg("Can't find the document.");
			_selectedCtrlBeforePopup = NIL;
			_selectedItemBeforePopup = NIL;
			return;
		}
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
			ErrorMsg("Unexpected document type.");
			_selectedCtrlBeforePopup = NIL;
			_selectedItemBeforePopup = NIL;
			return;
		}
		COODCommonDoc *doc = (COODCommonDoc *)pDoc;
		CString pathName = doc->GetPathName();
		doc->SetModifiedFlag(FALSE);
		doc->onWindowClose(TRUE);
		if (!pathName.IsEmpty()) {
			theAppPtr->removeFileAndBackingUp(pathName);
		}
		HTREEITEM hParent = _selectedCtrlBeforePopup->GetParentItem(_selectedItemBeforePopup);
		_selectedCtrlBeforePopup->DeleteItem(_selectedItemBeforePopup);
		if (!_selectedCtrlBeforePopup->ItemHasChildren(hParent)) {
			_selectedCtrlBeforePopup->SetItemImage(hParent,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
		}
		theAppPtr->pCOODClassDoc->SetModifiedFlag();
	}
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnFileTypeNewFile() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to create a new file.");
		return;
	}

	CString typeName = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString extension;
	if (typeName.CompareNoCase("Source Files") == 0) {
		extension = theAppPtr->projectSFExtension;
	} else if (typeName.CompareNoCase("Header Files") == 0) {
		extension = theAppPtr->projectHFExtension;
	} else { // Text Files
		extension = ".txt";
	}
	typeName = "Text File";
	mainFramePtr->onFileNew(typeName,extension);
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnFileMenuOpen() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to open a file.");
		return;
	}
	CString itemName = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString fullName = theAppPtr->projectCodegenTargetDir + itemName;
	mainFramePtr->openTextFile(fullName,itemName);
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnFileMenuDelete() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to delete a file.");
		return;
	}

	CString itemName = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString fullName = theAppPtr->projectCodegenTargetDir + itemName;
	mainFramePtr->openTextFile(fullName,itemName);
	char buffer[BUFSIZ];
	sprintf_s(buffer,BUFSIZ,"Are you sure to delete %s file from the workspace ?",itemName);
	int ans = YesNoMsg(buffer);
	if (ans != IDYES) {
		_selectedCtrlBeforePopup = NIL;
		_selectedItemBeforePopup = NIL;
		return;
	}
	CDocument *pDoc = mainFramePtr->getNamedTextDocument(itemName);
	if (pDoc == NIL) {
		ErrorMsg("Can't find the file.");
		_selectedCtrlBeforePopup = NIL;
		_selectedItemBeforePopup = NIL;
		return;
	}
	if (!pDoc->IsKindOf(RUNTIME_CLASS(CTextDoc))) {
		ErrorMsg("Unexpected document type.");
		_selectedCtrlBeforePopup = NIL;
		_selectedItemBeforePopup = NIL;
		return;
	}
	CTextDoc *doc = (CTextDoc *)pDoc;
	CString pathName = doc->GetPathName();
	doc->SetModifiedFlag(FALSE);
	doc->onWindowClose(TRUE);
	if (!pathName.IsEmpty()) {
		theAppPtr->removeFileAndBackingUp(pathName);
	}
	HTREEITEM hParent = _selectedCtrlBeforePopup->GetParentItem(_selectedItemBeforePopup);
	_selectedCtrlBeforePopup->DeleteItem(_selectedItemBeforePopup);
	if (!_selectedCtrlBeforePopup->ItemHasChildren(hParent)) {
		_selectedCtrlBeforePopup->SetItemImage(hParent,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	}
	theAppPtr->pCOODClassDoc->SetModifiedFlag();
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnPackageProperties() 
{
	// TODO: Add your command handler code here
	
	if (_selectedCtrlBeforePopup == NIL && _selectedItemBeforePopup == NIL) {
		ErrorMsg("Something wrong to show property dialog.");
		return;
	}
	PackagePropDlg *packageDlg = theAppPtr->thePackagePropDlg;
	if (packageDlg == NIL) {
		return;
	}
	if ((packageDlg->GetStyle() & WS_VISIBLE) == 0) {
		packageDlg->ShowWindow(SW_SHOW);
	}
	CString packageName = _selectedCtrlBeforePopup->GetItemText(_selectedItemBeforePopup);
	CString diagramName = packageName+_PAK_EXT;
	mainFramePtr->openNamedFile(CLASS_DIAGRAM_BM_ID,diagramName);
	packageDlg->loadPackageInfo(diagramName);
	_selectedCtrlBeforePopup = NIL;
	_selectedItemBeforePopup = NIL;
}

void CResizableTreeBar::OnClassRootNewPackage() 
{
	// TODO: Add your command handler code here
	
	QueryTextDlg askDlg(FOR_PACKAGE,"Type package name:");
	UINT ans = askDlg.DoModal();
	if (ans == IDCANCEL) return;
	CString packageName = askDlg.m_editAnswer;
	if (packageName.IsEmpty()) return;

	BOOL okFlag = mainFramePtr->createNewClassFrame(theAppPtr->pClassDocTemplate,(CDocument *)theAppPtr->pCOODClassDoc,packageName);
	if (okFlag == FALSE) { 
		ErrorMsg("File creation fails.\r\nPlease contact to the vendor.");
		return;
	}
	CString newDgmName = packageName;
	newDgmName = newDgmName + _PAK_EXT;
	POSITION pos = theAppPtr->pCOODClassDoc->activeViewNames.Find(newDgmName);
	if (pos == NULL) {
		theAppPtr->pCOODClassDoc->insertViewName(newDgmName);
		mainFramePtr->m_wndTreeBar.insertDiagramName(newDgmName);
	}

	if (ans == IDOK) return;

	// Display properties dialog: ans == IDMORE
	PackagePropDlg *packageDlg = theAppPtr->thePackagePropDlg;
	if (packageDlg == NIL) {
		return;
	}
	if ((packageDlg->GetStyle() & WS_VISIBLE) == 0) {
		packageDlg->ShowWindow(SW_SHOW);
	}
	packageDlg->loadPackageInfo(newDgmName);
}


void CResizableTreeBar::OnMemberDelete() 
{
	// TODO: Add your command handler code here
	// 아래 함수는 CResizableTreeBar::tryToDeleteSelectedItem() 함수로 부터 카피 했음: 변경 시 주의

	HTREEITEM pItem = classTreeCtrl->GetSelectedItem();
	if (pItem == NULL) return;
	if (classTreeCtrl->GetItemData(pItem) == MEMBERFUNCTION_ID) {
		deleteClassMember(MEMBERFUNCTION_ID,pItem);
	} else if (classTreeCtrl->GetItemData(pItem) == DATAMEMBER_ID) {
		deleteClassMember(DATAMEMBER_ID,pItem);
	}
}

void CResizableTreeBar::OnClassDelete() 
{
	// TODO: Add your command handler code here
	// 아래 함수는 CResizableTreeBar::tryToDeleteSelectedItem() 함수로 부터 카피 했음: 변경 시 주의
	
	HTREEITEM pItem = classTreeCtrl->GetSelectedItem();
	if (pItem == NULL) return;
	if (classTreeCtrl->GetItemData(pItem) != CLASS_ID) return;
	CString itemName = classTreeCtrl->GetItemText(pItem);

	CString packageName;
	ClassFigureLibrary *theLibrary = theAppPtr->pCOODClassDoc->getClassFiguresLibrary();
	BOOL exists = theLibrary->hasClassTemplate(itemName,packageName);
	if (exists == TRUE) {
		char msg[BUFSIZ];
sprintf_s(msg,BUFSIZ,"%s could not be deleted.\r\n\
%s is used in %s package.\r\n\
You must delete the class in %s diagram\r\n\
before deleting it on this browser.",itemName,itemName,packageName,packageName);
		WarningMsg(msg);
	} else {
		PackageLibrary *allContents = theAppPtr->pCOODClassDoc->getAllClassContents();
		packageName = classTreeCtrl->GetItemText(classTreeCtrl->GetParentItem(pItem));
		allContents->deleteClassContent(packageName,itemName);
		classTreeCtrl->DeleteItem(pItem);
		theAppPtr->pCOODClassDoc->deleteAllRelationshipWithClassName(itemName);
		invalidateCurrentTabCtrl(classTreeCtrl);
		theAppPtr->pCOODClassDoc->SetModifiedFlag();
	}
}

void CResizableTreeBar::OnPackageDelete() 
{
	// TODO: Add your command handler code here
	// 아래 함수는 CResizableTreeBar::tryToDeleteSelectedItem() 함수로 부터 카피 했음: 변경 시 주의
	
	HTREEITEM pItem = classTreeCtrl->GetSelectedItem();
	if (pItem == NULL) return;
	if (classTreeCtrl->GetItemData(pItem) != PACKAGE_ID) return;
	CString itemName = classTreeCtrl->GetItemText(pItem);

	if (classTreeCtrl->ItemHasChildren(pItem)) {
		char msg[BUFSIZ];
sprintf_s(msg,BUFSIZ,"%s could not be deleted.\r\n\
You must delete all classes\r\n\
before deleting the package.",itemName);
		WarningMsg(msg);
		return;
	}
	CString packageDiagramName = itemName + _PAK_EXT;
	ClassFigureLibrary *theLibrary = theAppPtr->pCOODClassDoc->getClassFiguresLibrary();
	FigureList * figures = theLibrary->figures(packageDiagramName);
	if (figures->nOfList() > 0) {
		char msg[BUFSIZ];
sprintf_s(msg,BUFSIZ,"%s could not be deleted.\r\n\
You must delete all graphic entities\r\n\
before deleting the package.",itemName);
		WarningMsg(msg);
		return;
	}
	theAppPtr->pCOODClassDoc->destroyClassFrameWindow(packageDiagramName);
	PackageLibrary *allContents = theAppPtr->pCOODClassDoc->getAllClassContents();
	CString packageName = itemName;
	allContents->deletePackage(packageName);
	classTreeCtrl->DeleteItem(pItem);
	deleteADiagram(packageDiagramName);
	invalidateCurrentTabCtrl(classTreeCtrl);
	theAppPtr->pCOODClassDoc->SetModifiedFlag();	
}

void CResizableTreeBar::OnClassMigrate() 
{
	// TODO: Add your command handler code here
	HTREEITEM pItem = classTreeCtrl->GetSelectedItem();
	if (pItem == NULL) return;
	if (classTreeCtrl->GetItemData(pItem) != CLASS_ID) return;
	CString className = classTreeCtrl->GetItemText(pItem);
	HTREEITEM packItem = classTreeCtrl->GetParentItem(pItem);
	CString packName = classTreeCtrl->GetItemText(packItem);
	CStringList packNames;

	HTREEITEM hRoot = classTreeCtrl->GetRootItem();
	HTREEITEM hPackage = classTreeCtrl->GetChildItem(hRoot);
	while (hPackage != NULL) {
		packNames.AddTail(classTreeCtrl->GetItemText(hPackage));
		hPackage = classTreeCtrl->GetNextSiblingItem(hPackage);
	}

	CClassMigrationDlg aDlg(packName,packNames);
	UINT ans = aDlg.DoModal();
	if (ans != IDOK) return;
	if (aDlg.m_DestinationString.CompareNoCase(packName) == 0) return;

	CString newPack = aDlg.m_DestinationString;
	theAppPtr->deactivateAllPropertyDlgs();

	// 클래스 컨텐트를 찾아서 라이브러리에서 갈아끼우고 ...
	ClassContent *theContent = 
		theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(className);
	ClassLibrary *pOldLibrary = theAppPtr->pCOODClassDoc->getAllClassContents()->getPackage(packName);
	ClassLibrary *pNewLibrary = theAppPtr->pCOODClassDoc->getAllClassContents()->getPackage(newPack);
	pOldLibrary->remove(theContent);
	pNewLibrary->insert(theContent);

	// 트리뷰에서 넣고빼고 ...
	hRoot = classTreeCtrl->GetRootItem();
	hPackage = classTreeCtrl->GetChildItem(hRoot);
	while (hPackage != NULL) {
		if (classTreeCtrl->GetItemText(hPackage).CompareNoCase(newPack) == 0) {
			insertClass(hPackage,className,theContent);
			break;
		}
		hPackage = classTreeCtrl->GetNextSiblingItem(hPackage);
	}

	classTreeCtrl->DeleteItem(pItem);
	invalidateCurrentTabCtrl(classTreeCtrl);
	theAppPtr->pCOODClassDoc->setModifiedFlag();
}

