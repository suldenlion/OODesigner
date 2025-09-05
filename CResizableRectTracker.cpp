#include "stdafx.h"
#include "CResizableRectTracker.h"

CResizableRectTracker::CResizableRectTracker()
{
//TRACE0("CResizableRectTracker::CResizableRectTracker\n");
	m_LimitRect.SetRectEmpty();
}

//------------------------------------------------------------------------------
BOOL CResizableRectTracker::TrackFromHitTest(int nHitTest, CWnd* pWnd, CPoint point,
	CWnd* pWndClipTo, BOOL bAllowInvert)
//------------------------------------------------------------------------------
{
//TRACE0("CResizableRectTracker::TrackFromHitTest\n");
	m_OrigRect = m_rect;		// save original rectangle
	m_bAllowInvert = bAllowInvert;
	int nHandle;
	switch (nHitTest)
	{
	case HTLEFT:
		nHandle = hitLeft;
		break;
	case HTRIGHT:
		nHandle = hitRight;
		break;
	case HTTOP:         
		nHandle = hitTop;
		break;
	case HTTOPLEFT:    
		nHandle = hitTopLeft;
		break;
	case HTTOPRIGHT:    
		nHandle = hitTopRight;
		break;
	case HTBOTTOM:      
		nHandle = hitBottom;
		break;
	case HTBOTTOMLEFT:  
		nHandle = hitBottomLeft;
		break;
	case HTBOTTOMRIGHT: 
		nHandle = hitBottomRight;
		break;
	default:
	    nHandle = hitMiddle;		// default is move
		break;
	}

	return CRectTracker::TrackHandle(nHandle, pWnd, point, pWndClipTo);
}




//-----------------------------------------------------------------------------
void CResizableRectTracker::DrawTrackerRect(LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd)
//-----------------------------------------------------------------------------
{
//TRACE0("CResizableRectTracker::DrawTrackerRect\n");
	// first, normalize the rectangle for drawing
	CRect rect = *lpRect;
	rect.NormalizeRect();

	// convert to client coordinates
	if (pWndClipTo != NULL)
	{
		pWnd->ClientToScreen(&rect);
		pWndClipTo->ScreenToClient(&rect);
	}
	CSize size(0, 0);
	if (!m_bFinalErase)
	{
		size.cx = 2;
		size.cy = 2;
	}
	// and draw it
	if (m_bFinalErase || !m_bErase)
		pDC->DrawDragRect(rect, size, m_rectLast, m_sizeLast);
	m_rectLast = rect;
	m_sizeLast = size; 
}


//-----------------------------------------------------------------------------
void CResizableRectTracker::AdjustRect(int nHandle, LPRECT lpRect)
//-----------------------------------------------------------------------------
{
//TRACE0("CResizableRectTracker::AdjustRect\n");
// clips to limiting rectangle...
	if (!m_LimitRect.IsRectNull())
	{
		if (nHandle == hitMiddle)  // if moving then have to ensure size is maintained...
		{
			CSize size = m_OrigRect.Size();
			lpRect->left = max (m_LimitRect.left , min (m_LimitRect.right , lpRect->left));
            lpRect->top =  max (m_LimitRect.top  , min (m_LimitRect.bottom - 10, lpRect->top ));
            lpRect->right  = lpRect->left + size.cx;
            lpRect->bottom = lpRect->top  + size.cy;
		}
		else
		{		
			CRect iRect;
			iRect.IntersectRect(m_LimitRect, lpRect);
			::CopyRect(lpRect, iRect);		
		}
	}

// enforces minimum width, etc
	CRectTracker::AdjustRect(nHandle, lpRect);

	if (m_nStyle & RectTracker_OnlyMoveHorz)
	{
		lpRect->top = m_OrigRect.top;
		lpRect->bottom = m_OrigRect.bottom;
	}
	
	if (m_nStyle & RectTracker_OnlyMoveVert)
	{
		lpRect->left = m_OrigRect.left;
		lpRect->right = m_OrigRect.right;
	}
	
}


