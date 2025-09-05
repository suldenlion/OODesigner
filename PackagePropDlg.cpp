// PackagePropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "PackagePropDlg.h"
#include "PackagePropGeneral.h"
#include "PackageCommentDlg.h"
#include "FigureLibrary.h"
#include "ClassFigureLibrary.h"
#include "COODClassDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PackagePropDlg dialog
IMPLEMENT_DYNAMIC(PackagePropDlg, TabDlgWithName)

PackagePropDlg::PackagePropDlg(CWnd* pParent /*=NULL*/)
	: TabDlgWithName(PackagePropDlg::IDD, pParent)
{
	_packageName = _T("");
	_packageInfo = NIL;

	_generalOption = NIL;
	_commentOption = NIL;
	//{{AFX_DATA_INIT(PackagePropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

PackagePropDlg::~PackagePropDlg()
{
	if (_generalOption != NIL) {
		delete _generalOption; _generalOption = NIL;
	}
	if (_commentOption != NIL) {
		delete _commentOption; _commentOption = NIL;
	}
}

void PackagePropDlg::loadPackageInfo(CString &dgmName)
{
	_packageName = dgmName;
	ClassFigureLibrary *theLibrary = theAppPtr->pCOODClassDoc->getClassFiguresLibrary();
	_packageInfo = theLibrary->getPackage(_packageName);
	if (_packageInfo == NIL) {
		ErrorMsg("Can't load package properties.");
		OnCancel();
		return;
	}
	_packageName = dgmName.Left(dgmName.GetLength()-_EXT_LEN5);
	m_staticPackageNameCtrl.SetWindowText(_packageName);
	_commentOption->loadComment(_packageInfo->comment());
}

void PackagePropDlg::DoDataExchange(CDataExchange* pDX)
{
	TabDlgWithName::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PackagePropDlg)
	DDX_Control(pDX, IDC_STATIC_PACKAGE_NAME, m_staticPackageNameCtrl);
	DDX_Control(pDX, IDC_TAB_PACKAGE_PROP, m_optionsTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PackagePropDlg, TabDlgWithName)
	//{{AFX_MSG_MAP(PackagePropDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PACKAGE_PROP, OnSelchangeTabPackageProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PackagePropDlg message handlers

BOOL PackagePropDlg::OnInitDialog() 
{
	TabDlgWithName::OnInitDialog();
	
	// TODO: Add extra initialization here
	
    RECT rect;
	GetWindowRect(&rect);

	_generalOption = new PackagePropGeneral(this);
	_generalOption->Create(IDD_PACKAGE_PROP_GENERAL,this);
	_generalOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_commentOption = new PackageCommentDlg(this);
	_commentOption->Create(IDD_PACKAGE_COMMENT_DLG,this);
	_commentOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	AddItem(m_optionsTab,0," General ",(LPARAM)_generalOption);
	AddItem(m_optionsTab,1," Documentation ",(LPARAM)_commentOption);

	_pTabCtrl = &m_optionsTab;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PackagePropDlg::OnSelchangeTabPackageProp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	ShowSelTabWindow();
	*pResult = 0;
}

void PackagePropDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	_commentOption->clearContents();
	ShowWindow(SW_HIDE);
}

void PackagePropDlg::OnOK() 
{
	// TODO: Add extra validation here
	_commentOption->writeComment();
	_commentOption->clearContents();
	ShowWindow(SW_HIDE);
}
