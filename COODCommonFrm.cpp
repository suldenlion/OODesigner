// COODCommonFrm.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "COODCommonFrm.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "COODView.h"
#include "COODCommonDoc.h"
#include "COODCntrlItem.h"
#include "COODCommonView.h"

extern UINT getFileName(LPCTSTR lpszPathName, LPTSTR lpszTitle);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL COODCommonFrm::ModelTBSupressedExplicitely = FALSE;
/////////////////////////////////////////////////////////////////////////////
// COODCommonFrm

IMPLEMENT_DYNCREATE(COODCommonFrm, CChildFrm)

COODCommonFrm::COODCommonFrm()
: CChildFrm()
{
	_modelToolBar = NIL;
	_resourceID = IDR_CLASSFRAME;
	_insertMenuID = _T("");
}

COODCommonFrm::~COODCommonFrm()
{
}

void COODCommonFrm::setModelIdentity(CString &extension)
{
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		_diagramType = "Class Diagram";
		_modelToolBar = &(mainFramePtr->classDiagramToolBar);
		_resourceID = IDR_CLASSFRAME;
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		_diagramType = "Use Case Diagram";
		_modelToolBar = &(mainFramePtr->usecaseDiagramToolBar);
		_resourceID = IDR_USECASEFRAME;
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		_diagramType = "Sequence Diagram";
		_modelToolBar = &(mainFramePtr->sequenceDiagramToolBar);
		_resourceID = IDR_SEQUENCEFRAME;
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		_diagramType = "Collaboration Diagram";
		_modelToolBar = &(mainFramePtr->collaborationDiagramToolBar);
		_resourceID = IDR_COLLABORATIONFRAME;
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		_diagramType = "State Diagram";
		_modelToolBar = &(mainFramePtr->stateDiagramToolBar);
		_resourceID = IDR_STATEFRAME;
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		_diagramType = "Activity Diagram";
		_modelToolBar = &(mainFramePtr->activityDiagramToolBar);
		_resourceID = IDR_ACTIVITYFRAME;
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		_diagramType = "Deployment Diagram";
		_modelToolBar = &(mainFramePtr->deploymentDiagramToolBar);
		_resourceID = IDR_DEPLOYMENTFRAME;
	}
}

BEGIN_MESSAGE_MAP(COODCommonFrm, CChildFrm)
	//{{AFX_MSG_MAP(COODCommonFrm)
	ON_COMMAND(ID_VIEW_MODEL_TOOLBAR, OnViewModelToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODEL_TOOLBAR, OnUpdateViewModelToolbar)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_OLE_ADAPT_VIEW_FRAME,COODCommonFrm::OnOleAdaptViewFrame)
END_MESSAGE_MAP()

CControlBar *COODCommonFrm::getModelToolBar()
{
	if (ModelTBSupressedExplicitely) return NIL;
	return _modelToolBar;
	/*
	CDocument *pDoc = GetActiveDocument();
	if (pDoc == NIL) return NIL;
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) return NIL;
	if (ModelTBSupressedExplicitely) return NIL;
	return &(mainFramePtr->classDiagramToolBar);
	*/
}

