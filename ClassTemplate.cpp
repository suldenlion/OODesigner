// ClassTemplate.cpp: implementation of the ClassTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "COODView.h"
#include "ClassTemplate.h"
#include "Box.h"
#include "Line.h"
#include "LineList.h"
#include "ClassText.h"
#include "ClassLibrary.h"
#include "SlaveryTextList.h"
#include "TextContent.h"
#include "UnsignedLong.h"
#include "ConnectionList.h"
#include "Connection.h"
#include "CITList.h"
#include "ConnectionInfoTuple.h"
#include "ClassTemplatePopup.h"
#include "TemplateClassTag.h"
#include "TwoPointFigure.h"
#include "FigureList.h"
#include "Association.h"
#include "InterfacePortList.h"
#include "InterfacePort.h"
#include "InterfacePortText.h"
#include "Circle.h"
#include "PackageLibrary.h"
#include "COODClassDoc.h"
#include "COODCommonDoc.h"
#include "TextContent.h"
#include "ClassContent.h"
#include "ClassFigureLibrary.h"
#include "CMainFrame.h"
#include "CResizableTreeBar.h"
#include "ExcludeRectList.h"
#include "ExcludeRect.h"

#define MORE_GAP_AT_TOP	(6)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ClassTemplate,EditableFigure,1)

ClassTemplate::ClassTemplate()
: EditableFigure()
{
	_popup = theAppPtr->theClassTemplatePopup;

	_templateFlag = FALSE;
	_fixedSizeFlag = FALSE;
	_varSupressedFlag = FALSE;
	_methodSupressedFlag = FALSE;
	_templateTag = NIL;
	_associationPtr = NIL;
	_savedX2 = -1;
	_savedY2 = -1;
	_nameField = NIL;
	_varField = NIL;
	_methodField = NIL;
	_separator1 = NIL;
	_separator2 = NIL;
	_minimized = FALSE;
	_ports = NIL;
	_interfaceExtensionLine = NIL;
	_alreadyCopiedFromContent = FALSE;
	_classContent = NIL;
	_stereotypeTmp = "";
	_canDoSupressDataMembers = FALSE;
	_canDoSupressMemberFunctions = FALSE;
	_doNotDrawAssociationLink = FALSE;
}

void ClassTemplate::Serialize(CArchive& ar)
{
	BOOL reservedFlag0ClassTemplate = FALSE;
	BOOL reservedFlag1ClassTemplate = FALSE;
	BOOL reservedFlag2ClassTemplate = FALSE;
	BOOL reservedFlag3ClassTemplate = FALSE;
	BOOL reservedFlag4ClassTemplate = FALSE;
	UINT reservedInt0ClassTemplate = 0;
	UINT reservedInt1ClassTemplate = 0;
	UINT reservedInt2ClassTemplate = 0;
	UINT reservedInt3ClassTemplate = 0;
	UINT reservedInt4ClassTemplate = 0;
	CString reservedString0ClassTemplate = _T("");
	CString reservedString1ClassTemplate = _T("");
	CString reservedString2ClassTemplate = _T("");
	CString reservedString3ClassTemplate = _T("");
	CString reservedString4ClassTemplate = _T("");

	EditableFigure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (BYTE) _templateFlag << (BYTE) _fixedSizeFlag;
		ar << (BYTE) _varSupressedFlag << (BYTE) _methodSupressedFlag;
		ar << _templateTag << _associationPtr;
		ar << _classContent << _nameField << _varField << _methodField;
		ar << _separator1 << _separator2;
		ar << (BYTE) _minimized;
		ar << _ports << _interfaceExtensionLine;

		ar << (BYTE)reservedFlag0ClassTemplate;
		ar << (BYTE)reservedFlag1ClassTemplate;
		ar << (BYTE)reservedFlag2ClassTemplate;
		ar << (BYTE)reservedFlag3ClassTemplate;
		ar << (BYTE)reservedFlag4ClassTemplate;
		ar << (LONG)reservedInt0ClassTemplate;
		ar << (LONG)reservedInt1ClassTemplate;
		ar << (LONG)reservedInt2ClassTemplate;
		ar << (LONG)reservedInt3ClassTemplate;
		ar << (LONG)reservedInt4ClassTemplate;
		ar << reservedString0ClassTemplate;
		ar << reservedString1ClassTemplate;
		ar << reservedString2ClassTemplate;
		ar << reservedString3ClassTemplate;
		ar << reservedString4ClassTemplate;
	} else {
		ar >> (BYTE&) _templateFlag >> (BYTE&) _fixedSizeFlag;
		ar >> (BYTE&) _varSupressedFlag >> (BYTE&) _methodSupressedFlag;
		ar >> _templateTag >> _associationPtr;
		ar >> _classContent >> _nameField >> _varField >> _methodField;
		ar >> _separator1 >> _separator2;
		ar >> (BYTE&) _minimized;
		ar >> _ports >> _interfaceExtensionLine;

		ar >> (BYTE&)reservedFlag0ClassTemplate;
		ar >> (BYTE&)reservedFlag1ClassTemplate;
		ar >> (BYTE&)reservedFlag2ClassTemplate;
		ar >> (BYTE&)reservedFlag3ClassTemplate;
		ar >> (BYTE&)reservedFlag4ClassTemplate;
		ar >> (LONG&)reservedInt0ClassTemplate;
		ar >> (LONG&)reservedInt1ClassTemplate;
		ar >> (LONG&)reservedInt2ClassTemplate;
		ar >> (LONG&)reservedInt3ClassTemplate;
		ar >> (LONG&)reservedInt4ClassTemplate;
		ar >> reservedString0ClassTemplate;
		ar >> reservedString1ClassTemplate;
		ar >> reservedString2ClassTemplate;
		ar >> reservedString3ClassTemplate;
		ar >> reservedString4ClassTemplate;
	}
}

ClassTemplate::ClassTemplate(COODView *controller,int ox,int oy,int deltaV,Popup *popup)
: EditableFigure(controller)
{
	_templateFlag = FALSE;
	_fixedSizeFlag = FALSE;
	_varSupressedFlag = FALSE;
	_methodSupressedFlag = FALSE;
	_doNotDrawAssociationLink = FALSE;

	_templateTag = NIL;
	_nameField = NIL;
	_varField = NIL;
	_methodField = NIL;
	_separator1 = NIL;
	_separator2 = NIL;
	_minimized = FALSE;
	_popup = popup;
	_savedX2 = -1;
	_savedY2 = -1;
	_associationPtr = NIL;
	_stereotypeTmp = "";

	_ports = new InterfacePortList();

	_canDoSupressDataMembers = FALSE;
	_canDoSupressMemberFunctions = FALSE;

	if (controller == NIL) return;
	_initWidth = CLASSTEMPLATE_INIT_WIDTH;
	_gapX = XGAP_CLASSTEMPLATE;
	_gapY = YGAP_CLASSTEMPLATE;
	_shape = new Box(controller,ox,oy,ox+_initWidth,oy+6*_gapY+3*deltaV,NIL);
	_shape->filled() = TRUE;
	_shape->setBackground(theAppPtr->shapeBackgroundColor);
	EditableFigure::setBackground(theAppPtr->shapeBackgroundColor);
	_nameField = new ClassText(controller,this,IAMCLASSNAME,ox+_gapX,oy+_gapY);
	_texts->insert(_nameField);
	_varField = new ClassText(controller,this,IAMVARIABLES,ox+_gapX,oy+3*_gapY+deltaV);
	_texts->insert(_varField);
	_methodField = new ClassText(controller,this,IAMMETHODS,ox+_gapX,oy+5*_gapY+2*deltaV);
	_texts->insert(_methodField);
	_separator1 = new Line(controller,ox,oy+2*_gapY+deltaV,ox+_initWidth,oy+2*_gapY+deltaV,NIL,STRAIGHT);
	_separators->insert(_separator1);
	_separator2 = new Line(controller,ox,oy+4*_gapY+2*deltaV,ox+_initWidth,oy+4*_gapY+2*deltaV,NIL,STRAIGHT);
	_separators->insert(_separator2);

	_interfaceExtensionLine = new Line(controller,ox,getY2(),ox,getY2(),NIL,STRAIGHT);
	_alreadyCopiedFromContent = FALSE;
	_classContent = NIL;
}

