// COODCommonDoc.cpp : implementation file
//

#include "stdafx.h"
#include "AfxDeleteExceptionMacro.h"
#include "OOD.h"
#include "COODCommonDoc.h"
#include "FigureList.h"
#include "Figure.h"
#include "CMainFrame.h"
#include "COODView.h"
#include "COODClassDoc.h"
#include "COODSrvrItem.h"
#include "FigureLibrary.h"
#include "ClassTemplate.h"
#include "UnsignedLong.h"
#include "ClassContent.h"
#include "CustomToolBar.h"
#include "COODCntrlItem.h"
#include "COODCntrlItemList.h"
#include "CChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COODCommonDoc

IMPLEMENT_DYNCREATE(COODCommonDoc, COODDoc)

COODCommonDoc::COODCommonDoc()
: COODDoc()
{
	_figures = new FigureList();
	_diagramName = "";
	_comment.RemoveAll();
	_zoomRatioX = 100;
	_zoomRatioY = 100;
	_originX = 0;
	_originY = 0;

	_visibleDocumentFlag = TRUE;
}

BOOL COODCommonDoc::OnNewDocument()
{
	if (!COODDoc::OnNewDocument())
		return FALSE;
	return TRUE;
}

COODCommonDoc::~COODCommonDoc()
{
	_comment.RemoveAll();
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		aFigure->clearLists();
		aFigure = _figures->getNext();
	}
	aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		delete aFigure;
		aFigure = _figures->getNext();
	}
	delete _figures;
	_figures = NIL;
	_visibleDocumentFlag = TRUE;
}


BEGIN_MESSAGE_MAP(COODCommonDoc, COODDoc)
	//{{AFX_MSG_MAP(COODCommonDoc)
	ON_COMMAND(ID_WINDOW_CLOSE, OnWindowClose)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODCommonDoc diagnostics

#ifdef _DEBUG
void COODCommonDoc::AssertValid() const
{
	COODDoc::AssertValid();
}

void COODCommonDoc::Dump(CDumpContext& dc) const
{
	COODDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COODCommonDoc serialization

void COODCommonDoc::Serialize(CArchive& ar)
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

	COODDoc::Serialize(ar);
	_comment.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << _diagramName << _figures;
		ar << (LONG)_zoomRatioX << (LONG)_zoomRatioY;
		ar << (LONG)_originX << (LONG)_originY;

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
		Figure *aFigure = _figures->getFirst();
		while (aFigure != NIL) {
			aFigure->clearLists();
			aFigure = _figures->getNext();
		}
		aFigure = _figures->getFirst();
		while (aFigure != NIL) {
			delete aFigure;
			aFigure = _figures->getNext();
		}
		delete _figures;

		ar >> _diagramName >> _figures;
		ar >> (LONG&) _zoomRatioX >> (LONG&) _zoomRatioY;
		ar >> (LONG&) _originX >> (LONG&) _originY;

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

		if (_visibleDocumentFlag) {
			POSITION pos = GetFirstViewPosition();
			CView* pFirstView = GetNextView( pos );
			ASSERT(pFirstView->IsKindOf(RUNTIME_CLASS(COODView)));
			COODView *pOODView = (COODView *)pFirstView;
			aFigure = _figures->getFirst();
			while(aFigure != NIL) {
				aFigure->setController(pOODView);
				aFigure = _figures->getNext();
			}
			aFigure = _figures->getFirst();
			while(aFigure != NIL) {
				aFigure->makeRegion(pOODView->canvasRgn());
				aFigure = _figures->getNext();
			}
			pos = GetStartPosition();
			while(pos != NULL) {
				COODCntrlItem *selection = (COODCntrlItem *)GetNextClientItem(pos);
				selection->setController((COODView*)pFirstView,pOODView->viewTitle);
			}
			pos = GetStartPosition();
			while(pos != NULL) {
				COODCntrlItem *selection = (COODCntrlItem *)GetNextClientItem(pos);
				selection->makeRegion(pOODView);
			}
			mainFramePtr->setZoomValue(this);
		}
	}
//	COleServerDoc::Serialize(ar);
}

void COODCommonDoc::setModifiedFlag(BOOL flag)
{
	if (IsModified() == FALSE) {
		POSITION pos = GetFirstViewPosition();
		CView* pFirstView = GetNextView(pos);
		ASSERT(pFirstView->IsKindOf(RUNTIME_CLASS(COODView)));
		if (flag) {
			((COODView*)pFirstView)->showTitleAsModified();
		} else {
			((COODView*)pFirstView)->showTitleAsNotModified();
		}
	}
	COleServerDoc::SetModifiedFlag(flag);
}

