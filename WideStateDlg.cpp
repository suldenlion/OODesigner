// WideStateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "WideStateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WideStateDlg dialog


WideStateDlg::WideStateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(WideStateDlg::IDD, pParent)
{
	_nOfPlanes = 1;
	//{{AFX_DATA_INIT(WideStateDlg)
	//}}AFX_DATA_INIT
}


void WideStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WideStateDlg)
	DDX_Control(pDX, IDC_EDIT_NUMBER, m_editNumberCtrl);
	DDX_Control(pDX, IDC_COMBO_NUMBER, m_comboNumberCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WideStateDlg, CDialog)
	//{{AFX_MSG_MAP(WideStateDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_NUMBER, OnSelchangeComboNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WideStateDlg message handlers

BOOL WideStateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_comboNumberCtrl.SetCurSel(0);
	m_editNumberCtrl.SetWindowText("1");
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void WideStateDlg::OnSelchangeComboNumber() 
{
	// TODO: Add your control notification handler code here
	CString val;
	m_comboNumberCtrl.GetWindowText(val);
	m_editNumberCtrl.SetWindowText(val);
}

void WideStateDlg::OnOK() 
{
	// TODO: Add extra validation here
		
	CString val;
	m_editNumberCtrl.GetWindowText(val);
	_nOfPlanes = atoi(val);

	if (_nOfPlanes <= 0) {
		WarningMsg("Invalid number of planes.");
		_nOfPlanes = 1;
	} else if (_nOfPlanes > 100) {
		WarningMsg("Too many planes.");
		_nOfPlanes = 100;
	}
	CDialog::OnOK();
}