ClassTemplate::~ClassTemplate()
{
	if (_templateTag != NIL) {
		delete _templateTag; _templateTag = NIL;
	}
	if (_associationPtr != NIL) {
		_associationPtr->setAssociationClassPtr(NIL);
		_associationPtr = NIL;
	}
	if (_interfaceExtensionLine != NIL) {
		delete _interfaceExtensionLine;
		_interfaceExtensionLine = NIL;
	}
	if (_ports != NIL) {
		delete _ports;
		_ports = NIL;
	}
	if (_minimized) {
		delete _varField;
		delete _methodField;
		delete _separator1;
		delete _separator2;
	}
}

int ClassTemplate::nOfMemberFunctions()
{
	if (_methodField->isEmpty()) return 0;
	return _methodField->nOfLines();
}

int ClassTemplate::nOfDataMembers()
{
	if (_varField->isEmpty()) return 0;
	return _varField->nOfLines();
}

void ClassTemplate::getDataMemberBrowserString(int i,int &vis,CString &aLineString)
{
	_varField->getMemberBrowserString(i,vis,aLineString);
}

void ClassTemplate::getMemberFunctionBrowserString(int i,int &vis,CString &aLineString)
{
	_methodField->getMemberBrowserString(i,vis,aLineString);
}

void ClassTemplate::deleteMemberTextContent()
{
	_varField->deleteTextContent();
	_methodField->deleteTextContent();
}

void ClassTemplate::setTemplateFlag()
{
	_templateFlag = TRUE;
	_moreGapAtTop = MORE_GAP_AT_TOP;
	int deltaV = _nameField->deltaV();
	int x1 = _shape->getX1();
	int x2 = _shape->getX2();
	int y1 = _shape->getY1();
	int ox = x1 + (x2 - x1)/2;
	int oy = y1 - deltaV/2 - 1;
	_templateTag = new TemplateClassTag(_controller,this,ox,oy,deltaV,NIL);
	int y2 = _shape->_y2.get();
	_shape->_y2.set(y2+_moreGapAtTop);
	_nameField->moveCoord(0,_moreGapAtTop);
	_varField->moveCoord(0,_moreGapAtTop);
	_methodField->moveCoord(0,_moreGapAtTop);
	_separator1->moveCoord(0,_moreGapAtTop);
	_separator2->moveCoord(0,_moreGapAtTop);
}

void ClassTemplate::setBackground(COLORREF c) 
{
	EditableFigure::setBackground(c);
	if (_templateTag != NIL)
		_templateTag->setBackground(c);
}

BOOL ClassTemplate::getInterfaceFlag() 
{ 
	return _classContent->getInterfaceFlag(); 
}

void ClassTemplate::setStereotype(const char *stype)
{
	char buffer[BUFSIZ];
	if (Text::strcpyCompact(buffer,stype,BUFSIZ) == 0) return;
	CString testName = stype;
	if (testName.CompareNoCase("interface") == 0) {
		_nameField->setItalicFont(TRUE);
	} else {
		_nameField->setItalicFont(FALSE);
	}
	_stereotypeTmp = stype;
	_moreGapAtTop = MORE_GAP_AT_TOP;
	int y2 = _shape->_y2.get();
	_shape->_y2.set(y2+_moreGapAtTop);
	_nameField->moveCoord(0,_moreGapAtTop);
	_varField->moveCoord(0,_moreGapAtTop);
	_methodField->moveCoord(0,_moreGapAtTop);
	_separator1->moveCoord(0,_moreGapAtTop);
	_separator2->moveCoord(0,_moreGapAtTop);
}

UnsignedLong* ClassTemplate::whoAreYou()
{
	return IAMCLASSTEMPLATE;
}

Figure* ClassTemplate::born(Figure* ptr)
{
	ClassTemplate *copied;
	if (ptr == NIL) {
		copied = new ClassTemplate(NIL,0,0,0,NIL);
	} else {
		copied = (ClassTemplate *)ptr;
	}
	copied->_minimized = _minimized;
	copied->_templateFlag = _templateFlag;
	copied->_fixedSizeFlag = _fixedSizeFlag;
	copied->_varSupressedFlag = _varSupressedFlag;
	copied->_methodSupressedFlag = _methodSupressedFlag;

	if (_minimized) {
		copied->_varField = (ClassText *)_varField->born();
		copied->_methodField = (ClassText *)_methodField->born();
		copied->_separator1 = (Line *)_separator1->born();
		copied->_separator2 = (Line *)_separator2->born();
	}
	return (EditableFigure::born((Figure *)copied));
}

void ClassTemplate::setSpecificDataMembers()
{
	if (_minimized) {
		_nameField = (ClassText *)_texts->getFirst();
	} else {
		_nameField = (ClassText *)_texts->getFirst();
		_varField = (ClassText *)_texts->getNext();
		_methodField = (ClassText *)_texts->getNext();
		_separator1 = (Line *)_separators->getFirst();
		_separator2 = (Line *)_separators->getNext();
	}
}

void ClassTemplate::changeSize()
{
	if (_varSupressedFlag) {
		_varSupressedFlag = FALSE;
		_methodSupressedFlag = FALSE;
		_minimized = FALSE;
		_texts->clear();
		_texts->insert(_nameField);
		_texts->insert(_varField);
		_texts->insert(_methodField);
		_varField->recalcCoordFromXY1();
		int startX1 = _varField->getX1();
		int startY1 = _varField->getY2() + 2*_gapY;
		_methodField->recalcCoordFromXY1(startX1,startY1);
		_separator1->_y1.y = _separator2->_y1.y;
		_separator1->_y2.y = _separator2->_y2.y;
		_separator2->_y1.set(_varField->getY2() + _gapY);
		_separator2->_y2.set(_varField->getY2() + _gapY);
		setXY2FromContent();
		int w = _shape->getX2() - _shape->getX1();
		if (w < _initWidth) {
			_shape->_x2.set(getX1()+_initWidth);
		}
		adjustTemplateTagPosition();
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
	} else if (_methodSupressedFlag) {
		_varSupressedFlag = FALSE;
		_methodSupressedFlag = FALSE;
		_minimized = FALSE;
		_texts->insert(_methodField);
		_separator2->_y1.set(_shape->getY2());
		_separator2->_y2.set(_shape->getY2());
		int startX1 = _shape->getX1() + _gapX;
		int startY1 = _shape->getY2() + _gapY;
		_methodField->recalcCoordFromXY1(startX1,startY1);
		setXY2FromContent();
		int w = _shape->getX2() - _shape->getX1();
		if (w < _initWidth) {
			_shape->_x2.set(getX1()+_initWidth);
		}
		adjustTemplateTagPosition();
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
	} else if (_fixedSizeFlag || _minimized) {
		_minimized = FALSE;
		_texts->insert(_varField);
		_texts->insert(_methodField);
		_separators->insert(_separator1);
		_separators->insert(_separator2);
		setXY2FromContent();
		int w = _shape->getX2() - _shape->getX1();
		if (w < _initWidth) {
			_shape->_x2.set(getX1()+_initWidth);
		}
		adjustTemplateTagPosition();
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
	} else if (_minimized == FALSE) {
		_minimized = TRUE;
		_texts->remove(_varField);
		_texts->remove(_methodField);
		_separators->clear();
		int y = _separator1->getY2();
		int nameW = _nameField->content()->otherLinesMaxWidth();
		if (nameW+2*_gapX > _initWidth) {
			_shape->_x2.set(getX1()+nameW+2*_gapX);
		} else {
			_shape->_x2.set(getX1()+_initWidth);
		}
		_shape->_y2.set(y);
		adjustTemplateTagPosition();
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
	}
	_fixedSizeFlag = FALSE;
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->extendToNodeFigure(this);
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->tailorEndLinesAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setModelSpecificSymbolAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->makeRegion(_controller->canvasRgn());
		ptr = _connections->getNext();
	}
	resetInterfaceExtensionLineSize();
	makeRegion(_controller->canvasRgn());
}

