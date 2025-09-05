// VCPPClassPropGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "VCPPClassPropGeneral.h"
#include "ClassContent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VCPPClassPropGeneral dialog
IMPLEMENT_DYNAMIC(VCPPClassPropGeneral, MemberOptionDlg)

VCPPClassPropGeneral::VCPPClassPropGeneral(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(VCPPClassPropGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(VCPPClassPropGeneral)
	m_comboStereotype = _T("");
	m_editResourceID = _T("");
	m_editInnerClassOf = _T("");
	//}}AFX_DATA_INIT
}


void VCPPClassPropGeneral::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VCPPClassPropGeneral)
	DDX_Control(pDX, IDC_EDIT_RESOURCE_ID, m_editResourceIDCtrl);
	DDX_Control(pDX, IDC_CHECK_DYNCREATE, m_checkDyncreateCtrl);
	DDX_Control(pDX, IDC_CHECK_DYNAMIC, m_checkDynamicCtrl);
	DDX_Control(pDX, IDC_CHECK_SERIALIZABLE, m_checkSerializableCtrl);
	DDX_Control(pDX, IDC_CHECK_MFC_CLASS, m_checkMFCClassCtrl);
	DDX_Control(pDX, IDC_CHECK_CONCRETE, m_checkConcreteCtrl);
	DDX_Control(pDX, IDC_CHECK_ABSTRACT, m_checkAbstractCtrl);
	DDX_CBString(pDX, IDC_COMBO_STEREOTYPE, m_comboStereotype);
	DDX_Text(pDX, IDC_EDIT_RESOURCE_ID, m_editResourceID);
	DDX_Text(pDX, IDC_EDIT_INNER_CLASS_OF, m_editInnerClassOf);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VCPPClassPropGeneral, MemberOptionDlg)
	//{{AFX_MSG_MAP(VCPPClassPropGeneral)
	ON_BN_CLICKED(IDC_CHECK_ABSTRACT, OnCheckAbstract)
	ON_BN_CLICKED(IDC_CHECK_CONCRETE, OnCheckConcrete)
	ON_BN_CLICKED(IDC_CHECK_DYNAMIC, OnCheckDynamic)
	ON_BN_CLICKED(IDC_CHECK_DYNCREATE, OnCheckDyncreate)
	ON_BN_CLICKED(IDC_CHECK_SERIALIZABLE, OnCheckSerializable)
	ON_BN_CLICKED(IDC_CHECK_MFC_CLASS, OnCheckMfcClass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VCPPClassPropGeneral message handlers

void VCPPClassPropGeneral::clearContents()
{
	MemberOptionDlg::clearContents();
	m_checkConcreteCtrl.SetCheck(0);
	m_checkAbstractCtrl.SetCheck(0);
	m_checkMFCClassCtrl.SetCheck(0);
	m_checkDyncreateCtrl.SetCheck(0);
	m_checkDynamicCtrl.SetCheck(0);
	m_checkSerializableCtrl.SetCheck(0);
	m_comboStereotype = _T("");
	m_editResourceID = _T("");
	UpdateData(FALSE);
}

void VCPPClassPropGeneral::setMFCClassCtrl()
{
	m_checkMFCClassCtrl.SetCheck(1);
	m_editResourceIDCtrl.EnableWindow(TRUE);
}

void VCPPClassPropGeneral::loadResourceID(CString &resourceID)
{
	resourceID = _classContent->resourceID();
}

BOOL VCPPClassPropGeneral::writeResourceID(CString &resourceID)
{
	if (_classContent == NIL) return FALSE;

	CString id = _classContent->resourceID();
	if (id.CompareNoCase(resourceID) == 0) {
		return FALSE;
	}

	_classContent->resourceID() = resourceID;
	return TRUE;
}

void VCPPClassPropGeneral::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);
	_classContent = aContent;

	unsigned int employeedMap = _classContent->employeedMap();
	if (employeedMap != 0) {
		_classContent->mfcClassFlag() = TRUE;
	}

	loadStereotype(m_comboStereotype);
	loadInnerClassOf(m_editInnerClassOf);
	loadResourceID(m_editResourceID);
	loadButtonState(&m_checkConcreteCtrl,!(aContent->abstractFlag()));
	loadButtonState(&m_checkAbstractCtrl,aContent->abstractFlag());
	loadButtonState(&m_checkMFCClassCtrl,aContent->mfcClassFlag());
	loadButtonState(&m_checkDyncreateCtrl,aContent->dyncreateFlag());
	loadButtonState(&m_checkDynamicCtrl,aContent->dynamicFlag());
	loadButtonState(&m_checkSerializableCtrl,aContent->serializableFlag());
	UpdateData(FALSE);

	if (_classContent->mfcClassFlag() == TRUE) {
		m_editResourceIDCtrl.EnableWindow(TRUE);
	} else {
		m_editResourceIDCtrl.EnableWindow(FALSE);
	}
}

