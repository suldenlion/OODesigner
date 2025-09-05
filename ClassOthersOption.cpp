// ClassOthersOption.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "ClassOthersOption.h"
#include "ClassContent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ClassOthersOption dialog


ClassOthersOption::ClassOthersOption(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(ClassOthersOption::IDD, pParent)
{
	//{{AFX_DATA_INIT(ClassOthersOption)
	m_editDirectory = _T("");
	m_editFileName = _T("");
	//}}AFX_DATA_INIT
}


void ClassOthersOption::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ClassOthersOption)
	DDX_Control(pDX, IDC_CHECK_CODE, m_checkCodeCtrl);
	DDX_Text(pDX, IDC_EDIT_DIRECTORY, m_editDirectory);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_editFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ClassOthersOption, MemberOptionDlg)
	//{{AFX_MSG_MAP(ClassOthersOption)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ClassOthersOption message handlers

void ClassOthersOption::clearContents()
{
	MemberOptionDlg::clearContents();
	m_editDirectory = _T("");
	m_editFileName = _T("");
	UpdateData(FALSE);
}

void ClassOthersOption::loadTargetDirectoryForCodeGeneration(CString &directory)
{
	directory = _classContent->targetDirectoryForCodeGeneration();
}

void ClassOthersOption::loadFileNameSpecified(CString &fileName)
{
	fileName = _classContent->fileNameSpecified();
}

void ClassOthersOption::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);
	_classContent = aContent;

	loadTargetDirectoryForCodeGeneration(m_editDirectory);
	loadFileNameSpecified(m_editFileName);
	loadButtonState(&m_checkCodeCtrl,aContent->generateCodeFlag());
	UpdateData(FALSE);
}

BOOL ClassOthersOption::writeFileNameSpecified(CString &fileName)
{
	if (_classContent == NIL) return FALSE;

	CString fname = _classContent->fileNameSpecified();
	if (fname.CompareNoCase(fileName) == 0) {
		return FALSE;
	}

	_classContent->setFileNameSpecified(fileName);
	return TRUE;
}

BOOL ClassOthersOption::writeOptionsToClassTextLine()
{
	if (_classContent == NIL) return FALSE;

	BOOL repaintFlag = FALSE;

	repaintFlag = writeFileNameSpecified(m_editFileName) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkCodeCtrl,_classContent->generateCodeFlag()) || repaintFlag;
	return repaintFlag;
}
