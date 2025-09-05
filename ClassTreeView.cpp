// ClassTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "figutil.h"
#include "KtgMacro.h"
#include "ClassTreeView.h"
#include "RelationTraverseDlg.h"
#include "CResizableTreeBar.h"
#include "CMainFrame.h"
#include "ClassMemberListView.h"
#include "RelationshipInfoTupleList.h"
#include "COODClassDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ClassTreeView

IMPLEMENT_DYNCREATE(ClassTreeView, CTreeView)

ClassTreeView::ClassTreeView()
{
	_whichRelationship = GENERALIZATION_RELATIONSHIP;
	_whichOrient = FORWARD_ORIENT;
	_rootClassName = _T("");
	_selectedClassName = _T("");
	_packageName = _T("");
}

ClassTreeView::~ClassTreeView()
{
}

RelationshipInfoTupleList *ClassTreeView::getActiveRelationshipLibrary()
{
	if (_whichRelationship == GENERALIZATION_RELATIONSHIP) {
		return theAppPtr->pCOODClassDoc->getGeneralizationLibrary();
	} else if (_whichRelationship == AGGREGATION_RELATIONSHIP) {
		return theAppPtr->pCOODClassDoc->getAggregationLibrary();
	} else {
		return theAppPtr->pCOODClassDoc->getDependencyLibrary();
	}
}

RelationTraverseDlg *ClassTreeView::getParentDlg()
{
	CWnd *pParent = GetParent()->GetParent()->GetParent();
	if (pParent == NIL) return NIL;
	if (!pParent->IsKindOf(RUNTIME_CLASS(RelationTraverseDlg))) return NIL;
	return (RelationTraverseDlg *) pParent;
}

BEGIN_MESSAGE_MAP(ClassTreeView, CTreeView)
	//{{AFX_MSG_MAP(ClassTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_WM_SHOWWINDOW()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_DELETE_RELATIONSHIP, OnDeleteRelationship)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ClassTreeView drawing

/////////////////////////////////////////////////////////////////////////////
// ClassTreeView diagnostics

#ifdef _DEBUG
void ClassTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void ClassTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ClassTreeView message handlers

void ClassTreeView::reloadClassMembers()
{
	RelationTraverseDlg *parentDlg = getParentDlg();
	if (parentDlg == NIL) return;
	ClassMemberListView *pView = parentDlg->getListView(0);
	if (pView != NIL) pView->loadDataMembers(_selectedClassName,_packageName);
	pView = parentDlg->getListView(1);
	if (pView != NIL) pView->loadMemberFunctions(_selectedClassName,_packageName);
}

