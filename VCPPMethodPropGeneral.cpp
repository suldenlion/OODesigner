// VCPPMethodPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "VCPPMethodPropGeneral.h"
#include "ClassTextLine.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VCPPMethodPropGeneral dialog


VCPPMethodPropGeneral::VCPPMethodPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(VCPPMethodPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(VCPPMethodPropGeneral)
	m_comboVisibility = _T("");
	//}}AFX_DATA_INIT
}


void VCPPMethodPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VCPPMethodPropGeneral)
	DDX_Control(pDX, IDC_CHECK_MFCVIRTUAL, m_checkMfcvirtualCtrl);
	DDX_Control(pDX, IDC_CHECK_VIRTUAL, m_checkVirtualCtrl);
	DDX_Control(pDX, IDC_CHECK_STATIC, m_checkStaticCtrl);
	DDX_Control(pDX, IDC_CHECK_AFXMSG, m_checkAfxmsgCtrl);
	DDX_Control(pDX, IDC_CHECK_INLINE, m_checkInlineCtrl);
	DDX_Control(pDX, IDC_CHECK_CONST, m_checkConstCtrl);
	DDX_CBString(pDX, IDC_COMBO_VISIBILITY, m_comboVisibility);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VCPPMethodPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(VCPPMethodPropGeneral)
	ON_BN_CLICKED(IDC_CHECK_AFXMSG, OnCheckAfxmsg)
	ON_BN_CLICKED(IDC_CHECK_STATIC, OnCheckStatic)
	ON_BN_CLICKED(IDC_CHECK_VIRTUAL, OnCheckVirtual)
	ON_BN_CLICKED(IDC_CHECK_MFCVIRTUAL, OnCheckMfcvirtual)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VCPPMethodPropGeneral message handlers

void VCPPMethodPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
}

void VCPPMethodPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);

	loadVisibilityForMember(m_comboVisibility);

	loadButtonState(&m_checkInlineCtrl,aLine->inlineFlag());
	loadButtonState(&m_checkConstCtrl,aLine->constFlag());
	if (aLine->staticFlag() == TRUE) {
		aLine->afxVirtualFlag() = FALSE;
		aLine->virtualFlag() = FALSE;
		aLine->afxMsgFlag() = FALSE;
	} else if (aLine->virtualFlag() == TRUE) {
		aLine->afxVirtualFlag() = FALSE;
		aLine->staticFlag() = FALSE;
		aLine->afxMsgFlag() = FALSE;
	} else if (aLine->afxMsgFlag() == TRUE) {
		aLine->afxVirtualFlag() = FALSE;
		aLine->staticFlag() = FALSE;
		aLine->virtualFlag() = FALSE;
	} else if (aLine->afxVirtualFlag() == TRUE) {
		aLine->staticFlag() = FALSE;
		aLine->virtualFlag() = FALSE;
		aLine->afxMsgFlag() = FALSE;
	}
	loadButtonState(&m_checkStaticCtrl,aLine->staticFlag());
	loadButtonState(&m_checkVirtualCtrl,aLine->virtualFlag());
	loadButtonState(&m_checkAfxmsgCtrl,aLine->afxMsgFlag());
	loadButtonState(&m_checkMfcvirtualCtrl,aLine->afxVirtualFlag());
	UpdateData(FALSE);
}

BOOL VCPPMethodPropGeneral::writeOptionsToClassTextLine()
{
	if (_currentLine == NIL) return FALSE;

	BOOL repaintFlag = FALSE;
	repaintFlag = writeButtonState(&m_checkInlineCtrl,_currentLine->inlineFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkConstCtrl,_currentLine->constFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkStaticCtrl,_currentLine->staticFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkVirtualCtrl,_currentLine->virtualFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkAfxmsgCtrl,_currentLine->afxMsgFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkMfcvirtualCtrl,_currentLine->afxVirtualFlag()) || repaintFlag;
	repaintFlag = writeVisibilityForMember(m_comboVisibility) || repaintFlag;
	return repaintFlag;
}


void VCPPMethodPropGeneral::OnCheckAfxmsg() 
{
	// TODO: Add your control notification handler code here
	if (m_checkAfxmsgCtrl.GetCheck() == 0) return;
	m_checkStaticCtrl.SetCheck(0);
	m_checkVirtualCtrl.SetCheck(0);	
	m_checkMfcvirtualCtrl.SetCheck(0);
}

void VCPPMethodPropGeneral::OnCheckStatic() 
{
	// TODO: Add your control notification handler code here
	if (m_checkStaticCtrl.GetCheck() == 0) return;
	m_checkVirtualCtrl.SetCheck(0);	
	m_checkAfxmsgCtrl.SetCheck(0);
	m_checkMfcvirtualCtrl.SetCheck(0);
}

void VCPPMethodPropGeneral::OnCheckVirtual() 
{
	// TODO: Add your control notification handler code here
	if (m_checkVirtualCtrl.GetCheck() == 0) return;
	m_checkStaticCtrl.SetCheck(0);
	m_checkAfxmsgCtrl.SetCheck(0);
	m_checkMfcvirtualCtrl.SetCheck(0);
}

void VCPPMethodPropGeneral::OnCheckMfcvirtual() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkMfcvirtualCtrl.GetCheck() == 0) return;
	m_checkVirtualCtrl.SetCheck(0);	
	m_checkStaticCtrl.SetCheck(0);
	m_checkAfxmsgCtrl.SetCheck(0);
}
