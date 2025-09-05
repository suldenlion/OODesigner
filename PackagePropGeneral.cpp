// PackagePropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "PackagePropGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PackagePropGeneral dialog


PackagePropGeneral::PackagePropGeneral(CWnd* pParent /*=NULL*/)
	: CDialog(PackagePropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(PackagePropGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PackagePropGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PackagePropGeneral)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PackagePropGeneral, CDialog)
	//{{AFX_MSG_MAP(PackagePropGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PackagePropGeneral message handlers
