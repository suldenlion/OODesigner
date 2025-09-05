// CMainFrame.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OOD.h"
#include <direct.h>
#include <io.h>

#include "CMainFrame.h"
#include "CNewDlg.h"
#include "KtgMacro.h"
#include "Frames.h"
#include "COODView.h"
#include "COODCommonFrm.h"
#include "Text.h"
#include "COODClassDoc.h"
#include "COODCommonDoc.h"
#include "PackageLibrary.h"
#include "CNewWSDlg.h"
#include "CResizableTreeBar.h"
#include "CProjectOptionsDlg.h"
#include "CTextView.h"
#include "CTextDoc.h"
#include "FigureList.h"
#include "MemberPropDlg.h"
#include "ClassPropDlg.h"
#include "ScreenCaptureDlg.h"
#include "CaptureDlg.h"
#include "RelationTraverseDlg.h"
#include "PackagePropDlg.h"
#include "COODCommonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CResizableMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CResizableMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_WINDOW_CLOSE_ALL, OnWindowCloseAll)
	ON_COMMAND(ID_WINDOW_NEXT, OnWindowNext)
	ON_COMMAND(ID_WINDOW_PREVIOUS, OnWindowPrevious)
	ON_COMMAND(ID_FILE_NEW_WORKSPACE, OnFileNewWorkspace)
	ON_COMMAND(ID_FILE_CLOSE_WORKSPACE, OnFileCloseWorkspace)
	ON_COMMAND(ID_FILE_OPEN_WORKSPACE, OnFileOpenWorkspace)
	ON_COMMAND(ID_FILE_SAVE_WORKSPACE, OnFileSaveWorkspace)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_WORKSPACE, OnUpdateFileSaveWorkspace)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE_WORKSPACE, OnUpdateFileCloseWorkspace)
	ON_COMMAND(ID_CLASS_TOOLS_OPTIONS, OnClassToolsOptions)
	ON_COMMAND(ID_OPTIONS_PROJECT, OnOptionsProject)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_VIEW_CUSTOMBAR, OnViewCustombar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CUSTOMBAR, OnUpdateViewCustombar)
	ON_COMMAND(ID_SCREENSHOT, OnScreenshot)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_WORKSPACE, OnUpdateFileSaveAsWorkspace)
	ON_COMMAND(ID_FILE_SAVE_AS_WORKSPACE, OnFileSaveAsWorkspace)
	ON_COMMAND(ID_CLASS_ROOT_NEW_PACKAGE, OnClassRootNewPackage)
	ON_COMMAND(ID_BAR_ALLOWDOCKING, OnBarAllowdocking)
	ON_COMMAND(ID_BAR_HIDE, OnBarHide)
	ON_UPDATE_COMMAND_UI(ID_CLASS_ROOT_NEW_PACKAGE, OnUpdateClassRootNewPackage)
	ON_COMMAND(ID_PACKAGE_NEW_CLASS, OnPackageNewClass)
	ON_COMMAND(ID_PACKAGE_OPEN, OnPackageOpen)
	ON_COMMAND(ID_PACKAGE_PROPERTIES, OnPackageProperties)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_GO_TO_DEFINITION, OnClassGoToDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_CLASS_RELATED_CLASSES, OnClassRelatedClasses)
	ON_COMMAND(ID_DATA_PROPERTIES, OnDataProperties)
	ON_COMMAND(ID_FUNCTION_PROPERTIES, OnFunctionProperties)
	ON_COMMAND(ID_DIAGRAM_DELETE, OnDiagramDelete)
	ON_COMMAND(ID_DIAGRAM_OPEN, OnDiagramOpen)
	ON_COMMAND(ID_DIAGRAM_TYPE_NEW_DIAGRAM, OnDiagramTypeNewDiagram)
	ON_COMMAND(ID_FILE_MENU_DELETE, OnFileMenuDelete)
	ON_COMMAND(ID_FILE_MENU_OPEN, OnFileMenuOpen)
	ON_COMMAND(ID_FILE_TYPE_NEW_FILE, OnFileTypeNewFile)
	ON_WM_INITMENU()
	ON_COMMAND(ID_MEMBER_DELETE, OnMemberDelete)
	ON_COMMAND(ID_CLASS_DELETE, OnClassDelete)
	ON_COMMAND(ID_PACKAGE_DELETE, OnPackageDelete)
	ON_COMMAND(ID_CLASS_MIGRATE, OnClassMigrate)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE,OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_WORKSPACE,OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DOCUMENTATION,OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_DOCUMENTATION,OnBarCheck)
END_MESSAGE_MAP()

// 아래 CInPlaceFrame 인디케이터는 에도 있으니까 똑같이 유지 할것 
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_POSITION,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

