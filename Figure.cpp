#include "stdafx.h"
/* Figure.C */

#include "Figure.h"
// Super Class : None

#include "COODView.h" 
#include "FigureList.h"
#include "Popup.h" 
#include "ExcludeRectList.h"
#include "ExcludeRect.h"

IMPLEMENT_SERIAL(Figure,CObject,1)

Figure *Figure::BackUp = NIL;

Figure::Figure()
: CObject()
{
	_controller = NIL;
	_points = NIL;
//	_region = createRegion();
//	_clip = createRegion();
	_region = NIL;
	_clip = NIL;
	_visited = FALSE;
	_inCanvas = TRUE;
	_borned = NIL;
	_popup = NIL;
	_dotedFlag = FALSE;
	_brushIndex = BLACK_BRUSH;
	_foreground = RGB(0,0,0);
	_background = RGB(255,255,255);
	_excludeRects = new ExcludeRectList();
}

Figure::Figure(COODView *controller)
: CObject()
{
	_controller = controller;
	_points = NIL;
//	_region = createRegion();
//	_clip = createRegion();
	_region = NIL;
	_clip = NIL;
	_visited = FALSE;
	_inCanvas = TRUE;
	_borned = NIL;
	_popup = NIL;
	_dotedFlag = FALSE;
	_brushIndex = BLACK_BRUSH;
	_foreground = RGB(0,0,0);
	_background = RGB(255,255,255);
	_excludeRects = new ExcludeRectList();
}

Figure::~Figure()
{
	_controller = NIL;
	_popup = NIL;
	_borned = NIL;

	if (_region != NIL) {
		delete _region; _region = NIL;
	}
	if (_clip != NIL) {
		delete _clip; _clip = NIL;
	}
	if (_points != NIL) {
		delete []_points; _points = NIL;
	}
	delete _excludeRects;
}

void Figure::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);   
	if (ar.IsStoring()) {
		ar << (LONG) _brushIndex;
		ar << (LONG) _foreground;
		ar << (LONG) _background;
	} else {
		UINT fore;
		UINT back;
		ar >> (LONG &) _brushIndex;
		ar >> (LONG &) fore;
		ar >> (LONG &) back;
		_foreground = (COLORREF)fore;
		_background = (COLORREF)back;
	}
}

void Figure::resetRegion()
{
	if (_region != NIL) delete _region;
	_region = createRegion();
	_region = NIL;
	if (_clip != NIL) delete _clip;
	_clip = createRegion();
	_clip = NIL;
}

void Figure::releaseRegion()
{
	if (_region != NIL) delete _region;
	_region = NIL;
	if (_clip != NIL) delete _clip;
	_clip = NIL;
}

COODView *Figure::controller()
{
	return _controller;
}

Figure* Figure::borned()
{
	return _borned; 
}

BOOL& Figure::visited()
{
	return _visited; 
}

void Figure::setInCanvas(BOOL flag)
{
	_inCanvas = flag;
}

BOOL& Figure::inCanvas()
{
	return _inCanvas;
}

BOOL Figure::checkInRegion(CRgn*)
{
	return FALSE; 
}

void Figure::center(int&,int&)
{
	// Empty
}

void Figure::getExclusiveClipRect(int &x1,int &y1,int &x2,int &y2)
{
	x1 = 0; y1 = 0;
	x2 = 0; y2 = 0;
}

void Figure::last(int&,int&)
{
	// Empty
}

BOOL Figure::checkNear(int,int)
{
	return FALSE;
}

void Figure::clear(CDC*)
{
	// Empty
}

BOOL Figure::startEdit()
{
	return FALSE;
}

void Figure::minMaxXY()
{
	// Empty
}

void Figure::getMinMaxXY(int &,int &,int &,int &)
{
	// Empty
}

void Figure::draw(CDC*)
{
	// Empty
}

void Figure::drawWithNeighbors(CDC *dcp)
{
	draw(dcp);
}

void Figure::drawOnMetaFile(CDC* dcp)
{
	draw(dcp);
}

void Figure::drawBoundary(CDC* dcp)
{
	draw(dcp);
}

void Figure::drawBoundaryEx(CDC* dcp)
{
	drawBoundary(dcp);
}

void Figure::deleteFocusObject()
{
	// Empty
}

void Figure::eraseDots(CDC*)
{
	// Empty
}

void Figure::drawDots(CDC*)
{
	// Empty
}

void Figure::drawing(CDC*,int,int)
{
	// Empty
}

void Figure::removeExcludeRect(Figure *ptr)
{
	_excludeRects->remove(ptr);
}

void Figure::removeAllExcludeRect()
{
	delete _excludeRects;
	_excludeRects = new ExcludeRectList();
}

