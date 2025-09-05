#ifndef _CRESIZABLEDOCKCONTEXT_H
#define _CRESIZABLEDOCKCONTEXT_H

#include <afxpriv.h>
class CResizableDockBar;

class CResizableDockContext : public CDockContext
{
// Attributes
public:
    CRect m_rectDragDock;                           // rectangle indicating where we'll dock

protected:
	CRect m_rectDragHorzAlone;		
	CRect m_rectDragVertAlone;
	CResizableDockBar * m_pTargetDockBar;
	CPoint	m_ptStart;

// Construction
public:
    CResizableDockContext(CControlBar* pBar);

// Operations
	virtual void StartDrag(CPoint pt);
	virtual void ToggleDocking();		// called to toggle docking

    void Move(CPoint pt);       // called when mouse has moved
    void EndDrag();             // drop
    void CancelDrag();          // drag cancelled
    void OnKey(int nChar, BOOL bDown);

// Implementation
public:
    virtual ~CResizableDockContext();
    BOOL Track();
    void DrawFocusRect(BOOL bRemoveRect = FALSE);
    void UpdateState(BOOL* pFlag, BOOL bNewValue);
    DWORD CanDock();
    CDockBar* GetDockBar();
};

#endif