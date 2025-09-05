#ifndef CRESIZABLERECTTRACKER_H
#define CRESIZABLERECTTRACKER_H

#define RectTracker_OnlyMoveHorz        0x0100L      // only move horizontally
#define RectTracker_OnlyMoveVert        0x0200L      // only move vertically

class CResizableRectTracker : public CRectTracker
{
public:
	CRect   m_LimitRect;  // limiting rectangle - all movement must be within this.
	CRect   m_OrigRect;   // original position at start of track
	
	CResizableRectTracker();
	virtual void AdjustRect(int nHandle, LPRECT);
	virtual void DrawTrackerRect(LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd);
	BOOL TrackFromHitTest(int nHitTest, CWnd* pWnd, CPoint point,
				CWnd* pWndClipTo = NULL, BOOL bAllowInvert = FALSE);
};

#endif