// CTextView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CTextView.h"
#include "KtgMacro.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CEditView)

CTextView::CTextView()
{
}

CTextView::~CTextView()
{
}


BEGIN_MESSAGE_MAP(CTextView, CEditView)
	//{{AFX_MSG_MAP(CTextView)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_CHAR()
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextView drawing

void CTextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTextView diagnostics

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTextView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers

int CTextView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	SetTabStops(8);
	return 0;
}

void CTextView::showCursorPos()
{
	CEdit& ctrl = GetEditCtrl();
	int line = ctrl.LineFromChar();
	int chars = ctrl.LineIndex(); 
	int nStartChar = 0;
	int nEndChar = 0;
	ctrl.GetSel(nStartChar,nEndChar);
	int col = nStartChar - chars;
	mainFramePtr->setPositionOnStatusBar(line+1,col+1);
}

void CTextView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
	showCursorPos();
}

void CTextView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEditView::OnLButtonDown(nFlags, point);
	showCursorPos();
}

void CTextView::OnSetFocus(CWnd* pOldWnd) 
{
	CEditView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	showCursorPos();	
}

void CTextView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEditView::OnChar(nChar, nRepCnt, nFlags);
	showCursorPos();	
}

void CTextView::OnEditDelete() 
{
	// TODO: Add your command handler code here
	ASSERT_VALID(this);
	GetEditCtrl().Cut();
	ASSERT_VALID(this);	
}

void CTextView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CEditView::OnUpdateNeedSel(pCmdUI);
}

void CTextView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (CWnd::GetFocus() != this) {
		pCmdUI->Enable(FALSE);
		return;
	}
	CEditView::OnUpdateNeedText(pCmdUI);	
}

void CTextView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (CWnd::GetFocus() != this) {
		pCmdUI->Enable(FALSE);
		return;
	}
	CEditView::OnUpdateNeedClip(pCmdUI);
}
