// FigureLibrary.cpp: implementation of the FigureLibrary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "FigureLibrary.h"
#include "FigureList.h"
#include "Figure.h"
#include "UnsignedLong.h"
#include "ClassTemplate.h"
#include "Generalization.h"
#include "CMainFrame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(FigureLibrary,CObject,1)

FigureLibrary::FigureLibrary()
:CObject()
{
	_figures = new FigureList();
	_diagramName = "";
	_comment.RemoveAll();
	_zoomRatioX = 100;
	_zoomRatioY = 100;
	_originX = 0;
	_originY = 0;
}

FigureLibrary::FigureLibrary(CString &packageName)
:CObject()
{
	_figures = new FigureList();
	_diagramName = packageName;
	_comment.RemoveAll();
	_zoomRatioX = 100;
	_zoomRatioY = 100;
	_originX = 0;
	_originY = 0;
}

void FigureLibrary::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	_comment.Serialize(ar);
	if (ar.IsStoring()) {
		ar << _diagramName << _figures;
		ar << (LONG)_zoomRatioX << (LONG)_zoomRatioY;
		ar << (LONG)_originX << (LONG)_originY;
	} else {
		if (_figures) delete _figures;
		ar >> _diagramName >> _figures;
		ar >> (LONG&) _zoomRatioX >> (LONG&) _zoomRatioY;
		ar >> (LONG&) _originX >> (LONG&) _originY;
	}
}

FigureLibrary::~FigureLibrary()
{
	clearPackage();
	delete _figures;
	_figures = NIL;
}

FigureLibrary* FigureLibrary::clearPackage()
{
	_comment.RemoveAll();
	Figure *aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		aFigure->clearLists();
		aFigure = _figures->getNext();
	}
	aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		delete aFigure;
		aFigure = _figures->getNext();
	}
	_figures->clear();
	return this;
}

BOOL FigureLibrary::hasRelationshipYet(UnsignedLong *identity,char *major,char *minor,CString &packName)
{
	Figure* aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(identity)) {
			Connection *aRelation = (Connection *)aFigure;
			if (aRelation->hasRelationshipYet(major,minor) == TRUE) {
				packName = _diagramName;
				return TRUE;
			}
		}
		aFigure = _figures->getNext();
	}
	return FALSE;
}

BOOL FigureLibrary::hasClassTemplate(CString &className,CString &packageName)
{
	packageName = _diagramName;
	Figure* aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *pClass = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			pClass->getName(buffer,BUFSIZ);
			if (className.CompareNoCase(buffer) == 0) {
				return TRUE;
			} else if (pClass->hasClassNameInInterfacePorts(className)) {
				return TRUE;
			}
		}
		aFigure = _figures->getNext();
	}
	return FALSE;
}

void FigureLibrary::replaceFieldTextContent(CString &packageName,CString &className,ClassTemplate *aClass,COODView *aView)
{
	Figure* aFigure = _figures->getFirst();
	while (aFigure != NIL) {
		if (aFigure->whoAreYou()->equals(IAMCLASSTEMPLATE)) {
			ClassTemplate *pClass = (ClassTemplate *)aFigure;
			char buffer[BUFSIZ];
			pClass->getName(buffer,BUFSIZ);
			if (className.CompareNoCase(buffer) == 0) {
				if (aClass != NIL) {
					pClass->replaceFieldTextContent(aClass,aClass->controller());
				} else {
					pClass->replaceFieldTextContent(aClass,aView);
				}
			}
		}
		aFigure = _figures->getNext();
	}
}

