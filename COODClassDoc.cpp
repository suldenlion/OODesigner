// COODClassDoc.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "AfxDeleteExceptionMacro.h"
#include "COODClassDoc.h"
#include "CMainFrame.h"
#include "CClassFrm.h"
#include "CClassView.h"
#include "FigureList.h"
#include "Figure.h"
#include "COODView.h"
#include "PackageLibrary.h"
#include "ClassFigureLibrary.h"
#include "RelationshipInfoTupleList.h"
#include "KtgMacro.h"
#include "FigureLibrary.h"
#include "UnsignedLong.h"
#include "ClassTemplate.h"
#include "ClassLibrary.h"
#include "ClassContent.h"
#include "TextContent.h"
#include "CClassDeleteDlg.h"
#include "Generalization.h"
#include "Aggregation.h"
#include "Dependency.h"
#include "COODCommonDoc.h"

#include <afxcom_.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COODClassDoc

IMPLEMENT_DYNCREATE(COODClassDoc, COODDoc)

COODClassDoc::COODClassDoc()
: COODDoc()
{
	classFiguresLibrary = new ClassFigureLibrary();
	allClassContents = new PackageLibrary();
	generalizationLibrary = new RelationshipInfoTupleList();
	aggregationLibrary = new RelationshipInfoTupleList();
	dependencyLibrary = new RelationshipInfoTupleList();
	recentViewName = "";
	_figureLibraryToSave = NIL;
}

BOOL COODClassDoc::OnNewDocument()
{
	if (!COODDoc::OnNewDocument())
		return FALSE;
	return TRUE;
}

COODClassDoc::~COODClassDoc()
{
	_figureLibraryToSave = NIL;
	if (classFiguresLibrary != NIL) {
		delete classFiguresLibrary; classFiguresLibrary = NIL;
	}
	if (allClassContents != NIL) {
		delete allClassContents; allClassContents = NIL;
	}
	if (generalizationLibrary != NIL) {
		delete generalizationLibrary; generalizationLibrary = NIL;
	}
	if (aggregationLibrary != NIL) {
		delete aggregationLibrary; aggregationLibrary = NIL;
	}
	if (dependencyLibrary != NIL) {
		delete dependencyLibrary; dependencyLibrary = NIL;
	}
}

FigureList *COODClassDoc::figures(CString& title)
{
	if (title.GetLength() == 0) return NIL;
	return classFiguresLibrary->figures(title);
}

FigureLibrary *COODClassDoc::getPackage(CString &title)
{
	if (title.GetLength() == 0) return NIL;
	return classFiguresLibrary->getPackage(title);
}

FigureLibrary *COODClassDoc::addPackage(CString &title)
{
	if (title.GetLength() == 0) return NIL;
	return classFiguresLibrary->addPackage(title);
}

FigureList *COODClassDoc::figures()
{
	FigureLibrary *lib = classFiguresLibrary->getFirst();
	if (lib == NIL) return NIL;
	return lib->figures();
}

int COODClassDoc::zoomRatioX()
{
	FigureLibrary *lib = classFiguresLibrary->getFirst();
	if (lib == NIL) return 100;
	return lib->zoomRatioX();
}

int COODClassDoc::zoomRatioY()
{
	FigureLibrary *lib = classFiguresLibrary->getFirst();
	if (lib == NIL) return 100;
	return lib->zoomRatioY();
}

int COODClassDoc::zoomRatioX(CString& title)
{
	if (title.GetLength() == 0) return 100;
	return classFiguresLibrary->zoomRatioX(title);
}

int COODClassDoc::zoomRatioY(CString& title)
{
	if (title.GetLength() == 0) return 100;
	return classFiguresLibrary->zoomRatioY(title);
}

void COODClassDoc::setZoomRatioX(CString& title,int zoomX)
{
	if (title.GetLength() == 0) return;
	classFiguresLibrary->setZoomRatioX(title,zoomX);
	return;
}

void COODClassDoc::setZoomRatioY(CString& title,int zoomY)
{
	if (title.GetLength() == 0) return;
	classFiguresLibrary->setZoomRatioY(title,zoomY);
	return;
}

int COODClassDoc::originX()
{
	FigureLibrary *lib = classFiguresLibrary->getFirst();
	if (lib == NIL) return 0;
	return lib->originX();
}

int COODClassDoc::originY()
{
	FigureLibrary *lib = classFiguresLibrary->getFirst();
	if (lib == NIL) return 0;
	return lib->originY();
}

