// JavaClassPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "JavaClassPropGeneral.h"
#include "ClassContent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// JavaClassPropGeneral dialog


JavaClassPropGeneral::JavaClassPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(JavaClassPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(JavaClassPropGeneral)
	m_comboStereotype = _T("");
	m_comboVisibility = _T("");
	m_editInnerClassOf = _T("");
	//}}AFX_DATA_INIT
}


void JavaClassPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(JavaClassPropGeneral)
	DDX_Control(pDX, IDC_CHECK_STATIC, m_checkStaticCtrl);
	DDX_Control(pDX, IDC_CHECK_CONCRETE, m_checkConcreteCtrl);
	DDX_Control(pDX, IDC_CHECK_ABSTRACT, m_checkAbstractCtrl);
	DDX_CBString(pDX, IDC_COMBO_STEREOTYPE, m_comboStereotype);
	DDX_CBString(pDX, IDC_COMBO_VISIBILITY, m_comboVisibility);
	DDX_Text(pDX, IDC_EDIT_INNER_CLASS_OF, m_editInnerClassOf);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(JavaClassPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(JavaClassPropGeneral)
	ON_BN_CLICKED(IDC_CHECK_ABSTRACT, OnCheckAbstract)
	ON_BN_CLICKED(IDC_CHECK_CONCRETE, OnCheckConcrete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// JavaClassPropGeneral message handlers

void JavaClassPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
	m_checkConcreteCtrl.SetCheck(0);
	m_checkAbstractCtrl.SetCheck(0);
	m_checkStaticCtrl.SetCheck(0);
	m_comboStereotype = _T("");
	m_comboVisibility = _T("");
	m_editInnerClassOf = _T("");
	UpdateData(FALSE);
}

void JavaClassPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);
	_classContent = aContent;

	loadVisibilityForClass(m_comboVisibility);
	loadStereotype(m_comboStereotype);
	loadInnerClassOf(m_editInnerClassOf);
	loadButtonState(&m_checkConcreteCtrl,!(aContent->abstractFlag()));
	loadButtonState(&m_checkAbstractCtrl,aContent->abstractFlag());
	loadButtonState(&m_checkStaticCtrl,aContent->staticFlag());
	UpdateData(FALSE);
}

BOOL JavaClassPropGeneral::writeOptionsToClassTextLine()
{
	if (_classContent == NIL) return FALSE;

	BOOL repaintFlag = FALSE;
	repaintFlag = writeStereotype(m_comboStereotype) || repaintFlag;
	repaintFlag = writeInnerClassOf(m_editInnerClassOf) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkStaticCtrl,_classContent->staticFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkAbstractCtrl,_classContent->abstractFlag()) || repaintFlag;
	repaintFlag = writeVisibilityForClass(m_comboVisibility) || repaintFlag;
	return repaintFlag;
}

void JavaClassPropGeneral::OnCheckAbstract() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkAbstractCtrl.GetCheck() == 0) return;
	m_checkConcreteCtrl.SetCheck(0);
}

void JavaClassPropGeneral::OnCheckConcrete() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkConcreteCtrl.GetCheck() == 0) return;
	m_checkAbstractCtrl.SetCheck(0);
}

