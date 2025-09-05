// CResizableDockBar.cpp : implementation file
//

#include "stdafx.h"
#include "CResizableDockBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "CResizableControlBar.h"
#include "CSplitterRect.h"
#include "CResizableRectTracker.h"
#include "ResizeGlobalData.h"


#define CX_SPLIT        8               // dimensions of splitter bars
#define CY_SPLIT        8
#define CX_BORDER       1
#define CY_BORDER       1

extern ResizeGlobalData afxData;

inline BOOL SetWindowSize(CWnd * pWnd, CSize size)
// in-line function for setting window size, without changing Z-order, etc
//-------------------------------------------------------------------
{
//TRACE0("SetWindowSize\n");
	return pWnd->SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE /* | SWP_NOREDRAW */ | SWP_NOZORDER);
}

CControlBar * GetDockedControlBar(int nPos, const CPtrArray & arrBars)
// helper which can acts on any array of windows
//------------------------------------------------------------------------
{
//TRACE0("GetDockedControlBar\n");
	CControlBar* pResult = (CControlBar*)arrBars[nPos];
	if (HIWORD(pResult) == 0)
		return NULL;
	return pResult;
}

IMPLEMENT_DYNAMIC(CResizableDockBar, CDockBar)

/////////////////////////////////////////////////////////////////////////////
// CResizableDockBar

CResizableDockBar::CResizableDockBar()
{
//TRACE0("CResizableDockBar::CResizableDockBar\n");
    m_pSplitCapture = NULL;
    m_hcurLast = NULL;
    m_LayoutSize.cx = 0xffff;       // some stupid values to force automatic resize
    m_LayoutSize.cy = 0xffff;
	m_CountBars = 0;
}

CResizableDockBar::~CResizableDockBar()
{
//TRACE0("CResizableDockBar::~CResizableDockBar\n");
    DeleteSplitterRects();          // delete any outstanding splitter rects
}


BEGIN_MESSAGE_MAP(CResizableDockBar, CDockBar)
	//{{AFX_MSG_MAP(CResizableDockBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResizableDockBar message handlers

void CResizableDockBar::OnPaint() 
{
//TRACE0("CResizableDockBar::OnPaint\n");
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    for (int i = m_SplitArr.GetUpperBound(); i >= 0; i--)
        ((CSplitterRect *)(m_SplitArr[i]))->Draw(&dc);
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CResizableDockBar::OnMouseMove(UINT nFlags, CPoint point) 
{
//TRACE0("CResizableDockBar::OnMouseMove\n");
	// TODO: Add your message handler code here and/or call default
    SetHitCursor(point);
    CDockBar::OnMouseMove(nFlags, point);
}

void CResizableDockBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
//TRACE0("CResizableDockBar::OnLButtonDown\n");
	// TODO: Add your message handler code here and/or call default
	if (m_pSplitCapture == NULL)
	{
		m_pSplitCapture = SetHitCursor(point);
		if (m_pSplitCapture != NULL)
		{
			StartTracking(point);
			m_pSplitCapture = NULL;
		}
	}
}

void CResizableDockBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
//TRACE0("CResizableDockBar::OnLButtonUp\n");
	// TODO: Add your message handler code here and/or call default
    CDockBar::OnLButtonUp(nFlags, point);
}

BOOL CResizableDockBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
//TRACE0("CResizableDockBar::OnSetCursor\n");
	// TODO: Add your message handler code here and/or call default
	
    if (nHitTest == HTCLIENT && pWnd == this) // && !m_bTracking)
        return TRUE;    // we will handle it in the mouse move

    return CDockBar::OnSetCursor(pWnd, nHitTest, message);
}

