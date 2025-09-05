// COODView.h : interface of the COODView class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_COODVIEW_H__91AA8C0F_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_COODVIEW_H__91AA8C0F_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "KtgMacro.h"
#include "figutil.h"
#include "ConnectionList.h"

#define FORK_TIMER	(1)

class COODCntrlItem;

class COODView : public CScrollView
{
protected: // create from serialization only
	COODView();
	DECLARE_DYNCREATE(COODView)
	void deleteBackUp();
	void clearBackUp();
	void remakeCanvasRgn();
	void moveScrollB(int deltax,int deltay);
	void localTraceEnter(CPoint event,FigureList *list,BOOL forFigures);
	void localMakeClear();
	void drawGrid(CDC *pDC);
	void onViewZoom(CString &value);
	void movingHandler(CPoint event,BOOL explicitCall = FALSE);
	void drawingHandler(CPoint event,Figure *focus);
	void stopMove();
	void stopDraw();
	void warpPointer(int x,int y);
	void resetFontHeight();
	void collectActiveNodes(UnsignedLong *category);
	BOOL findForkPoint();
	void showForkPointAsX();
	void clearForkPointAsX();
	void killForkTimer();
	CToolBarCtrl *getModelToolBarCtrl();
	void releaseModelTBButton();
	void releaseModelTBButton(UINT commandID);
	void pressModelTBButton(UINT commandID);
	BOOL undoIfSomeButtonAlreadyPressed(UINT commandID);
	void setPositionOnStatusBar(int x,int y);
	void movePointer(int x,int y);
	void addExcludeRectForBottomObjects(Figure *topFigure,FigureList *figures);
	void tryToDeleteClassContentFromRepository(const char *className);
	void onLineThickness(int n);
	void onLineStyle(int s);

// Attributes
private:
	COODCntrlItem *m_pSelection;
public:
	BOOL ktgF_selectionResizing;
	BOOL ktgF_selectionMoving;
	BOOL ktgF_connectionDrawing;
	BOOL ktgF_simpleDrawing;
	BOOL ktgF_simpleMoving;
	BOOL ktgF_processKeys;
	ConnectionList wrongConnections;
protected:
	BOOL ktgF_traceEnter;
	BOOL ktgF_connectionStartDraw;
	BOOL ktgF_connectionContinueDraw;

	int _savedHotX; // 이 변수들은 CSequenceView 에서만 사용됨
	int _savedHotY; // 이 변수들은 CSequenceView 에서만 사용됨
	BOOL _toBeDestroyed;
	UINT _whatNodeToDraw;
	int _whatTionToDraw;
	int _forkX;
	int _forkY;
	BOOL _firstOnDrawCall;
	BOOL _paintEventMustBeIgnored;
	BOOL _forkTimerOn;
	BOOL _forkPossibleFlag;
	BOOL _editPossibleOnLBUp;
	BOOL _editorJustStarted;
	BOOL _atFirstMove;
	BOOL _atFirstResize;
	BOOL _explicitScrolling;
	BOOL _enable;
	BOOL _ctrlKeyPressed;
	BOOL _isFixed;
	BOOL _editingTag;
	Popup *_mainPopup;
	int _regionLength;
	int _arrowLength;
	int _maxXValue, _maxYValue;
	int _minX, _minY;
	int _maxX, _maxY;
	int _width, _height;
	int _popupX, _popupY;
	int _currentX, _currentY;
	int _nOfRowsForPrint;
	int _nOfColsForPrint;
	int _oldOriginX;
	int _oldOriginY;
	FigureList *_focusList;
	FigureList *_activeNodes;
	int _drawingContext;
	CRgn *_canvasRgn;
	int _currentDrawingType;
	FontInfo *_fontInfo;
	int _fontHeight;
	Figure *_currentFocus;
	Connection *_currentConnection;
	Figure *_backUp;
	Bucket *_theBucket;

// Attributes
public:
	static CPen *PlainPen;
	static CPen *RubberbandPen;
	static CPen *HighlightPen;
	static CPen *ErasePen;

	static CBrush *PlainBrush;
	static CBrush *RubberbandBrush;
	static CBrush *HighlightBrush;
	static CBrush *EraseBrush;
	static CBrush *ShapeEraseBrush;

	static CPen *OldPen;
	static COLORREF OldTextColor;
	static COLORREF OldBkColor;
	static CBrush *OldBrush;
	static int OldMode;
	static CGdiObject *OldGdi;
	
	static CLIPFORMAT OODClipFormat;
	int originX();
	int originY();
	void setOriginX(int x);
	void setOriginY(int y);