int COODClassDoc::originX(CString& title)
{
	if (title.GetLength() == 0) return 100;
	return classFiguresLibrary->originX(title);
}

int COODClassDoc::originY(CString& title)
{
	if (title.GetLength() == 0) return 100;
	return classFiguresLibrary->originY(title);
}

void COODClassDoc::setOriginX(CString& title,int x)
{
	if (title.GetLength() == 0) return;
	classFiguresLibrary->setOriginX(title,x);
	return;
}

void COODClassDoc::setOriginY(CString& title,int y)
{
	if (title.GetLength() == 0) return;
	classFiguresLibrary->setOriginY(title,y);
	return;
}

void COODClassDoc::tryToDeleteClassContentFromRepository(CString &className)
{
	CString pName; // 뷰에서의 패키지 이름
	ClassFigureLibrary *theLibrary = theAppPtr->pCOODClassDoc->getClassFiguresLibrary();
	BOOL exists = theLibrary->hasClassTemplate(className,pName);

	if (exists == TRUE) {
		return;
	}

	if (theAppPtr->classDelYesAlwaysFlag == TRUE) {
		PackageLibrary *allContents = theAppPtr->pCOODClassDoc->getAllClassContents();
		CString packageName; // 라이브러리에서의 패키지 이름
		allContents->getPackageNameFor(className,packageName);
		allContents->deleteClassContent(packageName,className);
		mainFramePtr->m_wndTreeBar.deleteClass(packageName,className);
		theAppPtr->pCOODClassDoc->deleteAllRelationshipWithClassName(className);
		theAppPtr->pCOODClassDoc->SetModifiedFlag();
		return;
	}

	CClassDeleteDlg aDlg(className);
	UINT ans = aDlg.DoModal();
	if (ans == IDYES || ans == IDYESALWAYS) {
		PackageLibrary *allContents = theAppPtr->pCOODClassDoc->getAllClassContents();
		CString packageName; // 라이브러리에서의 패키지 이름
		allContents->getPackageNameFor(className,packageName);
		allContents->deleteClassContent(packageName,className);
		mainFramePtr->m_wndTreeBar.deleteClass(packageName,className);
		theAppPtr->pCOODClassDoc->deleteAllRelationshipWithClassName(className);
		theAppPtr->pCOODClassDoc->SetModifiedFlag();
	}
}

BOOL COODClassDoc::tryToRemoveRelationshipInfo(RelationshipInfoTupleList *library,char *major,char *minor,UnsignedLong *identity,CString &packName)
{
	if (classFiguresLibrary->hasRelationshipYet(identity,major,minor,packName) == TRUE) {
		return FALSE;
	}
	library->removeRelationshipInfo(major,minor);
	return TRUE;
}

void COODClassDoc::deleteAllRelationshipWithClassName(CString className)
{
	generalizationLibrary->removeRelationshipInfo(className);
	aggregationLibrary->removeRelationshipInfo(className);
	dependencyLibrary->removeRelationshipInfo(className);
}

CClassFrm *COODClassDoc::findClassFrame(CString &title)
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)	{
		CView* pView = GetNextView(pos);
		ASSERT_VALID(pView);
		if (!pView->IsKindOf(RUNTIME_CLASS(CClassView))) return NIL;
		CClassView *theView = (CClassView *)pView;
		if (title.CompareNoCase(theView->viewTitle) == 0) {
			CFrameWnd *theFrame = pView->GetParentFrame();
			ASSERT_VALID(theFrame);
			if (!theFrame->IsKindOf(RUNTIME_CLASS(CClassFrm))) return NIL;
			return (CClassFrm *)theFrame;
		}
	}
	return NIL;
}

void COODClassDoc::destroyClassFrameWindow(CString &title)
{
	classFiguresLibrary->deletePackage(title);
	removeViewName(title);
	CClassFrm *pFrame = findClassFrame(title);
	if (pFrame == NIL) return;
	CView *pView = pFrame->GetActiveView();
	if (pView != NULL &&
		pView->IsKindOf(RUNTIME_CLASS(COODView))) {
		((COODView *)pView)->setToBeDestroyed();
	}
	PreCloseFrame(pFrame);
	pFrame->DestroyWindow();
}

BOOL COODClassDoc::ifClassViewAlreadyExists(CString& title)
{
	CClassFrm *pFrame = findClassFrame(title);
	if (pFrame == NIL) 
		return FALSE;
	else {
		pFrame->MDIActivate();
		return TRUE;
	}
}