void COODCommonFrm::overwriteDocumentFile(COODCommonDoc *pDoc,CString &pathName)
{
	CString newName = pathName;
	char pathNameBuffer[BUFSIZ];
	char fileNameBuffer[BUFSIZ];
	strcpy_s(pathNameBuffer,BUFSIZ,pathName);
	getFileName(pathNameBuffer, fileNameBuffer);
	CString fileName = fileNameBuffer;

	CView *pView = GetActiveView();
	if (pView == NULL) return;
	if (!pView->IsKindOf(RUNTIME_CLASS(COODView))) return;
	COODView *pOODView = (COODView *)pView;

	CString fileExt = newName.Right(_EXT_LEN5);
	CDocument *docPtr = NIL; 
	if (fileExt.CompareNoCase(_PAK_EXT) == 0) {
		CDocument *pDocOld = CMainFrame::alreadyOpen(theAppPtr->pObjectDocTemplate,newName);
		if (pDocOld != NIL) return;
		docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pObjectDocTemplate,newName);
	} else if (fileExt.CompareNoCase(_USE_EXT) == 0) {
		CDocument *pDocOld = CMainFrame::alreadyOpen(theAppPtr->pUseCaseDocTemplate,newName);
		if (pDocOld != NIL) return;
		docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pUseCaseDocTemplate,newName);
	} else if (fileExt.CompareNoCase(_COL_EXT) == 0) {
		CDocument *pDocOld = CMainFrame::alreadyOpen(theAppPtr->pCollaborationDocTemplate,newName);
		if (pDocOld != NIL) return;
		docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pCollaborationDocTemplate,newName);
	} else if (fileExt.CompareNoCase(_SEQ_EXT) == 0) {
		CDocument *pDocOld = CMainFrame::alreadyOpen(theAppPtr->pSequenceDocTemplate,newName);
		if (pDocOld != NIL) return;
		docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pSequenceDocTemplate,newName);
	} else if (fileExt.CompareNoCase(_STA_EXT) == 0) {
		CDocument *pDocOld = CMainFrame::alreadyOpen(theAppPtr->pStateDocTemplate,newName);
		if (pDocOld != NIL) return;
		docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pStateDocTemplate,newName);
	} else if (fileExt.CompareNoCase(_ACT_EXT) == 0) {
		CDocument *pDocOld = CMainFrame::alreadyOpen(theAppPtr->pActivityDocTemplate,newName);
		if (pDocOld != NIL) return;
		docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pActivityDocTemplate,newName);
	} else if (fileExt.CompareNoCase(_DEP_EXT) == 0) {
		CDocument *pDocOld = CMainFrame::alreadyOpen(theAppPtr->pDeploymentDocTemplate,newName);
		if (pDocOld != NIL) return;
		docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pDeploymentDocTemplate,newName);
	}
	if (docPtr == NULL) {
		ErrorMsg("Can't create a document for "+newName+" file.");
		return;
	}
	if (!docPtr->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		ErrorMsg("Invalid document type");
		delete docPtr;
		return;
	}
	pDoc->clearContents(); 
	((COODCommonDoc *)docPtr)->copyDocumentContentsTo(pDoc);
	delete docPtr;
	pOODView->setControllerAbsolutely();
	Invalidate();
	return;
}

void COODCommonFrm::insertInsertPulldownMenu(CMenu *pInsertMenu)
{
	UINT resourceID = -1;
	CDocument *pDoc = GetActiveDocument();
	if (pDoc == NULL) return;
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) return;
	COODCommonDoc *pOODDoc = (COODCommonDoc *)pDoc;

	CString extension = pOODDoc->getExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		resourceID = IDR_CLASSFRAME;
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		resourceID = IDR_USECASEFRAME;
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		resourceID = IDR_SEQUENCEFRAME;
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		resourceID = IDR_COLLABORATIONFRAME;
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		resourceID = IDR_STATEFRAME;
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		resourceID = IDR_ACTIVITYFRAME;
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		resourceID = IDR_DEPLOYMENTFRAME;
	} else {
		return;
	}
	_insertMenuID = extension;

	CMenu tempMenu;
	if (!tempMenu.LoadMenu(resourceID)) {
		TRACE0("Loading insert pulldown menu fails");
		return;
	}

	CMenu *pSubMenu = tempMenu.GetSubMenu(INSERT_MENU_POS);
	if (pSubMenu == NULL) {
		return;
	}
	int nSubMenu = pSubMenu->GetMenuItemCount(); // 이 서브메뉴는 세퍼레이터이다.
	for (int i = 0; i < nSubMenu-2; i++) {
		UINT id = pSubMenu->GetMenuItemID(i);
		if (id == 0) {
			// Separator
			pInsertMenu->InsertMenu(i,MF_BYPOSITION|MF_SEPARATOR);
		} else {
			// Usual menu item
			CString menuName = _T("");
			UINT menuID = pSubMenu->GetMenuString(i,menuName,MF_BYPOSITION);
			pInsertMenu->InsertMenu(i,MF_BYPOSITION,id,menuName);
		}
	}
}

void COODCommonFrm::onInitMenu(CMenu* pMenu)
{
	CDocument *pDoc = GetActiveDocument();
	if (pDoc == NULL) return;
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) return;
	COODCommonDoc *pOODDoc = (COODCommonDoc *)pDoc;
	
	CString extension = pOODDoc->getExtension();
	if (extension.CompareNoCase(_insertMenuID) == 0) return;

	CMenu *pMainMenu = AfxGetMainWnd()->GetMenu();
	if (pMainMenu == NULL) return;
	CMenu *pSubMenu = pMainMenu->GetSubMenu(INSERT_MENU_POS_PLUS_1); //주의: CInPlaceFrame의 이자리에서는 더하기 1을 하지 않는다.
	// 그 이유는 첫번째 있는 아이콘도 메뉴 역할을 하기 때문이다.
	if (pSubMenu == NULL) {
		return;
	}
	int nSubMenu = pSubMenu->GetMenuItemCount(); // 이 서브메뉴는 세퍼레이터이다.
	if (nSubMenu > 1) {
		// 기존에 다른 메뉴가 로드되어있는 경우
		for (int i = 0; i < nSubMenu-2; i++) {
			pSubMenu->DeleteMenu(0,MF_BYPOSITION);
		}
	} else {
		pSubMenu->AppendMenu(MF_STRING,ID_INSERT_OBJECT,"&OLE Object");
	}
	insertInsertPulldownMenu(pSubMenu);
	DrawMenuBar();
}