BOOL VCPPClassPropGeneral::writeOptionsToClassTextLine()
{
	if (_classContent == NIL) return FALSE;

	BOOL repaintFlag = FALSE;
	repaintFlag = writeStereotype(m_comboStereotype) || repaintFlag;
	repaintFlag = writeInnerClassOf(m_editInnerClassOf) || repaintFlag;
	repaintFlag = writeResourceID(m_editResourceID) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkAbstractCtrl,_classContent->abstractFlag()) || repaintFlag;
	repaintFlag = writeButtonState(&m_checkMFCClassCtrl,_classContent->mfcClassFlag()) || repaintFlag;
	unsigned int employeedMap = _classContent->employeedMap();
	if (employeedMap != 0) {
		_classContent->mfcClassFlag() = TRUE;
	}

	if (_classContent->dyncreateFlag() == FALSE && 
		m_checkDyncreateCtrl.GetCheck() != 0) {
		BOOL inserted = _classContent->tryToInsertDefaultConstructor();
		repaintFlag = inserted || repaintFlag;
		if (inserted)
			setModifiedFlag(TRUE);
	}
	repaintFlag = writeButtonState(&m_checkDyncreateCtrl,_classContent->dyncreateFlag()) || repaintFlag;
	if (_classContent->dynamicFlag() == FALSE && 
		m_checkDynamicCtrl.GetCheck() != 0) {
		BOOL inserted = _classContent->tryToInsertDefaultConstructor();
		repaintFlag = inserted || repaintFlag;
		if (inserted)
			setModifiedFlag(TRUE);
	}
	repaintFlag = writeButtonState(&m_checkDynamicCtrl,_classContent->dynamicFlag()) || repaintFlag;
	if (_classContent->serializableFlag() == FALSE && 
		m_checkSerializableCtrl.GetCheck() != 0) {
		BOOL inserted = _classContent->tryToInsertSerializationFunction();
		repaintFlag = inserted || repaintFlag;
		if (inserted)
			setModifiedFlag(TRUE);
	}
	// 이 순서 중요함 ... if 문 다음에 ...
	repaintFlag = writeButtonState(&m_checkSerializableCtrl,_classContent->serializableFlag()) || repaintFlag;
	return repaintFlag;
}

void VCPPClassPropGeneral::OnCheckAbstract() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkAbstractCtrl.GetCheck() == 0) return;
	m_checkConcreteCtrl.SetCheck(0);
}

void VCPPClassPropGeneral::OnCheckConcrete() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkConcreteCtrl.GetCheck() == 0) return;
	m_checkAbstractCtrl.SetCheck(0);
}

void VCPPClassPropGeneral::OnCheckDynamic() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkDynamicCtrl.GetCheck() == 0) return;
	m_checkDyncreateCtrl.SetCheck(0);
	m_checkSerializableCtrl.SetCheck(0);	
}

void VCPPClassPropGeneral::OnCheckDyncreate() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkDyncreateCtrl.GetCheck() == 0) return;
	m_checkDynamicCtrl.SetCheck(0);
	m_checkSerializableCtrl.SetCheck(0);	
}

void VCPPClassPropGeneral::OnCheckSerializable() 
{
	// TODO: Add your control notification handler code here
	
	if (m_checkSerializableCtrl.GetCheck() == 0) return;
	m_checkDyncreateCtrl.SetCheck(0);
	m_checkDynamicCtrl.SetCheck(0);	
}

BOOL VCPPClassPropGeneral::OnInitDialog() 
{
	MemberOptionDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_editResourceIDCtrl.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void VCPPClassPropGeneral::OnCheckMfcClass() 
{
	// TODO: Add your control notification handler code here
	if (m_checkMFCClassCtrl.GetCheck() == 0) {
		m_editResourceIDCtrl.EnableWindow(FALSE);
	} else {
		m_editResourceIDCtrl.EnableWindow(TRUE);
	}
}
