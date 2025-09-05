#if !defined(AFX_CRESIZABLETREEBAR_H__91AA8C33_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLETREEBAR_H__91AA8C33_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableTreeBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableTreeBar window
#include "CResizableControlBar.h"
#include "Classes.h"

// 팝업에서 사용 예정
#define ROOT_ID				(0)
#define PACKAGE_ID			(1)
#define CLASS_ID			(2)
#define	DATAMEMBER_ID		(3)
#define	MEMBERFUNCTION_ID	(4)

#define FILE_CLOSE_BM_ID				(0)
#define FILE_OPEN_BM_ID					(1)
#define CLASS_DIAGRAM_BM_ID				(2)
#define USE_CASE_DIAGRAM_BM_ID			(3)
#define SEQUENCE_DIAGRAM_BM_ID			(4)
#define COLLABORATION_DIAGRAM_BM_ID		(5)
#define STATE_DIAGRAM_BM_ID				(6)
#define ACTIVITY_DIAGRAM_BM_ID			(7)
#define DEPLOYMENT_DIAGRAM_BM_ID		(8)

class CResizableTreeBar : public CResizableControlBar
{
private:
	CMenu		_allPopupMenu;
	CTreeCtrl*	_selectedCtrlBeforePopup;
	HTREEITEM	_selectedItemBeforePopup;
    CImageList  _classViewImageList;
    CImageList  _diagramViewImageList;
	CImageList	_fileViewImageList;
	CImageList	_infoViewImageList;
	void insertClassMember(HTREEITEM hClass,ClassTemplate *aClass,ClassContent *aContent);
	void deleteAllClassMember(HTREEITEM hClass);
	void deleteClassMember(UINT id,HTREEITEM pItem);
	void registerTextFilesFrom(char *dirString);
	BOOL tryToDeleteSelectedItem();
	void insertClass(HTREEITEM hPackage,CString &className,ClassContent *aClassContent);
	void popupTreeBarMenu(CTreeCtrl* currentCtrl,HTREEITEM pItem,CPoint point);
	BOOL showClassPropDlg(CTreeCtrl* currentCtrl,HTREEITEM pItem);
	BOOL showDataMemberPropDlg(CTreeCtrl* currentCtrl,HTREEITEM pItem);
	BOOL showFunctionMemberPropDlg(CTreeCtrl* currentCtrl,HTREEITEM pItem);
	void checkOrUncheckDockingMenu(CMenu *aMenu);
	void deleteADiagram(CString dgmName);
	BOOL containsAnyClassInPackage(CString packageName);
	void invalidateCurrentTabCtrl(CTreeCtrl* ctrl);
// Construction
public:
	CResizableTreeBar();

// Attributes
public:
    CTabCtrl    m_TabCtrl;
    CImageList  m_ImgList;
	CTreeCtrl	*classTreeCtrl;
	CTreeCtrl	*diagramTreeCtrl;
	CTreeCtrl	*fileTreeCtrl; 
	CTreeCtrl	*infoTreeCtrl;
// Operations
public:
	void clearContents();
	void insertDiagramName(CString &dgmName);
	void insertTextName(CString &txtName);
	void insertPackage(CString &packageName);
	void registerTextFiles();
	void registerDiagramFilesFromCurrentDir();
	void registerClassContentFromPackageLibrary(PackageLibrary *allClassContents);
	void registerClassDiagramFilesFromClassFigureLibrary(ClassFigureLibrary *classFiguresLibrary);
	void insertClass(CString &packageName,CString &className,ClassTemplate *aClass);
	void replaceClass(CString &packageName,CString &className,ClassContent *aContent);
	void deleteClass(CString &packageName,CString &className);
	CMenu *getDeleteRelationshipMenu();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableTreeBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizableTreeBar();

	// Generated message map functions
protected:
    virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
    // helper functions.
    CWnd * GetTabWindow(int nTab);
    void ShowSelTabWindow();

	//{{AFX_MSG(CResizableTreeBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDataProperties();
	afx_msg void OnFunctionProperties();
	afx_msg void OnClassProperties();
	afx_msg void OnClassGoToDefinition();
	afx_msg void OnPackageNewClass();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnPackageOpen();
	afx_msg void OnClassRelatedClasses();
	afx_msg void OnDiagramTypeNewDiagram();
	afx_msg void OnDiagramOpen();
	afx_msg void OnDiagramDelete();
	afx_msg void OnFileTypeNewFile();
	afx_msg void OnFileMenuOpen();
	afx_msg void OnFileMenuDelete();
	afx_msg void OnPackageProperties();
	afx_msg void OnClassRootNewPackage();
	afx_msg void OnMemberDelete();
	afx_msg void OnClassDelete();
	afx_msg void OnPackageDelete();
	afx_msg void OnClassMigrate();
	//}}AFX_MSG
    void OnTabChanged(NMHDR * pNotifyStruct,LRESULT * result);
	void OnItemExpendedAtFileTree(NMHDR * pNotifyStruct,LRESULT * result);
	void OnItemExpendedAtDiagramTree(NMHDR * pNotifyStruct,LRESULT * result);
	void OnItemExpendedAtInfoTree(NMHDR * pNotifyStruct,LRESULT * result);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLETREEBAR_H__91AA8C33_7A3E_11D2_AC44_00008610434C__INCLUDED_)
