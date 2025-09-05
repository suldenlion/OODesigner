// CSequenceFrm.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CSequenceFrm.h"
#include "KtgMacro.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CSequenceFrm::ModelTBSupressedExplicitely = FALSE;

IMPLEMENT_DYNCREATE(CSequenceFrm, CChildFrm)
/////////////////////////////////////////////////////////////////////////////
// CSequenceFrm

CSequenceFrm::CSequenceFrm()
: CChildFrm()
{
	_diagramType = _T("Sequence Diagram");
}

CSequenceFrm::~CSequenceFrm()
{
}


BEGIN_MESSAGE_MAP(CSequenceFrm, CChildFrm)
	//{{AFX_MSG_MAP(CSequenceFrm)
	ON_COMMAND(ID_VIEW_MODEL_TOOLBAR, OnViewModelToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODEL_TOOLBAR, OnUpdateViewModelToolbar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CControlBar *CSequenceFrm::getModelToolBar()
{
	if (ModelTBSupressedExplicitely) return NIL;
	return &(mainFramePtr->sequenceDiagramToolBar);
}

/////////////////////////////////////////////////////////////////////////////
// CSequenceFrm message handlers

void CSequenceFrm::OnViewModelToolbar() 
{
	// TODO: Add your command handler code here
	
	CControlBar *pBar = &(mainFramePtr->sequenceDiagramToolBar);
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

void CSequenceFrm::OnUpdateViewModelToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	CControlBar *pBar = &(mainFramePtr->sequenceDiagramToolBar);
	if (pBar != NULL) {
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
	pCmdUI->ContinueRouting();
}
