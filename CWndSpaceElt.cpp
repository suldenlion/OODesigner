#include "stdafx.h"
#include "CWndSpaceElt.h"
#include "macro_def.h"

static int CompareWndRect(const void *elem1, const void *elem2 )
{
	CRect rect1;
	CRect rect2;
	CWnd * pWnd1 = *((CWnd **)elem1);
	CWnd * pWnd2 = *((CWnd **)elem2);
	pWnd1->GetWindowRect(&rect1);
	pWnd2->GetWindowRect(&rect2);
	// array will be sorted into increasing order, so want the larger rectangles first.
	CSize size1 = rect1.Size();
	CSize size2 = rect2.Size();
	return ((size2.cx * size2.cy) - (size1.cx * size1.cy));
}

IMPLEMENT_DYNAMIC(CWndSpaceElt, CObject);

void CWndSpaceElt::PositionInSpcList(CWnd *pWnd, CObList & SpcList, DWORD dwOrient,
								CWnd * pParentWnd, CSize & ParentSize, HDWP hDwp)	
{
	CRect WndRect;
	pWnd->GetWindowRect(&WndRect);		// external dimensions of the window
	CSize WndSize;
	WndSize = WndRect.Size();			// size of rectangle
   	POSITION pos;

#ifdef _DEBUG
	CString strTitle;
	pWnd->GetWindowText(strTitle);
#ifdef _DEBUG_WNDPOS
	TRACE("Inserting Window: %s, cx = %d, cy = %d\n", LPCTSTR(strTitle), WndSize.cx, WndSize.cy);
#endif
	pos = SpcList.GetHeadPosition();
	int nTotalHeightBefore = 0;
	while (pos != NULL)
	{
		CWndSpaceElt * pSpcElt = (CWndSpaceElt *)SpcList.GetNext(pos);
		ASSERT(pSpcElt != NULL);
#ifdef _DEBUG_WNDPOS
		TRACE("    ht= %d w=%d\n", pSpcElt->ht, pSpcElt->wd);
#endif
		nTotalHeightBefore += pSpcElt->ht;
	}
	ASSERT(nTotalHeightBefore == ParentSize.cy);		
#endif

	int nHt = WndSize.cy;			// height of window....
	int nWd = WndSize.cx;			// width of window (used below)
	int nHtLeft;

	int nCurY = 0;					// current Y position of scan
	int nMinX = 0xffff;				// minimum X position found so far;
	int nMinY;						// again should be ok...
	
	POSITION MinListPos = NULL;		// position in the list with this minimum X;
	
	pos = SpcList.GetHeadPosition();
	while (pos != NULL)
	{
		POSITION posCurrent = pos;
		CWndSpaceElt * pSpcElt = (CWndSpaceElt *)SpcList.GetNext(pos);
		ASSERT(pSpcElt != NULL);
		ASSERT_VALID(pSpcElt);
		
		// if we inserted in this position, what would the width be ? 
		// Set nHtLeft, ThisPosX accordingly....
		nHtLeft = nHt;
		int nThisX = 0;
		POSITION posLoop = posCurrent;
		while (posLoop != NULL) 
		{
			CWndSpaceElt * pLoopSpcElt = (CWndSpaceElt *)SpcList.GetNext(posLoop);
			nThisX = max (nThisX, pLoopSpcElt->wd);
			if (nThisX > nMinX)
				break;		// give up if we're already beyond the current minimum
			nHtLeft -= pLoopSpcElt->ht;
			if (nHtLeft <= 0)
			{
				if (nThisX < nMinX)
				{
					nMinX = nThisX;
					MinListPos = posCurrent;	// acutually the position after the current index in the list
					nMinY = nCurY;
				}
				break;
			}
		}
		
   		nCurY += pSpcElt->ht;	// update current Y position.
   	}
	
	
	if (MinListPos == NULL || nMinX > ParentSize.cx)	// window wouldn't fit anywhere in the window cleanly, 
	{
#ifdef 	_DEBUG_WNDPOS
		TRACE("No insert position found\n");
#endif
			return;				// ignore this for now
	}

	ASSERT(MinListPos != NULL && nMinX < 0xffff);
	
	// work out the new position for the window
	// Might want to delay window positioning in future
	CPoint WndPt;
	WndPt.x = ((dwOrient & CBRS_ARRANGE_LEFT) ?  nMinX : ParentSize.cx - nMinX - WndSize.cx);
	WndPt.y = ((dwOrient & CBRS_ARRANGE_TOP)  ?  nMinY : ParentSize.cy - nMinY - WndSize.cy);
	ASSERT(WndPt.y >= -1);
	
#ifdef _DEBUG_WNDPOS
	TRACE("Positioning at: (%d, %d) nMinY=%d, nMinX=%d\n", WndPt.x, WndPt.y, nMinY, nMinX);
#endif
	
	// if not child of requested window, convert co-ords to Screen
	if ((pWnd->GetStyle() & WS_POPUP) || pWnd->GetParent() != pParentWnd)
		pParentWnd->ClientToScreen(&WndPt);
	

	CRect rcWnd;
	pWnd->GetWindowRect(rcWnd);
	// attempt to optimize by only moving windows that have changed position...
	if (rcWnd.TopLeft() != WndPt || rcWnd.Size() != WndSize)
	{
		if (hDwp == NULL)
  			pWnd->SetWindowPos(NULL, WndPt.x, WndPt.y, WndSize.cx, WndSize.cy,
								SWP_NOSIZE | SWP_NOZORDER);
		else
			::DeferWindowPos(hDwp, pWnd->m_hWnd, NULL, WndPt.x,  WndPt.y, WndSize.cx, WndSize.cy,
								SWP_NOSIZE | SWP_NOZORDER);
	}
	
	// now update the SpcList.
	nHtLeft = nHt;
	ASSERT(nHt > 0);
	pos = MinListPos;
	ASSERT(MinListPos != NULL);	// can't actually happen
	CWndSpaceElt * pSpcElt;
	POSITION InsertPos = NULL;
	while (pos != NULL)
	{
		POSITION Oldpos = pos;
		pSpcElt = (CWndSpaceElt *) SpcList.GetNext(pos);

		ASSERT_VALID(pSpcElt);
		if (pSpcElt->ht > nHtLeft)
		{		
			pSpcElt->ht -= nHtLeft;			
			nHtLeft = 0;
			InsertPos = Oldpos;		// position to insert before
			break;
		}
		nHtLeft -= pSpcElt->ht;
		
		CWndSpaceElt * pOldElt = (CWndSpaceElt *)SpcList.GetAt(Oldpos);
		ASSERT(pOldElt != NULL && pOldElt->IsKindOf(RUNTIME_CLASS(CWndSpaceElt)));
		SpcList.RemoveAt(Oldpos);				// remove that element
		
		ASSERT(pSpcElt != NULL && pSpcElt->IsKindOf(RUNTIME_CLASS(CWndSpaceElt)));
		delete pOldElt;
	}
	ASSERT(nHtLeft == 0);
	
	// should now be looking at the element we need to shrink...
	// NB: If pos = NULL then we removed to the end of the list...
	pSpcElt = new CWndSpaceElt;
	pSpcElt->wd = nMinX + nWd;
	pSpcElt->ht = nHt;
	if (InsertPos == NULL)
		SpcList.AddTail(pSpcElt);
	else
		SpcList.InsertBefore(InsertPos, pSpcElt);


#ifdef _DEBUG
#ifdef _DEBUG_WNDPOS
	TRACE("After insert:\n");
#endif
	pos = SpcList.GetHeadPosition();
	int nTotalHeightAfter = 0;
	while (pos != NULL)
	{
		CWndSpaceElt * pSpcElt = (CWndSpaceElt *)SpcList.GetNext(pos);
		ASSERT(pSpcElt != NULL);
		ASSERT_VALID(pSpcElt);
		nTotalHeightAfter += pSpcElt->ht;
#ifdef _DEBUG_WNDPOS
		TRACE("    ht= %d w=%d\n", pSpcElt->ht, pSpcElt->wd);
#endif
	}
	
	ASSERT(nTotalHeightAfter == ParentSize.cy);		
	ASSERT(nTotalHeightBefore == nTotalHeightAfter);
#endif
}

