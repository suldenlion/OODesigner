// COODDoc.cpp : implementation file
//
#include "stdafx.h"
#include "OOD.h"
#include "Text.h"
#include "COODDoc.h"
#include "COODView.h"
#include "COODSrvrItem.h"
#include "CMainFrame.h"
#include "CInPlaceFrame.h"
#include "CSelectDlg.h"
#include "CClassView.h"
#include "COODCommonFrm.h"
#include "FontInfo.h"
#include "COODCntrlItem.h"
#include "COODCntrlItemList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COODDoc

IMPLEMENT_DYNCREATE(COODDoc, COleServerDoc)

COODDoc::COODDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here
	extensionNameAfterLoad = _T("");
	embeddedFileName = _T("");
}

CInPlaceFrame* COODDoc::getInPlaceFrame() 
{
	if (m_pInPlaceFrame == NIL) return NIL;
	if (!m_pInPlaceFrame->IsKindOf(RUNTIME_CLASS(CInPlaceFrame))) return NIL;
	return (CInPlaceFrame *)m_pInPlaceFrame;
}

BOOL COODDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

void COODDoc::OnNewEmbedding(LPSTORAGE lpStorage)
{
	COleServerDoc::OnNewEmbedding(lpStorage);
	CSelectDlg aDlg;
	UINT button = aDlg.DoModal();
	int dgmType = aDlg.fileType();
	CString fileName = aDlg.m_name; 
	if (dgmType == KTG_CLASS_DIAGRAM) {
		extensionNameAfterLoad = _T(_PAK_EXT);
	} else if (dgmType == KTG_USE_CASES) {
		extensionNameAfterLoad = _T(_USE_EXT);
	} else if (dgmType == KTG_COLLABORATION_DIAGRAM) {
		extensionNameAfterLoad = _T(_COL_EXT);
	} else if (dgmType == KTG_SEQUENCE_DIAGRAM) {
		extensionNameAfterLoad = _T(_SEQ_EXT);
	} else if (dgmType == KTG_STATE_DIAGRAM) {
		extensionNameAfterLoad = _T(_STA_EXT);
	} else if (dgmType == KTG_ACTIVITY_DIAGRAM) {
		extensionNameAfterLoad = _T(_ACT_EXT);
	} else if (dgmType == KTG_DEPLOYMENT_DIAGRAM) {
		extensionNameAfterLoad = _T(_DEP_EXT);
	} else {
		extensionNameAfterLoad = _T(_PAK_EXT);
	}
	adaptViewAndFrameAndControlBar();
	if (!fileName.IsEmpty()) {
		embeddedFileName = fileName;
	} else {
		embeddedFileName = m_strTitle;
	}
	SetTitle(embeddedFileName);
}

void COODDoc::OnOpenEmbedding(LPSTORAGE lpStorage)
{
	COleServerDoc::OnOpenEmbedding(lpStorage);
//	adaptViewAndFrameAndControlBar(); OnOpenDocument 시에 실행함
	if (!embeddedFileName.IsEmpty()) {
		SetTitle(embeddedFileName);
	} else {
		SetTitle(m_strTitle);
	}
}

void COODDoc::adaptViewAndFrameAndControlBar()
{
	CWnd *pMainWnd = AfxGetMainWnd();
	if (pMainWnd == NIL) return;
	if (!pMainWnd->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd))) return;
	CMDIFrameWnd *pMainFrame = (CMDIFrameWnd*) pMainWnd;	
	CMDIChildWnd *pChildFrame = pMainFrame->MDIGetActive();
	if (pChildFrame == NIL) return;
	if (!pChildFrame->IsKindOf(RUNTIME_CLASS(COODCommonFrm))) return;
	COODCommonFrm *pCommonFrm = (COODCommonFrm *)pChildFrame;
	pCommonFrm->setModelIdentity(extensionNameAfterLoad);
	if (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) {
		CControlBar *pBar = pCommonFrm->getModelToolBar();
		if (pBar != NIL)
			((CMainFrame *)pMainWnd)->ShowControlBar(pBar,TRUE,TRUE);
	}
	::SendMessage(pCommonFrm->m_hWnd,WM_COMMAND,ID_OLE_ADAPT_VIEW_FRAME,0);
}

COODDoc::~COODDoc()
{
}

COODView *COODDoc::getFirstView()
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL) return NIL;
	CView* pFirstView = GetNextView( pos );
	if (!pFirstView->IsKindOf(RUNTIME_CLASS(COODView)))
		return NIL;
	COODView *theView = (COODView *)pFirstView;
	return theView;
}

