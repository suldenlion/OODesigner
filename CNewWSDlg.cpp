// CNewWSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "CNewWSDlg.h"
#include "CChooseDirDlg.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewWSDlg dialog


CNewWSDlg::CNewWSDlg(CString &wsName,CWnd* pParent /*=NULL*/)
	: CDialog(CNewWSDlg::IDD, pParent)
{
	char dirName[BUFSIZ];
	GetCurrentDirectory(BUFSIZ,dirName);
	_selectedDrive = dirName;
	_selectedDrive = _selectedDrive.Left(2);
	_selectedDir = "\\";
//	_selectedDir = "\\testData\\";
	//{{AFX_DATA_INIT(CNewWSDlg)
	m_language = theAppPtr->projectLanguage;
	workspaceName = wsName;
	//}}AFX_DATA_INIT
}

void CNewWSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewWSDlg)
	DDX_Control(pDX, IDC_EDIT_LOCATION, m_editLocation);
	DDX_CBString(pDX, IDC_COMBO_LANGUAGE, m_language);
	DDX_Text(pDX, IDC_EDIT_NAME, workspaceName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewWSDlg, CDialog)
	//{{AFX_MSG_MAP(CNewWSDlg)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_BN_CLICKED(IDC_DIR_BUTTON, OnDirButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewWSDlg message handlers

BOOL CNewWSDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_editLocation.ReplaceSel(_selectedDrive+_selectedDir+workspaceName);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewWSDlg::OnChangeEditName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_editLocation.SetSel(0,-1);
	m_editLocation.ReplaceSel(_selectedDrive+_selectedDir+workspaceName);
}


void CNewWSDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if (workspaceName.GetLength() == 0) {
		EndDialog(IDCANCEL);
		return; 
	}
	theAppPtr->projectLanguage = m_language;
	theAppPtr->setFileExtension();
	m_editLocation.GetWindowText(wsLocation);
	CDialog::OnOK();
}

void CNewWSDlg::OnDirButton() 
{
	// TODO: Add your control notification handler code here
	CChooseDirDlg aDlg(_selectedDrive,_selectedDir);
	UINT ans = aDlg.DoModal();
	if (ans == IDCANCEL) return;
	CString chooseName = aDlg.m_dirName;
	_selectedDrive = chooseName.Left(2);
	_selectedDir = chooseName.Right(chooseName.GetLength()-2);
	m_editLocation.SetSel(0,-1);
	m_editLocation.ReplaceSel(_selectedDrive+_selectedDir+workspaceName);
}
