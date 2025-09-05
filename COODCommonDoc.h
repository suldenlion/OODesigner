#if !defined(AFX_COODCOMMONDOC_H__96BF4BE0_00CA_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_COODCOMMONDOC_H__96BF4BE0_00CA_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// COODCommonDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COODCommonDoc document
#include "Classes.h"
#include "COODDoc.h"

class CustomToolBar;

#define INSERT_MENU_POS (3)
#define INSERT_MENU_POS_PLUS_1 (INSERT_MENU_POS+1)

class COODCommonDoc : public COODDoc
{
	DECLARE_DYNCREATE(COODCommonDoc)
private:
	CString _diagramName; // actually not used (클래스 다이어그램 경우와 맞춰주기 위해서 ...)
	FigureList *_figures;
	CStringList _comment; // actually not used (클래스 다이어그램 경우와 맞춰주기 위해서 ...)
	int _zoomRatioX;
	int _zoomRatioY;
	int _originX;
	int _originY;
private: // transient members
	BOOL _visibleDocumentFlag;
protected:
	COODCommonDoc();           // protected constructor used by dynamic creation
	void usualOnFileSaveAs();
	void serverOnFileSaveAs();
	void serverSaveDocument(LPCTSTR lpszPathName);

// Attributes
public:

// Operations
public:
	virtual FigureList *figures() {
		return _figures;
	}
	virtual FigureList *figures(CString& title) {
		return _figures;
	}
	virtual int zoomRatioX() {
		return _zoomRatioX;
	}
	virtual int zoomRatioY() {
		return _zoomRatioY;
	}
	virtual int zoomRatioX(CString& title) {
		return _zoomRatioX;
	}
	virtual int zoomRatioY(CString& title) {
		return _zoomRatioY;
	}
	virtual void setZoomRatioX(CString& title,int zoomX) {
		_zoomRatioX = zoomX;
		return;
	}
	virtual void setZoomRatioY(CString& title,int zoomY) {
		_zoomRatioY = zoomY;
		return;
	}
	virtual int originX() {
		return _originX;
	}
	virtual int originY() {
		return _originY;
	}
	virtual int originX(CString& title) {
		return _originX;
	}
	virtual int originY(CString& title) {
		return _originY;
	}
	virtual void setOriginX(CString& title,int x) {
		_originX = x;
		return;
	}
	virtual void setOriginY(CString& title,int y) {
		_originY = y;
		return;
	}
	virtual void setModifiedFlag(BOOL flag = TRUE);
	void setShapeBackground(COLORREF bkColor);
	void setShapeForeground(COLORREF fgColor);
	void clearContents();
	BOOL onWindowClose(BOOL removeViewNameFlag);
	void onFileSave();
	void copyDocumentContentsTo(FigureLibrary *toPackage,COODDoc *toDoc);
	void copyDocumentContentsTo(COODCommonDoc *toDoc);
	void replaceFieldTextContent(CString &className,ClassTemplate *aClass,COODView *aView = NIL);
	ClassContent* registerClassContent(CString &className,ClassTemplate *theClass);
	ClassContent* getClassContentFor(CString &className,ClassTemplate *theClass);
	static CDocument *openInvisibleDocument(CDocTemplate *pTemplate,LPCTSTR lpszPathName);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODCommonDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void DeleteContents();
	protected:
	virtual BOOL OnNewDocument();
	virtual void OnDeactivate();
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COODCommonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COODCommonDoc)
	afx_msg void OnWindowClose();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COODCOMMONDOC_H__96BF4BE0_00CA_11D4_AED4_00A0C9BA6734__INCLUDED_)