void COODClassDoc::hideClassViewIfAlreadyExists(CString& title)
{
	CClassFrm *pFrame = findClassFrame(title);
	if (pFrame == NULL) return;
	if (!pFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) return;
	ASSERT_VALID(pFrame);
	removeViewName(pFrame);
	PreCloseFrame(pFrame);
	pFrame->DestroyWindow();
}

void COODClassDoc::registerOrReplaceClassContent(CString &packName,FigureLibrary *aPackage)
{
	CStringList classNamesRegistered;
	// (1) 우선 aPackage에 있는 클래스가 이미 ClassLibrary에 존재하는 경우 처리
	FigureList *figures = aPackage->figures();
	Figure *aFigure = figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *pClass = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			pClass->getName(buffer,BUFSIZ);
			ClassLibrary *aLibrary = allClassContents->getFirst();
			while(aLibrary != NIL) {
				CString className = buffer;
				ClassContent *oldContent = aLibrary->getClassContentFor(className);
				if (oldContent != NIL) {
					if (classNamesRegistered.Find(className) == NULL) {
						classNamesRegistered.AddTail(className);
					}
					TextContent *varContent = oldContent->getVarContent();
					TextContent *methodContent = oldContent->getMethodContent();
					if (varContent != NIL) {
						delete varContent;
						oldContent->setVarContent(NIL);
					}
					if (methodContent != NIL) {
						delete methodContent;
						oldContent->setMethodContent(NIL);
					}
				}
				aLibrary = allClassContents->getNext();
			}
		}
		aFigure = figures->getNext();
	}
	aFigure = figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *pClass = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			pClass->getName(buffer,BUFSIZ);
			ClassLibrary *aLibrary = allClassContents->getFirst();
			while(aLibrary != NIL) {
				CString className = buffer;
				ClassContent *oldContent = aLibrary->getClassContentFor(className);
				if (oldContent != NIL) {
					oldContent->setVarContent(pClass->getVarContent());
					oldContent->setMethodContent(pClass->getMethodContent());
				}
				aLibrary = allClassContents->getNext();
			}
		}
		aFigure = figures->getNext();
	}
	aFigure = figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *pClass = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			pClass->getName(buffer,BUFSIZ);
			ClassLibrary *aLibrary = allClassContents->getFirst();
			while(aLibrary != NIL) {
				CString className = buffer;
				ClassContent *oldContent = aLibrary->getClassContentFor(className);
				if (oldContent != NIL) {
					pClass->setClassContent(oldContent);
				}
				aLibrary = allClassContents->getNext();
			}
		}
		aFigure = figures->getNext();
	}

	// 모든 클래스 그림들에 대해서 텍스트 내용을 다시 설정하고 그림 크기 조정 
	FigureLibrary *figLibrary = classFiguresLibrary->getFirst();
	while(figLibrary != NIL) {
		FigureList *figs = figLibrary->figures();
		Figure *aFigure = figs->getFirst();
		while(aFigure != NIL) {
			if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
				ClassTemplate *pClass = (ClassTemplate *)aFigure;
				pClass->resetAndReshapeClassTextContentFromClassContent(packName);
			}
			aFigure = figs->getNext();
		}
		figLibrary = classFiguresLibrary->getNext();
	}

	// 새로운 이름의 클래스 등록
	ClassLibrary *thePack = allClassContents->getPackage(packName);
	aFigure = figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *pClass = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			pClass->getName(buffer,BUFSIZ);
			if (classNamesRegistered.Find(buffer) == NULL) {
				pClass->justRegisterClassContent(thePack);
				classNamesRegistered.AddTail(buffer);
			}
		}
		aFigure = figures->getNext();
	}

	aFigure = figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMGENERALIZATION)) {
			Generalization *pGen = (Generalization *) aFigure;
			pGen->registerGeneralizationInfoEx();
		} else if (aFigure->whoAreYou()->equals(IAMAGGREGATION)) {
			Aggregation *pAgg = (Aggregation *) aFigure;
			pAgg->registerAggregationInfoEx();
		} else if (aFigure->whoAreYou()->equals(IAMDEPENDENCY)) {
			Dependency *pDep = (Dependency *) aFigure;
			pDep->registerDependencyInfoEx();
		}
		aFigure = figures->getNext();
	}

	UpdateAllViews((CView *)NIL);
}

void COODClassDoc::setShapeBackground(COLORREF bkColor)
{
	FigureLibrary *figLibrary = classFiguresLibrary->getFirst();
	while(figLibrary != NIL) {
		FigureList *figs = figLibrary->figures();
		Figure *aFigure = figs->getFirst();
		while(aFigure != NIL) {
			aFigure->setBackground(bkColor);
			aFigure = figs->getNext();
		}
		figLibrary = classFiguresLibrary->getNext();
	}
	UpdateAllViews(NULL);
}

