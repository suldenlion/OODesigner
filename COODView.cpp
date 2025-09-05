// COODView.cpp : implementation of the COODView class
//

#include "stdafx.h"
#include "OOD.h"

#include "COODDoc.h"
#include "CMainFrame.h"
#include "COODCommonDoc.h"
#include "COODView.h"
#include "CChildFrm.h"
#include "Popup.h"
#include "XCoord.h"
#include "YCoord.h"
#include "Figures.h"
#include "Circle.h"
#include "RoundBoxA.h"
#include "FontInfo.h"
#include "ExcludeRect.h"
#include "ExcludeRectList.h"
#include "UnsignedLong.h"
#include "NodeFigureList.h"
#include "CDeploymentView.h"
#include "RelationTraverseDlg.h"
#include "PackagePropDlg.h"
#include "COODCntrlItem.h"
#include "COODSrvrItem.h"
#include "ObjectPositionDlg.h"
#include "CInPlaceFrame.h"
#include "COODClassDoc.h"

static int TestCount = 0;
static BOOL KeepGoing = FALSE;

extern int getRandom(int low,int high);

#define SCROLLBARDELTA  (40)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPen *COODView::PlainPen = NIL;
CPen *COODView::RubberbandPen = NIL;
CPen *COODView::HighlightPen = NIL;
CPen *COODView::ErasePen = NIL;

CBrush *COODView::PlainBrush = NIL;
CBrush *COODView::RubberbandBrush = NIL;
CBrush *COODView::HighlightBrush = NIL;
CBrush *COODView::EraseBrush = NIL;
CBrush *COODView::ShapeEraseBrush = NIL;

CPen *COODView::OldPen = NIL;
COLORREF COODView::OldTextColor = RGB(0,0,0);
COLORREF COODView::OldBkColor = RGB(255,255,255);
CBrush *COODView::OldBrush = NIL;
int COODView::OldMode = 0;
CGdiObject *COODView::OldGdi = NIL;

CLIPFORMAT COODView::OODClipFormat = 
	(CLIPFORMAT)::RegisterClipboardFormat(_T("OODesigner Clipboard Object"));

/////////////////////////////////////////////////////////////////////////////
// COODView

IMPLEMENT_DYNCREATE(COODView, CScrollView)

BEGIN_MESSAGE_MAP(COODView, CScrollView)
	//{{AFX_MSG_MAP(COODView)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	ON_COMMAND(ID_TOOLS_FONT, OnToolsFont)
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_TB_ARROW, OnTbArrow)
	ON_COMMAND(ID_TB_ALPHABET, OnTbAlphabet)
	ON_COMMAND(ID_TB_NOTE, OnTbNote)
	ON_COMMAND(ID_TB_ANCHOR, OnTbAnchor)
	ON_WM_DESTROY()
	ON_COMMAND(ID_INSERT_OBJECT, OnInsertObject)
	ON_COMMAND(ID_OBJECT_EDIT, OnObjectEdit)
	ON_COMMAND(ID_OBJECT_OPEN, OnObjectOpen)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_OBJECT_TRANSPARENT, OnObjectTransparent)
	ON_COMMAND(ID_OBJECT_PROPERTIES, OnObjectProperties)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_POPUP_EDIT_PASTE, OnPopupEditPaste)
	ON_UPDATE_COMMAND_UI(ID_POPUP_EDIT_PASTE, OnUpdatePopupEditPaste)
	ON_COMMAND(ID_TOOLS_GRID, OnToolsGrid)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_GRID, OnUpdateToolsGrid)
	ON_COMMAND(ID_TOOLS_COLOR_PAPER, OnToolsColorPaper)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_TOOLS_COLOR_TEXT, OnToolsColorText)
	ON_COMMAND(ID_TOOLS_COLOR_SHAPE_FOREGROUND, OnToolsColorShapeForeground)
	ON_COMMAND(ID_TOOLS_COLOR_SHAPE_BACKGROUND, OnToolsColorShapeBackground)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_VIEW_ZOOM_10, OnViewZoom10)
	ON_COMMAND(ID_VIEW_ZOOM_100, OnViewZoom100)
	ON_COMMAND(ID_VIEW_ZOOM_20, OnViewZoom20)
	ON_COMMAND(ID_VIEW_ZOOM_30, OnViewZoom30)
	ON_COMMAND(ID_VIEW_ZOOM_40, OnViewZoom40)
	ON_COMMAND(ID_VIEW_ZOOM_50, OnViewZoom50)
	ON_COMMAND(ID_VIEW_ZOOM_60, OnViewZoom60)
	ON_COMMAND(ID_VIEW_ZOOM_70, OnViewZoom70)
	ON_COMMAND(ID_VIEW_ZOOM_80, OnViewZoom80)
	ON_COMMAND(ID_VIEW_ZOOM_90, OnViewZoom90)
	ON_COMMAND(ID_TB_ACTOR, OnTbActor)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_CREATE_ACTOR, COODView::OnCreateActor)
	ON_COMMAND(ID_EDIT_ROLE_NAME, COODView::OnEditRoleName)
	ON_COMMAND(ID_DELETE_FIGURE, COODView::OnDeleteFigure)
	ON_COMMAND(ID_POPUP_EDIT,COODView::OnPopupEdit)
	ON_COMMAND(ID_COMBO_ZOOM,COODView::OnZoom)
	ON_COMMAND(ID_LINE_ARROW,COODView::OnLineArrow)
	ON_COMMAND(ID_LINE_STYLE_SOLID,COODView::OnLineStyleSolid)
	ON_COMMAND(ID_LINE_STYLE_DASH,COODView::OnLineStyleDash)
	ON_COMMAND(ID_LINE_STYLE_DOT,COODView::OnLineStyleDot)
	ON_COMMAND(ID_LINE_THICKNESS_1,COODView::OnLineThickness1)
	ON_COMMAND(ID_LINE_THICKNESS_2,COODView::OnLineThickness2)
	ON_COMMAND(ID_LINE_THICKNESS_3,COODView::OnLineThickness3)
	ON_COMMAND(ID_LINE_THICKNESS_4,COODView::OnLineThickness4)
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_TB_BOX, &COODView::OnTbBox)
	ON_COMMAND(ID_TB_CIRCLE, &COODView::OnTbCircle)
	ON_COMMAND(ID_TB_ROUNDBOXA, &COODView::OnTbRoundboxa)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODView construction/destruction

COODView::COODView()
{
	// TODO: add construction code here
	m_pSelection = NULL;

	_savedHotX = -1;
	_savedHotY = -1;

	currentOrient = UNDEFINED;
	_toBeDestroyed = FALSE;

	ktgF_traceEnter = TRUE;
	ktgF_selectionResizing = FALSE;
	ktgF_selectionMoving = FALSE;
	ktgF_simpleMoving = FALSE;
	ktgF_simpleDrawing = FALSE;
	ktgF_processKeys = FALSE;
	ktgF_connectionStartDraw = FALSE;
	ktgF_connectionDrawing = FALSE;
	ktgF_connectionContinueDraw = FALSE;

	_whatNodeToDraw = -1;
	_whatTionToDraw = -1;
	_forkX = -1;
	_forkY = -1;
	_paintEventMustBeIgnored = FALSE;
	_forkTimerOn = FALSE;
	_forkPossibleFlag = FALSE;
	_editPossibleOnLBUp = FALSE;
	_editorJustStarted = FALSE;
	_atFirstMove = FALSE;
	_atFirstResize = FALSE;
	_explicitScrolling = FALSE;
	_enable = TRUE;
	_ctrlKeyPressed = FALSE;
	_isFixed = FALSE;
	_editingTag = FALSE;
	_mainPopup = NIL;
	_regionLength = REGIONLENGTH;
	_arrowLength = ARROWLENGTH;
	_maxXValue = MAXSCROLL;
	_maxYValue = MAXSCROLL;
	_minX = OODMAXINT;
	_minY = OODMAXINT;
	_maxX = 0;
	_maxY = 0;
	_width = 0;
	_height = 0;
	_popupX = 0;
	_popupY = 0;
	_currentX = 0;
	_currentY = 0;
	_focusList = new FigureList();
	_activeNodes = new FigureList();
	_drawingContext = KTG_DRAWING;
	_canvasRgn = NIL;
	_currentFocus = NIL;
	_currentConnection = NIL;
	_currentDrawingType = 0;
	_fontInfo = new FontInfo();
	_fontHeight = 0;
	_backUp = NIL;
	_theBucket = NIL;
	viewTitle = "";
	viewTitleWithOutExtension = "";
	_firstOnDrawCall = TRUE;
}

void COODView::deleteBackUp()
{
	if (_backUp == NIL) return;
	clearBackUp();
	_backUp->deleteNeighbors();
	delete _backUp;
	_backUp = NIL;
}

COODView::~COODView()
{
	deleteBackUp();
	if (_canvasRgn != NIL) {
		delete _canvasRgn;
		_canvasRgn = NIL;
	}
	if (_focusList != NIL) {
		delete _focusList;
		_focusList = NIL;
	}
	if (_activeNodes != NIL) {
		delete _activeNodes;
		_activeNodes = NIL;
	}
	if (_fontInfo != NIL) {
		delete _fontInfo;
		_fontInfo = NIL;
	}
	if (_theBucket != NIL) {
		delete _theBucket; 
		_theBucket = NIL;
	}
}

FigureList *COODView::figures()
{
	if (_toBeDestroyed) return NIL;
	COODDoc *docPtr = GetDocument();
	return docPtr->figures(viewTitle);
}

int COODView::originX()
{
	COODDoc *docPtr = GetDocument();
	return docPtr->originX(viewTitle);
}

int COODView::originY()
{
	COODDoc *docPtr = GetDocument();
	return docPtr->originY(viewTitle);
}

void COODView::setOriginX(int x)
{
	COODDoc *docPtr = GetDocument();
	docPtr->setOriginX(viewTitle,x);
	return;
}

void COODView::setOriginY(int y)
{
	COODDoc *docPtr = GetDocument();
	docPtr->setOriginY(viewTitle,y);
	return;
}

int COODView::zoomRatioX()
{
	COODDoc *docPtr = GetDocument();
	return docPtr->zoomRatioX(viewTitle);
}

int COODView::zoomRatioY()
{
	COODDoc *docPtr = GetDocument();
	return docPtr->zoomRatioY(viewTitle);
}

void COODView::setZoomRatioX(int zoomX)
{
	COODDoc *docPtr = GetDocument();
	docPtr->setZoomRatioX(viewTitle,zoomX);
	return;
}

void COODView::setZoomRatioY(int zoomY)
{
	COODDoc *docPtr = GetDocument();
	docPtr->setZoomRatioY(viewTitle,zoomY);
	return;
}

void COODView::setController()
{
	FigureList *figureList = figures();
	if (figureList == NIL) return;
	Figure *aFigure = figureList->getFirst();
	while(aFigure != NIL) {
		aFigure->setController(this);
		aFigure = figureList->getNext();
	}

	COODDoc *pDoc = GetDocument();
	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL) 
			selection->setController(this,viewTitle);
	}
}

void COODView::setControllerAbsolutely()
{
	COODView::setController();

	COODDoc *pDoc = GetDocument();
	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL) 
			selection->setControllerAbsolutely(this);
	}
}

void COODView::setPopups() 
{
}

void COODView::startFork()
{
}

void COODView::minMaxXY(XCoord &x1,YCoord &y1)
{
	if (_minX > x1.x) _minX = x1.x;
	if (_maxX < x1.x) _maxX = x1.x;
	if (_minY > y1.y) _minY = y1.y;
	if (_maxY < y1.y) _maxY = y1.y;
}

void COODView::minMaxXY(XCoord &x1,YCoord &y1,XCoord &x2,YCoord &y2)
{
	if (_minX > x1.x) _minX = x1.x;
	if (_maxX < x1.x) _maxX = x1.x;
	if (_minY > y1.y) _minY = y1.y;
	if (_maxY < y1.y) _maxY = y1.y;
	if (_minX > x2.x) _minX = x2.x;
	if (_maxX < x2.x) _maxX = x2.x;
	if (_minY > y2.y) _minY = y2.y;
	if (_maxY < y2.y) _maxY = y2.y;
}

void COODView::resetMinMaxXY()
{
	_maxX = 0; _maxY = 0;
	_minX = _maxXValue;
	_minY = _maxYValue;
}

void COODView::hideGlobalDlgs()
{
	theAppPtr->deactivateClassPropertyDlgs();
	if ((theAppPtr->theRelationTraverseDlg->GetStyle() & WS_VISIBLE) != 0) {
		theAppPtr->theRelationTraverseDlg->ShowWindow(SW_HIDE);
	}
	if ((theAppPtr->thePackagePropDlg->GetStyle() & WS_VISIBLE) != 0) {
		theAppPtr->thePackagePropDlg->ShowWindow(SW_HIDE);
	}
}

void COODView::remove(Figure *figure)	
{ 
	GetDocument()->setModifiedFlag(); 
	figures()->remove(figure); 
}

void COODView::insert(Figure *figure)	
{ 
	GetDocument()->setModifiedFlag(); 
	figures()->insert(figure); 
}

void COODView::remakeCanvasRgn()
{
	if (_canvasRgn != NIL) delete _canvasRgn;
	_canvasRgn = makeRectRegion(0,0,_width,_height);
}

void COODView::collectActiveNodes(UnsignedLong *category)
{
	_activeNodes->clear();
	Figure *aFigure = figures()->getFirst();
	while (aFigure != NIL) {
		UnsignedLong *who = aFigure->whoAreYou();
		if (who->isIn(category)) {
			_activeNodes->insert(aFigure);
		}
		aFigure = figures()->getNext();
	}
}

void COODView::saveViewBMP(CString &fileName)
{
	CDC *pDC = GetDC();

	CRect viewSize;
	GetClientRect(&viewSize);

	CDC imageDC;
	BOOL succ = imageDC.CreateCompatibleDC(pDC);
	if (!succ) {
		ErrorMsg("Can't create DC for image.");
		ReleaseDC(pDC);
		return;
	}

	CBitmap imageBitmap;
	succ = imageBitmap.CreateCompatibleBitmap(pDC,viewSize.Width(),viewSize.Height());
	if (!succ) {
		ErrorMsg("Can't create Bitmap image.");
		ReleaseDC(pDC);
		return;
	}

	imageDC.SelectObject(&imageBitmap);

	succ = imageDC.BitBlt(0,0,viewSize.Width(),viewSize.Height(),
		pDC,0,0,SRCCOPY);
	if (!succ) {
		ErrorMsg("Can't capture view image.");
		ReleaseDC(pDC);
		return;
	}
	ReleaseDC(pDC);

	mainFramePtr->saveImageToFileAndClipboard(fileName,imageBitmap);
}

/*
void COODView::collectActiveNodesWithName(UnsignedLong *category)
{
	char name[BUFSIZ];
	_activeNodes->clear();
	Figure *aFigure = figures()->getFirst();
	while (aFigure != NIL) {
		UnsignedLong *who = aFigure->whoAreYou();
		if (who->isIn(category) && who->isIn(WEAREEDITABLEOBJECTS)) {
			int n = ((EditableFigure *)aFigure)->getName(name,BUFSIZ);
			if (n > 0) _activeNodes->insert(aFigure);
		}
		aFigure = figures()->getNext();
	}
}
*/

