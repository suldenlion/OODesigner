// CollaborationObject.h: interface for the CollaborationObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLABORATIONOBJECT_H__57FE27E1_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_COLLABORATIONOBJECT_H__57FE27E1_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditableFigure.h"

#define COLLABORATION_OBJECT_INIT_WIDTH	(100)
#define XGAP_COLLABORATION_OBJECT		(10)
#define YGAP_COLLABORATION_OBJECT		(7)

class CollaborationObject : public EditableFigure  
{
	DECLARE_SERIAL(CollaborationObject)
private:
	CollaborationObjectMessageText *_selfMessageText;
	BOOL _selfDelegationFlag;
	BOOL _canDoSelfDelegation;
	void drawSelfDelegation(CDC *dcp);
	void clearSelfDelegation();
public:
	CollaborationObject();
	CollaborationObject(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual ~CollaborationObject();
	virtual void Serialize(CArchive& ar);
	void setMessageText(CollaborationObjectMessageText *text) {
		_selfMessageText = text;
	}
	void resetDelegationFlag() {
		_selfDelegationFlag = FALSE;
	}
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC *dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual void clear(CDC* dcp);
	virtual void modifyWidthMinus(int dx,int index);
	virtual void modifyWidthPlus(int dx,int index);
	virtual void bye();
	virtual BOOL onEnter(int x,int y);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void setController(COODView *ptr);
	virtual void popup(CPoint* event,BOOL = FALSE);
	virtual void deleteFocusObject();
	BOOL canDoSelfDelegation() {
		return _canDoSelfDelegation;
	}
	CollaborationObjectMessageText* setSelfDelegation();
};

#endif // !defined(AFX_COLLABORATIONOBJECT_H__57FE27E1_CDC2_11D3_BBC8_00A0C9BA6734__INCLUDED_)
