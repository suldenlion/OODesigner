#if !defined(AFX_COODSRVRITEM_H__4EA50142_64C1_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_COODSRVRITEM_H__4EA50142_64C1_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// COODSrvrItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COODSrvrItem document

class COODSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(COODSrvrItem)

public:
	COODSrvrItem(COODDoc* pServerDoc);	

// Attributes
public:
	COODDoc* GetDocument() const
		{ return (COODDoc*)COleServerItem::GetDocument(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COODSrvrItem)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnGetExtent(DVASPECT nDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COODSrvrItem();
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COODSrvrItem)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COODSRVRITEM_H__4EA50142_64C1_11D5_A72B_0050DA2D4248__INCLUDED_)