void COODView::localTraceEnter(CPoint event,FigureList *list,BOOL forFigures)
{
	FigureList *figure_list = list;
	if (figure_list == NIL) return;
	if (_enable == FALSE) return;
	int x = event.x;
	int y = event.y;
	CPoint pt(x,y);
	LPtoDP(pt);
	if (!_canvasRgn->PtInRegion(pt.x,pt.y)) {
		_focusList->clear();
		_currentFocus = NIL;
		return;
	}
	if (_currentFocus == NIL) _focusList->clear();
	if (_isFixed) {
		_currentFocus = NIL;
		return;
	}
	if (_currentFocus != NIL) {
		Figure *ptr = _focusList->pop();
		if (ptr == NIL) {
			_currentFocus = NIL;
		} else if (ptr->onEnter(x,y) == FALSE) {
			if (forFigures == FALSE) {
				lowlightDrawBoundary(ptr);
			}
			while (TRUE) {
				ptr = _focusList->pop();
				if (ptr == NIL) break;
				else if (ptr->onEnter(x,y)) {
					if (forFigures == FALSE) {
						highlight(ptr);
					}
					_focusList->push(ptr);
					break;
				}
			}
			_currentFocus = ptr;
		} else {
			_focusList->push(_currentFocus);
		}
	}
	BOOL check = FALSE;
	BOOL found = FALSE;
	BOOL newfound = FALSE;
	Figure *newFocus = NIL;
	Figure *figureptr = figure_list->getFirst();
	while (figureptr != NIL) {
		check = figureptr->onEnter(x,y);
		found = found || check;
		if ( (check) &&
			!(_focusList->inList(figureptr)) ) {
			_focusList->push(figureptr);
			newfound = TRUE;
			newFocus = figureptr;
			break;
		}
		figureptr = figure_list->getNext();
	}
	figureptr = _focusList->getFirst();
	while (figureptr != NIL) {
		check = figureptr->onEnter(x,y);
		if (check == FALSE) {
			_focusList->remove(figureptr);
			figureptr = _focusList->getFirst();
		} else {
			figureptr = _focusList->getNext();
		}
	}
	if (newfound) {
		if (forFigures == FALSE) {
			if (_currentFocus != NIL) {
				lowlightDrawBoundary(_currentFocus);
			}
			highlight(newFocus);
		}
		_currentFocus = newFocus;
	} else if (found == FALSE) {
		if (forFigures == FALSE) {
			if (_currentFocus != NIL) {
				lowlightDrawBoundary(_currentFocus);
			}
		}
		_currentFocus = NIL;
		_focusList->clear();
	}
}

void COODView::traceEnter(CPoint event)
{
	if (_enable == FALSE) return;
	if (_editingTag) return;
	localTraceEnter(event,figures(),TRUE);
}

void COODView::showFigureOnCenterOfView(NodeFigure *aNode)
{
	if (_currentFocus != NIL) {
		eraseDots(_currentFocus);
		_currentFocus = NIL;
		Invalidate();
	}
	CPoint sp;
	int cx = (aNode->shape()->_x1.x + aNode->shape()->_x2.x) / 2;
	int cy = (aNode->shape()->_y1.y + aNode->shape()->_y2.y) / 2;
	int px = cx - _width/2;
	int py = cy - _height/2;
	sp.x = px;
	sp.y = py;
	ScrollToPosition(sp);
	_currentFocus = aNode;
	drawDots(_currentFocus);
	Invalidate();
}

void COODView::moveScrollB(int deltax,int deltay)
{
	if (deltax == 0 && deltay == 0) return;
	CPoint sp;
	sp.x = originX() + deltax;
	if (sp.x < 0) {
		sp.x = 0;
	}
	sp.y = originY() + deltay;
	if (sp.y < 0) {
		sp.y = 0;
	}
	ScrollToPosition(sp);
}

void COODView::remakeAllRegions(COODDoc* pDoc)
{
	Figure *all = figures()->getFirst();
	while (all != NIL) {
		all->setInCanvas(all->checkInRegion(_canvasRgn));
		if (all->inCanvas()) {
			all->makeRegion(_canvasRgn);
		} else {
//			all->resetRegion();
			all->releaseRegion();
		}
		all->removeAllExcludeRect();
		all = figures()->getNext();
	}

	FigureList *tmpList = new FigureList();
	Figure *ptr = figures()->getLast();
	while (ptr != NIL) {
		addExcludeRectForBottomObjects(ptr,tmpList);
		tmpList->addFront(ptr);
		ptr = figures()->getBack();
	}
	delete tmpList;

	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL) {
			selection->setInCanvas(this,selection->checkInRegion(this,_canvasRgn));
			if (selection->inCanvas(this)) {
				selection->makeRegion(this);
			} else {
//				selection->resetRegion(this);
				selection->releaseRegion(this);
			}
		}
	}
}

void COODView::redrawFor(Figure *topFigure)
{
	if (topFigure != _currentFocus) return;
	if (topFigure->whoAreYou()->isIn(WEARENODEOBJECTS) == FALSE) return;
	topFigure->removeAllExcludeRect();
	FigureList *figs = figures();
	Figure *ptr = figs->getFirst();
	while (ptr != NIL) {
		ptr->removeExcludeRect(topFigure);
		ptr = figs->getNext();
	}
}

void COODView::localMakeClear()
{
	remakeAllRegions(GetDocument());
	Invalidate(TRUE);
	_currentFocus = NIL;
}

void COODView::OODReleaseDC(CDC* pDC,BOOL releaseFlag)
{
	pDC->SelectObject(OldPen);
	pDC->SetTextColor(OldTextColor);
	pDC->SetBkColor(OldBkColor);
	pDC->SelectObject(OldBrush);
	if (_drawingContext == KTG_RUBBERBANDING) {
		pDC->SetROP2(OldMode);
	}
	// OldGdi는 restore 시키면 리버스 현상이 일어나더라...
//	if (OldGdi != NIL) {
//		pDC->SelectObject(OldGdi);
//	}
	pDC->SelectStockObject(NULL_BRUSH);
	_drawingContext = KTG_DRAWING;
	if (releaseFlag == TRUE) ReleaseDC(pDC);
}

BOOL COODView::captureCursorOnBoundary(int x,int y)
{
	const int gap = 5;
	const int disableBoundary = 4;

	if ((x < -disableBoundary*gap) || (x > _width + disableBoundary*gap) ||
		(y < -disableBoundary*gap) || (y > _height + disableBoundary*gap)) {
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
		return TRUE;
	}
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return FALSE;
}

void COODView::movePointer(int x,int y)
{
	CPoint toMove(x,y);
	LPtoDP(toMove);
	ClientToScreen(&toMove);
	SetCursorPos(toMove.x,toMove.y);
	_currentX = x;
	_currentY = y;
}

BOOL COODView::checkLimitForFigure(int newx,int newy,int *deltax,int *deltay)
{
	if (_currentFocus != NIL &&
		ktgF_simpleMoving == TRUE &&
		_currentFocus->whoAreYou()->equals(IAMBUCKET)) 
		return FALSE;
	else if (_currentFocus != NIL &&
		ktgF_simpleDrawing == TRUE &&
		_currentFocus->whoAreYou()->equals(IAMANCHOR)) 
		return FALSE;

	CPoint pt(newx,newy);
	LPtoDP(pt);
	newx = pt.x;
	newy = pt.y;

	const int gap = 5;

	if ((originX() + newx < gap) ||
	    (originY() + newy < gap) ||
		(originX() + newx > _maxXValue - gap) ||
		(originY() + newy > _maxYValue - gap)) {
		return FALSE;
	}
	int dx = 0;
	int dy = 0;
	if (newx < gap) {
		dx = -SCROLLBARDELTA;
	} 
	if (newy < gap) {
		dy = -SCROLLBARDELTA;
	}
	if (newx > _width - gap) {
		dx = SCROLLBARDELTA;
	} 
	if (newy > _height - gap) {
		dy = SCROLLBARDELTA;
	}
	if (dx != 0 || dy != 0) {
		if (_editingTag && _currentFocus != NIL) {
			clear(_currentFocus);
//			((Text *)_currentFocus->focus())->vterm()->vanish();
		}
	}
	moveScrollB(dx,dy);
	if (dx != 0 || dy != 0) {
		// these values are used to reset the position of popup
		if (deltax != NIL) {
			*deltax = dx;
		}
		if (deltay != NIL) {
			*deltay = dy;
		}
		return TRUE;
	}
	return FALSE;
}

