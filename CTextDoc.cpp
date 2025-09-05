// CTextDoc.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CTextDoc.h"
#include "KtgMacro.h"
#include "COODClassDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDoc

IMPLEMENT_DYNCREATE(CTextDoc, CDocument)

CTextDoc::CTextDoc()
{
}

BOOL CTextDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SetModifiedFlag(TRUE);
	return TRUE;
}

CTextDoc::~CTextDoc()
{
}


BEGIN_MESSAGE_MAP(CTextDoc, CDocument)
	//{{AFX_MSG_MAP(CTextDoc)
	ON_COMMAND(ID_WINDOW_CLOSE, OnWindowClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDoc diagnostics

#ifdef _DEBUG
void CTextDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextDoc serialization

void CTextDoc::Serialize(CArchive& ar)
{
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTextDoc commands

BOOL CTextDoc::onWindowClose(BOOL removeViewNameFlag) 
{
	// TODO: Add your command handler code here
	if (IsModified()) {
		m_strPathName = GetPathName();
		char buffer[BUFSIZ];
		sprintf_s(buffer,BUFSIZ,"Do you want to save %s file ?",m_strPathName);
		int ans = YesNoCancelMsg(buffer);
		if (ans == IDCANCEL) return TRUE;
		if (ans == IDYES) {
			CDocument::DoSave(m_strPathName);
		}
	}
	if (removeViewNameFlag == TRUE && theAppPtr->pCOODClassDoc != NIL) {
		CString title = GetTitle();
		theAppPtr->pCOODClassDoc->removeViewName(title);
	}
	// shut it down
	OnCloseDocument();
		// this should destroy the document
	return FALSE;
}

void CTextDoc::closeWindowAbsolutely()
{
	CString title = GetTitle();
	theAppPtr->pCOODClassDoc->removeViewName(title);
	// shut it down
	OnCloseDocument();
		// this should destroy the document
}

void CTextDoc::OnWindowClose() 
{
	// TODO: Add your command handler code here
	if (IsModified()) {
		m_strPathName = GetPathName();
		char buffer[BUFSIZ];
		sprintf_s(buffer,BUFSIZ,"Do you want to save %s file ?",m_strPathName);
		int ans = YesNoCancelMsg(buffer);
		if (ans == IDCANCEL) return; // 2014 OODesigner 수정   TRUE;
		if (ans == IDYES) {
			CDocument::DoSave(m_strPathName);
		}
	}
	CString title = GetTitle();
	theAppPtr->pCOODClassDoc->removeViewName(title);
	// shut it down
	OnCloseDocument();
		// this should destroy the document
	return; // 2014 OODesigner 수정   FALSE;
}

void CTextDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_strPathName = lpszPathName;
	ASSERT(!m_strPathName.IsEmpty());       // must be set to something
	m_bEmbedded = FALSE;
	ASSERT_VALID(this);

	// add it to the file MRU list
	if (bAddToMRU)
		AfxGetApp()->AddToRecentFileList(m_strPathName);

	ASSERT_VALID(this);

	CString nameOnly = m_strPathName;
	while(TRUE) {
		int i = nameOnly.Find('\\');
		if (i <= -1) break;
		nameOnly = nameOnly.Right(nameOnly.GetLength()-i-1);
	}
	SetTitle(nameOnly);
}

