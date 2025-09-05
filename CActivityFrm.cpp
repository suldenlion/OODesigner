// CActivityFrm.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CActivityFrm.h"
#include "KtgMacro.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CActivityFrm::ModelTBSupressedExplicitely = FALSE;

IMPLEMENT_DYNCREATE(CActivityFrm, CChildFrm)

/////////////////////////////////////////////////////////////////////////////
// CActivityFrm

CActivityFrm::CActivityFrm()
: CChildFrm()
{
	_diagramType = _T("Activity Diagram");
}

CActivityFrm::~CActivityFrm()
{
}


BEGIN_MESSAGE_MAP(CActivityFrm, CChildFrm)
	//{{AFX_MSG_MAP(CActivityFrm)
	ON_COMMAND(ID_VIEW_MODEL_TOOLBAR, OnViewModelToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODEL_TOOLBAR, OnUpdateViewModelToolbar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CControlBar *CActivityFrm::getModelToolBar()
{
	if (ModelTBSupressedExplicitely) return NIL;
	return &(mainFramePtr->activityDiagramToolBar);
}

/////////////////////////////////////////////////////////////////////////////
// CActivityFrm message handlers

void CActivityFrm::OnViewModelToolbar() 
{
	// TODO: Add your command handler code here
	CControlBar *pBar = &(mainFramePtr->activityDiagramToolBar);
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

void CActivityFrm::OnUpdateViewModelToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	CControlBar *pBar = &(mainFramePtr->activityDiagramToolBar);
	if (pBar != NULL) {
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
	pCmdUI->ContinueRouting();
}