/* 이 함수는 정적 함수로서 뷰없이 파일 내용만을 로드하기위해 사용된다.
   특히 웍스페이스가 존재하는 상태에서 패키지 파일을 로드할 때 사용된다. 
   원본 라이브러리에 복사한 후 바로 없앨 것이다.
*/
CDocument *COODCommonDoc::openInvisibleDocument(CDocTemplate *pTemplate,LPCTSTR lpszPathName)
{
	CDocument* pDocument = (CDocument*)RUNTIME_CLASS(COODCommonDoc)->CreateObject();
	if (pDocument == NULL)
	{
		TRACE0("Warning: Dynamic create of document type COODCommonDoc failed.\n");
		return NULL;
	}
	ASSERT_KINDOF(COODCommonDoc, pDocument);
	pTemplate->AddDocument(pDocument);

	ASSERT_VALID(pDocument);

	pDocument->m_bAutoDelete = FALSE;   // 내가 직접 없앨 것이기 때문에

	// open an existing document
	CWaitCursor wait;
	((COODCommonDoc*)pDocument)->_visibleDocumentFlag = FALSE;

	if (!pDocument->OnOpenDocument(lpszPathName))
	{
		// user has be alerted to what failed in OnOpenDocument
		TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
		((COODCommonDoc*)pDocument)->_visibleDocumentFlag = TRUE;
		return NULL;
	}
	((COODCommonDoc*)pDocument)->_visibleDocumentFlag = TRUE;
#ifdef _MAC
	// if the document is dirty, we must have opened a stationery pad
	//  - don't change the pathname because we want to treat the document
	//  as untitled
	if (!pDocument->IsModified())
#endif
		pDocument->SetPathName(lpszPathName);

	return pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// COODCommonDoc commands

BOOL COODCommonDoc::onWindowClose(BOOL removeViewNameFlag) 
{
	// TODO: Add your command handler code here
	if (IsModified()) {
		m_strPathName = GetTitle();
		char buffer[BUFSIZ];
		sprintf_s(buffer,BUFSIZ,"Do you want to save %s diagram ?",m_strPathName);
		int ans = YesNoCancelMsg(buffer);
		if (ans == IDCANCEL) return TRUE;
		if (ans == IDYES) {
//			COODDoc::DoSave(m_strPathName);
			OnFileSave();
		}
	}
	if (removeViewNameFlag == TRUE) {
		POSITION pos = GetFirstViewPosition(); 
		CView* activeView = GetNextView( pos );
		if (activeView->IsKindOf(RUNTIME_CLASS(COODView)) &&
			activeView->GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc))) {
			COODView *theView = (COODView *)activeView;
			theAppPtr->pCOODClassDoc->removeViewName(theView->viewTitle);
		}
	}
	// shut it down
	OnCloseDocument();
		// this should destroy the document
	return FALSE;
}

void COODCommonDoc::OnWindowClose() 
{
	// TODO: Add your command handler code here
	if (theAppPtr->runAsServerFlag) {
		mainFramePtr->onClose();
		return; // 2014 OODesigner 수정   FALSE;
	}

	if (IsModified()) {
		m_strPathName = GetTitle();
		char buffer[BUFSIZ];
		sprintf_s(buffer,BUFSIZ,"Do you want to save %s diagram ?",m_strPathName);
		int ans = YesNoCancelMsg(buffer);
		if (ans == IDCANCEL) return; // 2014 OODesigner 수정   TRUE;
		if (ans == IDYES) {
			OnFileSave();
		}
	}
	// shut it down
	OnCloseDocument();
		// this should destroy the document
	return; // 2014 OODesigner 수정   FALSE;
}

void COODCommonDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	_comment.RemoveAll();
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		aFigure->clearLists();
		aFigure = _figures->getNext();
	}
	aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		delete aFigure;
		aFigure = _figures->getNext();
	}
	_figures->clear();
	COODDoc::DeleteContents();
}

void COODCommonDoc::clearContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	_comment.RemoveAll();
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		aFigure->clearLists();
		aFigure = _figures->getNext();
	}
	aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		delete aFigure;
		aFigure = _figures->getNext();
	}
	_figures->clear();
	COODCntrlItemList *pList = new COODCntrlItemList();
	POSITION itemPos = GetStartPosition();
	while(itemPos != NULL) {
		CDocItem *pDocItem = GetNextClientItem(itemPos);
		if (pDocItem != NULL) {
			pList->addTail((COODCntrlItem *)pDocItem);
		}
	}

	COODCntrlItem *pDocItem = pList->getFirst();
	while (pDocItem != NIL) {
		pDocItem->Delete();
		pDocItem = pList->getNext();
	}
	pList->clear();
	delete pList;

	setModifiedFlag(TRUE);     // make clean
}

