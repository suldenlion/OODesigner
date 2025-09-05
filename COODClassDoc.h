#if !defined(AFX_COODCLASSDOC_H__A4570580_0C15_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_COODCLASSDOC_H__A4570580_0C15_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// COODClassDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COODClassDoc document
#include "Classes.h"
#include "COODDoc.h"

class COODClassDoc : public COODDoc
{
protected:
	COODClassDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COODClassDoc)

// Attributes
private:
	ClassFigureLibrary *classFiguresLibrary;
	PackageLibrary *allClassContents;
	RelationshipInfoTupleList *generalizationLibrary;
	RelationshipInfoTupleList *aggregationLibrary;
	RelationshipInfoTupleList *dependencyLibrary;
public:
	FigureLibrary *_figureLibraryToSave;
	CStringList activeViewNames;
	CString recentViewName;

// Operations
public:
	virtual FigureList *figures();
	virtual FigureList *figures(CString& title);
	virtual int zoomRatioX();
	virtual int zoomRatioY();
	virtual int zoomRatioX(CString& title);
	virtual int zoomRatioY(CString& title);
	virtual void setZoomRatioX(CString& title,int zoomX);
	virtual void setZoomRatioY(CString& title,int zoomY);
	virtual int originX();
	virtual int originY();
	virtual int originX(CString& title);
	virtual int originY(CString& title);
	virtual void setOriginX(CString& title,int x);
	virtual void setOriginY(CString& title,int y);
	virtual void setModifiedFlag(BOOL flag = TRUE);
	void setModifiedFlagForAllView(BOOL flag = TRUE);
	void setShapeBackground(COLORREF bkColor);
	void setShapeForeground(COLORREF fgColor);
	void removeViewName(CFrameWnd* pFrame);
	void removeViewName(CString &viewName);
	void removeViewNameAt(POSITION pos);
	void insertViewName(CString& name);
	CClassFrm *findClassFrame(CString &title);
	FigureLibrary *getPackage(CString &title);
	FigureLibrary *addPackage(CString &packageName);
	BOOL ifClassViewAlreadyExists(CString& title);
	void hideClassViewIfAlreadyExists(CString &title);
	FigureLibrary* clearPackage(CString &title);
	void registerOrReplaceClassContent(CString &packName,FigureLibrary *aPackage);
	BOOL closeAllWindow(BOOL closeWorkspace);
	void destroyClassFrameWindow(CString &title);
	void tryToDeleteClassContentFromRepository(CString &className);
	BOOL tryToRemoveRelationshipInfo(RelationshipInfoTupleList *library,char *major,char *minor,UnsignedLong *identity,CString &packName);
	void deleteAllRelationshipWithClassName(CString className);
	void onFileSaveClassDocument();
	void setStrTitle(CString title) {
		m_strTitle = title;
	}
	ClassFigureLibrary *getClassFiguresLibrary() {
		return classFiguresLibrary;
	}
	PackageLibrary *getAllClassContents() {
		return allClassContents;
	}
	RelationshipInfoTupleList *getGeneralizationLibrary() {
		return generalizationLibrary;
	}
	RelationshipInfoTupleList *getAggregationLibrary() {
		return aggregationLibrary;
	}
	RelationshipInfoTupleList *getDependencyLibrary() {
		return dependencyLibrary;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODClassDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COODClassDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COODClassDoc)
	afx_msg void OnWindowClose();
	afx_msg void OnFileSave();
	afx_msg void OnFileClose();
	afx_msg void OnFileSaveAsPackage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COODCLASSDOC_H__A4570580_0C15_11D4_AED4_00A0C9BA6734__INCLUDED_)
