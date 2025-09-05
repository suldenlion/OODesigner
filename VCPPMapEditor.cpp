// VCPPMapEditor.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "VCPPMapEditor.h"
#include "ClassContent.h"
#include "KtgMacro.h"
#include "RelationshipInfoTupleList.h"
#include "COODClassDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VCPPMapEditor dialog


VCPPMapEditor::VCPPMapEditor(CString &mapName,ClassContent *aContent,CWnd* pParent /*=NULL*/)
	: CDialog(VCPPMapEditor::IDD, pParent)
{
	_mapName = mapName;
	_classContent = aContent;
	_className = aContent->className();
	_pFocusEditCtrl = NIL;
	if (_mapName.CompareNoCase("MESSAGE_MAP") == 0) {
		_currentMap = aContent->messageMap();
	} else if (_mapName.CompareNoCase("INTERFACE_MAP") == 0) {
		_currentMap = aContent->interfaceMap();
	} else if (_mapName.CompareNoCase("DISPATCH_MAP") == 0) {
		_currentMap = aContent->dispatchMap();
	} else if (_mapName.CompareNoCase("OLECMD_MAP") == 0) {
		_currentMap = aContent->olecmdMap();
	} else if (_mapName.CompareNoCase("CONNECTION_MAP") == 0) {
		_currentMap = aContent->connectionMap();
	} else if (_mapName.CompareNoCase("EVENTSINK_MAP") == 0) {
		_currentMap = aContent->eventsinkMap();
	} else {
		_currentMap = aContent->unspecifiedMaps();
	}
	//{{AFX_DATA_INIT(VCPPMapEditor)
	m_staticBegin = _T("");
	m_staticEnd = _T("");
	//}}AFX_DATA_INIT
}


void VCPPMapEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VCPPMapEditor)
	DDX_Control(pDX, IDC_EDIT, m_editCtrl);
	DDX_Text(pDX, IDC_STATIC_BEGIN, m_staticBegin);
	DDX_Text(pDX, IDC_STATIC_END, m_staticEnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VCPPMapEditor, CDialog)
	//{{AFX_MSG_MAP(VCPPMapEditor)
	ON_EN_KILLFOCUS(IDC_EDIT, OnKillfocusEdit)
	ON_EN_SETFOCUS(IDC_EDIT, OnSetfocusEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VCPPMapEditor message handlers

BOOL VCPPMapEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	if (_mapName.CompareNoCase("unspecified maps") != 0) {
		CStringList superClassNames;
		if (theAppPtr->pCOODClassDoc != NIL)
			theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->getMajorClassNames(_className,superClassNames);
		CString superClassName = "CCmdTarget";
		POSITION pos = superClassNames.GetHeadPosition();
		if (pos != NULL) {
			superClassName = superClassNames.GetNext(pos);
		}

		m_staticBegin = m_staticBegin + "BEGIN_" + _mapName + "(" + _className + "," + superClassName + ")";
		m_staticEnd = m_staticEnd + "END_" + _mapName + "()";
	} else {
		m_staticBegin = "Please specify any maps you want.";
		m_staticEnd = _T("");
	}
	UpdateData(FALSE);
	m_editCtrl.SetTabStops(12);

	// loading of map contents
	int totalChars = 0;
	POSITION pos = _currentMap->GetHeadPosition();
	while(pos != NULL) {
		CString aLine = _currentMap->GetNext(pos);
		totalChars = totalChars + aLine.GetLength();
		m_editCtrl.ReplaceSel(aLine);
		if (pos != NULL) 
			m_editCtrl.ReplaceSel("\r\n");
	}
	// if message map content is empty
	if (_mapName.CompareNoCase("MESSAGE_MAP") == 0 &&
		totalChars == 0) {
		m_editCtrl.ReplaceSel("\t//{{AFX_MSG_MAP(");
		m_editCtrl.ReplaceSel(_className);
		m_editCtrl.ReplaceSel(")\r\n");
		m_editCtrl.ReplaceSel("\t\t// NOTE - the ClassWizard will add and remove mapping macros here.\r\n");
		m_editCtrl.ReplaceSel("\t//}}AFX_MSG_MAP");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void VCPPMapEditor::OnKillfocusEdit() 
{
	// TODO: Add your control notification handler code here
	_pFocusEditCtrl = NIL;	
}

void VCPPMapEditor::OnSetfocusEdit() 
{
	// TODO: Add your control notification handler code here
	
	_pFocusEditCtrl = &m_editCtrl;	
}

BOOL VCPPMapEditor::PreTranslateMessage(MSG* pMsg) 
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
	return CDialog::PreTranslateMessage(pMsg);
}

void VCPPMapEditor::OnOK() 
{
	// TODO: Add extra validation here
	
	_currentMap->RemoveAll(); 
	int nOfLines = m_editCtrl.GetLineCount();
	if (nOfLines > 0) {
		int i = 0;
		for (i = 0; i < nOfLines; i++) {
			char lineBuffer[BUFSIZ];
			int n = m_editCtrl.GetLine(i,lineBuffer,BUFSIZ);
			if (n < 0 || n >= BUFSIZ) {
				WarningMsg("Some line in this comment is too long.\r\nThe line is truncated.");
				lineBuffer[BUFSIZ] = '\0';
			} else {
				lineBuffer[n] = '\0';
			}
			_currentMap->AddTail(lineBuffer);
		}
	}
	CDialog::OnOK();
}
