// COODCntrlItem.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "COODCntrlItem.h"
#include "COODView.h"
#include "COODDoc.h"
#include "COODCommonDoc.h"
#include "COODClassDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DELTA	(6)
extern void checkPoints(int& x1,int& y1,int& x2,int& y2);

#define CNTRL_ITEM_ID (0) 

/////////////////////////////////////////////////////////////////////////////
// COODCntrlItem

IMPLEMENT_SERIAL(COODCntrlItem, COleClientItem, 0)

COODCntrlItem::COODCntrlItem(COODDoc* pContainer)
		: COleClientItem(pContainer)
{
	_x1 = 0;
	_y1 = 0;
	_x2 = 100;
	_y2 = 100;
	_opaqueFlag = TRUE;
	_resizePoint = 0;
	_controller = NULL;
	_viewTitle = _T("");
	_region = createRegion();
	_inCanvas = TRUE;
	_dotedFlag = FALSE;
	_brushIndex = BLACK_BRUSH;
}

COODCntrlItem::~COODCntrlItem()
{
	if (_region) delete _region;
}

void COODCntrlItem::saveOriginXY(COODView *pController)
{
	_ox1 = _x1 - pController->originX();
	_oy1 = _y1 - pController->originY();
	_ox2 = _x2 - pController->originX();
	_oy2 = _y2 - pController->originY();
}

void COODCntrlItem::setControllerAbsolutely(COODView *controller)
{
	_controller = controller;
	_viewTitle = controller->viewTitle;
}

void COODCntrlItem::setController(COODView *controller,CString viewTitle)
{
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODCommonDoc)) &&
		GetActiveView() != NULL) {
		_controller = GetActiveView();
		_viewTitle = viewTitle;
		return;
	}
	if (_viewTitle.GetLength() > 0 && _viewTitle.CompareNoCase(viewTitle) == 0) {
		_controller = controller;
	} else if (_viewTitle.GetLength() == 0) {
		_controller = controller;
		_viewTitle = viewTitle;
	} /* 나머지 경우는 이름이 서로 다른 경우 임 */
}

void COODCntrlItem::resetController()
{
	_controller = NULL;
}

void COODCntrlItem::setCoord(int x1,int y1,int x2,int y2)
{
	_x1 = x1;
	_y1 = y1;
	_x2 = x2;
	_y2 = y2;
	_moveX = -1;
	_moveY = -1;
}

void COODCntrlItem::getClientRect(COODView *pController,CRect &rect)
{
	CPoint p1;
	p1.x = _x1 - pController->originX();
	p1.y = _y1 - pController->originY();
	pController->LPtoDP(p1);
	CPoint p2;
	p2.x = _x2 - pController->originX();
	p2.y = _y2 - pController->originY();
	pController->LPtoDP(p2);
	rect.left = p1.x;
	rect.top = p1.y;
	rect.right = p2.x;
	rect.bottom = p2.y;
}

void COODCntrlItem::getXY12(COODView *pController,CRect &rect)
{
	rect.left = _x1 - pController->originX();
	rect.top = _y1 - pController->originY();
	rect.right = _x2 - pController->originX();
	rect.bottom = _y2 - pController->originY();
}

void COODCntrlItem::getXY12Absolutely(CRect &rect)
{
	rect.left = _x1;
	rect.top = _y1;
	rect.right = _x2;
	rect.bottom = _y2;
}

BOOL COODCntrlItem::setControllerForViewName()
{
	COODDoc *pDoc = GetDocument();
	if (pDoc == NULL) return FALSE;
	if (pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		if (GetActiveView() != NULL) {
			_controller = GetActiveView();
			return TRUE;
		}
	}
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos != NULL) {
		CView* pView = pDoc->GetNextView(pos);
		if (!pView->IsKindOf(RUNTIME_CLASS(COODView))) return FALSE;
		COODView *pOODView = (COODView *)pView;
		if (_viewTitle.CompareNoCase(pOODView->viewTitle) == 0) {
			_controller = pOODView;
			return TRUE;
		}
	}
	return FALSE;
}