CSize CResizableDockBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
//TRACE0("CResizableDockBar::CalcFixedLayout\n");
    ASSERT_VALID(this);

    CSize sizeFixed = CControlBar::CalcFixedLayout(bStretch, bHorz);

    // ID for this bar...used to set MRU docked position
	UINT uDockBarID = GetWindowLong(m_hWnd, GWL_ID);
	
	// prepare for layout
    AFX_SIZEPARENTPARAMS layout;
    layout.hDWP = m_bLayoutQuery ?
            NULL : ::BeginDeferWindowPos(m_arrBars.GetSize());

    CPoint pt(-afxData.cxBorder2, -afxData.cyBorder2);

    BOOL bDrawBarForRow = FALSE;                    // true if we should draw a bar for this row
    BOOL bDrawBarWithinRow = FALSE;                 // true if we should draw a bar for this column
    BOOL bPrevBarSizeable = FALSE;                  // true if previous bar was sizeable


    DeleteSplitterRects();          // clear the splitter rects
    int nWidth = 0;
    int nFirstSplitterInRow = 0;
    int nFirstPaneInRow = 0;
    BOOL bFirstPaneInRow = TRUE;

    // layout all the control bars
	int nLastVisSep = -1;
    int nFirstSizeableInRow, nLastSizeableInRow;
    for (int nPos = 0; nPos < m_arrBars.GetSize(); nPos++)
    {
		void * pVoid = m_arrBars[nPos];
		CControlBar* pBar = GetDockedControlBar(nPos);
        if (pVoid != NULL)
        {
            if (pBar != NULL && pBar->IsVisible())
            {
                BOOL bBarSizeable = IsSizeable(pBar);
                
                if (bFirstPaneInRow)
                {
                    bFirstPaneInRow = FALSE;        // remember where the first pane in the row is..
                    nFirstPaneInRow = nPos;

                    GetFirstLastSizeableInRow(nPos, nFirstSizeableInRow, nLastSizeableInRow);         
                    if (m_dwStyle & (CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT))     // left/top: decide whether to draw a bar before the row
                    {
                        bDrawBarForRow = (nFirstSizeableInRow != -1 ? TRUE : FALSE);
                    }

                    if (bDrawBarForRow)    // use value from previous examining of the row
                    {
                        if (bHorz)
                        {
                            AddSplitterRect(SPLITTER_HORZ, pt.x, pt.y, 0 ,pt.y + CY_SPLIT, nPos);   // width set at end
                            pt.y += CY_SPLIT;
                        }
                        else
                        {
                            AddSplitterRect(SPLITTER_VERT, pt.x, pt.y, pt.x + CX_SPLIT, 0, nPos);   // height set at end
                            pt.x += CX_SPLIT;
                        }
                        bDrawBarForRow = FALSE;
                    }
                }
                else
                {   // Not the first pane in the row. Should we add a splitter between the elements in the row ?
                    // If either this 
                    if ( (bPrevBarSizeable || bBarSizeable) 
                        && (nPos <= nLastSizeableInRow && nPos > nFirstSizeableInRow) )
                    {
                        if (bHorz)
                        {
                            AddSplitterRect(SPLITTER_VERT, pt.x, pt.y, pt.x + CX_SPLIT, 0, nPos); // width set at end of row
                            pt.x += CX_SPLIT;
                        }
                        else
                        {
                            AddSplitterRect(SPLITTER_HORZ, pt.x, pt.y, 0, pt.y + CY_SPLIT, nPos); // width set at end of row
                            pt.y += CY_SPLIT;
                        }
                    }
				}                                                                // side by side are non-sizeable

                bPrevBarSizeable = bBarSizeable;
                if (bBarSizeable)
                {
                    bDrawBarWithinRow = TRUE;
                    bDrawBarForRow = TRUE;          // hit a sizeable bar, so we should draw a row
                }

                // get ideal rect for bar
				CSize sizeBar = pBar->CalcFixedLayout(FALSE,
                        (pBar->m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE);
				CRect rect(pt, sizeBar);

                // get current rect for bar
                CRect rectBar;
                pBar->GetWindowRect(&rectBar);
                ScreenToClient(&rectBar);

                if (bHorz)
                {
                    // change position if size changed or top not the same or
                    // rectbar.left < rect.left
                    // if floating compress
                    pt.x = rectBar.left;
                    if (rect.Size() != rectBar.Size() ||
                            rect.top != rectBar.top ||
                            (rectBar.left != rect.left && !m_bFloating) ||
                            (rectBar.left != rect.left && m_bFloating))
                    {
                        AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
                        pt.x = rect.left;
                    }
                    pt.x += sizeBar.cx - afxData.cxBorder2;
                    nWidth = max(nWidth, sizeBar.cy);
                }
                else
                {
                    // change position if size changed or top not the same or
                    // rectbar.left < rect.left
                    // if floating compress
                    pt.y = rectBar.top;
                    if (rect.Size() != rectBar.Size() ||
                            rect.left != rectBar.left ||
                            (rectBar.top != rect.top && !m_bFloating) ||
                            (rectBar.top != rect.top && m_bFloating))
                    {
                        AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
                        pt.y = rect.top;
                    }
                    pt.y += sizeBar.cy - afxData.cyBorder2;
                    nWidth = max(nWidth, sizeBar.cx);
                }
				// repositioned the bar, so update the MRU dock position.
				CDockContext * pDockContext = pBar->m_pDockContext;
				ASSERT(pDockContext != NULL);
				if (pDockContext != NULL)
				{
					pDockContext->m_rectMRUDockPos = rect;
					pDockContext->m_uMRUDockID = uDockBarID;
				}			

				// handle any delay/show hide for the bar
				pBar->RecalcDelayShow(&layout);
		
			}
        }
        else
		{
			//if (nWidth != 0)
            if (!bFirstPaneInRow)	// FALSE if we've hit anything....
            {
                 // end of row because pBar == NULL
                if (bHorz)
                {
                    pt.y += nWidth - afxData.cyBorder2;
                    sizeFixed.cx = max(sizeFixed.cx, pt.x);
                    sizeFixed.cy = max(sizeFixed.cy, pt.y);
                    pt.x = -afxData.cxBorder2;
                    SetSplitterSizeInRange(nFirstSplitterInRow, SPLITTER_VERT, pt.y);
				}
                else
                {
                    pt.x += nWidth - afxData.cxBorder2;
                    sizeFixed.cx = max(sizeFixed.cx, pt.x);
                    sizeFixed.cy = max(sizeFixed.cy, pt.y);
                    pt.y = -afxData.cyBorder2;
                    SetSplitterSizeInRange(nFirstSplitterInRow, SPLITTER_HORZ, pt.x);
				}
				nLastVisSep = nPos;			// record separator for last vis position
			}
			nFirstSplitterInRow = max(m_SplitArr.GetSize(), 0);
			nWidth = 0;
			bDrawBarWithinRow = FALSE;
			bFirstPaneInRow = TRUE;
		}
	}

    if (m_dwStyle & (CBRS_ALIGN_TOP | CBRS_ALIGN_LEFT))                         // there is at least one pane.    
    {
        if (nFirstPaneInRow != 0 && bDrawBarForRow) 
    
        {
            ASSERT(nLastVisSep != -1);
	        //while (m_arrBars[nLastVisibleBar] != NULL)
		        //nLastVisibleBar++;
	        
	        if (m_dwStyle & CBRS_ALIGN_TOP)
            {
                AddSplitterRect(SPLITTER_HORZ, pt.x, pt.y, 0 , pt.y + CY_SPLIT, nLastVisSep);
                sizeFixed.cy += CY_SPLIT;
            }
            else
            {
                AddSplitterRect(SPLITTER_VERT, pt.x, pt.y, pt.x + CX_SPLIT, 0, nLastVisSep);
                sizeFixed.cx += CX_SPLIT;
            }
        }
    }

    if (!m_bLayoutQuery)
    {
            // move and resize all the windows at once!
        if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
            TRACE0("Warning: DeferWindowPos failed - low system resources.\n");
    }

    // Finally go back and set the size of the bars between the rows
    if (bHorz)
        SetSplitterSizeInRange(0, SPLITTER_HORZ, sizeFixed.cx);         // set widths of inter-rows
    else
        SetSplitterSizeInRange(0, SPLITTER_VERT, sizeFixed.cy);         // set heights of inte-rcolumns

    return sizeFixed;

}

