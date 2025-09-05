// CInPlaceFrame.cpp : implementation file
//

#include "stdafx.h"
#include <afxpriv.h>
#include "OOD.h"
#include "KtgMacro.h"
#include "CInPlaceFrame.h"
#include "COODView.h"
#include "COODCommonDoc.h"

#define N_OOD_SRVR_IP_MENU_ITEM (5)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleIPFrameWnd)

CInPlaceFrame::CInPlaceFrame()
{
	_onActivateCalledFlag = FALSE;
	_insertMenuID = _T("");
}

CInPlaceFrame::~CInPlaceFrame()
{
}


BEGIN_MESSAGE_MAP(CInPlaceFrame, COleIPFrameWnd)
	//{{AFX_MSG_MAP(CInPlaceFrame)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_VIEW_MODEL_TOOLBAR, OnViewModelToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODEL_TOOLBAR, OnUpdateViewModelToolbar)
	ON_COMMAND(ID_VIEW_CUSTOMBAR, OnViewCustombar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CUSTOMBAR, OnUpdateViewCustombar)
	ON_WM_INITMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_POSITION,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

void CInPlaceFrame::getZoomValue(CString &value)
{
	m_wndCustomBar.getZoomValue(value);
}

void CInPlaceFrame::setZoomValue(const char *value)
{
	m_wndCustomBar.setZoomValue(value);
}

void CInPlaceFrame::setZoomValue(COODView *pView)
{
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

void CInPlaceFrame::setZoomValue(CDocument *pDoc)
{
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

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame message handlers

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COleIPFrameWnd::PreCreateWindow(cs);
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar implements in-place resizing.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // fail to create
	}
	
	// By default, it is a good idea to register a drop-target that does
	//  nothing with your frame window.  This prevents drops from
	//  "falling through" to a container that supports drag-drop.
	m_dropTarget.Register(this);

	_insertMenuID = _T("");

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame diagnostics

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
	COleIPFrameWnd::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleIPFrameWnd::Dump(dc);
}
#endif //_DEBUG

void CInPlaceFrame::setTextOnStatusBar(const char *text,int field)
{
	m_wndStatusBar.GetStatusBarCtrl().SetText(text,field,0);
}

void CInPlaceFrame::setPositionOnStatusBar(int x,int y,int field)
{
	char buffer[BUFSIZ];
	sprintf_s(buffer,BUFSIZ,"%4d, %4d",x,y);
	m_wndStatusBar.GetStatusBarCtrl().SetText(buffer,field,0);
}

void CInPlaceFrame::userMsg(const char *s)
{
	setTextOnStatusBar(s);
}

void CInPlaceFrame::userMsg(const char *s,int n)
{
	char buffer[BUFSIZ];
	sprintf_s(buffer,BUFSIZ,"%s%d",s,n);
	setTextOnStatusBar(buffer);
}

void CInPlaceFrame::userMsgForUsingUpperCaseAsBlank(char *s,char *comment)
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

BOOL CInPlaceFrame::createModelControlBar(CFrameWnd* pWndFrame)
{
	UINT resourceID = -1;
	CDocument *pDoc = GetActiveDocument();
	if (pDoc == NULL) return FALSE;
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) return FALSE;
	COODCommonDoc *pOODDoc = (COODCommonDoc *)pDoc;

	CString extension = pOODDoc->getExtension();
	if (extension.CompareNoCase(_PAK_EXT) == 0) {
		resourceID = IDR_TB_CLASS;
	} else if (extension.CompareNoCase(_USE_EXT) == 0) {
		resourceID = IDR_TB_USECASE;
	} else if (extension.CompareNoCase(_SEQ_EXT) == 0) {
		resourceID = IDR_TB_SEQUENCE;
	} else if (extension.CompareNoCase(_COL_EXT) == 0) {
		resourceID = IDR_TB_COLLABORATION;
	} else if (extension.CompareNoCase(_STA_EXT) == 0) {
		resourceID = IDR_TB_STATE;
	} else if (extension.CompareNoCase(_ACT_EXT) == 0) {
		resourceID = IDR_TB_ACTIVITY;
	} else if (extension.CompareNoCase(_DEP_EXT) == 0) {
		resourceID = IDR_TB_DEPLOYMENT;
	} else {
		return FALSE;
	}

	if (!modelDiagramToolBar.Create(pWndFrame,WS_CHILD | CBRS_TOP) ||
		!modelDiagramToolBar.LoadToolBar(resourceID))
	{
		return FALSE;
	}
	return TRUE;
}

// OnCreateControlBars is called by the framework to create control bars on the
//  container application's windows.  pWndFrame is the top level frame window of
//  the container and is always non-NULL.  pWndDoc is the doc level frame window
//  and will be NULL when the container is an SDI application.  A server
//  application can place MFC control bars on either window.

