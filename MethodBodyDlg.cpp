// MethodBodyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "MethodBodyDlg.h"
#include "ClassTextLine.h"
#include "BaseClassInitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int MethodBodyDlg::BoundaryGapX = 60;
const int MethodBodyDlg::BoundaryGapY = 158;

const int MethodBodyDlg::BoundaryGapXForEditBox = 26;
const int MethodBodyDlg::BoundaryGapYForEditBox = 69;

const int MethodBodyDlg::BoundaryGapXForBrace = 32;
const int MethodBodyDlg::BoundaryGapYForBrace = 86;

/////////////////////////////////////////////////////////////////////////////
// MethodBodyDlg dialog
IMPLEMENT_DYNAMIC(MethodBodyDlg,MemberOptionDlg)

MethodBodyDlg::MethodBodyDlg(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(MethodBodyDlg::IDD, pParent)
{
	_pFocusEditCtrl = NIL;
	//{{AFX_DATA_INIT(MethodBodyDlg)
	m_editMethodBody = _T("");
	//}}AFX_DATA_INIT
}


void MethodBodyDlg::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MethodBodyDlg)
	DDX_Control(pDX, IDC_STATIC_CLOSING_BRACE, m_staticClosingBrace);
	DDX_Control(pDX, IDC_BUTTON_MORE, m_buttonMore);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboTypeCtrl);
	DDX_Control(pDX, IDC_STATIC_SIGNATURE, m_staticSignature);
	DDX_Control(pDX, IDC_EDIT_METHOD_BODY, m_editMethodBodyCtrl);
	DDX_Text(pDX, IDC_EDIT_METHOD_BODY, m_editMethodBody);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MethodBodyDlg, MemberOptionDlg)
	//{{AFX_MSG_MAP(MethodBodyDlg)
	ON_CBN_DROPDOWN(IDC_COMBO_TYPE, OnDropdownComboType)
	ON_CBN_EDITCHANGE(IDC_COMBO_TYPE, OnEditchangeComboType)
	ON_EN_KILLFOCUS(IDC_EDIT_METHOD_BODY, OnKillfocusEditMethodBody)
	ON_EN_SETFOCUS(IDC_EDIT_METHOD_BODY, OnSetfocusEditMethodBody)
	ON_BN_CLICKED(IDC_BUTTON_MORE, OnButtonMore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MethodBodyDlg message handlers

void MethodBodyDlg::clearContents()
{
	MemberOptionDlg::clearContents();
	m_editMethodBodyCtrl.SetWindowText("");
	m_staticSignature.SetWindowText("return_type function_name(type arg, ...) {");
}

void MethodBodyDlg::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);

	loadType(&m_comboTypeCtrl,aLine->type());

	CString memberName = _T("");

	CString signature = "";
	aLine->getMemberBrowserString(signature);
	if (languageName.CompareNoCase("Java") != 0) {
		memberName = memberName + className + "::";
		if (className.CompareNoCase(aLine->name()) == 0) {
			m_buttonMore.ShowWindow(SW_SHOW);
		} else {
			m_buttonMore.ShowWindow(SW_HIDE);
		}
	}
	memberName = memberName + signature + " {";
	m_staticSignature.SetWindowText(memberName);

	CStringList &functionBody = _currentLine->functionBody();
	int nOfLines = functionBody.GetCount();
	if (nOfLines == 0) return;

	POSITION pos = functionBody.GetHeadPosition();
	while (pos != NULL) {
		CString aLine = functionBody.GetNext(pos);
		m_editMethodBodyCtrl.ReplaceSel(aLine);
		if (pos != NULL) 
			m_editMethodBodyCtrl.ReplaceSel("\r\n");
	} 
	m_editMethodBodyCtrl.SetSel(0);
	Invalidate();
}

