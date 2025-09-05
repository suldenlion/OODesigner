#include "stdafx.h"
#include "resource.h"
#include "CMainFrame.h"
#include "CResizeEditViewBarDocTemp.h"
#include "CResizableEditViewBar.h"
#include "CResizableEditDoc.h"

#define WS_RESIZABLE_EDIT_VIEW (AFX_WS_DEFAULT_VIEW|WS_HSCROLL|WS_VSCROLL|ES_WANTRETURN|ES_MULTILINE)

IMPLEMENT_DYNAMIC(CResizableEditViewBarDocTemplate,CMultiDocTemplate)

CResizableEditViewBarDocTemplate::CResizableEditViewBarDocTemplate(UINT nID,
									CRuntimeClass* pDocClass,
									CRuntimeClass* pFrameClass,
									CRuntimeClass* pViewClass)
:CMultiDocTemplate(nID,pDocClass,pFrameClass,pViewClass)
{
	// empty
}

CResizableEditViewBarDocTemplate::~CResizableEditViewBarDocTemplate()
{
	delete pBar;
}

CDocument *CResizableEditViewBarDocTemplate::OpenDocumentFile(LPCTSTR lpszPathName,
		BOOL bMakeVisible)
{
	CDocument *pDocument = CreateNewDocument();
	if (pDocument == NULL) {
		TRACE0("CDocTemplate::CreateNewDocument() fails.\n");
		return NULL;
	}
	ASSERT_VALID(pDocument);


	BOOL bAutoDelete = pDocument->m_bAutoDelete;
	pDocument->m_bAutoDelete = FALSE;

	pBar = new CResizableEditViewBar();
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pMainFrame != NULL);
	VERIFY(pBar->Create(NULL,NULL,
			/*WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN|*/CBRS_BOTTOM,
			CFrameWnd::rectDefault,
			pMainFrame,ID_VIEW_DOCUMENTATION));

	CView *pView = (CView *)m_pViewClass->CreateObject();
	if (pView == NULL) {
		TRACE1("Warning: Dynamic create of view type %hs failed.\n",
				m_pViewClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CWnd,pView);

	CCreateContext ccontext;
	ccontext.m_pCurrentDoc = pDocument;

	if (!pView->Create(NULL, NULL, WS_RESIZABLE_EDIT_VIEW,
		CRect(0,0,0,0), pBar, -1 /*AFX_IDW_PANE_FIRST*/ , &ccontext))
	{
		TRACE0("Warning: could not create view for frame.\n");
		return NULL;        // can't continue without a view
	}

	pBar->m_pChildView = pView;
	pBar->EnableDocking(CBRS_ALIGN_ANY);
	pMainFrame->DockControlBar(pBar);

	pDocument->m_bAutoDelete = bAutoDelete;

	if (lpszPathName == NULL)
	{
		SetDefaultTitle(pDocument);

		if (!bMakeVisible)
			pDocument->m_bEmbedded = TRUE;

		if (!pDocument->OnNewDocument())
		{
			TRACE0("CDocument::OnNewDocument returned FALSE.\n");
			return NULL;
		}
		m_nUntitledCount++;
	}
	else
	{
		CWaitCursor wait;
		if (!pDocument->OnOpenDocument(lpszPathName))
		{
			TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
			return NULL;
		}
#ifdef _MAC
		if (!pDocument->IsModified())
#endif
			pDocument->SetPathName(lpszPathName,FALSE);
	}

    pBar->SetWindowText(pDocument->GetTitle());

	if (bMakeVisible)
	{
		pBar->SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);
	}

	if (pDocument != NULL)
		pDocument->UpdateFrameCounts();
	
	if (pDocument->IsKindOf(RUNTIME_CLASS(CResizableEditDoc))) {
		((CResizableEditDoc *)pDocument)->setControlBar(pBar);
	}
	return pDocument; 
}

CFrameWnd* CResizableEditViewBarDocTemplate::CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther)
{
	return NULL;
}