void COODView::eraseDots(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_ERASING);
	OnPrepareDC(pDC);
	figure->eraseDots(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::drawDots(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_FOCUSING);
	OnPrepareDC(pDC);
	figure->drawDots(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::highlight(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_HIGHLIGHTING);
	OnPrepareDC(pDC);
	figure->draw(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::draw(Figure *figure)
{
	figure->makeRegion(_canvasRgn);
	CDC *pDC = GetDC();
	setDrawingContext(KTG_DRAWING);
	OnPrepareDC(pDC);
	figure->draw(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::drawWithNeighbors(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_DRAWING);
	OnPrepareDC(pDC);
	figure->drawWithNeighbors(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::lowlightDraw(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_DRAWING);
	OnPrepareDC(pDC);
	figure->drawBoundary(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::lowlightDrawBoundary(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_DRAWING);
	OnPrepareDC(pDC);
	figure->drawBoundaryEx(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::lowlight(Figure *figure)
{
	eraseDots(figure);
}

void COODView::drawAllFigures()
{
	CDC *pDC = GetDC();
	drawAllFigures(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::drawAllFigures(CDC* pDC)
{
	setDrawingContext(KTG_DRAWING);
	OnPrepareDC(pDC); 
	Figure *ptr = figures()->getFirst();
	while(ptr != NIL) {
		if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS) == TRUE)
			ptr->draw(pDC);
		ptr = figures()->getNext();
	}
	ptr = figures()->getFirst();
	while(ptr != NIL) {
		if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS) == FALSE)
			ptr->draw(pDC);
		ptr = figures()->getNext();
	}
	OODReleaseDC(pDC,FALSE);
}

void COODView::rubberbanding(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_RUBBERBANDING);
	OnPrepareDC(pDC);
	figure->drawBoundary(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::clear(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_ERASING);
	OnPrepareDC(pDC);
	figure->clear(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::clearBackUp()
{
	if (_backUp == NIL) return;
	CDC *pDC = GetDC();
	setDrawingContext(KTG_ERASING);
	OnPrepareDC(pDC);
	_backUp->clearMeAndNeighbors(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::erase(Figure *figure)
{
	CDC *pDC = GetDC();
	setDrawingContext(KTG_ERASING);
	OnPrepareDC(pDC);
	figure->draw(pDC);
	OODReleaseDC(pDC,TRUE);
}

void COODView::clearArea(int x,int y,int w,int h)
{
	CRect tmp(x,y,x+w,y+h);
	invalidateRect(&tmp,TRUE);
	/*
	MSG msg;
	while(TRUE) {
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			return;
		}
	}
	*/
}

void COODView::deleteSelectedObject() 
{
	if (m_pSelection == NULL) return;
	if (m_pSelection->IsInPlaceActive()) return;
	if (m_pSelection->IsOpen()) return;
	GetDocument()->setModifiedFlag(); 
	m_pSelection->Delete();
	m_pSelection = NULL;
	SetClassLong(m_hWnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
	Invalidate();
}

void COODView::deleteCurrentFigure()
{
	GetDocument()->setModifiedFlag(); 
	if (_theBucket->isEmpty() == FALSE) {
		COODCntrlItemList &bucketOleItems = _theBucket->getOleItems();
		COODCntrlItem *anItem = bucketOleItems.getFirst();
		while(anItem != NIL) {
			anItem->Delete();
			anItem = bucketOleItems.getNext();
		}
		bucketOleItems.clear();

		FigureList &bucketFigures = _theBucket->getFigures();
		FigureList nodeFigures;
		Figure *aFigure = bucketFigures.getFirst();
		while(aFigure != NIL) {
			if (aFigure->whoAreYou()->isIn(WEARECONNECTIONS) == FALSE) {
				nodeFigures.insert(aFigure);
			}
			aFigure = bucketFigures.getNext();
		}

		CStringList deletedClasses;
		aFigure = nodeFigures.getFirst();
		while(aFigure != NIL) {
			if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE) == TRUE) {
				char buffer[BUFSIZ];
				((ClassTemplate *)aFigure)->getName(buffer,BUFSIZ);
				CString aClassName = buffer;
				if (deletedClasses.Find(aClassName) == NULL) {
					deletedClasses.AddTail(aClassName);
				}
			}
			aFigure->deleteNeighbors();
			figures()->remove(aFigure);
			checkInList(aFigure);
			delete aFigure;
			aFigure = nodeFigures.getNext();
		}
		_currentFocus = NIL;
		_currentConnection = NIL;
		bucketFigures.clear();
		remakeAllRegions(GetDocument());
		Invalidate();

		POSITION pos = deletedClasses.GetHeadPosition();
		while (pos != NULL) {
			CString aName = deletedClasses.GetNext(pos);
			tryToDeleteClassContentFromRepository(aName);
		}
		return;
	}
	if (_currentFocus == NIL) {
		return;
	}
	if (_currentFocus != _currentFocus->container()) {
		_currentFocus->container()->deleteFocusObject();
		_currentFocus = NIL;
		Invalidate();
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMNOTE) &&
		_currentFocus->focus() != NIL &&
		_currentFocus->focus()->whoAreYou()->equals(IAMANCHOR)) {
		_currentFocus->deleteFocusObject();
		_currentFocus = NIL;
		Invalidate();
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE) &&
		_currentFocus->focus() != NIL &&
		(_currentFocus->focus()->whoAreYou()->equals(IAMCIRCLE) ||
		_currentFocus->focus()->whoAreYou()->equals(IAMINTERFACEPORTTEXT))) {
		_currentFocus->deleteFocusObject();
		_currentFocus = NIL;
		Invalidate();
		return;
	}
	if (_currentFocus->whoAreYou()->equals(IAMSEQUENCEOBJECT) &&
		_currentFocus->focus() != NIL &&
		_currentFocus->focus()->whoAreYou()->equals(IAMACTIVATIONBAR)) {
		_currentFocus->container()->deleteFocusObject();
		_currentFocus = NIL;
		Invalidate();
		return;
	}
	if (_currentFocus->whoAreYou()->isIn(WEARECONNECTIONS)) {
		BOOL segmentDeleted = 
			((Connection *)_currentFocus)->tryToDeleteOneLineSegment();
		if (segmentDeleted == TRUE) {
			_currentFocus = NIL;
			Invalidate();
			return;
		}
	}
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
		ClassTemplate *pClass = (ClassTemplate *)_currentFocus;
		char name[BUFSIZ];
		pClass->getName(name,BUFSIZ);
		_currentFocus->deleteNeighbors();
		figures()->remove(_currentFocus);
		redrawFor(_currentFocus);
		checkInList(_currentFocus);
		delete _currentFocus;
		_currentFocus = NIL;
		_currentConnection = NIL;
		Invalidate();
		tryToDeleteClassContentFromRepository(name);
		return;
	}
	_currentFocus->deleteNeighbors();
	figures()->remove(_currentFocus);
	redrawFor(_currentFocus);
	checkInList(_currentFocus);
	delete _currentFocus;
	_currentFocus = NIL;
	_currentConnection = NIL;
	Invalidate();
}

void COODView::tryToDeleteClassContentFromRepository(const char *className)
{
	if (theAppPtr->runAsServerFlag == TRUE) {
		return;
	}
	if (theAppPtr->pCOODClassDoc == NIL) {
		return;
	}
	if (theAppPtr->classDelNoAlwaysFlag == TRUE) {
		return;
	}

	CString cName = className;
	theAppPtr->pCOODClassDoc->tryToDeleteClassContentFromRepository(cName);
}

void COODView::startResize()
{
	eraseDots(_theBucket);
	_theBucket->clearList();

	/* 이 경우 currentFocus는 첫번째 OnDraw() 호출시에 figures에서 빠진다. */
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	lowlight(_currentFocus);
	redrawFor(_currentFocus);
	_currentFocus->resetFocus();
	_currentFocus->resizeProlog();
	Invalidate();
}

void COODView::startMove()
{
	if (_currentFocus->whoAreYou()->equals(IAMBUCKET) == FALSE) {
		eraseDots(_theBucket);
		_theBucket->clearList();
	}

	if (_currentFocus->whoAreYou()->isIn(WEAREWIDEOBJECTS)) {
		NodeFigure *nodeFigure = (NodeFigure *)_currentFocus;
		int x1 = nodeFigure->shape()->getX1();
		int y1 = nodeFigure->shape()->getY1();
		int x2 = nodeFigure->shape()->getX2();
		int y2 = nodeFigure->shape()->getY2();
		_theBucket->setCoord(x1-1,y1-1,x2+1,y2+1);
		_theBucket->insert(nodeFigure);
		_theBucket->collectContainedFigures(figures());
		_theBucket->collectContainedOleItems(GetDocument(),this);
		remakeAllRegions(GetDocument());
		_currentFocus = _theBucket;
	} else {
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
	}
	lowlight(_currentFocus);
	deleteBackUp();
//*	_backUp = _currentFocus->makeBackUp();
	redrawFor(_currentFocus);
	_currentFocus->moveProlog();
	Invalidate();
}

void COODView::killForkTimer()
{
	KillTimer(FORK_TIMER);
	_forkTimerOn = FALSE;
	clearForkPointAsX();
}

void COODView::warpPointer(int x,int y)
{
	CPoint tomove(x,y);
	ClientToScreen(&tomove);
	SetCursorPos(tomove.x,tomove.y);
	_currentX = x;
	_currentY = y;
	MSG msg;
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
		if (msg.message == WM_MOUSEMOVE) return;
		else DispatchMessage(&msg);
	}
}

void COODView::drawingHandler(CPoint event,Figure *focus)
{
	int x = event.x;
	int y = event.y;
	if (_currentX == x && _currentY == y) {
		return;
	}
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(&cursorPos);
	int tx = cursorPos.x;
	int ty = cursorPos.y;
	BOOL outOfRange = captureCursorOnBoundary(tx,ty);
	
	if (outOfRange) {
		return;
	}

	int dx = x - _currentX;
	int dy = y - _currentY;
	_currentX = x;
	_currentY = y;

	if (GetDocument()->IsInPlaceActive()) {
		CDC *pDC = GetDC();
		setDrawingContext(KTG_RUBBERBANDING);
		OnPrepareDC(pDC);
		focus->drawing(pDC,dx,dy);
		OODReleaseDC(pDC,TRUE);
		return;
	}

	int sdx = 0;
	int sdy = 0;
	BOOL moved = checkLimitForFigure(x,y,&sdx,&sdy);
	if (moved) {
		focus->setHotXY(x+sdx,y+sdy);
		Invalidate();
		return;
	}
	CDC *pDC = GetDC();
	setDrawingContext(KTG_RUBBERBANDING);
	OnPrepareDC(pDC);
	focus->drawing(pDC,dx,dy);
	OODReleaseDC(pDC,TRUE);
	return;
}

void COODView::movingHandler(CPoint event,BOOL explicitCall)
{
	int x = event.x;
	int y = event.y;
	if (explicitCall == FALSE && _currentX == x && _currentY == y) {
		return;
	}
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(&cursorPos);
	int tx = cursorPos.x;
	int ty = cursorPos.y;
	BOOL outOfRange = captureCursorOnBoundary(tx,ty);
	
	if (outOfRange) {
		KeepGoing = FALSE;
		return;
	}

	int dx = x - _currentX;
	int dy = y - _currentY;
	_currentX = x;
	_currentY = y;

	if (GetDocument()->IsInPlaceActive()) {
		CDC *pDC = GetDC();
		setDrawingContext(KTG_RUBBERBANDING);
		OnPrepareDC(pDC);
		_currentFocus->move(pDC,dx,dy);
		OODReleaseDC(pDC,TRUE);
		KeepGoing = FALSE;
		return;
	}

	int sdx = 0;
	int sdy = 0;
	BOOL moved = checkLimitForFigure(x,y,&sdx,&sdy);
	if (moved) {
		if (explicitCall) {
			_currentFocus->moveCoordForScroll(sdx,sdy);
		} else {
			if (KeepGoing) {
				_currentFocus->moveCoordForScroll(dx,dy);
			} else {
				_currentFocus->moveCoordForScroll(sdx+dx,sdy+dy);
			}
		}
		Invalidate();
		KeepGoing = TRUE;
		return;
	}
	CDC *pDC = GetDC();
	setDrawingContext(KTG_RUBBERBANDING);
	OnPrepareDC(pDC);
	_currentFocus->move(pDC,dx,dy);
	OODReleaseDC(pDC,TRUE);
	KeepGoing = FALSE;
	return;
}

void COODView::stopDraw()
{
	GetDocument()->setModifiedFlag(); 
	if (_currentFocus->whoAreYou()->equals(IAMBUCKET)) {
		_currentFocus->epilog();
		_currentFocus->makeRegion(_canvasRgn);
		clear(_currentFocus);
		_theBucket->copyContainedFigures(figures());
		_theBucket->copyContainedOleItems(GetDocument(),this);
		drawDots(_currentFocus);
		_currentFocus = NIL;
		remakeAllRegions(GetDocument());
	} else if (_currentFocus->whoAreYou()->equals(IAMANCHOR)) {
		_currentFocus = _currentFocus->container();
		_currentFocus->makeRegion(_canvasRgn);
		_whatTionToDraw = -1;
	} else {
		_currentFocus->resetFocus();
		_currentFocus->epilog();
		_currentFocus = _currentFocus->container();
		_currentFocus->makeRegion(_canvasRgn);
		addExcludeRectForBottomObjects(_currentFocus,figures());
		figures()->insert(_currentFocus);
		clear(_currentFocus);
		drawWithNeighbors(_currentFocus);
		if (_currentFocus->whoAreYou()->isIn(WEAREWIDEOBJECTS)) {
			remakeAllRegions(GetDocument());
		} else if (_currentFocus->whoAreYou()->equals(IAMLINE)) {
			_whatTionToDraw = -1;
		}
	}
	Invalidate(); 
}

void COODView::stopMove()
{
	GetDocument()->setModifiedFlag(); 
	deleteBackUp();
	if (_currentFocus->whoAreYou()->equals(IAMBUCKET)) {
		_currentFocus->epilog();
		_currentFocus->makeRegion(_canvasRgn);
		clear(_currentFocus);
		Bucket *theBucket = (Bucket *)_currentFocus;
		theBucket->restoreFigures(figures());
		theBucket->restoreOleItems(GetDocument());
		_currentFocus = NIL;
		remakeAllRegions(GetDocument());
	} else {
		_currentFocus->container()->resetFocus();
		_currentFocus->epilog();
		if (_currentFocus != _currentFocus->container()) {
			_currentFocus = _currentFocus->container();
			_currentFocus->makeRegion(_canvasRgn);
		} else {
			_currentFocus->makeRegion(_canvasRgn);
			addExcludeRectForBottomObjects(_currentFocus,figures());
			figures()->insert(_currentFocus);
		}
		clear(_currentFocus);
		drawWithNeighbors(_currentFocus);
		if (_currentFocus->whoAreYou()->isIn(WEAREWIDEOBJECTS)) {
			remakeAllRegions(GetDocument());
		}
	}
	Invalidate(); 
}

void COODView::addExcludeRectForBottomObjects(Figure *topFigure,FigureList *figs) 
{
	if (topFigure->whoAreYou()->isIn(WEARENODEOBJECTS) == FALSE) return;
	if (topFigure->whoAreYou()->isIn(WEAREWIDEOBJECTS) == TRUE) return;
	int x1 = ((NodeFigure *)topFigure)->getX1();
	int y1 = ((NodeFigure *)topFigure)->getY1();
	int x2 = ((NodeFigure *)topFigure)->getX2() + 1;
	int y2 = ((NodeFigure *)topFigure)->getY2() + 1;
	if (figs->inList(topFigure)) return;
	Figure *ptr = figs->getFirst();
	while (ptr != NIL) {
		ptr->removeExcludeRect(topFigure);
		ptr = figs->getNext();
	}
	ptr = figs->getFirst();
	while (ptr != NIL) {
		if (ptr->whoAreYou()->isIn(WEARENODEOBJECTS)) {
			NodeFigure *aNode = (NodeFigure *)ptr;
			CRgn jointRgn;
			jointRgn.CreateRectRgn(0,0,0,0);
			int result = jointRgn.CombineRgn(topFigure->clip(),aNode->clip(),RGN_AND);
			if (result != NULLREGION && result != ERROR) {
				ExcludeRect *pRect = new ExcludeRect(topFigure,x1,y1,x2,y2);
				aNode->addExcludeRect(pRect);
			}
		}
		ptr = figs->getNext();
	}
}

void COODView::checkInList(Figure *ptr)
{
	_focusList->clear();
}

// functions for Text objects

void COODView::setCaretXY(int x,int y)
{
	CPoint caretXY;
	caretXY.x = x;
	caretXY.y = y;
	LPtoDP(caretXY);
	SetCaretPos(caretXY);
}								  

BOOL COODView::editorFinished()
{
	GetDocument()->setModifiedFlag(); 
	if (_editingTag == FALSE) return TRUE;
	_editingTag = FALSE;
	if (ktgF_processKeys == FALSE) return TRUE;
	ktgF_processKeys = FALSE;
	if (_currentFocus == NIL) return TRUE;
	_currentFocus->bye();
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
		char name[BUFSIZ];
		int len = ((ClassTemplate *)_currentFocus)->getName(name,BUFSIZ);
		if (len <= 0) {
			clear(_currentFocus);
			((ClassTemplate *)_currentFocus)->deleteMemberTextContent();
			delete _currentFocus;
			_currentFocus = NIL;
			InfoMsg("Please set a name for the class.\nThis class is being deleted.");
			return FALSE;
		}
	}
	Text *textFocus = ((Text *)_currentFocus->focus());
	if (textFocus != NIL) {
		UnsignedLong* identity = textFocus->whoAreYou();
		if (identity->equals(IAMTEXT) && 
			textFocus->isObsolete()) {
			clear(_currentFocus);
			delete _currentFocus;
			_currentFocus = NIL;
			return TRUE;
		}
		if (_currentFocus->whoAreYou()->isIn(WEARECONNECTIONS) &&
			textFocus->whoAreYou()->isIn(WEARETEXTOBJECTS) &&
			textFocus->isObsolete()) {
			textFocus->disconnectFromContainer();
			delete textFocus;
		}
	}
	_currentFocus->recalcWidthHeight();
	_currentFocus->makeRegion(_canvasRgn);
	addExcludeRectForBottomObjects(_currentFocus,figures());
	figures()->insert(_currentFocus);
	draw(_currentFocus);
	if (_currentFocus->whoAreYou()->isIn(WEAREWIDEOBJECTS) == TRUE) {
		remakeAllRegions(GetDocument());
		Invalidate(TRUE);
	}
	/*
	if (_currentFocus->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
		char name[BUFSIZ];
		int len = ((ClassTemplate *)_currentFocus)->getName(name,BUFSIZ);
		char oldName[BUFSIZ];
		strcpy(oldName,((ClassTemplate *)_currentFocus)->getOldName());
		if (strlen(oldName) != 0) {
			CString oldString = oldName;
			if (oldString.CompareNoCase(name) != 0) {
				UINT ans = YesNoMsg("Are you sure to change this class name ?");
				if (ans == IDYES) return FALSE;
				return FALSE;
			}
		}
	}
	*/
	return TRUE;
}

void COODView::resetFontHeight()
{
	CFont font;
	font.CreateFont(_fontInfo->size,0,0,0,
		_fontInfo->weight,_fontInfo->italicFlag,
		_fontInfo->underlineFlag,_fontInfo->strikeOutFlag,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,_fontInfo->faceName);
	CDC *pDC = GetDC();
	CFont *oldFont = pDC->SelectObject(&font);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	_fontHeight = tm.tmHeight;
	pDC->SelectObject(oldFont);
	ReleaseDC(pDC);
}

BOOL COODView::findForkPoint()
{
	if (_currentFocus == NIL) return FALSE;
	if (_currentFocus->whoAreYou()->isIn(WEAREFORKABLELINES) == FALSE) return FALSE;
	if (_currentFocus->whoAreYou()->equals(IAMDEPENDENCY) == TRUE &&
		this->IsKindOf(RUNTIME_CLASS(CDeploymentView))) return FALSE;
	if (_currentFocus->whoAreYou()->equals(IAMASSOCIATION) == TRUE) {
		Association *association = (Association *)_currentFocus;
		if (association->nodeFigures()->nOfList() >= 3) return FALSE;
	}
	Lines *currentLines = (Lines *)_currentFocus;
	CPoint cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(&cursorPos);
	DPtoLP(cursorPos);
	int tx = cursorPos.x;
	int ty = cursorPos.y;
	_forkX = -1;
	_forkY = -1;
	if (currentLines->isForkable(tx,ty,_forkX,_forkY) == FALSE) return FALSE;
	if (_forkX == -1 || _forkY == -1) return FALSE;
	CPoint forkPoint(_forkX,_forkY);
	LPtoDP(forkPoint);
	_forkX = forkPoint.x;
	_forkY = forkPoint.y;
	showForkPointAsX();
	return TRUE;
}

void COODView::showForkPointAsX()
{
	int delta = 3;
	int x1 = _forkX - delta;
	int x2 = _forkX + delta;
	int y1 = _forkY - delta;
	int y2 = _forkY + delta;

	CDC *pDC = GetDC();
	Figure::DrawLine(pDC,x1,y1,x2+1,y2+1);
	Figure::DrawLine(pDC,x1,y2,x2+1,y1-1);
	ReleaseDC(pDC);

	userMsg("You can fork here.");
}

void COODView::clearForkPointAsX()
{
	if (_forkX == -1 || _forkY == -1) return;
	if (_forkPossibleFlag == FALSE) return;
	_forkPossibleFlag = FALSE;

	int delta = 3;
	int x1 = _forkX - delta - 1;
	int x2 = _forkX + delta + 1;
	int y1 = _forkY - delta - 1;
	int y2 = _forkY + delta + 1;

	CRect tmp(x1,y1,x2,y2);
	invalidateRect(&tmp);
	SendMessage(WM_PAINT);
	userMsg("Ready");
}

void COODView::startEditor(CPoint event)
{
	eraseDots(_theBucket);
	_theBucket->clearList();

	_editingTag = TRUE;
	resetWhatTionToDraw();
	_focusList->clear();
	localTraceEnter(event,figures(),TRUE);
	int x = event.x;
	int y = event.y;
	if (_currentFocus == NIL) {
		_currentFocus = (Figure *) new Text(this,x,y,NIL);
		((Text *)_currentFocus)->startEdit();
	} else if (_currentFocus->whoAreYou()->equals(IAMTEXT)) {
		lowlight(_currentFocus);
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
		redrawFor(_currentFocus);
		draw(_currentFocus);
		((Text *)_currentFocus)->setXY(x,y);
		((Text *)_currentFocus)->startEdit();
		clear(_currentFocus);
	} else if (_currentFocus->whoAreYou()->equals(IAMCOLLABORATIONOBJECT) &&
			_currentFocus->focus() != NIL &&
			_currentFocus->focus()->whoAreYou()->equals(IAMCOLOBJMESSAGETEXT)) {
		lowlight(_currentFocus->focus());
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
		redrawFor(_currentFocus);
		draw(_currentFocus);
		((CollaborationObjectMessageText *)_currentFocus->focus())->setXY(x,y);
		((CollaborationObjectMessageText *)_currentFocus->focus())->startEdit();
	} else if (_currentFocus->whoAreYou()->equals(IAMSEQUENCEOBJECT) &&
			_currentFocus->focus() != NIL &&
			_currentFocus->focus() != ((SequenceObject *)_currentFocus)->shape()) {
		_editingTag = FALSE;
		return;
	} else if (_currentFocus->whoAreYou()->equals(IAMNOTE) &&
			_currentFocus->focus() != NIL &&
			_currentFocus->focus()->whoAreYou()->equals(IAMANCHOR)) {
		lowlight(_currentFocus);
		_currentFocus = (Figure *) new Text(this,x,y,NIL);
		((Text *)_currentFocus)->startEdit();
	} else if (_currentFocus->whoAreYou()->isIn(WEAREEDITABLEOBJECTS)) {
		lowlight(_currentFocus);
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
		redrawFor(_currentFocus);
		clear(_currentFocus);
		draw(_currentFocus);
		((NodeFigure *)_currentFocus)->setFocus(x,y);
		((NodeFigure *)_currentFocus)->startEdit();
	} else if (_currentFocus->whoAreYou()->isIn(WEARECONNECTIONS) &&
			   _currentFocus->focus()->whoAreYou()->equals(IAMSTATICCONNECTIONTEXT) == FALSE &&
			   _currentFocus->focus()->whoAreYou()->isIn(WEARETEXTOBJECTS)) {
		lowlight(_currentFocus);
		figures()->remove(_currentFocus);
		checkInList(_currentFocus);
		redrawFor(_currentFocus);
		draw(_currentFocus);
		((ConnectionText *)_currentFocus->focus())->setXY(x,y);
		((ConnectionText *)_currentFocus->focus())->startEdit();
	} else {
		lowlight(_currentFocus);
		_currentFocus = (Figure *) new Text(this,x,y,NIL);
		((Text *)_currentFocus)->startEdit();
	}
	ktgF_processKeys = TRUE;
}

void COODView::processKeys(UINT nChar)
{
	char oneChar = nChar;
	char asString[2];
	asString[0] = oneChar;
	asString[1] = '\0';
	if (_currentFocus->focus() != NIL)
		((Text *)_currentFocus->focus())->insert(asString);
}

void COODView::setViewTitle(CString &title)
{
	viewTitle = title;
	int len = title.GetLength();
	if (len <= _EXT_LEN5) {
		viewTitleWithOutExtension = title; 
	} else {
		viewTitleWithOutExtension = title.Left(len-_EXT_LEN5);
	}
}

void COODView::showTitleAsModified()
{
	if (GetDocument()->IsInPlaceActive()) return;
//	CMDIChildWnd *pWnd = mainFramePtr->MDIGetActive();
	CFrameWnd *pWnd = GetParentFrame();
	if (pWnd == NULL) return;
	if (pWnd->IsKindOf(RUNTIME_CLASS(CChildFrm))) {
		CChildFrm *pFrame = (CChildFrm *)pWnd;
		CString currentTitle = pFrame->frameTitle;
		int len = currentTitle.GetLength();
		if (len > 0) {
			TCHAR c = currentTitle.GetAt(len-1);
			if (c == '*') return;
		}
		pFrame->frameTitle = pFrame->frameTitle + " *";
		pFrame->OnUpdateFrameTitle(TRUE);
	}
}

void COODView::showTitleAsNotModified()
{
	if (GetDocument()->IsInPlaceActive()) return;
//	CMDIChildWnd *pWnd = mainFramePtr->MDIGetActive();
	CFrameWnd *pWnd = GetParentFrame();
	if (pWnd == NULL) return;
	if (pWnd->IsKindOf(RUNTIME_CLASS(CChildFrm))) {
		CChildFrm *pFrame = (CChildFrm *)pWnd;
		CString currentTitle = pFrame->frameTitle;
		int len = currentTitle.GetLength();
		if (len > 0) {
			TCHAR c = currentTitle.GetAt(len-1);
			if (c != '*') return;
			pFrame->frameTitle = pFrame->frameTitle.Left(len-2);
			pFrame->OnUpdateFrameTitle(TRUE);
		}
	}
}

void COODView::setTitle(CString &title)
{
	if (GetDocument()->IsInPlaceActive()) return;
	setViewTitle(title);
	CMDIChildWnd *pWnd = mainFramePtr->MDIGetActive();
	if (pWnd == NULL) return;
	if (pWnd->IsKindOf(RUNTIME_CLASS(CChildFrm))) {
		CChildFrm *pFrame = (CChildFrm *)pWnd;
		CString title = pFrame->diagramType();
		title = title + ": " + viewTitle;
		pFrame->frameName = viewTitle;
		pFrame->frameTitle = title;
		pFrame->OnUpdateFrameTitle(TRUE);
	}
}

CToolBarCtrl *COODView::getModelToolBarCtrl()
{
	if (GetDocument()->IsInPlaceActive() && GetDocument()->getInPlaceFrame() != NIL) {
		return GetDocument()->getInPlaceFrame()->getModelToolBarCtrl();
	}
	CMDIChildWnd *pWnd = mainFramePtr->MDIGetActive(); 
	if (pWnd == NIL) return NIL;
	if (pWnd->IsKindOf(RUNTIME_CLASS(CChildFrm))) {
		CChildFrm *pFrame = (CChildFrm *)pWnd;
		CToolBar *modelToolBar = (CToolBar *)pFrame->getModelToolBar();
		if (modelToolBar == NIL) return NIL;
		if (modelToolBar->GetSafeHwnd() == NULL) return NIL;
		return &(modelToolBar->GetToolBarCtrl());
	}
	return NIL;
}

void COODView::releaseModelTBButton()
{
	if (_editingTag) {
		editorFinished();
	}
	CToolBarCtrl *control = getModelToolBarCtrl();
	if (control == NIL) return;
	int n = control->GetButtonCount();
	for (int i = 0; i < n; i++) {
		TBBUTTON buttonInfo;
		if (control->GetButton(i,&buttonInfo)) {
			UINT id = buttonInfo.idCommand;
			if (control->IsButtonPressed(id)) {
				control->PressButton(id,FALSE);
				break;
			}
		}
	}
}

void COODView::releaseModelTBButton(UINT commandID)
{
	CToolBarCtrl *tbControl = getModelToolBarCtrl();
	if (tbControl != NIL)
		tbControl->PressButton(commandID,FALSE);
}

void COODView::pressModelTBButton(UINT commandID)
{
	CToolBarCtrl *tbControl = getModelToolBarCtrl();
	if (tbControl != NIL)
		tbControl->PressButton(commandID,TRUE);
}

BOOL COODView::undoIfSomeButtonAlreadyPressed(UINT commandID)
{
	if (m_pSelection != NULL) {
		CRect rect;
		m_pSelection->getClientRect(this,rect);
		InvalidateRect(&rect);
		m_pSelection = NULL;
	}
	if (commandID != -1) {
		hideGlobalDlgs();
		CToolBarCtrl *control = getModelToolBarCtrl();
		if (control != NIL &&
			control->IsButtonPressed(commandID)) {
			// This button pressed again, nothing must be done.
			return TRUE;
		}
	}
	releaseModelTBButton();
	drawingEpilog();
	_theBucket->clearList();
	return FALSE;
}

void COODView::drawingEpilog()
{
	currentOrient = UNDEFINED;
	_activeNodes->clear();
	_whatTionToDraw = -1;
	_whatNodeToDraw = -1;
	ktgF_connectionStartDraw = FALSE;
	if (_currentConnection != NIL) lowlight(_currentConnection);
	if (_currentFocus != NIL) draw(_currentFocus);
	_currentConnection = NIL;
	_currentFocus = NIL;
}
//**
////////////////////////////////////////////////////////////////////////////
// Default function
BOOL COODView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COODView drawing

void COODView::drawGrid(CDC *pDC)
{
	CRect rect;
	int oX = originX();
	int oY = originY();
	int startX = oX - oX / 100 * 100;
	int startY = oY - oY / 100 * 100;
	rect.left = 100 - startX;
	rect.top = 100 - startY;
	rect.right = _width;
	rect.bottom = _height;

	CPen penDot;
	penDot.CreatePen(PS_DOT,1,RGB(0,0,128));
	CPen *oldPen = pDC->SelectObject(&penDot);
	for (int x = rect.left-1; x < rect.right; x += 100) {
		if (x > 0) {
			CPoint pt1(x,0);
			pDC->MoveTo(pt1.x,pt1.y);
			CPoint pt2(x,rect.bottom);
			pDC->LineTo(pt2.x,pt2.y);
		}
	}
	for (int y = rect.top-1; y < rect.bottom; y += 100) {
		if (y > 0) {
			CPoint pt1(0,y);
			pDC->MoveTo(pt1.x,pt1.y);
			CPoint pt2(rect.right,y);
			pDC->LineTo(pt2.x,pt2.y);
		}
	}
	pDC->SelectObject(oldPen);
}

void COODView::OnDraw(CDC* pDC)
{
	if (_paintEventMustBeIgnored) {
		drawAllFigures(pDC);
		return;
	}

	COODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (_firstOnDrawCall) {
		// 이 코드는 OnInitialUpdate()에 있으면 좋겠는데 ... InPlaceFrame 경우에 작동을 안해서 여기에 ...
		// 아울러 _firstOnDrawCall 는 InPlace Document 가 디엑티베이트 될 때 TRUE 로 다시 셋팅됨
		// COODCommonDoc::OnDeactivate() 참조할 것 : 졸나게 고생 끝에 만든 메카니즘이니까 함부로 수정하지 말자.
		CPoint testPoint = GetScrollPosition();
		if (testPoint.x == 0 && testPoint.y == 0 && (originX() != 0 || originY() != 0)) {
			// 스크롤바의 위치를 초기화 ...
			testPoint.x = originX();
			testPoint.y = originY();
			ScrollToPosition(testPoint);
		}
		_firstOnDrawCall = FALSE;
	}
	/*
	CRect client;
	pDC->GetClipBox(client);
//	DPtoLP(client);
	CBrush brush;
	brush.CreateSolidBrush(theAppPtr->paperColor);
//	brush.CreateSolidBrush(RGB(0,0,0));
	brush.UnrealizeObject();
	pDC->FillRect(client,&brush);
	*/

	// TODO: add draw code for native data here
	CPoint oldViewportOrg =	pDC->SetViewportOrg(0,0);
	CPoint sp = GetScrollPosition();
	DPtoLP(sp);
	if (sp.x != originX() || sp.y != originY()) {
		setOriginX(sp.x);
		setOriginY(sp.y);
		remakeAllRegions(pDoc);
		if (_currentFocus != NIL) {
			_currentFocus->makeRegion(_canvasRgn);
		}
	}

	if (!pDC->IsPrinting() && theAppPtr->setGridFlag) {
		drawGrid(pDC);
	}

	if (_backUp) {
		setDrawingContext(KTG_DRAWING);
		OnPrepareDC(pDC); 
		_backUp->drawWithNeighbors(pDC);
		OODReleaseDC(pDC,FALSE);
	}

	Figure *savedFocus = _currentFocus;
	Connection *aConnection = wrongConnections.getFirst();
	while(aConnection != NIL) {
		drawAllFigures(pDC);
		_paintEventMustBeIgnored = TRUE;
		char buffer[BUFSIZ];
		strcpy_s(buffer,BUFSIZ,"Wrong connection : ");
		strcat_s(buffer,BUFSIZ,aConnection->connectionClassName());
		strcat_s(buffer,BUFSIZ," must be deleted.");
		ErrorMsg(buffer);
		if (savedFocus == aConnection) savedFocus = NIL;
		_currentFocus = aConnection;
		_currentFocus->resetFocus();
		deleteCurrentFigure();
		aConnection = wrongConnections.getNext();
	}
	_paintEventMustBeIgnored = FALSE;
	wrongConnections.clear();
	_currentFocus = savedFocus;
	/*
	if (_editingTag == TRUE && _currentFocus != NIL) {
		int x1,y1,x2,y2;
		_currentFocus->getExclusiveClipRect(x1,y1,x2,y2);
		pDC->ExcludeClipRect(x1,y1,x2,y2);
	}
	*/
	setDrawingContext(KTG_DRAWING);
	OnPrepareDC(pDC); 
	FigureList *figs = figures();
	Figure *ptr = figs->getFirst();
	while(ptr != NIL) {
		if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS) == TRUE) {
			ptr->draw(pDC);
		}
		ptr = figs->getNext();
	}
	ptr = figs->getFirst();
	while(ptr != NIL) {
		if (ktgF_simpleMoving && 
			_currentFocus != NIL &&
			ptr->isNeighborConnection(_currentFocus)) {
			/* 화살표 잔상을 없애기 위해 필요하다. */
			rubberbanding(ptr);
		} else if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS) == FALSE) {
			ptr->draw(pDC);
		}
		ptr = figs->getNext();
	}

	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL && m_pSelection != selection) 
			selection->draw(this,pDC);
	}
	if (m_pSelection != NULL) {
		m_pSelection->draw(this,pDC);
		setDrawingContext(KTG_FOCUSING);
		OnPrepareDC(pDC);
		m_pSelection->drawAsSelected(this,pDC);
	}

	OODReleaseDC(pDC,FALSE);
	if (_explicitScrolling) {
		_explicitScrolling = FALSE;
		if (_currentFocus != NIL && _editingTag) {
			editorFinished();
		}
	}
	if (_currentFocus != NIL) {
		if (_editingTag) {
			draw(_currentFocus);
			if (_currentFocus->focus() != NIL) 
				((Text*)_currentFocus->focus())->vterm()->activate();
		} else if (ktgF_simpleMoving || ktgF_simpleDrawing) {
			rubberbanding(_currentFocus);
		} else {
			drawDots(_currentFocus);
		}
	} else {
		drawDots(_theBucket);
	}
	if (KeepGoing) {
		CPoint pt(_currentX,_currentY);
		if (ktgF_simpleMoving) {
			movingHandler(pt,TRUE);
		}
	}
	pDC->SetViewportOrg(oldViewportOrg);
}