const char *COODDoc::getExtension()
{
	CDocTemplate* pTemplate = GetDocTemplate();
	if (pTemplate == NULL) return "";
	if (pTemplate == theAppPtr->pClassDocTemplate) {
		return _PAK_EXT;
	} else if (pTemplate == theAppPtr->pObjectDocTemplate) {
		return _PAK_EXT;
	} else if (pTemplate == theAppPtr->pStateDocTemplate) {
		return _STA_EXT;
	} else if (pTemplate == theAppPtr->pUseCaseDocTemplate) {
		return _USE_EXT;
	} else if (pTemplate == theAppPtr->pCollaborationDocTemplate) {
		return _COL_EXT;
	} else if (pTemplate == theAppPtr->pSequenceDocTemplate) {
		return _SEQ_EXT;
	} else if (pTemplate == theAppPtr->pActivityDocTemplate) {
		return _ACT_EXT;
	} else if (pTemplate == theAppPtr->pDeploymentDocTemplate) {
		return _DEP_EXT;
	} else if (extensionNameAfterLoad.GetLength() > 0) { // pServerDocTemplate case
		return extensionNameAfterLoad;
	} else {
		return "";
	}
}

COleServerItem* COODDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	// Instead of returning NULL, return a pointer to a new COleServerItem
	//  derived class that is used in conjunction with this document, then
	//  remove the ASSERT(FALSE) below.
	//  (i.e., return new CMyServerItem.)
	COODSrvrItem *pItem = new COODSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}


BEGIN_MESSAGE_MAP(COODDoc, COleServerDoc)
	//{{AFX_MSG_MAP(COODDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleServerDoc::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleServerDoc::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleServerDoc::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleServerDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleServerDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, COleServerDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODDoc diagnostics

#ifdef _DEBUG
void COODDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void COODDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COODDoc serialization

void COODDoc::SerializeForPackageOnly(CArchive& ar,CString viewName)
{
	ASSERT_VALID(this);

	// serialize all items in the doc item list
	if (ar.IsStoring())
	{
		DWORD dwCount = 0;
		POSITION pos = GetStartPosition();
		while (pos != NULL)
		{
			CDocItem* pDocItem = GetNextClientItem(pos);
			ASSERT_VALID(pDocItem);

			// only count non-blank ones
			if (!pDocItem->IsBlank() && pDocItem->IsKindOf(RUNTIME_CLASS(COODCntrlItem))) {
				COODCntrlItem *pItem = (COODCntrlItem *)pDocItem;
				if (pItem->getViewTitle().CompareNoCase(viewName) == 0)
					++dwCount;
			}
		}
		ar << dwCount;  // write count of objects

		// serialize all the items in the list
		pos = GetStartPosition();
		while (pos != NULL)
		{
			CDocItem* pDocItem = GetNextClientItem(pos);
			ASSERT_VALID(pDocItem);

			// only write non-blank ones
			if (!pDocItem->IsBlank() && pDocItem->IsKindOf(RUNTIME_CLASS(COODCntrlItem))) {
				COODCntrlItem *pItem = (COODCntrlItem *)pDocItem;
				if (pItem->getViewTitle().CompareNoCase(viewName) == 0)
					ar << pDocItem;
			}
		}
	}
	else
	{
		// No need to implementation
	}

	SerializeCommon(ar);
}