void ClassTreeView::loadTree()
{
	_selectedClassName = _rootClassName;

	CTreeCtrl &ctrl = GetTreeCtrl();
	ctrl.DeleteAllItems();

	HTREEITEM rootItem = ctrl.InsertItem(_rootClassName);
	ctrl.SetItemImage(rootItem,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);


	RelationshipInfoTupleList *library = getActiveRelationshipLibrary();
	CStringList childrens;
	if (_whichOrient == FORWARD_ORIENT) {
		library->getMinorClassNames(_rootClassName,childrens);
	} else {
		library->getMajorClassNames(_rootClassName,childrens);
	}

	POSITION pos = childrens.GetHeadPosition();
	while (pos != NULL) {
		CString aChild = childrens.GetNext(pos);
		HTREEITEM hItem = ctrl.InsertItem(aChild,rootItem);
		ctrl.SetItemImage(hItem,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	}
	
	SetFocus();
	reloadClassMembers();

	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(&rect);
}

void ClassTreeView::loadTree(CString className,CString packageName,int relationship,int orient)
{
	_whichRelationship = relationship;
	_whichOrient = orient;
	_rootClassName = className;
	_selectedClassName = className;
	_packageName = packageName;

	loadTree();
}

BOOL ClassTreeView::ifExpanededAlready(HTREEITEM hItem)
{
	CTreeCtrl &ctrl = GetTreeCtrl();
	CString theName = ctrl.GetItemText(hItem);
	HTREEITEM hParent = ctrl.GetParentItem(hItem);
	while (hParent != NULL) {
		CString parentName = ctrl.GetItemText(hParent);
		if (parentName.CompareNoCase(theName) == 0)
			return TRUE;
		hParent = ctrl.GetParentItem(hParent);
	}
	return FALSE;
}

void ClassTreeView::loadGrandChildrens(HTREEITEM currentItem)
{
	CTreeCtrl &ctrl = GetTreeCtrl();
	HTREEITEM hChild = ctrl.GetChildItem(currentItem);
	while (hChild != NULL) {
		if (ctrl.ItemHasChildren(hChild) == FALSE &&
			ifExpanededAlready(hChild) == FALSE) {
			CString className = ctrl.GetItemText(hChild);
			RelationshipInfoTupleList *library = getActiveRelationshipLibrary();
			CStringList childrens;
			if (_whichOrient == FORWARD_ORIENT) {
				library->getMinorClassNames(className,childrens);
			} else {
				library->getMajorClassNames(className,childrens);
			}

			POSITION pos = childrens.GetHeadPosition();
			while (pos != NULL) {
				CString aGrandchild = childrens.GetNext(pos);
				HTREEITEM hItem = ctrl.InsertItem(aGrandchild,hChild);
				ctrl.SetItemImage(hItem,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
			}
		}
		hChild = ctrl.GetNextSiblingItem(hChild);
	}
}

int ClassTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	CFont font;
	font.CreateFont(0,0,0,0,
			FW_BOLD,FALSE,
			FALSE,FALSE,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Times New Roman");
	CTreeCtrl &ctrl = GetTreeCtrl();
	ctrl.SetFont(&font);


	ctrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	ctrl.ModifyStyle(0,TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT);

	_imageList.Create(IDR_WS_DIAGRAMVIEW_BITMAP, 17, 1, RGB(255, 255, 255));
	ctrl.SetImageList(&_imageList,TVSIL_NORMAL);
	return 0;
}


void ClassTreeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTreeView::OnLButtonDown(nFlags, point);
	CTreeCtrl &ctrl = GetTreeCtrl();
	HTREEITEM hItem	= ctrl.GetSelectedItem();
	if (hItem == NULL) return;
	CString className = ctrl.GetItemText(hItem);
	if (className.CompareNoCase(_selectedClassName) == 0) return;
	_selectedClassName = className;
	reloadClassMembers();
}

void ClassTreeView::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	HTREEITEM currentItem = pNMTreeView->itemNew.hItem;
	if (currentItem == NULL) return;

	CTreeCtrl &ctrl = GetTreeCtrl();
	if (ctrl.ItemHasChildren(currentItem) == FALSE) return;
	
	loadGrandChildrens(currentItem);

	UINT state = ctrl.GetItemState(currentItem,TVIF_STATE);
	if (state & TVIS_EXPANDED) {
		ctrl.SetItemImage(currentItem,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
	} else {
		ctrl.SetItemImage(currentItem,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	}
	
	*pResult = 0;
}

BOOL ClassTreeView::tryToDeleteSelectedItem()
{
	CTreeCtrl &ctrl = GetTreeCtrl();
	HTREEITEM minorItem	= ctrl.GetSelectedItem();
	if (minorItem == NULL) return FALSE;
	CString minorName = ctrl.GetItemText(minorItem);
	HTREEITEM majorItem = ctrl.GetParentItem(minorItem);
	if (majorItem == NULL) return FALSE;
	CString majorName = ctrl.GetItemText(majorItem);
	char buffer[BUFSIZ];
	CString statement = _T("");
	int sel = getParentDlg()->getOrientString(statement);
	sprintf_s(buffer,BUFSIZ,"Are you sure to delete \"%s %s %s\" relationship ?",
			majorName,statement,minorName);
	int ans = MessageBox(buffer,"OODesigner Question Message",MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION);
	if (ans != IDYES) return FALSE;
	RelationshipInfoTupleList *library = getActiveRelationshipLibrary();
	char major[BUFSIZ];
	char minor[BUFSIZ];
	if (sel == 0) {
		strcpy_s(major,BUFSIZ,majorName);
		strcpy_s(minor,BUFSIZ,minorName);
	} else {
		strcpy_s(major,BUFSIZ,minorName);
		strcpy_s(minor,BUFSIZ,majorName);
	}
	BOOL removed = FALSE;
	CString packName = _T("");
	if (_whichRelationship == GENERALIZATION_RELATIONSHIP) {
		removed = theAppPtr->pCOODClassDoc->tryToRemoveRelationshipInfo(library,major,minor,IAMGENERALIZATION,packName);
	} else if (_whichRelationship == AGGREGATION_RELATIONSHIP) {
		removed = theAppPtr->pCOODClassDoc->tryToRemoveRelationshipInfo(library,major,minor,IAMAGGREGATION,packName);
	} else {
		removed = theAppPtr->pCOODClassDoc->tryToRemoveRelationshipInfo(library,major,minor,IAMDEPENDENCY,packName);
	}
	if (removed == FALSE) {
		sprintf_s(buffer,BUFSIZ,"Can't delete the relationship.\r\nPlease delete the link in %s package.",packName);
		MessageBox(buffer,"OODesigner Warning Message",MB_OK|MB_TASKMODAL|MB_ICONWARNING);
		return FALSE;
	}
	loadTree();
	return TRUE;
}

BOOL ClassTreeView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN && (LOWORD(pMsg->wParam) == VK_DELETE)) {
		BOOL processed = tryToDeleteSelectedItem();
		if (processed == TRUE) {
			return -1;
		} else {
			return CTreeView::PreTranslateMessage(pMsg);
		}
	} 
	return CTreeView::PreTranslateMessage(pMsg);
}

void ClassTreeView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTreeView::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (bShow) return;
	if (nStatus & SW_PARENTOPENING) return;
	_selectedClassName = _rootClassName;
	CTreeCtrl &ctrl = GetTreeCtrl();
	ctrl.DeleteAllItems();
	RelationTraverseDlg *parentDlg = getParentDlg();
	if (parentDlg == NIL) return;
	ClassMemberListView *pView = parentDlg->getListView(0);
	if (pView != NIL) pView->deleteAllItems();
	pView = parentDlg->getListView(1);
	if (pView != NIL) pView->deleteAllItems();
}

void ClassTreeView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTreeCtrl &ctrl = GetTreeCtrl();
	HTREEITEM hItem	= ctrl.GetSelectedItem();
	if (hItem == NULL) {
		return;
	}
	if (hItem == ctrl.GetRootItem()) {
		return;
	}
	CRect tmpRect;
	ctrl.GetItemRect(hItem,&tmpRect,TRUE);
	if (tmpRect.PtInRect(point)) {
		ctrl.ClientToScreen(&point);
		CMenu *pMenu = mainFramePtr->m_wndTreeBar.getDeleteRelationshipMenu();
		pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,&ctrl);
	}
}

void ClassTreeView::OnDeleteRelationship() 
{
	// TODO: Add your command handler code here
	
	tryToDeleteSelectedItem();
}

