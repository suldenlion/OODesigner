#if !defined(AFX_TABDLGWITHNAME_H__EF60EBE0_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_TABDLGWITHNAME_H__EF60EBE0_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TabDlgWithName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TabDlgWithName dialog
#define PAGE_DISPX	(32)
#define PAGE_DISPY	(86)

class TabDlgWithName : public CDialog
{
	DECLARE_DYNAMIC(TabDlgWithName)
private:
	static const int BoundaryGapX;
	static const int BoundaryGapY;
// Construction
protected:
	TabDlgWithName(UINT id,CWnd* pParent = NULL);   // standard constructor
    void ShowSelTabWindow();
    CWnd * GetTabWindow(int nTab);
	void moveOptionDlgs(int x,int y);
	void updateData();
	void resizeTabControlSize(int w,int h);

	CTabCtrl *_pTabCtrl;

public:
	BOOL ShowWindow(int nCmdShow);
	static void AddItem(CTabCtrl &optionsTab,int index,char* name,LPARAM pDialog);

// Dialog Data
	//{{AFX_DATA(TabDlgWithName)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TabDlgWithName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TabDlgWithName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	void OnMove(int x, int y);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLGWITHNAME_H__EF60EBE0_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_)