void CResizableDockBar::AddSplitterRect(int type, int x1, int y1, int x2, int y2, int nPos)
{
//TRACE0("CResizableDockBar::AddSplitterRect\n");
    CSplitterRect * pSplit = new CSplitterRect(type, CRect(x1, y1, x2, y2));
    pSplit->m_nPos = nPos;
    ASSERT( pSplit != NULL);
    m_SplitArr.Add(pSplit);
}

void CResizableDockBar::SetSplitterSizeInRange(int start, int type, int length)
{
//TRACE0("CResizableDockBar::SetSplitterSizeInRange\n");
    ASSERT(type == SPLITTER_VERT || type == SPLITTER_HORZ);
    ASSERT(start >= 0 && start <= m_SplitArr.GetSize());

    for (int i = m_SplitArr.GetUpperBound(); i >= start; i--)
    {
        CSplitterRect * pItem = (CSplitterRect *)m_SplitArr[i];
        if (pItem->m_type == type)
        {
            if (type == SPLITTER_VERT)
                pItem->m_rect.bottom = length;
            else
                pItem->m_rect.right = length;
        }
    }
}

void CResizableDockBar::DeleteSplitterRects()
{
//TRACE0("CResizableDockBar::DeleteSplitterRects\n");
    for (int i = m_SplitArr.GetUpperBound(); i >= 0 ; i--)
        delete (m_SplitArr[i]);
    m_SplitArr.RemoveAll();
}

CSplitterRect * CResizableDockBar::HitTest(CPoint pt)
{
//TRACE0("CResizableDockBar::HitTest\n");
	for (int i = m_SplitArr.GetUpperBound(); i >= 0; i--)
    {
    	CSplitterRect *pSplit = GetSplitter(i);
        if (pSplit->m_rect.PtInRect(pt))
        	return(pSplit);
    }
    return NULL;
}

int CResizableDockBar::StartPosOfRow(int nPos)
{
//TRACE0("CResizableDockBar::StartPosOfRow\n");
    if (nPos > 0)
    {
        if (m_arrBars[nPos] == NULL)
            nPos --;
        while (nPos >= 0)
        {
            if (m_arrBars[nPos] == NULL)
                return (nPos + 1);
            nPos --;
        }
    }
    return 0;
}

int CResizableDockBar::StartPosOfPreviousRow(int nPos)
{
//TRACE0("CResizableDockBar::StartPosOfPreviousRow\n");
    ASSERT (nPos > 0);
    if (nPos >= m_arrBars.GetUpperBound())
        return (StartPosOfRow(nPos));
    else
        return StartPosOfRow(nPos - 1);
}

void CResizableDockBar::GetRowSizeInfo(int nPos,  ROWSIZEINFO * pRZI, const CPtrArray & arrBars)
{
//TRACE0("CResizableDockBar::GetRowSizeInfo\n");
	BOOL bHorz = IsBarHorizontal();

    // zero all the fields
    memset (pRZI, 0, sizeof (ROWSIZEINFO));
    BOOL bPrevBarSizeable = FALSE;

    // get start/end positions of bars
    int nLastSizeableInRow, nFirstSizeableInRow;
    GetFirstLastSizeableInRow(nPos, nFirstSizeableInRow, nLastSizeableInRow);

	pRZI->nFixedWidth -= (bHorz ? afxData.cxBorder2 : afxData.cyBorder2);

    while (nPos <= arrBars.GetUpperBound())
    {
    	CRect rect;
        void * pVoid = arrBars[nPos];
		if (pVoid == NULL)
        	break;                  // end of the row
		CControlBar * pBar = ::GetDockedControlBar(nPos, arrBars);
        
        if (pBar!= NULL && pBar->IsVisible())
		{	
			// get ideal rect for bar
			CSize szPane = pBar->CalcFixedLayout( FALSE, bHorz);
            int nWidth = max (0, (bHorz ? szPane.cx : szPane.cy) );
            int nHeight = max (0, (bHorz ? szPane.cy : szPane.cx) );

            pRZI->nTotalBars ++;
            if (nHeight > pRZI->nMaxHeight)
                pRZI->nMaxHeight = nHeight;

            // Would CalcFixedLayout add a splitter here ? Just count the splitters for now.
            BOOL bIsSizeable = IsSizeable(pBar);
			if ( (bPrevBarSizeable || bIsSizeable)
                  && (nPos <= nLastSizeableInRow && nPos > nFirstSizeableInRow) )
            {
                pRZI->nFixedWidth += (bHorz ? CX_SPLIT : CY_SPLIT);    
            }
                
            bPrevBarSizeable = bIsSizeable;
            if (bIsSizeable)
            {
                pRZI->nFlexBars ++;
                pRZI->nFlexWidth += nWidth;
            }
            else
            {
                pRZI->nFixedWidth += nWidth;
                
				if (nHeight > pRZI->nMaxFixedHeight)
 	            	pRZI->nMaxFixedHeight = nHeight;
            }
            pRZI->nFixedWidth -= (bHorz ? afxData.cxBorder2 : afxData.cyBorder2);
        }
        nPos ++;
    }
   	
    pRZI->nTotalWidth = pRZI->nFixedWidth + pRZI->nFlexWidth;
	return;
}

