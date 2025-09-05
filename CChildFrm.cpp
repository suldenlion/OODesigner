// CChildFrm.cpp : implementation of the CChildFrm class
//

#include "stdafx.h"
#include "OOD.h"

#include "KtgMacro.h"
#include "CChildFrm.h"
#include "CMainFrame.h"
#include "COODView.h"
#include "COODCommonDoc.h"
#include "CTextDoc.h"
#include "FigureList.h"
#include "CActivityView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrm

IMPLEMENT_DYNCREATE(CChildFrm, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrm)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_CLOSE()
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrm construction/destruction

CChildFrm::CChildFrm()
{
	// TODO: add member initialization code here
	_diagramType = _T("");
	frameName = _T("");
	frameTitle = _T("");
}

CChildFrm::~CChildFrm()
{
}

BOOL CChildFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrm diagnostics

#ifdef _DEBUG
void CChildFrm::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrm::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrm message handlers

void CChildFrm::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// Update our parent window first
	GetMDIFrame()->OnUpdateFrameTitle(bAddToTitle);
	if ((GetStyle() & FWS_ADDTOTITLE) == 0)
		return; // leave it alone!
	AfxSetWindowText(m_hWnd,(LPCTSTR)frameTitle);
}

void CChildFrm::OnFileNew() 
{
	// TODO: Add your command handler code here
	mainFramePtr->onFileNew();
}

void CChildFrm::OnFileOpen() 
{
	// TODO: Add your command handler code here
	mainFramePtr->onFileOpen();	
}

void CChildFrm::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (theAppPtr->runAsServerFlag) {
		mainFramePtr->onClose();
		return;
	}

	CDocument *aDoc = GetActiveView()->GetDocument();
	if (aDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		((COODCommonDoc *)aDoc)->onWindowClose(TRUE);
	} else if (aDoc->IsKindOf(RUNTIME_CLASS(CTextDoc))) {
		((CTextDoc *)aDoc)->onWindowClose(TRUE);
	} else {
		CMDIChildWnd::OnClose();
	}
}

void CChildFrm::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	// TODO: Add your message handler code here
	CControlBar *pBar = getModelToolBar();
	if (pBar == NIL) return;
	if (bActivate) {
		CView *pView = GetActiveView();
		if (pView != NIL && pView->IsKindOf(RUNTIME_CLASS(COODView))) {
			COODView *theView = (COODView *)pView;
			int zoomRatioX = theView->zoomRatioX();
			int zoomRatioY = theView->zoomRatioY();
			char value[BUFSIZ];
			if (zoomRatioX == zoomRatioY) {
				sprintf_s(value,BUFSIZ,"%d",zoomRatioX);
			} else {
				strcpy_s(value,BUFSIZ,"auto");
			}
			mainFramePtr->setZoomValue(value);
		}
		mainFramePtr->ShowControlBar(pBar,TRUE,TRUE);
	} else {
		mainFramePtr->ShowControlBar(pBar,FALSE,TRUE);
	}
}