UINT getFileName(LPCTSTR lpszPathName, LPTSTR lpszTitle)
{
	ASSERT(lpszTitle == NULL ||
		AfxIsValidAddress(lpszTitle, _MAX_FNAME));
	ASSERT(AfxIsValidString(lpszPathName, FALSE));

	// always capture the complete file name including extension (if present)
	LPTSTR lpszTemp = (LPTSTR)lpszPathName;
	for (LPCTSTR lpsz = lpszPathName; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
	{
		// remember last directory/drive separator
		if (*lpsz == '\\' || *lpsz == '/' || *lpsz == ':')
			lpszTemp = (LPTSTR)_tcsinc(lpsz);
	}

	// lpszTitle can be NULL which just returns the number of bytes
	if (lpszTitle == NULL)
		return lstrlen(lpszTemp)+1;

	// otherwise copy it into the buffer provided
	lstrcpyn(lpszTitle, lpszTemp, _MAX_FNAME);
	return 0;
}
/*
BOOL runningAsInPlaceFrame()
{ 	
	CWnd* pFrame = CWnd::GetActiveWindow();
	if (pFrame == mainFramePtr) {
		return FALSE;
	} else {
		return TRUE;
	}
}
*/
BOOL doesFileExist(const char* name)
{
	struct _finddata_t dir;
	long hFile;
	
	char fileName[BUFSIZ];
	strcpy_s(fileName,BUFSIZ,name);

	if ((hFile = _findfirst(fileName,&dir)) == -1L) return FALSE;
	_findclose(hFile);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::showControlBarJustFor(const char *dgmName,CControlBar *pBar)
{
	if (strcmp(dgmName,"Class Diagram") != 0 &&
		(classDiagramToolBar.GetStyle() & WS_VISIBLE)) {
		ShowControlBar(&classDiagramToolBar,FALSE,TRUE);
	} 
	if (strcmp(dgmName,"Use Case Diagram") != 0 &&
		(usecaseDiagramToolBar.GetStyle() & WS_VISIBLE)) {
		ShowControlBar(&usecaseDiagramToolBar,FALSE,TRUE);
	} 
	if (strcmp(dgmName,"Sequence Diagram") != 0 &&
		(sequenceDiagramToolBar.GetStyle() & WS_VISIBLE)) {
		ShowControlBar(&sequenceDiagramToolBar,FALSE,TRUE);
	} 
	if (strcmp(dgmName,"Collaboration Diagram") != 0 &&
		(collaborationDiagramToolBar.GetStyle() & WS_VISIBLE)) {
		ShowControlBar(&collaborationDiagramToolBar,FALSE,TRUE);
	} 
	if (strcmp(dgmName,"State Diagram") != 0 &&
		(stateDiagramToolBar.GetStyle() & WS_VISIBLE)) {
		ShowControlBar(&stateDiagramToolBar,FALSE,TRUE);
	} 
	if (strcmp(dgmName,"Activity Diagram") != 0 &&
		(activityDiagramToolBar.GetStyle() & WS_VISIBLE)) {
		ShowControlBar(&activityDiagramToolBar,FALSE,TRUE);
	} 
	if (strcmp(dgmName,"Deployment Diagram") != 0 &&
		(deploymentDiagramToolBar.GetStyle() & WS_VISIBLE)) {
		ShowControlBar(&deploymentDiagramToolBar,FALSE,TRUE);
	}
	if (pBar == NIL) return;
	if (pBar->GetSafeHwnd() == NIL) return;
	ShowControlBar(pBar,TRUE,FALSE);
}

void CMainFrame::setTextOnStatusBar(const char *text,int field)
{
	m_wndStatusBar.GetStatusBarCtrl().SetText(text,field,0);
}

void CMainFrame::setPositionOnStatusBar(int x,int y,int field)
{
	char buffer[BUFSIZ];
	sprintf_s(buffer,BUFSIZ,"%4d, %4d",x,y);
	m_wndStatusBar.GetStatusBarCtrl().SetText(buffer,field,0);
}

void CMainFrame::userMsg(const char *s)
{
	setTextOnStatusBar(s);
}

void CMainFrame::userMsg(const char *s,int n)
{
	char buffer[BUFSIZ];
	sprintf_s(buffer,BUFSIZ,"%s%d",s,n);
	setTextOnStatusBar(buffer);
}

void CMainFrame::userMsgForUsingUpperCaseAsBlank(char *s,char *comment)
{
	char buffer[BUFSIZ];
	strcpy_s(buffer,BUFSIZ,s);
	int i = strlen(buffer);
	char *p = comment;
	while(*p != '\0') {
		if (*p >= 'A' && *p <= 'Z') {
			buffer[i++] = ' ';
		}
		buffer[i++] = *p;
		p++;
	}
	buffer[i] = '\0';
	if (i >= BUFSIZ) buffer[BUFSIZ-1] = '\0';
	setTextOnStatusBar(buffer);
}

void CMainFrame::getZoomValue(CString &value)
{
	m_wndCustomBar.getZoomValue(value);
}

void CMainFrame::setZoomValue(const char *value)
{
	m_wndCustomBar.setZoomValue(value);
}

void CMainFrame::setZoomValue(COODView *pView)
{
	// 주의: CInPlaceFrame에 있는 함수 내용과 똑같음
	if (pView == NULL) setZoomValue("100");
	char value[BUFSIZ];
	int zoomRatioX = pView->zoomRatioX();
	int zoomRatioY = pView->zoomRatioY();
	if (zoomRatioX == zoomRatioY) {
		sprintf_s(value,BUFSIZ,"%d",zoomRatioX);
	} else {
		strcpy_s(value,BUFSIZ,"auto");
	}
	setZoomValue(value);
}

void CMainFrame::setZoomValue(CDocument *pDoc)
{
	// 주의: CInPlaceFrame에 있는 함수 내용과 똑같음
	if (pDoc == NULL) setZoomValue("100");
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) setZoomValue("100");
	char value[BUFSIZ];
	int zoomRatioX = ((COODCommonDoc*)pDoc)->zoomRatioX();
	int zoomRatioY = ((COODCommonDoc*)pDoc)->zoomRatioY();
	if (zoomRatioX == zoomRatioY) {
		sprintf_s(value,BUFSIZ,"%d",zoomRatioX);
	} else {
		strcpy_s(value,BUFSIZ,"auto");
	}
	setZoomValue(value);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CResizableMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndCustomBar.Create(this) ||
		!m_wndCustomBar.LoadToolBar(IDR_TB_CUSTOM)) 
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndCustomBar.makeZoomComboBox(this,2,ID_COMBO_ZOOM,CSize(60,100));
	setZoomValue("100");

	if (!classDiagramToolBar.Create(this,WS_CHILD | CBRS_TOP) ||
		!classDiagramToolBar.LoadToolBar(IDR_TB_CLASS)) 
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!usecaseDiagramToolBar.Create(this,WS_CHILD | CBRS_TOP) ||
		!usecaseDiagramToolBar.LoadToolBar(IDR_TB_USECASE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!sequenceDiagramToolBar.Create(this,WS_CHILD | CBRS_TOP) ||
		!sequenceDiagramToolBar.LoadToolBar(IDR_TB_SEQUENCE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!collaborationDiagramToolBar.Create(this,WS_CHILD | CBRS_TOP) ||
		!collaborationDiagramToolBar.LoadToolBar(IDR_TB_COLLABORATION))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!stateDiagramToolBar.Create(this,WS_CHILD | CBRS_TOP) ||
		!stateDiagramToolBar.LoadToolBar(IDR_TB_STATE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!activityDiagramToolBar.Create(this,WS_CHILD | CBRS_TOP) ||
		!activityDiagramToolBar.LoadToolBar(IDR_TB_ACTIVITY))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!deploymentDiagramToolBar.Create(this,WS_CHILD | CBRS_TOP) ||
		!deploymentDiagramToolBar.LoadToolBar(IDR_TB_DEPLOYMENT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndCustomBar.SetBarStyle(m_wndCustomBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	classDiagramToolBar.SetBarStyle(classDiagramToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	usecaseDiagramToolBar.SetBarStyle(usecaseDiagramToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	sequenceDiagramToolBar.SetBarStyle(sequenceDiagramToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	collaborationDiagramToolBar.SetBarStyle(collaborationDiagramToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	stateDiagramToolBar.SetBarStyle(stateDiagramToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	activityDiagramToolBar.SetBarStyle(activityDiagramToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	deploymentDiagramToolBar.SetBarStyle(deploymentDiagramToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCustomBar.EnableDocking(CBRS_ALIGN_ANY);
	classDiagramToolBar.EnableDocking(CBRS_ALIGN_ANY);
	usecaseDiagramToolBar.EnableDocking(CBRS_ALIGN_ANY);
	sequenceDiagramToolBar.EnableDocking(CBRS_ALIGN_ANY);
	collaborationDiagramToolBar.EnableDocking(CBRS_ALIGN_ANY);
	stateDiagramToolBar.EnableDocking(CBRS_ALIGN_ANY);
	activityDiagramToolBar.EnableDocking(CBRS_ALIGN_ANY);
	deploymentDiagramToolBar.EnableDocking(CBRS_ALIGN_ANY);

	CRect rect(0,0,300,300);
	if (!m_wndTreeBar.Create(NULL,"TreeBar",/*WS_VISIBLE|WS_CHILD|*/CBRS_LEFT,
		rect,this,ID_VIEW_WORKSPACE,NULL)) {
		TRACE0("Creating a treebar failed.");
		return -1;
	}
	m_wndTreeBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndTreeBar);

	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndCustomBar);
	DockControlBar(&classDiagramToolBar);
	DockControlBar(&usecaseDiagramToolBar);
	DockControlBar(&sequenceDiagramToolBar);
	DockControlBar(&collaborationDiagramToolBar);
	DockControlBar(&stateDiagramToolBar);
	DockControlBar(&activityDiagramToolBar);
	DockControlBar(&deploymentDiagramToolBar);

	CRect targetRect;
	CRect sourceRect;
	RecalcLayout();
	m_wndToolBar.GetWindowRect(&targetRect);
	m_wndCustomBar.GetWindowRect(&sourceRect);
	targetRect.left = targetRect.right;
	targetRect.right = targetRect.left + (sourceRect.right - sourceRect.left);
	DockControlBar(&m_wndCustomBar,(UINT)0,(LPCRECT)&targetRect);

	setModelBarPositionOnLeftOf(&m_wndCustomBar,&classDiagramToolBar);
	setModelBarPositionOnLeftOf(&m_wndCustomBar,&usecaseDiagramToolBar);
	setModelBarPositionOnLeftOf(&m_wndCustomBar,&sequenceDiagramToolBar);
	setModelBarPositionOnLeftOf(&m_wndCustomBar,&collaborationDiagramToolBar);
	setModelBarPositionOnLeftOf(&m_wndCustomBar,&stateDiagramToolBar);
	setModelBarPositionOnLeftOf(&m_wndCustomBar,&activityDiagramToolBar);
	setModelBarPositionOnLeftOf(&m_wndCustomBar,&deploymentDiagramToolBar);

	return 0;
}

void CMainFrame::setModelBarPositionOnLeftOf(CControlBar *targetBar,CControlBar *modelBar)
{
	CRect targetRect;
	CRect sourceRect;

	RecalcLayout();
	targetBar->GetWindowRect(&targetRect);
	modelBar->GetWindowRect(&sourceRect);
	targetRect.left = targetRect.right;
	targetRect.right = targetRect.left + (sourceRect.right - sourceRect.left);
	DockControlBar(modelBar,(UINT)0,(LPCRECT)&targetRect);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return CResizableMDIFrameWnd::PreCreateWindow(cs);
}

BOOL CMainFrame::createNewClassFrame(CDocTemplate* pTemplate,CDocument* pDocument,CString fileName)
{
	// 이 함수는 CMDIFrameWnd::OnWindowNew() 참조한 것임
	if (!pDocument->IsKindOf(RUNTIME_CLASS(COODClassDoc))) {
		TRACE0("Warning: failed to create new frame. CMainFrame::createNewClassFrame\n");
		return FALSE;
	}
	
	COODClassDoc *theDocument = (COODClassDoc *)pDocument;

	char buffer[BUFSIZ];
	int n = Text::strcpyCompact(buffer,fileName,BUFSIZ);
	CString compacted = buffer;
	if (compacted.Right(_EXT_LEN5).CompareNoCase(_PAK_EXT) != 0) {
		compacted = compacted + _PAK_EXT;
	}

	if (theDocument->ifClassViewAlreadyExists(compacted)) {
		return TRUE;
	}

	ASSERT_VALID(pTemplate);
	CFrameWnd *pFrame = pTemplate->CreateNewFrame(pDocument,NULL);
	if (pFrame == NULL) {
		TRACE0("Warning: failed to create new frame. CMainFrame::createNewClassFrame\n");
		return FALSE;
	}
	pTemplate->InitialUpdateFrame(pFrame,pDocument);
	if (!pFrame->IsKindOf(RUNTIME_CLASS(CChildFrm))) {
		TRACE0("Warning: failed to create new frame. CMainFrame::createNewClassFrame\n");
		return FALSE;
	}

	CString title = ((CChildFrm *)pFrame)->diagramType();
	title = title + ": " + compacted;
	((CChildFrm *)pFrame)->frameName = compacted;
	((CChildFrm *)pFrame)->frameTitle = title;
	((CChildFrm *)pFrame)->OnUpdateFrameTitle(TRUE);
	CView *activeView = pFrame->GetActiveView();
	if (activeView == NIL) {
		TRACE0("Warning: failed to create new frame. CMainFrame::createNewClassFrame\n");
		return FALSE;
	}
	if (!activeView->IsKindOf(RUNTIME_CLASS(COODView))) {
		TRACE0("Warning: failed to create new frame. CMainFrame::createNewClassFrame\n");
		return FALSE;
	}
	COODView *theView = (COODView *)activeView;
	theView->setViewTitle(compacted);
	theView->setController();
	theView->remakeAllRegions(theDocument);
	setZoomValue(theView);
	theView->onZoom();
	theAppPtr->pCOODClassDoc->setModifiedFlag(FALSE);

	theAppPtr->pCOODClassDoc->getAllClassContents()->registerPackage(theView->viewTitleWithOutExtension);
	POSITION pos = theAppPtr->pCOODClassDoc->activeViewNames.Find(compacted);
	if (pos == NULL) {
		theAppPtr->pCOODClassDoc->insertViewName(compacted);
		m_wndTreeBar.insertDiagramName(compacted);
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if ((GetStyle() & FWS_ADDTOTITLE) == 0)
		return; // leave it alone!
	TCHAR szTitle[256];
	CString title; 
	if (AfxLoadString(AFX_IDS_APP_TITLE, szTitle) != 0) {
//		title = _tcsdup(szTitle);  이거는 가비지가 생김
		title = szTitle;
	} else {
		title = "OODesigner";
	}
	AfxSetWindowText(m_hWnd,(LPCTSTR)title);
}

void CMainFrame::closeTextFile(CString &viewName)
{
	POSITION pos = theAppPtr->pTextDocTemplate->GetFirstDocPosition();
	while (pos != NULL) 
	{
		CDocument* pDoc = theAppPtr->pTextDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(CTextDoc))) break;
		CString title = pDoc->GetTitle();
		if (viewName.CompareNoCase(title) == 0) {
			((CTextDoc *)pDoc)->closeWindowAbsolutely();
			return;
		}
	}
}
void CMainFrame::openTextFile(CString &fullName,CString &viewName)
{
	// 이 함수는 주로 소스 디렉토리에서 오픈하는 것을 원칙으로 함...
	POSITION pos = theAppPtr->pTextDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pTextDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(CTextDoc))) break;
		if (viewName.CompareNoCase(pDoc->GetTitle()) == 0) {
			POSITION pos = pDoc->GetFirstViewPosition();
			CView *pView = pDoc->GetNextView(pos);
			if (pView == NULL) break;
			CFrameWnd *theFrame = pView->GetParentFrame();
			if (theFrame == NULL) break;
			if (!theFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) break;
			((CMDIChildWnd *)theFrame)->MDIActivate();
			return;
		}
	}

	CDocument *pDoc = NULL;
	if (doesFileExist(fullName) == TRUE) {
		pDoc = theAppPtr->pTextDocTemplate->OpenDocumentFile(fullName);
	} else {
		pDoc = theAppPtr->pTextDocTemplate->OpenDocumentFile(viewName);
	}
	if (pDoc == NULL) return;
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODClassDoc))) return;
	CString title = pDoc->GetTitle();
	pos = theAppPtr->pCOODClassDoc->activeViewNames.Find(title);
	if (pos == NULL) {
		theAppPtr->pCOODClassDoc->insertViewName(title);
		m_wndTreeBar.insertTextName(title);
	}
}

CDocument *CMainFrame::getNamedTextDocument(CString &dgmName)
{
	POSITION pos = theAppPtr->pTextDocTemplate->GetFirstDocPosition();
	while (pos != NULL) 
	{
		CDocument* pDoc = theAppPtr->pTextDocTemplate->GetNextDoc(pos);
		if (dgmName.CompareNoCase(pDoc->GetTitle()) == 0) return pDoc;
	}
	return NIL;
}

CDocument *CMainFrame::getNamedDocument(CString &dgmName)
{
	POSITION pos = theAppPtr->pUseCaseDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pUseCaseDocTemplate->GetNextDoc(pos);
		if (dgmName.CompareNoCase(pDoc->GetTitle()) == 0) return pDoc;
	}
	pos = theAppPtr->pCollaborationDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pCollaborationDocTemplate->GetNextDoc(pos);
		if (dgmName.CompareNoCase(pDoc->GetTitle()) == 0) return pDoc;
	}
	pos = theAppPtr->pSequenceDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pSequenceDocTemplate->GetNextDoc(pos);
		if (dgmName.CompareNoCase(pDoc->GetTitle()) == 0) return pDoc;
	}
	pos = theAppPtr->pStateDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pStateDocTemplate->GetNextDoc(pos);
		if (dgmName.CompareNoCase(pDoc->GetTitle()) == 0) return pDoc;
	}
	pos = theAppPtr->pActivityDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pActivityDocTemplate->GetNextDoc(pos);
		if (dgmName.CompareNoCase(pDoc->GetTitle()) == 0) return pDoc;
	}
	pos = theAppPtr->pDeploymentDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pDeploymentDocTemplate->GetNextDoc(pos);
		if (dgmName.CompareNoCase(pDoc->GetTitle()) == 0) return pDoc;
	}
	return NIL;
}