void COODClassDoc::setShapeForeground(COLORREF fgColor)
{
	FigureLibrary *figLibrary = classFiguresLibrary->getFirst();
	while(figLibrary != NIL) {
		FigureList *figs = figLibrary->figures();
		Figure *aFigure = figs->getFirst();
		while(aFigure != NIL) {
			aFigure->setForeground(fgColor);
			aFigure = figs->getNext();
		}
		figLibrary = classFiguresLibrary->getNext();
	}
	UpdateAllViews(NULL);
}

FigureLibrary* COODClassDoc::clearPackage(CString &title)
{
	return classFiguresLibrary->clearPackage(title);
}

BEGIN_MESSAGE_MAP(COODClassDoc, COODDoc)
	//{{AFX_MSG_MAP(COODClassDoc)
	ON_COMMAND(ID_WINDOW_CLOSE, OnWindowClose)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_FILE_SAVE_AS_PACKAGE, OnFileSaveAsPackage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODClassDoc diagnostics

#ifdef _DEBUG
void COODClassDoc::AssertValid() const
{
	COODDoc::AssertValid();
}

void COODClassDoc::Dump(CDumpContext& dc) const
{
	COODDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COODClassDoc serialization

void COODClassDoc::Serialize(CArchive& ar)
{
	BOOL reservedFlag0COODClassDoc = FALSE;
	BOOL reservedFlag1COODClassDoc = FALSE;
	BOOL reservedFlag2COODClassDoc = FALSE;
	BOOL reservedFlag3COODClassDoc = FALSE;
	BOOL reservedFlag4COODClassDoc = FALSE;
	UINT reservedInt0COODClassDoc = 0;
	UINT reservedInt1COODClassDoc = 0;
	UINT reservedInt2COODClassDoc = 0;
	UINT reservedInt3COODClassDoc = 0;
	UINT reservedInt4COODClassDoc = 0;
	CString reservedString0COODClassDoc = _T("");
	CString reservedString1COODClassDoc = _T("");
	CString reservedString2COODClassDoc = _T("");
	CString reservedString3COODClassDoc = _T("");
	CString reservedString4COODClassDoc = _T("");

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		if (_figureLibraryToSave == NIL) {
			COODDoc::Serialize(ar);

			activeViewNames.Serialize(ar);
			theAppPtr->cppHeaderFileAbsMacros.Serialize(ar);
			theAppPtr->cppSourceFileAbsMacros.Serialize(ar);
			theAppPtr->vcppHeaderFileAbsMacros.Serialize(ar);
			theAppPtr->vcppSourceFileAbsMacros.Serialize(ar);
			ar << theAppPtr->workspaceName; 
			ar << theAppPtr->workspaceDir;
			ar << theAppPtr->projectLanguage;
			ar << theAppPtr->projectHFExtension;
			ar << theAppPtr->projectSFExtension;
			ar << theAppPtr->projectInheritanceTreeOrient;
			ar << (BYTE) theAppPtr->projectDrawInheritanceTreeFlag;
			ar << theAppPtr->projectCodegenTargetDir;
			ar << theAppPtr->projectReverseSourceDir;
			ar << theAppPtr->projectAuthor;
			ar << theAppPtr->projectOrganization;
			ar << recentViewName;
			ar << classFiguresLibrary << allClassContents;
			ar << generalizationLibrary << aggregationLibrary << dependencyLibrary;

			ar << (BYTE)reservedFlag0COODClassDoc;
			ar << (BYTE)reservedFlag1COODClassDoc;
			ar << (BYTE)reservedFlag2COODClassDoc;
			ar << (BYTE)reservedFlag3COODClassDoc;
			ar << (BYTE)reservedFlag4COODClassDoc;
			ar << (LONG)reservedInt0COODClassDoc;
			ar << (LONG)reservedInt1COODClassDoc;
			ar << (LONG)reservedInt2COODClassDoc;
			ar << (LONG)reservedInt3COODClassDoc;
			ar << (LONG)reservedInt4COODClassDoc;
			ar << reservedString0COODClassDoc;
			ar << reservedString1COODClassDoc;
			ar << reservedString2COODClassDoc;
			ar << reservedString3COODClassDoc;
			ar << reservedString4COODClassDoc;
		} else { // Save a package
			COODDoc::SerializeForPackageOnly(ar,_figureLibraryToSave->packageName());

			/* 이건 실패작이지만 ... 나름대로 아까워서리 ...
			COODCommonDoc* docPtr = (COODCommonDoc*)RUNTIME_CLASS(COODCommonDoc)->CreateObject();
			if (docPtr == NULL)
			{
				TRACE0("Warning: Dynamic create of document type COODCommonDoc failed.\n");
				COODDoc::Serialize(ar);
			} else {
				docPtr->setRootStg("temp");
				docPtr->m_bAutoDelete = FALSE;   // 내가 직접 없앨 것이기 때문에
				copyOleItemsTo((COODDoc *)docPtr,&_figureLibraryToSave->packageName());
				docPtr->Serialize(ar);
				docPtr->DeleteContents();
				delete docPtr;
			}
			*/

			// COODCommonDoc 와 같은 양식으로 저장
			_figureLibraryToSave->comment()->Serialize(ar);
			ar << _figureLibraryToSave->packageName();
			ar << _figureLibraryToSave->figures();
			ar << (LONG)_figureLibraryToSave->zoomRatioX();
			ar << (LONG)_figureLibraryToSave->zoomRatioY();
			ar << (LONG)_figureLibraryToSave->originX();
			ar << (LONG)_figureLibraryToSave->originY();

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
	}
	else 
	{ 
		COODDoc::Serialize(ar);
		// TODO: add loading code here
		if (theAppPtr->fileVersionNo.CompareNoCase("2200") != 0 &&
			theAppPtr->fileVersionNo.CompareNoCase("0300") < 0) {
			ErrorMsg("Verion mismatch:\r\n\
This verion does not support old document verion\r\n\
less than 0300 any more.");
			return;
		}
		activeViewNames.Serialize(ar);
		theAppPtr->cppHeaderFileAbsMacros.RemoveAll();
		theAppPtr->cppSourceFileAbsMacros.RemoveAll();
		theAppPtr->vcppHeaderFileAbsMacros.RemoveAll();
		theAppPtr->vcppSourceFileAbsMacros.RemoveAll();
		theAppPtr->cppHeaderFileAbsMacros.Serialize(ar);
		theAppPtr->cppSourceFileAbsMacros.Serialize(ar);
		theAppPtr->vcppHeaderFileAbsMacros.Serialize(ar);
		theAppPtr->vcppSourceFileAbsMacros.Serialize(ar);
		ar >> theAppPtr->workspaceName; 
		ar >> theAppPtr->workspaceDir;
		ar >> theAppPtr->projectLanguage;
		ar >> theAppPtr->projectHFExtension;
		ar >> theAppPtr->projectSFExtension;
		ar >> theAppPtr->projectInheritanceTreeOrient;
		ar >> (BYTE&) theAppPtr->projectDrawInheritanceTreeFlag;
		ar >> theAppPtr->projectCodegenTargetDir;
		ar >> theAppPtr->projectReverseSourceDir;
		ar >> theAppPtr->projectAuthor;
		ar >> theAppPtr->projectOrganization;
		ar >> recentViewName;

		if (classFiguresLibrary) delete classFiguresLibrary;
		if (allClassContents) delete allClassContents;
		if (generalizationLibrary) delete generalizationLibrary;
		if (aggregationLibrary) delete aggregationLibrary;
		if (dependencyLibrary) delete dependencyLibrary;
		ar >> classFiguresLibrary >> allClassContents;
		ar >> generalizationLibrary >> aggregationLibrary >> dependencyLibrary;

		ar >> (BYTE&)reservedFlag0COODClassDoc;
		ar >> (BYTE&)reservedFlag1COODClassDoc;
		ar >> (BYTE&)reservedFlag2COODClassDoc;
		ar >> (BYTE&)reservedFlag3COODClassDoc;
		ar >> (BYTE&)reservedFlag4COODClassDoc;
		ar >> (LONG&)reservedInt0COODClassDoc;
		ar >> (LONG&)reservedInt1COODClassDoc;
		ar >> (LONG&)reservedInt2COODClassDoc;
		ar >> (LONG&)reservedInt3COODClassDoc;
		ar >> (LONG&)reservedInt4COODClassDoc;
		ar >> reservedString0COODClassDoc;
		ar >> reservedString1COODClassDoc;
		ar >> reservedString2COODClassDoc;
		ar >> reservedString3COODClassDoc;
		ar >> reservedString4COODClassDoc;
	}
//	COleServerDoc::Serialize(ar);
}

void COODClassDoc::setModifiedFlag(BOOL flag)
{
	COleServerDoc::SetModifiedFlag(flag); // 이 줄은 COODDoc::SetModifiedFlag(flag)로 바꾸면 절대 안됨 
	CMDIChildWnd *pWnd = mainFramePtr->MDIGetActive();
	if (pWnd == NULL) return;
	if (pWnd->IsKindOf(RUNTIME_CLASS(CClassFrm))) {
		CChildFrm *pFrame = (CChildFrm *)pWnd;
		CString currentTitle = pFrame->frameTitle;
		if (flag) {
			int len = currentTitle.GetLength();
			TCHAR c = currentTitle.GetAt(len-1);
			if (c == '*') return;
			pFrame->frameTitle = pFrame->frameTitle + " *";
			pFrame->OnUpdateFrameTitle(TRUE);
		} else {
			POSITION pos = GetFirstViewPosition();
			while (pos != NULL)	{
				CView* pView = GetNextView(pos);
				ASSERT_VALID(pView);
				if (!pView->IsKindOf(RUNTIME_CLASS(CClassView))) break;
				CFrameWnd *theFrame = pView->GetParentFrame();
				ASSERT_VALID(theFrame);
				if (!theFrame->IsKindOf(RUNTIME_CLASS(CClassFrm))) break;
				CChildFrm *pFrame = (CChildFrm *)theFrame;
				CString currentTitle = pFrame->frameTitle;
				int len = currentTitle.GetLength();
				TCHAR c = currentTitle.GetAt(len-1);
				if (c == '*') {
					pFrame->frameTitle = pFrame->frameTitle.Left(len-2);
					pFrame->OnUpdateFrameTitle(TRUE);
				}
			}
		}
	}
}

void COODClassDoc::setModifiedFlagForAllView(BOOL flag)
{
	COleServerDoc::SetModifiedFlag(flag); // 이 줄은 COODDoc::SetModifiedFlag(flag)로 바꾸면 절대 안됨 
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)	{
		CView* pView = GetNextView(pos);
		ASSERT_VALID(pView);
		if (!pView->IsKindOf(RUNTIME_CLASS(CClassView))) break;
		CFrameWnd *theFrame = pView->GetParentFrame();
		ASSERT_VALID(theFrame);
		if (!theFrame->IsKindOf(RUNTIME_CLASS(CClassFrm))) break;
		CChildFrm *pFrame = (CChildFrm *)theFrame;
		CString currentTitle = pFrame->frameTitle;
		if (flag == TRUE) {
			int len = currentTitle.GetLength();
			TCHAR c = currentTitle.GetAt(len-1);
			if (c == '*') return;
			pFrame->frameTitle = pFrame->frameTitle + " *";
			pFrame->OnUpdateFrameTitle(TRUE);
		} else {
			int len = currentTitle.GetLength();
			TCHAR c = currentTitle.GetAt(len-1);
			if (c == '*') {
				pFrame->frameTitle = pFrame->frameTitle.Left(len-2);
				pFrame->OnUpdateFrameTitle(TRUE);
			}
		}
	}
}