BOOL CResizableDockBar::AdjustAllRowSizes(int nNewSize)
{
//TRACE0("CResizableDockBar::AdjustAllRowSizes\n");
    BOOL bAdjusted = FALSE;
    int nPos = 0;
    while (nPos < m_arrBars.GetSize())
    {
        CControlBar * pBar = (CControlBar *) m_arrBars[nPos];
        if (pBar == NULL)
        {                                               // skip over NULLs
			nPos ++;
            continue;
        }
        bAdjusted |= AdjustRowSizes(nPos, nNewSize, m_arrBars);                    // adjust the sizes on a row
        while (m_arrBars[nPos] != NULL)                 // skip to end of row
                nPos++;
    }
    return bAdjusted;
}

BOOL CResizableDockBar::AdjustRowSizes(int nPos, int nNewSize, CPtrArray & arrBars)
{
//TRACE0("CResizableDockBar::AdjustRowSizes\n");
	BOOL bHorz = IsBarHorizontal();

    ROWSIZEINFO RZI;
    GetRowSizeInfo(nPos, &RZI, arrBars);
    if (RZI.nFlexBars == 0)
    	return FALSE;                   // no flexible bars - nothing to do !

	int nTotalSizeChange = (nNewSize - RZI.nTotalWidth);
    int nSizeChangeRemaining = nTotalSizeChange;
	int nSizeChange = nTotalSizeChange / RZI.nFlexBars;
	// have to apply this size change to the bars on this row. Note: This will work
    // by setting the docked size of the controls bars directly. Then ReCalcLayout will
    // do the rest.
    int nCountFlexBars = 0;
    while (TRUE)
    {
    	void * pVoid = arrBars[nPos];
		if (pVoid == NULL)
            break;          // end of the row, stop
		CResizableControlBar * pBar = (CResizableControlBar *)::GetDockedControlBar(nPos, arrBars);	// note:slight abuse of cast
        
        if (pBar != NULL && pBar->IsVisible() && IsSizeable(pBar))
        {
        	int nWidth = (bHorz ? pBar->m_HorzDockSize.cx : pBar->m_VertDockSize.cy);
			nCountFlexBars ++;
            if (nCountFlexBars == RZI.nFlexBars)    // last bar adjust size change
            {
            	nSizeChange = nSizeChangeRemaining;
            	// nSizeChange = nTotalSizeChange - ((RZI.nFlexBars - 1) * nSizeChange);
            }
            else
			{
				nSizeChange = (nWidth + 1) * nTotalSizeChange / (RZI.nFlexWidth + RZI.nFlexBars);
			}
			
#ifdef _VERBOSE_TRACE
			CString strTitle;
			pBar->GetWindowText(strTitle);
			TRACE("Size change: %d on %s\n", nSizeChange, strTitle);
#endif			
			int nNewWidth = max(nWidth + nSizeChange, 0);
			nSizeChangeRemaining -= (nNewWidth - nWidth);
			
			if (bHorz)
            {
				pBar->m_HorzDockSize.cx = nNewWidth;
                pBar->m_HorzDockSize.cy = RZI.nMaxHeight;
				SetWindowSize(pBar, pBar->m_HorzDockSize);
			}
            else
            {
                pBar->m_VertDockSize.cy = nNewWidth;
            	pBar->m_VertDockSize.cx = RZI.nMaxHeight;
				SetWindowSize(pBar, pBar->m_VertDockSize);
            }
         }
        nPos++;
    }

	return TRUE;
}

void CResizableDockBar::TileDockedBars()
{
//TRACE0("CResizableDockBar::TileDockedBars\n");
    int nPos = 0;
    while (nPos < m_arrBars.GetSize())
    {
        CControlBar * pBar = (CControlBar *) m_arrBars[nPos];
        if (pBar == NULL)
        {                                               // skip over NULLs
            nPos ++;
            continue;
        }
        TileDockedBarsRow(nPos);                                        // adjust the sizes on a row
        while (m_arrBars[nPos] != NULL)                         // skip to end of row
            nPos++;
    }
    return;
}

void CResizableDockBar::TileDockedBarsRow(int nPos)
{
//TRACE0("CResizableDockBar::TileDockedBarsRow\n");
    BOOL bHorz = IsBarHorizontal();

    ROWSIZEINFO RZI;
    GetRowSizeInfo(nPos, &RZI, m_arrBars);
    if (RZI.nFlexBars == 0)
            return;                         // no flexible bars - nothing to do !

    int nNewSize = (bHorz ? m_LayoutSize.cx : m_LayoutSize.cy);
    int nTotalSize = max (0, nNewSize - RZI.nFixedWidth);
    int nNewWidth = nTotalSize / RZI.nFlexBars;

    int nCountFlexBars = 0;
    while(TRUE)
    {
		void * pVoid = m_arrBars[nPos];    
		if (pVoid == NULL)
                break;          // end of the row, stop
		CResizableControlBar * pBar = (CResizableControlBar *) GetDockedControlBar(nPos); // note:slight abuse of cast
        
        if (pBar != NULL && IsSizeable(pBar) && pBar->IsVisible())
        {
            nCountFlexBars ++;
            if (nCountFlexBars == RZI.nFlexBars)    // last bar adjust size change
            {
                nNewWidth = nTotalSize - ((RZI.nFlexBars - 1) * nNewWidth);
            }
            if (bHorz)
            {
                pBar->m_HorzDockSize.cx = nNewWidth;
                pBar->m_HorzDockSize.cy = RZI.nMaxHeight;
            }
            else
            {
                pBar->m_VertDockSize.cy = nNewWidth;
                pBar->m_VertDockSize.cx = RZI.nMaxHeight;
            }
        }
        nPos++;
    }
}

