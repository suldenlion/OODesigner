// DataMembersOption.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "DataMembersOption.h"
#include "ClassTextLine.h"
#include "ClassContent.h"
#include "Text.h"
#include "ClassPropDlg.h"
#include "CMainFrame.h"
#include "MemberPropDlg.h"
#include "TextContent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DataMembersOption dialog


DataMembersOption::DataMembersOption(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(DataMembersOption::IDD, pParent)
{
	_iSelectedItem = -1;
	_newButtonPressed = FALSE;
	//{{AFX_DATA_INIT(DataMembersOption)
	m_editDataMember = _T("");
	//}}AFX_DATA_INIT
}


void DataMembersOption::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DataMembersOption)
	DDX_Control(pDX, IDC_EDIT_DATA_MEMBER, m_editDataMemberCtrl);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_buttonNewCtrl);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_buttonUpdateCtrl);
	DDX_Control(pDX, IDC_LIST_DATA_MEMBERS, m_listDataMembers);
	DDX_Text(pDX, IDC_EDIT_DATA_MEMBER, m_editDataMember);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DataMembersOption, MemberOptionDlg)
	//{{AFX_MSG_MAP(DataMembersOption)
	ON_EN_CHANGE(IDC_EDIT_DATA_MEMBER, OnChangeEditDataMember)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DATA_MEMBERS, OnClickListDataMembers)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DATA_MEMBERS, OnDblclkListDataMembers)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DataMembersOption message handlers

BOOL DataMembersOption::OnInitDialog() 
{
	MemberOptionDlg::OnInitDialog();
	// TODO: Add extra initialization here

	static LPCTSTR szTabName[] = { _T(" Visibility "), _T(" Name "), _T(" Type "), _T(" Default Value ") };

	LV_COLUMN columnValue;
	int i = 0;
	for(i = 0; i < 4; i++) {
		columnValue.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		columnValue.fmt = LVCFMT_LEFT;
		columnValue.pszText = (char *)szTabName[i];
		columnValue.iSubItem = i;
		columnValue.cx = 100;
		m_listDataMembers.InsertColumn(i,&columnValue);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DataMembersOption::clearContents()
{
	MemberOptionDlg::clearContents();
	m_listDataMembers.DeleteAllItems();
	_newButtonPressed = FALSE;
	m_buttonNewCtrl.EnableWindow(TRUE);
}

void DataMembersOption::loadClassTextLine(int i,ClassTextLine *pLine)
{
	LV_ITEM itemValue;
	itemValue.mask = LVIF_TEXT;

	itemValue.iItem = i;
	itemValue.iSubItem = 0;
	int vis = pLine->visibility();
	char buffer[BUFSIZ];
	if (vis == PUBLIC_ID) {
		strcpy_s(buffer,BUFSIZ,"public");
	} else if (vis == PROTECTED_ID) {
		strcpy_s(buffer,BUFSIZ,"protected");
	} else if (vis == PRIVATE_ID) {
		strcpy_s(buffer,BUFSIZ,"private");
	} else {
		strcpy_s(buffer,BUFSIZ,"default");
	}
	itemValue.pszText = buffer;
	m_listDataMembers.InsertItem(&itemValue);
	
	itemValue.iSubItem = 1;
	strcpy_s(buffer,BUFSIZ,pLine->name());
	itemValue.pszText = buffer;
	m_listDataMembers.SetItem(&itemValue);
	
	itemValue.iSubItem = 2;
	strcpy_s(buffer,BUFSIZ,pLine->type());
	itemValue.pszText = buffer;
	m_listDataMembers.SetItem(&itemValue);

	itemValue.iSubItem = 3;
	buffer[0] = '\0';
	if (pLine->defaultValue().IsEmpty() == FALSE) {
		strcpy_s(buffer,BUFSIZ,pLine->defaultValue().GetHead());
	}
	itemValue.pszText = buffer;
	m_listDataMembers.SetItem(&itemValue);
}

void DataMembersOption::reloadClassMembers()
{
	m_editDataMember = "";
	UpdateData(FALSE);
	if (_classContent == NIL) return;

	m_listDataMembers.DeleteAllItems();
	int nData = _classContent->nOfDataMembers();
	if (nData == 0) return;
	for (int i = 0; i < nData; i++) {
		ClassTextLine *pLine = _classContent->getDataMemberLine(i);
		if (pLine == NIL) break;
		loadClassTextLine(i,pLine);
	}
	ClassTextLine *firstLine = _classContent->getDataMemberLine(0);
	m_editDataMember = firstLine->ptrAt(0);
	_iSelectedItem = 0;
	UpdateData(FALSE);
	m_buttonUpdateCtrl.EnableWindow(FALSE);
}

void DataMembersOption::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	setCurrentLine(aLine);
	_classContent = aContent;
	releaseNewButton();

	reloadClassMembers();
	m_listDataMembers.SetFocus();
}

BOOL DataMembersOption::writeOptionsToClassTextLine()
{
	return FALSE;
}


void DataMembersOption::OnChangeEditDataMember() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the MemberOptionDlg::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	m_buttonUpdateCtrl.EnableWindow(TRUE);
}