void COODCntrlItem::drawAsSelected(COODView *pController,CDC *pDC)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return;
	}
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)) &&
		_viewTitle.CompareNoCase(pController->viewTitle) != 0) return;
	int x1 = _x1 - _controller->originX();
	int y1 = _y1 - _controller->originY();
	int x2 = _x2 - _controller->originX();
	int y2 = _y2 - _controller->originY();
	CGdiObject *oldGdi = pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(x1,y1,x2,y2);
	pDC->SelectObject(oldGdi);
	oldGdi = pDC->SelectStockObject(_brushIndex);
	pDC->Rectangle(x1,y1,x1+DELTA,y1+DELTA);
	pDC->Rectangle(x2,y1,x2-DELTA,y1+DELTA);
	pDC->Rectangle(x2,y2,x2-DELTA,y2-DELTA);
	pDC->Rectangle(x1,y2,x1+DELTA,y2-DELTA);
	int cx = (x1+x2)/2;
	int cy = (y1+y2)/2;
	pDC->Rectangle(cx-DELTA/2,y1,cx+DELTA/2,y1+DELTA);
	pDC->Rectangle(x2-DELTA,cy-DELTA/2,x2,cy+DELTA/2);
	pDC->Rectangle(cx-DELTA/2,y2-DELTA,cx+DELTA/2,y2);
	pDC->Rectangle(x1,cy-DELTA/2,x1+DELTA,cy+DELTA/2);
	pDC->SelectObject(oldGdi);
}

void COODCntrlItem::resizing(COODView *pController,CPoint point)
{
	CDC *pDC = pController->GetDC();
	pController->setDrawingContext(KTG_RUBBERBANDING);
	pController->OnPrepareDC(pDC);
	CPen *oldPen = pDC->GetCurrentPen();
	LOGPEN logpen;
	oldPen->GetLogPen(&logpen);
	CPen penDash(PS_DOT,1,logpen.lopnColor);
	oldPen = pDC->SelectObject(&penDash);
	int x1 = _x1 - pController->originX();
	int y1 = _y1 - pController->originY();
	int x2 = _x2 - pController->originX();
	int y2 = _y2 - pController->originY();
	pDC->Rectangle(x1,y1,x2,y2);
	if (_resizePoint == AT_1) {
		_x1 = point.x + pController->originX();
		_y1 = point.y + pController->originY();
	} else if (_resizePoint == AT_2) {
		_y1 = point.y + pController->originY();
	} else if (_resizePoint == AT_3) {
		_x2 = point.x + pController->originX();
		_y1 = point.y + pController->originY();
	} else if (_resizePoint == AT_4) {
		_x2 = point.x + pController->originX();
	} else if (_resizePoint == AT_5) {
		_x2 = point.x + pController->originX();
		_y2 = point.y + pController->originY();
	} else if (_resizePoint == AT_6) {
		_y2 = point.y + pController->originY();
	} else if (_resizePoint == AT_7) {
		_x1 = point.x + pController->originX();
		_y2 = point.y + pController->originY();
	} else if (_resizePoint == AT_8) {
		_x1 = point.x + pController->originX();
	}
	x1 = _x1 - pController->originX();
	y1 = _y1 - pController->originY();
	x2 = _x2 - pController->originX();
	y2 = _y2 - pController->originY();
	pDC->Rectangle(x1,y1,x2,y2);
	pDC->SelectObject(oldPen);
	pController->OODReleaseDC(pDC,FALSE);

	pController->setDrawingContext(KTG_DRAWING);
	pController->OnPrepareDC(pDC);
	pDC->Rectangle(_ox1,_oy1,_ox2,_oy2);
	pController->OODReleaseDC(pDC,TRUE);
}

