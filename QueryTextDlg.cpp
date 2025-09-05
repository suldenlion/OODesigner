// QueryTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "QueryTextDlg.h"
#include "Text.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// QueryTextDlg dialog


QueryTextDlg::QueryTextDlg(int purpose,const char* question,CWnd* pParent /*=NULL*/)
	: CDialog(QueryTextDlg::IDD, pParent)
{
	_forWhich = purpose;
	m_staticQuestion = question;
	//{{AFX_DATA_INIT(QueryTextDlg)
	m_editAnswer = _T("");
	//}}AFX_DATA_INIT
}


void QueryTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(QueryTextDlg)
	DDX_Control(pDX, IDC_BUTTON_PROPERTIES, m_buttonPropertiesCtrl);
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_editAnswer);
	DDX_Text(pDX, IDC_STATIC_QUESTION, m_staticQuestion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(QueryTextDlg, CDialog)
	//{{AFX_MSG_MAP(QueryTextDlg)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTIES, OnButtonProperties)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// QueryTextDlg message handlers

void QueryTextDlg::OnOK() 
{
	// TODO: Add extra validation here
	saveAnswer();
	EndDialog(IDOK);
}

void QueryTextDlg::OnButtonProperties() 
{
	// TODO: Add your control notification handler code here
	
	saveAnswer();
	EndDialog(IDMORE);
}

void QueryTextDlg::saveAnswer()
{
	UpdateData(TRUE);
	m_editAnswer.TrimLeft();
	char buffer[BUFSIZ];
	buffer[0] = '\0';
	int n = Text::strcpyCompact(buffer,m_editAnswer,BUFSIZ);
	m_editAnswer = buffer;
}

BOOL QueryTextDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/*
	if (_forWhich == FOR_PACKAGE) {
		m_buttonPropertiesCtrl.EnableWindow(FALSE);
	} else {
		m_buttonPropertiesCtrl.EnableWindow(TRUE);
	}
	*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void QueryTextDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	CWnd *pWnd = (CEdit*)GetDlgItem(IDC_EDIT_ANSWER);
	pWnd->SetFocus(); 
}