void COODView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	m_pSelection = NULL;
	_theBucket = new Bucket(this);

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	RECT box;
	GetClientRect(&box);
	CPoint point(box.right,box.bottom);
	DPtoLP(point);
	_width = point.x;
	_height = point.y;
	sizeTotal.cx = _maxXValue;
	sizeTotal.cy = _maxYValue;
	SetScrollSizes(MM_TEXT, sizeTotal);
	remakeCanvasRgn();
}

/////////////////////////////////////////////////////////////////////////////
// COODView printing

BOOL COODView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COODView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	_oldOriginX = originX();
	_oldOriginY = originY();
	setOriginX(0);
	setOriginY(0);
	_nOfRowsForPrint = 1;
	_nOfColsForPrint = 1;
	if (figures()->nOfList() == 0) {
		pInfo->SetMaxPage(1);
		return;
	}
	resetMinMaxXY();
	Figure *ptr = figures()->getFirst();
	while(ptr != NIL) {
		ptr->setInCanvas(TRUE);
		ptr->minMaxXY();
		ptr = figures()->getNext();
	}
	int dpiX = pDC->GetDeviceCaps(LOGPIXELSX);  
	int dpiY = pDC->GetDeviceCaps(LOGPIXELSY);  
	int deviceWidth = pDC->GetDeviceCaps(HORZRES); // 스크린 상의 x 픽셀 수
	int deviceHeight = pDC->GetDeviceCaps(VERTRES); // 스크린 상의 y 픽셀 수
	double xInch = (double)deviceWidth/(double)dpiX;
	double yInch = (double)deviceHeight/(double)dpiY;
    double rX; 
	double rY; 
	if (deviceWidth < deviceHeight) {
		rX = 8.27 / xInch;  // A4 용지의 크기: 8.27 X 11.69 inch 
		rY = 11.69 / yInch;
	} else {
		rX = 11.69 / xInch;  // A4 용지의 크기: 8.27 X 11.69 inch 
		rY = 8.27 / yInch;
	}
	int ratioX = (int)(10.0 * rX * (1200.0 / (double)dpiX));
	int ratioY = (int)(10.0 * rY * (1200.0 / (double)dpiY));

	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(ratioX*deviceWidth/zoomRatioX(),ratioY*deviceHeight/zoomRatioY());
	pDC->SetViewportExt(deviceWidth,deviceHeight);
	pDC->SetViewportOrg(0,0);
	CPoint minP(_minX,_minY);
	CPoint maxP(_maxX+_minX,_maxY+_minY);
	pDC->LPtoDP(&minP);
	pDC->LPtoDP(&maxP);
	_nOfRowsForPrint = maxP.y/deviceHeight+1;
	_nOfColsForPrint = maxP.x/deviceWidth+1;
	pInfo->SetMaxPage(_nOfRowsForPrint*_nOfColsForPrint);
}

void COODView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	setOriginX(_oldOriginX);
	setOriginY(_oldOriginY);
	_nOfRowsForPrint = 1;
	_nOfColsForPrint = 1;
	remakeAllRegions(GetDocument());
}

/////////////////////////////////////////////////////////////////////////////
// COODView diagnostics

#ifdef _DEBUG
void COODView::AssertValid() const
{
	CScrollView::AssertValid();
}

void COODView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

COODDoc* COODView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COODDoc)));
	return (COODDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COODView message handlers

BOOL COODView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int COODView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	setPopups();
	resetFontHeight();

	return 0;
}

