// CollaborationObject.cpp: implementation of the CollaborationObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "CollaborationObject.h"
#include "ObjectText.h"
#include "SlaveryTextList.h"
#include "FigureList.h"
#include "COODView.h"
#include "CollaborationObjectMessageText.h"
#include "CollaborationObjectPopup.h"

#define SELF_DELEGATION_WIDTH			(15)
#define SELF_DELEGATION_HEIGHT			(25)
#define SELF_DELEGATION_DELTA_FROM_X2	(10)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CollaborationObject,EditableFigure,1)

CollaborationObject::CollaborationObject()
: EditableFigure()
{
	_popup = theAppPtr->theCollaborationObjectPopup;

	_selfMessageText = NIL;
	_selfDelegationFlag = FALSE;
	_canDoSelfDelegation = FALSE;
}

CollaborationObject::CollaborationObject(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	_selfMessageText = NIL;
	_selfDelegationFlag = FALSE;
	_canDoSelfDelegation = FALSE;
	if (controller == NIL) return;
	_popup = popup;
	_initWidth = COLLABORATION_OBJECT_INIT_WIDTH;
	_gapX = XGAP_COLLABORATION_OBJECT;
	_gapY = YGAP_COLLABORATION_OBJECT;
	_shape = new Box(controller,ox,oy,ox+_initWidth,oy+2*_gapY+deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	setBackground(theAppPtr->shapeBackgroundColor);
	_texts->insert(new ObjectText(controller,this,IAMOBJECTNAME,ox+_gapX,oy+_gapY));
}

CollaborationObject::~CollaborationObject()
{
	if (_selfMessageText != NIL) {
		delete _selfMessageText;
		_selfMessageText = NIL;
	}
}

void CollaborationObject::Serialize(CArchive& ar)
{
	EditableFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _selfMessageText << (BYTE)_selfDelegationFlag;
	} else {
		ar >> _selfMessageText >> (BYTE&)_selfDelegationFlag;
	}
}

UnsignedLong* CollaborationObject::whoAreYou()
{
	return IAMCOLLABORATIONOBJECT;
}

Figure* CollaborationObject::born(Figure* ptr)
{
	CollaborationObject *copied;
	if (ptr == NIL) {
		copied = new CollaborationObject(NIL,0,0,0,NIL);
	} else {
		copied = (CollaborationObject *)ptr;
	}
	/* 아래 부분은 논리적으로 복사하면 안된다. 
	    왜냐하면 self delegation은 connection의 의미를 갖기 때문에 */
	/*
	copied->_selfDelegationFlag = _selfDelegationFlag;
	if (_selfMessageText != NIL) {
		copied->_selfMessageText = (Text *)_selfMessageText->born();
		copied->_selfMessageText->setMaster(this);
	}
	*/
	return (EditableFigure::born((Figure *)copied));
}

void CollaborationObject::deleteFocusObject()
{
	if (_focus == NIL) return;
	if (_selfDelegationFlag == FALSE) return;
	setSelfDelegation();
	_focus = NIL;
}

CollaborationObjectMessageText* CollaborationObject::setSelfDelegation()
{
	if (_selfDelegationFlag == TRUE) {
		clearSelfDelegation();
		_selfDelegationFlag = FALSE;
		if (_selfMessageText != NIL) {
			_controller->clear(_selfMessageText);
			delete _selfMessageText;
			_selfMessageText = NIL;
		}
		return NIL;
	} else {
		_selfDelegationFlag = TRUE;
		_controller->draw(this);
		int x = getX2();
		int y = getY1();
		int sx = x - SELF_DELEGATION_DELTA_FROM_X2 - 2*SELF_DELEGATION_WIDTH;
		int sy = y - SELF_DELEGATION_HEIGHT*5/3;
		_selfMessageText = new CollaborationObjectMessageText(_controller,this,sx,sy,NIL);
		_focus = _selfMessageText;
		return _selfMessageText;
	}
}

void CollaborationObject::clearSelfDelegation()
{
	if (_selfDelegationFlag == FALSE) return;
	int x1 = getX1(); int y1 = getY1();
	int x2 = getX2(); int y2 = getY2();
	int ax1 = x2 - SELF_DELEGATION_DELTA_FROM_X2 - SELF_DELEGATION_WIDTH;
	int ay1 = y1 - SELF_DELEGATION_HEIGHT;
	int ax2 = x2 - SELF_DELEGATION_DELTA_FROM_X2;
	int ay2 = y1;
	CRect tmp(ax1,ay1,ax2,ay2);
	_controller->invalidateRect(&tmp);
}

