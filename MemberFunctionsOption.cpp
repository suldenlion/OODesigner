// MemberFunctionsOption.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "MemberFunctionsOption.h"
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
// MemberFunctionsOption dialog


MemberFunctionsOption::MemberFunctionsOption(CWnd* pParent /*=NULL*/)
	: MemberOptionDlg(MemberFunctionsOption::IDD, pParent)
{
	_iSelectedItem = -1;
	_newButtonPressed = FALSE;
	//{{AFX_DATA_INIT(MemberFunctionsOption)
	m_editMemberFunction = _T("");
	//}}AFX_DATA_INIT
}


void MemberFunctionsOption::DoDataExchange(CDataExchange* pDX)
{
	MemberOptionDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MemberFunctionsOption)
	DDX_Control(pDX, IDC_LIST_MEMBER_FUNCTIONS, m_listMemberFunctions);
	DDX_Control(pDX, IDC_EDIT_MEMBER_FUNCTION, m_editMemberFunctionCtrl);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_buttonUpdateCtrl);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_buttonNewCtrl);
	DDX_Text(pDX, IDC_EDIT_MEMBER_FUNCTION, m_editMemberFunction);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MemberFunctionsOption, MemberOptionDlg)
	//{{AFX_MSG_MAP(MemberFunctionsOption)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEMBER_FUNCTIONS, OnClickListMemberFunctions)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MEMBER_FUNCTIONS, OnDblclkListMemberFunctions)
	ON_EN_CHANGE(IDC_EDIT_MEMBER_FUNCTION, OnChangeEditMemberFunction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MemberFunctionsOption message handlers

void MemberFunctionsOption::clearContents()
{
	MemberOptionDlg::clearContents();
	m_listMemberFunctions.DeleteAllItems();
	releaseNewButton();
}

void MemberFunctionsOption::loadClassTextLine(int i,ClassTextLine *pLine)
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
	m_listMemberFunctions.InsertItem(&itemValue);
	
	itemValue.iSubItem = 1;
	strcpy_s(buffer,BUFSIZ,pLine->type());
	itemValue.pszText = buffer;
	m_listMemberFunctions.SetItem(&itemValue);
	
	itemValue.iSubItem = 2;
	CString str;
	pLine->getMemberBrowserString(str);
	strcpy_s(buffer,BUFSIZ,str);
	itemValue.pszText = buffer;
	m_listMemberFunctions.SetItem(&itemValue);
}

void MemberFunctionsOption::reloadClassMembers()
{
	m_editMemberFunction = "";
	UpdateData(FALSE);
	if (_classContent == NIL) return;

	m_listMemberFunctions.DeleteAllItems();
	int nData = _classContent->nOfMemberFunctions();
	if (nData == 0) return;
	for (int i = 0; i < nData; i++) {
		ClassTextLine *pLine = _classContent->getMemberFunctionLine(i);
		if (pLine == NIL) break;
		loadClassTextLine(i,pLine);
	}
	ClassTextLine *firstLine = _classContent->getMemberFunctionLine(0);
	m_editMemberFunction = firstLine->ptrAt(0);
	_iSelectedItem = 0;
	UpdateData(FALSE);
	m_buttonUpdateCtrl.EnableWindow(FALSE);
}

void MemberFunctionsOption::loadFromClassTextLine(ClassContent *aContent,ClassTextLine *aLine,CString &className,CString &languageName)
{
	releaseNewButton();
	setCurrentLine(aLine);
	_classContent = aContent;

	reloadClassMembers();
	m_listMemberFunctions.SetFocus();
}

BOOL MemberFunctionsOption::writeOptionsToClassTextLine()
{
	return FALSE;
}

void MemberFunctionsOption::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	
	releaseNewButton();
	if (_iSelectedItem < 0) return;
	if (_iSelectedItem >= m_listMemberFunctions.GetItemCount()) {
		_iSelectedItem = m_listMemberFunctions.GetItemCount() - 1;
		if (_iSelectedItem >= 0) {
			ClassTextLine *theLine = _classContent->getMemberFunctionLine(_iSelectedItem);
			m_editMemberFunction = theLine->ptrAt(0);
			UpdateData(FALSE);
		} else {
			m_editMemberFunction = "";
			UpdateData(FALSE);
		}
		return;
	}
	m_listMemberFunctions.DeleteItem(_iSelectedItem);
	_classContent->deleteMemberFunction(_iSelectedItem);
	_iSelectedItem--;
	if (_iSelectedItem == -1 &&
		m_listMemberFunctions.GetItemCount() > 0) {
		_iSelectedItem = 0;
	}
	if (_iSelectedItem >= 0) {
		ClassTextLine *theLine = _classContent->getMemberFunctionLine(_iSelectedItem);
		m_editMemberFunction = theLine->ptrAt(0);
		UpdateData(FALSE);
	} else {
		m_editMemberFunction = "";
		UpdateData(FALSE);
	}
	refreshAllViews();
}