void COODView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	COleClientItem *pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetActiveView() == this) {
		pActiveItem->Deactivate();
		m_pSelection = NULL;
	}

	hideGlobalDlgs();
	if (_forkTimerOn == TRUE) {
		killForkTimer();
	}	
	if (_forkPossibleFlag == TRUE) {
		clearForkPointAsX();
		_forkPossibleFlag = FALSE;
	}
	if (_editingTag) {
		editorFinished();
	}
	if (_whatNodeToDraw != -1 ||
		ktgF_connectionDrawing ||
		ktgF_simpleDrawing ||
		ktgF_simpleMoving ||
		ktgF_connectionStartDraw ||
		ktgF_connectionContinueDraw) {
		beep("Popup can't be active at the moment.");
		return;
	}
	CPoint testPoint(point);
	ScreenToClient(&testPoint);
	DPtoLP(testPoint);

	if (m_pSelection != NULL && m_pSelection->onEnter(this,testPoint.x,testPoint.y)) {
		if (ktgF_selectionMoving) {
			ktgF_selectionMoving = FALSE;
			m_pSelection->stopMove(this);
		}
		if (ktgF_selectionResizing) {
			ktgF_selectionResizing = FALSE;
			m_pSelection->stopResize(this);
		}
		SetClassLong(m_hWnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
		m_pSelection->popup(this,&point);

		ScreenToClient(&point);
		DPtoLP(point);
		_popupX = point.x;
		_popupY = point.y;
		return;
	} else if (m_pSelection != NULL) {
		CRect rect;
		m_pSelection->getClientRect(this,rect);
		InvalidateRect(&rect);
		m_pSelection = NULL;
	}

	Figure *oldFocus = _currentFocus;
	if (ktgF_traceEnter) {
		localTraceEnter(testPoint,figures(),TRUE);
	}
	if (_currentFocus != NIL) {
		if (_currentFocus->popupPointer() != NIL) {
			_currentFocus->popup(&point);
		} else if (_currentFocus->whoAreYou()->isIn(WEAREWIDEOBJECTS)) {
			if (_mainPopup == NIL) {
				beep("No popup is available.");
			} else {
				if (oldFocus != NIL) lowlight(oldFocus);
				_mainPopup->popup(this,&point);
			}
			_currentFocus = NIL;
		} else {
			beep("No popup is available.");
		}
	} else {
		if (_mainPopup == NIL) {
			beep("No popup is available.");
		} else {
			if (oldFocus != NIL) lowlight(oldFocus);
			_mainPopup->popup(this,&point);
		}
	}
	ScreenToClient(&point);
	DPtoLP(point);
	_popupX = point.x;
	_popupY = point.y;
}

void COODView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT box;
	GetClientRect(&box);
	CPoint point(box.right,box.bottom);
	DPtoLP(point);
	_width = point.x;
	_height = point.y;
	remakeCanvasRgn();
	if (figures() == NIL) return;
	remakeAllRegions(GetDocument());

	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

void COODView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pSender == NULL) return;
	if (!pSender->IsKindOf(RUNTIME_CLASS(COODView))) return;
}

CRgn* COODView::makeRectRegion(int x,int y,int w,int h)
{
	int x1 = x;
	int y1 = y;
	int x2 = x + w;
	int y2 = y + h;

	CRgn* tmp = new CRgn();
	tmp->CreateRectRgn(x1,y1,x2,y2);
	return tmp;
}

int COODView::rectInRegion(CRgn* region,int x,int y,int w,int h)
{
	CRect rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + w;
	rect.bottom = y + h;
	LPtoDP(rect);
	if (!region->RectInRegion(&rect)) return RectangleOut;
	CRgn* rect_region = makeRectRegion(x,y,x+w,y+h);
	CRgn* tmp = createRegion();
	tmp->CombineRgn(region,rect_region,RGN_AND);
	BOOL eq = rect_region->EqualRgn(tmp);
	delete rect_region;
	delete tmp;
	if (eq) {
		return RectangleIn;
	} else {
		return RectanglePart;
	}
}

BOOL COODView::checkInRegion(CRgn* someregion,XCoord &x1,YCoord &y1,XCoord &x2,YCoord &y2)
{
	if (someregion == NIL) return(FALSE);
	int ax = x1.get();  int bx = x2.get();
	int ay = y1.get();  int by = y2.get();
	int w = abs(ax - bx);
	int h = abs(ay - by);
	if (w == 0) w = 1;
	if (h == 0) h = 1;
	checkPoints(ax,ay,bx,by);
	if (rectInRegion(someregion,ax,ay,w,h) == RectangleOut) {
		return(FALSE);  // outside someregion
	} else {
		return(TRUE);   // inside someregion
	}
}

BOOL COODView::checkInRegion(CRgn* someregion,int x1,int y1,int x2,int y2)
{
	if (someregion == NIL) return(FALSE);
	int ax = x1;  int bx = x2;
	int ay = y1;  int by = y2;
	int w = abs(ax - bx);
	int h = abs(ay - by);
	if (w == 0) w = 1;
	if (h == 0) h = 1;
	checkPoints(ax,ay,bx,by);
	if (rectInRegion(someregion,ax,ay,w,h) == RectangleOut) {
		return(FALSE);  // outside someregion
	} else {
		return(TRUE);   // inside someregion
	}
}

CRgn* COODView::createPolygonRegion(LPPOINT points,int count)
{
	CRgn* tmp = new CRgn();
	tmp->CreatePolygonRgn(points,count,WINDING);
	return tmp;
}

void COODView::invalidateRect(CRect *pRect,BOOL flag)
{
	CPoint p1(pRect->left,pRect->top);
	CPoint p2(pRect->right,pRect->bottom);
	LPtoDP(p1);
	LPtoDP(p2);
	CRect theRect(p1.x,p1.y,p2.x,p2.y);
	InvalidateRect(&theRect,flag);
}

void COODView::LPtoDP(CRect &rect)
{
	if (zoomRatioX() == 100 && zoomRatioY() == 100) return;
	CDC *pDC = GetDC();
	int deviceWidth = pDC->GetDeviceCaps(HORZRES);
	int deviceHeight = pDC->GetDeviceCaps(VERTRES);
	int oldMapMode = pDC->SetMapMode(MM_ISOTROPIC);
	CSize oldWindowExt = pDC->SetWindowExt(100*deviceWidth/zoomRatioX(),100*deviceHeight/zoomRatioY());
	CSize oldViewportExt = pDC->SetViewportExt(deviceWidth,deviceHeight);
	CPoint oldViewportOrg = pDC->SetViewportOrg(0,0);
	pDC->LPtoDP(&rect);
	pDC->SetViewportOrg(oldViewportOrg);
	pDC->SetViewportExt(oldViewportExt);
	pDC->SetWindowExt(oldWindowExt);
	pDC->SetMapMode(oldMapMode);
	ReleaseDC(pDC);
}

void COODView::LPtoDP(CPoint &point)
{
	if (zoomRatioX() == 100 && zoomRatioY() == 100) return;
	CDC *pDC = GetDC();
	int deviceWidth = pDC->GetDeviceCaps(HORZRES);
	int deviceHeight = pDC->GetDeviceCaps(VERTRES);
	int oldMapMode = pDC->SetMapMode(MM_ISOTROPIC);
	CSize oldWindowExt = pDC->SetWindowExt(100*deviceWidth/zoomRatioX(),100*deviceHeight/zoomRatioY());
	CSize oldViewportExt = pDC->SetViewportExt(deviceWidth,deviceHeight);
	CPoint oldViewportOrg = pDC->SetViewportOrg(0,0);
	pDC->LPtoDP(&point);
	pDC->SetViewportOrg(oldViewportOrg);
	pDC->SetViewportExt(oldViewportExt);
	pDC->SetWindowExt(oldWindowExt);
	pDC->SetMapMode(oldMapMode);
	ReleaseDC(pDC);
}

void COODView::DPtoLP(CRect &rect)
{
	if (zoomRatioX() == 100 && zoomRatioY() == 100) return;
	CDC *pDC = GetDC();
	int deviceWidth = pDC->GetDeviceCaps(HORZRES);
	int deviceHeight = pDC->GetDeviceCaps(VERTRES);
	int oldMapMode = pDC->SetMapMode(MM_ISOTROPIC);
	CSize oldWindowExt = pDC->SetWindowExt(100*deviceWidth/zoomRatioX(),100*deviceHeight/zoomRatioY());
	CSize oldViewportExt = pDC->SetViewportExt(deviceWidth,deviceHeight);
	CPoint oldViewportOrg = pDC->SetViewportOrg(0,0);
	pDC->DPtoLP(&rect);
	pDC->SetViewportOrg(oldViewportOrg);
	pDC->SetViewportExt(oldViewportExt);
	pDC->SetWindowExt(oldWindowExt);
	pDC->SetMapMode(oldMapMode);
	ReleaseDC(pDC);
}

void COODView::DPtoLP(CPoint &point)
{
	if (zoomRatioX() == 100 && zoomRatioY() == 100) return;
	CDC *pDC = GetDC();
	int deviceWidth = pDC->GetDeviceCaps(HORZRES);
	int deviceHeight = pDC->GetDeviceCaps(VERTRES);
	int oldMapMode = pDC->SetMapMode(MM_ISOTROPIC);
	CSize oldWindowExt = pDC->SetWindowExt(100*deviceWidth/zoomRatioX(),100*deviceHeight/zoomRatioY());
	CSize oldViewportExt = pDC->SetViewportExt(deviceWidth,deviceHeight);
	CPoint oldViewportOrg = pDC->SetViewportOrg(0,0);
	pDC->DPtoLP(&point);
	pDC->SetViewportOrg(oldViewportOrg);
	pDC->SetViewportExt(oldViewportExt);
	pDC->SetWindowExt(oldWindowExt);
	pDC->SetMapMode(oldMapMode);
	ReleaseDC(pDC);
}

void COODView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnPrepareDC(pDC, pInfo);
	// TODO: Add your specialized code here and/or call the base class
	int deviceWidth = pDC->GetDeviceCaps(HORZRES);
	int deviceHeight = pDC->GetDeviceCaps(VERTRES);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(100*deviceWidth/zoomRatioX(),100*deviceHeight/zoomRatioY());
	pDC->SetViewportExt(deviceWidth,deviceHeight);
	pDC->SetViewportOrg(0,0);
	OldMode = R2_BLACK;
	OldGdi = NIL;
	CRect boundRect(0,0,_width,_height);
	switch(_drawingContext) {
	case KTG_DRAWING:
		OldPen = pDC->SelectObject(PlainPen);
		OldTextColor = pDC->SetTextColor(theAppPtr->textColor);
		OldBkColor = pDC->SetBkColor(theAppPtr->paperColor);
		OldBrush = pDC->SelectObject(PlainBrush);
		OldGdi = pDC->SelectStockObject(NULL_BRUSH);
		break;
	case KTG_FOCUSING:
		OldPen = pDC->SelectObject(PlainPen);
		OldTextColor = pDC->SetTextColor(theAppPtr->textColor);
		OldBkColor = pDC->SetBkColor(theAppPtr->paperColor);
		OldBrush = pDC->SelectObject(PlainBrush);
		OldGdi = pDC->SelectStockObject(BLACK_BRUSH);
		break;
	case KTG_HIGHLIGHTING:
		OldPen = pDC->SelectObject(HighlightPen);
		OldTextColor = pDC->SetTextColor(theAppPtr->textColor);
		OldBkColor = pDC->SetBkColor(theAppPtr->paperColor);
		OldBrush = pDC->SelectObject(HighlightBrush);
		OldGdi = pDC->SelectStockObject(NULL_BRUSH);
		break;
	case KTG_RUBBERBANDING:
		pDC->SetBoundsRect(&boundRect,DCB_ACCUMULATE|DCB_ENABLE);
		OldPen = pDC->SelectObject(RubberbandPen);
		OldTextColor = pDC->SetTextColor(theAppPtr->textColor);
		OldBkColor = pDC->SetBkColor(theAppPtr->paperColor);
		OldBrush = pDC->SelectObject(RubberbandBrush);
		OldMode = pDC->SetROP2(R2_NOTXORPEN);
		OldGdi = pDC->SelectStockObject(NULL_BRUSH);
		break;
	case KTG_ERASING:
		pDC->SetBoundsRect(&boundRect,DCB_ACCUMULATE|DCB_ENABLE);
		OldPen = pDC->SelectObject(ErasePen);
		OldBrush = pDC->SelectObject(EraseBrush);
		OldGdi = pDC->SelectStockObject(NULL_BRUSH);
		break;
	default:
		break;
	}
}

