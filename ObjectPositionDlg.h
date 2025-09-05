#if !defined(AFX_OBJECTPOSITIONDLG_H__23EADE83_4DD7_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_OBJECTPOSITIONDLG_H__23EADE83_4DD7_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectPositionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ObjectPositionDlg dialog

class ObjectPositionDlg : public CDialog
{
// Construction
public:
	ObjectPositionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ObjectPositionDlg)
	enum { IDD = IDD_OBJECT_POSITION_DLG };
	UINT	m_height;
	UINT	m_width;
	UINT	m_x;
	UINT	m_y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ObjectPositionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ObjectPositionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTPOSITIONDLG_H__23EADE83_4DD7_11D5_A72B_0050DA2D4248__INCLUDED_)
