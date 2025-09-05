// CSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog


CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{
	_dgmType = _T("Class Diagram");
	_index = 2;
	//{{AFX_DATA_INIT(CSelectDlg)
	m_name = _T("");
	//}}AFX_DATA_INIT
}


void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDlg)
	DDX_Control(pDX, IDC_FILE_TYPE_LIST, m_fileTypes);
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectDlg)
	ON_LBN_DBLCLK(IDC_FILE_TYPE_LIST, OnDblclkFileTypeList)
	ON_WM_PAINT()
	ON_LBN_SELCHANGE(IDC_FILE_TYPE_LIST, OnSelchangeFileTypeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg message handlers

void CSelectDlg::OnDblclkFileTypeList() 
{
	// TODO: Add your control notification handler code here
	
	_index = m_fileTypes.GetCurSel();
	_index = _index + 3;
	OnOK();
}

BOOL CSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	// 매크로 정의와 순서가 꺼꾸로 임 ...
	m_fileTypes.InsertString(0,"Class Diagram");
	m_fileTypes.InsertString(1,"Use Case Diagram");
	m_fileTypes.InsertString(2,"Sequence Diagram");
	m_fileTypes.InsertString(3,"Collaboration Diagram");
	m_fileTypes.InsertString(4,"State Diagram");
	m_fileTypes.InsertString(5,"Activity Diagram");
	m_fileTypes.InsertString(6,"Deployment Diagram");
	
	m_fileTypes.SetCurSel(0);
	
	OnSelchangeFileTypeList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	UpdateData(TRUE);
	/*
	char buffer[BUFSIZ];
	int n = Text::strcpyCompact(buffer,m_name,BUFSIZ);
	if (n == 0 && _index > 1) {
		InfoMsg("You must provide a file name.");
		return;
	}
	m_name = buffer;
	*/
	EndDialog(IDOK);
}

void CSelectDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	CWnd *pWnd = GetDlgItem(IDC_NAME);
	pWnd->SetFocus();

}

void CSelectDlg::OnSelchangeFileTypeList() 
{
	// TODO: Add your control notification handler code here
	
	_index = m_fileTypes.GetCurSel();
	_index = _index + 3;
}
