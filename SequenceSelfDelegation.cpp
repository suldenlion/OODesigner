// SequenceSelfDelegation.cpp: implementation of the SequenceSelfDelegation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "SequenceSelfDelegation.h"
#include "COODView.h"
#include "SequenceObject.h"
#include "Line.h"
#include "LineNode.h"
#include "LineNodeList.h"
#include "NodeFigureList.h"
#include "ConnectionText.h"
#include "UnsignedLong.h"

#define SELF_DELEGATION_WIDTH	(40)
#define SELF_DELEGATION_HEIGHT	(30)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//#define SELF_DELEGATION_WIDTH	(20)
//#define SELF_DELEGATION_HEIGHT	(5)

IMPLEMENT_SERIAL(SequenceSelfDelegation,Connection,1)

SequenceSelfDelegation::SequenceSelfDelegation()
: Connection()
{
	_popup = theAppPtr->theMessagePopup;

	_moveUpperBound = -1;
	_moveLowerBound = -1;
	_activationBarFlag = FALSE;
}

SequenceSelfDelegation::SequenceSelfDelegation(COODView *controller,SequenceObject *theObject,int x,int y,Popup *popup)
: Connection(controller,popup,NIL)
{
	_moveUpperBound = -1;
	_moveLowerBound = -1;
	_activationBarFlag = FALSE;
	if (controller == NIL) return;
	int x1 = x;
	int y1 = y;
	int x2 = x+SELF_DELEGATION_WIDTH;
	int y2 = y+SELF_DELEGATION_HEIGHT;
	Line *aLine = new Line(controller,x1,y1,x2,y1,NIL,STRAIGHT);
	LineNode *aNode = new LineNode(aLine);
	_lines->insert(aNode);
	aLine = new Line(controller,x2,y1,x2,y2,NIL,STRAIGHT);
	aNode = new LineNode(aLine);
	_lines->insert(aNode);
	aLine = new Line(controller,x2,y2,x1,y2,NIL,STRAIGHT);
	aLine->setDir(NORMAL_DIR,HEADARROW1);
	aNode = new LineNode(aLine);
	_lines->insert(aNode);
	remake();
	_nodeFigures->insert(theObject);
	_nodeFigures->insert(theObject,ABSOLUTELY);
}

SequenceSelfDelegation::~SequenceSelfDelegation()
{
}

void SequenceSelfDelegation::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _moveUpperBound << (LONG) _moveLowerBound;
		ar << (BYTE) _activationBarFlag;
	} else {
		ar >> (LONG&) _moveUpperBound >> (LONG&) _moveLowerBound;
		ar >> (BYTE&) _activationBarFlag;
		if (_text != NIL)
			_text->setPopupPointer(theAppPtr->theEditPopup);
	}
}

Figure* SequenceSelfDelegation::born(Figure* ptr)
{
	SequenceSelfDelegation *copied;
	if (ptr == NIL) {
		copied = new SequenceSelfDelegation(NIL,NIL,0,0,NIL);
	} else {
		copied = (SequenceSelfDelegation *)ptr;
	}
	copied->_activationBarFlag = _activationBarFlag;
	return (Connection::born((Figure *)copied));
}

UnsignedLong *SequenceSelfDelegation::whoAreYou()
{
	return IAMSEQUENCESELFDELEGATION;
}

void SequenceSelfDelegation::epilog(BOOL skipflag)
{
	_moveAllFlag = FALSE;
	if (skipflag) return;
	tailorEndLinesAll();
	makeRegion(_controller->canvasRgn());
}

void SequenceSelfDelegation::move(CDC* dcp,int dx,int dy)
{
	Line *aLine = _lines->getFirst()->line();
	if (_moveUpperBound > aLine->getY1() + dy) return;
	aLine = _lines->getLast()->line();
	if (_moveLowerBound < aLine->getY2() + dy) return;
	if (_activationBarFlag) drawActivationBar(dcp);
	Connection::move(dcp,0,dy);
	if (_activationBarFlag) drawActivationBar(dcp);
}