void ClassTemplate::supressDataMembers()
{
	if (_varSupressedFlag) return;
	_fixedSizeFlag = FALSE;
	if (_methodSupressedFlag) {
		_methodSupressedFlag = FALSE;
		_varSupressedFlag = FALSE;
		_minimized = FALSE;
		// recover original shape
		_texts->clear();
		_texts->insert(_nameField);
		_texts->insert(_varField);
		_texts->insert(_methodField);
		_separator2->_y1.set(_shape->getY2());
		_separator2->_y2.set(_shape->getY2());
		int startX1 = _shape->getX1()+_gapX;
		int startY1 = _varField->getY2()+2*_gapY;
		_methodField->recalcCoordFromXY1(startX1,startY1);
		setXY2FromContent();
		int w = _shape->getX2() - _shape->getX1();
		if (w < _initWidth) {
			_shape->_x2.set(getX1()+_initWidth);
		}
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
		changeSize();
		return;
	}
	_varSupressedFlag = TRUE;
	int varX1 = _varField->getX1();
	int varY1 = _varField->getY1();
	_texts->remove(_varField);
	_methodField->recalcCoordFromXY1(varX1,varY1);
	_separator2->_y1.y = _separator1->_y1.y;
	_separator2->_y2.y = _separator1->_y2.y;
	_separator1->_y1.y = _separator1->_y1.y - 2;
	_separator1->_y2.y = _separator1->_y2.y - 2;
	setXY2FromContent();
	int w = _shape->getX2() - _shape->getX1();
	if (w < _initWidth) {
		_shape->_x2.set(getX1()+_initWidth);
	}
	adjustTemplateTagPosition();
	_separator1->_x2.set(_shape->getX2());
	_separator2->_x2.set(_shape->getX2());
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->extendToNodeFigure(this);
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setModelSpecificSymbolAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->makeRegion(_controller->canvasRgn());
		ptr = _connections->getNext();
	}
	resetInterfaceExtensionLineSize();
	makeRegion(_controller->canvasRgn());
}

void ClassTemplate::supressMemberFuctions()
{
	if (_methodSupressedFlag) return;
	_fixedSizeFlag = FALSE;
	if (_varSupressedFlag) {
		_methodSupressedFlag = FALSE;
		_varSupressedFlag = FALSE;
		_minimized = FALSE;
		// recover original shape
		_texts->clear();
		_texts->insert(_nameField);
		_texts->insert(_varField);
		_texts->insert(_methodField);
		_separator1->_y1.y = _separator2->_y1.y;
		_separator1->_y2.y = _separator2->_y2.y;
		int startX1 = _shape->getX1()+_gapX;
		int startY1 = _varField->getY2()+2*_gapY;
		_methodField->recalcCoordFromXY1(startX1,startY1);
		_separator2->_y1.set(startY1-_gapY);
		_separator2->_y2.set(startY1-_gapY);
		setXY2FromContent();
		int w = _shape->getX2() - _shape->getX1();
		if (w < _initWidth) {
			_shape->_x2.set(getX1()+_initWidth);
		}
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
		changeSize();
		return;
	}
	_methodSupressedFlag = TRUE;
	_texts->remove(_methodField);
	_separator2->_y1.y = _separator2->_y1.y - 2;
	_separator2->_y2.y = _separator2->_y2.y - 2;
	setXY2FromContent();
	int w = _shape->getX2() - _shape->getX1();
	if (w < _initWidth) {
		_shape->_x2.set(getX1()+_initWidth);
	}
	adjustTemplateTagPosition();
	_separator1->_x2.set(_shape->getX2());
	_separator2->_x2.set(_shape->getX2());
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->extendToNodeFigure(this);
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setModelSpecificSymbolAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->makeRegion(_controller->canvasRgn());
		ptr = _connections->getNext();
	}
	resetInterfaceExtensionLineSize();
	makeRegion(_controller->canvasRgn());
}

void ClassTemplate::move(CDC* dcp,int dx,int dy)
{
	drawAssociationLink(dcp);
	EditableFigure::move(dcp,dx,dy);
	moveCoordWhenMinimized(dx,dy);
	if (_varSupressedFlag) {
		_varField->moveCoord(dx,dy);
	} else if (_methodSupressedFlag) {
		_methodField->moveCoord(dx,dy);
	}
	if (_templateTag != NIL) _templateTag->move(dcp,dx,dy);
	drawAssociationLink(dcp);
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->move(dcp,dx,dy);
		aPort = _ports->getNext();
	}
	_interfaceExtensionLine->move(dcp,dx,dy);
}

void ClassTemplate::moveCoord(int dx,int dy)
{
	EditableFigure::moveCoord(dx,dy);
	moveCoordWhenMinimized(dx,dy);
	if (_varSupressedFlag) {
		_varField->moveCoord(dx,dy);
	} else if (_methodSupressedFlag) {
		_methodField->moveCoord(dx,dy);
	}
	if (_templateTag != NIL) _templateTag->moveCoord(dx,dy);
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->moveCoord(dx,dy);
		aPort = _ports->getNext();
	}
	_interfaceExtensionLine->moveCoord(dx,dy);
}

void ClassTemplate::moveCoordForScroll(int dx,int dy)
{
	EditableFigure::moveCoordForScroll(dx,dy);
	moveCoordWhenMinimized(dx,dy);
	if (_varSupressedFlag) {
		_varField->moveCoord(dx,dy);
	} else if (_methodSupressedFlag) {
		_methodField->moveCoord(dx,dy);
	}
	if (_templateTag != NIL) _templateTag->moveCoord(dx,dy);
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->moveCoord(dx,dy);
		aPort = _ports->getNext();
	}
	_interfaceExtensionLine->moveCoord(dx,dy);
}

void ClassTemplate::moveCoordWhenMinimized(int dx,int dy)
{
	if (_minimized == FALSE) return;
	_varField->moveCoord(dx,dy);
	_methodField->moveCoord(dx,dy);
	_separator1->moveCoord(dx,dy);
	_separator2->moveCoord(dx,dy);
}