void COODCntrlItem::moving(COODView *pController,CPoint point)
{
	CDC *pDC = pController->GetDC();
	pController->setDrawingContext(KTG_RUBBERBANDING);
	pController->OnPrepareDC(pDC);
	CPen *oldPen = pDC->GetCurrentPen();
	LOGPEN logpen;
	oldPen->GetLogPen(&logpen);
	CPen penDash(PS_DOT,1,logpen.lopnColor);
	oldPen = pDC->SelectObject(&penDash);
	int x1 = _x1 - pController->originX();
	int y1 = _y1 - pController->originY();
	int x2 = _x2 - pController->originX();
	int y2 = _y2 - pController->originY();
	pDC->Rectangle(x1,y1,x2,y2);
	int dx = point.x - _moveX;
	int dy = point.y - _moveY;
	_moveX = point.x;
	_moveY = point.y;
	_x1 = _x1 + dx;
	_y1 = _y1 + dy;
	_x2 = _x2 + dx;
	_y2 = _y2 + dy;
	x1 = _x1 - pController->originX();
	y1 = _y1 - pController->originY();
	x2 = _x2 - pController->originX();
	y2 = _y2 - pController->originY();
	pDC->Rectangle(x1,y1,x2,y2);
	pDC->SelectObject(oldPen);
	pController->OODReleaseDC(pDC,TRUE);
}

void COODCntrlItem::move(COODView *pController,int dx,int dy)
{
	CDC *pDC = pController->GetDC();
	pController->setDrawingContext(KTG_RUBBERBANDING);
	pController->OnPrepareDC(pDC);
	CPen *oldPen = pDC->GetCurrentPen();
	LOGPEN logpen;
	oldPen->GetLogPen(&logpen);
	CPen penDash(PS_DOT,1,logpen.lopnColor);
	oldPen = pDC->SelectObject(&penDash);
	int x1 = _x1 - pController->originX();
	int y1 = _y1 - pController->originY();
	int x2 = _x2 - pController->originX();
	int y2 = _y2 - pController->originY();
	pDC->Rectangle(x1,y1,x2,y2);
	
	_x1 = _x1 + dx;
	_y1 = _y1 + dy;
	_x2 = _x2 + dx;
	_y2 = _y2 + dy;
	x1 = _x1 - pController->originX();
	y1 = _y1 - pController->originY();
	x2 = _x2 - pController->originX();
	y2 = _y2 - pController->originY();
	pDC->Rectangle(x1,y1,x2,y2);
	pDC->SelectObject(oldPen);
	pController->OODReleaseDC(pDC,TRUE);
}

void COODCntrlItem::clear(COODView *pController,CDC* pDC)
{
	int x1 = _x1 - pController->originX();
	int y1 = _y1 - pController->originY();
	int x2 = _x2 - pController->originX();
	int y2 = _y2 - pController->originY();
	CRect tmp(x1,y1,x2,y2);
	pController->invalidateRect(&tmp,TRUE);
}

void COODCntrlItem::drawBoundary(COODView *pController,CDC* pDC)
{
	int x1 = _x1 - pController->originX();
	int y1 = _y1 - pController->originY();
	int x2 = _x2 - pController->originX();
	int y2 = _y2 - pController->originY();
	pDC->Rectangle(x1,y1,x2,y2);
}

BOOL COODCntrlItem::draw(CDC* pDC)
{
	if (_inCanvas == FALSE) return FALSE;
	int x1 = _x1 - _controller->originX();
	int y1 = _y1 - _controller->originY();
	int x2 = _x2 - _controller->originX();
	int y2 = _y2 - _controller->originY();
	if (_opaqueFlag) {
		CRect rect(x1,y1,x2,y2); 
		return COleClientItem::Draw(pDC,&rect);
	} else if (pDC->IsKindOf(RUNTIME_CLASS(CMetaFileDC))) {
		// 실제로는 디버깅이 필요
		// 메타 파일 경우에는 왜 안되노 ...
		CRect rect(x1,y1,x2,y2); 
		int oldMode = pDC->SetBkMode(TRANSPARENT);
		BOOL val = COleClientItem::Draw(pDC,&rect);
		pDC->SetBkMode(oldMode);
		return val;
	}
	CRect backRect(x1,y1,x2,y2); 

	int w = abs(x2-x1);
	int h = abs(y2-y1);

	CDC imageDC;

	BOOL succ = imageDC.CreateCompatibleDC(pDC);
	if (!succ) { 
		ErrorMsg("Can't create DC for image.");
		return FALSE;
	}

	CBitmap imageBitmap;
	succ = imageBitmap.CreateCompatibleBitmap(pDC,w,h);
	if (!succ) {
		ErrorMsg("Can't create Bitmap image.");
		return FALSE;
	}
	imageDC.SelectObject(&imageBitmap);
	succ = imageDC.BitBlt(0,0,w,h,pDC,x1,y1,SRCCOPY);

	if (!succ) {
		ErrorMsg("Can't capture background image.");
		return FALSE;
	}

	CRect rect(x1,y1,x2,y2); 
	BOOL val = COleClientItem::Draw(pDC,&rect);

	succ = pDC->BitBlt(x1,y1,w,h,&imageDC,0,0,SRCAND);
	if (!succ) {
		ErrorMsg("Can't capture background image.");
		return FALSE;
	}

	return val;
}

