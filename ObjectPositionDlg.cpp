// ObjectPositionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "ObjectPositionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ObjectPositionDlg dialog


ObjectPositionDlg::ObjectPositionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ObjectPositionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ObjectPositionDlg)
	m_height = 100;
	m_width = 100;
	m_x = 0;
	m_y = 0;
	//}}AFX_DATA_INIT
}


void ObjectPositionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ObjectPositionDlg)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
	DDX_Text(pDX, IDC_EDIT_X, m_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ObjectPositionDlg, CDialog)
	//{{AFX_MSG_MAP(ObjectPositionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ObjectPositionDlg message handlers