void COODView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	hideGlobalDlgs();

	CPoint orgPoint(point);
	DPtoLP(point);

	if (_forkTimerOn == TRUE) {
		killForkTimer();
	}
	if (_forkPossibleFlag == TRUE) {
		clearForkPointAsX();
		startFork();
		CScrollView::OnLButtonDown(nFlags, orgPoint);
		return;
	}
	_atFirstMove = FALSE;
	_atFirstResize = FALSE;
	_editPossibleOnLBUp = FALSE;
	if (_editingTag) {
		BOOL ok = editorFinished();
		if (ok == FALSE) {
			CScrollView::OnLButtonDown(nFlags, orgPoint);
			return;
		}
	}

	COleClientItem *pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetActiveView() == this) {
		pActiveItem->Deactivate();
		m_pSelection = NULL;
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	}

	if (m_pSelection != NULL) { 
		m_pSelection->trackMouse(this,point);
		if (m_pSelection->resizePoint() != 0) {
			if (m_pSelection->resizePoint() == AT_MOVE) {
				ktgF_selectionMoving = TRUE;
				CScrollView::OnLButtonDown(nFlags, point);
				return;
			}
			m_pSelection->saveOriginXY(this);
			ktgF_selectionResizing = TRUE;
			CScrollView::OnLButtonDown(nFlags, point);
			return;
		}
	}
	COODDoc *pDoc = GetDocument();
	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL && selection->onEnter(this,point.x,point.y)) {
			if (m_pSelection != NULL && m_pSelection != selection) {
				CRect rect;
				m_pSelection->getClientRect(this,rect);
				InvalidateRect(&rect);
			}
			m_pSelection = selection;
			CDC *pDC = GetDC();
			setDrawingContext(KTG_FOCUSING);
			OnPrepareDC(pDC);
			m_pSelection->drawAsSelected(this,pDC);
			OODReleaseDC(pDC,TRUE);
			if (_currentFocus != NULL) {
				eraseDots(_currentFocus);
				_currentFocus = NIL;
			}
			m_pSelection->trackMouse(this,point);
			if ( m_pSelection->resizePoint() != 0) {
				if (m_pSelection->resizePoint() == AT_MOVE &&
					_theBucket->hasSelection(m_pSelection)) {
					_atFirstMove = TRUE;
					_currentFocus = _theBucket;
					m_pSelection = NULL;
					_currentX = point.x;
					_currentY = point.y;
					CScrollView::OnLButtonDown(nFlags, point);
					return;
				} else if (m_pSelection->resizePoint() == AT_MOVE) {
					ktgF_selectionMoving = TRUE;
					CScrollView::OnLButtonDown(nFlags, point);
					return;
				}
				m_pSelection->saveOriginXY(this);
				ktgF_selectionResizing = TRUE;
			}
			CScrollView::OnLButtonDown(nFlags, point);
			return;
		}
	}
	if (m_pSelection != NULL) {
		CRect rect;
		m_pSelection->getClientRect(this,rect);
		InvalidateRect(&rect);
		m_pSelection = NULL;
	}

	_currentX = point.x;
	_currentY = point.y;
	Figure *oldFocus = _currentFocus;
	if (_currentFocus != NIL) {
		BOOL wantResize = _currentFocus->wantToResize(_currentX,_currentY);
		if (wantResize && 
			_currentFocus->whoAreYou()->equals(IAMNOTE) &&
			_currentFocus->focus() != NIL &&
			_currentFocus->focus()->whoAreYou()->equals(IAMANCHOR)) {
			_currentFocus = _currentFocus->focus();
			draw(_currentFocus);
			((Anchor *)_currentFocus)->wantToResizeExact(_currentX,_currentY);
			SetCapture();
			ktgF_traceEnter = FALSE;
			ktgF_simpleDrawing = TRUE;
			CScrollView::OnLButtonDown(nFlags, orgPoint);
			return;
		} else if (wantResize) {
			_atFirstResize = TRUE;
			eraseDots(_currentFocus);

			eraseDots(_theBucket);
			_theBucket->clearList();
			CScrollView::OnLButtonDown(nFlags, orgPoint);
			return;
		}
		eraseDots(_currentFocus);
		_currentFocus = NIL;
	}
	if (ktgF_traceEnter) {
		localTraceEnter(point,figures(),TRUE);
	}
    if (_whatTionToDraw == KTG_BOX && _currentFocus == NIL) {  // 2014 danger
        _currentFocus = new Box(this,point.x,point.y,NULL);
        ((Box *)_currentFocus)->setFollowing2(point.x,point.y);
	    draw(_currentFocus);
		SetCapture();
		ktgF_traceEnter = FALSE;
		ktgF_simpleDrawing = TRUE;
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	}
    if (_whatTionToDraw == KTG_CIRCLE && _currentFocus == NIL) {  // 2014 danger
        _currentFocus = new Circle(this,point.x,point.y,NULL);
        ((Circle *)_currentFocus)->setFollowing2(point.x,point.y);
	    draw(_currentFocus);
		SetCapture();
		ktgF_traceEnter = FALSE;
		ktgF_simpleDrawing = TRUE;
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	}
    if (_whatTionToDraw == KTG_ROUNDBOXA && _currentFocus == NIL) {  // 2014 danger
        _currentFocus = new RoundBoxA(this,point.x,point.y,NULL);
        ((RoundBoxA *)_currentFocus)->setFollowing2(point.x,point.y);
	    draw(_currentFocus);
		SetCapture();
		ktgF_traceEnter = FALSE;
		ktgF_simpleDrawing = TRUE;
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	}
	if (_whatTionToDraw == KTG_ANCHOR) {
		releaseModelTBButton(ID_TB_ANCHOR);
		if (_currentFocus == NIL) { 
//			InfoMsg("Please drag from a note.");
//			_whatTionToDraw = -1;
			_currentFocus = new Line(this,point.x,point.y,theAppPtr->theLinePopup,ORDINARY);
			((Line *)_currentFocus)->style() = DOTED;
			((Line *)_currentFocus)->head() = HEADARROW2;
			((Line *)_currentFocus)->setFollowing2(point.x,point.y);
			draw(_currentFocus);
			SetCapture();
			ktgF_traceEnter = FALSE;
			ktgF_simpleDrawing = TRUE;
			CScrollView::OnLButtonDown(nFlags, point);
			return;
		} else if (_currentFocus->whoAreYou()->equals(IAMNOTE) == FALSE) {
//			InfoMsg("Please drag from a note.");
//			_whatTionToDraw = -1;
			_currentFocus = new Line(this,point.x,point.y,theAppPtr->theLinePopup,ORDINARY);
			((Line *)_currentFocus)->style() = DOTED;
			((Line *)_currentFocus)->head() = HEADARROW2;
			((Line *)_currentFocus)->setFollowing2(point.x,point.y);
			draw(_currentFocus);
			SetCapture();
			ktgF_traceEnter = FALSE;
			ktgF_simpleDrawing = TRUE;
			CScrollView::OnLButtonDown(nFlags, point);
			return;
		} else {
			Note *fromNote = (Note *)_currentFocus;
			int cx = 0; int cy = 0;
			fromNote->center(cx,cy);
			_currentFocus = new Anchor(this,fromNote,cx,cy,_currentX,_currentY,NIL);
			fromNote->addAnchor((Anchor *)_currentFocus);
			draw(_currentFocus);
			((Anchor *)_currentFocus)->wantToResizeExact(_currentX,_currentY);
			SetCapture();
			ktgF_traceEnter = FALSE;
			ktgF_simpleDrawing = TRUE;
			CScrollView::OnLButtonDown(nFlags, orgPoint);
			return;
		}
	}
	if (_currentFocus != NIL) {
		if (oldFocus == _currentFocus &&
			_currentFocus->whoAreYou()->equals(IAMNOTE) &&
			_currentFocus->focus() != NIL &&
			_currentFocus->focus()->whoAreYou()->equals(IAMANCHOR)) {
			_editPossibleOnLBUp = FALSE;
		} else if (oldFocus == _currentFocus && 
			oldFocus->whoAreYou()->isIn(WEAREEDITABLEOBJECTS)) {
			_editPossibleOnLBUp = TRUE;
		}
		if (_currentFocus->whoAreYou()->isIn(WEARECONNECTIONS) &&
			_currentFocus->focus() != NIL &&
			_currentFocus->focus()->whoAreYou()->isIn(WEARETEXTOBJECTS)) {
			_currentFocus = _currentFocus->focus();
			if (_currentFocus == oldFocus) {
				_editPossibleOnLBUp = TRUE;
			}
		} else if (_currentFocus->whoAreYou()->equals(IAMCOLLABORATIONOBJECT) &&
			_currentFocus->focus() != NIL &&
			_currentFocus->focus()->whoAreYou()->equals(IAMCOLOBJMESSAGETEXT)) {
			_currentFocus = _currentFocus->focus();
			if (_currentFocus == oldFocus) {
				_editPossibleOnLBUp = TRUE;
			}
		}
		if (_currentFocus->wantToMove(_currentX,_currentY)) {
			_atFirstMove = TRUE;
			if (_theBucket->hasFigure(_currentFocus)) {
				_currentFocus = _theBucket;
			}
		} else if (_currentFocus->whoAreYou()->equals(IAMQUALIFICATIONTEXT) == FALSE) {
			_atFirstMove = FALSE;
			_currentFocus = _currentFocus->container();

			eraseDots(_theBucket);
			_theBucket->clearList();
		}
		drawDots(_currentFocus);
	} else {
		_atFirstResize = TRUE;
		eraseDots(_theBucket);
		_theBucket->clearList();
		_theBucket->setCoord(point.x,point.y,point.x,point.y);
	}
	CScrollView::OnLButtonDown(nFlags, orgPoint);
}

void COODView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint orgPoint(point);
	DPtoLP(point);
	
	if (m_pSelection != NULL && ktgF_selectionResizing) {
		Invalidate();
		ktgF_selectionResizing = FALSE;
		GetDocument()->setModifiedFlag();
		m_pSelection->stopResize(this);
		CScrollView::OnLButtonUp(nFlags, orgPoint);
		return;
	} else if (m_pSelection != NULL && ktgF_selectionMoving) {
		Invalidate();
		ktgF_selectionMoving = FALSE;
		GetDocument()->setModifiedFlag();
		m_pSelection->stopMove(this);
		SetClassLong(m_hWnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
		CScrollView::OnLButtonUp(nFlags, orgPoint);
		return;
	}
	
	_atFirstMove = FALSE;
	if (_atFirstResize == TRUE && _currentFocus != NULL) {
		_currentFocus->epilog();
	}
	_atFirstResize = FALSE;
	_editorJustStarted = FALSE;
	if (ktgF_simpleMoving && _currentFocus != NIL) {
		stopMove();
		SetClassLong(m_hWnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
		ReleaseCapture();
		ktgF_simpleMoving = FALSE;
		ktgF_traceEnter = TRUE;
	} else if (ktgF_simpleDrawing && _currentFocus != NIL) {
		stopDraw();
		ReleaseCapture();
		ktgF_simpleDrawing = FALSE;
		ktgF_traceEnter = TRUE;
	} else if (_currentFocus != NIL &&
			_editPossibleOnLBUp &&
			_currentFocus->whoAreYou()->isIn(WEAREEDITABLEOBJECTS)) {
		_editorJustStarted = TRUE;
		_editPossibleOnLBUp = FALSE;
		startEditor(point);
		CScrollView::OnLButtonUp(nFlags, orgPoint);
		return;
	} else if (_currentFocus != NIL &&
			_editPossibleOnLBUp &&
			_currentFocus->whoAreYou()->isIn(WEARETEXTOBJECTS)) {
		_editorJustStarted = TRUE;
		_editPossibleOnLBUp = FALSE;
		startEditor(point);
		CScrollView::OnLButtonUp(nFlags, orgPoint);
		return;
	}
	if (_currentFocus != NIL &&
		_currentFocus->whoAreYou()->isIn(WEAREFORKABLELINES) == TRUE) {
		_forkTimerOn = TRUE;
		SetTimer(FORK_TIMER,1000,NULL);
	} else if (_currentFocus != NIL && figures()->inList(_currentFocus)) {
		drawDots(_currentFocus);
	}
	if (_currentFocus == NIL) {
		userMsg("Ready");
	}
	CScrollView::OnLButtonUp(nFlags, orgPoint);
}

void COODView::setPositionOnStatusBar(int x,int y)
{
	if (!GetDocument()->IsInPlaceActive()) {
		mainFramePtr->setPositionOnStatusBar(x,y);
	} else if (GetDocument()->getInPlaceFrame() != NIL) {
		GetDocument()->getInPlaceFrame()->setPositionOnStatusBar(x,y);
	}
}

void COODView::userMsg(const char*s)
{
	if (!GetDocument()->IsInPlaceActive()) {
		mainFramePtr->userMsg(s);
	} else if (GetDocument()->getInPlaceFrame() != NIL) {
		GetDocument()->getInPlaceFrame()->userMsg(s);
	}
}

void COODView::userMsg(const char*s,int n)
{
	if (!GetDocument()->IsInPlaceActive()) {
		mainFramePtr->userMsg(s,n);
	} else if (GetDocument()->getInPlaceFrame() != NIL) {
		GetDocument()->getInPlaceFrame()->userMsg(s,n);
	}
}

void COODView::userMsgForUsingUpperCaseAsBlank(char *s1,char *s2)
{
	if (!GetDocument()->IsInPlaceActive()) {
		mainFramePtr->userMsgForUsingUpperCaseAsBlank(s1,s2);
	} else if (GetDocument()->getInPlaceFrame() != NIL) {
		GetDocument()->getInPlaceFrame()->userMsgForUsingUpperCaseAsBlank(s1,s2);
	}
}

void COODView::beep(const char *s)
{
	userMsg(s);
	Beep(1000,1000);
}

void COODView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint orgPoint(point);
	DPtoLP(point);
	setPositionOnStatusBar(point.x,point.y);

	if (_forkTimerOn == TRUE) {
		killForkTimer();
	}

	if (_currentX == point.x && _currentY == point.y) {
		CScrollView::OnMouseMove(nFlags, orgPoint);
		return;
	}

	if (m_pSelection != NULL) {
		if (ktgF_selectionResizing) {
			m_pSelection->resizing(this,point);
			return;
		} else if (ktgF_selectionMoving) {
			m_pSelection->moving(this,point);
			return;
		}
		m_pSelection->trackMouse(this,point);
	}

	if (_currentFocus == NIL && _atFirstResize == FALSE) {
		CScrollView::OnMouseMove(nFlags, orgPoint);
		return;
	}
	if (_atFirstMove) {
		startMove();
		/* 다음 아래 명령어 위치는 매우 중요함. 위로 옮기지 마라. */
		/* 관계되는 함수 : Line::fillBgArrow */
		_atFirstMove = FALSE;
		SetCapture();
		ktgF_traceEnter = FALSE;
		ktgF_simpleMoving = TRUE;
	} else if (_atFirstResize) {
		_atFirstResize = FALSE;
		if (_currentFocus == NIL) _currentFocus = _theBucket;
		startResize();
		SetCapture();
		ktgF_traceEnter = FALSE;
		ktgF_simpleDrawing = TRUE;
	}
	if (ktgF_simpleMoving) {
		movingHandler(point);
	} else if (ktgF_simpleDrawing) {
		drawingHandler(point,_currentFocus);
	} else if (_editingTag == FALSE &&
		_currentFocus->whoAreYou()->isIn(WEAREFORKABLELINES) == TRUE) {
		_forkTimerOn = TRUE;
		SetTimer(FORK_TIMER,1000,NULL);
	}
	CScrollView::OnMouseMove(nFlags, orgPoint);
}

void COODView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint orgPoint(point);
	if (_enable == FALSE) {
		CScrollView::OnLButtonDblClk(nFlags, orgPoint);
		return;
	}
	DPtoLP(point);
	if (_forkTimerOn == TRUE) {
		killForkTimer();
	}
	if (m_pSelection != NULL &&
		ktgF_selectionMoving == FALSE && 
		ktgF_selectionResizing == FALSE) {
		editorFinished();
		_editPossibleOnLBUp = FALSE;
		SetClassLong(m_hWnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
		m_pSelection->Activate(OLEIVERB_SHOW,this);
	} if (_editorJustStarted == FALSE && 
		_editingTag) {
		editorFinished();
		startEditor(point);
		_editPossibleOnLBUp = FALSE;
	} else if (_editorJustStarted == FALSE && 
		_editingTag == FALSE) {
		startEditor(point);
		_editPossibleOnLBUp = FALSE;
	}
	_editorJustStarted = FALSE;
	CScrollView::OnLButtonDblClk(nFlags, orgPoint);
}

void COODView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (ktgF_processKeys && _currentFocus != NIL) {
		Text *currentText = (Text *)_currentFocus->focus();
		switch (nChar) {
		case VK_CONTROL :
			_ctrlKeyPressed = TRUE;
			break;
		case VK_ESCAPE :
			editorFinished();
			break;
		case VK_HOME :
			if (currentText != NIL) currentText->goHome();
			break;
		case VK_END :
			if (currentText != NIL) currentText->goEnd();
			break;
		case VK_UP :
			if (currentText != NIL) currentText->goUp();
			break;
		case VK_DOWN :
			if (currentText != NIL) currentText->goDown();
			break;
		case VK_LEFT :
			if (currentText != NIL) currentText->goLeft();
			break;
		case VK_RIGHT :
			if (currentText != NIL) currentText->goRight();
			break;
		case VK_DELETE :
			if (currentText != NIL) currentText->delChar();
			break;
		case VK_TAB :
			if (currentText != NIL)  {
				currentText->insert(" ");
				currentText->insert(" ");
				currentText->insert(" ");
			}
			break;
		case VK_BACK :
			if (_ctrlKeyPressed == FALSE) {
				if (currentText != NIL) currentText->delCharBack();
			} else {
				if (currentText != NIL) currentText->delLine();
			}
			break;
		case VK_RETURN : 
			if (currentText != NIL)  {
				if (currentText->whoAreYou()->isIn(WEAREONELINETEXTS)) {
					GetDocument()->setModifiedFlag(); 
					currentText->bye();
					_editingTag = FALSE;
					ktgF_processKeys = FALSE;
					if (currentText->container() == _currentFocus) {
						_currentFocus->resetOneLineTextIfObsolete(currentText);
						_currentFocus->recalcWidthHeight();
						_currentFocus->makeRegion(_canvasRgn);
						draw(_currentFocus);
					}
					addExcludeRectForBottomObjects(_currentFocus,figures());
					figures()->insert(_currentFocus);
					_currentFocus = NIL;
				} else {
					currentText->goNextLine();
				}
			}
			break;
		}
	} else if (ktgF_traceEnter) {
		if (VK_DELETE == nChar) {
			if (m_pSelection != NULL) {
				if (ktgF_selectionMoving == FALSE && ktgF_selectionResizing == FALSE) {
					deleteSelectedObject();
					CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
					return;
				}
			}
			if (_forkPossibleFlag) {
				clearForkPointAsX();
			}
			deleteCurrentFigure();
		} else if (VK_ESCAPE == nChar &&
			_currentConnection != NIL) {
			if (ktgF_connectionDrawing ||
				ktgF_connectionContinueDraw) {
				BOOL abortAll = _currentConnection->abortDraw(FALSE);
				if (abortAll) {
					delete _currentConnection;
					_currentConnection = NIL;
					Invalidate();
				} else {
					insert(_currentConnection);
				}
				ktgF_connectionContinueDraw = FALSE;
				drawingEpilog();
				ReleaseCapture();
			}
		}
	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void COODView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (ktgF_processKeys) {
		if (nChar == VK_CONTROL) _ctrlKeyPressed = FALSE;
	}
	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void COODView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (ktgF_processKeys) {
		if (_ctrlKeyPressed) return;
		if (nChar == VK_RETURN) return;
		if (nChar == VK_BACK) return;
		if (nChar == VK_TAB) return;
		// 주의 : VK_UP 과 같은 문자는 키보드 상의 
		// 어떠한 문자들(%&) 등과 겹치기 때문에 체크하면 안됨
		processKeys(nChar);
	}
	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}
void COODView::setFontInfo(CFontDialog *pFontDlg)
{
	_fontInfo->setFontInfo(pFontDlg);
	resetFontHeight();
}

void COODView::OnToolsFont() 
{
	// TODO: Add your command handler code here
	CFont font;
	font.CreateFont(_fontInfo->size+5,0,0,0,
		_fontInfo->weight,_fontInfo->italicFlag,
		_fontInfo->underlineFlag,_fontInfo->strikeOutFlag,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,_fontInfo->faceName);
	LOGFONT currentLogFont;
	int succ = font.GetLogFont(&currentLogFont);
	LOGFONT *logFontPtr = NIL;
	if (succ != 0) {
		logFontPtr = &currentLogFont; 
	}
	CFontDialog fontDlg(logFontPtr);
	UINT ok = fontDlg.DoModal();
	if (ok == IDOK) {
		_fontInfo->setFontInfo(&fontDlg);
		resetFontHeight();
		if (!GetDocument()->IsInPlaceActive()) {
			mainFramePtr->setFontInfoForAllViews(&fontDlg);
		}
	}
}