COODView* CMainFrame::openNamedFile(DWORD dgmID,CString &dgmName)
{
	CString fileName = dgmName.Left(dgmName.GetLength()-_EXT_LEN5);

	BOOL okFlag = TRUE;
	CDocument *docPtr = NIL;
	if (dgmID == CLASS_DIAGRAM_BM_ID) {
		okFlag = createNewClassFrame(theAppPtr->pClassDocTemplate,(CDocument *)theAppPtr->pCOODClassDoc,fileName);
		docPtr = (CDocument *)theAppPtr->pCOODClassDoc;
	} else if (dgmID == USE_CASE_DIAGRAM_BM_ID) {
		docPtr = openOrCreateDocumentFile(theAppPtr->pUseCaseDocTemplate,dgmName);
		docPtr->SetTitle(fileName);
	} else if (dgmID == COLLABORATION_DIAGRAM_BM_ID) {
		docPtr = openOrCreateDocumentFile(theAppPtr->pCollaborationDocTemplate,dgmName);
		docPtr->SetTitle(fileName);
	} else if (dgmID == SEQUENCE_DIAGRAM_BM_ID) {
		docPtr = openOrCreateDocumentFile(theAppPtr->pSequenceDocTemplate,dgmName);
		docPtr->SetTitle(fileName);
	} else if (dgmID == STATE_DIAGRAM_BM_ID) {
		docPtr = openOrCreateDocumentFile(theAppPtr->pStateDocTemplate,dgmName);
		docPtr->SetTitle(fileName);
	} else if (dgmID == ACTIVITY_DIAGRAM_BM_ID) {
		docPtr = openOrCreateDocumentFile(theAppPtr->pActivityDocTemplate,dgmName);
		docPtr->SetTitle(fileName);
	} else if (dgmID == DEPLOYMENT_DIAGRAM_BM_ID) {
		docPtr = openOrCreateDocumentFile(theAppPtr->pDeploymentDocTemplate,dgmName);
		docPtr->SetTitle(fileName);
	} else {
		return NIL;
	}
	if (okFlag == FALSE) { 
		ErrorMsg("File creation fails.\r\nPlease contact to the vendor.");
		return NIL;
	}

	CString compacted = dgmName;
	if (docPtr == NIL) return NIL;
	if (!docPtr->IsKindOf(RUNTIME_CLASS(COODDoc))) return NIL;
	POSITION pos = theAppPtr->pCOODClassDoc->activeViewNames.Find(compacted);
	if (pos == NULL) {
		theAppPtr->pCOODClassDoc->insertViewName(compacted);
		m_wndTreeBar.insertDiagramName(compacted);
	}
	CFrameWnd *pFrameWnd = GetActiveFrame();
	if (pFrameWnd == NIL) return NIL;
	CView *activeView = pFrameWnd->GetActiveView();
	if (activeView == NIL) return NIL;
	if (!activeView->IsKindOf(RUNTIME_CLASS(COODView)))	return NIL;
	return (COODView *)activeView;
}

CDocument *CMainFrame::openOrCreateDocumentFile(CMultiDocTemplate* pDocumentTemplate,CString& dgmName)
{
	CString fullName = theAppPtr->workspaceDir + "\\" + dgmName;

	POSITION pos = pDocumentTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = pDocumentTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		POSITION pos = pDoc->GetFirstViewPosition();
		if (pos != NULL) {
			CView *pView = pDoc->GetNextView(pos);
			ASSERT_VALID(pView);
			if (!pView->IsKindOf(RUNTIME_CLASS(COODView))) break;
			COODView *theView = (COODView *)pView;
			if (dgmName.CompareNoCase(theView->viewTitle) == 0) {
				CFrameWnd *theFrame = pView->GetParentFrame();
				ASSERT_VALID(theFrame);
				if (!theFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) break;
				((CMDIChildWnd *)theFrame)->MDIActivate();
				return pDoc;
			}
		}
	}
	if (doesFileExist(fullName) == TRUE) {
		return pDocumentTemplate->OpenDocumentFile(fullName);
	}
	CDocument *pDoc = pDocumentTemplate->OpenDocumentFile(NULL);
	pDoc->SetModifiedFlag(TRUE);
	if (pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		COODCommonDoc *commonDoc = (COODCommonDoc *)pDoc;
		commonDoc->setRootStg(fullName);
		commonDoc->onFileSave();
	}
	return pDoc;
}

void CMainFrame::onFileNew(CString dgmTypeString,const char *defaultExtension)
{
	CNewDlg aDlg(dgmTypeString,defaultExtension);
	UINT button = aDlg.DoModal();
	if (button == IDCANCEL) return;
	int dgmType = aDlg.fileType();
	CString fileName = aDlg.m_name; 
	CDocument *docPtr = NIL;
	BOOL okFlag = TRUE;
	if (dgmType == KTG_PROJECT_WORKSPACE) {
		if (fileName.IsEmpty()) {
			ErrorMsg("Wrong workspace name.");
			return;
		}
		onFileNewWorkspace(fileName);
	} else if (dgmType == KTG_TEXT_FILE) {
		docPtr = theAppPtr->pTextDocTemplate->OpenDocumentFile(NULL);
		CString pathName = theAppPtr->workspaceDir + "\\src\\" + fileName;
		docPtr->SetPathName(pathName,FALSE);
		docPtr->SetTitle(fileName);
	} else if (dgmType == KTG_CLASS_DIAGRAM) {
		okFlag = createNewClassFrame(theAppPtr->pClassDocTemplate,(CDocument *)theAppPtr->pCOODClassDoc,fileName);
		docPtr = (CDocument *)theAppPtr->pCOODClassDoc;
	} else if (dgmType == KTG_USE_CASES) {
		if (fileName.Right(_EXT_LEN5).CompareNoCase(_USE_EXT) != 0) {
			fileName = fileName + _USE_EXT;
		}
		docPtr = openOrCreateDocumentFile(theAppPtr->pUseCaseDocTemplate,fileName);
		docPtr->SetTitle(fileName);
		setZoomValue(docPtr);
	} else if (dgmType == KTG_COLLABORATION_DIAGRAM) {
		if (fileName.Right(_EXT_LEN5).CompareNoCase(_COL_EXT) != 0) {
			fileName = fileName + _COL_EXT;
		}
		docPtr = openOrCreateDocumentFile(theAppPtr->pCollaborationDocTemplate,fileName);
		docPtr->SetTitle(fileName);
		setZoomValue(docPtr);
	} else if (dgmType == KTG_SEQUENCE_DIAGRAM) {
		if (fileName.Right(_EXT_LEN5).CompareNoCase(_SEQ_EXT) != 0) {
			fileName = fileName + _SEQ_EXT;
		}
		docPtr = openOrCreateDocumentFile(theAppPtr->pSequenceDocTemplate,fileName);
		docPtr->SetTitle(fileName);
		setZoomValue(docPtr);
	} else if (dgmType == KTG_STATE_DIAGRAM) {
		if (fileName.Right(_EXT_LEN5).CompareNoCase(_STA_EXT) != 0) {
			fileName = fileName + _STA_EXT;
		}
		docPtr = openOrCreateDocumentFile(theAppPtr->pStateDocTemplate,fileName);
		docPtr->SetTitle(fileName);
		setZoomValue(docPtr);
	} else if (dgmType == KTG_ACTIVITY_DIAGRAM) {
		if (fileName.Right(_EXT_LEN5).CompareNoCase(_ACT_EXT) != 0) {
			fileName = fileName + _ACT_EXT;
		}
		docPtr = openOrCreateDocumentFile(theAppPtr->pActivityDocTemplate,fileName);
		docPtr->SetTitle(fileName);
		setZoomValue(docPtr);
	} else if (dgmType == KTG_DEPLOYMENT_DIAGRAM) {
		if (fileName.Right(_EXT_LEN5).CompareNoCase(_DEP_EXT) != 0) {
			fileName = fileName + _DEP_EXT;
		}
		docPtr = openOrCreateDocumentFile(theAppPtr->pDeploymentDocTemplate,fileName);
		docPtr->SetTitle(fileName);
		setZoomValue(docPtr);
	}	
	if (okFlag == FALSE) { 
		ErrorMsg("File creation fails.\r\nPlease contact to the vendor.");
		return;
	}
	// text 경우 나중에 처리
	if (dgmType != KTG_PROJECT_WORKSPACE && 
		dgmType != KTG_TEXT_FILE) {
		char buffer[BUFSIZ];
		int n = Text::strcpyCompact(buffer,fileName,BUFSIZ);
		CString compacted = buffer;
		if (!docPtr->IsKindOf(RUNTIME_CLASS(COODDoc))) return;
		COODDoc *oodDoc = (COODDoc *)docPtr;
		if (compacted.Right(_EXT_LEN5).CompareNoCase(oodDoc->getExtension()) != 0) {
			compacted = compacted + oodDoc->getExtension();
		}
		POSITION pos = theAppPtr->pCOODClassDoc->activeViewNames.Find(compacted);
		if (pos == NULL) {
			theAppPtr->pCOODClassDoc->insertViewName(compacted);
			m_wndTreeBar.insertDiagramName(compacted);
		}
	} else if (dgmType != KTG_PROJECT_WORKSPACE) {
		POSITION pos = theAppPtr->pCOODClassDoc->activeViewNames.Find(fileName);
		if (pos == NULL) {
			theAppPtr->pCOODClassDoc->insertViewName(fileName);
			m_wndTreeBar.insertTextName(fileName);
		}
	}
	if (docPtr != NULL && docPtr->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		COODCommonDoc *commonDoc = (COODCommonDoc *)docPtr;
		if (commonDoc->figures()->nOfList() == 0) {
			// 새로 만들어진 경우
			docPtr->SetModifiedFlag(FALSE); // 껐다가 켜야지 작동함
			commonDoc->setModifiedFlag(TRUE);
		}
	}
}