void CWndSpaceElt::ArrangeWindowsInWindow (CWnd * pParentWnd, CObArray & arrWnd, DWORD dwOrient)
{
	if (arrWnd.GetSize() == 0)			// no windows to size.. do nothing
		return;

	CRect ClientRect;
	pParentWnd->GetClientRect(&ClientRect);
	
	CSize ParentSize = ClientRect.Size();
	if (ParentSize.cy == 0)
		return;							// no height => not much we can do	
	
	CObList SpcList;					// list used to keep track of window spacing
	
	// add initial Arrange rectangle to the list;	
	CWndSpaceElt * pSpcElt = new CWndSpaceElt;
	pSpcElt->wd = 0;
	pSpcElt->ht = ClientRect.Height();
	SpcList.AddTail(pSpcElt); 


	// sort array of window positions by size so that we position the largest windows first.
	// this improves the results quite a bit
	CObject ** pArrData = arrWnd.GetData();
	ASSERT(pArrData != NULL);		// shouldn't be NULL as array is non-empty, but check anyway	
	qsort(pArrData, arrWnd.GetSize(), sizeof(CObject *), CompareWndRect); 	
	
	
	HDWP hDWP = BeginDeferWindowPos(arrWnd.GetSize());	   // defer window moves to save on refresh

	// iterate thru all the windows in the list looking for a position to put it
	for (int nWndNo = 0; nWndNo < arrWnd.GetSize(); nWndNo++)
	{
		CWnd * pWnd = (CWnd *)arrWnd[nWndNo];
		ASSERT(pWnd != NULL);
		ASSERT_VALID(pWnd);
		PositionInSpcList(pWnd, SpcList, dwOrient, pParentWnd, ParentSize, hDWP);
	} 

	if (hDWP != NULL)
		::EndDeferWindowPos(hDWP);		// move the windows

	// Remove elements from the SpcList;
	while (!SpcList.IsEmpty())
	{
		CWndSpaceElt * pElt = (CWndSpaceElt *) SpcList.GetTail();
		delete pElt;
		SpcList.RemoveTail();
	}
}

