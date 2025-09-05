#if !defined(AFX_ZOOMCOMBOBOX_H__79385503_0D74_11D5_A80A_0050DA2D4248__INCLUDED_)
#define AFX_ZOOMCOMBOBOX_H__79385503_0D74_11D5_A80A_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ZoomComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ZoomComboBox window

class ZoomComboBox : public CComboBox
{
// Construction
public:
	ZoomComboBox();
	void setFrameWnd(CWnd *pFrame);
// Attributes
private:
	UINT _messageId;
	CWnd *_pRealMainFrame; // CMainFrame È¤Àº CInPlaceFrame
// Operations
public:
	void setMessageId(UINT id);
	void getZoomValue(CString &value);
	void setZoomValue(const char *value);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZoomComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZoomComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(ZoomComboBox)
	afx_msg void OnSelchange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMCOMBOBOX_H__79385503_0D74_11D5_A80A_0050DA2D4248__INCLUDED_)
