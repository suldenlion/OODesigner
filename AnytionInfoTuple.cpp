// AnytionInfoTuple.cpp: implementation of the AnytionInfoTuple class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "AnytionInfoTuple.h"
#include "TupleText.h"
#include "QualificationText.h"
#include "Connection.h"
#include "NodeFigure.h"
#include "Line.h"

#define PROPER_DISTANCE	(60)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(AnytionInfoTuple,ConnectionInfoTuple,1)

AnytionInfoTuple::AnytionInfoTuple()
: ConnectionInfoTuple()
{
	_roleName = NIL;
	_multiplicity = NIL;
	_qualification = NIL;
}

AnytionInfoTuple::AnytionInfoTuple(NodeFigure* config,int x,int y)
: ConnectionInfoTuple(config,x,y)
{
	_roleName = NIL;
	_multiplicity = NIL;
	_qualification = NIL;
}

AnytionInfoTuple::AnytionInfoTuple(AnytionInfoTuple* from)
: ConnectionInfoTuple(from)
{
	if (from->_roleName != NIL) {
		_roleName = (TupleText *)_roleName->born();
	}
	if (from->_multiplicity != NIL) {
		_multiplicity = (TupleText *)_multiplicity->born();
	}
	if (from->_qualification != NIL) {
		_qualification = (QualificationText *)_qualification->born();
	}
}

AnytionInfoTuple::~AnytionInfoTuple()
{
	if (_multiplicity != NIL) {
		delete _multiplicity;
		_multiplicity = NIL;
	}
	if (_roleName != NIL) {
		delete _roleName;
		_roleName = NIL;
	}
	if (_qualification != NIL) {
		delete _qualification;
		_qualification = NIL;
	}
}

void AnytionInfoTuple::Serialize(CArchive& ar)
{
	ConnectionInfoTuple::Serialize(ar);
	if (ar.IsStoring()) {
		ar << _multiplicity << _roleName << _qualification;
	} else {
		ar >> _multiplicity >> _roleName >> _qualification;
	}
}

void AnytionInfoTuple::setTupleText(TupleText *aText)
{
	int whichText = aText->getWhichText();
	if (whichText == ROLE_NAME_ID) {
		_roleName = aText;
	} else if (whichText == MULTIPLICITY_ID) {
		_multiplicity = aText;
	} else if (whichText == QUALIFICATION_ID) {
		_qualification = (QualificationText *)aText;
	}
}

int AnytionInfoTuple::determineTuplePointSide(Connection *connection)
{
	TwoPointFigure *shape = _nodeFigurePtr->shape();
	int side = SOUTH;
	int x = _x.get(); int y = _y.get();
	int sx1 = shape->getX1(); int sy1 = shape->getY1();
	int sx2 = shape->getX2(); int sy2 = shape->getY2();
	if (x == sx1 && y == sy1) {
		int orient = connection->getBoundaryLineOrient(x,y);
		if (orient == NORTH) {
			side = NORTH;
		} else {
			side = WEST;
		}
	} else if (x == sx2 && y == sy1) {
		int orient = connection->getBoundaryLineOrient(x,y);
		if (orient == NORTH) {
			side = NORTH;
		} else {
			side = EAST;
		}
	} else if (x == sx2 && y == sy2) {
		int orient = connection->getBoundaryLineOrient(x,y);
		if (orient == NORTH) {
			side = SOUTH;
		} else {
			side = EAST;
		}
	} else if (x == sx1 && y == sy2) {
		int orient = connection->getBoundaryLineOrient(x,y);
		if (orient == NORTH) {
			side = SOUTH;
		} else {
			side = WEST;
		}
	} else {
		side = shape->onWhichSide(_x.get(),_y.get());
	}
	return side;
}

OneLineText *AnytionInfoTuple::selectOrCreateRoleName(Connection *connection)
{
	if (_roleName != NIL) return _roleName;
	COODView *controller = connection->controller();
	if (controller == NIL) return NIL;
	int side = determineTuplePointSide(connection);
	if (side == NORTH) {
		_roleName = new TupleText(controller,connection,
			_x.get()+7,_y.get()-20,theAppPtr->theEditPopup);
	} else if (side == EAST) {
		_roleName = new TupleText(controller,connection,
			_x.get()+7,_y.get()+6,theAppPtr->theEditPopup);
	} else if (side == SOUTH) {
		_roleName = new TupleText(controller,connection,
			_x.get()-40,_y.get()+6,theAppPtr->theEditPopup);
	} else if (side == WEST) {
		_roleName = new TupleText(controller,connection,
			_x.get()-40,_y.get()-20,theAppPtr->theEditPopup);
	} else {
		_roleName = new TupleText(controller,connection,
			_x.get()-40,_y.get()+6,theAppPtr->theEditPopup);
	}
	_roleName->setTuplePtr(this);
	_roleName->setWhichText(ROLE_NAME_ID);
	return _roleName;
}