void CMainFrame::OnFileNew() 
{
	// TODO: Add your command handler code here
	onFileNew("");
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CView *preView = GetActiveView();
	if (preView != NULL && preView->IsKindOf(RUNTIME_CLASS(CPreviewView))) {
		// 이 코드는 졸라 쌩고생해서 찾았음
		::SendMessage(preView->m_hWnd,WM_COMMAND,AFX_ID_PREVIEW_CLOSE,0);
		return;
	}

	if (theAppPtr->runAsServerFlag) {
		COODView *pView = getActiveCOODView();
		if (pView != NIL) {
			pView->editorFinished();
			COODDoc *pDoc = pView->GetDocument(); 
			pDoc->UpdateAllItems(NULL);
		}
		CResizableMDIFrameWnd::OnClose();
		return;
	}
	COODView *pView = getActiveCOODView();
	if (pView != NIL && theAppPtr->pCOODClassDoc != NIL) {
		theAppPtr->pCOODClassDoc->recentViewName = pView->viewTitle;
	}

	BOOL canceled = onWindowCloseAll();
	if (canceled == TRUE) return;

	SetActiveView(NULL,FALSE);
	theAppPtr->deleteDocTemplates();

	CResizableMDIFrameWnd::OnClose();
}

void CMainFrame::OnFileOpen() 
{
	// TODO: Add your command handler code here
	if (theAppPtr->workspaceName.GetLength() == 0 &&
		theAppPtr->pCOODClassDoc != NIL) {
		BOOL canceled = onWindowCloseAll();
		if (canceled == TRUE) return;
		OnFileOpenWorkspace();
		return;
	}
	CString pathName;

	CFileDialog dlgFile(TRUE);

	CString title = "Open diagram/text files";

	dlgFile.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	CString strFilter;
	CString strDefault;

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
#ifndef _MAC
	strFilter += _T("*.*");
#else
	strFilter += _T("****");
#endif
	strFilter += (TCHAR)'\0';   // next string please

	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter = strFilter + "Class Diagrams (" + _PAK_EXT + ")" ;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter = strFilter + _T("*") + _PAK_EXT;
	strFilter += (TCHAR)'\0';   // next string please
	
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter = strFilter + "Use Case Diagrams (" + _USE_EXT + ")" ;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter = strFilter + _T("*") + _USE_EXT;
	strFilter += (TCHAR)'\0';   // next string please
	
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter = strFilter + "Sequence Diagrams (" + _SEQ_EXT + ")" ;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter = strFilter + _T("*") + _SEQ_EXT;
	strFilter += (TCHAR)'\0';   // next string please
	
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter = strFilter + "Collaboration Diagrams (" + _COL_EXT + ")" ;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter = strFilter + _T("*") + _COL_EXT;
	strFilter += (TCHAR)'\0';   // next string please
	
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter = strFilter + "State Diagrams (" + _STA_EXT + ")" ;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter = strFilter + _T("*") + _STA_EXT;
	strFilter += (TCHAR)'\0';   // next string please
	
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter = strFilter + "Activity Diagrams (" + _ACT_EXT + ")" ;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter = strFilter + _T("*") + _ACT_EXT;
	strFilter += (TCHAR)'\0';   // next string please
	
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter = strFilter + "Deployment Diagrams (" + _DEP_EXT + ")" ;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter = strFilter + _T("*") + _DEP_EXT;
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

	// pathName is full path name of the file.
	openDocumentFile(pathName);
}

CDocument* CMainFrame::alreadyOpen(CDocTemplate *pTemplate,CString &fileName)
{
	CDocTemplate::Confidence match;
	CDocument *pOpenDocument = NULL;
#ifndef _MAC
	match = pTemplate->MatchDocType(fileName, pOpenDocument);
#else
	match = pTemplate->MatchDocType(fileName, fileData.dwFileType, pOpenDocument);
#endif
	if (match != CDocTemplate::yesAlreadyOpen) return NIL;
	if (pOpenDocument != NULL)
	{
		POSITION pos = pOpenDocument->GetFirstViewPosition();
		if (pos != NULL)
		{
			CView* pView = pOpenDocument->GetNextView(pos); // get first one
			ASSERT_VALID(pView);
			CFrameWnd* pFrame = pView->GetParentFrame();
			if (pFrame != NULL)
				pFrame->ActivateFrame();
			else
				TRACE0("Error: Can not find a frame for document to activate.\n");
			CFrameWnd* pAppFrame;
			if (pFrame != (pAppFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd))
			{
				ASSERT_KINDOF(CFrameWnd, pAppFrame);
				pAppFrame->ActivateFrame();
			}
		}
		else
		{
			TRACE0("Error: Can not find a view for document to activate.\n");
		}
	}
	return pOpenDocument;		
}

CDocument* CMainFrame::openDocumentFile(CString &pathName)
{
	CString newName = pathName;
	char pathNameBuffer[BUFSIZ];
	char fileNameBuffer[BUFSIZ];
	strcpy_s(pathNameBuffer,BUFSIZ,pathName);
	getFileName(pathNameBuffer, fileNameBuffer);
	CString fileName = fileNameBuffer;

	CString oodExt = newName.Right(_EXT_LEN4);
	CString fileExt = newName.Right(_EXT_LEN5);
	CDocument *docPtr = NIL; 
	if (oodExt.CompareNoCase(_OOD_EXT) == 0) {
		InfoMsg("Please use <File>/<Open Workspace> menu to open class diagrams.");
	} else if (fileExt.CompareNoCase(_PAK_EXT) == 0) {
		CDocument *pDocOld = alreadyOpen(theAppPtr->pObjectDocTemplate,newName);
		if (pDocOld != NIL) return pDocOld;
		char buffer[BUFSIZ];
		int n = Text::strcpyCompact(buffer,fileName,BUFSIZ);
		CString viewName = buffer;
		if (viewName.Right(_EXT_LEN5).CompareNoCase(_PAK_EXT) != 0) {
			viewName = viewName + _PAK_EXT;
		}
		if (theAppPtr->workspaceName.GetLength() != 0) { // valid workspace
			COODClassDoc *theDocument = (COODClassDoc *)theAppPtr->pCOODClassDoc;

			CString packName = viewName.Left(viewName.GetLength()-_EXT_LEN5);
			FigureLibrary *aPackage = theDocument->getPackage(viewName);
			if (aPackage != NIL) {
				UINT ans = YesNoMsg("The existing "+viewName+" package will be overwritten.\r\nAre you sure to overload "+viewName+" document ?");
				if (ans != IDYES) return theDocument;
				docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pObjectDocTemplate,newName);
				if (docPtr == NULL) {
					ErrorMsg("Can't make a document for "+viewName+" file.");
					return theDocument;
				}
				theDocument->hideClassViewIfAlreadyExists(viewName);
				FigureLibrary* aPackage = theDocument->clearPackage(viewName);
				if (aPackage != NULL) {
					((COODCommonDoc*)docPtr)->copyDocumentContentsTo(aPackage,theDocument);
					theDocument->registerOrReplaceClassContent(packName,aPackage);
				}
			} else {
				docPtr = COODCommonDoc::openInvisibleDocument(theAppPtr->pObjectDocTemplate,newName);
				if (docPtr == NULL) {
					ErrorMsg("Can't make a document for "+viewName+" file.");
					return theDocument;
				}
				if (!createNewClassFrame(theAppPtr->pClassDocTemplate,theDocument,viewName)) return theDocument;
				theDocument->hideClassViewIfAlreadyExists(viewName); // 만들자 말자 바로 숨김
				FigureLibrary *aPackage = theDocument->getPackage(viewName);
				if (aPackage == NIL) {
					aPackage = theDocument->addPackage(viewName);
				}
				if (aPackage == NIL) {
					ErrorMsg("Can't find data for "+viewName+" view.");
					theAppPtr->pObjectDocTemplate->RemoveDocument(docPtr);
					delete docPtr;
					return theDocument;
				}
				((COODCommonDoc*)docPtr)->copyDocumentContentsTo(aPackage,theDocument);
				theDocument->registerOrReplaceClassContent(packName,aPackage);
			}
			if (!createNewClassFrame(theAppPtr->pClassDocTemplate,theDocument,viewName)) return theDocument;
			theAppPtr->pObjectDocTemplate->RemoveDocument(docPtr);
			delete docPtr;
			theDocument->setModifiedFlag();
			return theDocument;
		} else {
			docPtr = theAppPtr->pObjectDocTemplate->OpenDocumentFile(newName);
			docPtr->SetTitle(viewName);
			return docPtr;
		}
	} else if (fileExt.CompareNoCase(_USE_EXT) == 0) {
		CDocument *pDocOld = alreadyOpen(theAppPtr->pUseCaseDocTemplate,newName);
		if (pDocOld != NIL) return pDocOld;
		docPtr = theAppPtr->pUseCaseDocTemplate->OpenDocumentFile(newName);
	} else if (fileExt.CompareNoCase(_COL_EXT) == 0) {
		CDocument *pDocOld = alreadyOpen(theAppPtr->pCollaborationDocTemplate,newName);
		if (pDocOld != NIL) return pDocOld;
		docPtr = theAppPtr->pCollaborationDocTemplate->OpenDocumentFile(newName);
	} else if (fileExt.CompareNoCase(_SEQ_EXT) == 0) {
		CDocument *pDocOld = alreadyOpen(theAppPtr->pSequenceDocTemplate,newName);
		if (pDocOld != NIL) return pDocOld;
		docPtr = theAppPtr->pSequenceDocTemplate->OpenDocumentFile(newName);
	} else if (fileExt.CompareNoCase(_STA_EXT) == 0) {
		CDocument *pDocOld = alreadyOpen(theAppPtr->pStateDocTemplate,newName);
		if (pDocOld != NIL) return pDocOld;
		docPtr = theAppPtr->pStateDocTemplate->OpenDocumentFile(newName);
	} else if (fileExt.CompareNoCase(_ACT_EXT) == 0) {
		CDocument *pDocOld = alreadyOpen(theAppPtr->pActivityDocTemplate,newName);
		if (pDocOld != NIL) return pDocOld;
		docPtr = theAppPtr->pActivityDocTemplate->OpenDocumentFile(newName);
	} else if (fileExt.CompareNoCase(_DEP_EXT) == 0) {
		CDocument *pDocOld = alreadyOpen(theAppPtr->pDeploymentDocTemplate,newName);
		if (pDocOld != NIL) return pDocOld;
		docPtr = theAppPtr->pDeploymentDocTemplate->OpenDocumentFile(newName);
	} else {
		CDocument *pDocOld = alreadyOpen(theAppPtr->pTextDocTemplate,newName);
		if (pDocOld != NIL) return pDocOld;
		docPtr = theAppPtr->pTextDocTemplate->OpenDocumentFile(newName);
	}
	if (docPtr != NIL && 
		docPtr->IsKindOf(RUNTIME_CLASS(COODDoc)) &&
		theAppPtr->workspaceName.GetLength() != 0) {
		CString viewName = ((COODDoc *)docPtr)->getFirstView()->viewTitle;
		m_wndTreeBar.insertDiagramName(viewName);
	}
	return docPtr;
}

