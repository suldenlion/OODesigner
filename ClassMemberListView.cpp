// ClassMemberListView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "ClassMemberListView.h"
#include "COODClassDoc.h"
#include "PackageLibrary.h"
#include "ClassContent.h"
#include "ClassLibrary.h"
#include "MemberPropDlg.h"
#include "ClassTextLine.h"
#include "CResizableTreeBar.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ClassMemberListView

IMPLEMENT_DYNCREATE(ClassMemberListView, CListView)

ClassMemberListView::ClassMemberListView()
{
	_className = _T("");
	_packageName = _T("");
	_whichMember = -1;
}

ClassMemberListView::~ClassMemberListView()
{
}


BEGIN_MESSAGE_MAP(ClassMemberListView, CListView)
	//{{AFX_MSG_MAP(ClassMemberListView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ClassMemberListView diagnostics

#ifdef _DEBUG
void ClassMemberListView::AssertValid() const
{
	CListView::AssertValid();
}

void ClassMemberListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ClassMemberListView message 

void ClassMemberListView::deleteAllItems()
{
	CListCtrl& ctrl = GetListCtrl();
	ctrl.DeleteAllItems();
}

void ClassMemberListView::loadDataMembers(CString className,CString packageName)
{
	_className = className;
	_packageName = packageName;
	_whichMember = DATAMEMBER_ID;

	CListCtrl& ctrl = GetListCtrl();
	ctrl.DeleteAllItems();
	ctrl.InsertItem(0,"Data Members:");

	ClassContent *theContent = 
		theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(className);

	int nDataMembers = theContent->nOfDataMembers();
	for (int i = 0; i < nDataMembers; i++) {
		ClassTextLine *pLine = theContent->getDataMemberLine(i);
		if (pLine == NIL) break;
		CString aLine = _T("");
		int vis = pLine->visibility();
		if (vis == PUBLIC_ID) {
			aLine = aLine + "public ";
		} else if (vis == PROTECTED_ID) {
			aLine = aLine + "protected ";
		} else if (vis == PRIVATE_ID) {
			aLine = aLine + "private ";
		}
		CString browserString;
		pLine->getMemberBrowserString(browserString);
		CString type;
		type = pLine->type();
		if (type.IsEmpty()) {
			aLine = aLine + browserString;
		} else {
			aLine = aLine + type + " " + browserString;
		}
		ctrl.InsertItem(i+1,aLine);
	}
	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(&rect);
}

void ClassMemberListView::loadMemberFunctions(CString className,CString packageName)
{
	_className = className;
	_packageName = packageName;
	_whichMember = MEMBERFUNCTION_ID;

	CListCtrl& ctrl = GetListCtrl();
	ctrl.DeleteAllItems();
	ctrl.InsertItem(0,"Member Functions:");

	ClassContent *theContent = 
		theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(className);

	int nMemberFunctions = theContent->nOfMemberFunctions();
	for (int i = 0; i < nMemberFunctions; i++) {
		ClassTextLine *pLine = theContent->getMemberFunctionLine(i);
		if (pLine == NIL) break;
		CString aLine = _T("");
		int vis = pLine->visibility();
		if (vis == PUBLIC_ID) {
			aLine = aLine + "public ";
		} else if (vis == PROTECTED_ID) {
			aLine = aLine + "protected ";
		} else if (vis == PRIVATE_ID) {
			aLine = aLine + "private ";
		}
		CString browserString;
		pLine->getMemberBrowserString(browserString);
		CString type;
		type = pLine->type();
		if (type.IsEmpty()) {
			aLine = aLine + browserString;
		} else {
			aLine = aLine + type + " " + browserString;
		}
		ctrl.InsertItem(i+1,aLine);
	}
	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(&rect);
}

int ClassMemberListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CFont font;
	font.CreateFont(0,0,0,0,
			FW_BOLD,FALSE,
			FALSE,FALSE,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Times New Roman");
	CListCtrl& ctrl = GetListCtrl();
	ctrl.SetFont(&font);
	ctrl.ModifyStyle(0,LVS_NOCOLUMNHEADER|LVS_REPORT|LVS_SINGLESEL);
	LV_COLUMN columnData;
	columnData.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	columnData.fmt = LVCFMT_LEFT;
	columnData.pszText = "Members";
	columnData.iSubItem = 0;
	columnData.cx = 1000;
	columnData.cchTextMax = BUFSIZ;
	ctrl.InsertColumn(0,&columnData);
	return 0;
}


void ClassMemberListView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	ShowScrollBar(SB_HORZ,FALSE);
}

void ClassMemberListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iItem = pNMListView->iItem;
	if (iItem <= 0) return;
	if (iItem >= GetListCtrl().GetItemCount()) return;
	ClassContent *theContent = 
		theAppPtr->pCOODClassDoc->getAllClassContents()->getClassContentFor(_className);
	ClassTextLine *theLine = NIL;
	if (_whichMember == DATAMEMBER_ID) {
		theLine = theContent->getDataMemberLine(iItem-1);
	} else if (_whichMember == MEMBERFUNCTION_ID) {
		theLine = theContent->getMemberFunctionLine(iItem-1);
	}
	if (theLine == NIL) return;
	MemberPropDlg *memberDlg = NIL;
	if (_whichMember == DATAMEMBER_ID) {
		memberDlg = theAppPtr->getActiveVarPropDlg();
	} else if (_whichMember == MEMBERFUNCTION_ID) {
		memberDlg = theAppPtr->getActiveMethodPropDlg();
	}
	if (memberDlg == NIL) return;
	if ((memberDlg->GetStyle() & WS_VISIBLE) == 0) {
		memberDlg->ShowWindow(SW_SHOW);
	}
	memberDlg->loadFromClassTextLine(NIL,theLine,iItem-1,theContent,_className,_packageName);
	*pResult = 0;
}

