// CDeploymentFrm.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CDeploymentFrm.h"
#include "KtgMacro.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CDeploymentFrm::ModelTBSupressedExplicitely = FALSE;

IMPLEMENT_DYNCREATE(CDeploymentFrm, CChildFrm)
/////////////////////////////////////////////////////////////////////////////
// CDeploymentFrm

CDeploymentFrm::CDeploymentFrm()
: CChildFrm()
{
	_diagramType = _T("Deployment Diagram");
}

CDeploymentFrm::~CDeploymentFrm()
{
}


BEGIN_MESSAGE_MAP(CDeploymentFrm, CChildFrm)
	//{{AFX_MSG_MAP(CDeploymentFrm)
	ON_COMMAND(ID_VIEW_MODEL_TOOLBAR, OnViewModelToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODEL_TOOLBAR, OnUpdateViewModelToolbar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CControlBar *CDeploymentFrm::getModelToolBar()
{
	if (ModelTBSupressedExplicitely) return NIL;
	return &(mainFramePtr->deploymentDiagramToolBar);
}

/////////////////////////////////////////////////////////////////////////////
// CDeploymentFrm message handlers


void CDeploymentFrm::OnViewModelToolbar() 
{
	// TODO: Add your command handler code here
	
	CControlBar *pBar = &(mainFramePtr->deploymentDiagramToolBar);
	if (pBar == NULL) return;
	/* ModelTBSupressedExplicitely�� �� Ŭ������ static �����̴�.
	�ٸ� �����ӵ鿡�� ���� �̸��� ���� ������ �ִ�.
	���� �� �κ��� CChildFrm���� �ű�� ū�ϳ���. */
	if (pBar->GetStyle() & WS_VISIBLE) {
		ModelTBSupressedExplicitely = TRUE;
	} else {
		ModelTBSupressedExplicitely = FALSE;
	}
	mainFramePtr->ShowControlBar(pBar,
		(pBar->GetStyle() & WS_VISIBLE) == 0, 
		FALSE);		
}

void CDeploymentFrm::OnUpdateViewModelToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	CControlBar *pBar = &(mainFramePtr->deploymentDiagramToolBar);
	if (pBar != NULL) {
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
	pCmdUI->ContinueRouting();
}