OneLineText *AnytionInfoTuple::selectOrCreateMultiplicity(Connection *connection)
{
	if (_multiplicity != NIL) return _multiplicity;
	COODView *controller = connection->controller();
	if (controller == NIL) return NIL;
	int side = determineTuplePointSide(connection);
	if (side == NORTH) {
		_multiplicity = new TupleText(controller,connection,
			_x.get()-30,_y.get()-20,theAppPtr->theEditPopup);
	} else if (side == EAST) {
		_multiplicity = new TupleText(controller,connection,
			_x.get()+7,_y.get()-20,theAppPtr->theEditPopup);
	} else if (side == SOUTH) {
		_multiplicity = new TupleText(controller,connection,
			_x.get()+7,_y.get()+6,theAppPtr->theEditPopup);
	} else if (side == WEST) {
		_multiplicity = new TupleText(controller,connection,
			_x.get()-30,_y.get()+6,theAppPtr->theEditPopup);
	} else {
		_multiplicity = new TupleText(controller,connection,
			_x.get()+7,_y.get()+6,theAppPtr->theEditPopup);
	}
	_multiplicity->setTuplePtr(this);
	_multiplicity->setWhichText(MULTIPLICITY_ID);
	return _multiplicity;
}

QualificationText *AnytionInfoTuple::selectOrCreateQualification(Connection *connection)
{
	if (_qualification != NIL) return _qualification;
	COODView *controller = connection->controller();
	if (controller == NIL) return NIL;
	int side = determineTuplePointSide(connection);
	if (side == NORTH ||
		side == EAST ||
		side == SOUTH ||
		side == WEST) {
		_qualification = new QualificationText(controller,connection,side,
			_x.get(),_y.get(),theAppPtr->theEditPopup);
	} else {
		return NIL;
	}
	_qualification->setTuplePtr(this);
	_qualification->setWhichText(QUALIFICATION_ID);
	return _qualification;
}

void AnytionInfoTuple::locateTupleTextOnProperPosition(Connection *connection)
{
	int side = determineTuplePointSide(connection);
	int cx,cy;
	if (_roleName != NIL) {
		_roleName->center(cx,cy);
		int dx = abs(cx-getX());
		int dy = abs(cy-getY());
		if (dx > PROPER_DISTANCE || dy > PROPER_DISTANCE ||
			_nodeFigurePtr->contains(cx,cy)) {
			if (side == NORTH) {
				_roleName->_x1.set(_x.get()+7);
				_roleName->_y1.set(_y.get()-20);
			} else if (side == EAST) {
				_roleName->_x1.set(_x.get()+7);
				_roleName->_y1.set(_y.get()+6);
			} else if (side == SOUTH) {
				_roleName->_x1.set(_x.get()-40);
				_roleName->_y1.set(_y.get()+6);
			} else if (side == WEST) {
				_roleName->_x1.set(_x.get()-40);
				_roleName->_y1.set(_y.get()-20);
			} else {
				_roleName->_x1.set(_x.get()-40);
				_roleName->_y1.set(_y.get()+6);
			}
			_roleName->recalcCoordFromXY1();
		}
	}
	if (_multiplicity != NIL) {
		_multiplicity->center(cx,cy);
		int dx = abs(cx-getX());
		int dy = abs(cy-getY());
		if (dx > PROPER_DISTANCE || dy > PROPER_DISTANCE ||
			_nodeFigurePtr->contains(cx,cy)) {
			if (side == NORTH) {
				_multiplicity->_x1.set(_x.get()-30);
				_multiplicity->_y1.set(_y.get()-20);
			} else if (side == EAST) {
				_multiplicity->_x1.set(_x.get()+7);
				_multiplicity->_y1.set(_y.get()-20);
			} else if (side == SOUTH) {
				_multiplicity->_x1.set(_x.get()+7);
				_multiplicity->_y1.set(_y.get()+6);
			} else if (side == WEST) {
				_multiplicity->_x1.set(_x.get()-30);
				_multiplicity->_y1.set(_y.get()+6);
			} else {
				_multiplicity->_x1.set(_x.get()+7);
				_multiplicity->_y1.set(_y.get()+6);
			}
			_multiplicity->recalcCoordFromXY1();
		}
	}
	if (_qualification != NIL) {
		if (side == NORTH ||
			side == EAST ||
			side == SOUTH ||
			side == WEST) {
				_qualification->setWhichSide(side);
				_qualification->recalcCoordFromTuplePointXY(_x.get(),_y.get());
		}
	}
}

