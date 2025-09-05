// ClassDocumentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "ClassDocumentDlg.h"
#include "KtgMacro.h"
#include "ClassContent.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ClassDocumentDlg dialog
IMPLEMENT_DYNAMIC(ClassDocumentDlg,MemberOptionDlg)

ClassDocumentDlg::ClassDocumentDlg(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(ClassDocumentDlg::IDD, pParent)
{
	_whichRadio = HFFRONT;
	_pFocusEditCtrl = NIL;
	_currentDocument = NIL;
	//{{AFX_DATA_INIT(ClassDocumentDlg)
	m_staticBegin = _T("");
	m_staticEnd = _T("");
	//}}AFX_DATA_INIT
}


void ClassDocumentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ClassDocumentDlg)
	DDX_Control(pDX, IDC_RADIO_HF_MIDDLE, m_radioHFMiddleCtrl);
	DDX_Control(pDX, IDC_RADIO_SF_FRONT, m_radioSFFrontCtrl);
	DDX_Control(pDX, IDC_RADIO_HF_END, m_radioHFEndCtrl);
	DDX_Control(pDX, IDC_EDIT_DOCUMENT, m_editDocumentCtrl);
	DDX_Control(pDX, IDC_RADIO_HF_FRONT, m_radioHFFrontCtrl);
	DDX_Text(pDX, IDC_STATIC_BEGIN, m_staticBegin);
	DDX_Text(pDX, IDC_STATIC_END, m_staticEnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ClassDocumentDlg, CDialog)
	//{{AFX_MSG_MAP(ClassDocumentDlg)
	ON_EN_SETFOCUS(IDC_EDIT_DOCUMENT, OnSetfocusEditDocument)
	ON_EN_KILLFOCUS(IDC_EDIT_DOCUMENT, OnKillfocusEditDocument)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_RADIO_HF_END, OnRadioHfEnd)
	ON_BN_CLICKED(IDC_RADIO_HF_FRONT, OnRadioHfFront)
	ON_BN_CLICKED(IDC_RADIO_SF_FRONT, OnRadioSfFront)
	ON_BN_CLICKED(IDC_RADIO_HF_MIDDLE, OnRadioHfMiddle)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ClassDocumentDlg message handlers

void ClassDocumentDlg::clearContents()
{
	_currentDocument = NIL;
	MemberOptionDlg::clearContents();
	m_editDocumentCtrl.SetWindowText("");
	m_radioHFFrontCtrl.SetCheck(0);
	m_radioHFMiddleCtrl.SetCheck(0);
	m_radioSFFrontCtrl.SetCheck(0);
	m_radioHFEndCtrl.SetCheck(0);
}

void ClassDocumentDlg::setStaticTitle(int which) 
{
	if (which == HFFRONT) {
		m_staticBegin = "//{{MODELER_BEFORE_CLASS(" + _classContent->className() + ")";
		m_staticEnd = "//}}MODELER_BEFORE_CLASS";
	} else if (which == SFFRONT) {
		m_staticBegin = "//{{MODELER_SOURCE_DOCUMENT(" + _classContent->className() + ")";
		m_staticEnd = "//}}MODELER_SOURCE_DOCUMENT";
	} else if (which == HFMIDDLE) {
		m_staticBegin = "//{{MODELER_IN_CLASS(" + _classContent->className() + ")";
		m_staticEnd = "//}}MODELER_IN_CLASS";
	} else if (which == HFEND) {
		m_staticBegin = "//{{MODELER_AFTER_CLASS(" + _classContent->className() + ")";
		m_staticEnd = "//}}MODELER_AFTER_CLASS";
	}
	UpdateData(FALSE);
}

void ClassDocumentDlg::loadDocument()
{
	m_editDocumentCtrl.SetWindowText("");
	int totalChars = 0;
	POSITION pos = _currentDocument->GetHeadPosition();
	while (pos != NULL) {
		CString aLine = _currentDocument->GetNext(pos);
		totalChars = totalChars + aLine.GetLength();
		m_editDocumentCtrl.ReplaceSel(aLine);
		if (pos != NULL) 
			m_editDocumentCtrl.ReplaceSel("\r\n");
	} 
	m_editDocumentCtrl.SetSel(0);
	Invalidate();
	setModifiedFlag(FALSE);
}

void ClassDocumentDlg::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	if (aContent == NIL) return;

	setCurrentLine(aLine);
	_classContent = aContent;

	m_radioHFFrontCtrl.SetCheck(1);
	setStaticTitle(HFFRONT);
	_whichRadio = HFFRONT;

	_currentDocument = aContent->headerFileFrontDocument();
	int nOfLines = _currentDocument->GetCount();
	if (nOfLines == 0) {
		_classContent->resetDocument(_currentDocument,HFFRONT);
	}
	loadDocument();
}

BOOL ClassDocumentDlg::writeOptionsToClassTextLine()
{
	OnButtonSave();
	return FALSE;
}

void ClassDocumentDlg::OnSetfocusEditDocument() 
{
	// TODO: Add your control notification handler code here
	
	_pFocusEditCtrl = &m_editDocumentCtrl;
}

void ClassDocumentDlg::OnKillfocusEditDocument() 
{
	// TODO: Add your control notification handler code here
	
	_pFocusEditCtrl = NIL;
}

