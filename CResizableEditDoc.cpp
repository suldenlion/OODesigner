// CResizableEditDoc.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CMainFrame.h"
#include "KtgMacro.h"
#include "CResizableEditDoc.h"
#include "CResizableEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizableEditDoc

IMPLEMENT_DYNCREATE(CResizableEditDoc, CDocument)

CResizableEditDoc::CResizableEditDoc()
{
	_pBar = NULL;
}

BOOL CResizableEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CResizableEditDoc::~CResizableEditDoc()
{
}

void CResizableEditDoc::showControlFrame(BOOL bShow)
{
	if (_pBar == NULL) {
		TRACE0("Error : CResizableEditDoc::showControlFrame");
		return;
	}
	CFrameWnd* pFrameWnd = _pBar->GetDockingFrame();
	pFrameWnd->ShowControlBar(_pBar, bShow, TRUE);
}


BEGIN_MESSAGE_MAP(CResizableEditDoc, CDocument)
	//{{AFX_MSG_MAP(CResizableEditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizableEditDoc diagnostics

#ifdef _DEBUG
void CResizableEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CResizableEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResizableEditDoc serialization

void CResizableEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CResizableEditDoc commands

CResizableEditView * CResizableEditDoc::getFirstView()
{ 
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL) return NIL;
	CView* pFirstView = GetNextView(pos);
	if (pFirstView == NULL) return NIL;
	ASSERT(pFirstView->IsKindOf(RUNTIME_CLASS(CResizableEditView)));
	return (CResizableEditView*) pFirstView;
}

void CResizableEditDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
    CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->SetActiveView(NULL,FALSE);

	BOOL bAutoDelete = m_bAutoDelete;
	m_bAutoDelete = FALSE;
	while(!m_viewList.IsEmpty()) {
		CView *pView = (CView*)m_viewList.GetHead();
		ASSERT_VALID(pView);
		CControlBar *pBar = (CControlBar *)pView->GetParent();
		ASSERT_KINDOF(CControlBar,pBar);

		pBar->DestroyWindow();
		delete pBar;
	}
	m_bAutoDelete = bAutoDelete;

	DeleteContents(); 
	if(m_bAutoDelete) delete this;
}

BOOL CResizableEditDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

void CResizableEditDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	SetModifiedFlag(FALSE);
	CDocument::DeleteContents();
}

BOOL CResizableEditDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModifiedFlag(FALSE);
	DeleteContents(); 
	return CDocument::SaveModified();
}
