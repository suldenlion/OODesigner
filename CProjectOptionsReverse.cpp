// CProjectOptionsReverse.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CProjectOptionsReverse.h"
#include "KtgMacro.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsReverse dialog


CProjectOptionsReverse::CProjectOptionsReverse(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectOptionsReverse::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectOptionsReverse)
	m_comboTreeOrient = theAppPtr->projectInheritanceTreeOrient;
	m_editSourceDir = theAppPtr->projectReverseSourceDir;
	//}}AFX_DATA_INIT
}


void CProjectOptionsReverse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectOptionsReverse)
	DDX_Control(pDX, IDC_RADIO_YES, m_radioNo);
	DDX_Control(pDX, IDC_RADIO_NO, m_radioYes);
	DDX_CBString(pDX, IDC_COMBO_TREE_ORIENT, m_comboTreeOrient);
	DDX_Text(pDX, IDC_EDIT_SOURCE_DIR, m_editSourceDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectOptionsReverse, CDialog)
	//{{AFX_MSG_MAP(CProjectOptionsReverse)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_DIR, OnButtonChooseDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsReverse message handlers

void CProjectOptionsReverse::OnButtonChooseDir() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CProjectOptionsReverse::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	if (theAppPtr->projectDrawInheritanceTreeFlag == TRUE) {
		m_radioYes.SetCheck(1);
	} else {
		m_radioNo.SetCheck(1);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CProjectOptionsReverse::PreTranslateMessage(MSG* pMsg) 
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
