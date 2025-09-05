// CClassMigrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CClassMigrationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassMigrationDlg dialog


CClassMigrationDlg::CClassMigrationDlg(CString& currentPack,CStringList& packNames,CWnd* pParent /*=NULL*/)
	: _packageNames(packNames), CDialog(CClassMigrationDlg::IDD, pParent)
{
	_packageName = currentPack;
	//{{AFX_DATA_INIT(CClassMigrationDlg)
	m_DestinationString = _T("");
	//}}AFX_DATA_INIT
}


void CClassMigrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassMigrationDlg)
	DDX_Control(pDX, IDC_COMBO_DESTINATION, m_comboDestinationCtrl);
	DDX_CBString(pDX, IDC_COMBO_DESTINATION, m_DestinationString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClassMigrationDlg, CDialog)
	//{{AFX_MSG_MAP(CClassMigrationDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassMigrationDlg message handlers

BOOL CClassMigrationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	POSITION pos = _packageNames.GetHeadPosition();
	int i = 0;
	while (pos != NULL) {
		CString aName = _packageNames.GetNext(pos);
		m_comboDestinationCtrl.AddString(aName);
		if (aName.CompareNoCase(_packageName) == 0) {
			m_comboDestinationCtrl.SetCurSel(i);
		}
		i++;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