void SequenceSelfDelegation::tailorEndLinesAll()
{
	_activationBarFlag = FALSE;
	NodeFigure *majorNode = _nodeFigures->getFirst();
	Line *startLine = _lines->getFirst()->line();
	_controller->clear(startLine);
	majorNode->adjustLine(startLine,TRUE);
	NodeFigure *lastNode = _nodeFigures->getLast();
	Line *lastLine = _lines->getLast()->line();
	lastNode->adjustLine(lastLine,FALSE);
	if (majorNode->whoAreYou()->equals(IAMSEQUENCEOBJECT) == FALSE) 
		return;
	SequenceObject *theObject = (SequenceObject *)majorNode;
	int centerX = theObject->lifeLane()->getX1();
	int testX = lastLine->getX2();
	if (testX >= centerX+10) {
		int newX2 = lastLine->_x2.get() + ACTIVATION_BAR_WIDTH;
		lastLine->_x2.set(newX2);
		_activationBarFlag = TRUE;
	} else {
		_activationBarFlag = FALSE;
	}
	return;
}

BOOL SequenceSelfDelegation::moveProlog(BOOL moveAllFlag)
{
	if (moveAllFlag) return TRUE;
	_focus = NIL;
	_moveAllFlag = TRUE;
	SequenceObject *theObject = (SequenceObject *)_nodeFigures->getFirst();
	_moveUpperBound = theObject->lifeLane()->getY1()+1;
	_moveLowerBound = theObject->lifeLane()->getY2()-1;
	return FALSE;
}

BOOL SequenceSelfDelegation::wantToResize(int &x,int &y)
{
	return FALSE;
}

void SequenceSelfDelegation::letsGo(NodeFigure *leader)
{
	_moveAllFlag = TRUE;
}

void SequenceSelfDelegation::comeOn(CDC* dcp,int dx,int dy)
{
	if (_moveAllFlag) {
		if (_activationBarFlag) drawActivationBar(dcp);
		Connection::move(dcp,dx,dy);
		if (_activationBarFlag) drawActivationBar(dcp);
	}
}

ConnectionText* SequenceSelfDelegation::selectOrCreateText()
{
	if (_text != NIL) {
		_focus = _text;
		return _text;
	}
	_text = new ConnectionText(_controller,this,0,0,theAppPtr->theEditPopup);
	setTextPosition(-20,20,-10);
	return _text;
}

void SequenceSelfDelegation::drawBoundary(CDC* dcp)
{
	Lines::draw(dcp);
	if (_text != NIL && 
		_text->isEmpty() == FALSE) {
		int mode = dcp->GetROP2();
		if (mode == R2_NOTXORPEN) {
			_text->drawBoundary(dcp);
		} else {
			_text->draw(dcp);
		}
	}
	if (_symbol != NIL) _symbol->drawBoundary(dcp);
	if (_activationBarFlag) drawActivationBar(dcp);
}

void SequenceSelfDelegation::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	Connection::draw(dcp);
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) return;
	if (_activationBarFlag) drawActivationBar(dcp);
}

BOOL SequenceSelfDelegation::tryToDeleteOneLineSegment(NodeFigure *aNodeFigure)
{
	return FALSE;
}

void SequenceSelfDelegation::drawActivationBar(CDC *dcp)
{
	Line *lastLine = _lines->getLast()->line();
	int x = lastLine->getX2();
	int y = lastLine->getY2();
	int x1 = x - 2 * ACTIVATION_BAR_WIDTH;
	int y1 = y - ACTIVATION_BAR_WIDTH;
	int x2 = x;
	int y2 = y + ACTIVATION_BAR_WIDTH;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		CRect rect(x1,y1,x2,y2);
		CBrush brush(theAppPtr->shapeBackgroundColor);
		dcp->FillRect(&rect,&brush);
		dcp->Rectangle(x1,y1,x2,y2);
	} else {
		dcp->Rectangle(x1,y1,x2,y2);
	}
}