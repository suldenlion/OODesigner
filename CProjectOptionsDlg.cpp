// CProjectOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CProjectOptionsDlg.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "CProjectOptionsGeneral.h"
#include "CProjectOptionsCodeGen.h"
#include "CProjectOptionsReverse.h"
#include "CProjectOptionsMacros.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PAGE_DISPX	(35)
#define PAGE_DISPY	(65)

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsDlg dialog


CProjectOptionsDlg::CProjectOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectOptionsDlg::IDD, pParent)
{
	_generalOption = NIL;
	_codegenOption = NIL;
	_reverseOption = NIL;
	_macrosOption = NIL;
	//{{AFX_DATA_INIT(CProjectOptionsDlg)
	//}}AFX_DATA_INIT
}

CProjectOptionsDlg::~CProjectOptionsDlg()
{
	/*
	CWnd *ptr[100];
	int n = m_optionsTab.GetItemCount();
	int i;
    for (i = 0; i < n; i++)
    {
        CWnd *aWnd = GetTabWindow(i);
		ptr[i] = aWnd;
    }
    for (i = 0; i < n; i++)
    {
		CWnd *aWnd = ptr[i];
		if (aWnd != NULL) delete aWnd;
	}
	*/
}

void CProjectOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectOptionsDlg)
	DDX_Control(pDX, IDC_TAB_PROJECT_OPTIONS, m_optionsTab);
	//}}AFX_DATA_MAP
}

CWnd * CProjectOptionsDlg::GetTabWindow(int nTab)
{
    TC_ITEM TCI;
    TCI.mask = TCIF_PARAM; 
    m_optionsTab.GetItem(nTab, &TCI);
    CWnd * pWnd = (CWnd *)TCI.lParam;
    ASSERT(pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
    return pWnd;
}

void CProjectOptionsDlg::ShowSelTabWindow()
{    
    int nSel = m_optionsTab.GetCurSel();   
    ASSERT(nSel != -1);
    
    for (int i = 0; i < m_optionsTab.GetItemCount(); i++)
    {
        GetTabWindow(i)->ShowWindow(i == nSel ? SW_SHOW : SW_HIDE);
    }
}

BEGIN_MESSAGE_MAP(CProjectOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CProjectOptionsDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PROJECT_OPTIONS, OnSelchangeTabProjectOptions)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsDlg message handlers

BOOL CProjectOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
 
	// populate the tab control ....
    static LPCTSTR szTabName[] = { _T(" General "), 
								   _T(" Code Gen... "), 
								   _T(" Reverse Eng... "),
								   _T(" Macros ") };

    RECT rect;
	GetWindowRect(&rect);
	_generalOption = new CProjectOptionsGeneral(this);
	_generalOption->Create(IDD_PROJECT_OPTIONS_GENERAL,this);
	_generalOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_codegenOption = new CProjectOptionsCodeGen(this);
	_codegenOption->Create(IDD_PROJECT_OPTIONS_CODEGEN,this);
	_codegenOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_reverseOption = new CProjectOptionsReverse(this);
	_reverseOption->Create(IDD_PROJECT_OPTIONS_REVERSE,this);
	_reverseOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_macrosOption = new CProjectOptionsMacros(this);
	_macrosOption->Create(IDD_PROJECT_OPTIONS_MACROS,this);
	_macrosOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_generalOption->setProjectOptionsCodeGen(_codegenOption);
	_generalOption->setProjectOptionsMacros(_macrosOption);
	_codegenOption->languageSelected(theAppPtr->projectLanguage);
	_macrosOption->languageSelected(theAppPtr->projectLanguage);

	TC_ITEM TCI_GENERAL;
	TCI_GENERAL.mask = TCIF_TEXT | TCIF_PARAM;
	TCI_GENERAL.pszText = (char *)szTabName[0];
	TCI_GENERAL.lParam = (LPARAM)_generalOption;
	VERIFY(m_optionsTab.InsertItem(0, &TCI_GENERAL) != -1);

	TC_ITEM TCI_CODEGEN;
	TCI_CODEGEN.mask = TCIF_TEXT | TCIF_PARAM;
	TCI_CODEGEN.pszText = (char *)szTabName[1];
	TCI_CODEGEN.lParam = (LPARAM)_codegenOption;
	VERIFY(m_optionsTab.InsertItem(1, &TCI_CODEGEN) != -1);

	TC_ITEM TCI_REVERSE;
	TCI_REVERSE.mask = TCIF_TEXT | TCIF_PARAM;
	TCI_REVERSE.pszText = (char *)szTabName[2];
	TCI_REVERSE.lParam = (LPARAM)_reverseOption;
	VERIFY(m_optionsTab.InsertItem(2, &TCI_REVERSE) != -1);

	TC_ITEM TCI_MACROS;
	TCI_MACROS.mask = TCIF_TEXT | TCIF_PARAM;
	TCI_MACROS.pszText = (char *)szTabName[3];
	TCI_MACROS.lParam = (LPARAM)_macrosOption;
	VERIFY(m_optionsTab.InsertItem(3, &TCI_MACROS) != -1);

	ShowSelTabWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProjectOptionsDlg::OnSelchangeTabProjectOptions(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
    ShowSelTabWindow();
    *pResult = TRUE;
}

void CProjectOptionsDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
    RECT rect;
	GetWindowRect(&rect);
	if (_generalOption != NIL) {
		_generalOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);
	}
	if (_codegenOption != NIL) {
		_codegenOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);
	}	
	if (_reverseOption != NIL) {
		_reverseOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);
	}	
	if (_macrosOption != NIL) {
		_macrosOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);
	}	
}

void CProjectOptionsDlg::OnOK() 
{
	// TODO: Add extra validation here
	_generalOption->UpdateData();
	_codegenOption->UpdateData();
	_reverseOption->UpdateData();
	_macrosOption->writeMacros();

	theAppPtr->projectLanguage = _generalOption->m_comboLanguage;
	theAppPtr->projectAuthor = _generalOption->m_editAuthor;
	theAppPtr->projectOrganization = _generalOption->m_editOrganization;
	
	theAppPtr->projectHFExtension = _codegenOption->m_comboHFExtension;
	theAppPtr->projectSFExtension = _codegenOption->m_comboSFExtension;
	theAppPtr->projectCodegenTargetDir = _codegenOption->m_editTargetDirectory;

	CDialog::OnOK();
}


