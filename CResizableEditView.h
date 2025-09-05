#if !defined(AFX_CRESIZABLEEDITVIEW_H__91AA8C2D_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLEEDITVIEW_H__91AA8C2D_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableEditView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableEditView view
class CResizableEditDoc;

class CResizableEditView : public CEditView
{
protected:
	CResizableEditView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResizableEditView)

// Attributes
public:

// Operations
public:
	CDocument* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableEditView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CResizableEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CResizableEditView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline CDocument* CResizableEditView::GetDocument()
   { return (CDocument*)m_pDocument; }

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLEEDITVIEW_H__91AA8C2D_7A3E_11D2_AC44_00008610434C__INCLUDED_)
