// CClassDeleteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CClassDeleteDlg.h"
#include "KtgMacro.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassDeleteDlg dialog


CClassDeleteDlg::CClassDeleteDlg(const char *className,CWnd* pParent /*=NULL*/)
	: CDialog(CClassDeleteDlg::IDD, pParent)
{
	CString name = _T("\"");
	name = name + className + _T("\"");
	//{{AFX_DATA_INIT(CClassDeleteDlg)
	m_staticClassName = name;
	//}}AFX_DATA_INIT
}


void CClassDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassDeleteDlg)
	DDX_Text(pDX, IDC_STATIC_CLASS_NAME, m_staticClassName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClassDeleteDlg, CDialog)
	//{{AFX_MSG_MAP(CClassDeleteDlg)
	ON_BN_CLICKED(IDNO, OnNo)
	ON_BN_CLICKED(IDNOALWAYS, OnNoalways)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDYESALWAYS, OnYesalways)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassDeleteDlg message handlers

void CClassDeleteDlg::OnNo() 
{
	// TODO: Add your control notification handler code here
	
	EndDialog(IDNO);
}

void CClassDeleteDlg::OnNoalways() 
{
	// TODO: Add your control notification handler code here
	
	theAppPtr->classDelNoAlwaysFlag = TRUE;
	EndDialog(IDNOALWAYS);
}

void CClassDeleteDlg::OnYes() 
{
	// TODO: Add your control notification handler code here
	
	EndDialog(IDYES);
}

void CClassDeleteDlg::OnYesalways() 
{
	// TODO: Add your control notification handler code here

	theAppPtr->classDelYesAlwaysFlag = TRUE;
	EndDialog(IDYESALWAYS);
}

BOOL CClassDeleteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	sndPlaySound("C:\\ood\\res\\chord.wav",SND_ASYNC);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
