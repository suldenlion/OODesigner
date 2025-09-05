#if !defined(AFX_CRESIZABLEDOCKBAR_H__91AA8C2B_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLEDOCKBAR_H__91AA8C2B_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableDockBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableDockBar window
#include <afxpriv.h>

typedef struct _ROWSIZEINFO
{
    int nFlexWidth;                 // space taken up by flexible bars
    int nFixedWidth;                // space taken up by fixed size bars
    int nMaxHeight;                 // max height taken  (both flexible and fixed height bars)
    int nMaxFixedHeight;    // max height taken by a fixed size bar.
    int nFlexBars;                  // number of sized bars
    int nTotalBars;                 // total no of bars in the row.
	int nTotalWidth;					// fixed + flex width
} ROWSIZEINFO;

class CSplitterRect;
class CResizableControlBar;

#define IsSizeable(pBar) (BOOL) ((CControlBar *) pBar)->IsKindOf(RUNTIME_CLASS(CResizableControlBar))

class CResizableDockBar : public CDockBar
{
	friend class CResizableDockContext;
	DECLARE_DYNAMIC(CResizableDockBar)
// Construction
public:
	CResizableDockBar();

// Attributes
public:
    CObArray        m_SplitArr;             // array of CSplitterRect's constructed by ReCalcLayout

    CSplitterRect * m_pSplitCapture;        // capture splitter rect (if any)
    HCURSOR         m_hcurLast;                             // last cursor type

    // following items used to detect when DockBar has changed since last time, so we
    // can re-arrange the rows if parent resizes, or bars are docked/floated/hidden
    CSize           m_LayoutSize;   // size used in previous layout
    int             m_CountBars;    // no of bars for previous layout - need to go better than this..
	CPtrArray		m_arrHiddenBars;		// array of currently invisible bars

// Operations
public:
    virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    void TileDockedBars();
	void AdjustForNewBar(CControlBar *pBar);		
	BOOL WasBarHidden(CControlBar *pBar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableDockBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizableDockBar();

protected:
    CSplitterRect * GetSplitter(int i)
                { return ((CSplitterRect *)(m_SplitArr[i])); };
    void AddSplitterRect(int type, int x1, int y1, int x2, int y2, int nPos);
    void DeleteSplitterRects();
    void SetSplitterSizeInRange(int start, int type, int length);
    CSplitterRect * SetHitCursor(CPoint pt);
    CSplitterRect * HitTest(CPoint pt);
    void StartTracking(CPoint pt);

        // Navigating rows
    int StartPosOfRow(int nPos);
    int StartPosOfPreviousRow(int nPos);

        // Resizing rows
    void GetFirstLastSizeableInRow(int nPos, int & nPosFirst, int & nPosLast);

    void GetRowSizeInfo(int nPos,  ROWSIZEINFO * pRZI, const CPtrArray & arrBars);
    BOOL AdjustAllRowSizes(int nNewSize);
    BOOL AdjustRowSizes(int nPos, int nNewSize, CPtrArray & arrBars);
    void TileDockedBarsRow(int nPos);

    int ShrinkRowToLeft(int nPos, int nAmount, BOOL bApply, int * pnFlex = NULL);
    int ShrinkRowToRight(int nPos, int nAmount, BOOL bApply, int * pnFlex = NULL);
    int CheckSumBars() const;

public:
    // Dragging
	int TestInsertPosition(CControlBar* pBarIns, CRect rect);
	int BarsOnThisRow(CControlBar *pBarIns, CRect rect);
        
    // Miscellaneous
    CResizableControlBar * GetFirstControlBar ();

    BOOL IsBarHorizontal()
                { return (m_dwStyle & (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM)); };

	// Generated message map functions
protected:
	//{{AFX_MSG(CResizableDockBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
    LRESULT OnSizeParent(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLEDOCKBAR_H__91AA8C2B_7A3E_11D2_AC44_00008610434C__INCLUDED_)