void CMainFrame::setFontInfoForDocument(CDocument* pDoc,CFontDialog *pFontDlg)
{
	POSITION viewPos = pDoc->GetFirstViewPosition();
	while (viewPos != NULL)	{
		CView* pView = pDoc->GetNextView(viewPos);
		ASSERT_VALID(pView);
		if (!pView->IsKindOf(RUNTIME_CLASS(COODView))) break;
		((COODView *)pView)->setFontInfo(pFontDlg);
	}
}

void CMainFrame::setFontInfoForAllViews(CFontDialog *pFontDlg)
{
	if (theAppPtr->pCOODClassDoc != NIL) {
		setFontInfoForDocument(theAppPtr->pCOODClassDoc,pFontDlg);
	}
	POSITION pos = theAppPtr->pObjectDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pObjectDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		setFontInfoForDocument(pDoc,pFontDlg);
	}
	pos = theAppPtr->pUseCaseDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pUseCaseDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		setFontInfoForDocument(pDoc,pFontDlg);
	}
	pos = theAppPtr->pCollaborationDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pCollaborationDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		setFontInfoForDocument(pDoc,pFontDlg);
	}
	pos = theAppPtr->pSequenceDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pSequenceDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		setFontInfoForDocument(pDoc,pFontDlg);
	}
	pos = theAppPtr->pStateDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pStateDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		setFontInfoForDocument(pDoc,pFontDlg);
	}
	pos = theAppPtr->pActivityDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pActivityDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		setFontInfoForDocument(pDoc,pFontDlg);
	}
	pos = theAppPtr->pDeploymentDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pDeploymentDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		setFontInfoForDocument(pDoc,pFontDlg);
	}
}

BOOL CMainFrame::onWindowCloseAllCommon(BOOL closeWorkspace)
{
	BOOL removeNameFlag = FALSE;
	if (closeWorkspace != TRUE) {
		removeNameFlag = TRUE; 
	}

	POSITION pos = theAppPtr->pObjectDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pObjectDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		BOOL canceled = ((COODCommonDoc *)pDoc)->onWindowClose(removeNameFlag);
		if (canceled == TRUE) return TRUE;
	}
	pos = theAppPtr->pUseCaseDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pUseCaseDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		BOOL canceled = ((COODCommonDoc *)pDoc)->onWindowClose(removeNameFlag);
		if (canceled == TRUE) return TRUE;
	}
	pos = theAppPtr->pCollaborationDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pCollaborationDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		BOOL canceled = ((COODCommonDoc *)pDoc)->onWindowClose(removeNameFlag);
		if (canceled == TRUE) return TRUE;
	}
	pos = theAppPtr->pSequenceDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pSequenceDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		BOOL canceled = ((COODCommonDoc *)pDoc)->onWindowClose(removeNameFlag);
		if (canceled == TRUE) return TRUE;
	}
	pos = theAppPtr->pStateDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pStateDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		BOOL canceled = ((COODCommonDoc *)pDoc)->onWindowClose(removeNameFlag);
		if (canceled == TRUE) return TRUE;
	}
	pos = theAppPtr->pActivityDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pActivityDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		BOOL canceled = ((COODCommonDoc *)pDoc)->onWindowClose(removeNameFlag);
		if (canceled == TRUE) return TRUE;
	}
	pos = theAppPtr->pDeploymentDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pDeploymentDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		BOOL canceled = ((COODCommonDoc *)pDoc)->onWindowClose(removeNameFlag);
		if (canceled == TRUE) return TRUE;
	}
	pos = theAppPtr->pTextDocTemplate->GetFirstDocPosition();
	while (pos != NULL) 
	{
		CDocument* pDoc = theAppPtr->pTextDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(CTextDoc))) break;
		BOOL canceled = ((CTextDoc *)pDoc)->onWindowClose(removeNameFlag);
		if (canceled == TRUE) return TRUE;
	}
	return FALSE;
}

BOOL CMainFrame::onWindowCloseAll()
{
	theAppPtr->deactivateClassPropertyDlgs();
	if ((theAppPtr->theRelationTraverseDlg->GetStyle() & WS_VISIBLE) != 0) {
		theAppPtr->theRelationTraverseDlg->ShowWindow(SW_HIDE);
	}
	if ((theAppPtr->thePackagePropDlg->GetStyle() & WS_VISIBLE) != 0) {
		theAppPtr->thePackagePropDlg->ShowWindow(SW_HIDE);
	}
	BOOL canceled = onWindowCloseAllCommon(TRUE);
	if (canceled == TRUE) return TRUE;
	canceled = FALSE;  
	if (theAppPtr->pCOODClassDoc != NIL) {
	    canceled = theAppPtr->pCOODClassDoc->closeAllWindow(TRUE);
	}
	if (canceled == TRUE) return TRUE;
	if (theAppPtr->pCOODClassDoc != NIL) {
	    theAppPtr->pCOODClassDoc->DeleteContents();
	}
	theAppPtr->CloseAllDocuments(TRUE);
	return FALSE;
}

void CMainFrame::OnWindowCloseAll() 
{
	// TODO: Add your command handler code here
	if (theAppPtr->runAsServerFlag) {
		OnClose();
		return; // 2014 OODesigner 수정 FALSE;
	}

	BOOL canceled = onWindowCloseAllCommon(FALSE);
	if (canceled == TRUE) return; // 2014 OODesigner 수정  TRUE;
	if (theAppPtr->pCOODClassDoc != NIL) {
	    theAppPtr->pCOODClassDoc->closeAllWindow(FALSE);
	}
//	theAppPtr->CloseAllDocuments(TRUE); 이 경우는 윈도만 닫아야 하기때문에 도큐먼트를 닫으면 문제가 생김
	return; // 2014 OODesigner 수정  FALSE;
}

COODView* CMainFrame::getActiveCOODView() 
{
	// TODO: Add your command handler code here
	CMDIChildWnd* currentFrame = MDIGetActive(); 
	if (currentFrame == NIL) return NIL;
	if (!currentFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) return NIL;
	CView *currentView = currentFrame->GetActiveView();
	if (currentView == NIL) return NIL;
	if (!currentView->IsKindOf(RUNTIME_CLASS(COODView))) return NIL;
	return (COODView *)currentView;
}

void CMainFrame::OnWindowNext() 
{
	// TODO: Add your command handler code here
	MDINext();
}

void CMainFrame::OnWindowPrevious() 
{
	// TODO: Add your command handler code here
	CMDIChildWnd* currentFrame = MDIGetActive(); 
	if (currentFrame == NIL) return;
	CWnd* prevFrame = currentFrame->GetWindow(GW_HWNDLAST);
	if (prevFrame == NIL) return;
	if (!prevFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) return;
	MDIActivate(prevFrame); 
}

