// CClassFrm.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CClassFrm.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "COODView.h"
#include "COODClassDoc.h"
#include "COODCntrlItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CClassFrm::ModelTBSupressedExplicitely = FALSE;

IMPLEMENT_DYNCREATE(CClassFrm, CChildFrm)
/////////////////////////////////////////////////////////////////////////////
// CClassFrm

CClassFrm::CClassFrm()
: CChildFrm()
{
	_diagramType = _T("Class Diagram");
}

CClassFrm::~CClassFrm()
{
}


BEGIN_MESSAGE_MAP(CClassFrm, CChildFrm)
	//{{AFX_MSG_MAP(CClassFrm)
	ON_COMMAND(ID_VIEW_MODEL_TOOLBAR, OnViewModelToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODEL_TOOLBAR, OnUpdateViewModelToolbar)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CControlBar *CClassFrm::getModelToolBar()
{
	if (ModelTBSupressedExplicitely) return NIL;
	return &(mainFramePtr->classDiagramToolBar);
}

/////////////////////////////////////////////////////////////////////////////
// CClassFrm message handlers

void CClassFrm::OnViewModelToolbar() 
{
	// TODO: Add your command handler code here
	CControlBar *pBar = &(mainFramePtr->classDiagramToolBar);
	if (pBar == NULL) return;
	/* ModelTBSupressedExplicitely는 이 클래스의 static 변수이다.
	다른 프레임들에도 같은 이름의 정적 변수가 있다.
	따라서 이 부분을 CChildFrm으로 옮기면 큰일난다. */
	if (pBar->GetStyle() & WS_VISIBLE) {
		ModelTBSupressedExplicitely = TRUE;
	} else {
		ModelTBSupressedExplicitely = FALSE;
	}
	mainFramePtr->ShowControlBar(pBar,
		(pBar->GetStyle() & WS_VISIBLE) == 0, 
		FALSE);	
}

void CClassFrm::OnUpdateViewModelToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CControlBar *pBar = &(mainFramePtr->classDiagramToolBar);
	if (pBar != NULL) {
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
	pCmdUI->ContinueRouting();
}


void CClassFrm::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDocument *aDoc = GetActiveView()->GetDocument();
	theAppPtr->pCOODClassDoc->removeViewName(this);
	POSITION pos = theAppPtr->pCOODClassDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)theAppPtr->pCOODClassDoc->GetNextClientItem(pos);
		selection->resetController();
	}
	aDoc->PreCloseFrame(this);
	DestroyWindow();
}

