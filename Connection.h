// Connection.h: interface for the Connection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTION_H__9C23B743_01AE_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_CONNECTION_H__9C23B743_01AE_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Lines.h"

class Connection : public Lines {
	DECLARE_SERIAL(Connection)
private:
	BOOL _movedFlag;
	int nOfVisitedLinesFromANode();
	void boundaryLineCheck();
	BOOL tuplePointsContainedInNodeFigures();
	BOOL tuplePointsConnectedAnyLine();
	BOOL isBoundOnOneObject();
	BOOL severalLinesOnNodeFigureBoundary();
	void setOrientForObsoleteLines();
	BOOL connectedToOnlyOneNodeFigure(NodeFigure *leader);
	BOOL containJointPointIn(NodeFigure *nodeFigure,LineNodeList *lines);
	void getPreferedPointOnNodeFigureVertex(int &preferedX,int &preferedY,NodeFigure *nodeFigure);
	LineNode* extendLineToNodeFigure(int whichSide,ConnectionInfoTuple *aTuple,
								LineNode *aNode,NodeFigure *aNodeFigure);
protected:
	BOOL _symbolMoveFlag;
	TwoPointFigure *_symbol;
	ConnectionText *_text;
	NodeFigureList *_nodeFigures;
	CITList *_infoTuples;
	LineNodeList *_activeLines;
	int _nOfDeltaList;
	CPoint _deltaList[3];
protected:
	Connection(COODView *controller,Popup* popup,Line *aLine);
	virtual void resetMark();
	virtual BOOL ifAllConstraintSatisfied(NodeFigure *nodeFocus);
	virtual void tailorEndLines(NodeFigure *lastNode);
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
	virtual void doAcompanySymbol(NodeFigure *leader);
	virtual void clearSymbolIfFirstLine();
	void clearActiveLines();
	ConnectionInfoTuple* findTheNearestTuple(int x,int y,BOOL includeFirstTuple);
public:
	Connection();
	virtual ~Connection();
	virtual void Serialize(CArchive& ar);
	virtual void clearLists();
	virtual BOOL valid(NodeFigure *);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual BOOL checkEntries(CRgn*);
	virtual void minMaxXY();
	virtual BOOL checkInRegion(CRgn* someregion);
	virtual void getMinMaxXY(int &minX,int &minY,int &maxX,int &maxY);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void clear(CDC* dcp);
	virtual BOOL onEnter(int x,int y);
	virtual void drawing(CDC* dcp,int dx,int dy);
	virtual void comeOn(CDC* dcp,int dx,int dy);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual Figure* born(Figure* ptr = NIL);
	virtual void letsGo(NodeFigure *leader);
	virtual void epilog(BOOL abortionFlag = FALSE);
	virtual void resizeProlog(NodeFigure* aNode = NIL);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void setController(COODView *ptr);
	virtual void setModelSpecificSymbolAll();
	virtual void setHotXYUsingDelta(int ox,int oy,int dx,int dy);
	virtual void continueDraw();
	virtual void bye();
	virtual void deleteFocusObject();
	virtual void popup(CPoint* event,BOOL = FALSE);
	virtual void setTextPosition(int d1,int d2,int d3);
	virtual BOOL wantToResize(int &x,int &y);
	virtual BOOL isNeighborConnection(Figure *node);
	virtual BOOL isLinearConnection(BOOL abortionFlag);
	virtual CPoint *collectTuplePoints(int &nPoints);
	virtual BOOL isSelfConnectionAllowable();
	virtual void tailorEndLinesAll();
	virtual void extendToNodeFigure(NodeFigure *aNodeFigure);
	virtual void resetOneLineTextIfObsolete(Text *text);
	virtual char *connectionClassName() { return "a connection"; }
	virtual BOOL containedWithin(int x1,int y1,int x2,int y2);
	virtual BOOL tryToDeleteOneLineSegment(NodeFigure *aNodeFigure);
	void setConnectionMovedFlag(BOOL flag) {
		_movedFlag = flag;
	}
	void letsGoWithBucket(NodeFigure *leader);
	void initializeForMoveProlog();
	int getBoundaryLineOrient(int x,int y);
	BOOL abortDraw(BOOL printMsgFlag=TRUE);
	BOOL stopDraw(CPoint point,NodeFigure *nodeFocus);
	NodeFigureList *nodeFigures();
	void remove(NodeFigure *nodeFigure);
	void insert(NodeFigure *nodeFigure);
	void replaceNodeFigurePtr(NodeFigure *from,NodeFigure *to);
	BOOL amISource(NodeFigure *ptr);
	BOOL amISink(NodeFigure *ptr);
	ConnectionText* selectOrCreateText();
	OneLineText *selectOrCreateRoleName(int x,int y);
	OneLineText *selectOrCreateMultiplicity(int x,int y);
	QualificationText *selectOrCreateQualification(int x,int y);
	void removeFromTupleList(Text *text);
	BOOL tryToDeleteOneLineSegment();
	CITList *infoTuples() { return _infoTuples; }
	LineNodeList *activeLines() { return _activeLines; }
	void setText(ConnectionText *text) { _text = text; }
	ConnectionText *getText() { return _text; }
	BOOL hasRelationshipYet(char *major,char *minor);
};

#endif // !defined(AFX_CONNECTION_H__9C23B743_01AE_11D3_AC44_00008610434C__INCLUDED_)
