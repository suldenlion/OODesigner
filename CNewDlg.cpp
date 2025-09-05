// CNewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CNewDlg.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "Text.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewDlg dialog


CNewDlg::CNewDlg(CString dgmType,const char *defaultExtension,CWnd* pParent /*=NULL*/)
	: CDialog(CNewDlg::IDD, pParent)
{
	_dgmType = dgmType;
	_index = 1;
	//{{AFX_DATA_INIT(CNewDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_name = _T(defaultExtension);
	//}}AFX_DATA_INIT
}


void CNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_FILE_TYPE_LIST, m_fileTypes);
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewDlg, CDialog)
	//{{AFX_MSG_MAP(CNewDlg)
	ON_LBN_SELCHANGE(IDC_FILE_TYPE_LIST, OnSelchangeFileTypeList)
	ON_LBN_DBLCLK(IDC_FILE_TYPE_LIST, OnDblclkFileTypeList)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewDlg message handlers

BOOL CNewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// 매크로 정의와 순서가 꺼꾸로 임 ...
	m_fileTypes.InsertString(0,"Project Workspace");

	if (theAppPtr->workspaceName.GetLength() > 0) {
		m_fileTypes.InsertString(1,"Text File");
		m_fileTypes.InsertString(2,"Class Diagram");
		m_fileTypes.InsertString(3,"Use Case Diagram");
		m_fileTypes.InsertString(4,"Sequence Diagram");
		m_fileTypes.InsertString(5,"Collaboration Diagram");
		m_fileTypes.InsertString(6,"State Diagram");
		m_fileTypes.InsertString(7,"Activity Diagram");
		m_fileTypes.InsertString(8,"Deployment Diagram");
	}
	
	if (_dgmType.CompareNoCase("Text File") == 0) {
		m_fileTypes.SetCurSel(1);
	} else if (_dgmType.CompareNoCase("Class Diagram") == 0) {
		m_fileTypes.SetCurSel(2);
	} else if (_dgmType.CompareNoCase("Use Case Diagram") == 0) {
		m_fileTypes.SetCurSel(3);
	} else if (_dgmType.CompareNoCase("Sequence Diagram") == 0) {
		m_fileTypes.SetCurSel(4);
	} else if (_dgmType.CompareNoCase("Collaboration Diagram") == 0) {
		m_fileTypes.SetCurSel(5);
	} else if (_dgmType.CompareNoCase("State Diagram") == 0) {
		m_fileTypes.SetCurSel(6);
	} else if (_dgmType.CompareNoCase("Activity Diagram") == 0) {
		m_fileTypes.SetCurSel(7);
	} else if (_dgmType.CompareNoCase("Deployment Diagram") == 0) {
		m_fileTypes.SetCurSel(8);
	} else {
		m_fileTypes.SetCurSel(0);
	}
	
	if (theAppPtr->workspaceName.GetLength() == 0) {
		m_fileTypes.SetCurSel(0);
	}

	OnSelchangeFileTypeList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewDlg::OnSelchangeFileTypeList() 
{
	// TODO: Add your control notification handler code here
	_index = m_fileTypes.GetCurSel();
	_index++;
}

void CNewDlg::OnDblclkFileTypeList() 
{
	// TODO: Add your control notification handler code here
	_index = m_fileTypes.GetCurSel();
	_index++;
	OnOK();
}

void CNewDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	char buffer[BUFSIZ];
	int n = Text::strcpyCompact(buffer,m_name,BUFSIZ);
	if (n == 0 && _index > 1) {
		InfoMsg("You must provide a file name.");
		return;
	}
	m_name = buffer;
	EndDialog(IDOK);
}

void CNewDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	CWnd *pWnd = GetDlgItem(IDC_NAME);
	pWnd->SetFocus();

}