BOOL CInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// Remove this if you use pWndDoc
	UNREFERENCED_PARAMETER(pWndDoc);

	// Set owner to this window, so messages are delivered to correct app
	m_wndToolBar.SetOwner(pWndFrame);

	// Create toolbar on client's frame window
	if (!m_wndToolBar.Create(pWndFrame) ||
		!m_wndToolBar.LoadToolBar(IDR_OOD_SRVR_IP))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}
	m_wndCustomBar.SetOwner(this);
	if (!m_wndCustomBar.Create(pWndFrame) ||
		!m_wndCustomBar.LoadToolBar(IDR_TB_CUSTOM)) 
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;      // fail to create
	}
	m_wndCustomBar.makeZoomComboBox(this,2,ID_COMBO_ZOOM,CSize(60,100));
	CDocument *pDoc = GetActiveDocument();
	if (pDoc != NIL) {
		setZoomValue(pDoc);
	} else {
		setZoomValue("100");
	}

	modelDiagramToolBar.SetOwner(this);
	if (!createModelControlBar(pWndFrame)) 
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;      // fail to create
	}

	m_wndStatusBar.SetOwner(this);
	if (!m_wndStatusBar.Create(pWndFrame) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndCustomBar.SetBarStyle(m_wndCustomBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	modelDiagramToolBar.SetBarStyle(modelDiagramToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCustomBar.EnableDocking(CBRS_ALIGN_ANY);
	modelDiagramToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndToolBar);
	pWndFrame->DockControlBar(&m_wndCustomBar);
	pWndFrame->DockControlBar(&modelDiagramToolBar);

	return TRUE;
}

CToolBarCtrl *CInPlaceFrame::getModelToolBarCtrl() {
	if (modelDiagramToolBar.GetSafeHwnd() != NULL)
		return &modelDiagramToolBar.GetToolBarCtrl();
	return NIL;
}

void CInPlaceFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	COleIPFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	setTextOnStatusBar("Ready");

	// TODO: Add your message handler code here
	if (_onActivateCalledFlag) return;
	_onActivateCalledFlag = TRUE;

	// 원래는 아래작업을 OnCreateControlBar() 마지막에서 해야되는데 ...
	// 크기가 구해지지 않아서 ... 여기에 ...
	CRect targetRect;
	CRect sourceRect;
	RecalcLayout(); // parameters are meaningless
	m_pMainFrame->RecalcLayout(); // parameters are meaningless
	m_wndToolBar.GetWindowRect(&targetRect);
	m_wndCustomBar.GetWindowRect(&sourceRect);
	targetRect.left = targetRect.right - 1;
	targetRect.right = targetRect.left + (sourceRect.right - sourceRect.left);
	m_pMainFrame->DockControlBar(&m_wndCustomBar,(UINT)0,(LPCRECT)&targetRect);

	RecalcLayout();
	m_wndCustomBar.GetWindowRect(&targetRect);
	modelDiagramToolBar.GetWindowRect(&sourceRect);
	targetRect.left = targetRect.right - 1;
	targetRect.right = targetRect.left + (sourceRect.right - sourceRect.left);
	m_pMainFrame->DockControlBar(&modelDiagramToolBar,(UINT)0,(LPCRECT)&targetRect);
	m_pMainFrame->ShowControlBar(&modelDiagramToolBar,TRUE,TRUE);

	CMenu *pMenu = m_pMainFrame->GetMenu();
	if (pMenu == NULL) return;
	int nMenu = pMenu->GetMenuItemCount();
	for (int i = N_OOD_SRVR_IP_MENU_ITEM + 1; i < nMenu; i++) {
		pMenu->EnableMenuItem(i,MF_BYPOSITION|MF_GRAYED);
	}
	DrawMenuBar();
}

void CInPlaceFrame::OnViewModelToolbar() 
{
	// TODO: Add your command handler code here
	
	m_pMainFrame->ShowControlBar(&modelDiagramToolBar,
		(modelDiagramToolBar.GetStyle() & WS_VISIBLE) == 0, 
		FALSE);		
}

void CInPlaceFrame::OnUpdateViewModelToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((modelDiagramToolBar.GetStyle() & WS_VISIBLE) != 0);	
}

void CInPlaceFrame::OnViewCustombar() 
{
	// TODO: Add your command handler code here
	
	ShowControlBar(&m_wndCustomBar,
		(m_wndCustomBar.GetStyle() & WS_VISIBLE) == 0, 
		FALSE);	
}

void CInPlaceFrame::OnUpdateViewCustombar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck((m_wndCustomBar.GetStyle() & WS_VISIBLE) != 0);
}

void CInPlaceFrame::insertInsertPulldownMenu(CMenu *pInsertMenu)
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

void CInPlaceFrame::OnInitMenu(CMenu* pMenu) 
{
	COleIPFrameWnd::OnInitMenu(pMenu);
	
	// TODO: Add your message handler code here
	
	CDocument *pDoc = GetActiveDocument();
	if (pDoc == NULL) return;
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) return;
	COODCommonDoc *pOODDoc = (COODCommonDoc *)pDoc;
	
	CString extension = pOODDoc->getExtension();
	if (extension.CompareNoCase(_insertMenuID) == 0) return;

	CMenu *pMainMenu = m_pMainFrame->GetMenu();
	if (pMainMenu == NULL) return;

	CMenu *pSubMenu = pMainMenu->GetSubMenu(INSERT_MENU_POS);
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