void COODDoc::SerializeCommon(CArchive& ar)
{
	BOOL reservedFlag0 = FALSE;
	BOOL reservedFlag1 = FALSE;
	BOOL reservedFlag2 = FALSE;
	BOOL reservedFlag3 = FALSE;
	BOOL reservedFlag4 = FALSE;
	UINT reservedInt0 = 0;
	UINT reservedInt1 = 0;
	UINT reservedInt2 = 0;
	UINT reservedInt3 = 0;
	UINT reservedInt4 = 0;
	CString reservedString0 = _T("");
	CString reservedString1 = _T("");
	CString reservedString2 = _T("");
	CString reservedString3 = _T("");
	CString reservedString4 = _T("");

	if (ar.IsStoring()) 
	{
		// TODO: add storing code here
		CString ext = getExtension();
		ar << theAppPtr->versionNo;
		ar << ext;
		ar << embeddedFileName;
		ar << (BYTE) theAppPtr->setGridFlag;
		ar << (LONG) theAppPtr->paperColor;
		ar << (LONG) theAppPtr->textColor;
		ar << (LONG) theAppPtr->shapeForegroundColor;
		ar << (LONG) theAppPtr->shapeBackgroundColor;
		ar << (LONG) theAppPtr->currentFontSize;
		ar << (LONG) theAppPtr->currentFontWeight;
		ar << (LONG) theAppPtr->currentFontColor;
		ar << theAppPtr->currentFontFaceName;
		ar << theAppPtr->currentFontStyleName;
		ar << (BYTE) theAppPtr->currentFontBoldFlag;
		ar << (BYTE) theAppPtr->currentFontItalicFlag;
		ar << (BYTE) theAppPtr->currentFontStrikeOutFlag;
		ar << (BYTE) theAppPtr->currentFontUnderlineFlag;

		ar << (BYTE)reservedFlag0;
		ar << (BYTE)reservedFlag1;
		ar << (BYTE)reservedFlag2;
		ar << (BYTE)reservedFlag3;
		ar << (BYTE)reservedFlag4;
		ar << (LONG)reservedInt0;
		ar << (LONG)reservedInt1;
		ar << (LONG)reservedInt2;
		ar << (LONG)reservedInt3;
		ar << (LONG)reservedInt4;
		ar << reservedString0;
		ar << reservedString1;
		ar << reservedString2;
		ar << reservedString3;
		ar << reservedString4;
	}
	else
	{
		// TODO: add loading code here
		CString versionNo;
		CString ext;
		CString fName;
		BOOL flag = FALSE;
		UINT paperColor;
		UINT textColor;
		UINT shapeForegroundColor;
		UINT shapeBackgroundColor;
		BOOL flag1 = FALSE;
		ar >> versionNo;
		ar >> ext;
		ar >> fName;
		ar >> (BYTE&)flag;
		ar >> (LONG&) paperColor;
		ar >> (LONG&) textColor;
		ar >> (LONG&) shapeForegroundColor;
		ar >> (LONG&) shapeBackgroundColor;
		ar >> (LONG&) theAppPtr->currentFontSize;
		ar >> (LONG&) theAppPtr->currentFontWeight;
		ar >> (LONG&) theAppPtr->currentFontColor;
		ar >> theAppPtr->currentFontFaceName;
		ar >> theAppPtr->currentFontStyleName;
		ar >> (BYTE&) theAppPtr->currentFontBoldFlag;
		ar >> (BYTE&) theAppPtr->currentFontItalicFlag;
		ar >> (BYTE&) theAppPtr->currentFontStrikeOutFlag;
		ar >> (BYTE&) theAppPtr->currentFontUnderlineFlag;

		ar >> (BYTE&)reservedFlag0;
		ar >> (BYTE&)reservedFlag1;
		ar >> (BYTE&)reservedFlag2;
		ar >> (BYTE&)reservedFlag3;
		ar >> (BYTE&)reservedFlag4;
		ar >> (LONG&)reservedInt0;
		ar >> (LONG&)reservedInt1;
		ar >> (LONG&)reservedInt2;
		ar >> (LONG&)reservedInt3;
		ar >> (LONG&)reservedInt4;
		ar >> reservedString0;
		ar >> reservedString1;
		ar >> reservedString2;
		ar >> reservedString3;
		ar >> reservedString4;

		theAppPtr->fileVersionNo = versionNo;
		theAppPtr->setGridFlag = flag;
		theAppPtr->paperColor = (COLORREF)paperColor;
		theAppPtr->textColor = (COLORREF)textColor;
		theAppPtr->shapeForegroundColor = (COLORREF)shapeForegroundColor;
		theAppPtr->shapeBackgroundColor = (COLORREF)shapeBackgroundColor;

		if (COODView::ErasePen != NIL) {
			delete COODView::ErasePen; COODView::ErasePen = NIL;
		}
		COODView::ErasePen = new CPen(PS_SOLID,1,theAppPtr->paperColor);

		if (COODView::EraseBrush != NIL) {
			delete COODView::EraseBrush; COODView::EraseBrush = NIL;
		}
		COODView::EraseBrush = new CBrush(theAppPtr->paperColor);

		if (COODView::ShapeEraseBrush != NIL) {
			delete COODView::ShapeEraseBrush; COODView::ShapeEraseBrush = NIL;
		}
		COODView::ShapeEraseBrush = new CBrush(theAppPtr->shapeBackgroundColor);

		if (COODView::RubberbandPen != NIL) {
			delete COODView::RubberbandPen; COODView::RubberbandPen = NIL;
		}
		COODView::RubberbandPen = new CPen(PS_SOLID,1,theAppPtr->shapeForegroundColor);

		if (COODView::PlainPen != NIL) {
			delete COODView::PlainPen; COODView::PlainPen = NIL;
		}
		COODView::PlainPen = new CPen(PS_SOLID,1,theAppPtr->shapeForegroundColor);

		if (COODView::PlainBrush != NIL) {
			delete COODView::PlainBrush; COODView::PlainBrush = NIL;
		}
		COODView::PlainBrush = new CBrush(theAppPtr->shapeForegroundColor);

		extensionNameAfterLoad = ext;
		embeddedFileName = fName;

		COODView *pView = getFirstView();
		if (pView != NULL) {
			pView->fontInfo()->resetFontInfo();
			pView->resetFontHeight();
		}
	}
}

void COODDoc::Serialize(CArchive& ar)
{
	COleServerDoc::Serialize(ar);

	SerializeCommon(ar);
}

/////////////////////////////////////////////////////////////////////////////
// COODDoc commands

