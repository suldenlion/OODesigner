#if !defined(AFX_COODDOC_H__4EA50140_64C1_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_COODDOC_H__4EA50140_64C1_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// COODDoc.h : header file
//
#include "Classes.h"
#include "KtgMacro.h"

/////////////////////////////////////////////////////////////////////////////
// COODDoc document
class COODSrvrItem;

class COODDoc : public COleServerDoc
{
protected:
	COODDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COODDoc)
	void setRootStg();
	virtual void OnNewEmbedding(LPSTORAGE lpStorage);
	virtual void OnOpenEmbedding(LPSTORAGE lpStorage);
	void adaptViewAndFrameAndControlBar();
	void copyOleItemsTo(COODDoc *toDoc,CString *viewName = NULL);
	void SerializeForPackageOnly(CArchive& ar,CString viewName);
	void SerializeCommon(CArchive& ar);

// Attributes
public:
	CString extensionNameAfterLoad; //Serialize 대상임: 도큐 템플리트를 결정하기 위해
	CString embeddedFileName; //Serialize 대상임

	const char *getExtension();
	COODSrvrItem* GetEmbeddedItem() {
		return (COODSrvrItem*)COleServerDoc::GetEmbeddedItem();
	}
	CInPlaceFrame* getInPlaceFrame();

// Operations
public:
	virtual FigureList *figures() {
		return NIL;
	}
	virtual FigureList *figures(CString& title) {
		return NIL;
	}
	virtual int zoomRatioX() {
		return 100;
	}
	virtual int zoomRatioY() {
		return 100;
	}
	virtual int zoomRatioX(CString& title) {
		return 100;
	}
	virtual int zoomRatioY(CString& title) {
		return 100;
	}
	virtual void setZoomRatioX(CString& title,int zoomX) {
		return;
	}
	virtual void setZoomRatioY(CString& title,int zoomY) {
		return;
	}
	virtual int originX() {
		return 0;
	}
	virtual int originY() {
		return 0;
	}
	virtual int originX(CString& title) {
		return 0;
	}
	virtual int originY(CString& title) {
		return 0;
	}
	virtual void setOriginX(CString& title,int x) {
		return;
	}
	virtual void setOriginY(CString& title,int y) {
		return;
	}
	virtual void setModifiedFlag(BOOL flag = TRUE) {
		COleServerDoc::SetModifiedFlag(flag);
	}
	void setRootStg(CString lpszPathName);
	COODView *getFirstView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	virtual COleServerItem* OnGetEmbeddedItem();
	virtual void OnDeactivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COODDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COODDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COODDOC_H__4EA50140_64C1_11D5_A72B_0050DA2D4248__INCLUDED_)
