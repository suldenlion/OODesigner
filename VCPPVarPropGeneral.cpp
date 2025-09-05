// VCPPVarPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "VCPPVarPropGeneral.h"
#include "KtgMacro.h"
#include "ClassTextLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VCPPVarPropGeneral dialog


VCPPVarPropGeneral::VCPPVarPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(VCPPVarPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(VCPPVarPropGeneral)
	m_comboVisibility = _T("");
	//}}AFX_DATA_INIT
}


void VCPPVarPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VCPPVarPropGeneral)
	DDX_Control(pDX, IDC_CHECK_AFXFIELD, m_checkAfxfieldCtrl);
	DDX_Control(pDX, IDC_CHECK_AFXDATA, m_checkAfxdataCtrl);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboTypeCtrl);
	DDX_Control(pDX, IDC_STATIC_EQUAL, m_staticEqualCtrl);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_VALUE, m_editDefaultValueCtrl);
	DDX_Control(pDX, IDC_CHECK_TRANSIENT, m_checkTransientCtrl);
	DDX_Control(pDX, IDC_CHECK_STATIC, m_checkStaticCtrl);
	DDX_CBString(pDX, IDC_COMBO_VISIBILITY, m_comboVisibility);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VCPPVarPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(VCPPVarPropGeneral)
	ON_CBN_DROPDOWN(IDC_COMBO_TYPE, OnDropdownComboType)
	ON_CBN_EDITCHANGE(IDC_COMBO_TYPE, OnEditchangeComboType)
	ON_EN_CHANGE(IDC_EDIT_DEFAULT_VALUE, OnChangeEditDefaultValue)
	ON_BN_CLICKED(IDC_CHECK_AFXDATA, OnCheckAfxdata)
	ON_BN_CLICKED(IDC_CHECK_AFXFIELD, OnCheckAfxfield)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VCPPVarPropGeneral message handlers

void VCPPVarPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
	m_editDefaultValueCtrl.SetSel(0,-1);
	m_editDefaultValueCtrl.Clear();
}

void VCPPVarPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);

	loadVisibilityForMember(m_comboVisibility);
	loadType(&m_comboTypeCtrl,aLine->type());
	loadDefaultValue(&m_editDefaultValueCtrl,aLine->defaultValue());
	loadButtonState(&m_checkStaticCtrl,aLine->staticFlag());
	loadButtonState(&m_checkTransientCtrl,aLine->transientFlag());
	if (aLine->afxDataFlag() == TRUE) {
		aLine->afxFieldFlag() = FALSE;
	} else if (aLine->afxFieldFlag() == TRUE) {
		aLine->afxDataFlag() = FALSE;
	}
	loadButtonState(&m_checkAfxdataCtrl,aLine->afxDataFlag());
	loadButtonState(&m_checkAfxfieldCtrl,aLine->afxFieldFlag());
	UpdateData(FALSE);
}

BOOL VCPPVarPropGeneral::writeOptionsToClassTextLine()
{
	if (_currentLine == NIL) return FALSE;

	writeType(&m_comboTypeCtrl,_currentLine->type());
	writeDefaultValue(&m_editDefaultValueCtrl,_currentLine->defaultValue());
	BOOL repaintFlag = FALSE;
	repaintFlag = writeButtonState(&m_checkStaticCtrl,_currentLine->staticFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkTransientCtrl,_currentLine->transientFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkAfxdataCtrl,_currentLine->afxDataFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkAfxfieldCtrl,_currentLine->afxFieldFlag()) || repaintFlag;
	repaintFlag = writeVisibilityForMember(m_comboVisibility) || repaintFlag;
	return repaintFlag;
}

BOOL VCPPVarPropGeneral::OnInitDialog() 
{
	MemberOptionDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	RECT rect;
	m_staticEqualCtrl.GetWindowRect(&rect);
    m_staticEqualCtrl.SetWindowPos(NULL,rect.left,rect.top,rect.right-10,rect.bottom,SWP_NOMOVE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void VCPPVarPropGeneral::OnDropdownComboType() 
{
	// TODO: Add your control notification handler code here
	
	setModifiedFlag(TRUE);
}

void VCPPVarPropGeneral::OnEditchangeComboType() 
{
	// TODO: Add your control notification handler code here
	
	setModifiedFlag(TRUE);
}

void VCPPVarPropGeneral::OnChangeEditDefaultValue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
	setModifiedFlag(TRUE);
}

void VCPPVarPropGeneral::OnCheckAfxdata() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkAfxdataCtrl.GetCheck() == 0) return;
	m_checkAfxfieldCtrl.SetCheck(0);	
}

void VCPPVarPropGeneral::OnCheckAfxfield() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkAfxfieldCtrl.GetCheck() == 0) return;
	m_checkAfxdataCtrl.SetCheck(0);	
}
