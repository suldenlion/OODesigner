// BaseClassInitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "BaseClassInitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BaseClassInitDlg dialog


BaseClassInitDlg::BaseClassInitDlg(CStringList *initValue,CWnd* pParent /*=NULL*/)
	: CDialog(BaseClassInitDlg::IDD, pParent)
{
	_initValue = initValue;
	//{{AFX_DATA_INIT(BaseClassInitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void BaseClassInitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BaseClassInitDlg)
	DDX_Control(pDX, IDC_EDIT_INIT_VALUE, m_editInitValueCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BaseClassInitDlg, CDialog)
	//{{AFX_MSG_MAP(BaseClassInitDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BaseClassInitDlg message handlers

BOOL BaseClassInitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	if (_initValue->GetCount() == 0) return TRUE;

	POSITION pos = _initValue->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = _initValue->GetNext(pos);
		m_editInitValueCtrl.ReplaceSel(aLine);
		if (pos != NULL) 
			m_editInitValueCtrl.ReplaceSel("\r\n");
	} 
	m_editInitValueCtrl.SetSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void BaseClassInitDlg::OnOK() 
{
	// TODO: Add extra validation here
	_initValue->RemoveAll();
	int nOfLines = m_editInitValueCtrl.GetLineCount(); 
	if (nOfLines > 0) {
		int i = 0;
		for (i = 0; i < nOfLines; i++) {
			char lineBuffer[BUFSIZ];
			int n = m_editInitValueCtrl.GetLine(i,lineBuffer,BUFSIZ);
			if (n < 0 || n >= BUFSIZ) {
				WarningMsg("Some line in this method is too long.\r\nThe line is truncated.");
				lineBuffer[BUFSIZ] = '\0';
			} else {
				lineBuffer[n] = '\0';
			}
			CString aValue = lineBuffer;
			aValue.TrimLeft();
			if (!aValue.IsEmpty()) 
				_initValue->AddTail(lineBuffer);
		}
	}
	CDialog::OnOK();
}
