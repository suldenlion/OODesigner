// InterfacePortText.cpp: implementation of the InterfacePortText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "InterfacePortText.h"
#include "NodeFigure.h"
#include "TextContent.h"
#include "COODView.h"
#include "PackageLibrary.h"
#include "COODClassDoc.h"
#include "ClassContent.h"
#include "ClassFigureLibrary.h"
#include "CMainFrame.h"
#include "CResizableTreeBar.h"
#include "RelationshipInfoTupleList.h"
#include "ClassTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(InterfacePortText,Text,1)

InterfacePortText::InterfacePortText()
: Text()
{
	_master = NIL;
	_autoDelete = FALSE;
}

InterfacePortText::InterfacePortText(COODView *controller,NodeFigure *master,int ox,int oy,Popup *popup)
: Text(controller,ox,oy,popup)
{
	_master = master;
	setMaxLines(1);
	_autoDelete = FALSE;
}

InterfacePortText::~InterfacePortText()
{
	_master = NIL;
}

void InterfacePortText::Serialize(CArchive& ar)
{
	Text::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (LONG) _baseXForEditing << _master;
	} else {
		ar >> (LONG&) _baseXForEditing >> _master;
	}
}

Figure* InterfacePortText::born(Figure* ptr)
{
	InterfacePortText *copied;
	if (ptr == NIL) {
		copied = new InterfacePortText(NIL,NIL,0,0,NIL);
	} else {
		copied = (InterfacePortText *)ptr;
	}
	return (Text::born((Figure *)copied));
}

UnsignedLong *InterfacePortText::whoAreYou()
{
	return IAMINTERFACEPORTTEXT; 
}

BOOL InterfacePortText::startEdit()
{
	Text::startEdit();
	_baseXForEditing = _x2.x;
	return TRUE;
}

void InterfacePortText::adjustXCoord(int newWidth)
{
	invalidate();
	_x1.x = _baseXForEditing-newWidth;
}

int InterfacePortText::insert(char* keypressed)
{
	int lineDX = Text::insert(keypressed);
	if (lineDX == -1) return 0;
	if (_content->otherLinesMaxWidth() < lineDX) {
		adjustXCoord(lineDX);
	}
	return lineDX;
}

BOOL InterfacePortText::delChar()
{
	if (_content->valueAt(_cursorX,_cursorY) == '\0') return TRUE;
	if (Text::delChar()) return TRUE;
	CRect tmp(getX1()-10,getY1()-1,getX2()+10,getY2()+1);
	_controller->invalidateRect(&tmp,TRUE);
	int lineDX = _content->otherLinesMaxWidth();
	adjustXCoord(lineDX);
	return FALSE;
}

BOOL InterfacePortText::delCharBack()
{
	if (_cursorX == 0) return TRUE;
	if (Text::delCharBack()) return TRUE;
	CRect tmp(getX1()-10,getY1()-1,getX2()+10,getY2()+1);
	_controller->invalidateRect(&tmp,TRUE);
	int lineDX = _content->otherLinesMaxWidth();
	adjustXCoord(lineDX);
	return FALSE;
}

BOOL InterfacePortText::delLine()
{
	if (textHeight() == 1 && _content->valueAt(0,0) == '\0') {
		 return TRUE;
	}
	if (Text::delLine()) {
		adjustXCoord(0);
		return TRUE;
	}
	int lineDX = _content->otherLinesMaxWidth();
	adjustXCoord(lineDX);
	return FALSE;
}

void InterfacePortText::bye()
{
	Text::bye();
	if (_controller->GetDocument()->IsEmbedded()) return;
	if (theAppPtr->pCOODClassDoc == NIL) return;

	char interfaceName[BUFSIZ];
	getName(interfaceName,BUFSIZ);

	if (strlen(interfaceName) == 0) {
		return;
	}

	CString packageName = _controller->viewTitleWithOutExtension;
	CString className = interfaceName;

	PackageLibrary *allClassContents = theAppPtr->pCOODClassDoc->getAllClassContents();
	ClassContent *classContent = 
		allClassContents->getClassContentFor(className);
	if (classContent != NIL) return;
	mainFramePtr->m_wndTreeBar.insertClass(packageName,className,NIL);
	classContent = 
		allClassContents->registerClassContent(packageName,className,NIL);
	classContent->setStereotype("Interface");
	char superClassName[BUFSIZ];
	((ClassTemplate *)_master)->getName(superClassName,BUFSIZ);
	theAppPtr->pCOODClassDoc->getGeneralizationLibrary()->registerRelationshipInfo(interfaceName,superClassName,"Refinement");
	theAppPtr->pCOODClassDoc->SetModifiedFlag();
}