void ClassTemplate::bye()
{
	if (_focus == NIL) return;
	if (_focus->whoAreYou()->isIn(WEARETEXTOBJECTS) == FALSE) return;
	if (_focus->whoAreYou()->equals(IAMINTERFACEPORTTEXT) == TRUE) {
		((InterfacePortText *)_focus)->bye(); 
		return;
	}
	((SlaveryText *)_focus)->bye();
	if (_minimized) {
		_texts->remove(_varField);
		_texts->remove(_methodField);
		_separators->clear();
		int y = _separator1->getY2();
		int nameW = _nameField->content()->otherLinesMaxWidth();
		if (nameW+2*_gapX > _initWidth) {
			_shape->_x2.set(getX1()+nameW+2*_gapX);
		} else {
			_shape->_x2.set(getX1()+_initWidth);
		}
		_shape->_y2.set(y);
		adjustTemplateTagPosition();
		makeRegion(_controller->canvasRgn());
		Connection *ptr = _connections->getFirst();
		while (ptr != NIL) {
			ptr->extendToNodeFigure(this);
			ptr = _connections->getNext();
		}
		ptr = _connections->getFirst();
		while (ptr != NIL) {
			ptr->tailorEndLinesAll();
			ptr = _connections->getNext();
		}
		ptr = _connections->getFirst();
		while (ptr != NIL) {
			ptr->setModelSpecificSymbolAll();
			ptr = _connections->getNext();
		}
		ptr = _connections->getFirst();
		while (ptr != NIL) {
			ptr->makeRegion(_controller->canvasRgn());
			ptr = _connections->getNext();
		}
		_controller->Invalidate();
	} else if (_fixedSizeFlag) {
		if (_savedX2 != -1 && _savedY2 != -1) {
			_shape->_x2.x = _savedX2;
			_shape->_y2.y = _savedY2;
		}
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
		adjustTemplateTagPosition();
		makeRegion(_controller->canvasRgn());
		_savedX2 = -1;
		_savedY2 = -1;
		_controller->Invalidate();
	} else {
		EditableFigure::bye();
		adjustTemplateTagPosition();
	}
	parseMembers();
	registerClassContent();
	if (_stereotypeTmp.IsEmpty() == FALSE &&
		_classContent != NIL) {
		_classContent->setStereotype(_stereotypeTmp);
		_stereotypeTmp = "";
	}
	resetInterfaceExtensionLineSize();

	CDocument *pDoc = _controller->GetDocument();
	if (pDoc == NULL) return;
	if (pDoc->IsKindOf(RUNTIME_CLASS(COODClassDoc))) {
		theAppPtr->pCOODClassDoc->UpdateAllViews((CView *)_controller);
	}
}

PackageLibrary *ClassTemplate::getPackageLibrary()
{
	return theAppPtr->pCOODClassDoc->getAllClassContents();
}

ClassFigureLibrary *ClassTemplate::getClassFigureLibrary()
{
	return theAppPtr->pCOODClassDoc->getClassFiguresLibrary();
}

void ClassTemplate::justRegisterClassContent(ClassLibrary *pPackage)
{
	if (pPackage == NIL) return;
	char buffer[BUFSIZ];
	getName(buffer,BUFSIZ);
	if (strlen(buffer) == 0) return;
	CString className = buffer;
	pPackage->registerClassContent(className,_classContent);
}

void ClassTemplate::registerClassContent()
{
	char buffer[BUFSIZ];
	getName(buffer,BUFSIZ);
	if (strlen(buffer) == 0) return;
	if (_controller == NIL) return;
		// will be destroyed automatically
	CDocument *pDoc = _controller->GetDocument();
	if (pDoc == NULL) return;
	if (pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		// 이 경우는 패키지 그림 하나만 그리는 경우이다. 
		if (_alreadyCopiedFromContent == FALSE) { 
			CString className = buffer;
			_classContent = 
				((COODCommonDoc*)pDoc)->getClassContentFor(className,this);
			if (_classContent != NIL) {
				deleteMemberTextContent();
				_varField->setTextContent(_classContent->varContent());
				_methodField->setTextContent(_classContent->methodContent());

				makeShapeFromMemberContent();
				changeSize();
				return;
			}
		}
		CString className = buffer;
		_classContent = 
			((COODCommonDoc*)pDoc)->registerClassContent(className,this);
		((COODCommonDoc*)pDoc)->replaceFieldTextContent(className,this);
		return;
	}
	// 아래 경우는 워크 스페이스에서 작업하는 경우이다.
	if (_alreadyCopiedFromContent == FALSE) { 
		PackageLibrary *allClassContents = getPackageLibrary();
		CString className = buffer;
		_classContent = 
			allClassContents->getClassContentFor(className);
		if (_classContent != NIL) {
			deleteMemberTextContent();
			_varField->setTextContent(_classContent->varContent());
			_methodField->setTextContent(_classContent->methodContent());

			makeShapeFromMemberContent();
			changeSize();
			return;
		}
	}
	
	PackageLibrary *allClassContents = getPackageLibrary();
	CString packageName = _controller->viewTitleWithOutExtension;
	CString className = buffer;
	if (_modifiedFlag == TRUE) {
		mainFramePtr->m_wndTreeBar.insertClass(packageName,className,this);
	}
	_classContent = 
		allClassContents->registerClassContent(packageName,className,this);
	ClassFigureLibrary *classFiguresLibrary = getClassFigureLibrary();
	packageName = _controller->viewTitle;
	classFiguresLibrary->replaceFieldTextContent(packageName,className,this);
}

void ClassTemplate::replaceNameFieldContent()
{
	if (_templateFlag) return;
	char stype[BUFSIZ];
	int n = Text::strcpyCompact(stype,_classContent->stereotype(),BUFSIZ);

	if (n == 0 && _moreGapAtTop > 0) {
		_nameField->moveCoord(0,-_moreGapAtTop);
		_varField->moveCoord(0,-_moreGapAtTop);
		_methodField->moveCoord(0,-_moreGapAtTop);
		_separator1->moveCoord(0,-_moreGapAtTop);
		_separator2->moveCoord(0,-_moreGapAtTop);
		_moreGapAtTop = 0;
		_fixedSizeFlag = TRUE;
		_minimized = FALSE;
		_varSupressedFlag = FALSE;
		_methodSupressedFlag = FALSE;
	} else if (n > 0 && _moreGapAtTop == 0) {
		_moreGapAtTop = MORE_GAP_AT_TOP;
		_nameField->moveCoord(0,_moreGapAtTop);
		_varField->moveCoord(0,_moreGapAtTop);
		_methodField->moveCoord(0,_moreGapAtTop);
		_separator1->moveCoord(0,_moreGapAtTop);
		_separator2->moveCoord(0,_moreGapAtTop);
		_fixedSizeFlag = TRUE;
		_minimized = FALSE;
		_varSupressedFlag = FALSE;
		_methodSupressedFlag = FALSE;
	}
}

void ClassTemplate::replaceFieldTextContent(ClassTemplate *aClass,COODView *controller)
{
	if (this == aClass) return;
	if (_classContent == NIL) return;

	replaceNameFieldContent();

	int dx1 = _varField->_x2.x - _varField->_x1.x; 
	int dx2 = _methodField->_x2.x - _methodField->_x1.x;
	int oldDx = dx1;
	if (dx2 > dx1) oldDx = dx2;
	int oldDy = (_varField->_y2.y - _varField->_y1.y) +
				(_methodField->_y2.y - _methodField->_y1.y);

	_varField->setTextContent(_classContent->varContent());
	_methodField->setTextContent(_classContent->methodContent());
	// 이 함수에서의 좌표 계산은 실좌표를 이용해서 ...
	_varField->recalcCoordFromRealXY1(controller);
	int x2 = _varField->_x2.x;
	int y2 = _varField->_y2.y;
	_separator2->_y1.y = _varField->_y2.y + _gapY;
	_separator2->_y2.y = _varField->_y2.y + _gapY;
	int startX1 = _varField->_x1.x;
	int startY1 = _varField->_y2.y + 2*_gapY;
	_methodField->recalcCoordFromRealXY1(controller,startX1,startY1);
	if (_minimized) return;
	_texts->clear();
	_texts->insert(_nameField);
	_texts->insert(_varField);
	_texts->insert(_methodField);
	_separators->clear();
	_separators->insert(_separator1);
	_separators->insert(_separator2);
	_separator1->_x2.x = _shape->_x2.x;
	_separator2->_x2.x = _shape->_x2.x;
	_varSupressedFlag = FALSE;
	_methodSupressedFlag = FALSE;

	dx1 = _varField->_x2.x - _varField->_x1.x; 
	dx2 = _methodField->_x2.x - _methodField->_x1.x;
	int newDx = dx1;
	if (dx2 > dx1) newDx = dx2;
	int newDy = (_varField->_y2.y - _varField->_y1.y) +
				(_methodField->_y2.y - _methodField->_y1.y);
	if (newDx == oldDx && newDy == oldDy) return;
	_fixedSizeFlag = TRUE;
}