	int currentOrient;
	CString viewTitle;
	CString viewTitleWithOutExtension;

// Operations
public:
	COODDoc* GetDocument();
	FigureList *figures();
	void showTitleAsModified();
	void showTitleAsNotModified();
	virtual void setPopups();
	virtual void drawingEpilog();
	virtual void startFork();
	virtual void startResize();
	virtual BOOL checkLimitForFigure(int newx,int newy,int *deltax = NIL,int *deltay = NIL);
	void setController();
	void setControllerAbsolutely();
	void remakeAllRegions(COODDoc* pDoc);
	void setTitle(CString &title);
	void setViewTitle(CString &title);
	CRgn *canvasRgn() { return _canvasRgn; }
	void setToBeDestroyed() { _toBeDestroyed = TRUE; }
	BOOL &editingTag() { return _editingTag; }
	int width() { return _width; }
	int height() { return _height; }
	int maxXValue() { return _maxXValue; }
	int maxYValue() { return _maxYValue; }
	int currentX() { return _currentX; }
	int currentY() { return _currentY; }
	void setCurrentXY(int x,int y) { _currentX = x; _currentY = y; }
	void resetCurrentFocus() { _currentFocus = NIL; }
	void resetCurrentConnection() { _currentConnection = NIL; }
	Figure *currentFocus() { return _currentFocus; }
	Connection *currentConnection() { return _currentConnection; }
	void resetWhatTionToDraw() { _whatTionToDraw = -1; }
	int whatTionToDraw() { return _whatTionToDraw; }
	int zoomRatioX();
	int zoomRatioY();
	void setZoomRatioX(int zoomX);
	void setZoomRatioY(int zoomY);
	void LPtoDP(CPoint &point);
	void LPtoDP(CRect &rect);
	void DPtoLP(CPoint &point);
	void DPtoLP(CRect &rect);
	CRgn* createPolygonRegion(LPPOINT points,int count);
	CRgn* makeRectRegion(int x,int y,int w,int h);
	BOOL checkInRegion(CRgn* someregion,int x1,int y1,int x2,int y2);
	BOOL checkInRegion(CRgn* someregion,XCoord &x1,YCoord &y1,XCoord &x2,YCoord &y2);
	int rectInRegion(CRgn* region,int x,int y,int w,int h);
	void invalidateRect(CRect *pRect,BOOL flag = TRUE);
	void saveViewBMP(CString &fileName);
	void showFigureOnCenterOfView(NodeFigure *aNode);
	void setFontInfo(CFontDialog *pFontDlg);
	void userMsg(const char*);
	void userMsg(const char*,int n);
	void userMsgForUsingUpperCaseAsBlank(char *,char *);
	void beep(const char *);

	BOOL captureCursorOnBoundary(int x,int y);
	void startMove();
	void deleteCurrentFigure();
	void deleteSelectedObject();
	void checkInList(Figure *ptr);
	void remove(Figure *figure);
	void insert(Figure *figure);
	void clearArea(int x,int y,int w,int h);
	void eraseDots(Figure *figure);
	void drawDots(Figure *figure);
	void highlight(Figure *figure);
	void draw(Figure *figure);
	void drawWithNeighbors(Figure *figure);
	void lowlight(Figure *figure);
	void lowlightDraw(Figure *figure);
	void lowlightDrawBoundary(Figure *figure);
	void erase(Figure *figure);
	void rubberbanding(Figure *figure);
	void clear(Figure *figure);
	void redrawFor(Figure *figure);
	void drawAllFigures();
	void drawAllFigures(CDC* pDC);
	void traceEnter(CPoint event);
	void OODReleaseDC(CDC* pDC,BOOL releaseFlag);
	void minMaxXY(XCoord &x1,YCoord &y1,XCoord &x2,YCoord &y2);
	void minMaxXY(XCoord &x1,YCoord &y1);
	void setDrawingContext(int context) {
		_drawingContext = context;
	}
	FontInfo *fontInfo() { return _fontInfo; }
	int fontHeight() { return _fontHeight; }
	int regionLength() { return _regionLength; }
	int arrowLength() { return _arrowLength; }
	int popupX() { return _popupX; }
	int popupY() { return _popupY; }
	void setFirstOnDrawCall(BOOL flag) { 
		_firstOnDrawCall = flag; 
	}

	// operations for Text object
	void setCaretXY(int x,int y);
	BOOL editorFinished();
	void startEditor(CPoint p);
	void processKeys(UINT nChar);
	void onZoom() { OnZoom(); }
	void onTbActor() { OnTbActor(); }
	void onCreateActor() { OnCreateActor(); }

	void OnCreateNote();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual BOOL IsSelected(const CObject* pDocItem) const;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~COODView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void resetMinMaxXY();
	void hideGlobalDlgs();

// Generated message map functions
protected:
	//{{AFX_MSG(COODView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnToolsFont();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTbArrow();
	afx_msg void OnTbAlphabet();
	afx_msg void OnTbNote();
	afx_msg void OnTbAnchor();
	afx_msg void OnDestroy();
	afx_msg void OnInsertObject();
	afx_msg void OnObjectEdit();
	afx_msg void OnObjectOpen();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnObjectTransparent();
	afx_msg void OnObjectProperties();
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnCancelEditCntr();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnPopupEditPaste();
	afx_msg void OnUpdatePopupEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnToolsGrid();
	afx_msg void OnUpdateToolsGrid(CCmdUI* pCmdUI);
	afx_msg void OnToolsColorPaper();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnToolsColorText();
	afx_msg void OnToolsColorShapeForeground();
	afx_msg void OnToolsColorShapeBackground();
	afx_msg void OnViewRefresh();
	afx_msg void OnViewZoom10();
	afx_msg void OnViewZoom100();
	afx_msg void OnViewZoom20();
	afx_msg void OnViewZoom30();
	afx_msg void OnViewZoom40();
	afx_msg void OnViewZoom50();
	afx_msg void OnViewZoom60();
	afx_msg void OnViewZoom70();
	afx_msg void OnViewZoom80();
	afx_msg void OnViewZoom90();
	afx_msg void OnTbActor();
	//}}AFX_MSG
	void OnCreateActor();
	void OnDeleteFigure();
	void OnPopupEdit();
	void OnEditRoleName();
	void OnZoom();
	void OnLineArrow();
	void OnLineStyleSolid();
	void OnLineStyleDash();
	void OnLineStyleDot();
	void OnLineThickness1();
	void OnLineThickness2();
	void OnLineThickness3();
	void OnLineThickness4();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTbBox();
	afx_msg void OnTbCircle();
	afx_msg void OnTbRoundboxa();
};

#ifndef _DEBUG  // debug version in COODView.cpp
inline COODDoc* COODView::GetDocument()
   { return (COODDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COODVIEW_H__91AA8C0F_7A3E_11D2_AC44_00008610434C__INCLUDED_)

