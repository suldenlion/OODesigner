// CProjectOptionsMacros.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CProjectOptionsMacros.h"
#include "KtgMacro.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsMacros dialog


CProjectOptionsMacros::CProjectOptionsMacros(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectOptionsMacros::IDD, pParent)
{
	_language = _T("");
	//{{AFX_DATA_INIT(CProjectOptionsMacros)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProjectOptionsMacros::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectOptionsMacros)
	DDX_Control(pDX, IDC_EDIT_SOURCEFILE, m_editSourceFileCtrl);
	DDX_Control(pDX, IDC_EDIT_HEADERFILE, m_editHeaderFileCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectOptionsMacros, CDialog)
	//{{AFX_MSG_MAP(CProjectOptionsMacros)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectOptionsMacros message handlers

void CProjectOptionsMacros::writeMacros()
{
	UpdateData();
	if (_language.CompareNoCase("Java") == 0) return;
	
	writeAMacro(theAppPtr->getHeaderFileAbsMacros(_language),m_editHeaderFileCtrl);
	writeAMacro(theAppPtr->getSourceFileAbsMacros(_language),m_editSourceFileCtrl);
}

void CProjectOptionsMacros::writeAMacro(CStringList &theMacro,CEdit &theEditCtrl)
{
	int nOfLines = theEditCtrl.GetLineCount();

	theMacro.RemoveAll();
	if (nOfLines == 0) {
		return;
	} else if (nOfLines == 1) {
		char lineBuffer[BUFSIZ];
		int n = theEditCtrl.GetLine(nOfLines-1,lineBuffer,BUFSIZ);
		if (n <= 0) return;
		lineBuffer[n] = '\0';
		theMacro.AddTail(lineBuffer);
		return;
	}

	// 우선 실제 의미 있는 라인 수를 센다. 뒷 부분의 빈 라인 삭제...
	int nOfActualLine = nOfLines;

	while (nOfLines > 0) {
		char lineBuffer[BUFSIZ];
		int n = theEditCtrl.GetLine(nOfLines-1,lineBuffer,BUFSIZ);
		if (n > 0) {
			break;
		}
		nOfLines--;
	}
	
	// 다시 한번 boundary condition 경우
	if (nOfLines == 0) {
		return;
	} else if (nOfLines == 1) {
		char lineBuffer[BUFSIZ];
		int n = theEditCtrl.GetLine(nOfLines-1,lineBuffer,BUFSIZ);
		if (n <= 0) return;
		lineBuffer[n] = '\0';
		theMacro.AddTail(lineBuffer);
		return;
	}

	int i = 0;
	for (i = 0; i < nOfLines; i++) {
		char lineBuffer[BUFSIZ];
		int n = theEditCtrl.GetLine(i,lineBuffer,BUFSIZ);
		if (n < 0 || n >= BUFSIZ) {
			WarningMsg("Some line in this macro definition is too long.\r\nThe line is truncated.");
			lineBuffer[BUFSIZ] = '\0';
		} else {
			lineBuffer[n] = '\0';
		}
		theMacro.AddTail(lineBuffer);
	}
}

void CProjectOptionsMacros::languageSelected(CString &language)
{
	_language = language;
	if (language.CompareNoCase("Java") == 0) {
		m_editHeaderFileCtrl.SetWindowText("");
		m_editSourceFileCtrl.SetWindowText("");

		m_editHeaderFileCtrl.EnableWindow(FALSE);
		m_editSourceFileCtrl.EnableWindow(FALSE);
	} else if (language.CompareNoCase("C#") == 0) {
		// 나중에 ...
		m_editHeaderFileCtrl.SetWindowText("");
		m_editSourceFileCtrl.SetWindowText("");

		m_editHeaderFileCtrl.EnableWindow(FALSE);
		m_editSourceFileCtrl.EnableWindow(FALSE);
	} else { 
		m_editHeaderFileCtrl.EnableWindow(TRUE);
		m_editSourceFileCtrl.EnableWindow(TRUE);

		m_editHeaderFileCtrl.SetWindowText("");
		m_editSourceFileCtrl.SetWindowText("");
		CStringList &hpMacros = theAppPtr->getHeaderFileAbsMacros(language);
		POSITION pos = hpMacros.GetHeadPosition();
		while (pos != NULL) {
			CString aLine = hpMacros.GetNext(pos);
			m_editHeaderFileCtrl.ReplaceSel(aLine);
			if (pos != NULL) 
				m_editHeaderFileCtrl.ReplaceSel("\r\n");
		} 

		CStringList &spMacros = theAppPtr->getSourceFileAbsMacros(language);
		pos = spMacros.GetHeadPosition();
		while (pos != NULL) {
			CString aLine = spMacros.GetNext(pos);
			m_editSourceFileCtrl.ReplaceSel(aLine);
			if (pos != NULL) 
				m_editSourceFileCtrl.ReplaceSel("\r\n");
		} 
	}
}
