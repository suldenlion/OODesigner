// JavaMethodPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "JavaMethodPropGeneral.h"
#include "ClassTextLine.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// JavaMethodPropGeneral dialog


JavaMethodPropGeneral::JavaMethodPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(JavaMethodPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(JavaMethodPropGeneral)
	m_comboVisibility = _T("");
	//}}AFX_DATA_INIT
}


void JavaMethodPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(JavaMethodPropGeneral)
	DDX_Control(pDX, IDC_CHECK_FINAL, m_checkFinalCtrl);
	DDX_Control(pDX, IDC_CHECK_NATIVE, m_checkNativeCtrl);
	DDX_Control(pDX, IDC_CHECK_SYNCHRONIZED, m_checkSynchronizedCtrl);
	DDX_Control(pDX, IDC_CHECK_STATIC, m_checkStaticCtrl);
	DDX_Control(pDX, IDC_CHECK_ABSTRACT, m_checkAbstractCtrl);
	DDX_CBString(pDX, IDC_COMBO_VISIBILITY, m_comboVisibility);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(JavaMethodPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(JavaMethodPropGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// JavaMethodPropGeneral message handlers

void JavaMethodPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
}

void JavaMethodPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);

	loadVisibilityForMember(m_comboVisibility);
	loadButtonState(&m_checkAbstractCtrl,aLine->abstractFlag());
	loadButtonState(&m_checkNativeCtrl,aLine->nativeFlag());
	loadButtonState(&m_checkStaticCtrl,aLine->staticFlag());
	loadButtonState(&m_checkSynchronizedCtrl,aLine->synchronizedFlag());
	loadButtonState(&m_checkFinalCtrl,aLine->finalFlag());
	UpdateData(FALSE);
}

BOOL JavaMethodPropGeneral::writeOptionsToClassTextLine()
{
	if (_currentLine == NIL) return FALSE;

	BOOL repaintFlag = FALSE;
	repaintFlag = writeButtonState(&m_checkAbstractCtrl,_currentLine->abstractFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkNativeCtrl,_currentLine->nativeFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkStaticCtrl,_currentLine->staticFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkSynchronizedCtrl,_currentLine->synchronizedFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkFinalCtrl,_currentLine->finalFlag()) || repaintFlag;
	repaintFlag = writeVisibilityForMember(m_comboVisibility) || repaintFlag;
	return repaintFlag;
}