BOOL MethodBodyDlg::writeOptionsToClassTextLine()
{
	writeType(&m_comboTypeCtrl,_currentLine->type());

	CStringList &functionBody = _currentLine->functionBody();
	functionBody.RemoveAll(); 

	int nOfLines = m_editMethodBodyCtrl.GetLineCount();
	if (nOfLines == 0) return FALSE;

	int i = 0;
	for (i = 0; i < nOfLines; i++) {
		char lineBuffer[BUFSIZ];
		int n = m_editMethodBodyCtrl.GetLine(i,lineBuffer,BUFSIZ);
		if (n < 0 || n >= BUFSIZ) {
			WarningMsg("Some line in this method is too long.\r\nThe line is truncated.");
			lineBuffer[BUFSIZ] = '\0';
		} else {
			lineBuffer[n] = '\0';
		}
		functionBody.AddTail(lineBuffer);
	}

	return FALSE;
}

BOOL MethodBodyDlg::OnInitDialog() 
{
	MemberOptionDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_editMethodBodyCtrl.SetTabStops(12);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MethodBodyDlg::OnDropdownComboType() 
{
	// TODO: Add your control notification handler code here
	
	setModifiedFlag(TRUE);
}

void MethodBodyDlg::OnEditchangeComboType() 
{
	// TODO: Add your control notification handler code here
	
	setModifiedFlag(TRUE);
}

void MethodBodyDlg::OnKillfocusEditMethodBody() 
{
	// TODO: Add your control notification handler code here
	_pFocusEditCtrl = NIL;
}

void MethodBodyDlg::OnSetfocusEditMethodBody() 
{
	// TODO: Add your control notification handler code here
	_pFocusEditCtrl = &m_editMethodBodyCtrl;
}

BOOL MethodBodyDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && (LOWORD(pMsg->wParam) == VK_TAB) && _pFocusEditCtrl != NIL) {
		_pFocusEditCtrl->ReplaceSel("\t");
		return -1;
	}
	if (pMsg->message == WM_KEYDOWN && (LOWORD(pMsg->wParam) == VK_RETURN) && _pFocusEditCtrl != NIL) {
		int index = _pFocusEditCtrl->LineFromChar();
		char lineBuffer[BUFSIZ];
		int n = _pFocusEditCtrl->GetLine(index,lineBuffer,BUFSIZ);
		lineBuffer[n] = '\0';
		int nTabs = 0;
		int i;
		for (i = 0; i < n; i++) {
			if (lineBuffer[i] == '\t') nTabs++;
			else break;
		}
		_pFocusEditCtrl->ReplaceSel("\r\n");
		for (i = 0; i < nTabs; i++) {
			_pFocusEditCtrl->ReplaceSel("\t");
		}
		return -1;
	}
	return MemberOptionDlg::PreTranslateMessage(pMsg);
}

void MethodBodyDlg::OnButtonMore() 
{
	// TODO: Add your control notification handler code here
	
	BaseClassInitDlg aDlg(_currentLine->baseClassInitialization());
	aDlg.DoModal();
}

void MethodBodyDlg::resizeDialogToFitPropertyDialog(RECT propRect)
{
	int w = propRect.right - propRect.left;
	int h = propRect.bottom - propRect.top;
	int newW = w-BoundaryGapX;
	int newH = h-BoundaryGapY;
	SetWindowPos(NULL,0,0,newW,newH,SWP_NOMOVE);
	m_editMethodBodyCtrl.SetWindowPos(NULL,0,0,
			newW-BoundaryGapXForEditBox,newH-BoundaryGapYForEditBox,SWP_NOMOVE);

	RECT editBoxRect;
	m_editMethodBodyCtrl.GetWindowRect(&editBoxRect);
	int newX = editBoxRect.left - propRect.left - BoundaryGapXForBrace;
	int newY = editBoxRect.bottom - propRect.top - BoundaryGapYForBrace;
	m_staticClosingBrace.SetWindowPos(NULL,newX,newY,0,0,SWP_NOSIZE);
}
