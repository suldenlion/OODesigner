#if !defined(AFX_CUSTOMTOOLBAR_H__79385504_0D74_11D5_A80A_0050DA2D4248__INCLUDED_)
#define AFX_CUSTOMTOOLBAR_H__79385504_0D74_11D5_A80A_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomToolBar.h : header file
//

#include "ZoomComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CustomToolBar window

class CustomToolBar : public CToolBar
{
// Construction
public:
	CustomToolBar();

// Attributes
private:
	ZoomComboBox _zoomBox;

// Operations
public:
	void makeZoomComboBox(CWnd *pFrame,int pos,UINT messageId,CSize size);
	void getZoomValue(CString &value);
	void setZoomValue(const char *value);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CustomToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CustomToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CustomToolBar)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTOOLBAR_H__79385504_0D74_11D5_A80A_0050DA2D4248__INCLUDED_)
