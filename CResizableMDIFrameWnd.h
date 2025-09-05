#if !defined(AFX_CRESIZABLEMDIFRAMEWND_H__91AA8C31_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLEMDIFRAMEWND_H__91AA8C31_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableMDIFrameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableMDIFrameWnd window

class BarSizeSaveInfo {
public:
    CSize   FloatSize;          // floating size
	CSize	HorzDockSize;       // size when docked horizontally
    CSize   VertDockSize;       // size when docked vertically
	BOOL	bMDIFloating;		// floating in an MDI child window
};

class CResizableMDIFrameWnd : public CMDIFrameWnd
{
    DECLARE_DYNCREATE(CResizableMDIFrameWnd)
// Construction
protected:
    CResizableMDIFrameWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
    void EnableDocking(DWORD dwDockStyle);
    void TileDockedBars(DWORD dwDockStyle = CBRS_ALIGN_ANY);
	void ArrangeFloatingBars(DWORD dwOrient);
	void ArrangeWindows(CObArray & arrWnd, DWORD dwOrient);
	void GetFloatingBars(CObArray & arrWnd);
	void LoadSizeBarState(LPCTSTR pszProfileName);
	void SaveSizeBarState(LPCTSTR pszProfileName);
    void LoadBarState(LPCTSTR pszProfileName);
	void DestroyDynamicBars();
	void FloatControlBarInMDIChild(CControlBar* pBar, CPoint point, DWORD dwStyle = CBRS_ALIGN_TOP);
	void UnFloatInMDIChild(CControlBar* pBar, CPoint point, DWORD dwStyle = CBRS_ALIGN_TOP);
	void FloatControlBar(CControlBar* pBar, CPoint point, DWORD dwStyle = CBRS_ALIGN_TOP);
    void DockControlBarLeftOf(CControlBar* pBar, CControlBar* pLeftOf);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableMDIFrameWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizableMDIFrameWnd();

	// Generated message map functions
protected:
	void SaveBarSizes(LPCTSTR pszSection, BOOL bSave);
	//{{AFX_MSG(CResizableMDIFrameWnd)
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLEMDIFRAMEWND_H__91AA8C31_7A3E_11D2_AC44_00008610434C__INCLUDED_)