void COODClassDoc::removeViewNameAt(POSITION pos)
{
	activeViewNames.RemoveAt(pos);
	SetModifiedFlag();
}

void COODClassDoc::removeViewName(CString &viewName)
{
	POSITION pos = activeViewNames.Find(viewName);
	if (pos != NULL) {
		removeViewNameAt(pos);
	}
}

void COODClassDoc::insertViewName(CString& name)
{
	activeViewNames.AddTail(name);
	SetModifiedFlag();
}

void COODClassDoc::removeViewName(CFrameWnd* pFrame)
{
	CView *activeView = pFrame->GetActiveView();
	if (activeView == NULL) return;
	if (activeView->IsKindOf(RUNTIME_CLASS(COODView))) {
		COODView *theView = (COODView *)activeView;
		POSITION pos = activeViewNames.Find(theView->viewTitle);
		if (pos != NULL) {
			removeViewNameAt(pos);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// COODClassDoc commands

BOOL COODClassDoc::closeAllWindow(BOOL closeWorkspace)
{
	if (closeWorkspace == TRUE && IsModified()) {
		m_strPathName = GetTitle();
		char buffer[BUFSIZ];
		sprintf_s(buffer,BUFSIZ,"Do you want to save the workspace ?");
		int ans = YesNoCancelMsg(buffer);
		if (ans == IDCANCEL) return TRUE;
		if (ans == IDYES) {
			onFileSaveClassDocument();
		}
	}
	while (!m_viewList.IsEmpty())
	{
		// get frame attached to the view
		CView* pView = (CView*)m_viewList.GetHead();
		ASSERT_VALID(pView);
		CFrameWnd* pFrame = pView->GetParentFrame();
		ASSERT_VALID(pFrame);

		if (closeWorkspace != TRUE) {
			removeViewName(pFrame);
		}
		// and close it
		PreCloseFrame(pFrame);
		pFrame->DestroyWindow();
			// will destroy the view as well
	}
	return FALSE;
}

void COODClassDoc::OnWindowClose() 
{
	// TODO: Add your command handler code here
	CMDIChildWnd* currentFrame = mainFramePtr->MDIGetActive(); 
	if (currentFrame == NIL) return;
	if (!currentFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) return;
	ASSERT_VALID(currentFrame);
	removeViewName(currentFrame);
	PreCloseFrame(currentFrame);
	currentFrame->DestroyWindow();
} 

void COODClassDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (classFiguresLibrary != NIL) {
		delete classFiguresLibrary; classFiguresLibrary = NIL;
	}
	if (allClassContents != NIL) {
		delete allClassContents; allClassContents = NIL;
	}	
	if (generalizationLibrary != NIL) {
		delete generalizationLibrary; generalizationLibrary = NIL;
	}
	if (aggregationLibrary != NIL) {
		delete aggregationLibrary; aggregationLibrary = NIL;
	}
	if (dependencyLibrary != NIL) {
		delete dependencyLibrary; dependencyLibrary = NIL;
	}
	classFiguresLibrary = new ClassFigureLibrary();
	allClassContents = new PackageLibrary();
	generalizationLibrary = new RelationshipInfoTupleList();
	aggregationLibrary = new RelationshipInfoTupleList();
	dependencyLibrary = new RelationshipInfoTupleList();

	activeViewNames.RemoveAll();

	COODDoc::DeleteContents();
}

void COODClassDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	// 이 함수에서는 현재 패키지만 save 함

	CMDIChildWnd *pWnd = mainFramePtr->MDIGetActive();
	if (pWnd == NULL) return;
	if (!pWnd->IsKindOf(RUNTIME_CLASS(CClassFrm))) return;
	CChildFrm *pFrame = (CChildFrm *)pWnd;
	CView *activeView = pFrame->GetActiveView();
	if (activeView == NULL) return;
	if (!activeView->IsKindOf(RUNTIME_CLASS(COODView))) return;
	COODView *theView = (COODView *)activeView;
	CString currentTitle = theView->viewTitle;

	BOOL bModified = IsModified();
	m_strPathName = theAppPtr->workspaceDir + "\\" + currentTitle;
	setModifiedFlag(FALSE); // 이 패키지 화면은 세이브 된 거로 표시 함과 동시에 ...
	COleServerDoc::SetModifiedFlag(TRUE); // 원본 도큐먼트는 세이브되지 않은 거처럼 ...
	_figureLibraryToSave = classFiguresLibrary->getPackage(currentTitle);

	OnSaveDocument(m_strPathName);	

	_figureLibraryToSave = NIL;
	COleServerDoc::SetModifiedFlag(bModified);
}

void COODClassDoc::onFileSaveClassDocument() 
{
	// 이 함수에서는 클래스 도큐먼트 몽땅 save 함
	m_strPathName = theAppPtr->workspaceDir + "\\" + theAppPtr->workspaceName+_OOD_EXT;
	COleServerDoc::SetModifiedFlag(TRUE);
	_figureLibraryToSave = NIL;
	COODDoc::OnSaveDocument(m_strPathName);	
	setModifiedFlagForAllView(FALSE);
//	setModifiedFlag(FALSE);
}

/* 논리적으로는 이 함수가 작동해야 좀더 자연스럽게 패키지 세이브가 처리되는데 ...
 * 안타깝게도 이 함수로 dynamic binding 이 안되고 있음
 * 물론 이유는 모르겠고 ... 분명히 CDocument::GetFile() 함수가 가상함수 인데도 불구하고 ...
CFile* COODClassDoc::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
	CFileException* pError)
{
	WarningMsg("-----------------");
	if (_figureLibraryToSave == NIL) {
		WarningMsg("THERE");
		return COODDoc::GetFile(lpszFileName,nOpenFlags,pError);
	} else {
		// 위의 경우는 일반적인 경우로 미러 파일을 이용하기 때문에 *.ood 파일에 세이브되며
		// 지금 경우처럼 해야 패키지 파일에 세이브 됨
		WarningMsg("HERE");
		CFile* pFile = new CFile();
		ASSERT(pFile != NULL);
		if (!pFile->Open(lpszFileName, nOpenFlags, pError))
		{
			delete pFile;
			pFile = NULL;
		}
		return pFile;
	}
}
*/

void COODClassDoc::OnFileClose() 
{
	// TODO: Add your command handler code here
	OnWindowClose();
}

/*************************************************************
요건 OLE 이용 전에 ...
BOOL COODClassDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (_figureLibraryToSave == NIL)
		return COODDoc::OnSaveDocument(lpszPathName);

	CFileException fe;
	CFile* pFile = new CFile();
	pFile->Open(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	// 아래 두줄은 원본 CDocument::OnSaveDocument() 함수에서 사용되는 메카니즘이다. 미러 파일을 이용함.
//	pFile = GetFile(lpszPathName, CFile::modeCreate |
//		CFile::modeReadWrite | CFile::shareExclusive, &fe);

	if (pFile == NULL)
	{
		ReportSaveLoadException(lpszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return FALSE;
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
		return FALSE;
	}
	END_CATCH_ALL

#ifdef _MAC
	RecordDataFileOwner(lpszPathName, AfxGetAppName());
#endif
	return TRUE;
}
************************************************************************/
BOOL COODClassDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (_figureLibraryToSave == NIL)
		return COODDoc::OnSaveDocument(lpszPathName);

	// 이 아래 코드는 COleDocument::OnSaveDocument()를 흉내낸 것임.
	// 솔직히 나도 잘 모름
	USES_CONVERSION;

	SetModifiedFlag(TRUE);
	LPSTORAGE lpOrigStg = NULL;
	m_bSameAsLoad = FALSE;

	TRY
	{
		// temporarily detach current storage
		lpOrigStg = m_lpRootStg;
		m_lpRootStg = NULL;

		LPSTORAGE lpStorage;
		SCODE sc = ::StgCreateDocfile(T2COLE(lpszPathName),
			STGM_READWRITE|STGM_TRANSACTED|STGM_SHARE_DENY_WRITE|STGM_CREATE,
			0, &lpStorage);
		if (sc != S_OK)
			AfxThrowOleException(sc);

		ASSERT(lpStorage != NULL);
		m_lpRootStg = lpStorage;

		ASSERT(m_lpRootStg != NULL);

		// use helper to save to root storage
		SaveToStorage();

		CommitItems(FALSE);

		m_lpRootStg->Release();
		m_lpRootStg = lpOrigStg;

	}
	CATCH_ALL(e)
	{
		if (lpOrigStg != NULL)
		{
			// save as failed: abort new storage, and re-attach original
			m_lpRootStg->Release();
			m_lpRootStg = lpOrigStg;
		}

		if (lpszPathName == NULL)
		{
			THROW_LAST();
			ASSERT(FALSE);  // not reached
		}

		TRY
		{
			ReportSaveLoadException(lpszPathName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		}
		END_TRY
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	// cleanup
	m_bSameAsLoad = TRUE;
	m_bRemember = TRUE;

	return TRUE;
}

void COODClassDoc::OnFileSaveAsPackage() 
{
	// TODO: Add your command handler code here
	// 이 함수에서는 현재 패키지만 save 함
	CMDIChildWnd *pWnd = mainFramePtr->MDIGetActive();
	if (pWnd == NULL) return;
	if (!pWnd->IsKindOf(RUNTIME_CLASS(CClassFrm))) return;
	CChildFrm *pFrame = (CChildFrm *)pWnd;
	CView *activeView = pFrame->GetActiveView();
	if (activeView == NULL) return;
	if (!activeView->IsKindOf(RUNTIME_CLASS(COODView))) return;
	COODView *theView = (COODView *)activeView;
	CString currentTitle = theView->viewTitle;

	BOOL bModified = IsModified();
	COleServerDoc::SetModifiedFlag(TRUE);
	_figureLibraryToSave = classFiguresLibrary->getPackage(currentTitle);

	CString newName = currentTitle;
	if (!AfxGetApp()->DoPromptFileName(newName,
		  AFX_IDS_SAVEFILE,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, GetDocTemplate()))
			return;       // don't even attempt to save

	if (newName.Right(_EXT_LEN5).CompareNoCase(_PAK_EXT) != 0) {
		newName = newName + _PAK_EXT;
	}

	CWaitCursor wait;

	OnSaveDocument(newName);	

	_figureLibraryToSave = NIL;
	COleServerDoc::SetModifiedFlag(bModified);
}

