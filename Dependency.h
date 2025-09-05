// Dependency.h: interface for the Dependency class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEPENDENCY_H__9FC36303_056E_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_DEPENDENCY_H__9FC36303_056E_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class Dependency : public Connection {
	DECLARE_SERIAL(Dependency)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	Dependency();
	Dependency(COODView *controller,Popup *popup,Line *aLine);
	virtual ~Dependency();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a dependency"; }
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC *dcp);
	virtual void clear(CDC* dcp);
	virtual void drawing(CDC* dcp,int dx,int dy);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void setModelSpecificSymbolAll();
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	void registerDependencyInfo();
	void registerDependencyInfoEx();
};

#endif // !defined(AFX_DEPENDENCY_H__9FC36303_056E_11D3_AC44_00008610434C__INCLUDED_)
