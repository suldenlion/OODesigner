// CSharpClassPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CSharpClassPropGeneral.h"
#include "ClassContent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSharpClassPropGeneral dialog


CSharpClassPropGeneral::CSharpClassPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(CSharpClassPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSharpClassPropGeneral)
	m_comboStereotype = _T("");
	m_comboVisibility = _T("");
	m_editInnerClassOf = _T("");
	//}}AFX_DATA_INIT
}


void CSharpClassPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSharpClassPropGeneral)
	DDX_Control(pDX, IDC_CHECK_CONCRETE, m_checkConcreteCtrl);
	DDX_Control(pDX, IDC_CHECK_ABSTRACT, m_checkAbstractCtrl);
	DDX_CBString(pDX, IDC_COMBO_STEREOTYPE, m_comboStereotype);
	DDX_CBString(pDX, IDC_COMBO_VISIBILITY, m_comboVisibility);
	DDX_Text(pDX, IDC_EDIT_INNER_CLASS_OF, m_editInnerClassOf);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSharpClassPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(CSharpClassPropGeneral)
	ON_BN_CLICKED(IDC_CHECK_ABSTRACT, OnCheckAbstract)
	ON_BN_CLICKED(IDC_CHECK_CONCRETE, OnCheckConcrete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSharpClassPropGeneral message handlers

void CSharpClassPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
	m_checkConcreteCtrl.SetCheck(0);
	m_checkAbstractCtrl.SetCheck(0);
	m_comboStereotype = _T("");
	m_comboVisibility = _T("");
	m_editInnerClassOf = _T("");
	UpdateData(FALSE);
}

void CSharpClassPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);
	_classContent = aContent;

	loadVisibilityForClass(m_comboVisibility);
	loadStereotype(m_comboStereotype);
	loadInnerClassOf(m_editInnerClassOf);
	loadButtonState(&m_checkConcreteCtrl,!(aContent->abstractFlag()));
	loadButtonState(&m_checkAbstractCtrl,aContent->abstractFlag());
	UpdateData(FALSE);
}

BOOL CSharpClassPropGeneral::writeOptionsToClassTextLine()
{
	if (_classContent == NIL) return FALSE;

	BOOL repaintFlag = FALSE;
	repaintFlag = writeStereotype(m_comboStereotype) || repaintFlag;
	repaintFlag = writeInnerClassOf(m_editInnerClassOf) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkAbstractCtrl,_classContent->abstractFlag()) || repaintFlag;
	repaintFlag = writeVisibilityForClass(m_comboVisibility) || repaintFlag;
	return repaintFlag;
}


void CSharpClassPropGeneral::OnCheckAbstract() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkAbstractCtrl.GetCheck() == 0) return;
	m_checkConcreteCtrl.SetCheck(0);
}

void CSharpClassPropGeneral::OnCheckConcrete() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkConcreteCtrl.GetCheck() == 0) return;
	m_checkAbstractCtrl.SetCheck(0);
}