void CMainFrame::onFileNewWorkspace(CString &wsName)
{
	BOOL canceled = onWindowCloseAll();
	if (canceled == TRUE) return;

	m_wndTreeBar.clearContents();	
	theAppPtr->workspaceName = _T("");

	CNewWSDlg newWSDlg(wsName,this);
	UINT ans = newWSDlg.DoModal();
	if (ans != IDOK) return;

	CString oldWSDir = theAppPtr->workspaceDir;
	CString oldWSName = theAppPtr->workspaceName;

	theAppPtr->workspaceDir = newWSDlg.wsLocation;
	theAppPtr->workspaceName = newWSDlg.workspaceName;

	char location[BUFSIZ];
	strcpy_s(location,BUFSIZ,theAppPtr->workspaceDir);
	char subLocation[BUFSIZ];

	if (_mkdir(location) != 0) {
		theAppPtr->workspaceDir = oldWSDir;
		theAppPtr->workspaceName = oldWSName;
		ErrorMsg("Creating new workspace fails.\nCreating a directory fails");
		return;
	} 

	strcpy_s(subLocation,BUFSIZ,location);
	strcat_s(subLocation,BUFSIZ,"\\src");
	if (_mkdir(subLocation) != 0) {
		theAppPtr->workspaceDir = oldWSDir;
		theAppPtr->workspaceName = oldWSName;
		ErrorMsg("Creating new workspace fails.\nCreating a directory fails");
		return;
	} 

	strcpy_s(subLocation,BUFSIZ,location);
	theAppPtr->projectCodegenTargetDir = theAppPtr->workspaceDir + "\\src\\";

	strcat_s(subLocation,BUFSIZ,"\\backup");
	if (_mkdir(subLocation) != 0) {
		theAppPtr->workspaceDir = oldWSDir;
		theAppPtr->workspaceName = oldWSName;
		ErrorMsg("Creating new workspace fails.\nCreating a directory fails");
		return;
	} 
	
	char msg[BUFSIZ];
	sprintf_s(msg,BUFSIZ,"OODesigner created workspace %s at %s directory.\n\
This has the following subdirectories.\n\
(1) src: will save automatically generated program files.\n\
         This directory can be changed by <Tools>/<Option> menu later.\n\
(2) backup: will save backup files.",theAppPtr->workspaceName,theAppPtr->workspaceDir);
	InfoMsg(msg);

	if (_chdir(location) != 0) {
		theAppPtr->workspaceDir = oldWSDir;
		theAppPtr->workspaceName = oldWSName;
		ErrorMsg("Change directory to workspace fails.");
		return;
	}

	if (theAppPtr->pCOODClassDoc != NULL) {
		theAppPtr->pClassDocTemplate->RemoveDocument(theAppPtr->pCOODClassDoc);
		delete theAppPtr->pCOODClassDoc;
		theAppPtr->pCOODClassDoc = NIL;
	}
	theAppPtr->pCOODClassDoc = (COODClassDoc *) RUNTIME_CLASS(COODClassDoc)->CreateObject();
	if (theAppPtr->pCOODClassDoc == NULL) {
		ErrorMsg("Creating COODClassDoc failed.");
		return;
	}
	ASSERT_KINDOF(COODClassDoc,theAppPtr->pCOODClassDoc);
	theAppPtr->pCOODClassDoc->m_bAutoDelete = FALSE;
	theAppPtr->pClassDocTemplate->AddDocument(theAppPtr->pCOODClassDoc);

	BOOL okFlag = createNewClassFrame(theAppPtr->pClassDocTemplate,(CDocument *)theAppPtr->pCOODClassDoc,theAppPtr->workspaceName);
	if (okFlag == FALSE) { 
		ErrorMsg("Class diagram window creation fails.\r\nPlease contact to the vendor.");
		return;
	}
	

	CString pathFullName = theAppPtr->workspaceDir + "\\" + theAppPtr->workspaceName + _OOD_EXT;
	theAppPtr->addToWorkspaceList(pathFullName);
	theAppPtr->pCOODClassDoc->setRootStg(pathFullName);
	theAppPtr->pCOODClassDoc->onFileSaveClassDocument();
	theAppPtr->pCOODClassDoc->setStrTitle("OODesigner");
}

void CMainFrame::OnFileNewWorkspace() 
{
	// TODO: Add your command handler code here
	CString wsName = _T("");
	onFileNewWorkspace(wsName);
}

void CMainFrame::OnFileCloseWorkspace() 
{
	// TODO: Add your command handler code here
	COODView *pView = getActiveCOODView();
	if (pView != NIL) {
		theAppPtr->pCOODClassDoc->recentViewName = pView->viewTitle;
	}
	BOOL canceled = onWindowCloseAll();
	if (canceled == TRUE) return;
	m_wndTreeBar.clearContents();	
	theAppPtr->workspaceName = _T("");
	if (theAppPtr->pCOODClassDoc != NULL) {
		theAppPtr->pClassDocTemplate->RemoveDocument(theAppPtr->pCOODClassDoc);
		delete theAppPtr->pCOODClassDoc;
		theAppPtr->pCOODClassDoc = NIL;
	}
}

BOOL CMainFrame::onFileOpenWorkspace(LPCTSTR fileName)
{
	if (!doesFileExist(fileName)) {
		ErrorMsg("Unable to open the workspace.");
		return FALSE;
	}

	if (theAppPtr->pCOODClassDoc != NULL) {
		theAppPtr->pClassDocTemplate->RemoveDocument(theAppPtr->pCOODClassDoc);
		delete theAppPtr->pCOODClassDoc;
		theAppPtr->pCOODClassDoc = NIL;
	}
	theAppPtr->pCOODClassDoc = (COODClassDoc *) RUNTIME_CLASS(COODClassDoc)->CreateObject();
	if (theAppPtr->pCOODClassDoc == NULL) {
		ErrorMsg("Creating COODClassDoc failed.");
		return FALSE;
	}
	ASSERT_KINDOF(COODClassDoc,theAppPtr->pCOODClassDoc);
	theAppPtr->pCOODClassDoc->m_bAutoDelete = FALSE;
	theAppPtr->pClassDocTemplate->AddDocument(theAppPtr->pCOODClassDoc);

	theAppPtr->pCOODClassDoc->setRootStg(fileName);
	theAppPtr->pCOODClassDoc->setStrTitle("OODesigner");

	// fileName is full path name of the file.
	CDocument *pDocument = (CDocument *)theAppPtr->pCOODClassDoc;
	pDocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
	LPCTSTR lpszPathName = fileName;
	// open an existing document
	CWaitCursor wait;
	if (!pDocument->OnOpenDocument(lpszPathName))
	{
		// user has be alerted to what failed in OnOpenDocument
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return FALSE;
	} 
	CString newWSDir = lpszPathName;
	int totalLen = newWSDir.GetLength();
	int tailLen = theAppPtr->workspaceName.GetLength() + (_EXT_LEN4 + 1);
	newWSDir = newWSDir.Left(totalLen-tailLen);
	theAppPtr->workspaceDir = newWSDir;
	if (_chdir(theAppPtr->workspaceDir) != 0) {
		ErrorMsg("Change directory to workspace fails: "+newWSDir+" ");
		return FALSE;
	}

	char subLocation[BUFSIZ];
	if (doesFileExist("src") == FALSE) {
		strcpy_s(subLocation,BUFSIZ,"src");
		if (_mkdir(subLocation) != 0) {
			WarningMsg("Creating new workspace fails.\nCreating a directory fails");
		} 
	}

	int length = theAppPtr->projectCodegenTargetDir.GetLength();
	CString tempDir = theAppPtr->projectCodegenTargetDir.Left(length-1);
	if (doesFileExist(tempDir) == FALSE) {
		theAppPtr->projectCodegenTargetDir = theAppPtr->workspaceDir + "\\src\\";
	}

	if (doesFileExist("backup") == FALSE) {
		strcpy_s(subLocation,BUFSIZ,"backup");
		if (_mkdir(subLocation) != 0) {
			WarningMsg("Creating new workspace fails.\nCreating a directory fails");
		} 
	}

	if (theAppPtr->projectCodegenTargetDir.GetLength() < 3) {
		theAppPtr->projectCodegenTargetDir = theAppPtr->workspaceDir + "\\src\\";
	}
	
	m_wndTreeBar.registerTextFiles();
	m_wndTreeBar.registerDiagramFilesFromCurrentDir();
	m_wndTreeBar.registerClassDiagramFilesFromClassFigureLibrary(theAppPtr->pCOODClassDoc->getClassFiguresLibrary());
	m_wndTreeBar.registerClassContentFromPackageLibrary(theAppPtr->pCOODClassDoc->getAllClassContents());

	CProgressCtrl prgressCtrl;
	int nFiles = theAppPtr->pCOODClassDoc->activeViewNames.GetCount();
	if (nFiles > 0) {
		setTextOnStatusBar("Loading files...");
		CRect rect = CRect(100,3,300,18);
		prgressCtrl.Create(WS_VISIBLE|WS_CHILD,rect,&m_wndStatusBar,0);
		prgressCtrl.SetRange(0,nFiles);
		prgressCtrl.SetPos(0);
	}

	CString topViewName = theAppPtr->pCOODClassDoc->recentViewName;
	CMultiDocTemplate *pTopTemplate = NIL;

	CStringList namesToRemove;

	int fileCount = 0;
	POSITION pos = theAppPtr->pCOODClassDoc->activeViewNames.GetHeadPosition();
	while (pos != NULL)
	{
		fileCount++;
		prgressCtrl.SetPos(fileCount);

		CDocument *docPtr = NIL;
		CString viewName = theAppPtr->pCOODClassDoc->activeViewNames.GetNext(pos);
		if (viewName.Right(_EXT_LEN5).CompareNoCase(_PAK_EXT) == 0) {
			createNewClassFrame(theAppPtr->pClassDocTemplate,theAppPtr->pCOODClassDoc,viewName);
			if (topViewName.CompareNoCase(viewName) == 0) {
				pTopTemplate = theAppPtr->pClassDocTemplate;
			}
		} else if (viewName.Right(_EXT_LEN5).CompareNoCase(_USE_EXT) == 0) {
			if (doesFileExist(viewName) == TRUE) {
				docPtr = openOrCreateDocumentFile(theAppPtr->pUseCaseDocTemplate,viewName);
				docPtr->SetTitle(viewName);
				if (topViewName.CompareNoCase(viewName) == 0) {
					pTopTemplate = theAppPtr->pUseCaseDocTemplate;
				}
			} else {
				namesToRemove.AddTail(viewName);
			}
		} else if (viewName.Right(_EXT_LEN5).CompareNoCase(_SEQ_EXT) == 0) {
			if (doesFileExist(viewName) == TRUE) {
				docPtr = openOrCreateDocumentFile(theAppPtr->pSequenceDocTemplate,viewName);
				docPtr->SetTitle(viewName);
				if (topViewName.CompareNoCase(viewName) == 0) {
					pTopTemplate = theAppPtr->pSequenceDocTemplate;
				}
			} else {
				namesToRemove.AddTail(viewName);
			}
		} else if (viewName.Right(_EXT_LEN5).CompareNoCase(_COL_EXT) == 0) {
			if (doesFileExist(viewName) == TRUE) {
				docPtr = openOrCreateDocumentFile(theAppPtr->pCollaborationDocTemplate,viewName);
				docPtr->SetTitle(viewName);
				if (topViewName.CompareNoCase(viewName) == 0) {
					pTopTemplate = theAppPtr->pCollaborationDocTemplate;
				}
			} else {
				namesToRemove.AddTail(viewName);
			}
		} else if (viewName.Right(_EXT_LEN5).CompareNoCase(_STA_EXT) == 0) {
			if (doesFileExist(viewName) == TRUE) {
				docPtr = openOrCreateDocumentFile(theAppPtr->pStateDocTemplate,viewName);
				docPtr->SetTitle(viewName);
				if (topViewName.CompareNoCase(viewName) == 0) {
					pTopTemplate = theAppPtr->pStateDocTemplate;
				}
			} else {
				namesToRemove.AddTail(viewName);
			}
		} else if (viewName.Right(_EXT_LEN5).CompareNoCase(_ACT_EXT) == 0) {
			if (doesFileExist(viewName) == TRUE) {
				docPtr = openOrCreateDocumentFile(theAppPtr->pActivityDocTemplate,viewName);
				docPtr->SetTitle(viewName);
				if (topViewName.CompareNoCase(viewName) == 0) {
					pTopTemplate = theAppPtr->pActivityDocTemplate;
				}
			} else {
				namesToRemove.AddTail(viewName);
			}
		} else if (viewName.Right(_EXT_LEN5).CompareNoCase(_DEP_EXT) == 0) {
			if (doesFileExist(viewName) == TRUE) {
				docPtr = openOrCreateDocumentFile(theAppPtr->pDeploymentDocTemplate,viewName);
				docPtr->SetTitle(viewName);
				if (topViewName.CompareNoCase(viewName) == 0) {
					pTopTemplate = theAppPtr->pDeploymentDocTemplate;
				}
			} else {
				namesToRemove.AddTail(viewName);
			}
		} else {
			CString srcViewName = theAppPtr->projectCodegenTargetDir;
			srcViewName = srcViewName + viewName;
			if (doesFileExist(srcViewName) == TRUE) {
				docPtr = theAppPtr->pTextDocTemplate->OpenDocumentFile(srcViewName);
				CString title = docPtr->GetTitle();
				m_wndTreeBar.insertTextName(title);
			} else {
				namesToRemove.AddTail(viewName);
			}
		}
	}

	pos = namesToRemove.GetHeadPosition();
	while (pos != NULL)
	{
		CString viewName = namesToRemove.GetNext(pos);
		theAppPtr->pCOODClassDoc->removeViewName(viewName);
	}

	if (pTopTemplate != NULL) {
		if (pTopTemplate == theAppPtr->pClassDocTemplate) {
			createNewClassFrame(theAppPtr->pClassDocTemplate,theAppPtr->pCOODClassDoc,topViewName);
		} else {
			openOrCreateDocumentFile(pTopTemplate,topViewName);
		}
	}

	setTextOnStatusBar("Ready");
	CString pathFullName = theAppPtr->workspaceDir + "\\" + theAppPtr->workspaceName + _OOD_EXT;
	theAppPtr->addToWorkspaceList(pathFullName);
	return TRUE;
}