void COODView::OnDeleteFigure()
{
	if (_currentFocus == NIL) {
		beep("Error : No focus.");
		return;
	}
	deleteCurrentFigure();
}

void COODView::OnEditRoleName()
{
	if (_currentFocus == NIL) {
		beep("COODView::OnEditRoleName()");
		return;
	}
	UnsignedLong *id = _currentFocus->whoAreYou();
	if (id->equals(IAMAGGREGATION) == FALSE &&
		id->equals(IAMDEPENDENCY) == FALSE &&
		id->equals(IAMASSOCIATION) == FALSE &&
		id->equals(IAMCOMMUNICATION) == FALSE) {
		beep("COODView::OnEditRoleName()");
		return;
	}
	lowlight(_currentFocus);
	_editingTag = TRUE;
	Connection * thisConnection = (Connection *)_currentFocus;
	OneLineText *aText = thisConnection->selectOrCreateRoleName(_popupX,_popupY);
	if (aText == NIL) {
		_editingTag = FALSE;
		return;
	}
	figures()->remove(_currentFocus);
	checkInList(_currentFocus);
	aText->startEdit();
	ktgF_processKeys = TRUE;
}

void COODView::OnPopupEdit()
{
	if (_currentFocus == NIL) {
		beep("Error : No focus.");
		return;
	}
	CPoint point(_popupX,_popupY);
	startEditor(point);
}

void COODView::OnZoom()
{
	CString value = _T("100");
	if (!GetDocument()->IsInPlaceActive()) {
		mainFramePtr->getZoomValue(value);
	} else if (GetDocument()->getInPlaceFrame() != NIL) {
		GetDocument()->getInPlaceFrame()->getZoomValue(value);
	}
	GetDocument()->setModifiedFlag();
	if (value.CompareNoCase("auto") == 0) {
		if (figures()->nOfList() == 0) {
			return;
		}
		resetMinMaxXY();
		Figure *ptr = figures()->getFirst();
		while(ptr != NIL) {
			ptr->setInCanvas(TRUE);
			ptr->minMaxXY();
			ptr = figures()->getNext();
		}
		CDC *pDC = GetDC();
		int deviceWidth = pDC->GetDeviceCaps(HORZRES);
		int deviceHeight = pDC->GetDeviceCaps(VERTRES);
		int oldMapMode = pDC->SetMapMode(MM_ISOTROPIC);
		CSize oldWindowExt = pDC->SetWindowExt(100*deviceWidth/zoomRatioX(),100*deviceHeight/zoomRatioY());
		CSize oldViewportExt = pDC->SetViewportExt(deviceWidth,deviceHeight);
		CPoint oldViewportOrg = pDC->SetViewportOrg(0,0);
		CPoint minP(_minX,_minY);
		CPoint maxP(_maxX+_minX,_maxY+_minY);
		pDC->LPtoDP(&maxP);

		RECT box;
		GetClientRect(&box);
		CPoint viewSize(box.right,box.bottom);
		pDC->DPtoLP(&viewSize);
		pDC->SetViewportOrg(oldViewportOrg);
		pDC->SetViewportExt(oldViewportExt);
		pDC->SetWindowExt(oldWindowExt);
		pDC->SetMapMode(oldMapMode);
		ReleaseDC(pDC);

		double xRatio = ((double)maxP.x)/((double)viewSize.x);
		if (xRatio < 1.0) {
			setZoomRatioX(100);
		} else {
			setZoomRatioX((int)(100.0/xRatio));
		}
		double yRatio = ((double)maxP.y)/((double)viewSize.y);
		if (yRatio < 1.0) {
			setZoomRatioY(100);
		} else {
			setZoomRatioY((int)(100.0/yRatio));
		}
	} else {
		int count = value.GetLength();
		for(int i = 0; i < count; i++) {
			if (value[i] < '0' || value[i] > '9') {
				WarningMsg("Invalid zoom rate");
				return;
			}
		}
		int zoomRatio = atoi(value);
		if (zoomRatio > 200) {
			WarningMsg("Too big size");
			return;
		}
		if (zoomRatio < 10) {
			WarningMsg("Too small size");
			return;
		}
		setZoomRatioX(zoomRatio);
		setZoomRatioY(zoomRatio);
	}
	RECT box;
	GetClientRect(&box);
	CPoint point(box.right,box.bottom);
	DPtoLP(point);
	_width = point.x;
	_height = point.y;
	remakeCanvasRgn();
	remakeAllRegions(GetDocument());
	Invalidate();
}

void COODView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent) {
	case FORK_TIMER :
		KillTimer(FORK_TIMER);
		_forkTimerOn = FALSE;
		_forkPossibleFlag = findForkPoint();
		break;
	}
	CScrollView::OnTimer(nIDEvent);
}

void COODView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (bActivate) {
	} else {
		_whatNodeToDraw = -1;
		undoIfSomeButtonAlreadyPressed(-1);
	}
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void COODView::OnKillFocus(CWnd* pNewWnd) 
{
	CScrollView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	_whatNodeToDraw = -1;
	undoIfSomeButtonAlreadyPressed(-1);
	Invalidate();
}

void COODView::OnTbArrow() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_ARROW);
	if (itsMe) return;
	_whatNodeToDraw = -1;
	pressModelTBButton(ID_TB_ARROW);					
}

void COODView::OnTbAlphabet() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_ALPHABET);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_ALPHABET;
	pressModelTBButton(ID_TB_ALPHABET);					
}

void COODView::OnTbNote() 
{
	// TODO: Add your command handler code here
	
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_NOTE);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_NOTE;
	pressModelTBButton(ID_TB_NOTE);					
}

void COODView::OnCreateNote()
{
	Note *aNote = new Note(this,_popupX,_popupY,_fontHeight,NIL);
	aNote->setFocus();
	BOOL ok = aNote->startEdit();
	if (ok == FALSE) {
		beep("COODView::OnCreateNote()");
		delete aNote;
		return;
	}
	draw(aNote);
	_currentFocus = (Figure *)aNote;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void COODView::OnCreateActor()
{
	Actor *anActor = new Actor(this,_popupX,_popupY,NIL);
	BOOL ok = anActor->startEdit();
	if (ok == FALSE) {
		beep("COODView::OnCreateActor()");
		delete anActor;
		return;
	}
	draw(anActor);
	_currentFocus = (Figure *)anActor;
	_editingTag = TRUE;
	ktgF_processKeys = TRUE;
}

void COODView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	COODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here 
	int dpiX = pDC->GetDeviceCaps(LOGPIXELSX);  
	int dpiY = pDC->GetDeviceCaps(LOGPIXELSY);  
	int deviceWidth = pDC->GetDeviceCaps(HORZRES); // 스크린 상의 x 픽셀 수
	int deviceHeight = pDC->GetDeviceCaps(VERTRES); // 스크린 상의 y 픽셀 수
	double xInch = (double)deviceWidth/(double)dpiX;
	double yInch = (double)deviceHeight/(double)dpiY;
    double rX; 
	double rY; 
	if (deviceWidth < deviceHeight) {
		rX = 8.27 / xInch;  // A4 용지의 크기: 8.27 X 11.69 inch 
		rY = 11.69 / yInch;
	} else {
		rX = 11.69 / xInch;  // A4 용지의 크기: 8.27 X 11.69 inch 
		rY = 8.27 / yInch;
	}
	int ratioX = (int)(10.0 * rX * (1200.0 / (double)dpiX));
	int ratioY = (int)(10.0 * rY * (1200.0 / (double)dpiY));

	pDC->SetMapMode(MM_ISOTROPIC);
	// 아래 값에서 10 보다 작은 경우에는 이미지가 크게 나옴
	pDC->SetWindowExt(ratioX*deviceWidth/zoomRatioX(),ratioY*deviceHeight/zoomRatioY());
	pDC->SetViewportExt(deviceWidth,deviceHeight);
	int nCurPage = pInfo->m_nCurPage-1;
	int rowIndex = nCurPage/_nOfColsForPrint;
	int colIndex = nCurPage - rowIndex*_nOfColsForPrint;

	CPoint oldViewportOrg =	pDC->SetViewportOrg(-colIndex*deviceWidth,-rowIndex*deviceHeight);

	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		selection->setInCanvas(true);
		if (selection != NULL) selection->draw(this,pDC);
	}

	FigureList *figs = figures();
	Figure *ptr = figs->getFirst();
	while(ptr != NIL) {
		ptr->setInCanvas();
		ptr = figs->getNext();
	}
	ptr = figs->getFirst();
	while(ptr != NIL) {
		ptr->setInCanvas();
		if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS) == TRUE) {
			ptr->draw(pDC);
		}
		ptr = figs->getNext();
	}
	ptr = figs->getFirst();
	while(ptr != NIL) {
		if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS) == FALSE) {
			ptr->draw(pDC);
		}
		ptr = figs->getNext();
	}

	CRect oldRect;
// 2014 OODesigner 수정 				pDC->GetClipBox(&oldRect);
// 2014 OODesigner 수정 				pDC->Rectangle(&oldRect);

	pDC->SetViewportOrg(oldViewportOrg);
}

void COODView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnEndPrintPreview(pDC, pInfo, point, pView);
	CFrameWnd *theFrame = GetParentFrame();
	if (theFrame == NIL) return;
	ASSERT_VALID(theFrame);
	if (!theFrame->IsKindOf(RUNTIME_CLASS(CChildFrm))) return;
	CChildFrm *pChildFrame = (CChildFrm *)theFrame;
	mainFramePtr->showControlBarJustFor(pChildFrame->diagramType(),pChildFrame->getModelToolBar());
}

void COODView::OnTbAnchor() 
{
	// TODO: Add your command handler code here
	
	_whatNodeToDraw = -1;
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_ANCHOR);
	if (itsMe) return;
	_whatTionToDraw = KTG_ANCHOR;
	pressModelTBButton(ID_TB_ANCHOR);					
}

BOOL COODView::IsSelected(const CObject* pDocItem) const
{
	// TODO: Add your specialized code here and/or call the base class
	return pDocItem == m_pSelection;
//	return CScrollView::IsSelected(pDocItem);
}

void COODView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL && pActiveItem->GetActiveView() == this) {
		pActiveItem->Deactivate();
		ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
	}
}

void COODView::OnInsertObject() 
{
	// TODO: Add your command handler code here
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CContainerCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;
	ObjectPositionDlg posDlg;
	if (posDlg.DoModal() != IDOK)
		return;

	int x1 = posDlg.m_x;
	int y1 = posDlg.m_y;
	int x2 = x1 + posDlg.m_width;
	int y2 = y1 + posDlg.m_height;
	int w = x2 - x1;
	int h = y2 - y1;
	if (x1 < 0) {
		x1 = 0;
		x2 = x1 + w;
	}
	if (y1 < 0) {
		y1 = 0;
		y2 = y1 + h;
	}
	if (x1 >= _width) {
		x1 = _width - w;
		x2 = x1 + w;
	}
	if (y1 >= _height) {
		y1 = _height - h;
		y2 = y1 + h;
	}

	BeginWaitCursor();

	COODCntrlItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		COODDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new COODCntrlItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);
		pItem->setCoord(x1+originX(),y1+originY(),x2+originX(),y2+originY());
		pItem->setController(this,viewTitle);
		pItem->makeRegion(this);
		if (!pItem->IsInPlaceActive()) {
			CFrameWnd *theFrame = GetParentFrame();
			ASSERT_VALID(theFrame);
			if (theFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) 
					((CMDIChildWnd *)theFrame)->MDIActivate();
		}

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();	
}

void COODView::OnObjectEdit() 
{
	// TODO: Add your command handler code here
	
	GetDocument()->setModifiedFlag();
	if (m_pSelection != NULL) 
		m_pSelection->Activate(OLEIVERB_SHOW,this);
}

void COODView::OnObjectOpen() 
{
	// TODO: Add your command handler code here
	
	GetDocument()->setModifiedFlag();
	if (m_pSelection != NULL) 
		m_pSelection->Activate(OLEIVERB_OPEN,this);
}

void COODView::OnEditCut() 
{
	// TODO: Add your command handler code here
	// 이 코드는 복사 경우와 똑같으니깐 upgrade 시 주의 할 것 
	GetDocument()->setModifiedFlag();
	if (m_pSelection != NULL) {
		m_pSelection->CopyToClipboard(m_pSelection->CanPasteLink());
		deleteSelectedObject();
	} else if (_currentFocus != NIL && 
		_currentFocus->whoAreYou()->isIn(WEARECLIPBOARDOBJECTS) &&
		_editingTag == FALSE) {
		CSharedFile file;
		CArchive ar(&file,CArchive::store);
		FigureList aList;
		aList.insert(_currentFocus);
		aList.Serialize(ar);
		ar.Close();

		COleDataSource *pDataSource = NULL;
		TRY {
			pDataSource = new COleDataSource;
			pDataSource->CacheGlobalData(OODClipFormat,file.Detach());
			pDataSource->SetClipboard();
		} CATCH_ALL(e) {
			delete pDataSource;
			THROW_LAST();
		}
		END_CATCH_ALL
		deleteCurrentFigure();
	}
}

void COODView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	// 이 코드는 자르기 경우와 똑같으니깐 upgrade 시 주의 할 것 
	GetDocument()->setModifiedFlag();
	if (m_pSelection != NULL) {
		m_pSelection->CopyToClipboard(m_pSelection->CanPasteLink());
	} else if (_currentFocus != NIL && 
		_currentFocus->whoAreYou()->isIn(WEARECLIPBOARDOBJECTS) &&
		_editingTag == FALSE) {
		CSharedFile file;
		CArchive ar(&file,CArchive::store);
		FigureList aList;
		aList.insert(_currentFocus);
		aList.Serialize(ar);
		ar.Close();

		COleDataSource *pDataSource = NULL;
		TRY {
			pDataSource = new COleDataSource;
			pDataSource->CacheGlobalData(OODClipFormat,file.Detach());
			pDataSource->SetClipboard();
		} CATCH_ALL(e) {
			delete pDataSource;
			THROW_LAST();
		}
		END_CATCH_ALL
	}
}

void COODView::OnPopupEditPaste()
{
	COleDataObject dataObject;
	dataObject.AttachClipboard();

	if (dataObject.IsDataAvailable(OODClipFormat)) {
		// OODesigner의 그림 객체 경우
		CFile* pFile = dataObject.GetFileData(OODClipFormat);
		if (pFile != NULL) {

			Figure *newFigure;
			// connect the file to the archive
			CArchive ar(pFile, CArchive::load);
			TRY	{
				ar.m_pDocument = GetDocument(); // set back-pointer in archive

				// read the selection
				FigureList aList;
				aList.Serialize(ar);
				newFigure = aList.getFirst();
			} CATCH_ALL(e) {
				ar.Close();
				delete pFile;
				THROW_LAST();
			}
			END_CATCH_ALL

			ar.Close();
			delete pFile;
			if (newFigure != NIL) {
				newFigure->setController(this);
				int newX = getRandom(0,_width*2/3);
				int newY = getRandom(0,_height*2/3);
				if (newFigure->whoAreYou()->isIn(WEARENODEOBJECTS)) {
					int oldX = ((NodeFigure *)newFigure)->getX1();
					int oldY = ((NodeFigure *)newFigure)->getY1();
					int dx = newX - oldX;
					int dy = newY - oldY;
					newFigure->moveCoord(dx,dy);
				} else if (newFigure->whoAreYou()->equals(IAMTEXT)) {
					int oldX = ((Text *)newFigure)->getX1();
					int oldY = ((Text *)newFigure)->getY1();
					int dx = newX - oldX;
					int dy = newY - oldY;
					newFigure->moveCoord(dx,dy);
				}
				newFigure->makeRegion(_canvasRgn);
				addExcludeRectForBottomObjects(newFigure,figures());
				figures()->insert(newFigure);
				draw(newFigure);
				_currentFocus = newFigure;
			}
		}
	} else {
		// 일반적인 클립보드 내용인 경우
		BeginWaitCursor();
		int x1 = 0;
		int y1 = 0;
		int x2 = x1 + 100;
		int y2 = y1 + 100;
		CRect rect;
		if (m_pSelection) {
			m_pSelection->getXY12(this,rect);
			m_pSelection->Delete();
			x1 = rect.left;
			y1 = rect.top;
			x2 = rect.right;
			y2 = rect.bottom;
		} else if (_popupX > 0 && _popupY > 0) {
			x1 = _popupX;
			y1 = _popupY;
			x2 = x1 + 100;
			y2 = y1 + 100;
		}
		m_pSelection = new COODCntrlItem(GetDocument());
		TRY {
			if (!m_pSelection->CreateFromData(&dataObject) &&
				!m_pSelection->CreateStaticFromData(&dataObject)) {
				AfxThrowMemoryException();
			}
			m_pSelection->setCoord(x1+originX(),y1+originY(),x2+originX(),y2+originY());
			m_pSelection->setController(this,viewTitle);
			m_pSelection->makeRegion(this);
			m_pSelection->UpdateLink();
		}
		CATCH_ALL(e) {
			m_pSelection->Delete();
			m_pSelection = NULL;
			AfxMessageBox(IDP_FAILED_TO_CREATE);
		}
		END_CATCH_ALL

		EndWaitCursor();
	}

	GetDocument()->setModifiedFlag();
	GetDocument()->UpdateAllViews(NULL);
	Invalidate();
}

