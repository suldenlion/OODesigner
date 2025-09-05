// TipDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "TipDialog.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// TipDialog dialog


TipDialog::TipDialog(CWnd* pParent /*=NULL*/)
	: CDialog(TipDialog::IDD, pParent)
{
	m_checkStartUp = theAppPtr->showTipsFlag;
	//{{AFX_DATA_INIT(TipDialog)
	//}}AFX_DATA_INIT
}


void TipDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TipDialog)
	DDX_Check(pDX, IDC_CHECK_START_UP, m_checkStartUp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TipDialog, CDialog)
	//{{AFX_MSG_MAP(TipDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TipDialog message handlers

void TipDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	theAppPtr->showTipsFlag = m_checkStartUp;
	CDialog::OnCancel();
}

BOOL TipDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int TipDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	RECT box;
	GetClientRect(&box);

	if (!_whiteBoard.Create(NULL,"TipBoard",WS_CHILD|WS_VISIBLE|WS_BORDER,
		CRect(15,15,box.right-15,box.bottom-60),this,ID_TIP_BOARD)) {
		TRACE0("Failed to create TipBoard\n");
		return -1;
	}
	_whiteBoard.loadBitmap(IDB_TIP);
	_whiteBoard.setIndex();
	
	return 0;
}

void TipDialog::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	
	_whiteBoard.setNextIndex();
	_whiteBoard.Invalidate();
}
