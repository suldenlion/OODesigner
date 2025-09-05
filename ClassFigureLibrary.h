// ClassFigureLibrary.h: interface for the ClassFigureLibrary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSFIGURELIBRARY_H__9A14A721_0F1D_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CLASSFIGURELIBRARY_H__9A14A721_0F1D_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "List.h"

class ClassFigureLibrary : public List  
{
public:
	DECLARE_SERIAL(ClassFigureLibrary)
public:
	ClassFigureLibrary();
	virtual ~ClassFigureLibrary();
	virtual void Serialize(CArchive& ar);
	FigureList *figures(CString &packageName);
	int zoomRatioX(CString& packageName);
	int zoomRatioY(CString& packageName);
	void setZoomRatioX(CString& packageName,int zoomX);
	void setZoomRatioY(CString& packageName,int zoomY);
	int originX(CString& packageName);
	int originY(CString& packageName);
	void setOriginX(CString& packageName,int x);
	void setOriginY(CString& packageName,int y);
	FigureLibrary *getPackage(CString &packageName);
	void deletePackage(CString &packageName);
	FigureLibrary *addPackage(CString &packageName);
	FigureLibrary* clearPackage(CString &packageName);
	BOOL hasClassTemplate(CString &className,CString &packageName);
	void replaceFieldTextContent(CString &packageName,CString &className,ClassTemplate *aClass,COODView *aView = NIL);
	BOOL hasRelationshipYet(UnsignedLong *identity,char *major,char *minor,CString &packName); 
	void insert(FigureLibrary* ptr,int tag = 0);
	BOOL inList(FigureLibrary* ptr);
	void remove(FigureLibrary* ptr,int tag = 0);
	FigureLibrary* getFirst();
	FigureLibrary* getNext();
};

#endif // !defined(AFX_CLASSFIGURELIBRARY_H__9A14A721_0F1D_11D4_AED4_00A0C9BA6734__INCLUDED_)