void Figure::excludeRects(CDC *dcp)
{
	ExcludeRectList *list = getExcudeRects();
	ExcludeRect *pRect = list->getFirst();
	while (pRect != NIL) {
		dcp->ExcludeClipRect(pRect->rectPtr());
		pRect = list->getNext();
	}
}

void Figure::addExcludeRect(ExcludeRect *ptr)
{
	_excludeRects->addTail(ptr);
}

void Figure::getAdditionalExcludeRects(ExcludeRectList *pList)
{
	return ;
}

BOOL Figure::onEnter(int x,int y)
{
	CPoint pt(x,y);
	ExcludeRectList *list = getExcudeRects();
	ExcludeRect *pRect = list->getFirst();
	while (pRect != NIL) {
		CRect *ptr = pRect->rectPtr();
		if (ptr->PtInRect(pt)) return FALSE;
		pRect = list->getNext();
	}
	if (_region != NIL && !isEmptyRegion(_region)) {
		return _region->PtInRegion(x,y);
	} else {
		return(FALSE);
	}
}

BOOL Figure::wantToResize(int&,int&)
{
	return FALSE;
}

BOOL Figure::wantToMove(int,int)
{
	return TRUE;
}

void Figure::moveCoord(int,int)
{
	// Empty
}

void Figure::moveCoordForScroll(int dx,int dy)
{
	moveCoord(dx,dy);
}

int Figure::setHotXY(int,int)
{
	return 0;
}

void Figure::move(CDC*,int,int)
{
	// Empty
}

void Figure::popup(CPoint* event,BOOL)
{
	if (_controller != NIL) _popup->popup(_controller,event);
}

Popup *Figure::popupPointer()
{
	return (Popup *)_popup;
}

void Figure::bornFocus()
{
	// Empty
}

UnsignedLong* Figure::whoAreYou()
{
	return IAMFIGURE;
}

Figure* Figure::born(Figure* ptr)
{
	Figure *copied;
	if ( ptr == NIL) {
		copied = new Figure(NIL);
	} else {
		copied = ptr;
	}
	_borned = copied;
	copied->_controller = _controller;
	copied->_popup = _popup;
	copied->_brushIndex = _brushIndex;
	copied->_background = _background;
	copied->_foreground = _foreground;
	return(copied);
}

BOOL Figure::checkEntries(CRgn*)
{
	return TRUE; 
}

CRgn*& Figure::region()
{
	return _region; 
}

CRgn*& Figure::clip()
{
	return _clip; 
}

CRgn* Figure::clip(CDC *pDC)
{
	if (pDC->IsKindOf(RUNTIME_CLASS(CClientDC)) ||
		pDC->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) ||
		pDC->IsKindOf(RUNTIME_CLASS(CPaintDC)) ||
		pDC->IsKindOf(RUNTIME_CLASS(CWindowDC))) {
		return _clip;
	} else { // Print 용 DC
		return NULL;
	}
}

void Figure::makeRegion(CRgn *sourceClipRgn)
{
	// Empty
}

void Figure::remakeRegionForContainer()
{
	makeRegion(_controller->canvasRgn());
}

void Figure::checkInlist(FigureList *alist)
{
	if (alist->inList(this)) alist->remove(this);
}

BOOL Figure::checkMinWH()
{
	return(FALSE);
}

void Figure::recalcWidthHeight(BOOL)
{
	// Empty
}

int Figure::nOfFigures()
{
	return 1;
}

void Figure::epilog(BOOL skipflag)
{
	return;
}

BOOL Figure::isObsolete()
{
	return FALSE;
}

BOOL Figure::isNeighborConnection(Figure *node)
{
	return FALSE;
}

Figure *Figure::focus()
{
	return this;
}

Figure *Figure::container()
{
	return this;
}

BOOL Figure::containedWithin(int x1,int y1,int x2,int y2)
{
	return FALSE;
}

void Figure::bye()
{
	return;
}

void Figure::resetOneLineTextIfObsolete(Text *aText)
{
	return;
}

void Figure::setFocus(int,int)
{
	// Empty
}

void Figure::setSpecificDataMembers()
{
	// Empty
}

void Figure::setThisFocus(Figure *)
{
	// Empty
}

void Figure::resetFocus()
{
	// Empty
}

BOOL Figure::moveProlog(BOOL)
{
	return TRUE;
}

void Figure::resizeProlog(NodeFigure* aNode)
{
	// Empty
}

Figure* Figure::makeBackUp()
{
	return born();
}

void Figure::setXY1(int,int)
{
	// Empty
}

void Figure::setXY2(int,int)
{
	// Empty
}