void ClassTemplate::copyMemberContentIfNeed()
{
	if (_alreadyCopiedFromContent == TRUE) return;
	char buffer[BUFSIZ];
	getName(buffer,BUFSIZ);
	if (strlen(buffer) == 0) return;
	if (_controller == NIL) return;
	CDocument *pDoc = _controller->GetDocument();
	if (pDoc == NULL) return;
	if (pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		// 이 경우는 패키지 그림 하나만 그리는 경우이다. 
		CString className = buffer;
		_classContent = 
			((COODCommonDoc*)pDoc)->getClassContentFor(className,this);
	} else {
		PackageLibrary *allClassContents = getPackageLibrary();
		CString packageName = _controller->viewTitleWithOutExtension;
		CString className = buffer;
		_classContent = 
			allClassContents->getClassContentFor(className);
	}
	if (_classContent == NIL) return;
	_alreadyCopiedFromContent = TRUE;
	deleteMemberTextContent();
	_varField->setTextContent(_classContent->copyVarContent());
	_methodField->setTextContent(_classContent->copyMethodContent());
	
	makeShapeFromMemberContent();
}

void ClassTemplate::makeShapeFromMemberContent()
{
	char stype[BUFSIZ];
	int n = Text::strcpyCompact(stype,_classContent->stereotype(),BUFSIZ);
	if (_stereotypeTmp.IsEmpty() == FALSE &&
		n > 0) {
		_stereotypeTmp = _classContent->stereotype();
		CString testName = _stereotypeTmp;
		if (testName.CompareNoCase("interface") == 0) {
			_nameField->setItalicFont(TRUE);
		} else {
			_nameField->setItalicFont(FALSE);
		}
	} else if (_stereotypeTmp.IsEmpty() == FALSE &&
		n == 0) {
		_stereotypeTmp = "";
		_controller->clear(this);
		_nameField->setItalicFont(FALSE);
		int y2 = _shape->_y2.get();
		_shape->_y2.set(y2-_moreGapAtTop);
		_nameField->moveCoord(0,-_moreGapAtTop);
		_varField->moveCoord(0,-_moreGapAtTop);
		_methodField->moveCoord(0,-_moreGapAtTop);
		_separator1->moveCoord(0,-_moreGapAtTop);
		_separator2->moveCoord(0,-_moreGapAtTop);
		_moreGapAtTop = 0;
		_fixedSizeFlag = FALSE;
		_minimized = FALSE;
		_varSupressedFlag = FALSE;
		_methodSupressedFlag = FALSE;
	} else if (_stereotypeTmp.IsEmpty() != FALSE &&
		n > 0) {
		_stereotypeTmp = _classContent->stereotype();
		CString testName = _stereotypeTmp;
		if (testName.CompareNoCase("interface") == 0) {
			_nameField->setItalicFont(TRUE);
		} else {
			_nameField->setItalicFont(FALSE);
		}
		_moreGapAtTop = MORE_GAP_AT_TOP;
		int y2 = _shape->_y2.get();
		_shape->_y2.set(y2+_moreGapAtTop);
		_nameField->moveCoord(0,_moreGapAtTop);
		_varField->moveCoord(0,_moreGapAtTop);
		_methodField->moveCoord(0,_moreGapAtTop);
		_separator1->moveCoord(0,_moreGapAtTop);
		_separator2->moveCoord(0,_moreGapAtTop);
		_fixedSizeFlag = FALSE;
		_minimized = FALSE;
		_varSupressedFlag = FALSE;
		_methodSupressedFlag = FALSE;
	}
	int maxX2 = 0;
	int maxY2 = 0;
	_varField->recalcCoordFromRealXY1(_controller);
	int x2 = _varField->_x2.x;
	int y2 = _varField->_y2.y;
	if (x2 > maxX2) maxX2 = x2;
	if (y2 > maxY2) maxY2 = y2;
	_separator2->_y1.y = _varField->_y2.y + _gapY;
	_separator2->_y2.y = _varField->_y2.y + _gapY;
	int startX1 = _varField->_x1.x;
	int startY1 = _varField->_y2.y + 2*_gapY;
	_methodField->recalcCoordFromRealXY1(_controller,startX1,startY1);
	x2 = _methodField->_x2.x;
	y2 = _methodField->_y2.y;
	if (x2 > maxX2) maxX2 = x2;
	if (y2 > maxY2) maxY2 = y2;
	_shape->_x2.x = maxX2 + _gapX;
	_shape->_y2.y = maxY2 + _gapY;
	_separator1->_x2.x = _shape->_x2.x;
	_separator2->_x2.x = _shape->_x2.x;

	int w = _shape->getX2() - _shape->getX1();
	if (w < _initWidth) {
		_shape->_x2.set(getX1()+_initWidth);
	}
	adjustTemplateTagPosition();
	_separator1->_x2.set(_shape->getX2());
	_separator2->_x2.set(_shape->getX2());
	if (_controller != NIL)
		_controller->draw(this);
}

BOOL ClassTemplate::startEdit()
{
	theAppPtr->deactivateAllPropertyDlgs();
	if (_focus == NIL) return FALSE;
	if (_focus->whoAreYou()->isIn(WEARETEXTOBJECTS) == FALSE) return FALSE;

	_modifiedFlag = FALSE;

	if (_focus->whoAreYou()->equals(IAMINTERFACEPORTTEXT)) {
		((Text *)_focus)->startEdit();
		return TRUE;
	}
	if (_minimized) {
		_texts->insert(_varField);
		_texts->insert(_methodField);
		_separators->insert(_separator1);
		_separators->insert(_separator2);
		setXY2FromContent();
		int w = _shape->getX2() - _shape->getX1();
		if (w < _initWidth) {
			_shape->_x2.set(getX1()+_initWidth);
		}
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
		makeRegion(_controller->canvasRgn());
		_shape->invalidate();
	} else if (_fixedSizeFlag) {
		_savedX2 = _shape->_x2.x;
		_savedY2 = _shape->_y2.y;
		setXY2FromContent();
		int w = _shape->getX2() - _shape->getX1();
		if (w < _initWidth) {
			_shape->_x2.set(getX1()+_initWidth);
		}
		_separator1->_x2.set(_shape->getX2());
		_separator2->_x2.set(_shape->getX2());
		makeRegion(_controller->canvasRgn());
		_controller->Invalidate();
	} else {
		/* 이건 이유를 모르는 디버깅 때문에 (resize랑 관계되는)... */
		/* 그러나 나중에 이유를 알았음: resize 테스트(wantToResize) 시에 _separators를 clear함 */
		_separators->insert(_separator1);
		_separators->insert(_separator2);
	}

	getName(_oldName,BUFSIZ);
	_alreadyCopiedFromContent = FALSE;
	if (strlen(_oldName) != 0) {
		_alreadyCopiedFromContent = TRUE;
		_varField->setTextContent(_classContent->copyVarContent());
		_methodField->setTextContent(_classContent->copyMethodContent());
	}

	((Text *)_focus)->startEdit();
	return TRUE;
}

