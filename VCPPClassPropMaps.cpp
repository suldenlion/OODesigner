// VCPPClassPropMaps.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "VCPPClassPropMaps.h"
#include "VCPPMapEditor.h"
#include "ClassContent.h"
#include "ClassPropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VCPPClassPropMaps dialog
IMPLEMENT_DYNAMIC(VCPPClassPropMaps,MemberOptionDlg)

VCPPClassPropMaps::VCPPClassPropMaps(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(VCPPClassPropMaps::IDD, pParent)
{
	//{{AFX_DATA_INIT(VCPPClassPropMaps)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void VCPPClassPropMaps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VCPPClassPropMaps)
	DDX_Control(pDX, IDC_LIST_SYSTEM_MAPS, m_listSystemMapsCtrl);
	DDX_Control(pDX, IDC_LIST_CLASS_MAPS, m_listClassMapsCtrl);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAddCtrl);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_buttonEditCtrl);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDeleteCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VCPPClassPropMaps, CDialog)
	//{{AFX_MSG_MAP(VCPPClassPropMaps)
	ON_LBN_SETFOCUS(IDC_LIST_CLASS_MAPS, OnSetfocusListClassMaps)
	ON_LBN_SETFOCUS(IDC_LIST_SYSTEM_MAPS, OnSetfocusListSystemMaps)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_LBN_DBLCLK(IDC_LIST_CLASS_MAPS, OnDblclkListClassMaps)
	ON_LBN_DBLCLK(IDC_LIST_SYSTEM_MAPS, OnDblclkListSystemMaps)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VCPPClassPropMaps message handlers

void VCPPClassPropMaps::clearContents()
{
	m_listClassMapsCtrl.ResetContent();
	MemberOptionDlg::clearContents();
}

void VCPPClassPropMaps::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	_classContent = aContent;

	unsigned int employeedMap = _classContent->employeedMap();
	if (employeedMap & KTG_MESSAGEMAP) {
		m_listClassMapsCtrl.AddString("MESSAGE_MAP");
	} 
	if (employeedMap & KTG_INTERFACEMAP) {
		m_listClassMapsCtrl.AddString("INTERFACE_MAP");
	} 
	if (employeedMap & KTG_DISPATCHMAP) {
		m_listClassMapsCtrl.AddString("DISPATCH_MAP");
	} 
	if (employeedMap & KTG_OLECMDMAP) {
		m_listClassMapsCtrl.AddString("OLECMD_MAP");
	} 
	if (employeedMap & KTG_CONNECTIONMAP) {
		m_listClassMapsCtrl.AddString("CONNECTION_MAP");
	} 
	if (employeedMap & KTG_EVENTSINKMAP) {
		m_listClassMapsCtrl.AddString("EVENTSINK_MAP");
	} 
	if (employeedMap & KTG_UNSPECIFIEDMAP) {
		m_listClassMapsCtrl.AddString("unspecified maps");
	}
	m_listSystemMapsCtrl.SetCurSel(0);

	if (m_listClassMapsCtrl.GetCount() > 0) {
		m_listClassMapsCtrl.SetFocus();
		m_listClassMapsCtrl.SetCurSel(0);
	}
}

BOOL VCPPClassPropMaps::writeOptionsToClassTextLine()
{
	return FALSE;
}

BOOL VCPPClassPropMaps::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listSystemMapsCtrl.AddString("MESSAGE_MAP");
	m_listSystemMapsCtrl.AddString("INTERFACE_MAP");
	m_listSystemMapsCtrl.AddString("DISPATCH_MAP");
	m_listSystemMapsCtrl.AddString("OLECMD_MAP");
	m_listSystemMapsCtrl.AddString("CONNECTION_MAP");
	m_listSystemMapsCtrl.AddString("EVENTSINK_MAP");
	m_listSystemMapsCtrl.AddString("unspecified maps");
	m_listSystemMapsCtrl.SetCurSel(0);
	m_listClassMapsCtrl.SetCurSel(0);
	m_buttonAddCtrl.EnableWindow(FALSE);
	m_buttonDeleteCtrl.EnableWindow(FALSE);
	m_buttonEditCtrl.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void VCPPClassPropMaps::OnSetfocusListClassMaps() 
{
	// TODO: Add your control notification handler code here
	m_buttonAddCtrl.EnableWindow(FALSE);
	m_buttonDeleteCtrl.EnableWindow(TRUE);
	m_buttonEditCtrl.EnableWindow(TRUE);	
}

void VCPPClassPropMaps::OnSetfocusListSystemMaps() 
{
	// TODO: Add your control notification handler code here
	m_buttonAddCtrl.EnableWindow(TRUE);
	m_buttonDeleteCtrl.EnableWindow(FALSE);
	m_buttonEditCtrl.EnableWindow(FALSE);	
}

