// Aggregation.h: interface for the Aggregation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGGREGATION_H__DCE18487_0625_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_AGGREGATION_H__DCE18487_0625_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class Aggregation : public Connection {
	DECLARE_SERIAL(Aggregation)
	BOOL _compositionFlag;
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	Aggregation();
	Aggregation(COODView *controller,Popup *popup,Line *aLine);
	virtual ~Aggregation();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a aggregation"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual void draw(CDC* dcp);
	virtual void setModelSpecificSymbolAll();
	void setComposition();
	void registerAggregationInfo();
	void registerAggregationInfoEx();
};

#endif // !defined(AFX_AGGREGATION_H__DCE18487_0625_11D3_AC44_00008610434C__INCLUDED_)