BOOL COODCntrlItem::draw(COODView *pController,CDC* pDC)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return FALSE;
	}
	if (_controller != NIL && 
		GetDocument() != NIL &&
		GetDocument()->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		return draw(pDC);
	}
	if (_viewTitle.CompareNoCase(pController->viewTitle) != 0) return FALSE;
	return draw(pDC);
}

BEGIN_MESSAGE_MAP(COODCntrlItem, COleClientItem)
	//{{AFX_MSG_MAP(COODCntrlItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODCntrlItem diagnostics

#ifdef _DEBUG
void COODCntrlItem::AssertValid() const
{
	COleClientItem::AssertValid();
}

void COODCntrlItem::Dump(CDumpContext& dc) const
{
	COleClientItem::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COODCntrlItem serialization

void COODCntrlItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);
	COleClientItem::Serialize(ar);
	if (ar.IsStoring())	{
		// TODO: add storing code here
		ar << _viewTitle;
		ar << (LONG) _x1;
		ar << (LONG) _y1;
		ar << (LONG) _x2;
		ar << (LONG) _y2;
		ar << (BYTE) _opaqueFlag;
		ar << (LONG) _brushIndex;		
	} else {
		// TODO: add loading code here
		ar >> _viewTitle;
		ar >> (LONG&) _x1;
		ar >> (LONG&) _y1;
		ar >> (LONG&) _x2;
		ar >> (LONG&) _y2;
		ar >> (BYTE&) _opaqueFlag;
		ar >> (LONG&) _brushIndex;		
	}
}

/////////////////////////////////////////////////////////////////////////////
// COODCntrlItem commands

void COODCntrlItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	ASSERT_VALID(this);
	COleClientItem::OnChange(nCode, dwParam);
	GetDocument()->UpdateAllViews(NULL);
}

void COODCntrlItem::OnActivate() 
{
	// TODO: Add your specialized code here and/or call the base class
	COODView *pView = GetActiveView();
	ASSERT_VALID(pView);
	COleClientItem *pItem = GetDocument()->GetInPlaceActiveItem(pView);
	if (pItem != NULL && pItem != this)
		pItem->Close();
	COleClientItem::OnActivate();
}

void COODCntrlItem::OnGetItemPosition(CRect& rPosition) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	ASSERT_VALID(this);
	if (_controller == NULL) {
		if (!setControllerForViewName()) return;
	}
	int x1 = _x1 - _controller->originX();
	int y1 = _y1 - _controller->originY();
	int x2 = _x2 - _controller->originX();
	int y2 = _y2 - _controller->originY();
	rPosition.SetRect(x1,y1,x2,y2);
}

void COODCntrlItem::OnDeactivateUI(BOOL bUndoable) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COleClientItem::OnDeactivateUI(bUndoable);
	// Hide the object if it is not an outside-in object
	DWORD dwMisc = 0;
	m_lpObject->GetMiscStatus(GetDrawAspect(),&dwMisc);
	if (dwMisc & OLEMISC_INSIDEOUT)
		DoVerb(OLEIVERB_HIDE,NULL);
}

BOOL COODCntrlItem::OnChangeItemPosition(const CRect& rectPos) 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT_VALID(this);
	if (!COleClientItem::OnChangeItemPosition(rectPos))
		return FALSE;
	if (_controller == NULL) {
		if (!setControllerForViewName()) return TRUE;
	}
	_x1 = rectPos.left + _controller->originX();
	_y1 = rectPos.top + _controller->originY();
	_x2 = rectPos.right + _controller->originX();
	_y2 = rectPos.bottom + _controller->originY();
	return TRUE;
}