void CollaborationObject::drawSelfDelegation(CDC *dcp)
{
	if (_selfDelegationFlag == FALSE) return;
	int x1 = getX1(); int y1 = getY1();
	int x2 = getX2(); int y2 = getY2();
	int ax1 = x2 - SELF_DELEGATION_DELTA_FROM_X2 - SELF_DELEGATION_WIDTH;
	int ay1 = y1 - SELF_DELEGATION_HEIGHT;
	int ax2 = x2 - SELF_DELEGATION_DELTA_FROM_X2;
	int ay2 = y1 + 15;
	int startX = ax2;
	int startY = y1;
	int endX = ax1;
	int endY = startY;
	dcp->Arc(ax1,ay1,ax2,ay2,startX,startY,endX,endY);
	if (_selfMessageText == NIL) return;
	if (_selfMessageText->isEmpty()) return;
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) return;
	_selfMessageText->draw(dcp);
}

void CollaborationObject::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(clip(dcp),RGN_COPY);
		excludeRects(dcp);
	}
	EditableFigure::draw(dcp);
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(NULL,RGN_COPY);
	}
	drawSelfDelegation(dcp);
}

void CollaborationObject::drawOnMetaFile(CDC *dcp)
{
	if (!_inCanvas) return;
	EditableFigure::drawOnMetaFile(dcp);
	drawSelfDelegation(dcp);
}

void CollaborationObject::drawBoundary(CDC *dcp)
{
	EditableFigure::drawBoundary(dcp);
	drawSelfDelegation(dcp);
	if (_controller->whatTionToDraw() != -1) return;
	if (_selfMessageText != NIL) {
		_selfMessageText->drawBoundary(dcp);
	}
}

void CollaborationObject::clear(CDC *dcp)
{
	clearSelfDelegation();
	EditableFigure::clear(dcp);
	if (_selfMessageText != NIL) {
		_selfMessageText->clear(dcp);
	}
}

void CollaborationObject::setController(COODView *ptr)
{
	EditableFigure::setController(ptr);
	if (_selfMessageText != NIL) {
		_selfMessageText->setController(ptr);
	}
}

void CollaborationObject::move(CDC *dcp,int dx,int dy)
{
	drawSelfDelegation(dcp);
	EditableFigure::move(dcp,dx,dy);
	drawSelfDelegation(dcp);
	if (_selfMessageText != NIL) {
		_selfMessageText->move(dcp,dx,dy);
	}
}

void CollaborationObject::moveCoordForScroll(int dx,int dy)
{
	EditableFigure::moveCoordForScroll(dx,dy);
	if (_selfMessageText != NIL) {
		_selfMessageText->moveCoord(dx,dy);
	}
}

void CollaborationObject::modifyWidthMinus(int lineDX,int index)
{
	clearSelfDelegation();
	EditableFigure::modifyWidthMinus(lineDX,index);
}

void CollaborationObject::modifyWidthPlus(int lineDX,int index)
{
	clearSelfDelegation();
	EditableFigure::modifyWidthPlus(lineDX,index);
}

void CollaborationObject::bye()
{
	if (_focus != NIL && _focus == _selfMessageText) {
		_selfMessageText->bye();
		if (_selfMessageText->isObsolete()) {
			clearSelfDelegation();
			delete _selfMessageText;
			_selfMessageText = NIL;
			_selfDelegationFlag = FALSE;
			_focus = this;
		}
	} else {
		EditableFigure::bye();
	}
}

BOOL CollaborationObject::onEnter(int x,int y)
{
	_focus = NIL;
	if (_selfMessageText != NIL && _selfMessageText->onEnter(x,y)) {
		_focus = _selfMessageText;
		return TRUE;
	}
	return EditableFigure::onEnter(x,y);
}

void CollaborationObject::makeRegion(CRgn *sourceClipRgn)
{
	if (_selfMessageText != NIL) {
		_selfMessageText->makeRegion(sourceClipRgn);
	}
	EditableFigure::makeRegion(sourceClipRgn);
}

void CollaborationObject::resetRegion()
{
	if (_selfMessageText != NIL) {
		_selfMessageText->resetRegion();
	}
	EditableFigure::resetRegion();
}

void CollaborationObject::releaseRegion()
{
	if (_selfMessageText != NIL) {
		_selfMessageText->releaseRegion();
	}
	EditableFigure::releaseRegion();
}

void CollaborationObject::popup(CPoint* event,BOOL)
{
	if (_selfMessageText != NIL &&
		_focus == _selfMessageText) {
		popupPointer()->changeMenuItemName("Delete");
		Figure::popup(event);
		return;
	}
	if (_selfDelegationFlag) {
		popupPointer()->changeMenuItemName("Self Delegation");
		_canDoSelfDelegation = FALSE;
	} else {
		popupPointer()->changeMenuItemName("Self Delegation");
		_canDoSelfDelegation = TRUE;
	}
	Figure::popup(event);
}
