#if !defined(AFX_CTEXTDOC_H__91AA8C24_7A3E_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_CTEXTDOC_H__91AA8C24_7A3E_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CTextDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDoc document

class CTextDoc : public CDocument
{
protected:
	CTextDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTextDoc)

// Attributes
public:

// Operations
public:
	BOOL onWindowClose(BOOL removeViewNameFlag);
	void closeWindowAbsolutely();
	void onFileSave() {
		OnFileSave();
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextDoc)
	afx_msg void OnWindowClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTEXTDOC_H__91AA8C24_7A3E_11D2_AC44_00008610434C__INCLUDED_)