void CMainFrame::OnFileOpenWorkspace() 
{
	// TODO: Add your command handler code here
	BOOL canceled = onWindowCloseAll();
	if (canceled == TRUE) return;

	m_wndTreeBar.clearContents();	
	theAppPtr->workspaceName = _T("");

	CString fileName;

	CFileDialog dlgFile(TRUE);
	CString title = "Open workspace";

	dlgFile.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	CString strFilter;
	CString strDefault;

	strFilter += "Workspace (.ood)";
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.ood");
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;

	dlgFile.m_ofn.lpstrFilter = strFilter;
#ifndef _MAC
	dlgFile.m_ofn.lpstrTitle = title;
#else
	dlgFile.m_ofn.lpstrPrompt = title;
#endif
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;
	fileName.ReleaseBuffer();
	
	if (!bResult) return;

	// fileName is full path name of the file.
	onFileOpenWorkspace(fileName);
}


void CMainFrame::OnFileSaveAsWorkspace() 
{
	// TODO: Add your command handler code here
	CString name = "";
	CNewWSDlg newWSDlg(name);
	UINT ans = newWSDlg.DoModal();
	if (ans != IDOK) return;

	COODView *pView = getActiveCOODView();
	if (pView != NIL) {
		theAppPtr->pCOODClassDoc->recentViewName = pView->viewTitle;
	}

	CString oldWSDir = theAppPtr->workspaceDir;
	CString oldWSName = theAppPtr->workspaceName;

	theAppPtr->workspaceDir = newWSDlg.wsLocation;
	theAppPtr->workspaceName = newWSDlg.workspaceName;

	char location[BUFSIZ];
	strcpy_s(location,BUFSIZ,theAppPtr->workspaceDir);
	char subLocation[BUFSIZ];

	if (_mkdir(location) != 0) {
		theAppPtr->workspaceDir = oldWSDir;
		theAppPtr->workspaceName = oldWSName;
		ErrorMsg("Creating new workspace fails.\nCreating a directory fails");
		return;
	} 

	strcpy_s(subLocation,BUFSIZ,location);
	strcat_s(subLocation,BUFSIZ,"\\src");
	if (_mkdir(subLocation) != 0) {
		theAppPtr->workspaceDir = oldWSDir;
		theAppPtr->workspaceName = oldWSName;
		ErrorMsg("Creating new workspace fails.\nCreating a directory fails");
		return;
	} 

	strcpy_s(subLocation,BUFSIZ,location);
	theAppPtr->projectCodegenTargetDir = theAppPtr->workspaceDir + "\\src\\";

	strcat_s(subLocation,BUFSIZ,"\\backup");
	if (_mkdir(subLocation) != 0) {
		theAppPtr->workspaceDir = oldWSDir;
		theAppPtr->workspaceName = oldWSName;
		ErrorMsg("Creating new workspace fails.\nCreating a directory fails");
		return;
	} 
	
	if (_chdir(location) != 0) {
		theAppPtr->workspaceDir = oldWSDir;
		theAppPtr->workspaceName = oldWSName;
		ErrorMsg("Change directory to workspace fails.");
		return;
	}

	CString pathFullName = theAppPtr->workspaceDir + "\\" + theAppPtr->workspaceName + _OOD_EXT;
	theAppPtr->addToWorkspaceList(pathFullName);
	theAppPtr->pCOODClassDoc->setRootStg(pathFullName);
	POSITION pos = theAppPtr->pUseCaseDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pUseCaseDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		CString title = ((COODCommonDoc *)pDoc)->getFirstView()->viewTitle;
		CString fullName = theAppPtr->workspaceDir + "\\" + title;
		((COODCommonDoc *)pDoc)->setRootStg(fullName);
	}
	pos = theAppPtr->pCollaborationDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pCollaborationDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		CString title = ((COODCommonDoc *)pDoc)->getFirstView()->viewTitle;
		CString fullName = theAppPtr->workspaceDir + "\\" + title;
		((COODCommonDoc *)pDoc)->setRootStg(fullName);
	}
	pos = theAppPtr->pSequenceDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pSequenceDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		CString title = ((COODCommonDoc *)pDoc)->getFirstView()->viewTitle;
		CString fullName = theAppPtr->workspaceDir + "\\" + title;
		((COODCommonDoc *)pDoc)->setRootStg(fullName);
	}
	pos = theAppPtr->pStateDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pStateDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		CString title = ((COODCommonDoc *)pDoc)->getFirstView()->viewTitle;
		CString fullName = theAppPtr->workspaceDir + "\\" + title;
		((COODCommonDoc *)pDoc)->setRootStg(fullName);
	}
	pos = theAppPtr->pActivityDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pActivityDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		CString title = ((COODCommonDoc *)pDoc)->getFirstView()->viewTitle;
		CString fullName = theAppPtr->workspaceDir + "\\" + title;
		((COODCommonDoc *)pDoc)->setRootStg(fullName);
	}
	pos = theAppPtr->pDeploymentDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pDeploymentDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		CString title = ((COODCommonDoc *)pDoc)->getFirstView()->viewTitle;
		CString fullName = theAppPtr->workspaceDir + "\\" + title;
		((COODCommonDoc *)pDoc)->setRootStg(fullName);
	}
	pos = theAppPtr->pTextDocTemplate->GetFirstDocPosition();
	while (pos != NULL) 
	{
		CDocument* pDoc = theAppPtr->pTextDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(CTextDoc))) break;
		CString title = pDoc->GetTitle();
		CString fullName = theAppPtr->workspaceDir + "\\" + title;
		((CTextDoc*)pDoc)->SetPathName(fullName,FALSE);
	}

	OnFileSaveWorkspace();
}

void CMainFrame::setModifiedFlagForAllDocAndInvalidate()
{
	POSITION pos = theAppPtr->pUseCaseDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pUseCaseDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setModifiedFlag();
		COODView *pView = ((COODCommonDoc *)pDoc)->getFirstView();
		if (pView != NIL) pView->Invalidate();
	}
	pos = theAppPtr->pCollaborationDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pCollaborationDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setModifiedFlag();
		COODView *pView = ((COODCommonDoc *)pDoc)->getFirstView();
		if (pView != NIL) pView->Invalidate();
	}
	pos = theAppPtr->pSequenceDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pSequenceDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setModifiedFlag();
		COODView *pView = ((COODCommonDoc *)pDoc)->getFirstView();
		if (pView != NIL) pView->Invalidate();
	}
	pos = theAppPtr->pStateDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pStateDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setModifiedFlag();
		COODView *pView = ((COODCommonDoc *)pDoc)->getFirstView();
		if (pView != NIL) pView->Invalidate();
	}
	pos = theAppPtr->pActivityDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pActivityDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setModifiedFlag();
		COODView *pView = ((COODCommonDoc *)pDoc)->getFirstView();
		if (pView != NIL) pView->Invalidate();
	}
	pos = theAppPtr->pDeploymentDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pDeploymentDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setModifiedFlag();
		COODView *pView = ((COODCommonDoc *)pDoc)->getFirstView();
		if (pView != NIL) pView->Invalidate();
	}
	pos = theAppPtr->pObjectDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pObjectDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setModifiedFlag();
		COODView *pView = ((COODCommonDoc *)pDoc)->getFirstView();
		if (pView != NIL) pView->Invalidate();
	}
	if (theAppPtr->pCOODClassDoc != NIL) {
		theAppPtr->pCOODClassDoc->setModifiedFlagForAllView(TRUE);
		theAppPtr->pCOODClassDoc->UpdateAllViews(NULL);
	}
}

