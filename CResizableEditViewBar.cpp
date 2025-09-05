// CResizableEditViewBar.cpp : implementation file
//

#include "stdafx.h"
#include "CResizableEditViewBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CResizableEditViewBar,CResizableControlBar)
/////////////////////////////////////////////////////////////////////////////
// CResizableEditViewBar

CResizableEditViewBar::CResizableEditViewBar()
:CResizableControlBar(/*SZBARF_DESTROY_ON_CLOSE|SZBARF_AUTOTIDY|*/SZBARF_STDMOUSECLICKS)
{
//TRACE0("CResizableEditViewBar::CResizableEditViewBar\n");
	   m_pChildView = NULL;
}

CResizableEditViewBar::~CResizableEditViewBar()
{
//TRACE0("CResizableEditViewBar::~CResizableEditViewBar\n");
}


BEGIN_MESSAGE_MAP(CResizableEditViewBar, CResizableControlBar)
	//{{AFX_MSG_MAP(CResizableEditViewBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResizableEditViewBar message handlers

int CResizableEditViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
//TRACE0("CResizableEditViewBar::OnCreate\n");
	if (CResizableControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CResizableEditViewBar::OnSizedOrDocked(int cx,int cy,BOOL bFloating,int flags)
{
//TRACE0("CResizableEditViewBar::OnSizedOrDocked\n");
	CRect rect(0,0,cx,cy);
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	if (IsProbablyFloating()) {
		rect.InflateRect(-2,-2);
	} else {
		rect.InflateRect(-4,-4);
	}
	if (m_pChildView != NULL && m_pChildView->m_hWnd != NULL) 
		m_pChildView->MoveWindow(&rect);
}

BOOL CResizableEditViewBar::SaveModified()
{
//TRACE0("CResizableEditViewBar::SaveModified\n");
	CDocument *pDoc = m_pChildView->GetDocument();
	if (pDoc == NULL) return TRUE; // keep going
	if (pDoc->IsKindOf(RUNTIME_CLASS(CDocument))) {
		return pDoc->SaveModified();
	}
	return TRUE;
}