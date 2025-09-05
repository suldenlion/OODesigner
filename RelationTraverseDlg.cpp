// RelationTraverseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "RelationTraverseDlg.h"
#include "RelationTraverseFrame.h"
#include "ClassTreeView.h"
#include "ClassMemberListView.h"
#include "ClassTreeView.h"
#include "CMainFrame.h"
#include "ResizeGlobalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(RelationTraverseDlg,CDialog)

/////////////////////////////////////////////////////////////////////////////
// RelationTraverseDlg dialog

RelationTraverseDlg::RelationTraverseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RelationTraverseDlg::IDD, pParent)
{
	_whichOrient = FORWARD_ORIENT;
	_whichRelationship = GENERALIZATION_RELATIONSHIP;
	_className = _T("");
	_packageName = _T("");
	_theFrame = NIL;
	_initX = 0;
	_initY = 0;
}

RelationTraverseDlg::RelationTraverseDlg(CString &className,CString &packageName,CWnd* pParent /*=NULL*/)
	: CDialog(RelationTraverseDlg::IDD, pParent)
{
	_whichOrient = FORWARD_ORIENT;
	_whichRelationship = GENERALIZATION_RELATIONSHIP;
	_className = className;
	_packageName = packageName;
	_theFrame = NIL;
	_initX = 0;
	_initY = 0;
	//{{AFX_DATA_INIT(RelationTraverseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void RelationTraverseDlg::setNameAndLoadClassInfo(CString &className,CString &packageName)
{
	_className = className;
	_packageName = packageName;
	m_comboRelationshipCtrl.SetCurSel(_whichRelationship);
	OnSelchangeComboRelationship();
}

ClassMemberListView *RelationTraverseDlg::getListView(int i)
{
	return _theFrame->getListView(i);
}

int RelationTraverseDlg::getOrientString(CString &statement)
{
	m_comboOrientCtrl.GetLBText(_whichOrient,statement);
	return _whichOrient;
}

void RelationTraverseDlg::reloadClassMembers()
{
	ClassTreeView *treeView = _theFrame->getTreeView();
	if (treeView == NIL) return;
	treeView->reloadClassMembers();
}

void RelationTraverseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RelationTraverseDlg)
	DDX_Control(pDX, IDC_COMBO_ORIENT, m_comboOrientCtrl);
	DDX_Control(pDX, IDC_COMBO_RELATIONSHIP, m_comboRelationshipCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RelationTraverseDlg, CDialog)
	//{{AFX_MSG_MAP(RelationTraverseDlg)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_RELATIONSHIP, OnSelchangeComboRelationship)
	ON_CBN_SELCHANGE(IDC_COMBO_ORIENT, OnSelchangeComboOrient)
	//}}AFX_MSG_MAP
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RelationTraverseDlg message handlers

BOOL RelationTraverseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_theFrame = (RelationTraverseFrame *)RUNTIME_CLASS(RelationTraverseFrame)->CreateObject();
	if (_theFrame == NULL) {
		ErrorMsg("Can't create a frame in the dialog.");
		return TRUE;
	}

	if (!_theFrame->LoadFrame(IDR_DUMMY_FRAME,
		WS_CHILD|WS_VISIBLE,this,NULL)) {
		ErrorMsg("Can't load a frame in the dialog.");
		return TRUE;
	}

	RECT comboBox;
	m_comboRelationshipCtrl.GetWindowRect(&comboBox);

	ScreenToClient(&comboBox);

	_initX = 0;
	_initY = comboBox.bottom + comboBox.top;

	RECT thisBox;
	GetClientRect(&thisBox);

	int hFrame = thisBox.bottom - _initY;
	int wFrame = thisBox.right;
	_theFrame->SetWindowPos(NULL,_initX,_initY,wFrame,hFrame,SWP_SHOWWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RelationTraverseDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CDialog::OnGetMinMaxInfo(lpMMI);
	if (_theFrame == NIL) return;
	RECT leftBox;
	RECT rightBox;
	CWnd *pWnd = _theFrame->getTreeView();
	pWnd->GetClientRect(&leftBox);
	lpMMI->ptMinTrackSize.x = leftBox.right + 17;

	pWnd = _theFrame->getListView(0);
	pWnd->GetWindowRect(&rightBox);
	ScreenToClient(&rightBox);
	lpMMI->ptMinTrackSize.y = rightBox.bottom + _initY - 2;
}

void RelationTraverseDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT thisBox;
	GetClientRect(&thisBox);

	if (_theFrame == NIL) return;
	int hFrame = thisBox.bottom - _initY;
	int wFrame = thisBox.right;
	_theFrame->SetWindowPos(NULL,_initX,_initY,wFrame,hFrame,SWP_SHOWWINDOW);	
}

void RelationTraverseDlg::OnSelchangeComboRelationship() 
{
	// TODO: Add your control notification handler code here
	m_comboOrientCtrl.ResetContent();
	int sel = m_comboRelationshipCtrl.GetCurSel();
	if (sel == GENERALIZATION_RELATIONSHIP) {
		m_comboOrientCtrl.AddString("Derives");
		m_comboOrientCtrl.AddString("Is Derived By");
	} else if (sel == AGGREGATION_RELATIONSHIP) {
		m_comboOrientCtrl.AddString("Has Parts");
		m_comboOrientCtrl.AddString("Is Part Of");
	} else if (sel == DEPENDENCY_RELATIONSHIP) {
		m_comboOrientCtrl.AddString("Uses");
		m_comboOrientCtrl.AddString("Is Used By");
	} else {
		ErrorMsg("Something wrong to select relationship.");
		return;
	}
	_whichRelationship = sel;
	m_comboOrientCtrl.SetCurSel(_whichOrient);
	OnSelchangeComboOrient();
}

void RelationTraverseDlg::OnSelchangeComboOrient() 
{
	// TODO: Add your control notification handler code here

	ClassTreeView *treeView = _theFrame->getTreeView();
	if (treeView == NIL) {
		ErrorMsg("Can't find tree view for relationship.");
		return;
	}

	int sel = m_comboOrientCtrl.GetCurSel();

	if (_whichRelationship == GENERALIZATION_RELATIONSHIP) {
		treeView->loadTree(_className,_packageName,GENERALIZATION_RELATIONSHIP,sel);
	} else if (_whichRelationship == AGGREGATION_RELATIONSHIP) {
		treeView->loadTree(_className,_packageName,AGGREGATION_RELATIONSHIP,sel);
	} else if (_whichRelationship == DEPENDENCY_RELATIONSHIP) {
		treeView->loadTree(_className,_packageName,DEPENDENCY_RELATIONSHIP,sel);
	} else {
		ErrorMsg("Something wrong to select relationship.");
		return;
	}
	_whichOrient = sel;
}

