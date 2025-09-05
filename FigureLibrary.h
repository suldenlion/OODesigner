// FigureLibrary.h: interface for the FigureLibrary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIGURELIBRARY_H__9A14A720_0F1D_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_FIGURELIBRARY_H__9A14A720_0F1D_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "KtgMacro.h"

class FigureLibrary : public CObject  
{
	DECLARE_SERIAL(FigureLibrary)
private:
	CString _diagramName; // packageName
	FigureList *_figures;
	CStringList _comment;
	int _zoomRatioX;
	int _zoomRatioY;
	int _originX;
	int _originY;
public:
	FigureLibrary();
	FigureLibrary(CString &packageName);
	virtual ~FigureLibrary();
	virtual void Serialize(CArchive& ar);
	BOOL hasRelationshipYet(UnsignedLong *identity,char *major,char *minor,CString &packName); 
	void replaceFieldTextContent(CString &packageName,CString &className,ClassTemplate *aClass,COODView *aView = NIL);
	BOOL hasClassTemplate(CString &className,CString &packageName);
	FigureLibrary*  clearPackage();
	CString& packageName() { return _diagramName; }
	FigureList *figures() { return _figures; }
	int zoomRatioX() { return _zoomRatioX; }
	int zoomRatioY() { return _zoomRatioY; }
	void setZoomRatioX(int zoomX) { _zoomRatioX = zoomX; }
	void setZoomRatioY(int zoomY) { _zoomRatioY = zoomY; }
	int originX() { return _originX; }
	int originY() { return _originY; }
	void setOriginX(int x) { _originX = x; }
	void setOriginY(int y) { _originY = y; }
	CStringList *comment() { return &_comment; }
};

#endif // !defined(AFX_FIGURELIBRARY_H__9A14A720_0F1D_11D4_AED4_00A0C9BA6734__INCLUDED_)
