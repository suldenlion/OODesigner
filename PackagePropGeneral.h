#if !defined(AFX_PACKAGEPROPGENERAL_H__EF60EBE3_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_PACKAGEPROPGENERAL_H__EF60EBE3_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PackagePropGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PackagePropGeneral dialog

class PackagePropGeneral : public CDialog
{
// Construction
public:
	PackagePropGeneral(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PackagePropGeneral)
	enum { IDD = IDD_PACKAGE_PROP_GENERAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PackagePropGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PackagePropGeneral)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PACKAGEPROPGENERAL_H__EF60EBE3_3FB3_11D5_A72B_0050DA2D4248__INCLUDED_)