BOOL ClassDocumentDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN) {
		setModifiedFlag(TRUE);
	}
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
		for (int i = 0; i < n; i++) {
			if (lineBuffer[i] == '\t') nTabs++;
			else break;
		}
		_pFocusEditCtrl->ReplaceSel("\r\n");
		for (int i = 0; i < nTabs; i++) {
			_pFocusEditCtrl->ReplaceSel("\t");
		}
		return -1;
	}
	return MemberOptionDlg::PreTranslateMessage(pMsg);
}

BOOL ClassDocumentDlg::OnInitDialog() 
{
	MemberOptionDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_editDocumentCtrl.SetTabStops(12);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ClassDocumentDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	
	UINT ans = YesNoMsg("Are you sure to reset the comment block ?");
	if (ans != IDYES) return;

	if (_classContent == NIL) return;
	setStaticTitle(_whichRadio);

	_classContent->resetDocument(_currentDocument,_whichRadio);
	loadDocument();
}

void ClassDocumentDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	if (isModified() == FALSE) return;
	if (_currentDocument == NIL) return;

	_currentDocument->RemoveAll(); 
	int nOfLines = m_editDocumentCtrl.GetLineCount();
	if (nOfLines == 0) return;

	int i = 0;
	for (i = 0; i < nOfLines; i++) {
		char lineBuffer[BUFSIZ];
		int n = m_editDocumentCtrl.GetLine(i,lineBuffer,BUFSIZ);
		if (n < 0 || n >= BUFSIZ) {
			WarningMsg("Some line in this document is too long.\r\nThe line is truncated.");
			lineBuffer[BUFSIZ] = '\0';
		} else {
			lineBuffer[n] = '\0';
		}
		_currentDocument->AddTail(lineBuffer);
	}

	setModifiedFlag(FALSE);
}

void ClassDocumentDlg::OnRadioHfEnd() 
{
	// TODO: Add your control notification handler code here
	if (_classContent == NIL) return;

	if (isModified() == TRUE) {
		UINT ans = YesNoMsg("Save changes ?");
		if (ans == IDYES) {
			OnButtonSave();
		}
	}
	_whichRadio = HFEND;
	setStaticTitle(_whichRadio);
	_currentDocument = _classContent->headerFileEndDocument();
	int nOfLines = _currentDocument->GetCount();
	if (nOfLines == 0) {
		_classContent->resetDocument(_currentDocument,_whichRadio);
	}
	loadDocument();
}

void ClassDocumentDlg::OnRadioHfFront() 
{
	// TODO: Add your control notification handler code here
	if (_classContent == NIL) return;
	
	if (isModified() == TRUE) {
		UINT ans = YesNoMsg("Save changes ?");
		if (ans == IDYES) {
			OnButtonSave();
		}
	}
	_whichRadio = HFFRONT;
	_currentDocument = _classContent->headerFileFrontDocument();
	setStaticTitle(_whichRadio);
	loadDocument();
	setModifiedFlag(FALSE);
}

void ClassDocumentDlg::OnRadioSfFront() 
{
	// TODO: Add your control notification handler code here
	if (_classContent == NIL) return;

	if (isModified() == TRUE) {
		UINT ans = YesNoMsg("Save changes ?");
		if (ans == IDYES) {
			OnButtonSave();
		}
	}
	_whichRadio = SFFRONT;
	setStaticTitle(_whichRadio);
	_currentDocument = _classContent->sourceFileFrontDocument();
	int nOfLines = _currentDocument->GetCount();
	if (nOfLines == 0) {
		_classContent->resetDocument(_currentDocument,_whichRadio);
	}
	loadDocument();
}

void ClassDocumentDlg::OnRadioHfMiddle() 
{
	// TODO: Add your control notification handler code here
	
	if (_classContent == NIL) return;
	if (isModified() == TRUE) {
		UINT ans = YesNoMsg("Save changes ?");
		if (ans == IDYES) {
			OnButtonSave();
		}
	}
	_whichRadio = HFMIDDLE;
	setStaticTitle(_whichRadio);
	_currentDocument = _classContent->headerFileMiddleDocument();
	int nOfLines = _currentDocument->GetCount();
	if (nOfLines == 0) {
		_classContent->resetDocument(_currentDocument,_whichRadio);
	}
	loadDocument();
}

void ClassDocumentDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages

	CString language = theAppPtr->projectLanguage;
	if (language.CompareNoCase("Java") == 0) {
		m_radioHFFrontCtrl.EnableWindow(TRUE);
		m_radioHFMiddleCtrl.EnableWindow(TRUE);
		m_radioSFFrontCtrl.EnableWindow(FALSE);
		m_radioHFEndCtrl.EnableWindow(FALSE);
	} else if (language.CompareNoCase("C#") == 0) {
		m_radioHFFrontCtrl.EnableWindow(TRUE);
		m_radioHFMiddleCtrl.EnableWindow(TRUE);
		m_radioSFFrontCtrl.EnableWindow(FALSE);
		m_radioHFEndCtrl.EnableWindow(FALSE);
	} else if (language.CompareNoCase("Generic C++") == 0) {
		m_radioHFFrontCtrl.EnableWindow(TRUE);
		m_radioHFMiddleCtrl.EnableWindow(TRUE);
		m_radioSFFrontCtrl.EnableWindow(TRUE);
		m_radioHFEndCtrl.EnableWindow(FALSE);
	} else if (language.CompareNoCase("Visual C++") == 0) {
		m_radioHFFrontCtrl.EnableWindow(TRUE);
		m_radioHFMiddleCtrl.EnableWindow(TRUE);
		m_radioSFFrontCtrl.EnableWindow(TRUE);
		m_radioHFEndCtrl.EnableWindow(TRUE);
	}
}