void ClassTemplate::popup(CPoint* event,BOOL)
{
	if (_focus != NIL) {
		if (_focus->whoAreYou()->equals(IAMINTERFACEPORTTEXT) ||
			_focus->whoAreYou()->equals(IAMCIRCLE)) {
			_focus->popup(event);
			return;
		}
	}
	if (_minimized) {
		popupPointer()->changeMenuItemName("Normal Size");
		_canDoSupressDataMembers = FALSE;
		_canDoSupressMemberFunctions = FALSE;
		Figure::popup(event);
		return;
	}
	if (_varSupressedFlag) {
		popupPointer()->changeMenuItemName("Normal Size");
		_canDoSupressDataMembers = FALSE;
		_canDoSupressMemberFunctions = TRUE;
	} else if (_methodSupressedFlag) {
		popupPointer()->changeMenuItemName("Normal Size");
		_canDoSupressDataMembers = TRUE;
		_canDoSupressMemberFunctions = FALSE;
	} else if (_fixedSizeFlag) {
		popupPointer()->changeMenuItemName("Normal Size");
		_canDoSupressDataMembers = TRUE;
		_canDoSupressMemberFunctions = TRUE;
	} else {
		popupPointer()->changeMenuItemName("Minimize");
		_canDoSupressDataMembers = TRUE;
		_canDoSupressMemberFunctions = TRUE;
	}
	Figure::popup(event);
}

void ClassTemplate::drawAssociationLink(CDC *dcp)
{
	if (_associationPtr == NIL) return;
	if (_doNotDrawAssociationLink) return;

	int x1,y1;
	_associationPtr->getCenterPosition(x1,y1);
	int x2 = getX1() + width()/2;
	int y2 = getY1();
	DrawLine(dcp,x1,y1,x2,y2,1,DOTED);
}

void ClassTemplate::modifyWidthMinus(int lineDX,int index)
{
	if (_associationPtr != NIL) {
		int x1,y1;
		_associationPtr->getCenterPosition(x1,y1);
		int x2 = getX1() + width()/2;
		int y2 = getY1();
		if (x2 < x1) {
			int t = x1;
			x1 = x2;
			x2 = t;
		}
		if (y2 < y1) {
			int t = y1;
			y1 = y2;
			y2 = t;
		}
		x2 = x2 + 10;
		x1 = x1 - 10;
		CRect tmp(x1,y1,x2,y2);
		_controller->invalidateRect(&tmp,TRUE);
	}
	EditableFigure::modifyWidthMinus(lineDX,index);
}

void ClassTemplate::modifyWidthPlus(int lineDX,int index)
{
	EditableFigure::modifyWidthPlus(lineDX,index);
	if (_associationPtr == NIL) return;
	int x1,y1;
	_associationPtr->getCenterPosition(x1,y1);
	int x2 = getX1() + width()/2;
	int y2 = getY1();
	if (x2 < x1) {
		int t = x1;
		x1 = x2;
		x2 = t;
	}
	if (y2 < y1) {
		int t = y1;
		y1 = y2;
		y2 = t;
	}
	x2 = x2 + 10;
	x1 = x1 - 10;
	CRect tmp(x1,y1,x2,y2);
	_controller->invalidateRect(&tmp,TRUE);
}

void ClassTemplate::modifyHeight(int dy,int originalIndex)
{
	EditableFigure::modifyHeight(dy,originalIndex);
	resetInterfaceExtensionLineSize();
}

void ClassTemplate::setController(COODView *ptr)
{
	EditableFigure::setController(ptr);

	// minimized 된 경우 대비
	_nameField->setController(ptr);
	_varField->setController(ptr);
	_methodField->setController(ptr);
	_separator1->setController(ptr);
	_separator2->setController(ptr);

	if (_templateTag != NIL) _templateTag->setController(ptr);
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->setController(ptr);
		aPort = _ports->getNext();
	}
	_interfaceExtensionLine->setController(ptr);
}


void ClassTemplate::draw(CDC* dcp)
{
	if (!_inCanvas) return;
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
// 2014 OODesigner 수정 			dcp->SelectClipRgn(clip(dcp),RGN_COPY);
// 2014 OODesigner 수정 			excludeRects(dcp);
	}
	EditableFigure::draw(dcp);

	char stereoType[BUFSIZ];
	if (_stereotypeTmp.IsEmpty() == FALSE) {
		CString stype = "<<" + _stereotypeTmp + ">>";
		CFont font;
		font.CreateFont(12,0,0,0,
			FW_NORMAL,FALSE,
			FALSE,FALSE,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
//			DEFAULT_PITCH|FF_MODERN,"Times New Roman");
			DEFAULT_PITCH|FF_MODERN,DEFAULT_FACE_NAME);
		CFont *oldFont = dcp->SelectObject(&font);
		COLORREF oldColor = dcp->SetBkColor(background());
		dcp->TextOut(_shape->getX1()+5,_shape->getY1()+1,
			stype,strlen(stype));
		dcp->SetBkColor(oldColor);
		dcp->SelectObject(oldFont);
	} else if (_classContent != NIL &&
		_classContent->getStereotype(stereoType) == TRUE) {
		CFont font;
		font.CreateFont(12,0,0,0,
			FW_NORMAL,FALSE,
			FALSE,FALSE,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
//			DEFAULT_PITCH|FF_MODERN,"Times New Roman");
			DEFAULT_PITCH|FF_MODERN,DEFAULT_FACE_NAME);
		CFont *oldFont = dcp->SelectObject(&font);
		COLORREF oldColor = dcp->SetBkColor(background());
		dcp->TextOut(_shape->getX1()+5,_shape->getY1()+1,
			stereoType,strlen(stereoType));
		dcp->SetBkColor(oldColor);
		dcp->SelectObject(oldFont);
	}
	if (mode != R2_NOTXORPEN) {
// 2014 OODesigner 수정 			dcp->SelectClipRgn(NULL,RGN_COPY);
	}
	if (_templateTag != NIL) {
		_templateTag->draw(dcp);
	}
	drawAssociationLink(dcp);
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->draw(dcp);
		aPort = _ports->getNext();
	}
	_interfaceExtensionLine->draw(dcp);
}

void ClassTemplate::drawOnMetaFile(CDC* dcp)
{
	if (!_inCanvas) return;

	EditableFigure::drawOnMetaFile(dcp);

	char stereoType[BUFSIZ];
	if (_stereotypeTmp.IsEmpty() == FALSE) {
		CString stype = "<<" + _stereotypeTmp + ">>";
		CFont font;
		font.CreateFont(12,0,0,0,
			FW_NORMAL,FALSE,
			FALSE,FALSE,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
//			DEFAULT_PITCH|FF_MODERN,"Times New Roman");
			DEFAULT_PITCH|FF_MODERN,DEFAULT_FACE_NAME);
		CFont *oldFont = dcp->SelectObject(&font);
		COLORREF oldColor = dcp->SetBkColor(background());
		dcp->TextOut(_shape->getX1()+5,_shape->getY1()+1,
			stype,strlen(stype));
		dcp->SetBkColor(oldColor);
		dcp->SelectObject(oldFont);
	} else if (_classContent != NIL &&
		_classContent->getStereotype(stereoType) == TRUE) {
		CFont font;
		font.CreateFont(12,0,0,0,
			FW_NORMAL,FALSE,
			FALSE,FALSE,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
//			DEFAULT_PITCH|FF_MODERN,"Times New Roman");
			DEFAULT_PITCH|FF_MODERN,DEFAULT_FACE_NAME);
		CFont *oldFont = dcp->SelectObject(&font);
		COLORREF oldColor = dcp->SetBkColor(background());
		dcp->TextOut(_shape->getX1()+5,_shape->getY1()+1,
			stereoType,strlen(stereoType));
		dcp->SetBkColor(oldColor);
		dcp->SelectObject(oldFont);
	}
	if (_templateTag != NIL) {
		_templateTag->drawOnMetaFile(dcp);
	}
	drawAssociationLink(dcp);
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->draw(dcp);
		aPort = _ports->getNext();
	}
	_interfaceExtensionLine->drawOnMetaFile(dcp);
}