/////////////////////////////////////////////////////////////////////////////
// COODCommonFrm message handlers


void COODCommonFrm::OnViewModelToolbar() 
{
	// TODO: Add your command handler code here
	if (_modelToolBar == NULL) return;
	/* ModelTBSupressedExplicitely는 이 클래스의 static 변수이다.
	다른 프레임들에도 같은 이름의 정적 변수가 있다.
	따라서 이 부분을 CChildFrm으로 옮기면 큰일난다. */
	if (_modelToolBar->GetStyle() & WS_VISIBLE) {
		ModelTBSupressedExplicitely = TRUE;
	} else {
		ModelTBSupressedExplicitely = FALSE;
	}
	mainFramePtr->ShowControlBar(_modelToolBar,
		(_modelToolBar->GetStyle() & WS_VISIBLE) == 0, 
		FALSE);		
}

void COODCommonFrm::OnUpdateViewModelToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (_modelToolBar != NULL) {
		pCmdUI->SetCheck((_modelToolBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
	pCmdUI->ContinueRouting();
}

void COODCommonFrm::OnOleAdaptViewFrame()
{
	CDocument *pDoc = GetActiveDocument();
	if (pDoc == NIL) return;
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) return;
	COODCommonDoc *pDocument = (COODCommonDoc *)pDoc;
	CView *pView = GetActiveView();
	if (!pView->IsKindOf(RUNTIME_CLASS(COODCommonView))) return;
	COODCommonView *pOleView = (COODCommonView *) pView;
	pOleView->setMainPopup();

	HINSTANCE hInst = AfxFindResourceHandle(
		MAKEINTRESOURCE(_resourceID), RT_GROUP_ICON);
	HICON hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(_resourceID));
	SetIcon(hIcon,TRUE);
}

void COODCommonFrm::OnFileNew() 
{
	// TODO: Add your command handler code here
	if (theAppPtr->runAsServerFlag) {
		UINT ans = YesNoMsg("OODesigner is going to clear this document.\nAre you sure ?");
		if (ans != IDYES) return;
		CDocument *pDoc = GetActiveDocument();
		if (pDoc == NIL) return;
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) return;
		COODCommonDoc *theDoc = (COODCommonDoc *)pDoc;
		theDoc->clearContents();
		Invalidate();
		return;
	}
	CChildFrm::OnFileNew();
}

void COODCommonFrm::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	if (theAppPtr->runAsServerFlag) {
		UINT ans = YesNoMsg("OODesigner is going to overwrite this document with new document.\nAre you sure ?");
		if (ans != IDYES) return;
		CDocument *pDoc = GetActiveDocument();
		if (pDoc == NIL) return;
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) return;
		COODCommonDoc *theDoc = (COODCommonDoc *)pDoc;
		CString extension = theDoc->getExtension();
		CString pathName;

		CFileDialog dlgFile(TRUE); 

		CString title = "Open diagram";

		dlgFile.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

		CString strFilter;
		CString strDefault;

		strFilter = strFilter + "Class Diagrams (" + extension + ")" ;
		strFilter += (TCHAR)'\0';   // next string please
		strFilter = strFilter + _T("*") + extension;
		strFilter += (TCHAR)'\0';   // next string please
		
		strFilter += (TCHAR)'\0';   // last string
		dlgFile.m_ofn.nMaxCustFilter++;

		dlgFile.m_ofn.lpstrFilter = strFilter;
#ifndef _MAC
		dlgFile.m_ofn.lpstrTitle = title;
#else
		dlgFile.m_ofn.lpstrPrompt = title;
#endif
		dlgFile.m_ofn.lpstrFile = pathName.GetBuffer(_MAX_PATH);

		BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;
		pathName.ReleaseBuffer();
		if (!bResult) return;

		overwriteDocumentFile(theDoc,pathName);
		return;
	}
	CChildFrm::OnFileOpen();
}