void COODDoc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// TODO: Add your specialized code here and/or call the base class
	char buffer[BUFSIZ];
	int n = Text::strcpyCompact(buffer,lpszTitle,BUFSIZ);
	CString compacted = buffer;
	if (compacted.Right(_EXT_LEN5).CompareNoCase(getExtension()) != 0) {
		compacted = compacted + getExtension();
	}
	COleServerDoc::SetTitle(compacted);
	POSITION pos = GetFirstViewPosition();
	CView* pFirstView = GetNextView(pos);
	if (pFirstView == NULL) return; // 패키지 도큐먼트 로드 시에 사용되는 special case
	ASSERT(pFirstView->IsKindOf(RUNTIME_CLASS(COODView)));
	((COODView*)pFirstView)->setTitle(compacted);
}

void COODDoc::setRootStg(CString lpszPathName)
{
	CString oldPathName = m_strPathName;
	m_strPathName = lpszPathName;
	setRootStg();
	m_strPathName = oldPathName;
}

void COODDoc::setRootStg()
{
	USES_CONVERSION;

	if (m_lpRootStg != NULL)
	{
		m_lpRootStg->Release();
		m_lpRootStg = NULL;
	}

	CString lpszPathName = m_strPathName;
	LPCOLESTR lpsz = T2COLE(lpszPathName);

	// use STGM_CONVERT if necessary
	SCODE sc;
	LPSTORAGE lpStorage = NULL;
	// convert existing storage file
	sc = StgCreateDocfile(lpsz, STGM_READWRITE|
		STGM_TRANSACTED|STGM_SHARE_EXCLUSIVE|STGM_CONVERT,
		0, &lpStorage);
	if (FAILED(sc) || lpStorage == NULL)
		sc = StgCreateDocfile(lpsz, STGM_READ|
				STGM_TRANSACTED|STGM_SHARE_DENY_WRITE|STGM_CONVERT,
				0, &lpStorage);
	ASSERT(lpStorage != NULL);
	m_lpRootStg = lpStorage;
//	COleDocument::SetModifiedFlag(FALSE); // start off with unmodified
}

void COODDoc::OnDeactivate() 
{
	// TODO: Add your specialized code here and/or call the base class
	COODView *pView = getFirstView();
	if (pView != NULL) {
		pView->editorFinished();
	}
	UpdateAllItems(NULL); // 이 문장이 있어야 COODSrvrItem::OnDraw() 함수가 호출됨
	COleServerDoc::OnDeactivate();
}

void COODDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	SetModifiedFlag(FALSE);     // make clean
	COleServerDoc::DeleteContents();
}

void COODDoc::copyOleItemsTo(COODDoc *toDoc,CString *viewName)
{
	// OLE 객체 복사 ...

	COODCntrlItemList *pList = new COODCntrlItemList();
	POSITION itemPos = GetStartPosition();
	while(itemPos != NULL) {
		CDocItem *pDocItem = GetNextClientItem(itemPos);
		if (pDocItem != NULL) {
			if (viewName == NULL) {
				pList->addTail((COODCntrlItem *)pDocItem);
			} else if (((COODCntrlItem *)pDocItem)->getViewTitle().GetLength() > 0 &&
				viewName->CompareNoCase(((COODCntrlItem *)pDocItem)->getViewTitle()) == 0) {
				pList->addTail((COODCntrlItem *)pDocItem);
			}
		}
	}
	COODCntrlItem *pDocItem = pList->getFirst();
	while (pDocItem != NIL) {
		pDocItem->CopyToClipboard(pDocItem->CanPasteLink());

		COleDataObject dataObject;
		dataObject.AttachClipboard();

		BeginWaitCursor();
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;
		CRect rect;
		pDocItem->getXY12Absolutely(rect);
		pDocItem->Delete();
		x1 = rect.left;
		y1 = rect.top;
		x2 = rect.right;
		y2 = rect.bottom;

		pDocItem = new COODCntrlItem(toDoc);
		TRY {
			if (!pDocItem->CreateFromData(&dataObject) &&
				!pDocItem->CreateStaticFromData(&dataObject)) {
				AfxThrowMemoryException();
			}
			pDocItem->setCoord(x1,y1,x2,y2);
			pDocItem->UpdateLink();
		}
		CATCH_ALL(e) {
			pDocItem->Delete();
			pDocItem = NULL;
			AfxMessageBox(IDP_FAILED_TO_CREATE);
		}
		END_CATCH_ALL

		EndWaitCursor();

		pDocItem = pList->getNext();
	}
	pList->clear();
	delete pList;
}

BOOL COODDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!COleServerDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	adaptViewAndFrameAndControlBar(); // Linking 시에는 이곳 말고 다른 곳을 찾을 수 가 없었슴 (Embedding은 당연빵)
	return TRUE;
}

