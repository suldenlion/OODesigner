// CProjectOptionsCodeGen.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CProjectOptionsCodeGen.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "CChooseDirDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsCodeGen dialog


CProjectOptionsCodeGen::CProjectOptionsCodeGen(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectOptionsCodeGen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectOptionsCodeGen)
	m_comboHFExtension = theAppPtr->projectHFExtension;
	m_comboSFExtension = theAppPtr->projectSFExtension;
	m_editTargetDirectory = theAppPtr->projectCodegenTargetDir;
	//}}AFX_DATA_INIT
}

void CProjectOptionsCodeGen::languageSelected(CString &language)
{
	m_comboSFExtensionCtrl.ResetContent();
	if (language.CompareNoCase("Java") == 0) {
		m_comboSFExtensionCtrl.AddString(".java");

		m_comboSFExtensionCtrl.SelectString(-1,".java");
		m_comboHFExtensionCtrl.EnableWindow(FALSE);
	} else if (language.CompareNoCase("C#") == 0) {
		m_comboSFExtensionCtrl.AddString(".cs");

		m_comboSFExtensionCtrl.SelectString(-1,".cs");
		m_comboHFExtensionCtrl.EnableWindow(FALSE);
	} else { 
		m_comboSFExtensionCtrl.AddString(".cpp");
		m_comboSFExtensionCtrl.AddString(".c");
		m_comboSFExtensionCtrl.AddString(".cxx");

		m_comboSFExtensionCtrl.SelectString(-1,".cpp");
		m_comboHFExtensionCtrl.EnableWindow(TRUE);
	}
}

void CProjectOptionsCodeGen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectOptionsCodeGen)
	DDX_Control(pDX, IDC_COMBO_HF_EXTENSION, m_comboHFExtensionCtrl);
	DDX_Control(pDX, IDC_COMBO_SF_EXTENSION, m_comboSFExtensionCtrl);
	DDX_Control(pDX, IDC_BUTTON_CHOOSE_DIR, m_buttonChooseDir);
	DDX_CBString(pDX, IDC_COMBO_HF_EXTENSION, m_comboHFExtension);
	DDX_CBString(pDX, IDC_COMBO_SF_EXTENSION, m_comboSFExtension);
	DDX_Text(pDX, IDC_EDIT_TARGET_DIR, m_editTargetDirectory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectOptionsCodeGen, CDialog)
	//{{AFX_MSG_MAP(CProjectOptionsCodeGen)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_DIR, OnButtonChooseDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsCodeGen message handlers

void CProjectOptionsCodeGen::OnButtonChooseDir() 
{
	// TODO: Add your control notification handler code here
	if (m_editTargetDirectory.GetLength() < 3) {
		// 이 문장은 실제 수행될 일이 없을 것이다...
		InfoMsg("Please set this option after setting up the workspace.");
		return;
	}
	CString drive = m_editTargetDirectory.Left(2);
	CString dir = m_editTargetDirectory.Right(m_editTargetDirectory.GetLength()-2);
	CChooseDirDlg aDlg(drive,dir);
	UINT ans = aDlg.DoModal();
	if (ans == IDCANCEL) return;
	m_editTargetDirectory = aDlg.m_dirName;
	UpdateData(FALSE);
}

BOOL CProjectOptionsCodeGen::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (theAppPtr->workspaceName.GetLength() == 0) {
		m_buttonChooseDir.EnableWindow(FALSE);
	} else {
		m_buttonChooseDir.EnableWindow(TRUE);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CProjectOptionsCodeGen::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		CWnd *pParent = GetParent();
		if (pParent != NIL &&
			pParent->IsKindOf(RUNTIME_CLASS(CDialog))) {
			CDialog *aDlg = (CDialog *)pParent;
			aDlg->PostMessage(WM_KEYDOWN,VK_RETURN);
			return -1;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
