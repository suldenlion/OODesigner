// Association.h: interface for the Association class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSOCIATION_H__7B5343E1_E228_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_ASSOCIATION_H__7B5343E1_E228_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class Association : public Connection  
{
	DECLARE_SERIAL(Association)
private:
	ClassTemplate *_associationClassPtr;
	BOOL _canDoAssociationClass;
	void makeTernarySymbol();
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	Association();
	Association(COODView *controller,Popup *popup,Line *aLine);
	virtual ~Association();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "an association"; }
	virtual void setModelSpecificSymbolAll();
	virtual void draw(CDC* dcp);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual void doAcompanySymbol(NodeFigure *leader);
	virtual void clearSymbolIfFirstLine();
	virtual void popup(CPoint* event,BOOL = FALSE);
	virtual void resizeProlog(NodeFigure* aNode = NIL);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual BOOL isSelfConnectionAllowable() { return TRUE; }
	void setAssociationClassPtr(ClassTemplate *associationClassPtr) {
		_associationClassPtr = associationClassPtr;
	}
	void getCenterPosition(int &cx,int &cy);
	BOOL getJointPoint(CPoint &aPoint);
	BOOL canDoAssociationClass() {
		return _canDoAssociationClass;
	}
};

#endif // !defined(AFX_ASSOCIATION_H__7B5343E1_E228_11D3_BBC8_00A0C9BA6734__INCLUDED_)