void Figure::setModelSpecificSymbolAll()
{
	return;
}

void Figure::clearLists()
{
	return;
}

void Figure::deleteNeighbors()
{
	return;
}

void Figure::clearMeAndNeighbors(CDC *dcp)
{
	clear(dcp);
}

void Figure::setPopupPointer(Popup *ptr)
{
	_popup = ptr;
}

void Figure::setController(COODView *ptr)
{
	_controller = ptr;
}

void Figure::invalidate()
{
	_controller->Invalidate();
}

void Figure::DrawLine(CDC* dcp,int x1,int y1,int x2,int y2,int thickness,int style)
{
	CRect clipRect;
	dcp->GetClipBox(&clipRect);

	/* 수평선이거나 수직선인 경우에만 ...
	   네장 이상에 걸쳐 그려진 라인은 프린트가 되지 않는 현상이 있음 ...
	   프린트 시의 문제이기 때문에 일반적으로는 이렇게 클립핑할 필요가 없을것 ... */
	int xLowBound = clipRect.left;
	int xHighBound = clipRect.right;
	int yLowBound = clipRect.top;
	int yHighBound = clipRect.bottom;
	if (x1 == x2 && x1 >= xLowBound && x1 <= xHighBound) { // 수직선 경우 
		if (y1 < y2) {
			if (y1 < yLowBound && y2 > yLowBound) y1 = yLowBound;
			if (y2 > yHighBound && y1 < yHighBound) y2 = yHighBound;
		} else { // y1 >= y2
			if (y2 < yLowBound && y1 > yLowBound) y2 = yLowBound;
			if (y1 > yHighBound && y2 < yHighBound) y1 = yHighBound;
		}
	} else if (y1 == y2 && y1 >= yLowBound && y1 <= yHighBound ) { // 수평선 경우 
		if (x1 < x2) {
			if (x1 < xLowBound && x2 > xLowBound) x1 = xLowBound;
			if (x2 > xHighBound && x1 < xHighBound) x2 = xHighBound;
		} else { // x1 >= x2
			if (x2 < xLowBound && x1 > xLowBound) x2 = xLowBound;
			if (x1 > xHighBound && x2 < xHighBound) x1 = xHighBound;
		}
	}
	DWORD dashStyle[2];
	UINT penStyle = PS_GEOMETRIC|PS_ENDCAP_SQUARE;
	if (style == DASHED || style == DOTED) {
		penStyle = penStyle|PS_USERSTYLE;
		if (style == DASHED) {
			dashStyle[0] = 15; // 실선 길이
			dashStyle[1] = 10; // 빈선 길이
		} else if (style == DOTED) {
			dashStyle[0] = 5; // 실선 길이
			dashStyle[1] = 5; // 빈선 길이
		}
		CPen *oldPen = dcp->GetCurrentPen();
		LOGPEN logpen;
		oldPen->GetLogPen(&logpen);
		CBrush tmpBrush(logpen.lopnColor);
		LOGBRUSH logbrush;
		tmpBrush.GetLogBrush(&logbrush);
		CPen newPen(penStyle,thickness,&logbrush,2,(const DWORD*)&dashStyle);
		oldPen = dcp->SelectObject(&newPen);
		dcp->MoveTo(x1,y1);
		dcp->LineTo(x2,y2);
		dcp->SelectObject(oldPen);
	} else {
		penStyle = penStyle|PS_SOLID;
		CPen *oldPen = dcp->GetCurrentPen();
		LOGPEN logpen;
		oldPen->GetLogPen(&logpen);
		CBrush tmpBrush(logpen.lopnColor);
		LOGBRUSH logbrush;
		tmpBrush.GetLogBrush(&logbrush);
		CPen thickPen(penStyle,thickness,&logbrush);
		oldPen = dcp->SelectObject(&thickPen);
		dcp->MoveTo(x1,y1);
		dcp->LineTo(x2,y2);
		dcp->SelectObject(oldPen);
	}
}

void Figure::FillPolygon(CDC* dcp,POINT* points,int npoint)
{
	CRgn rgn;
	rgn.CreatePolygonRgn(points,npoint,WINDING);
	dcp->FillRgn(&rgn,dcp->GetCurrentBrush());
}

int Figure::GetMax(int x,int y,int z)
{
	int max = x;
	if (y > max) max = y;
	if (z > max) max = z;
	return max;
}

int Figure::GetMin(int x,int y,int z)
{
	int min = x;
	if (y < min) min = y;
	if (z < min) min = z;
	return min;
}

BOOL Figure::isEditable()
{
	return FALSE;
}

void Figure::setMoveAllFlag(BOOL flag)
{
}

