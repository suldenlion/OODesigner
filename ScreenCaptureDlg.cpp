// ScreenCaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "ScreenCaptureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ScreenCaptureDlg dialog


ScreenCaptureDlg::ScreenCaptureDlg(CString &fName,BOOL captureView,CWnd* pParent /*=NULL*/)
	: CDialog(ScreenCaptureDlg::IDD, pParent)
{
	_viewFlag = captureView;
	//{{AFX_DATA_INIT(ScreenCaptureDlg)
	m_editBMPFileName = fName;
	//}}AFX_DATA_INIT
}


void ScreenCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ScreenCaptureDlg)
	DDX_Text(pDX, IDC_EDIT_BMP_FILE_NAME, m_editBMPFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ScreenCaptureDlg, CDialog)
	//{{AFX_MSG_MAP(ScreenCaptureDlg)
	ON_BN_CLICKED(IDC_RADIO_USER_RECT, OnRadioUserRect)
	ON_BN_CLICKED(IDC_RADIO_VIEW, OnRadioView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ScreenCaptureDlg message handlers

void ScreenCaptureDlg::OnRadioUserRect() 
{
	// TODO: Add your control notification handler code here
	_viewFlag = FALSE;
}

void ScreenCaptureDlg::OnRadioView() 
{
	// TODO: Add your control notification handler code here
	_viewFlag = TRUE;	
}

BOOL ScreenCaptureDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd *pWnd = NULL;
	if (_viewFlag) {
		pWnd = GetDlgItem(IDC_RADIO_VIEW);
	} else {
		pWnd = GetDlgItem(IDC_RADIO_USER_RECT);
	}
	if (pWnd != NULL &&
		!pWnd->IsKindOf(RUNTIME_CLASS(CButton))) {
		CButton *button = (CButton *)pWnd;
		button->SetCheck(1);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
