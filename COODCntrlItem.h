#if !defined(AFX_COODCNTRLITEM_H__23EADE80_4DD7_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_COODCNTRLITEM_H__23EADE80_4DD7_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// COODCntrlItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COODCntrlItem document
class COODDoc;
class COODView;

#define AT_1	(1)
#define AT_2	(2)
#define AT_3	(3)
#define AT_4	(4)
#define AT_5	(5)
#define AT_6	(6)
#define AT_7	(7)
#define AT_8	(8)
#define AT_MOVE (9)

class COODCntrlItem : public COleClientItem
{
	DECLARE_SERIAL(COODCntrlItem)
public:
	COODCntrlItem(COODDoc* pContainer = NULL);	
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
private:
	int _x1;
	int _y1;
	int _x2;
	int _y2;
	int _ox1;
	int _oy1;
	int _ox2;
	int _oy2;
	BOOL _opaqueFlag;
	int _moveX;
	int _moveY;
	int _resizePoint;
	COODView *_controller;
	CString _viewTitle;
	CRgn* _region;
	BOOL _inCanvas;
	BOOL _dotedFlag;
	int _brushIndex;
private:
	BOOL setControllerForViewName();
public:
	COODDoc *GetDocument()
	{ return (COODDoc *)COleClientItem::GetDocument(); }
	COODView *GetActiveView()
	{ return (COODView*)COleClientItem::GetActiveView(); }
// Operations
public:
	COODView *getController() { return _controller; }
	void setDocument(COleDocument *pDoc) { m_pDocument = pDoc; }
	CString &getViewTitle() { return _viewTitle; }
	void saveOriginXY(COODView *pController);
	void resetRegion(COODView *pController);
	void releaseRegion(COODView *pController);
	void makeRegion(COODView *pController);
	void setCoord(int x1,int y1,int x2,int y2);
	void setControllerAbsolutely(COODView *controller);
	void setController(COODView *controller,CString viewTitle);
	void resetController();
	BOOL checkInRegion(COODView *pController,CRgn* someregion);
	void setInCanvas(COODView *pController,BOOL flag);
	void setInCanvas(BOOL flag);
	BOOL inCanvas(COODView *pController);
	BOOL onEnter(COODView *pController,int x,int y);
	void drawBoundary(COODView *pController,CDC* pDC);
	void clear(COODView *pController,CDC* pDC);
	BOOL draw(CDC* pDC);
	BOOL draw(COODView *pController,CDC* pDC);
	void resizing(COODView *pController,CPoint point);
	void moving(COODView *pController,CPoint point);
	void move(COODView *pController,int dx,int dy);
	void drawAsSelected(COODView *pController,CDC *pDC);
	void getClientRect(COODView *pController,CRect &rect);
	void getXY12(COODView *pController,CRect &rect);
	void getXY12Absolutely(CRect &rect);
	void trackMouse(COODView *pController,CPoint point);
	void stopResize(COODView *pController);
	void stopMove(COODView *pController);
	void popup(CWnd *pWnd,CPoint* event);
	void toggleOpaqueFlag();
	BOOL containedWithin(COODView *pController,int x1,int y1,int x2,int y2);
	int resizePoint() {
		return _resizePoint;
	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODCntrlItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION nCode, DWORD dwParam);
	virtual void OnDeactivateUI(BOOL bUndoable);
	protected:
	virtual void OnActivate();
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COODCntrlItem();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COODCntrlItem)
	//}}AFX_MSG
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COODCNTRLITEM_H__23EADE80_4DD7_11D5_A72B_0050DA2D4248__INCLUDED_)