void DataMembersOption::setEditField(NMHDR* pNMHDR)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iItem = pNMListView->iItem;
	if (iItem < 0) return;
	if (iItem >= m_listDataMembers.GetItemCount()) return;
	ClassTextLine *theLine = _classContent->getDataMemberLine(iItem);
	if (theLine == NIL) return;
	_iSelectedItem = iItem;
	m_editDataMember = theLine->ptrAt(0);
	UpdateData(FALSE);
	m_buttonUpdateCtrl.EnableWindow(FALSE);
}

void DataMembersOption::OnClickListDataMembers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	releaseNewButton();
	setEditField(pNMHDR);
	*pResult = 0;
}

void DataMembersOption::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	m_buttonUpdateCtrl.EnableWindow(FALSE);
	UpdateData(TRUE);
	char buffer[BUFSIZ];
	int n = Text::strcpyCompact(buffer,m_editDataMember,BUFSIZ);
	if (n == 0) {
		OnButtonDelete();
		return;
	}
	if (_iSelectedItem < 0) return;
	if (_iSelectedItem > m_listDataMembers.GetItemCount()) {
		releaseNewButton();
		return;
	} else if (_iSelectedItem == m_listDataMembers.GetItemCount() && 
		_newButtonPressed == FALSE) {
		releaseNewButton();
		return;
	} else if (_iSelectedItem == m_listDataMembers.GetItemCount() && 
		_newButtonPressed == TRUE &&
		_classContent->nOfDataMembers() > 0) {
		ClassTextLine *aLine = new ClassTextLine();
		_classContent->varContent()->insertAt(aLine,_iSelectedItem);
	}
	releaseNewButton(); // 이 함수에서 _newButtonPressed 가 reset됨 
	ClassTextLine *theLine = _classContent->getDataMemberLine(_iSelectedItem);
	if (theLine == NIL) return;
	theLine->setString(m_editDataMember);
	theLine->parseAsDataMember();
	m_listDataMembers.DeleteItem(_iSelectedItem);
	loadClassTextLine(_iSelectedItem,theLine);
	refreshAllViews();
}

void DataMembersOption::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	
	releaseNewButton();
	if (_iSelectedItem < 0) return;
	if (_iSelectedItem >= m_listDataMembers.GetItemCount()) {
		_iSelectedItem = m_listDataMembers.GetItemCount() - 1;
		if (_iSelectedItem >= 0) {
			ClassTextLine *theLine = _classContent->getDataMemberLine(_iSelectedItem);
			m_editDataMember = theLine->ptrAt(0);
			UpdateData(FALSE);
		} else {
			m_editDataMember = "";
			UpdateData(FALSE);
		}
		return;
	}
	m_listDataMembers.DeleteItem(_iSelectedItem);
	_classContent->deleteDataMember(_iSelectedItem);
	_iSelectedItem--;
	if (_iSelectedItem == -1 &&
		m_listDataMembers.GetItemCount() > 0) {
		_iSelectedItem = 0;
	}
	if (_iSelectedItem >= 0) {
		ClassTextLine *theLine = _classContent->getDataMemberLine(_iSelectedItem);
		m_editDataMember = theLine->ptrAt(0);
		UpdateData(FALSE);
	} else {
		m_editDataMember = "";
		UpdateData(FALSE);
	}
	refreshAllViews();
}


void DataMembersOption::OnDblclkListDataMembers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	releaseNewButton();
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iItem = pNMListView->iItem;
	if (iItem < 0) return;
	if (iItem >= m_listDataMembers.GetItemCount()) return;
	ClassTextLine *theLine = _classContent->getDataMemberLine(iItem);
	if (theLine == NIL) return;
	_iSelectedItem = iItem;
	MemberPropDlg *memberDlg = theAppPtr->getActiveVarPropDlg();
	if (memberDlg == NIL) return;
	CWnd *pParent = GetParent();
	if (!pParent->IsKindOf(RUNTIME_CLASS(ClassPropDlg))) return;
	ClassPropDlg *parentDlg = (ClassPropDlg*)pParent;
	CString className = parentDlg->className();
	CString packageName = parentDlg->packageName();
	COODView *theView = parentDlg->pView();
	if (theView == NIL) return;
	if ((memberDlg->GetStyle() & WS_VISIBLE) == 0) {
		memberDlg->ShowWindow(SW_SHOW);
	}
	memberDlg->loadFromClassTextLine(theView,theLine,_iSelectedItem,_classContent,className,packageName);
	*pResult = 0;
}

void DataMembersOption::OnButtonNew() 
{
	// TODO: Add your control notification handler code here
	_newButtonPressed = TRUE;
	_iSelectedItem = m_listDataMembers.GetItemCount();
	m_editDataMember = "";
	UpdateData(FALSE);
	m_buttonNewCtrl.EnableWindow(FALSE);
	m_editDataMemberCtrl.SetFocus();
}

void DataMembersOption::releaseNewButton()
{
	if (_classContent->getInterfaceFlag() == TRUE) {
		m_buttonNewCtrl.EnableWindow(FALSE);
		return;
	}
	_newButtonPressed = FALSE;
	m_buttonNewCtrl.EnableWindow(TRUE);
}
