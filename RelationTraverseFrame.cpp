// RelationTraverseFrame.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "RelationTraverseFrame.h"
#include "ClassMemberListView.h"
#include "ClassTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RelationTraverseFrame

IMPLEMENT_DYNCREATE(RelationTraverseFrame, CFrameWnd)

RelationTraverseFrame::RelationTraverseFrame()
{
}

RelationTraverseFrame::~RelationTraverseFrame()
{
}


BEGIN_MESSAGE_MAP(RelationTraverseFrame, CFrameWnd)
	//{{AFX_MSG_MAP(RelationTraverseFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RelationTraverseFrame message handlers
ClassTreeView *RelationTraverseFrame::getTreeView()
{
	CWnd *pView = m_wndSplitter.GetPane(0,0);
	if (pView == NIL) return NIL;
	if (!pView->IsKindOf(RUNTIME_CLASS(ClassTreeView))) return NIL;
	return (ClassTreeView *)pView;
}

ClassMemberListView *RelationTraverseFrame::getListView(int i)
{
	CWnd *pView = m_wndListSplitter.GetPane(i,0);
	if (pView == NIL) return NIL;
	if (!pView->IsKindOf(RUNTIME_CLASS(ClassMemberListView))) return NIL;
	return (ClassMemberListView *)pView;
}

BOOL RelationTraverseFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	RECT dlgBox;
	GetParent()->GetClientRect(&dlgBox);
	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(ClassTreeView),CSize(dlgBox.right/2,dlgBox.bottom),pContext);

	m_wndListSplitter.CreateStatic(&m_wndSplitter,2,1,
		WS_CHILD|WS_VISIBLE|WS_BORDER,m_wndSplitter.IdFromRowCol(0,1));
	m_wndListSplitter.CreateView(0,0,RUNTIME_CLASS(ClassMemberListView),CSize(dlgBox.right/2,(dlgBox.bottom-50)/2),pContext);
	m_wndListSplitter.CreateView(1,0,RUNTIME_CLASS(ClassMemberListView),CSize(dlgBox.right/2,(dlgBox.bottom-50)/2),pContext);

	return TRUE;
}

