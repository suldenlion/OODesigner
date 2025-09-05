#if !defined(AFX_COODCOMMONFRM_H__AF6CBF30_31E1_4EB5_8492_66858EC93986__INCLUDED_)
#define AFX_COODCOMMONFRM_H__AF6CBF30_31E1_4EB5_8492_66858EC93986__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// COODCommonFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COODCommonFrm frame
#include "Classes.h"
#include "CChildFrm.h" // Generalization

class COODCommonFrm : public CChildFrm
{
	DECLARE_DYNCREATE(COODCommonFrm)
protected:
	COODCommonFrm();           // protected constructor used by dynamic creation
	void overwriteDocumentFile(COODCommonDoc *pDoc,CString &pathName);
	void insertInsertPulldownMenu(CMenu *pInsertMenu); // CInPlaceFrame에 있는 함수 내용과 완조니 같음
private:
	CControlBar *_modelToolBar;
	UINT _resourceID;
	CString _insertMenuID;

// Attributes
public:
	static BOOL ModelTBSupressedExplicitely;

// Operations
public:
	virtual CControlBar *getModelToolBar();
	void setModelIdentity(CString &extension);
	void onInitMenu(CMenu* pMenu); // CInPlaceFrame에 있는 OnInitMenu()함수 내용과 거의 같음
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODCommonFrm)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COODCommonFrm();

	// Generated message map functions
	//{{AFX_MSG(COODCommonFrm)
	afx_msg void OnViewModelToolbar();
	afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	void OnOleAdaptViewFrame();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COODCOMMONFRM_H__AF6CBF30_31E1_4EB5_8492_66858EC93986__INCLUDED_)