BOOL CResizableDockBar::WasBarHidden(CControlBar *pBar)
{
//TRACE0("CResizableDockBar::WasBarHidden\n");
	for (int i= 0; i < m_arrHiddenBars.GetSize(); i++)
		{							
			if (m_arrHiddenBars[i] == pBar)
				return TRUE;
		}
	return FALSE;
}

LRESULT CResizableDockBar::OnSizeParent(WPARAM wParam, LPARAM lParam)
{
//TRACE0("CResizableDockBar::OnSizeParent\n");
	AFX_SIZEPARENTPARAMS* lpLayout = (AFX_SIZEPARENTPARAMS*)lParam;
	
	BOOL bInvalidate = FALSE;
	BOOL bHorz = IsBarHorizontal();

    CRect LayRect;
    LayRect.CopyRect(&lpLayout->rect);
    CSize LaySize = LayRect.Size();  // maximum size available
	int nLayoutWidth = bHorz ? LaySize.cx : LaySize.cy;
	BOOL bLayoutWidthChanged = (nLayoutWidth != (bHorz ? m_LayoutSize.cx : m_LayoutSize.cy));
	m_LayoutSize = LaySize;

	// Attempt to detect bars that have changed state from Hidden->Visible. For these we attempt
	// to adjust the other (previously visible) bars on the row so that the newly shown bars
	// restore their previous size.
	CPtrArray	arrVisibleBarsInRow;		// Bars visible in the row (ones we can shrink)
	int nWidthNeeded = 0;
	int i;
	for (i = 0; i < m_arrBars.GetSize(); i++)
    {
		if (m_arrBars[i] == NULL)
		{
			ROWSIZEINFO RZI;
			if (arrVisibleBarsInRow.GetSize() != 0 && nWidthNeeded != 0)
			{
				arrVisibleBarsInRow.Add(NULL);
				
				GetRowSizeInfo(0, &RZI, arrVisibleBarsInRow);
				int nNewWidth = max(0, RZI.nTotalWidth - nWidthNeeded);
				AdjustRowSizes(0, nNewWidth, arrVisibleBarsInRow);
			}
			nWidthNeeded = 0;
			arrVisibleBarsInRow.RemoveAll();
		}
		else
		{
			CControlBar* pBar = GetDockedControlBar(i);
			if (pBar != NULL)
			{
				if (pBar->IsVisible())
				{
					if (WasBarHidden(pBar))
					{
						CRect rect;
						pBar->GetWindowRect(&rect);
						nWidthNeeded += (bHorz ? rect.Width() : rect.Height());
					}
					else
					{
						arrVisibleBarsInRow.Add(pBar);		// Track visible bars in this row that we can shrink
					}
				}
			}
		}
	}
	
	// construct new array of bars that are hidden in this dockbar
	m_arrHiddenBars.RemoveAll();
	for (i = 0; i < m_arrBars.GetSize(); i++)
    {
		CControlBar* pBar = GetDockedControlBar(i);
		if (pBar != NULL && ! pBar->IsVisible())
			m_arrHiddenBars.Add(pBar);
	}

	int nCheckSum = CheckSumBars();

    // any other changes and we size the bars to fit the layout width
	if (bLayoutWidthChanged || nCheckSum != m_CountBars)
    {
        AdjustAllRowSizes(nLayoutWidth);
        m_CountBars = nCheckSum;
        InvalidateRect(NULL);   // force redraw of the dock bar - seems a bit of a sledgehammer
    }

	// set m_bLayoutQuery to TRUE if lpLayout->hDWP == NULL
	BOOL bLayoutQuery = m_bLayoutQuery;
    m_bLayoutQuery = (lpLayout->hDWP == NULL);
	LRESULT lResult = CControlBar::OnSizeParent(wParam, lParam);
    // restore m_bLayoutQuery
    m_bLayoutQuery = bLayoutQuery;

    return lResult;
}

int CResizableDockBar::CheckSumBars() const
{
//TRACE0("CResizableDockBar::CheckSumBars\n");
	int nCount = 0;         // total no of bars
    int nCheckSum = 0;      // XOR, power of 2 checksum
    for (int i = 0; i < m_arrBars.GetSize(); i++)
    {
    	if (m_arrBars[i] == NULL)
			nCheckSum *= 2;
		else
		{        
			CControlBar* pBar = GetDockedControlBar(i);
			ASSERT(pBar == NULL || pBar->IsKindOf(RUNTIME_CLASS(CControlBar)));
        	if (pBar != NULL && pBar->IsVisible())
            {
            	nCheckSum++;
                nCount++;
            }
		}
	}
        // LSB = actual no of dockbars (limited to 256 !)
        // bits 8-31 = checksum based on layout of rows.
    return ((nCheckSum << 8) | (nCount & 0xff));
}

void CResizableDockBar::AdjustForNewBar(CControlBar *pNewBar)		
{
//TRACE0("CResizableDockBar::AdjustForNewBar\n");
	int nPos = FindBar(pNewBar);
	ASSERT(nPos != -1);			// bar should have been found.
	
	// Go back to start of row.
	while (m_arrBars[nPos] != NULL)
		nPos--;

	nPos++;

	// create an array for the bars on the row, that aren't this one
	CPtrArray arrOtherBarsInRow;
	while (nPos < m_arrBars.GetSize() && m_arrBars[nPos] != NULL)
	{
		CControlBar* pBar = GetDockedControlBar(nPos);
		if (pBar != pNewBar)
			arrOtherBarsInRow.Add(pBar);
		nPos++;
	}

	ROWSIZEINFO RZI;
	arrOtherBarsInRow.Add(NULL);
	GetRowSizeInfo(0, &RZI, arrOtherBarsInRow);
	CRect rcNewBar;
	pNewBar->GetWindowRect(&rcNewBar);
	int nWidthNeeded = (IsBarHorizontal() ? rcNewBar.Width() : rcNewBar.Height());
	int nNewWidth = max(0, RZI.nTotalWidth - nWidthNeeded);
	AdjustRowSizes(0, nNewWidth, arrOtherBarsInRow);
}