void COODCntrlItem::resetRegion(COODView *pController)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return;
	}
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)) &&
		_viewTitle.CompareNoCase(pController->viewTitle) != 0) return;
	if (_region != NIL) delete _region;
	_region = createRegion();
}

void COODCntrlItem::releaseRegion(COODView *pController)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return;
	}
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)) &&
		_viewTitle.CompareNoCase(pController->viewTitle) != 0) return;
	if (_region != NIL) delete _region;
	_region = NIL;
}

void COODCntrlItem::makeRegion(COODView *pController)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return;
	}
	if (GetDocument() != NULL &&
		GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)) &&
		_viewTitle.CompareNoCase(pController->viewTitle) != 0) return;
	if (_region) delete _region;
	_region = new CRgn();
	int x1 = _x1 - _controller->originX();
	int y1 = _y1 - _controller->originY();
	int x2 = _x2 - _controller->originX();
	int y2 = _y2 - _controller->originY();
	_region->CreateRectRgn(x1,y1,x2,y2);
}

void COODCntrlItem::stopResize(COODView *pController)
{
	if (_x1 > _x2) {
		int x = _x1;
		_x1 = _x2;
		_x2 = x;
	}
	if (_y1 > _y2) {
		int y = _y1;
		_y1 = _y2;
		_y2 = y;
	}
	makeRegion(pController);
	_ox1 = 0;
	_oy1 = 0;
	_ox2 = 0;
	_oy2 = 0;
	_resizePoint = 0;
}

void COODCntrlItem::stopMove(COODView *pController)
{
	makeRegion(pController);
	_moveX = -1;
	_moveY = -1;
	_resizePoint = 0;
}

void COODCntrlItem::setInCanvas(BOOL flag)
{
	_inCanvas = flag;
}

void COODCntrlItem::setInCanvas(COODView *pController,BOOL flag)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return;
	}
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)) &&
		_viewTitle.CompareNoCase(pController->viewTitle) != 0) return;
	_inCanvas = flag;
}

BOOL COODCntrlItem::inCanvas(COODView *pController)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return FALSE;
	}
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)) &&
		_viewTitle.CompareNoCase(pController->viewTitle) != 0) return FALSE;
	return _inCanvas;
}

BOOL COODCntrlItem::onEnter(COODView *pController,int x,int y)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return FALSE;
	}
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)) &&
		_viewTitle.CompareNoCase(pController->viewTitle) != 0) return FALSE;
	if (_region != NIL && !isEmptyRegion(_region)) {
		return _region->PtInRegion(x,y);
	} else {
		return(FALSE);
	}
}

BOOL COODCntrlItem::containedWithin(COODView *pController,int x1,int y1,int x2,int y2)
{
	int thisX1 = _x1;
	int thisY1 = _y1;
	int thisX2 = _x2;
	int thisY2 = _y2;
	checkPoints(thisX1,thisY1,thisX2,thisY2);
	if (thisX1 >= x1 && thisY1 >= y1 && 
		thisX2 <= x2 && thisY2 <= y2) return TRUE;
	return FALSE;
}

BOOL COODCntrlItem::checkInRegion(COODView *pController,CRgn* someregion)
{
	if (_controller == NULL) {
		if (!setControllerForViewName()) return (FALSE);
	}
	if (GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc)) &&
		_viewTitle.CompareNoCase(pController->viewTitle) != 0) return FALSE;
	if (someregion == NIL) return(FALSE);
	int x1 = _x1 - _controller->originX();
	int y1 = _y1 - _controller->originY();
	int x2 = _x2 - _controller->originX();
	int y2 = _y2 - _controller->originY();
	int w = abs(x1 - x2);
	int h = abs(y1 - y2);
	if (w == 0) w = 1;
	if (h == 0) h = 1;
	checkPoints(x1,y1,x2,y2);
	if (_controller->rectInRegion(someregion,x1,y1,w,h) == RectangleOut) {
		return(FALSE);  // outside someregion
	} else {
		return(TRUE);   // inside someregion
	}
}

