#if !defined(AFX_RELATIONTRAVERSEFRAME_H__D757C100_3896_11D5_A72B_0050DA2D4248__INCLUDED_)
#define AFX_RELATIONTRAVERSEFRAME_H__D757C100_3896_11D5_A72B_0050DA2D4248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RelationTraverseFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RelationTraverseFrame frame
class ClassTreeView;
class ClassMemberListView;

class RelationTraverseFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(RelationTraverseFrame)
protected:
	RelationTraverseFrame();           // protected constructor used by dynamic creation

// Attributes
private:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndListSplitter;

// Operations
public:
	ClassTreeView *getTreeView();
	ClassMemberListView *getListView(int i);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RelationTraverseFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~RelationTraverseFrame();

	// Generated message map functions
	//{{AFX_MSG(RelationTraverseFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELATIONTRAVERSEFRAME_H__D757C100_3896_11D5_A72B_0050DA2D4248__INCLUDED_)
