// CProjectOptionsGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CProjectOptionsGeneral.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "CProjectOptionsCodeGen.h"
#include "CProjectOptionsMacros.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsGeneral dialog


CProjectOptionsGeneral::CProjectOptionsGeneral(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectOptionsGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectOptionsGeneral)
	m_comboLanguage = theAppPtr->projectLanguage;
	m_editAuthor = theAppPtr->projectAuthor;
	m_editOrganization = theAppPtr->projectOrganization;
	//}}AFX_DATA_INIT
}


void CProjectOptionsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectOptionsGeneral)
	DDX_CBString(pDX, IDC_COMBO_LANGUAGE, m_comboLanguage);
	DDX_Text(pDX, IDC_EDIT_AUTHOR, m_editAuthor);
	DDX_Text(pDX, IDC_EDIT_ORGANIZATION, m_editOrganization);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectOptionsGeneral, CDialog)
	//{{AFX_MSG_MAP(CProjectOptionsGeneral)
	ON_CBN_SELCHANGE(IDC_COMBO_LANGUAGE, OnSelchangeComboLanguage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsGeneral message handlers

BOOL CProjectOptionsGeneral::PreTranslateMessage(MSG* pMsg) 
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

void CProjectOptionsGeneral::OnSelchangeComboLanguage() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	_codegenOption->languageSelected(m_comboLanguage);
	_macrosOption->languageSelected(m_comboLanguage);
}
