#if !defined(AFX_CRESIZABLEEDITDOC_H__91AA8C2C_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CRESIZABLEEDITDOC_H__91AA8C2C_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CResizableEditDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizableEditDoc document
class CControlBar;
class CResizableEditView;

class CResizableEditDoc : public CDocument
{
protected:
	CResizableEditDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResizableEditDoc)
	CControlBar *_pBar;

// Attributes
public:

// Operations
public:
	CResizableEditView *getFirstView();
	void setControlBar(CControlBar *pBar) {
		_pBar = pBar;
	}
	void showControlFrame(BOOL bShow);
	CControlBar *pBar() { return _pBar; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableEditDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	protected:
	virtual BOOL OnNewDocument();
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizableEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CResizableEditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRESIZABLEEDITDOC_H__91AA8C2C_7A3E_11D2_AC44_00008610434C__INCLUDED_)
