// CCollaborationFrm.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CCollaborationFrm.h"
#include "KtgMacro.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CCollaborationFrm::ModelTBSupressedExplicitely = FALSE;

IMPLEMENT_DYNCREATE(CCollaborationFrm, CChildFrm)
/////////////////////////////////////////////////////////////////////////////
// CCollaborationFrm

CCollaborationFrm::CCollaborationFrm()
: CChildFrm()
{
	_diagramType = _T("Collaboration Diagram");
}

CCollaborationFrm::~CCollaborationFrm()
{
}


BEGIN_MESSAGE_MAP(CCollaborationFrm, CChildFrm)
	//{{AFX_MSG_MAP(CCollaborationFrm)
	ON_COMMAND(ID_VIEW_MODEL_TOOLBAR, OnViewModelToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODEL_TOOLBAR, OnUpdateViewModelToolbar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CControlBar *CCollaborationFrm::getModelToolBar()
{
	if (ModelTBSupressedExplicitely) return NIL;
	return &(mainFramePtr->collaborationDiagramToolBar);
}

/////////////////////////////////////////////////////////////////////////////
// CCollaborationFrm message handlers

void CCollaborationFrm::OnViewModelToolbar() 
{
	// TODO: Add your command handler code here
	CControlBar *pBar = &(mainFramePtr->collaborationDiagramToolBar);
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

void CCollaborationFrm::OnUpdateViewModelToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CControlBar *pBar = &(mainFramePtr->collaborationDiagramToolBar);
	if (pBar != NULL) {
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
	pCmdUI->ContinueRouting();
}
