// CSharpMethodPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CSharpMethodPropGeneral.h"
#include "ClassTextLine.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSharpMethodPropGeneral dialog


CSharpMethodPropGeneral::CSharpMethodPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(CSharpMethodPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSharpMethodPropGeneral)
	m_comboVisibility = _T("");
	//}}AFX_DATA_INIT
}


void CSharpMethodPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSharpMethodPropGeneral)
	DDX_Control(pDX, IDC_CHECK_OVERRIDE, m_checkOverrideCtrl);
	DDX_Control(pDX, IDC_CHECK_EXTERN, m_checkExternCtrl);
	DDX_Control(pDX, IDC_CHECK_VIRTUAL, m_checkVirtualCtrl);
	DDX_Control(pDX, IDC_CHECK_STATIC, m_checkStaticCtrl);
	DDX_Control(pDX, IDC_CHECK_INTERNAL, m_checkInternalCtrl);
	DDX_Control(pDX, IDC_CHECK_ABSTRACT, m_checkAbstractCtrl);
	DDX_CBString(pDX, IDC_COMBO_VISIBILITY, m_comboVisibility);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSharpMethodPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(CSharpMethodPropGeneral)
	ON_BN_CLICKED(IDC_CHECK_STATIC, OnCheckStatic)
	ON_BN_CLICKED(IDC_CHECK_VIRTUAL, OnCheckVirtual)
	ON_BN_CLICKED(IDC_CHECK_INTERNAL, OnCheckInternal)
	ON_BN_CLICKED(IDC_CHECK_EXTERN, OnCheckExtern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSharpMethodPropGeneral message handlers
void CSharpMethodPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
}

void CSharpMethodPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);

	loadVisibilityForMember(m_comboVisibility);

	loadButtonState(&m_checkAbstractCtrl,aLine->abstractFlag());
	loadButtonState(&m_checkOverrideCtrl,aLine->overrideFlag());
	if (aLine->staticFlag() == TRUE) {
		aLine->virtualFlag() = FALSE;
	} else if (aLine->virtualFlag() == TRUE) {
		aLine->staticFlag() = FALSE;
	}
	loadButtonState(&m_checkStaticCtrl,aLine->staticFlag());
	loadButtonState(&m_checkVirtualCtrl,aLine->virtualFlag());
	if (aLine->internalFlag() == TRUE) {
		aLine->externFlag() = FALSE;
	} else if (aLine->externFlag() == TRUE) {
		aLine->internalFlag() = FALSE;
	}
	loadButtonState(&m_checkInternalCtrl,aLine->internalFlag());
	loadButtonState(&m_checkExternCtrl,aLine->externFlag());
	UpdateData(FALSE);
}

BOOL CSharpMethodPropGeneral::writeOptionsToClassTextLine()
{
	if (_currentLine == NIL) return FALSE;

	BOOL repaintFlag = FALSE;
	repaintFlag = writeButtonState(&m_checkStaticCtrl,_currentLine->staticFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkVirtualCtrl,_currentLine->virtualFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkInternalCtrl,_currentLine->internalFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkExternCtrl,_currentLine->externFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkAbstractCtrl,_currentLine->abstractFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkOverrideCtrl,_currentLine->overrideFlag()) || repaintFlag;
	repaintFlag = writeVisibilityForMember(m_comboVisibility) || repaintFlag;
	return repaintFlag;
}


void CSharpMethodPropGeneral::OnCheckStatic() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkStaticCtrl.GetCheck() == 0) return;
	m_checkVirtualCtrl.SetCheck(0);	
}

void CSharpMethodPropGeneral::OnCheckVirtual() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkVirtualCtrl.GetCheck() == 0) return;
	m_checkStaticCtrl.SetCheck(0);
}

void CSharpMethodPropGeneral::OnCheckInternal() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkInternalCtrl.GetCheck() == 0) return;
	m_checkExternCtrl.SetCheck(0);
}

void CSharpMethodPropGeneral::OnCheckExtern() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkExternCtrl.GetCheck() == 0) return;
	m_checkInternalCtrl.SetCheck(0);
}