void MemberFunctionsOption::OnButtonNew() 
{
	// TODO: Add your control notification handler code here
	
	_newButtonPressed = TRUE;
	_iSelectedItem = m_listMemberFunctions.GetItemCount();
	m_editMemberFunction = "";
	UpdateData(FALSE);
	m_buttonNewCtrl.EnableWindow(FALSE);
	m_editMemberFunctionCtrl.SetFocus();
}

void MemberFunctionsOption::releaseNewButton()
{
	_newButtonPressed = FALSE;
	m_buttonNewCtrl.EnableWindow(TRUE);
}

void MemberFunctionsOption::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	
	m_buttonUpdateCtrl.EnableWindow(FALSE);
	UpdateData(TRUE);
	char buffer[BUFSIZ];
	int n = Text::strcpyCompact(buffer,m_editMemberFunction,BUFSIZ);
	if (n == 0) {
		OnButtonDelete();
		return;
	}
	if (_iSelectedItem < 0) return;
	if (_iSelectedItem > m_listMemberFunctions.GetItemCount()) {
		releaseNewButton();
		return;
	} else if (_iSelectedItem == m_listMemberFunctions.GetItemCount() && 
		_newButtonPressed == FALSE) {
		releaseNewButton();
		return;
	} else if (_iSelectedItem == m_listMemberFunctions.GetItemCount() && 
		_newButtonPressed == TRUE &&
		_classContent->nOfMemberFunctions() > 0) {
		ClassTextLine *aLine = new ClassTextLine();
		_classContent->methodContent()->insertAt(aLine,_iSelectedItem);
	}
	releaseNewButton(); // 이 함수에서 _newButtonPressed 가 reset됨 
	ClassTextLine *theLine = _classContent->getMemberFunctionLine(_iSelectedItem);
	if (theLine == NIL) return;
	theLine->setString(m_editMemberFunction);
	theLine->parseAsMemberFunction();
	m_listMemberFunctions.DeleteItem(_iSelectedItem);
	loadClassTextLine(_iSelectedItem,theLine);
	refreshAllViews();
}

void MemberFunctionsOption::setEditField(NMHDR* pNMHDR)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iItem = pNMListView->iItem;
	if (iItem < 0) return;
	if (iItem >= m_listMemberFunctions.GetItemCount()) return;
	ClassTextLine *theLine = _classContent->getMemberFunctionLine(iItem);
	if (theLine == NIL) return;
	_iSelectedItem = iItem;
	m_editMemberFunction = theLine->ptrAt(0);
	UpdateData(FALSE);
	m_buttonUpdateCtrl.EnableWindow(FALSE);
}

void MemberFunctionsOption::OnClickListMemberFunctions(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	releaseNewButton();
	setEditField(pNMHDR);
	*pResult = 0;
}

void MemberFunctionsOption::OnDblclkListMemberFunctions(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	releaseNewButton();
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iItem = pNMListView->iItem;
	if (iItem < 0) return;
	if (iItem >= m_listMemberFunctions.GetItemCount()) return;
	ClassTextLine *theLine = _classContent->getMemberFunctionLine(iItem);
	if (theLine == NIL) return;
	_iSelectedItem = iItem;
	MemberPropDlg *memberDlg = theAppPtr->getActiveMethodPropDlg();
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

void MemberFunctionsOption::OnChangeEditMemberFunction() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the MemberOptionDlg::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
	m_buttonUpdateCtrl.EnableWindow(TRUE);
}

BOOL MemberFunctionsOption::OnInitDialog() 
{
	MemberOptionDlg::OnInitDialog();
	
	// TODO: Add extra initialization here

	static LPCTSTR szTabName[] = { _T(" Visibility "), _T(" Return Type "), _T(" Name ") };

	LV_COLUMN columnValue;
	int i = 0;
	for(i = 0; i < 3; i++) {
		columnValue.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		columnValue.fmt = LVCFMT_LEFT;
		columnValue.pszText = (char *)szTabName[i];
		columnValue.iSubItem = i;
		columnValue.cx = 100;
		m_listMemberFunctions.InsertColumn(i,&columnValue);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