void AnytionInfoTuple::moveCoord(int dx,int dy)
{
	ConnectionInfoTuple::moveCoord(dx,dy);
	if (_roleName != NIL) {
		_roleName->moveCoord(dx,dy);
	}
	if (_multiplicity != NIL) {
		_multiplicity->moveCoord(dx,dy);
	}
	if (_qualification != NIL) {
		_qualification->moveCoord(dx,dy);
	}
}

void AnytionInfoTuple::draw(CDC* dcp)
{
	if (_roleName != NIL) {
		_roleName->draw(dcp);
	}
	if (_multiplicity != NIL) {
		_multiplicity->draw(dcp);
	}
	if (_qualification != NIL) {
		_qualification->draw(dcp);
	}
}

void AnytionInfoTuple::makeRegion(CRgn *sourceClipRgn)
{
	if (_roleName != NIL) {
		_roleName->makeRegion(sourceClipRgn);
	}
	if (_multiplicity != NIL) {
		_multiplicity->makeRegion(sourceClipRgn);
	}
	if (_qualification != NIL) {
		_qualification->makeRegion(sourceClipRgn);
	}
}

void AnytionInfoTuple::resetRegion()
{
	if (_roleName != NIL) {
		_roleName->resetRegion();
	}
	if (_multiplicity != NIL) {
		_multiplicity->resetRegion();
	}
	if (_qualification != NIL) {
		_qualification->resetRegion();
	}
}

void AnytionInfoTuple::releaseRegion()
{
	if (_roleName != NIL) {
		_roleName->releaseRegion();
	}
	if (_multiplicity != NIL) {
		_multiplicity->releaseRegion();
	}
	if (_qualification != NIL) {
		_qualification->releaseRegion();
	}
}

void AnytionInfoTuple::move(CDC* dcp,int dx,int dy)
{
	ConnectionInfoTuple::moveCoord(dx,dy);
	if (_roleName != NIL) {
		_roleName->move(dcp,dx,dy);
	}
	if (_multiplicity != NIL) {
		_multiplicity->move(dcp,dx,dy);
	}
	if (_qualification != NIL) {
		_qualification->move(dcp,dx,dy);
	}
}

void AnytionInfoTuple::drawDots(CDC* dcp)
{
	if (_roleName != NIL) {
		_roleName->drawDots(dcp);
	}
	if (_multiplicity != NIL) {
		_multiplicity->drawDots(dcp);
	}
	if (_qualification != NIL) {
		_qualification->drawDots(dcp);
	}
}

void AnytionInfoTuple::eraseDots(CDC* dcp)
{
	if (_roleName != NIL) {
		_roleName->eraseDots(dcp);
	}
	if (_multiplicity != NIL) {
		_multiplicity->eraseDots(dcp);
	}
	if (_qualification != NIL) {
		_qualification->eraseDots(dcp);
	}
}

void AnytionInfoTuple::clear(CDC *dcp)
{
	if (_roleName != NIL) {
		_roleName->eraseDots(dcp);
	}
	if (_multiplicity != NIL) {
		_multiplicity->eraseDots(dcp);
	}
	if (_qualification != NIL) {
		_qualification->eraseDots(dcp);
	}
}

void AnytionInfoTuple::setInCanvas(BOOL flag)
{
	if (_roleName != NIL) {
		_roleName->setInCanvas(flag);
	}
	if (_multiplicity != NIL) {
		_multiplicity->setInCanvas(flag);
	}
	if (_qualification != NIL) {
		_qualification->setInCanvas(flag);
	}
}

void AnytionInfoTuple::setController(COODView *ptr)
{
	ConnectionInfoTuple::setController(ptr);
	if (_roleName != NIL) {
		_roleName->setController(ptr);
	}
	if (_multiplicity != NIL) {
		_multiplicity->setController(ptr);
	}
	if (_qualification != NIL) {
		_qualification->setController(ptr);
	}
}

Figure *AnytionInfoTuple::onEnter(int x,int y)
{
	if (_roleName != NIL &&
		_roleName->onEnter(x,y)) {
		return _roleName;
	}
	if (_multiplicity != NIL &&
		_multiplicity->onEnter(x,y)) {
		return _multiplicity;
	}
	if (_qualification != NIL &&
		_qualification->onEnter(x,y)) {
		return _qualification;
	}
	return NIL;
}

void AnytionInfoTuple::drawBoundary(CDC *dcp)
{
	if (_roleName != NIL) {
		_roleName->drawBoundary(dcp);
	}
	if (_multiplicity != NIL) {
		_multiplicity->drawBoundary(dcp);
	}
	if (_qualification != NIL) {
		_qualification->drawBoundary(dcp);
	}
}

void AnytionInfoTuple::removeFromTuple(Figure *fig)
{
	if (_roleName == fig) {
		_roleName = NIL;
	}
	if (_multiplicity == fig) {
		_multiplicity = NIL;
	}
	if (_qualification == fig) {
		_qualification = NIL;
	}
}