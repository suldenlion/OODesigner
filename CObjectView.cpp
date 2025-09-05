// CObjectView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CObjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectView

IMPLEMENT_DYNCREATE(CObjectView, CClassView)

CObjectView::CObjectView()
: CClassView()
{
}

CObjectView::~CObjectView()
{
}


BEGIN_MESSAGE_MAP(CObjectView, CClassView)
	//{{AFX_MSG_MAP(CObjectView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectView drawing

void CObjectView::OnInitialUpdate()
{
	CClassView::OnInitialUpdate();
}

void CObjectView::OnDraw(CDC* pDC)
{
	// TODO: add draw code here
	CClassView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CObjectView diagnostics

#ifdef _DEBUG
void CObjectView::AssertValid() const
{
	CClassView::AssertValid();
}

void CObjectView::Dump(CDumpContext& dc) const
{
	CClassView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObjectView message handlers
