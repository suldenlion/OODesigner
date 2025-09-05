// PackageCommentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "PackageCommentDlg.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PackageCommentDlg dialog


PackageCommentDlg::PackageCommentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PackageCommentDlg::IDD, pParent)
{
	_comment = NIL;
	_pFocusEditCtrl = NIL;
	//{{AFX_DATA_INIT(PackageCommentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void PackageCommentDlg::clearContents()
{
	m_editCommentCtrl.SetWindowText("");
	_comment = NIL;
}

void PackageCommentDlg::writeComment()
{
	if (_comment == NIL) return;
	_comment->RemoveAll(); 
	int nOfLines = m_editCommentCtrl.GetLineCount();
	if (nOfLines == 0) return;

	int i = 0;
	for (i = 0; i < nOfLines; i++) {
		char lineBuffer[BUFSIZ];
		int n = m_editCommentCtrl.GetLine(i,lineBuffer,BUFSIZ);
		if (n < 0 || n >= BUFSIZ) {
			WarningMsg("Some line in this comment is too long.\r\nThe line is truncated.");
			lineBuffer[BUFSIZ] = '\0';
		} else {
			lineBuffer[n] = '\0';
		}
		_comment->AddTail(lineBuffer);
	}
}

void PackageCommentDlg::loadComment(CStringList *comment)
{
	clearContents();
	if (comment == NIL) return;
	_comment = comment;

	int nOfLines = _comment->GetCount();
	if (nOfLines == 0) {
		m_editCommentCtrl.ReplaceSel("/**\r\n */");
		return;
	}

	int totalChars = 0;
	POSITION pos = _comment->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = _comment->GetNext(pos);
		totalChars = totalChars + aLine.GetLength();
		m_editCommentCtrl.ReplaceSel(aLine);
		if (pos != NULL) 
			m_editCommentCtrl.ReplaceSel("\r\n");
	} 

	if (totalChars == 0) {
		m_editCommentCtrl.ReplaceSel("/**\r\n */");
	}

	m_editCommentCtrl.SetSel(0);
	Invalidate();
}

void PackageCommentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PackageCommentDlg)
	DDX_Control(pDX, IDC_EDIT_COMMENT, m_editCommentCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PackageCommentDlg, CDialog)
	//{{AFX_MSG_MAP(PackageCommentDlg)
	ON_EN_KILLFOCUS(IDC_EDIT_COMMENT, OnKillfocusEditComment)
	ON_EN_SETFOCUS(IDC_EDIT_COMMENT, OnSetfocusEditComment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PackageCommentDlg message handlers

BOOL PackageCommentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_editCommentCtrl.SetTabStops(12);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PackageCommentDlg::OnKillfocusEditComment() 
{
	// TODO: Add your control notification handler code here
	
	_pFocusEditCtrl = NIL;	
}

void PackageCommentDlg::OnSetfocusEditComment() 
{
	// TODO: Add your control notification handler code here
	
	_pFocusEditCtrl = &m_editCommentCtrl;	
}

BOOL PackageCommentDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pMsg->message == WM_KEYDOWN && (LOWORD(pMsg->wParam) == VK_TAB) && _pFocusEditCtrl != NIL) {
		_pFocusEditCtrl->ReplaceSel("\t");
		return -1;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
