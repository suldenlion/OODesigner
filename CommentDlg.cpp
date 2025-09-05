// CommentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "CommentDlg.h"
#include "ClassTextLine.h"
#include "ClassContent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int CommentDlg::BoundaryGapX = 60;
const int CommentDlg::BoundaryGapY = 158;

const int CommentDlg::BoundaryGapXForEditBox = 26;
const int CommentDlg::BoundaryGapYForEditBox = 69;

/////////////////////////////////////////////////////////////////////////////
// CommentDlg dialog
IMPLEMENT_DYNAMIC(CommentDlg,MemberOptionDlg)

CommentDlg::CommentDlg(const char* forName,CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(CommentDlg::IDD, pParent)
{
	_pFocusEditCtrl = NIL;
	//{{AFX_DATA_INIT(CommentDlg)
	m_editComment = _T("");
	m_staticForName = _T(forName);
	//}}AFX_DATA_INIT
}


void CommentDlg::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CommentDlg)
	DDX_Control(pDX, IDC_EDIT_COMMENT, m_editCommentCtrl);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_editComment);
	DDX_Text(pDX, IDC_STATIC_FOR_NAME, m_staticForName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CommentDlg, MemberOptionDlg)
	//{{AFX_MSG_MAP(CommentDlg)
	ON_EN_KILLFOCUS(IDC_EDIT_COMMENT, OnKillfocusEditComment)
	ON_EN_SETFOCUS(IDC_EDIT_COMMENT, OnSetfocusEditComment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CommentDlg message handlers

void CommentDlg::clearContents()
{
	MemberOptionDlg::clearContents();
	m_editCommentCtrl.SetWindowText("");
}

void CommentDlg::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);

	CStringList *comment;
	if (_currentLine == NIL) {
		return;
	}
	comment = _currentLine->comment();

	int nOfLines = comment->GetCount();
	if (nOfLines == 0) {
		m_editCommentCtrl.ReplaceSel("/**\r\n */");
		return;
	}

	int totalChars = 0;
	POSITION pos = comment->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = comment->GetNext(pos);
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

BOOL CommentDlg::writeOptionsToClassTextLine()
{
	CStringList *comment;
	if (_currentLine == NIL) {
		return FALSE;
	}
	comment = _currentLine->comment();
	comment->RemoveAll(); 
	int nOfLines = m_editCommentCtrl.GetLineCount();
	if (nOfLines == 0) return FALSE;

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
		comment->AddTail(lineBuffer);
	}

	return FALSE;
}

void CommentDlg::OnKillfocusEditComment() 
{
	// TODO: Add your control notification handler code here
	_pFocusEditCtrl = NIL;	
}

void CommentDlg::OnSetfocusEditComment() 
{
	// TODO: Add your control notification handler code here
	_pFocusEditCtrl = &m_editCommentCtrl;	
}

BOOL CommentDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pMsg->message == WM_KEYDOWN && (LOWORD(pMsg->wParam) == VK_TAB) && _pFocusEditCtrl != NIL) {
		_pFocusEditCtrl->ReplaceSel("\t");
		return -1;
	}
	return MemberOptionDlg::PreTranslateMessage(pMsg);
}

BOOL CommentDlg::OnInitDialog() 
{
	MemberOptionDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_editCommentCtrl.SetTabStops(12);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CommentDlg::resizeDialogToFitPropertyDialog(RECT propRect)
{
	int w = propRect.right - propRect.left;
	int h = propRect.bottom - propRect.top;
	int newW = w-BoundaryGapX;
	int newH = h-BoundaryGapY;
	SetWindowPos(NULL,0,0,newW,newH,SWP_NOMOVE);
	m_editCommentCtrl.SetWindowPos(NULL,0,0,
			newW-BoundaryGapXForEditBox,newH-BoundaryGapYForEditBox,SWP_NOMOVE);
}
