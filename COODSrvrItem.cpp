// COODSrvrItem.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "KtgMacro.h"
#include "COODSrvrItem.h"
#include "COODCntrlItem.h"
#include "COODDoc.h"
#include "FigureList.h"
#include "Figure.h"
#include "CMainFrame.h"
#include "COODView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COODSrvrItem

IMPLEMENT_DYNAMIC(COODSrvrItem, COleServerItem)

COODSrvrItem::COODSrvrItem(COODDoc* pServerDoc)
: COleServerItem(pServerDoc,TRUE)
{
}

COODSrvrItem::~COODSrvrItem()
{
}

CRect testRect;

BOOL COODSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	// Remove this if you use rSize
//	UNREFERENCED_PARAMETER(rSize);
	rSize.cx = MAXSCROLL;
	rSize.cy = MAXSCROLL;

	COODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)
	int deviceWidth = pDC->GetDeviceCaps(HORZRES);
	int deviceHeight = pDC->GetDeviceCaps(VERTRES);

	int zoomRatioX = pDoc->zoomRatioX();
	int zoomRatioY = pDoc->zoomRatioY();
	int oldMapMode = pDC->SetMapMode(MM_ISOTROPIC);
	CSize oldWindowExt = pDC->SetWindowExt(deviceWidth,-deviceHeight);
	pDC->ScaleWindowExt(100,zoomRatioX,100,zoomRatioY);
	CSize oldViewportExt = pDC->SetViewportExt(deviceWidth,-deviceHeight);
	CPoint oldViewportOrg = pDC->SetViewportOrg(0,0);
	CPoint oldWindowOrg = pDC->SetWindowOrg(0,0);

	pDC->SelectObject(COODView::PlainPen);
	pDC->SetTextColor(theAppPtr->textColor);
	pDC->SetBkColor(theAppPtr->paperColor);
	pDC->SelectObject(COODView::PlainBrush);
	pDC->SelectStockObject(NULL_BRUSH);
	// TODO: add drawing code here.  Optionally, fill in the HIMETRIC extent.
	//  All drawing takes place in the metafile device context (pDC).

	CRect client;
	pDC->GetClipBox(&client);
	CBrush brush(theAppPtr->paperColor);
	pDC->FillRect(&client,&brush);
	Figure *all = pDoc->figures()->getFirst();
	while (all != NIL) {
		all->setInCanvas(TRUE);
		all->releaseRegion();
		all->removeAllExcludeRect();
		all = pDoc->figures()->getNext();
	}

	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL) {
			selection->setInCanvas(TRUE);
		}
	}

	FigureList *figs = pDoc->figures();
	Figure *ptr = figs->getLast();
	while(ptr != NIL) {
		ptr->drawOnMetaFile(pDC);
		ptr = figs->getBack();
	}
	// TODO: also draw embedded CBothCntrItem objects.

	// The following code draws the first item at an arbitrary position.

	// TODO: remove this code when your real drawing code is complete
	pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL) {
			selection->draw(pDC);
		}
	}

	pDC->SetWindowOrg(oldWindowOrg);
	pDC->SetViewportOrg(oldViewportOrg);
	pDC->SetViewportExt(oldViewportExt);
	pDC->SetWindowExt(oldWindowExt);
	pDC->SetMapMode(oldMapMode);
	return TRUE;
}

BEGIN_MESSAGE_MAP(COODSrvrItem, COleServerItem)
	//{{AFX_MSG_MAP(COODSrvrItem)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODSrvrItem diagnostics

#ifdef _DEBUG
void COODSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void COODSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COODSrvrItem serialization

void COODSrvrItem::Serialize(CArchive& ar)
{
	// CBothSrvrItem::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  A good default for
	//  the embedded item is simply to delegate to the document's Serialize
	//  function.  If you support links, then you will want to serialize
	//  just a portion of the document.
	if (!IsLinkedItem())
	{
		COODDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// COODSrvrItem commands

BOOL COODSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).
	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);
	// CBothSrvrItem::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.

	COODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: replace this arbitrary size
	rSize = CSize(MAXSCROLL, MAXSCROLL);   // HIMETRIC units

	return TRUE;
}

