// CMainFrame.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_CMAINFRAME_H__91AA8C09_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CMAINFRAME_H__91AA8C09_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "CResizableMDIFrameWnd.h"
#include "CResizableTreeBar.h"
#include "CustomToolBar.h"

class CMainFrame : public CResizableMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	// data members
public:
	CMainFrame();
	void onFileNew(CString dgmType,const char * = NULL);
	void onFileNew() { OnFileNew(); }
	void onFileOpen() { OnFileOpen(); }
	void onClose() { OnClose(); }
	BOOL onWindowCloseAll();
	BOOL onWindowCloseAllCommon(BOOL closeWorkspace);
	void getZoomValue(CString &value);
	void setZoomValue(const char *value);
	void setZoomValue(CDocument *pDoc);
	void setZoomValue(COODView *pView);
	CDocument *openDocumentFile(CString &pathName);
	CDocument *getNamedTextDocument(CString &dgmName);
	CDocument *getNamedDocument(CString &dgmName);
	void setShapeBackground(COLORREF bkcolor);
	void setShapeForeground(COLORREF fgcolor);
	void setModifiedFlagForAllDocAndInvalidate();
	static CDocument *alreadyOpen(CDocTemplate *pTemplate,CString &fileName);

private:
	void saveUserRectBMP(CString &fileName);
	void onFileNewWorkspace(CString &wsName);
	void setModelBarPositionOnLeftOf(CControlBar *targetBar,CControlBar *modelBar);
	CDocument *openOrCreateDocumentFile(CMultiDocTemplate* pDocumentTemplate,CString& dgmName);
	void setFontInfoForDocument(CDocument* pDoc,CFontDialog *pFontDlg);
// Attributes
public:

// Operations
public:
	void SetActiveViewDirect(CView *pView) {
		m_pViewActive = pView;
	}
	BOOL createNewClassFrame(CDocTemplate* pTemplate,CDocument* pDocument,CString fileName);
	void setTextOnStatusBar(const char *text,int field = 0);
	void setPositionOnStatusBar(int x,int y,int field = 1);
	void userMsg(const char*);
	void userMsg(const char*,int n);
	void userMsgForUsingUpperCaseAsBlank(char *,char *);
	void showControlBarJustFor(const char *dgmName,CControlBar *pBar);
	COODView* openNamedFile(DWORD dgmID,CString &dgmName);
	void openTextFile(CString &fileName,CString &viewName);
	void closeTextFile(CString &viewName);
	BOOL onFileOpenWorkspace(LPCTSTR fileName);
	COODView* getActiveCOODView();
	void saveImageToFileAndClipboard(CString &fileName,CBitmap &imageBitmap);
	void setFontInfoForAllViews(CFontDialog *pFontDlg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CustomToolBar  m_wndCustomBar;
public:
	CToolBar	classDiagramToolBar;
	CToolBar	usecaseDiagramToolBar;
	CToolBar	sequenceDiagramToolBar;
	CToolBar	collaborationDiagramToolBar;
	CToolBar	stateDiagramToolBar;
	CToolBar	activityDiagramToolBar;
	CToolBar	deploymentDiagramToolBar;
	CResizableTreeBar	m_wndTreeBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnWindowCloseAll();
	afx_msg void OnWindowNext();
	afx_msg void OnWindowPrevious();
	afx_msg void OnFileNewWorkspace();
	afx_msg void OnFileCloseWorkspace();
	afx_msg void OnFileOpenWorkspace();
	afx_msg void OnFileSaveWorkspace();
	afx_msg void OnUpdateFileSaveWorkspace(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileCloseWorkspace(CCmdUI* pCmdUI);
	afx_msg void OnClassToolsOptions();
	afx_msg void OnOptionsProject();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnViewCustombar();
	afx_msg void OnUpdateViewCustombar(CCmdUI* pCmdUI);
	afx_msg void OnScreenshot();
	afx_msg void OnUpdateFileSaveAsWorkspace(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAsWorkspace();
	afx_msg void OnClassRootNewPackage();
	afx_msg void OnBarAllowdocking();
	afx_msg void OnBarHide();
	afx_msg void OnUpdateClassRootNewPackage(CCmdUI* pCmdUI);
	afx_msg void OnPackageNewClass();
	afx_msg void OnPackageOpen();
	afx_msg void OnPackageProperties();
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassGoToDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnClassRelatedClasses();
	afx_msg void OnDataProperties();
	afx_msg void OnFunctionProperties();
	afx_msg void OnDiagramDelete();
	afx_msg void OnDiagramOpen();
	afx_msg void OnDiagramTypeNewDiagram();
	afx_msg void OnFileMenuDelete();
	afx_msg void OnFileMenuOpen();
	afx_msg void OnFileTypeNewFile();
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnMemberDelete();
	afx_msg void OnClassDelete();
	afx_msg void OnPackageDelete();
	afx_msg void OnClassMigrate();
	//}}AFX_MSG
	void OnUpdateControlBarMenu(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMAINFRAME_H__91AA8C09_7A3E_11D2_AC44_00008610434C__INCLUDED_)