CSplitterRect * CResizableDockBar::SetHitCursor(CPoint pt)
{
//TRACE0("CResizableDockBar::SetHitCursor\n");
	// Set up the split cursors here. This guarantees the app is around
    if (afxData.hcurSizeWE == NULL)
    { 
    	afxData.hcurSizeWE = AfxGetApp()->LoadCursor(AFX_IDC_HSPLITBAR);
		if (afxData.hcurSizeWE == NULL)
    		afxData.hcurSizeWE = ::LoadCursor(NULL, IDC_SIZEWE);
	}			
   
    if (afxData.hcurSizeNS == NULL)
    {
    	afxData.hcurSizeNS = AfxGetApp()->LoadCursor(AFX_IDC_VSPLITBAR);
		if (afxData.hcurSizeNS == NULL)
			afxData.hcurSizeNS = ::LoadCursor(NULL, IDC_SIZENS);
	}


    HCURSOR hcurNew;
    CSplitterRect * pSplit = HitTest(pt);
    if (pSplit != NULL)
   		hcurNew = (pSplit->m_type == SPLITTER_VERT ? afxData.hcurSizeWE : afxData.hcurSizeNS);
    else
        hcurNew = afxData.hcurArrow;

    ::SetCursor(hcurNew);
    return pSplit;
}

void CResizableDockBar::StartTracking(CPoint pt)
{
//TRACE0("CResizableDockBar::StartTracking\n");
    ASSERT(m_pSplitCapture != NULL);

    // Some organizational flags: helps to cut down the cases
    BOOL bHorz      = IsBarHorizontal();
    BOOL bVertSplitter = (m_pSplitCapture->m_type == SPLITTER_VERT);
    BOOL bRowDivider = ((!bVertSplitter) && bHorz) || (bVertSplitter && (!bHorz));
    int nPos = m_pSplitCapture->m_nPos;

    CResizableRectTracker MvRect;

    // attempt to clip move rect by current layout size of the dockbar
    CRect LayoutRect(CPoint(0,0), m_LayoutSize);
    MvRect.m_rect = m_pSplitCapture->m_rect;

	// Shrink the splitter rectangle to end up with a solid bar
	if (bVertSplitter)
		MvRect.m_rect.InflateRect(-2, 0);
	else
		MvRect.m_rect.InflateRect(0, -2);


    MvRect.m_rect.IntersectRect(MvRect.m_rect, LayoutRect);
    ASSERT(!(MvRect.m_rect.IsRectEmpty()));
    
    // get main window - all dragging is done relative to this window.
	// this should be the frame window.....
	CWnd * pClipWnd = GetParentFrame();

	
    if (bVertSplitter)
		MvRect.m_nStyle |= RectTracker_OnlyMoveHorz;      // allow horizontal movement
    else
    	MvRect.m_nStyle |= RectTracker_OnlyMoveVert;      // allow horizontal movement

    
	// workout a limiting rectangle; - very dependent on orientation. Eventually may need to work
    // out the fixed size of the windows beyond the current splitter, so it could get nasty.
    // for now just use the client area of the window
    ROWSIZEINFO RZI;
    CRect LimitRect;
    pClipWnd->GetClientRect(&LimitRect);
    pClipWnd->ClientToScreen(&LimitRect);
    ScreenToClient(&LimitRect);			// map to co-ords of pWnd

#ifdef _VERBOSE_TRACE
	Dump(afxDump);
#endif

    if (bRowDivider)
    {
		if (m_dwStyle & (CBRS_ALIGN_TOP | CBRS_ALIGN_LEFT))             // apply to previous row for top/bottom
        {
        	nPos = StartPosOfPreviousRow(nPos);
            ASSERT(nPos != 0);
       	}
       	GetRowSizeInfo(nPos, &RZI, m_arrBars);             // get the row information:
       	switch (m_dwStyle & CBRS_ALIGN_ANY)
       	{
        	case CBRS_ALIGN_BOTTOM:
                LimitRect.bottom = min (LimitRect.bottom, MvRect.m_rect.top + (RZI.nMaxHeight - RZI.nMaxFixedHeight));
                break;
            case CBRS_ALIGN_TOP:
            	LimitRect.top = max (LimitRect.top, MvRect.m_rect.top - (RZI.nMaxHeight - RZI.nMaxFixedHeight));
              	break;
            case CBRS_ALIGN_LEFT:
                LimitRect.left = max (LimitRect.left, MvRect.m_rect.left - (RZI.nMaxHeight - RZI.nMaxFixedHeight));
                break;
            case CBRS_ALIGN_RIGHT:
                LimitRect.right = max (LimitRect.right, MvRect.m_rect.left + (RZI.nMaxHeight - RZI.nMaxFixedHeight));
                break;
            default:
                ASSERT(FALSE);
  		}
    }
	else
    {
        // How far can we go to down/right
        int nFlexToRight, nFlexToLeft;
        int nDownRight = ShrinkRowToRight(nPos, 16000, FALSE, &nFlexToRight);
        int nUpLeft = ShrinkRowToLeft(nPos - 1, 16000, FALSE, &nFlexToLeft);

        if ((nFlexToRight + nFlexToLeft) <= 1 )  // only 1 flex bar in the array - no movement !
        {
            nDownRight = 0;
            nUpLeft = 0;
        }

        if (bHorz)
        {
			LimitRect.left = max(LimitRect.left, MvRect.m_rect.left - nUpLeft);
            LimitRect.right = min(LimitRect.right, MvRect.m_rect.left + nDownRight);
        }
        else
        {
            LimitRect.top = max(LimitRect.top , MvRect.m_rect.top - nUpLeft);
            LimitRect.bottom = min(LimitRect.bottom, MvRect.m_rect.top + nDownRight);
        }
    }

    // Now enter the CMoveRect's modal track function
    MvRect.m_LimitRect = LimitRect;	  
    if (!MvRect.TrackFromHitTest (HTCAPTION, this, pt, pClipWnd))
     	return;

        // Workout the size change cause by the drag:
	int nSizeChange;
    if (m_pSplitCapture->m_type == SPLITTER_VERT)
    	nSizeChange = MvRect.m_rect.left - MvRect.m_OrigRect.left;
	else
        nSizeChange = MvRect.m_rect.top - MvRect.m_OrigRect.top;
    if (nSizeChange == 0)
        return;

    // CSplitterRect::m_nPos is the pane position that the splitter was created at.
    // For a row divider: this is the pane that immediately starts the next row
    // For a column divider: this is the pane that is to the right of it.
    // special case will be needed for the splitter used at the end of a left/top aligned
    // dockbar.
    int nSizeMoved;
    if (bRowDivider)
    {
        if (m_dwStyle & (CBRS_ALIGN_TOP | CBRS_ALIGN_LEFT))             // apply to previous row for top/bottom
        {
             nSizeChange = -nSizeChange;             // reverse polarity of change
        }

        int nNewHeight = max (RZI.nMaxFixedHeight, RZI.nMaxHeight - nSizeChange);

        // go along the rows applying size change to each bar in turn....
        while (nPos < m_arrBars.GetSize())	// need to check size now
        {
            void * pVoid = m_arrBars[nPos];
			if (pVoid == NULL)
                break;
            CResizableControlBar * pBar = (CResizableControlBar *)GetDockedControlBar(nPos);
            // should check for visible ???
			if (pBar != NULL && pBar->IsVisible() && IsSizeable(pBar))
            {
                if (bHorz)
                   	pBar->m_HorzDockSize.cy = nNewHeight;
                else
                	pBar->m_VertDockSize.cx = nNewHeight;
            }
            nPos ++;
     	}

    }
    else
    {
        if (nSizeChange < 0)
        {                                                               // move to left/up
        	nSizeMoved = ShrinkRowToLeft(nPos - 1, - nSizeChange, TRUE);
            ShrinkRowToRight(nPos, - nSizeMoved, TRUE);
        }
        else
        {                                                               // move to right/down
        	nSizeMoved = ShrinkRowToRight(nPos, nSizeChange, TRUE);
            ShrinkRowToLeft(nPos - 1, - nSizeMoved, TRUE);
        }

    }
    // reposition the bars..
    InvalidateRect(NULL);
    //((CFrameWnd *)AfxGetMainWnd())->RecalcLayout();
    ASSERT(pClipWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)));
    ((CFrameWnd *)pClipWnd)->RecalcLayout();
    return;
}

