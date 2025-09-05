#ifndef _CRESIZABLEEDITVIEWBARDOCTEMPLATE_H
#define _CRESIZABLEEDITVIEWBARDOCTEMPLATE_H

class CResizableEditViewBar;
class CResizableEditViewBarDocTemplate : public CMultiDocTemplate
{
private:
	CResizableEditViewBar *pBar;

public:
	DECLARE_DYNAMIC(CResizableEditViewBarDocTemplate)
	CResizableEditViewBarDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
										 CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);
	virtual ~CResizableEditViewBarDocTemplate();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszPathName,
		BOOL bMakeVisible=TRUE);
	virtual CFrameWnd* CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther);
};

#endif