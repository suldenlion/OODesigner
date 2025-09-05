// CollaborationMultiObject.h: interface for the CollaborationMultiObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLABORATIONMULTIOBJECT_H__B2E94021_D3D2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_COLLABORATIONMULTIOBJECT_H__B2E94021_D3D2_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CollaborationObject.h"

class CollaborationMultiObject : public CollaborationObject  
{
	DECLARE_SERIAL(CollaborationMultiObject)
private:
	Line *_line1;
	Line *_line2;
	Line *_line3;
	Line *_line4;
	void recalcDecorationsCoord();
	void drawDecoLines();
	void clearDecoLines();
public:
	CollaborationMultiObject();
	CollaborationMultiObject(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual ~CollaborationMultiObject();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void modifyWidthMinus(int dx,int index);
	virtual void modifyWidthPlus(int dx,int index);
	virtual void modifyHeight(int dy,int index);
	virtual void bye();
	virtual void setSpecificDataMembers();
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void draw(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void getAdditionalExcludeRects(ExcludeRectList *pList);
};

#endif // !defined(AFX_COLLABORATIONMULTIOBJECT_H__B2E94021_D3D2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