void COODCommonDoc::replaceFieldTextContent(CString &className,ClassTemplate *aClass,COODView *aView)
{
	Figure* aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *pClass = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			pClass->getName(buffer,BUFSIZ);
			if (className.CompareNoCase(buffer) == 0) {
				if (aClass != NIL) {
					pClass->replaceFieldTextContent(aClass,aClass->controller());
				} else {
					pClass->replaceFieldTextContent(aClass,aView);
				}
			}
		}
		aFigure = _figures->getNext();
	}
}

ClassContent *COODCommonDoc::registerClassContent(CString &className,ClassTemplate *theClass)
{
	ClassContent *aContent = getClassContentFor(className,theClass);
	if (aContent != NIL) {
		aContent->setClassContentFrom(theClass);
		return aContent;
	}
	aContent = new ClassContent();
	aContent->setName(className);
	aContent->setClassContentFrom(theClass);
	return aContent;
}

ClassContent* COODCommonDoc::getClassContentFor(CString &className,ClassTemplate *theClass)
{
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *pClass = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			pClass->getName(buffer,BUFSIZ);
			if (className.CompareNoCase(buffer) == 0 &&
				pClass != theClass) 
				return pClass->classContent();
		}
		aFigure = _figures->getNext();
	}
	return NIL;
}

/* 이 함수에서는 현재 도큐먼트의 내용을 통채로(포인터 그대로) 패키지로 옮긴후
   자기 자신의 figures 내용을 clear 시킨다.
*/
void COODCommonDoc::copyDocumentContentsTo(FigureLibrary *toPackage,COODDoc *toDoc)
{
	copyOleItemsTo(toDoc);

	POSITION pos = _comment.GetHeadPosition();
	while (pos != NULL) {
		CString aLine = _comment.GetNext(pos);
		toPackage->comment()->AddTail(aLine);
	} 
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		toPackage->figures()->addTail(aFigure);
		aFigure = _figures->getNext();
	}
	_figures->clear(); // 현재 도큐먼트 내용 clear 시킴, 객체는 delete 시키면 안됨
	toPackage->setZoomRatioX(_zoomRatioX);
	toPackage->setZoomRatioY(_zoomRatioY);
}

void COODCommonDoc::copyDocumentContentsTo(COODCommonDoc *toDoc)
{
	copyOleItemsTo(toDoc);

	POSITION pos = _comment.GetHeadPosition();
	while (pos != NULL) {
		CString aLine = _comment.GetNext(pos);
		toDoc->_comment.AddTail(aLine);
	} 
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		toDoc->_figures->addTail(aFigure);
		aFigure = _figures->getNext();
	}
	_figures->clear(); // 현재 도큐먼트 내용 clear 시킴, 객체는 delete 시키면 안됨
	toDoc->_zoomRatioX = _zoomRatioX;
	toDoc->_zoomRatioY = _zoomRatioY;
}

void COODCommonDoc::setShapeBackground(COLORREF bkColor)
{
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		aFigure->setBackground(bkColor);
		aFigure = _figures->getNext();
	}
	COODView *pView = getFirstView();
	if (pView != NIL) pView->Invalidate();
}

void COODCommonDoc::setShapeForeground(COLORREF fgColor)
{
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		aFigure->setForeground(fgColor);
		aFigure = _figures->getNext();
	}
	COODView *pView = getFirstView();
	if (pView != NIL) pView->Invalidate();
}

void COODCommonDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	if (!theAppPtr->runAsServerFlag) {
		m_strPathName = GetTitle();
		m_strPathName = theAppPtr->workspaceDir + "\\" + m_strPathName;
		COODDoc::OnSaveDocument(m_strPathName);	
		setModifiedFlag(FALSE);
	} else {
		char lpszPathName[BUFSIZ];
		if (m_strPathName.IsEmpty()) {
			strcpy_s(lpszPathName,BUFSIZ,m_strTitle); // Embedding Case
			serverSaveDocument(lpszPathName);
		} else {
			COODDoc::OnFileSave(); // Linking Case
			SetModifiedFlag(FALSE);
		}
	}
}