void VCPPClassPropMaps::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	char buffer[BUFSIZ];

	buffer[0] = '\0';
	int iSelectedItem = m_listSystemMapsCtrl.GetCurSel();
	int n = m_listSystemMapsCtrl.GetText(iSelectedItem,buffer);
	if (n == LB_ERR || n < 0) return;
	if (m_listClassMapsCtrl.FindString(-1,buffer) != LB_ERR) {
		WarningMsg("The map is already registered.");
		m_listSystemMapsCtrl.SetFocus();
		return;
	}
	m_listClassMapsCtrl.AddString(buffer);
	m_listClassMapsCtrl.SetFocus();
	int i = m_listClassMapsCtrl.GetCount() - 1;
	m_listClassMapsCtrl.SetCurSel(i);

	CString mapName = buffer;
	if (mapName.CompareNoCase("MESSAGE_MAP") == 0) {
		_classContent->setEmployeedMap(KTG_MESSAGEMAP);
	} else if (mapName.CompareNoCase("INTERFACE_MAP") == 0) {
		_classContent->setEmployeedMap(KTG_INTERFACEMAP);
	} else if (mapName.CompareNoCase("DISPATCH_MAP") == 0) {
		_classContent->setEmployeedMap(KTG_DISPATCHMAP);
	} else if (mapName.CompareNoCase("OLECMD_MAP") == 0) {
		_classContent->setEmployeedMap(KTG_OLECMDMAP);
	} else if (mapName.CompareNoCase("CONNECTION_MAP") == 0) {
		_classContent->setEmployeedMap(KTG_CONNECTIONMAP);
	} else if (mapName.CompareNoCase("EVENTSINK_MAP") == 0) {
		_classContent->setEmployeedMap(KTG_EVENTSINKMAP);
	} else {
		_classContent->setEmployeedMap(KTG_UNSPECIFIEDMAP);
	}

	_classContent->setMfcClassFlag();
	CWnd *pParent = GetParent();
	if (pParent == NULL) return;
	if (!pParent->IsKindOf(RUNTIME_CLASS(ClassPropDlg))) return;
	ClassPropDlg *parentDlg = (ClassPropDlg *)pParent;
	parentDlg->setMfcClassFlag();
}

void VCPPClassPropMaps::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	char buffer[BUFSIZ];

	buffer[0] = '\0';
	int iSelectedItem = m_listClassMapsCtrl.GetCurSel();
	int n = m_listClassMapsCtrl.GetText(iSelectedItem,buffer);
	if (n == LB_ERR || n < 0) return;
	UINT ans = YesNoMsg("Are you sure to delete the map ?");
	if (ans != IDYES) return;
	m_listClassMapsCtrl.DeleteString(iSelectedItem);
	m_listClassMapsCtrl.SetFocus();
	m_listClassMapsCtrl.SetCurSel(0);

	CString mapName = buffer;
	if (mapName.CompareNoCase("MESSAGE_MAP") == 0) {
		_classContent->resetEmployeedMap(KTG_MESSAGEMAP);
		_classContent->messageMap()->RemoveAll();
	} else if (mapName.CompareNoCase("INTERFACE_MAP") == 0) {
		_classContent->resetEmployeedMap(KTG_INTERFACEMAP);
		_classContent->interfaceMap()->RemoveAll();
	} else if (mapName.CompareNoCase("DISPATCH_MAP") == 0) {
		_classContent->resetEmployeedMap(KTG_DISPATCHMAP);
		_classContent->dispatchMap()->RemoveAll();
	} else if (mapName.CompareNoCase("OLECMD_MAP") == 0) {
		_classContent->resetEmployeedMap(KTG_OLECMDMAP);
		_classContent->olecmdMap()->RemoveAll();
	} else if (mapName.CompareNoCase("CONNECTION_MAP") == 0) {
		_classContent->resetEmployeedMap(KTG_CONNECTIONMAP);
		_classContent->connectionMap()->RemoveAll();
	} else if (mapName.CompareNoCase("EVENTSINK_MAP") == 0) {
		_classContent->resetEmployeedMap(KTG_EVENTSINKMAP);
		_classContent->eventsinkMap()->RemoveAll();
	} else if (mapName.CompareNoCase("unspecified maps") == 0) {
		_classContent->resetEmployeedMap(KTG_UNSPECIFIEDMAP);
		_classContent->unspecifiedMaps()->RemoveAll();
	}
}

void VCPPClassPropMaps::OnButtonEdit() 
{
	// TODO: Add your control notification handler code here
	char buffer[BUFSIZ];

	buffer[0] = '\0';
	int iSelectedItem = m_listClassMapsCtrl.GetCurSel();
	int n = m_listClassMapsCtrl.GetText(iSelectedItem,buffer);
	if (n == LB_ERR || n < 0) return;
	CString mapName = buffer;
	VCPPMapEditor mapEditor(mapName,_classContent);
	mapEditor.DoModal();
}

void VCPPClassPropMaps::OnDblclkListClassMaps() 
{
	// TODO: Add your control notification handler code here
	OnButtonEdit();
}

void VCPPClassPropMaps::OnDblclkListSystemMaps() 
{
	// TODO: Add your control notification handler code here
	OnButtonAdd();
}
