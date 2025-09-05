#ifndef _CWNDSPACEELT_H
#define _CWNDSPACEELT_H

class CResizableMDIFrameWnd;

class CWndSpaceElt : public CObject
{
	friend class CResizableMDIFrameWnd;

DECLARE_DYNAMIC(CWndSpaceElt);
public:
	WORD ht;
	WORD wd;
private:
    static void ArrangeWindowsInWindow (CWnd * pParentWnd, CObArray & arrWnd, DWORD dwOrient);
	static void PositionInSpcList(CWnd *pWnd, CObList & SpcList, DWORD dwOrient,
		CWnd * pParentWnd, CSize & ParentSize, HDWP hDwp);
};

#endif