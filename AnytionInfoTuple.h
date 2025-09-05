// AnytionInfoTuple.h: interface for the AnytionInfoTuple class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANYTIONINFOTUPLE_H__116AD082_F509_11D3_BBC8_D43900002E32__INCLUDED_)
#define AFX_ANYTIONINFOTUPLE_H__116AD082_F509_11D3_BBC8_D43900002E32__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "ConnectionInfoTuple.h"

class AnytionInfoTuple : public ConnectionInfoTuple  
{
	DECLARE_SERIAL(AnytionInfoTuple)
private:
	TupleText *_roleName;
	TupleText *_multiplicity;
	QualificationText *_qualification;
public:
	AnytionInfoTuple();
	AnytionInfoTuple(NodeFigure* config,int x,int y);
	AnytionInfoTuple(AnytionInfoTuple* from);
	virtual ~AnytionInfoTuple();
	virtual void Serialize(CArchive& ar);
	OneLineText *selectOrCreateRoleName(Connection *connection);
	OneLineText *selectOrCreateMultiplicity(Connection *connection);
	QualificationText *selectOrCreateQualification(Connection *connection);
	void setTupleText(TupleText *aText);
	int determineTuplePointSide(Connection *connection);
	virtual void locateTupleTextOnProperPosition(Connection *connection);
	virtual void moveCoord(int dx,int dy);
	virtual void draw(CDC* dcp);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void clear(CDC* dcp);
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual void setController(COODView *ptr);
	virtual Figure* onEnter(int x,int y);
	virtual void drawBoundary(CDC* dcp);
	virtual void removeFromTuple(Figure *fig);
};

#endif // !defined(AFX_ANYTIONINFOTUPLE_H__116AD082_F509_11D3_BBC8_D43900002E32__INCLUDED_)