void ClassTemplate::drawBoundary(CDC* dcp)
{
	int mode = dcp->GetROP2();
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(clip(dcp),RGN_COPY);
		excludeRects(dcp);
	}
	if (mode != R2_NOTXORPEN && _templateTag != NIL) {
		int x1,y1,x2,y2;
		_templateTag->getExclusiveClipRect(x1,y1,x2,y2);
		dcp->ExcludeClipRect(x1,y1,x2,y2);
	}
	EditableFigure::drawBoundary(dcp);
	if (mode != R2_NOTXORPEN) {
		dcp->SelectClipRgn(NULL,RGN_COPY);
	}

	if (_templateTag != NIL) _templateTag->drawBoundary(dcp);
	drawAssociationLink(dcp);
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->drawBoundary(dcp);
		aPort = _ports->getNext();
	}
	_interfaceExtensionLine->draw(dcp);
}

void ClassTemplate::clear(CDC* dcp)
{
	EditableFigure::clear(dcp);
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->clear(dcp);
		aPort = _ports->getNext();
	}
}

void ClassTemplate::adjustTemplateTagPosition()
{
	if (_templateTag == NIL) return;
	int oldX1 = _templateTag->getX1();
	int newX1 = _shape->getX1() + _shape->width()/2;
	if (oldX1 == newX1) return;
	int diff = newX1 - oldX1;
	_templateTag->moveCoord(diff,0);
}

void ClassTemplate::deleteFocusObject()
{
	if (_focus == NIL) return;
	if (_focus->whoAreYou()->equals(IAMCIRCLE) == FALSE &&
		_focus->whoAreYou()->equals(IAMINTERFACEPORTTEXT) == FALSE)
		return;
	InterfacePort *portToDelete = NIL;
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		InterfacePortText *aNameText = aPort->interfaceName();
		Circle *aHole = aPort->hole();
		if (_focus == aNameText ||
			_focus == aHole) {
			portToDelete = aPort;
			break;
		}
		aPort = _ports->getNext();
	}
	Circle *newHole = NIL;
	_focus = NIL;
	if (portToDelete != NIL) {
		Circle *aHole = portToDelete->hole();
		newHole = (Circle *)aHole->born();
		_ports->remove(portToDelete);
		delete portToDelete;
	} else {
		return;
	}
	if (newHole == NIL) return;
	ConnectionList *copiedList = new ConnectionList();
	copiedList->copy(_connections);
	Connection *aConnection = copiedList->getFirst();
	while (aConnection != NIL) {
		BOOL meetOnInterface = FALSE;
		ConnectionInfoTuple *aTuple = aConnection->infoTuples()->getFirst();
		while (aTuple != NIL) {
			int x = aTuple->getX();
			int y = aTuple->getY();
			if (newHole->containsOnLargeBound(x,y)) {
				meetOnInterface = TRUE;
				break;
			}
			aTuple = aConnection->infoTuples()->getNext();
		}
		if (meetOnInterface == FALSE) {
			aConnection = copiedList->getNext();
			continue;
		}
		meetOnInterface = FALSE;
		BOOL segmentDeleted = 
			aConnection->tryToDeleteOneLineSegment(this);
		if (segmentDeleted == FALSE) {
			_controller->remove(aConnection);
			_controller->checkInList(aConnection);
			_controller->erase(aConnection);
			delete aConnection;
		}
		aConnection = copiedList->getNext();
	}
	delete copiedList;
	delete newHole;
	resetInterfaceExtensionLineSize();
}

void ClassTemplate::setFocus(int x,int y)
{
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		InterfacePortText *aNameText = aPort->interfaceName();
		if (aNameText->contains(x,y)) {
			aNameText->setXY(x,y);
			_focus = aPort->interfaceName();
			return;
		}
		Circle *aHole = aPort->hole();
		if (aHole->contains(x,y)) {
			_focus = aPort->interfaceName();
			return;
		}
		aPort = _ports->getNext();
	}
	if (_templateTag == NIL) {
		EditableFigure::setFocus(x,y);
		return;
	}
	if (x == -OODMAXINT && y == -OODMAXINT) {
		_focus = (Figure *)_templateTag->tagText();
		return;
	}
	int x1 = _templateTag->getX1();
	int y1 = _templateTag->getY1();
	int x2 = _templateTag->getX2();
	int y2 = _templateTag->getY2();
	CRgn *testRgn = _controller->makeRectRegion(x1,y1,x2-x1,y2-y1);
	if (!isEmptyRegion(testRgn) && testRgn->PtInRegion(x,y)) {
		delete testRgn;
		_focus = (Figure *)_templateTag->tagText();
		return;
	}
	delete testRgn;
	EditableFigure::setFocus(x,y);
}

int ClassTemplate::ptInWhichField(int x,int y)
{
	// reserve old focus
	Figure *oldFocus = _focus;

	EditableFigure::setFocus(x,y);
	Figure *testFocus = _focus;

	_focus = oldFocus;

	if (testFocus != NIL && testFocus == _varField) {
		return IAMVARIABLES;
	} else if (testFocus != NIL &&  testFocus == _methodField) {
		return IAMMETHODS;
	} else {
		return IAMCLASSNAME; // equals 0;
	}
}

BOOL ClassTemplate::wantToResize(int& x,int& y)
{
	if (_varSupressedFlag == TRUE) return FALSE;
	if (_methodSupressedFlag == TRUE) return FALSE;
	if (_minimized == TRUE) return FALSE;
	_savedX2 = -1;
	_savedY2 = -1;
	int x2 = _shape->getX2();
	int y2 = _shape->getY2();
	if (TwoPointFigure::wantToResize(x,y,x2,y2)) {
		_shape->wantToResizeExact(x2,y2);
		x = x2; y = y2;
		_separators->clear();
		_savedX2 = _shape->_x2.x;
		_savedY2 = _shape->_y2.y;
		return TRUE;
	}
	_shape->resetHotXY();
	return FALSE;
}

BOOL ClassTemplate::moveProlog(BOOL moveAllFlag)
{
	if (moveAllFlag) {
		_doNotDrawAssociationLink = TRUE;
	}
	return EditableFigure::moveProlog(moveAllFlag);
}

void ClassTemplate::epilog(BOOL skipflag)
{
	_doNotDrawAssociationLink = FALSE;
	if (_savedX2 == -1 && _savedY2 == -1) {
		EditableFigure::epilog(skipflag);
		return;
	}
	if (_shape->hotX() == NIL || _shape->hotY() == NIL) {
		EditableFigure::epilog(skipflag);
		return;
	}
	_separators->insert(_separator1);
	_separators->insert(_separator2);
	int nameW = _nameField->content()->otherLinesMaxWidth();
	int limitX = _separator1->_x1.x + nameW + 4;
	int limitY = _separator1->_y2.y;
	int lastX = _shape->hotX()->x;
	int lastY = _shape->hotY()->y;
	if (lastX < limitX ||
		lastY < limitY) {
		_controller->beep("Resizing aborted.");
		_shape->_x2.x = _savedX2;
		_shape->_y2.y = _savedY2;
		_savedX2 = -1;
		_savedY2 = -1;
		_controller->Invalidate();
		return;
	}
	_fixedSizeFlag = TRUE;
	_separator1->_x2.x = lastX;
	_separator2->_x2.x = lastX;
	_savedX2 = -1;
	_savedY2 = -1;
	adjustTemplateTagPosition();
	makeRegion(_controller->canvasRgn());
	Connection *ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->extendToNodeFigure(this);
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->tailorEndLinesAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->setModelSpecificSymbolAll();
		ptr = _connections->getNext();
	}
	ptr = _connections->getFirst();
	while (ptr != NIL) {
		ptr->makeRegion(_controller->canvasRgn());
		ptr = _connections->getNext();
	}
	_controller->Invalidate();
}

