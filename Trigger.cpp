// Trigger.cpp: implementation of the Trigger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "Trigger.h"
#include "ConnectionInfoTuple.h"
#include "Line.h"
#include "LineNodeList.h"
#include "LineNode.h"
#include "CITList.h"
#include "NodeFigureList.h"
#include "COODView.h"
#include "ConnectionText.h"
#include "TriggerText.h"
#include "Diamond.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DIAMOND_WIDTH	(15)
#define DIAMOND_HEIGHT	(10)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Trigger,Connection,1)

Trigger::Trigger()
: Connection()
{
	_popup = theAppPtr->theTriggerPopup;
}

Trigger::Trigger(COODView *controller,Popup *popup,Line *aLine)
: Connection(controller,popup,aLine)
{
}

Trigger::~Trigger()
{
}

void Trigger::Serialize(CArchive& ar)
{
	Connection::Serialize(ar);
}

Figure* Trigger::born(Figure* ptr)
{
	Trigger *copied;
	if (ptr == NIL) {
		copied = new Trigger(NIL,NIL,NIL);
	} else {
		copied = (Trigger *)ptr;
	}
	return (Connection::born((Figure *)copied));
}


UnsignedLong *Trigger::whoAreYou()
{
	return IAMTRIGGER; 
}

BOOL Trigger::setModelSpecificSymbol(NodeFigure *nodeFocus)
{
	int n = _nodeFigures->nOfList();
	if (n < 1) {
		return TRUE;
	} 
	if (n == 1) {
		Line *firstLine = _lines->getFirst()->line();
		int x1 = firstLine->getX1();
		int y1 = firstLine->getY1();
		ConnectionInfoTuple *aTuple = 
			new ConnectionInfoTuple(_nodeFigures->getFirst(),x1,y1);
		_infoTuples->insert(aTuple);
	}
	Line *lastLine = _lines->getLast()->line();
	lastLine->setDir(NORMAL_DIR,HEADARROW2);
	int x = lastLine->getX2();
	int y = lastLine->getY2();
	ConnectionInfoTuple *aTuple = 
		new ConnectionInfoTuple(nodeFocus,x,y);
	_infoTuples->insert(aTuple);
	return FALSE;
}

void Trigger::setModelSpecificSymbolAll()
{
	LineNode *aNode = _lines->getFirst();
	while(aNode != NIL) {
		aNode->line()->setDir(NODIR,HEADNONE);
		aNode = _lines->getNext();
	}
	NodeFigure *nodeFigure = _nodeFigures->getFirst();
	nodeFigure = _nodeFigures->getNext();
	while (nodeFigure != NIL) {
		ConnectionInfoTuple *aTuple = _infoTuples->findTupleFor(nodeFigure);
		int x = aTuple->getX();
		int y = aTuple->getY();
		Line *foundLine = NIL;
		int where;
		aNode = _lines->getFirst();
		while(aNode != NIL) {
			where = aNode->line()->whereToMeet(x,y); 
			if (where == ATBEFORE || where == ATAFTER) {
				foundLine = aNode->line();
				break;
			}
			aNode = _lines->getNext();
		}
		if (foundLine != NIL) {
			if (where == ATBEFORE) {
				foundLine->setDir(INVERT_DIR,HEADARROW2);	
			} else {
				foundLine->setDir(NORMAL_DIR,HEADARROW2);	
			}
		}
		nodeFigure = _nodeFigures->getNext();
	}
	/*
	NodeFigure *nodeFigure = _nodeFigures->getLast();
	ConnectionInfoTuple *aTuple = _infoTuples->getLast();
	if (aTuple == NIL) return;
	int x = aTuple->getX();
	int y = aTuple->getY();
	int where = -1;
	Line *lastLine = NIL;
	aNode = _lines->getFirst();
	while(aNode != NIL) {
		where = aNode->line()->whereToMeet(x,y); 
		if (where == ATBEFORE || where == ATAFTER) {
			lastLine = aNode->line();
			break;
		}
		aNode = _lines->getNext();
	}
	if (lastLine == NIL) return;
	if (where == ATBEFORE) {
		lastLine->setDir(INVERT_DIR,HEADARROW2);	
	} else {
		lastLine->setDir(NORMAL_DIR,HEADARROW2);	
	}
	*/
}

TriggerText* Trigger::selectOrCreateText()
{
	if (_text != NIL) {
		_focus = _text;
		return (TriggerText *)_text;
	}
	_text = new TriggerText(_controller,this,0,0,theAppPtr->theEditPopup);
	setTextPosition(-30,20,-10);
	return (TriggerText *)_text;
}

void Trigger::draw(CDC *dcp)
{
	if (!_inCanvas) return;
	Connection::draw(dcp); 
	int mode = dcp->GetROP2();
	if (mode == R2_NOTXORPEN) return;
	CPoint *jointPoints = NIL;
	int n = getJointPoints(jointPoints);
	if (n > 0) {
		// ternary association
		for (int i = 0; i < n; i++) {
			int x1 = jointPoints[i].x - DIAMOND_WIDTH;
			int y1 = jointPoints[i].y - DIAMOND_HEIGHT;
			int x2 = jointPoints[i].x + DIAMOND_WIDTH;
			int y2 = jointPoints[i].y + DIAMOND_HEIGHT;
			Diamond aDiamond(_controller,x1,y1,x2,y2,NIL);
			aDiamond.draw(dcp);
		}
		delete jointPoints;
	}
}

int Trigger::getJointPoints(CPoint*& points)
{
	CPoint tmpPoints[100];
	int count = 0;
	LineNode *aNode = _lines->getFirst();
	while (aNode != NIL) {
		int nOfListWithoutObsoleteLine = 0;
		LineNode *tmpNode = aNode->beforeList()->getFirst();
		while(tmpNode != NIL) {
			if (tmpNode->line()->isObsolete() == FALSE)
				nOfListWithoutObsoleteLine++;
			tmpNode = aNode->beforeList()->getNext();
		}
		if (nOfListWithoutObsoleteLine > 1) {
			int x = aNode->line()->getX1();
			int y = aNode->line()->getY1();
			BOOL alreadyFound = FALSE;
			for (int i = 0; i < count; i++) {
				if (tmpPoints[i].x == x &&
					tmpPoints[i].y == y) {
					alreadyFound = TRUE;
					break;
				}
			}
			if (alreadyFound == FALSE) {
				tmpPoints[count].x = x;
				tmpPoints[count].y = y;
				count++;
			}
			if (count > 99) break;
		}
		nOfListWithoutObsoleteLine = 0;
		tmpNode = aNode->afterList()->getFirst();
		while(tmpNode != NIL) {
			if (tmpNode->line()->isObsolete() == FALSE)
				nOfListWithoutObsoleteLine++;
			tmpNode = aNode->afterList()->getNext();
		}
		if (nOfListWithoutObsoleteLine > 1) {
			int x = aNode->line()->getX2();
			int y = aNode->line()->getY2();
			BOOL alreadyFound = FALSE;
			for (int i = 0; i < count; i++) {
				if (tmpPoints[i].x == x &&
					tmpPoints[i].y == y) {
					alreadyFound = TRUE;
					break;
				}
			}
			if (alreadyFound == FALSE) {
				tmpPoints[count].x = x;
				tmpPoints[count].y = y;
				count++;
			}
			if (count > 99) break;
		}
		aNode = _lines->getNext();
	}
	if (count == 0) return 0;
	points = new CPoint[count];
	for (int i = 0; i < count; i++) {
		points[i].x = tmpPoints[i].x;
		points[i].y = tmpPoints[i].y;
	}
	return count;
}