void COODCommonDoc::serverSaveDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = new CFile();
	pFile->Open(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);

	if (pFile == NULL)
	{
		ReportSaveLoadException(lpszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return;
	}

	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_pDocument = this;
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);

		TRY
		{
			ReportSaveLoadException(lpszPathName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		}
		END_TRY
		DELETE_EXCEPTION(e);
		return;
	}
	END_CATCH_ALL

#ifdef _MAC
	RecordDataFileOwner(lpszPathName, AfxGetAppName());
#endif
}

void COODCommonDoc::serverOnFileSaveAs()
{
	CString newName = "";
	if (newName.IsEmpty())
	{
		CDocTemplate* pTemplate = GetDocTemplate();
		ASSERT(pTemplate != NULL);

		newName = newName + "Untitled" + getExtension();
		if (!AfxGetApp()->DoPromptFileName(newName,
		  AFX_IDS_SAVEFILECOPY,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
			return;       // don't even attempt to save
	}
	if (newName.Right(_EXT_LEN5).CompareNoCase(getExtension()) != 0) {
		newName = newName + getExtension();
	}

	CWaitCursor wait;

	serverSaveDocument(newName);
}

void COODCommonDoc::usualOnFileSaveAs() 
{
	LPCTSTR lpszPathName = NULL;
	BOOL bReplace = TRUE;
	CString newName = lpszPathName;
	if (newName.IsEmpty())
	{
		CDocTemplate* pTemplate = GetDocTemplate();
		ASSERT(pTemplate != NULL);

		newName = m_strPathName;
		if (bReplace && newName.IsEmpty())
		{
			newName = m_strTitle;
#ifndef _MAC
			// check for dubious filename
			int iBad = newName.FindOneOf(_T(" #%;/\\"));
#else
			int iBad = newName.FindOneOf(_T(":"));
#endif
			if (iBad != -1)
				newName.ReleaseBuffer(iBad);

#ifndef _MAC
			// append the default suffix if there is one
			CString strExt;
			if (pTemplate->GetDocString(strExt, CDocTemplate::filterExt) &&
			  !strExt.IsEmpty())
			{
				ASSERT(strExt[0] == '.');
				newName += strExt;
			}
#endif
		}

		if (!AfxGetApp()->DoPromptFileName(newName,
		  bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
			return;       // don't even attempt to save
	}

	if (newName.Right(_EXT_LEN5).CompareNoCase(getExtension()) != 0) {
		newName = newName + getExtension();
	}

	CWaitCursor wait;

	if (!OnSaveDocument(newName))
	{
		if (lpszPathName == NULL)
		{
			// be sure to delete the file
			TRY
			{
				CFile::Remove(newName);
			}
			CATCH_ALL(e)
			{
				TRACE0("Warning: failed to delete file after failed SaveAs.\n");
				DELETE_EXCEPTION(e);
			}
			END_CATCH_ALL
		}
		return;
	}

	// reset the title and change the document name
	if (bReplace)
		SetPathName(newName);
}

void COODCommonDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	if (!theAppPtr->runAsServerFlag) {
		usualOnFileSaveAs();
	} else {
		serverOnFileSaveAs();
	}
}

void COODCommonDoc::onFileSave() {
	OnFileSave();
	setModifiedFlag(FALSE);
}

void COODCommonDoc::OnFileClose() 
{
	// TODO: Add your command handler code here
	OnWindowClose();
}

void COODCommonDoc::OnDeactivate() 
{
	// TODO: Add your specialized code here and/or call the base class
	COODDoc::OnDeactivate();

	//--- 또 하나의 임무: 스크롤바를 원위치 시키기 위한 작업 ...
	// 이 코드들을 위로 옮기면 안됨
	POSITION pos = GetFirstViewPosition();
	CView* pFirstView = GetNextView(pos);
	if (pFirstView->IsKindOf(RUNTIME_CLASS(COODView))) {
		((COODView *)pFirstView)->setFirstOnDrawCall(TRUE);
	}
}


BOOL COODCommonDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (theAppPtr->runAsServerFlag) {
		if (IsModified()) {
			if (m_strPathName.IsEmpty()) {
				return COleServerDoc::SaveModified(); // Embedding Case
			} else {
				char buffer[BUFSIZ];
				sprintf_s(buffer,BUFSIZ,"Do you want to save %s diagram ?",m_strPathName);
				int ans = YesNoCancelMsg(buffer);
				if (ans == IDCANCEL) return TRUE;
				if (ans == IDYES) {
					COODDoc::DoFileSave(); // Linking Case
				}
				SetModifiedFlag(FALSE);
			}
		}
	}
	return COleServerDoc::SaveModified();
}
