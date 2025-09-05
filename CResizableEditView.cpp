// CResizableEditView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CResizableEditView.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizableEditView

IMPLEMENT_DYNCREATE(CResizableEditView, CEditView)

CResizableEditView::CResizableEditView()
{
}

CResizableEditView::~CResizableEditView()
{
}


BEGIN_MESSAGE_MAP(CResizableEditView, CEditView)
	//{{AFX_MSG_MAP(CResizableEditView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizableEditView drawing

void CResizableEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CResizableEditView diagnostics

#ifdef _DEBUG
void CResizableEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CResizableEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResizableEditView message handlers

BOOL CResizableEditView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pMsg->message == WM_KEYDOWN) {
		return -1;
	}
	return CEditView::PreTranslateMessage(pMsg);
}
