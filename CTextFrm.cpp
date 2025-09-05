// CTextFrm.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CTextFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTextFrm, CChildFrm)
/////////////////////////////////////////////////////////////////////////////
// CTextFrm

CTextFrm::CTextFrm()
: CChildFrm()
{
}

CTextFrm::~CTextFrm()
{
}


BEGIN_MESSAGE_MAP(CTextFrm, CChildFrm)
	//{{AFX_MSG_MAP(CTextFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTextFrm message handlers
void CTextFrm::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
}
