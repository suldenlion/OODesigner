// TabDlgWithName.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "TabDlgWithName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int TabDlgWithName::BoundaryGapX = 26;
const int TabDlgWithName::BoundaryGapY = 121;

/////////////////////////////////////////////////////////////////////////////
// TabDlgWithName dialog
IMPLEMENT_DYNAMIC(TabDlgWithName, CDialog)

TabDlgWithName::TabDlgWithName(UINT id,CWnd* pParent /*=NULL*/)
	: CDialog(id, pParent)
{
	_pTabCtrl = NIL;
	//{{AFX_DATA_INIT(TabDlgWithName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void TabDlgWithName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TabDlgWithName)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TabDlgWithName, CDialog)
	//{{AFX_MSG_MAP(TabDlgWithName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_MOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TabDlgWithName message handlers

void TabDlgWithName::ShowSelTabWindow()
{    
	ShowWindow(SW_SHOW);
    int nSel = _pTabCtrl->GetCurSel();   
    ASSERT(nSel != -1);
    
    for (int i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        GetTabWindow(i)->ShowWindow(i == nSel ? SW_SHOW : SW_HIDE);
    }
}

CWnd * TabDlgWithName::GetTabWindow(int nTab)
{
    TC_ITEM TCI;
    TCI.mask = TCIF_PARAM; 
    _pTabCtrl->GetItem(nTab, &TCI);
    CWnd * pWnd = (CWnd *)TCI.lParam;
    ASSERT(pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
    return pWnd;
}

void TabDlgWithName::moveOptionDlgs(int x,int y)    
{
	if (_pTabCtrl == NIL) return;
	RECT rect;
	GetWindowRect(&rect);
    for (int i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        GetTabWindow(i)->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);
    }
}

void TabDlgWithName::updateData()    
{
    for (int i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        GetTabWindow(i)->UpdateData();
    }
}

BOOL TabDlgWithName::ShowWindow(int nCmdShow)
{
    int nSel = _pTabCtrl->GetCurSel();   
    ASSERT(nSel != -1);
    
    for (int i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        GetTabWindow(i)->ShowWindow(i == nSel ? nCmdShow : SW_HIDE);
    }
	return CDialog::ShowWindow(nCmdShow);
}

void TabDlgWithName::AddItem(CTabCtrl &optionsTab,int index,char* name,LPARAM pDialog)
{
	TC_ITEM item;
	item.mask = TCIF_TEXT | TCIF_PARAM;
	item.pszText = name;
	item.lParam = pDialog;
	VERIFY(optionsTab.InsertItem(index, &item) != -1);
}

void TabDlgWithName::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);	
	// TODO: Add your message handler code here

	moveOptionDlgs(x,y);	
}

void TabDlgWithName::resizeTabControlSize(int w,int h)
{
	_pTabCtrl->SetWindowPos(NULL,0,0,w-BoundaryGapX,h-BoundaryGapY,SWP_NOMOVE);
}