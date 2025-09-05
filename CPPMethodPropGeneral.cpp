// CPPMethodPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CPPMethodPropGeneral.h"
#include "ClassTextLine.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPMethodPropGeneral dialog


CPPMethodPropGeneral::CPPMethodPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(CPPMethodPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPPMethodPropGeneral)
	m_comboVisibility = _T("");
	//}}AFX_DATA_INIT
}


void CPPMethodPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPMethodPropGeneral)
	DDX_Control(pDX, IDC_CHECK_VIRTUAL, m_checkVirtualCtrl);
	DDX_Control(pDX, IDC_CHECK_STATIC, m_checkStaticCtrl);
	DDX_Control(pDX, IDC_CHECK_INLINE, m_checkInlineCtrl);
	DDX_Control(pDX, IDC_CHECK_CONST, m_checkConstCtrl);
	DDX_CBString(pDX, IDC_COMBO_VISIBILITY, m_comboVisibility);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPMethodPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(CPPMethodPropGeneral)
	ON_BN_CLICKED(IDC_CHECK_STATIC, OnCheckStatic)
	ON_BN_CLICKED(IDC_CHECK_VIRTUAL, OnCheckVirtual)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPMethodPropGeneral message handlers

void CPPMethodPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
}

void CPPMethodPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);

	loadVisibilityForMember(m_comboVisibility);

	loadButtonState(&m_checkInlineCtrl,aLine->inlineFlag());
	loadButtonState(&m_checkConstCtrl,aLine->constFlag());
	if (aLine->staticFlag() == TRUE) {
		aLine->virtualFlag() = FALSE;
	} else if (aLine->virtualFlag() == TRUE) {
		aLine->staticFlag() = FALSE;
	}
	loadButtonState(&m_checkStaticCtrl,aLine->staticFlag());
	loadButtonState(&m_checkVirtualCtrl,aLine->virtualFlag());
	UpdateData(FALSE);
}

BOOL CPPMethodPropGeneral::writeOptionsToClassTextLine()
{
	if (_currentLine == NIL) return FALSE;

	BOOL repaintFlag = FALSE;
	repaintFlag = writeButtonState(&m_checkInlineCtrl,_currentLine->inlineFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkConstCtrl,_currentLine->constFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkStaticCtrl,_currentLine->staticFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkVirtualCtrl,_currentLine->virtualFlag()) || repaintFlag;
	repaintFlag = writeVisibilityForMember(m_comboVisibility) || repaintFlag;
	return repaintFlag;
}


void CPPMethodPropGeneral::OnCheckStatic() 
{
	// TODO: Add your control notification handler code here
	if (m_checkStaticCtrl.GetCheck() == 0) return;
	m_checkVirtualCtrl.SetCheck(0);
}

void CPPMethodPropGeneral::OnCheckVirtual() 
{
	// TODO: Add your control notification handler code here
	if (m_checkVirtualCtrl.GetCheck() == 0) return;
	m_checkStaticCtrl.SetCheck(0);	
}