int CResizableDockBar::ShrinkRowToLeft(int nPos, int nOrigAmount, BOOL bApply, int * pnFlexBars)
{
//TRACE0("CResizableDockBar::ShrinkRowToLeft\n");
    ASSERT(nPos >= 0 && nPos <= m_arrBars.GetSize());

    int nAmount = nOrigAmount;
    int nFlexBars = 0;
    while (nPos >= 0)
    {
		if (m_arrBars[nPos] == NULL)
            break;
        CResizableControlBar * pBar = (CResizableControlBar *)GetDockedControlBar(nPos);
        if (pBar!= NULL && IsSizeable(pBar) && pBar->IsVisible())
        {
            nFlexBars ++;
            if (IsBarHorizontal())
            {
                if (pBar->m_HorzDockSize.cx >= nAmount)
                {
                    if (bApply)
                        pBar->m_HorzDockSize.cx -= nAmount;
                    nAmount = 0;
                    break;
                }
                else
                {
                    nAmount -= pBar->m_HorzDockSize.cx;
                    if (bApply)
                        pBar->m_HorzDockSize.cx = 0;
                }
            }
            else
            {
                if (pBar->m_VertDockSize.cy >= nAmount)
                {
                    if (bApply)
                        pBar->m_VertDockSize.cy -= nAmount;
                    nAmount = 0;
                    break;
                }
                else
                {
                    if (bApply)
                        pBar->m_VertDockSize.cy = 0;
                    nAmount -= pBar->m_VertDockSize.cy;
                }
            }

        }
        nPos--;
    }

    // return no of flexible components encountered (if pointer supplied)
    if (pnFlexBars != NULL)
        *pnFlexBars = nFlexBars;

    // reached left/top of row - return what size is still left to allocate
    return (nOrigAmount - nAmount);
}

