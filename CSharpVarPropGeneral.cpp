// CSharpVarPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CSharpVarPropGeneral.h"
#include "KtgMacro.h"
#include "ClassTextLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSharpVarPropGeneral dialog


CSharpVarPropGeneral::CSharpVarPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(CSharpVarPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSharpVarPropGeneral)
	m_comboVisibility = _T("");
	//}}AFX_DATA_INIT
}


void CSharpVarPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSharpVarPropGeneral)
	DDX_Control(pDX, IDC_STATIC_EQUAL, m_staticEqualCtrl);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_VALUE, m_editDefaultValueCtrl);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboTypeCtrl);
	DDX_Control(pDX, IDC_CHECK_STATIC, m_checkStaticCtrl);
	DDX_Control(pDX, IDC_CHECK_READONLY, m_checkReadonlyCtrl);
	DDX_Control(pDX, IDC_CHECK_INTERNAL, m_checkInternalCtrl);
	DDX_CBString(pDX, IDC_COMBO_VISIBILITY, m_comboVisibility);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSharpVarPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(CSharpVarPropGeneral)
	ON_CBN_DROPDOWN(IDC_COMBO_TYPE, OnDropdownComboType)
	ON_CBN_EDITCHANGE(IDC_COMBO_TYPE, OnEditchangeComboType)
	ON_EN_CHANGE(IDC_EDIT_DEFAULT_VALUE, OnChangeEditDefaultValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSharpVarPropGeneral message handlers
void CSharpVarPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
	m_editDefaultValueCtrl.SetSel(0,-1);
	m_editDefaultValueCtrl.Clear();
}

void CSharpVarPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);

	loadVisibilityForMember(m_comboVisibility);
	loadType(&m_comboTypeCtrl,aLine->type());
	loadDefaultValue(&m_editDefaultValueCtrl,aLine->defaultValue());
	loadButtonState(&m_checkStaticCtrl,aLine->staticFlag());
	loadButtonState(&m_checkInternalCtrl,aLine->internalFlag());
	loadButtonState(&m_checkReadonlyCtrl,aLine->readonlyFlag());
	UpdateData(FALSE);
}

BOOL CSharpVarPropGeneral::writeOptionsToClassTextLine()
{
	if (_currentLine == NIL) return FALSE;

	writeType(&m_comboTypeCtrl,_currentLine->type());
	writeDefaultValue(&m_editDefaultValueCtrl,_currentLine->defaultValue());
	BOOL repaintFlag = FALSE;
	repaintFlag = writeButtonState(&m_checkStaticCtrl,_currentLine->staticFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkInternalCtrl,_currentLine->internalFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkReadonlyCtrl,_currentLine->readonlyFlag()) || repaintFlag;
	repaintFlag = writeVisibilityForMember(m_comboVisibility) || repaintFlag;
	return repaintFlag;
}

BOOL CSharpVarPropGeneral::OnInitDialog() 
{
	MemberOptionDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	RECT rect;
	m_staticEqualCtrl.GetWindowRect(&rect);
    m_staticEqualCtrl.SetWindowPos(NULL,rect.left,rect.top,rect.right-10,rect.bottom,SWP_NOMOVE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSharpVarPropGeneral::OnDropdownComboType() 
{
	// TODO: Add your control notification handler code here
	
	setModifiedFlag(TRUE);
}

void CSharpVarPropGeneral::OnEditchangeComboType() 
{
	// TODO: Add your control notification handler code here
	
	setModifiedFlag(TRUE);
}

void CSharpVarPropGeneral::OnChangeEditDefaultValue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
	setModifiedFlag(TRUE);
}
