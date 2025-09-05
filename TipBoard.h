#if !defined(AFX_TIPBOARD_H__0FA16EC3_2781_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_TIPBOARD_H__0FA16EC3_2781_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TipBoard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TipBoard window

class TipBoard : public CWnd
{
// Construction
public:
	TipBoard();

// Attributes
private:
	CBitmap _background;
	int _index;

// Operations
public:
	void setNextIndex();
	void setIndex();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TipBoard)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~TipBoard();
	void loadBitmap(UINT id);
	// Generated message map functions
protected:
	//{{AFX_MSG(TipBoard)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPBOARD_H__0FA16EC3_2781_11D5_A72B_0050DA2D4248__INCLUDED_)