void COODCntrlItem::trackMouse(COODView *pController,CPoint point)
{
	if (onEnter(pController,point.x,point.y) == FALSE) {
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
		_moveX = -1;
		_moveY = -1;
		_resizePoint = 0;
		return;
	}

	int x1 = _x1 - _controller->originX();
	int y1 = _y1 - _controller->originY();
	int x2 = _x2 - _controller->originX();
	int y2 = _y2 - _controller->originY();
	int cx = (x1+x2)/2;
	int cy = (y1+y2)/2; 
	CRect rect1(x1,y1,x1+DELTA,y1+DELTA);
	CRect rect2(cx-DELTA/2,y1,cx+DELTA/2,y1+DELTA);
	CRect rect3(x2-DELTA,y1,x2,y1+DELTA);
	CRect rect4(x2-DELTA,cy-DELTA/2,x2,cy+DELTA/2);
	CRect rect5(x2-DELTA,y2-DELTA,x2,y2);
	CRect rect6(cx-DELTA/2,y2-DELTA,cx+DELTA/2,y2);
	CRect rect7(x1,y2-DELTA,x1+DELTA,y2);
	CRect rect8(x1,cy-DELTA/2,x1+DELTA,cy+DELTA/2);
	if (rect1.PtInRect(point)) {
		_resizePoint = AT_1;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNWSE));
	} else if (rect2.PtInRect(point)) {
		_resizePoint = AT_2;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNS));
	} else if (rect3.PtInRect(point)) {
		_resizePoint = AT_3;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNESW));
	} else if (rect4.PtInRect(point)) {
		_resizePoint = AT_4;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKWE));
	} else if (rect5.PtInRect(point)) {
		_resizePoint = AT_5;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNWSE));
	} else if (rect6.PtInRect(point)) {
		_resizePoint = AT_6;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNS));
	} else if (rect7.PtInRect(point)) {
		_resizePoint = AT_7;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNESW));
	} else if (rect8.PtInRect(point)) {
		_resizePoint = AT_8;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKWE));
	} else {
		_resizePoint = AT_MOVE;
		_moveX = point.x;
		_moveY = point.y;
		SetClassLong(pController->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACK4WAY));
	}
}

void COODCntrlItem::toggleOpaqueFlag()
{
	if (_opaqueFlag) {
		_opaqueFlag = FALSE;
	} else {
		_opaqueFlag = TRUE;
	}
}

void COODCntrlItem::popup(CWnd *pWnd,CPoint* event)
{
	CMenu oleMenu;
	if (!oleMenu.LoadMenu(IDR_OLE_POPUPS)) {
		TRACE0("Loading menu for tree bar fails");
		return;
	}
	COleDataObject dataObject;
	BOOL bEnable = dataObject.AttachClipboard() &&
		COleClientItem::CanCreateFromData(&dataObject);

	CMenu *subMenu = oleMenu.GetSubMenu(CNTRL_ITEM_ID);
	if (bEnable) {
		subMenu->EnableMenuItem(ID_EDIT_PASTE,MF_BYCOMMAND|MF_ENABLED);
	} else {
		subMenu->EnableMenuItem(ID_EDIT_PASTE,MF_BYCOMMAND|MF_GRAYED);
	}
	if (_opaqueFlag) {
		subMenu->ModifyMenu(ID_OBJECT_TRANSPARENT,MF_BYCOMMAND|MF_STRING, ID_OBJECT_TRANSPARENT,"Tr&ansparent");
	} else {
		subMenu->ModifyMenu(ID_OBJECT_TRANSPARENT,MF_BYCOMMAND|MF_STRING, ID_OBJECT_TRANSPARENT,"Op&aque");
	}
	subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, event->x, event->y, pWnd->GetParent());
	oleMenu.DestroyMenu();
}

BOOL COODCntrlItem::CanActivate()
{
	// Editing in-place while the server itself is being edited in-place
	//  does not work and is not supported.  So, disable in-place
	//  activation in this case.
	COODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(COleServerDoc)));
	if (pDoc->IsInPlaceActive())
		return FALSE;

	// otherwise, rely on default behavior
	return COleClientItem::CanActivate();
}