void ClassTemplate::eraseDots(CDC* dcp)
{
	if (_focus != NIL) {
		if (_focus->whoAreYou()->equals(IAMINTERFACEPORTTEXT) ||
			_focus->whoAreYou()->equals(IAMCIRCLE)) {
			_focus->eraseDots(dcp);
			return;
		}
	}
	EditableFigure::eraseDots(dcp);
}

void ClassTemplate::drawDots(CDC* dcp)
{
	if (_focus != NIL) {
		if (_focus->whoAreYou()->equals(IAMINTERFACEPORTTEXT) ||
			_focus->whoAreYou()->equals(IAMCIRCLE)) {
			_focus->drawDots(dcp);
			return;
		}
	}
	EditableFigure::drawDots(dcp);
}

void ClassTemplate::getInterfacePortText(char *text,int bufsiz)
{
	strcpy_s(text,bufsiz,"");
	if (_focus == NIL) return;
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		if (_focus == aPort->interfaceName() ||
			_focus == aPort->hole()) {
			aPort->interfaceName()->getName(text,bufsiz);
			return;
		}
		aPort = _ports->getNext();
	}
}

BOOL ClassTemplate::hasClassNameInInterfacePorts(CString &interfaceName)
{
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		char text[BUFSIZ];
		aPort->interfaceName()->getName(text,BUFSIZ);
		char compactedName[BUFSIZ];
		int n = Text::strcpyCompact(compactedName,text,BUFSIZ);
		if (n > 0 &&
			interfaceName.CompareNoCase(compactedName) == 0)
			return TRUE;
		aPort = _ports->getNext();
	}
	return FALSE;
}

BOOL ClassTemplate::onEnter(int x,int y)
{
	if (_controller->currentConnection() != NIL &&
		_controller->currentConnection()->whoAreYou()->equals(IAMDEPENDENCY)) {
		InterfacePort *aPort = _ports->getFirst();
		while (aPort != NIL) {
			Figure* ptr = aPort->onEnter(x,y);
			if (ptr != NIL &&
				ptr->whoAreYou()->equals(IAMCIRCLE)) {
				_focus = ptr;
				return TRUE;
			}
			aPort = _ports->getNext();
		}
	} else if (_controller->currentConnection() == NIL) {
		InterfacePort *aPort = _ports->getFirst();
		while (aPort != NIL) {
			Figure* ptr = aPort->onEnter(x,y);
			if (ptr != NIL) {
				_focus = ptr;
				return TRUE;
			}
			aPort = _ports->getNext();
		}
	}
	return EditableFigure::onEnter(x,y);
}

void ClassTemplate::makeRegion(CRgn *sourceClipRgn)
{
	EditableFigure::makeRegion(sourceClipRgn);
	if (_templateTag != NIL) {
		_templateTag->makeRegion(sourceClipRgn);
	}
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->makeRegion(sourceClipRgn);
		aPort = _ports->getNext();
	}
}

void ClassTemplate::resetRegion()
{
	EditableFigure::resetRegion();
	if (_templateTag != NIL) {
		_templateTag->resetRegion();
	}
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->resetRegion();
		aPort = _ports->getNext();
	}
}

void ClassTemplate::releaseRegion()
{
	EditableFigure::releaseRegion();
	if (_templateTag != NIL) {
		_templateTag->releaseRegion();
	}
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		aPort->releaseRegion();
		aPort = _ports->getNext();
	}
}

void ClassTemplate::resetInterfaceExtensionLineSize()
{
	int maxY = _ports->getMaxY();
	int baseY = getY2();
	if (maxY == 0) maxY = baseY;
	if (maxY > baseY) {
		_interfaceExtensionLine->_y1.set(baseY);
		_interfaceExtensionLine->_y2.set(maxY+1);
	} else {
		_interfaceExtensionLine->_y1.set(baseY);
		_interfaceExtensionLine->_y2.set(baseY);
	}
}

InterfacePortText* ClassTemplate::createInterfacePort()
{
	int ox = getX1();
	int oy = getY1();
	int newY = _ports->getNextYPosition(oy,INTERFACE_PORT_DELTA_Y);
	InterfacePort *aPort = new InterfacePort(_controller,this,
		ox,newY);
	_ports->insert(aPort);
	resetInterfaceExtensionLineSize();
	InterfacePortText *aText = aPort->interfaceName();
	_focus = (Figure *)aText;
	return aText;
}

BOOL ClassTemplate::adjustLine(Line *line,BOOL startPoint)
{
	int sx = 0;
	int sy = 0;
	if (startPoint) {
		sx = line->getX1();
		sy = line->getY1();
	} else {
		sx = line->getX2();
		sy = line->getY2();
	}
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		Circle *aHole = aPort->hole();
		if (aHole->contains(sx,sy)) {
			return aHole->adjustLine(line,startPoint);
		}
		aPort = _ports->getNext();
	}
	return EditableFigure::adjustLine(line,startPoint);
}

BOOL ClassTemplate::containsOnTupleBound(int x,int y)
{
	if (EditableFigure::containsOnLargeBound(x,y)) return TRUE;
	InterfacePort *aPort = _ports->getFirst();
	while (aPort != NIL) {
		Circle *aHole = aPort->hole();
		if (aHole->containsOnLargeBound(x,y)) {
			return TRUE;
		}
		aPort = _ports->getNext();
	}
	return FALSE;
}

void ClassTemplate::setClassContent(ClassContent *ptr)
{
	_classContent = ptr;
}

void ClassTemplate::resetAndReshapeClassTextContentFromClassContent(CString &packageName)
{
	_varField->setTextContent(_classContent->varContent());
	_methodField->setTextContent(_classContent->methodContent());	

	_savedX2 = _shape->_x2.x;
	_savedY2 = _shape->_y2.y;

	makeShapeFromMemberContent();

	if (_savedX2 == _shape->_x2.x && _savedY2 == _shape->_y2.y) {
		_savedX2 = -1;
		_savedY2 = -1;
		_fixedSizeFlag = FALSE;
	} else {
		_shape->_x2.x = _savedX2;
		_shape->_y2.y = _savedY2;
		_fixedSizeFlag = TRUE;
	}
	_separator1->_x2.set(_shape->getX2());
	_separator2->_x2.set(_shape->getX2());
	adjustTemplateTagPosition();
	parseMembers();
	if (_stereotypeTmp.IsEmpty() == FALSE &&
		_classContent != NIL) {
		_classContent->setStereotype(_stereotypeTmp);
		_stereotypeTmp = "";
	}
	resetInterfaceExtensionLineSize();
	char buffer[BUFSIZ];
	getName(buffer,BUFSIZ);
	CString className = buffer;
	mainFramePtr->m_wndTreeBar.insertClass(packageName,className,this);
}

TextContent *ClassTemplate::getNameContent()
{
	return _nameField->content();
}

TextContent *ClassTemplate::getVarContent()
{
	return _varField->content();
}

TextContent *ClassTemplate::getMethodContent()
{
	return _methodField->content();
}

void ClassTemplate::parseMembers()
{
	_varField->parseMembers();
	_methodField->parseMembers();
}

void ClassTemplate::getTemplateTagString(char *buffer,int size)
{
	if (_templateTag == NIL) {
		strcpy_s(buffer,BUFSIZ,"");
	} else {
		_templateTag->getTemplateTagString(buffer,size);
	}
}