int CResizableDockBar::ShrinkRowToRight(int nPos, int nOrigAmount, BOOL bApply, int *pnFlexBars)
{
//TRACE0("CResizableDockBar::ShrinkRowToRight\n");
    ASSERT(nPos >= 0 && nPos <= m_arrBars.GetSize());
    int nAmount = nOrigAmount;
    int nFlexBars = 0;

    CResizableControlBar * pLastBar = NULL;

    while (nPos < m_arrBars.GetSize())
    {
        if (m_arrBars[nPos] == NULL)
			break;

		CResizableControlBar * pBar = (CResizableControlBar *)GetDockedControlBar(nPos);
        if (pBar != NULL)
		{				
			pLastBar = pBar;
			if (IsSizeable(pBar) && pBar->IsVisible())
			{
				nFlexBars ++;
				if (IsBarHorizontal())
				{
					if (pBar->m_HorzDockSize.cx >= nAmount)
					{
						if (bApply)
							pBar->m_HorzDockSize.cx -= nAmount;
						nAmount = 0;
						break;
					}
					else
					{
						nAmount -= pBar->m_HorzDockSize.cx;
						if (bApply)
							pBar->m_HorzDockSize.cx = 0;
					}
				}
				else		// Vertical
				{
					if (pBar->m_VertDockSize.cy >= nAmount)
					{
						if (bApply)
							pBar->m_VertDockSize.cy -= nAmount;
						nAmount = 0;
						break;
					}
					else
					{
						nAmount -= pBar->m_VertDockSize.cy;
						if (bApply)
							pBar->m_VertDockSize.cy = 0;
					}
				}
				
			}
        }
		nPos++;
    }
    // We've reached the end of the row. If we still have size left to find, the only way we can do it is if there
    // is a flexble area at the end of the control bars..
    if (nAmount > 0 && pLastBar != NULL)
    {
        int nSub;
        CRect rect;
        pLastBar->GetWindowRect(&rect);
        ScreenToClient(&rect);
        if (IsBarHorizontal())
            nSub = m_LayoutSize.cx - rect.right;
        else
            nSub = m_LayoutSize.cy - rect.bottom;
        nAmount -= min (max( 0, nSub), nAmount);
    }

    // return no of flexible components encountered (if pointer supplied)
    if (pnFlexBars != NULL)
        *pnFlexBars = nFlexBars;

    // return amount allocated
    return (nOrigAmount - nAmount);
}

CResizableControlBar * CResizableDockBar::GetFirstControlBar()
{
//TRACE0("CResizableDockBar::GetFirstControlBar\n");
    // CMiniDockFrameWnd assumes that if there's only one bar, then it's at position 1
    // in the array
    // need to make a check for 0 sized array however
	if (m_arrBars.GetSize() > 1)
		return ((CResizableControlBar *) GetDockedControlBar(1));
	else
		return NULL;
}

void CResizableDockBar::GetFirstLastSizeableInRow(int nPos, int & nPosFirst, int & nPosLast)
{
//TRACE0("CResizableDockBar::GetFirstLastSizeableInRow\n");
    nPosFirst = -1;
    nPosLast = -1;

    ASSERT(nPos >= 0 && nPos < m_arrBars.GetSize());
    while (nPos < m_arrBars.GetSize())
    {
		if (m_arrBars[nPos] == NULL)
			break;
		CControlBar *pBar = GetDockedControlBar(nPos);
        if (pBar!= NULL && IsSizeable(pBar)  && pBar->IsVisible())
        {
            if (nPosFirst == -1)
                nPosFirst = nPos;
            nPosLast = nPos;
        }
        nPos++;
    }
}

int CResizableDockBar::TestInsertPosition(CControlBar* pBarIns, CRect rect)
{
//TRACE0("CResizableDockBar::TestInsertPosition\n");
    CPoint ptMid(rect.left + rect.Width()/2, rect.top + rect.Height()/2);
	// hang-on: Don't we want to work in client co-ords ???
	ScreenToClient(&ptMid);
	
	ASSERT_VALID(this);
	ASSERT(pBarIns != NULL);

	int nPos = 0;
	int nPosInsAfter = 0;
	int nWidth = 0;
	int nTotalWidth = 0;
	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;

	for (nPos = 0; nPos < m_arrBars.GetSize(); nPos++)
	{
		void * pVoid = m_arrBars[nPos];
		CControlBar* pBar = GetDockedControlBar(nPos);

		if (pVoid == NULL)
		{
			nTotalWidth += nWidth - afxData.cyBorder2;
			nWidth = 0;
			if ((bHorz ? ptMid.y : ptMid.x) < nTotalWidth)
			{
				if (nPos == 0) // ie in first section....
					return 0;  // indicate before first position....
			//	if (nPos == 0) // first section
			//		m_arrBars.InsertAt(nPosInsAfter+1, (CObject*)NULL);
			//	m_arrBars.InsertAt(nPosInsAfter+1, pBarIns);
				return nPosInsAfter+1;
			}
			nPosInsAfter = nPos;
		}
		else
			if (pBar != NULL && pBar->IsVisible())	
			{
				CRect rectBar;
				pBar->GetWindowRect(&rectBar);
				ScreenToClient(&rectBar);
				nWidth = max(nWidth,
					bHorz ? rectBar.Size().cy : rectBar.Size().cx - 1);
				//if (bHorz ? rect.left > rectBar.left : rect.top > rectBar.top)
				// don't need above test - only interested if it should go on the row or not...
				nPosInsAfter = nPos;
			}
	}

	return nPosInsAfter+1;
}

int CResizableDockBar::BarsOnThisRow(CControlBar *pBarIns, CRect rect)
{
//TRACE0("CResizableDockBar::BarsOnThisRow\n");
	int nPos = TestInsertPosition(pBarIns, rect);
	
	// if inserting before the first row, or after the last row, then return 0
	// (there are no bars on this row).
	if (nPos == 0 ||nPos > m_arrBars.GetUpperBound())		// case if inserting before first bar in the array.
		return 0;		// return 0 to use the full size
	
	// go back to start of row.
	while (nPos != 0 && m_arrBars[nPos - 1] != 0)
		nPos --;

	int nCount = 0;
	while (TRUE)
	{
		void * pVoid = m_arrBars[nPos];
		CControlBar * pBar = GetDockedControlBar(nPos);
		if (pVoid == NULL)
			break;
		if (pBar != NULL && pBar != pBarIns) 
			nCount++;
		nPos++;
	}
	return nCount;
}