void COODView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	_popupX = getRandom(0,_width*2/3);
	_popupY = getRandom(0,_height*2/3);
	OnPopupEditPaste();
}

void COODView::OnSetFocus(CWnd* pOldWnd) 
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState) {
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL) {
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}
	CScrollView::OnSetFocus(pOldWnd);
}

void COODView::OnObjectTransparent() 
{
	// TODO: Add your command handler code here
	
	GetDocument()->setModifiedFlag();
	if (m_pSelection != NULL) {
		m_pSelection->toggleOpaqueFlag();
		Invalidate();
	}
}

void COODView::OnObjectProperties() 
{
	// TODO: Add your command handler code here
	if (m_pSelection == NULL) return;
	COlePropertiesDialog dlg(m_pSelection,100,100,NULL);
	dlg.DoModal();
}

void COODView::OnEditDelete() 
{
	// TODO: Add your command handler code here
	if (m_pSelection != NULL) {
		deleteSelectedObject();
	} else if (_theBucket->isEmpty() == FALSE || _currentFocus != NIL) {
		deleteCurrentFigure();
	}
}

void COODView::OnEditSelectAll() 
{
	// TODO: Add your command handler code here
	if (figures()->nOfList() == 0) return;
	eraseDots(_theBucket);
	_theBucket->clearList();
	_theBucket->copyAllFigures(figures());
	_theBucket->copyAllOleItems(GetDocument(),this);
	_currentFocus = NIL;
	Invalidate();
}

void COODView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (CWnd::GetFocus() != this) {
		pCmdUI->Enable(FALSE);
		return;
	}
	if (_theBucket->isEmpty() == FALSE) {
		pCmdUI->Enable(TRUE);
		return;
	}
	if (_currentFocus != NIL) {
		// figure object
		pCmdUI->Enable(TRUE);
		return;
	}
	if (m_pSelection != NULL) {
		// OLE object
		pCmdUI->Enable(TRUE);
		return;
	}
	pCmdUI->Enable(FALSE);
}

void COODView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (CWnd::GetFocus() != this) {
		pCmdUI->Enable(FALSE);
		return;
	}
	if (_currentFocus != NIL && 
		_currentFocus->whoAreYou()->isIn(WEARECLIPBOARDOBJECTS) &&
		_editingTag == FALSE) {
		pCmdUI->Enable(TRUE);
		return;
	}
	if (m_pSelection != NULL) {
		pCmdUI->Enable(TRUE);
	} else {
		pCmdUI->Enable(FALSE);
	}
}

void COODView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if (CWnd::GetFocus() != this) {
		pCmdUI->Enable(FALSE);
		return;
	}
	COleDataObject dataObject;
	BOOL bEnable = dataObject.AttachClipboard() &&
		(dataObject.IsDataAvailable(OODClipFormat) ||
		 COleClientItem::CanCreateFromData(&dataObject));
	pCmdUI->Enable(bEnable);
}

void COODView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (CWnd::GetFocus() != this) {
		pCmdUI->Enable(FALSE);
		return;
	}
	if (_currentFocus != NIL && 
		_currentFocus->whoAreYou()->isIn(WEARECLIPBOARDOBJECTS) &&
		_editingTag == FALSE) {
		pCmdUI->Enable(TRUE);
		return;
	}
	if (m_pSelection != NULL) {
		pCmdUI->Enable(TRUE);
	} else {
		pCmdUI->Enable(FALSE);
	}
}

void COODView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (CWnd::GetFocus() != this) {
		pCmdUI->Enable(FALSE);
		return;
	}
	if (figures()->nOfList() > 0) {
		pCmdUI->Enable(TRUE);
	} else {
		pCmdUI->Enable(FALSE);
	}
}

void COODView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

void COODView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

BOOL COODView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ((pMsg->message == WM_KEYDOWN) && 
		(LOWORD(pMsg->wParam) == VK_ESCAPE) &&
		(ktgF_processKeys == TRUE) &&
		_currentFocus != NIL) {
		editorFinished();
		return -1;
	} else if ((pMsg->message == WM_KEYDOWN) && 
		(LOWORD(pMsg->wParam) == VK_ESCAPE) &&
		(ktgF_connectionContinueDraw == TRUE) &&
		_currentConnection != NIL) {
		BOOL abortAll = _currentConnection->abortDraw(FALSE);
		if (abortAll) {
			delete _currentConnection;
			_currentConnection = NIL;
			Invalidate();
		} else {
			insert(_currentConnection);
		}
		ktgF_connectionContinueDraw = FALSE;
		drawingEpilog();
		ReleaseCapture();
	}
	return CScrollView::PreTranslateMessage(pMsg);
}

void COODView::OnUpdatePopupEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	COleDataObject dataObject;
	BOOL bEnable = dataObject.AttachClipboard() &&
		COleClientItem::CanCreateFromData(&dataObject);
	if (bEnable) {
		pCmdUI->Enable(TRUE);
	} else {
		pCmdUI->Enable(FALSE);
	}	
}


void COODView::OnToolsGrid() 
{
	// TODO: Add your command handler code here
	if (theAppPtr->setGridFlag) {
		theAppPtr->setGridFlag = FALSE;
	} else {
		theAppPtr->setGridFlag = TRUE;
	}
	Invalidate(); // for InPlaceFrame
	mainFramePtr->setModifiedFlagForAllDocAndInvalidate();
}

void COODView::OnUpdateToolsGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(theAppPtr->setGridFlag);
}

BOOL COODView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	COleClientItem *pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetActiveView() == this) {
		pActiveItem->Deactivate();
		m_pSelection = NULL;
	}
	BOOL flag = CScrollView::OnScrollBy(sizeScroll, bDoScroll);
	if (flag == FALSE) return FALSE;
	_explicitScrolling = TRUE;

	CPoint pt(abs(sizeScroll.cx),abs(sizeScroll.cy));
	DPtoLP(pt);
	if (sizeScroll.cx > 0) {
		CRect rect(_width-pt.x-100,0,_width,_height);
		LPtoDP(rect);
		InvalidateRect(&rect,TRUE);
	} else if (sizeScroll.cx < 0) {
		CRect rect(0,0,pt.x+100,_height);
		LPtoDP(rect);
		InvalidateRect(&rect,TRUE);
	}
	if (sizeScroll.cy > 0) {
		CRect rect(0,_height-pt.y-100,_width,_height);
		LPtoDP(rect);
		InvalidateRect(&rect,TRUE);
	} else if (sizeScroll.cy < 0) {
		CRect rect(0,0,_width,pt.y+100);
		LPtoDP(rect);
		InvalidateRect(&rect,TRUE);
	}
	return flag;
}


BOOL COODView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect client;
	pDC->GetClipBox(client);
	CBrush brush;
	brush.CreateSolidBrush(theAppPtr->paperColor);
	brush.UnrealizeObject();
	pDC->FillRect(client,&brush);	
	return TRUE;
}

void COODView::OnToolsColorPaper() 
{
	// TODO: Add your command handler code here
	CColorDialog aDlg;
	UINT ans = aDlg.DoModal();
	if (ans != IDOK) return;
	theAppPtr->paperColor = aDlg.GetColor();
	if (ErasePen != NIL) {
		delete ErasePen; ErasePen = NIL;
	}
	ErasePen = new CPen(PS_SOLID,1,theAppPtr->paperColor);
	if (EraseBrush != NIL) {
		delete EraseBrush; EraseBrush = NIL;
	}
	EraseBrush = new CBrush(theAppPtr->paperColor);
	Invalidate(); // for InPlaceFrame
	mainFramePtr->setModifiedFlagForAllDocAndInvalidate();
}

void COODView::OnToolsColorText() 
{
	// TODO: Add your command handler code here
	
	CColorDialog aDlg;
	UINT ans = aDlg.DoModal();
	if (ans != IDOK) return;
	theAppPtr->textColor = aDlg.GetColor();
	Invalidate(); // for InPlaceFrame
	mainFramePtr->setModifiedFlagForAllDocAndInvalidate();
}

void COODView::OnToolsColorShapeForeground() 
{
	// TODO: Add your command handler code here
	
	CColorDialog aDlg;
	UINT ans = aDlg.DoModal();
	if (ans != IDOK) return;
	theAppPtr->shapeForegroundColor = aDlg.GetColor();
	if (PlainPen != NIL) {
		delete PlainPen; PlainPen = NIL;
	}
	PlainPen = new CPen(PS_SOLID,1,theAppPtr->shapeForegroundColor);
	if (RubberbandPen != NIL) {
		delete RubberbandPen; RubberbandPen = NIL;
	}
	RubberbandPen = new CPen(PS_SOLID,1,theAppPtr->shapeForegroundColor);
	if (PlainBrush != NIL) {
		delete PlainBrush; PlainBrush = NIL;
	}
	PlainBrush = new CBrush(theAppPtr->shapeForegroundColor);
	Figure *ptr = figures()->getFirst();
	while (ptr != NIL) {
		ptr->setForeground(theAppPtr->shapeForegroundColor);
		ptr = figures()->getNext();
	}
	Invalidate(); // for InPlaceFrame
	mainFramePtr->setShapeForeground(theAppPtr->shapeForegroundColor);
}

void COODView::OnToolsColorShapeBackground() 
{
	// TODO: Add your command handler code here
	
	CColorDialog aDlg;
	UINT ans = aDlg.DoModal();
	if (ans != IDOK) return;
	theAppPtr->shapeBackgroundColor = aDlg.GetColor();
	if (ShapeEraseBrush != NIL) {
		delete ShapeEraseBrush; ShapeEraseBrush = NIL;
	}
	ShapeEraseBrush = new CBrush(theAppPtr->shapeBackgroundColor);
	Figure *ptr = figures()->getFirst();
	while (ptr != NIL) {
		ptr->setBackground(theAppPtr->shapeBackgroundColor);
		ptr = figures()->getNext();
	}
	Invalidate(); // for InPlaceFrame
	mainFramePtr->setShapeBackground(theAppPtr->shapeBackgroundColor);
}

void COODView::OnViewRefresh() 
{
	// TODO: Add your command handler code here
	
	CDC *pDC = GetDC();

	_currentFocus = NULL;
	m_pSelection = NULL;

	COODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect client;
	GetClientRect(client);
	CBrush brush;
	brush.CreateSolidBrush(theAppPtr->paperColor);
	brush.UnrealizeObject();
	pDC->FillRect(client,&brush);

	// TODO: add draw code for native data here
	setDrawingContext(KTG_DRAWING);
	OnPrepareDC(pDC); 

	if (theAppPtr->setGridFlag) {
		drawGrid(pDC);
	}

	remakeAllRegions(pDoc);

	FigureList *figs = figures();
	Figure *ptr = figs->getFirst();
	while(ptr != NIL) {
		if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS) == TRUE) {
			ptr->draw(pDC);
		}
		ptr = figs->getNext();
	}
	ptr = figs->getFirst();
	while(ptr != NIL) {
		if (ptr->whoAreYou()->isIn(WEAREWIDEOBJECTS) == FALSE) {
			ptr->draw(pDC);
		}
		ptr = figs->getNext();
	}

	POSITION pos = pDoc->GetStartPosition();
	while(pos != NULL) {
		COODCntrlItem *selection = (COODCntrlItem *)pDoc->GetNextClientItem(pos);
		if (selection != NULL) 
			selection->draw(this,pDC);
	}

	OODReleaseDC(pDC,TRUE);
}

void COODView::onViewZoom(CString &value)
{
	if (!GetDocument()->IsInPlaceActive()) {
		mainFramePtr->setZoomValue(value);
	} else if (GetDocument()->getInPlaceFrame() != NIL) {
		GetDocument()->getInPlaceFrame()->setZoomValue(value);
	}
	OnZoom();
}

void COODView::OnViewZoom10() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("10");
	onViewZoom(value);
}

void COODView::OnViewZoom100() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("100");
	onViewZoom(value);
}

void COODView::OnViewZoom20() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("20");
	onViewZoom(value);
}

void COODView::OnViewZoom30() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("30");
	onViewZoom(value);
}

void COODView::OnViewZoom40() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("40");
	onViewZoom(value);
}

void COODView::OnViewZoom50() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("50");
	onViewZoom(value);
}

void COODView::OnViewZoom60() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("60");
	onViewZoom(value);
}

void COODView::OnViewZoom70() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("70");
	onViewZoom(value);
}

void COODView::OnViewZoom80() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("80");
	onViewZoom(value);
}

void COODView::OnViewZoom90() 
{
	// TODO: Add your command handler code here
	
	CString value = _T("90");
	onViewZoom(value);
}

void COODView::OnLineArrow()
{
	if (_currentFocus == NIL) return;
	if (_currentFocus->whoAreYou()->equals(IAMLINE) == FALSE) return;
	((Line *)_currentFocus)->setArrow(_popupX,_popupY);
	_currentFocus = NIL;
	Invalidate();
}

void COODView::onLineStyle(int s)
{
	if (_currentFocus == NIL) return;
	if (_currentFocus->whoAreYou()->equals(IAMLINE) == FALSE) return;
	((Line *)_currentFocus)->style() = s;
	_currentFocus = NIL;
	Invalidate();
}

void COODView::OnLineStyleSolid()
{
	onLineStyle(SOLID);
}

void COODView::OnLineStyleDash()
{
	onLineStyle(DASHED);
}

void COODView::OnLineStyleDot()
{
	onLineStyle(DOTED);
}

void COODView::onLineThickness(int n)
{
	if (_currentFocus == NIL) return;
	if (_currentFocus->whoAreYou()->equals(IAMLINE) == FALSE) return;
	((Line *)_currentFocus)->setThickness(n);
	_currentFocus = NIL;
	Invalidate();
}

void COODView::OnLineThickness1()
{
	onLineThickness(1);
}

void COODView::OnLineThickness2()
{
	onLineThickness(2);
}

void COODView::OnLineThickness3()
{
	onLineThickness(3);
}

void COODView::OnLineThickness4()
{
	onLineThickness(4);
}

void COODView::OnTbActor() 
{
	// TODO: Add your command handler code here
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_ACTOR);
	if (itsMe) return;
	_whatNodeToDraw = ID_TB_ACTOR;
	pressModelTBButton(ID_TB_ACTOR);					
}


void COODView::OnTbBox()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: Add your command handler code here
	
	_whatNodeToDraw = -1;
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_BOX);
	if (itsMe) return;
	_whatTionToDraw = KTG_BOX;
	pressModelTBButton(ID_TB_BOX);					
}


void COODView::OnTbCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	_whatNodeToDraw = -1;
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_CIRCLE);
	if (itsMe) return;
	_whatTionToDraw = KTG_CIRCLE;
	pressModelTBButton(ID_TB_CIRCLE);					
}


void COODView::OnTbRoundboxa()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	_whatNodeToDraw = -1;
	BOOL itsMe = undoIfSomeButtonAlreadyPressed(ID_TB_ROUNDBOXA);
	if (itsMe) return;
	_whatTionToDraw = KTG_ROUNDBOXA;
	pressModelTBButton(ID_TB_ROUNDBOXA);					
}