void CMainFrame::setShapeBackground(COLORREF bkcolor)
{
	POSITION pos = theAppPtr->pUseCaseDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pUseCaseDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeBackground(bkcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pCollaborationDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pCollaborationDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeBackground(bkcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pSequenceDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pSequenceDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeBackground(bkcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pStateDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pStateDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeBackground(bkcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pActivityDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pActivityDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeBackground(bkcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pDeploymentDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pDeploymentDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeBackground(bkcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pObjectDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pObjectDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeBackground(bkcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	if (theAppPtr->pCOODClassDoc != NIL) {
		theAppPtr->pCOODClassDoc->setShapeBackground(bkcolor);	
		theAppPtr->pCOODClassDoc->setModifiedFlagForAllView(TRUE);
	}
}

void CMainFrame::setShapeForeground(COLORREF fgcolor)
{
	POSITION pos = theAppPtr->pUseCaseDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pUseCaseDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeForeground(fgcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pCollaborationDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pCollaborationDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeForeground(fgcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pSequenceDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pSequenceDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeForeground(fgcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pStateDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pStateDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeForeground(fgcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pActivityDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pActivityDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeForeground(fgcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pDeploymentDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pDeploymentDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeForeground(fgcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	pos = theAppPtr->pObjectDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pObjectDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->setShapeForeground(fgcolor);
		((COODCommonDoc *)pDoc)->setModifiedFlag();
	}
	if (theAppPtr->pCOODClassDoc != NIL) {
		theAppPtr->pCOODClassDoc->setShapeForeground(fgcolor);	
		theAppPtr->pCOODClassDoc->setModifiedFlagForAllView(TRUE);
	}
}

void CMainFrame::OnFileSaveWorkspace() 
{
	// TODO: Add your command handler code here
	COODView *pView = getActiveCOODView();
	if (pView != NIL) {
		theAppPtr->pCOODClassDoc->recentViewName = pView->viewTitle;
	}
	POSITION pos = theAppPtr->pUseCaseDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pUseCaseDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->onFileSave();
	}
	pos = theAppPtr->pCollaborationDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pCollaborationDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->onFileSave();
	}
	pos = theAppPtr->pSequenceDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pSequenceDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->onFileSave();
	}
	pos = theAppPtr->pStateDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pStateDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->onFileSave();
	}
	pos = theAppPtr->pActivityDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pActivityDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->onFileSave();
	}
	pos = theAppPtr->pDeploymentDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = theAppPtr->pDeploymentDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) break;
		((COODCommonDoc *)pDoc)->onFileSave();
	}
	pos = theAppPtr->pTextDocTemplate->GetFirstDocPosition();
	while (pos != NULL) 
	{
		CDocument* pDoc = theAppPtr->pTextDocTemplate->GetNextDoc(pos);
		if (!pDoc->IsKindOf(RUNTIME_CLASS(CTextDoc))) break;
		((CTextDoc *)pDoc)->onFileSave();
	}
	theAppPtr->pCOODClassDoc->onFileSaveClassDocument();	
}


void CMainFrame::OnUpdateFileSaveAsWorkspace(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (theAppPtr->workspaceName.GetLength() == 0) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
}

void CMainFrame::OnUpdateFileSaveWorkspace(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (theAppPtr->workspaceName.GetLength() == 0) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
}

void CMainFrame::OnUpdateFileCloseWorkspace(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (theAppPtr->workspaceName.GetLength() == 0) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}	
}

void CMainFrame::OnClassToolsOptions() 
{
	// TODO: Add your command handler code here
	CProjectOptionsDlg options;
	options.DoModal();
}

void CMainFrame::OnOptionsProject() 
{
	// TODO: Add your command handler code here
	OnClassToolsOptions();
}

void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	SetActiveWindow();
	UINT count = ::DragQueryFile(hDropInfo,(UINT)-1,NULL,0);
	CWinApp* pApp = AfxGetApp();
	UINT i;
	for (i = 0; i < count; i++) {
		TCHAR szFileName[_MAX_PATH];
		::DragQueryFile(hDropInfo,i,szFileName,_MAX_PATH);
		CString fileName = szFileName;
		CString extension = fileName.Right(_EXT_LEN4); 
		if (extension.CompareNoCase(_OOD_EXT) == 0) {
			BOOL canceled = onWindowCloseAll();
			if (canceled == TRUE) {
				::DragFinish(hDropInfo);
				return;
			}
			onFileOpenWorkspace(fileName);
			break;
		}
	}
	for (i = 0; i < count; i++) {
		TCHAR szFileName[_MAX_PATH];
		::DragQueryFile(hDropInfo,i,szFileName,_MAX_PATH);
		CString fileName = szFileName;
		CString extension = fileName.Right(_EXT_LEN4); 
		if (extension.CompareNoCase(_OOD_EXT) != 0) {
			openDocumentFile(fileName);
		}
	}
	::DragFinish(hDropInfo);
}


void CMainFrame::OnViewCustombar() 
{
	// TODO: Add your command handler code here
	
	ShowControlBar(&m_wndCustomBar,
		(m_wndCustomBar.GetStyle() & WS_VISIBLE) == 0, 
		FALSE);	
}

void CMainFrame::OnUpdateViewCustombar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck((m_wndCustomBar.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::saveImageToFileAndClipboard(CString &fileName,CBitmap &imageBitmap)
{
	CFile fileObj;
	HANDLE hDIB;
	BITMAPFILEHEADER bmfileHdr;
	BYTE *lptrData;

	if (!OpenClipboard()) {
		ErrorMsg("Can't open clipboard.");
		return;
	}
	EmptyClipboard();
	SetClipboardData(CF_BITMAP,imageBitmap.m_hObject);
	CloseClipboard();

	OpenClipboard();
	if (!IsClipboardFormatAvailable(CF_DIB)) {
		ErrorMsg("Clipboard data has not DIB format.");
		return;
	}
	hDIB = ::GetClipboardData(CF_DIB);
	if (!hDIB) {
		CloseClipboard();
		ErrorMsg("Can't get clipboard data.");
		return;
	}
	CloseClipboard();

	bmfileHdr.bfType = 0x4D42; // 이 숫자는 "BM" 이란다. 메모리 역전을 고려해서 ... 42(B)4D(M)
	bmfileHdr.bfSize = sizeof(BITMAPFILEHEADER) + GlobalSize(hDIB);
	bmfileHdr.bfReserved1 = 0;
	bmfileHdr.bfReserved2 = 0;
	bmfileHdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	lptrData = (BYTE *)GlobalLock(hDIB);
	if (!fileObj.Open(fileName,CFile::modeCreate|CFile::modeWrite)) {
		ErrorMsg("Unable to open file.");
		return;
	}
	
	fileObj.Write(&bmfileHdr,sizeof(BITMAPFILEHEADER));
	fileObj.Write(lptrData,GlobalSize(hDIB));
	fileObj.Close();

	GlobalUnlock(hDIB);
	GlobalFree(hDIB);
}

void CMainFrame::OnScreenshot() 
{
	// TODO: Add your command handler code here
	COODView *currentView = getActiveCOODView();
	BOOL flag;
	if (currentView == NIL) flag = FALSE;
	else flag = TRUE;

	CString defaultFileName = "";
	if (theAppPtr->workspaceDir.IsEmpty()) {
		defaultFileName = "capture.bmp";
	} else {
		defaultFileName = theAppPtr->workspaceDir + "\\" + "capture.bmp";
	}
	ScreenCaptureDlg aDlg(defaultFileName,flag);
	UINT ans = aDlg.DoModal();
	if (ans == IDCANCEL) return;
	if (aDlg.getViewFlag()) {
		currentView->saveViewBMP(aDlg.m_editBMPFileName);
		return;
	}
	saveUserRectBMP(aDlg.m_editBMPFileName);
}

void CMainFrame::saveUserRectBMP(CString &fileName)
{
	setTextOnStatusBar("Press LBUTTON and drag mouse to set user rectangle");
	CaptureDlg captureDlg;
	UINT ans = captureDlg.DoModal();
	setTextOnStatusBar("Ready");
	if (ans != IDOK) {
		InfoMsg("Screen capture aborted !");
		return;
	}
	saveImageToFileAndClipboard(fileName,captureDlg.resultBitmap);
}

void CMainFrame::OnInitMenu(CMenu* pMenu) 
{
	CResizableMDIFrameWnd::OnInitMenu(pMenu);
	
	// TODO: Add your message handler code here
	CFrameWnd *pFrameWnd = GetActiveFrame();
	if (pFrameWnd == NIL) return;
	if (!pFrameWnd->IsKindOf(RUNTIME_CLASS(COODCommonFrm))) return; // 사실 여기까지만 체크하면되는데 확인 사살차원에서 한번 체크

	CView *pView = pFrameWnd->GetActiveView();
	if (pView == NIL) return;
	CDocument *pDocument = pView->GetDocument();
	if (pDocument == NIL) return;
	if (!pDocument->IsKindOf(RUNTIME_CLASS(COODCommonDoc)))	return;
	COODCommonDoc *pDoc = (COODCommonDoc *)pDocument;
	if (!pDoc->IsEmbedded()) return;

	((COODCommonFrm *)pFrameWnd)->onInitMenu(pMenu);
}

void CMainFrame::OnUpdateControlBarMenu(CCmdUI* pCmdUI)
{
	if (theAppPtr->runAsServerFlag) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
	CResizableMDIFrameWnd::OnUpdateControlBarMenu(pCmdUI);
}

void CMainFrame::OnClassRootNewPackage() 
{
	// TODO: Add your command handler code here

	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_ROOT_NEW_PACKAGE,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnUpdateClassRootNewPackage(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (theAppPtr->workspaceName.GetLength() == 0) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
}

void CMainFrame::OnBarAllowdocking() 
{
	// TODO: Add your command handler code here
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_BAR_ALLOWDOCKING,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnBarHide() 
{
	// TODO: Add your command handler code here
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_BAR_HIDE,0);	
}


void CMainFrame::OnPackageNewClass() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_PACKAGE_NEW_CLASS,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnPackageOpen() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_PACKAGE_OPEN,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnPackageProperties() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_PACKAGE_PROPERTIES,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnClassAddMemberFunction() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_ADD_MEMBER_FUNCTION,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnClassAddMemberVariable() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_ADD_MEMBER_VARIABLE,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnClassGoToDefinition() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_GO_TO_DEFINITION,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnClassProperties() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_PROPERTIES,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnClassRelatedClasses() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_RELATED_CLASSES,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnDataProperties() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_DATA_PROPERTIES,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnFunctionProperties() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_FUNCTION_PROPERTIES,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnDiagramDelete() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_DIAGRAM_DELETE,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnDiagramOpen() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_DIAGRAM_OPEN,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnDiagramTypeNewDiagram() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_DIAGRAM_TYPE_NEW_DIAGRAM,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnFileMenuDelete() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_FILE_MENU_DELETE,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnFileMenuOpen() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_FILE_MENU_OPEN,0);
	m_wndTreeBar.Invalidate();
}

void CMainFrame::OnFileTypeNewFile() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_FILE_TYPE_NEW_FILE,0);
	m_wndTreeBar.Invalidate();
}


void CMainFrame::OnMemberDelete() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_MEMBER_DELETE,0);
	m_wndTreeBar.Invalidate();
}


void CMainFrame::OnClassDelete() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_DELETE,0);
	m_wndTreeBar.Invalidate();
}


void CMainFrame::OnPackageDelete() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_PACKAGE_DELETE,0);
	m_wndTreeBar.Invalidate();
}


void CMainFrame::OnClassMigrate() 
{
	// TODO: Add your command handler code here
	
	::SendMessage(m_wndTreeBar.m_hWnd,WM_COMMAND,ID_CLASS_MIGRATE,0);
	m_wndTreeBar.Invalidate();
}
