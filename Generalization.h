// Generalization.h: interface for the Generalization class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERALIZATION_H__DCE18486_0625_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_GENERALIZATION_H__DCE18486_0625_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class Generalization : public Connection {
	DECLARE_SERIAL(Generalization)
private:
	BOOL _refinementFlag;
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	Generalization();
	Generalization(COODView *controller,Popup *popup,Line *aLine);
	virtual ~Generalization();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a generalization"; }
	virtual UnsignedLong* whoAreYou();
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC *dcp);
	virtual void clear(CDC* dcp);
	virtual void drawing(CDC* dcp,int dx,int dy);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual Figure* born(Figure* ptr = NIL);
	virtual void setModelSpecificSymbolAll();
	void setRefinement();
	void registerGeneralizationInfo();
	void registerGeneralizationInfoEx();
};

#endif // !defined(AFX_GENERALIZATION_H__DCE18486_0625_11D3_AC44_00008610434C__INCLUDED_)
