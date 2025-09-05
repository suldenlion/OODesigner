/* Lines.h */

#ifndef _LINES_H
#define _LINES_H

#include "Classes.h"
#include "Figure.h" // Generalization

class Lines : public Figure {
	DECLARE_SERIAL(Lines)
private:
	CPoint *collectEndPoints(int &nPoints);
	LineNode *removeCycle();
	BOOL cutLineAt(int x,int y,Line *focus,LineNode *focusNode);
protected : // data members
	LineNodeList* _lines;
	LineNode* _focusNode;
	Figure* _focus; 
	// ORDINARY or STRAIGHT
	int _type;
	// SOLID or DASHED	
	int _style;
	int _lastx;
	int _lasty;
	BOOL _moveAllFlag;
	void setStyle(int style);
	void remake(CPoint endPoints[],int nPoints);
	virtual void resetMark();
	void resetFlags();
	void epilogForMovingAndResizing();
	void epilogForLinearConnection();
	void epilogForLinearAndSelfConnection();
	BOOL checkIfThereIsOverlapLine();
	LineNode *findNodeFor(int x,int y);
	void removeLineNode(LineNode *focusNode);
	LineNode *findABoundaryLineNode(int &where);
	LineNode *findNextLineNode(LineNode *from,int &where);
	void localDoBreak();
	void localDoDetach();
	BOOL localDoAttach(int popupX,int popupY,Line *focus,LineNode *focus_node,BOOL originalattach = FALSE);
public : // member functions
	virtual ~Lines();
	Lines();
	Lines(COODView *controller,Popup* popup,int type,Line *line = NIL);
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void bornFocus();
	virtual void center(int& x,int& y);
	virtual void last(int& x,int& y);
	virtual void minMaxXY();
	virtual void getMinMaxXY(int &,int &,int &,int &);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void setInCanvas(BOOL flag = TRUE);
	virtual int setHotXY(int x,int y);
	virtual BOOL wantToResize(int& x,int& y);
	virtual BOOL checkInRegion(CRgn* someregion);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void clear(CDC* dcp);
	virtual void drawing(CDC* dcp,int dx,int dy);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual BOOL onEnter(int x,int y);
	virtual Figure *focus();
	virtual void setFocus(int x = -OODMAXINT, int y = -OODMAXINT);
	virtual void resetFocus();
	virtual int nOfFigures();
	virtual BOOL checkNear(int x,int y);
	virtual void epilog(BOOL skipflag = FALSE);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void resizeProlog(NodeFigure* aNode = NIL);
	virtual void setXY2(int x,int y);
	virtual void setController(COODView *ptr);
	virtual BOOL isLinearConnection(BOOL abortionFlag);
	virtual CPoint *collectTuplePoints(int &nPoints);
	virtual BOOL containedWithin(int x1,int y1,int x2,int y2);
	virtual void setMoveAllFlag(BOOL flag) { _moveAllFlag = flag; }
	BOOL moveAllFlag() { return _moveAllFlag; }
	void resetHotXY();
	LineNodeList *lines() { return _lines; }
	LineNode *node(Line *line);
	LineNode *insertALine(Line *newline,BOOL focusflag);
	void calcForkPoint(int popupX,int popupY,int &newx,int &newy);
	void retrySetFocus(int &x,int &y);
	void remake();
	void resetHeadType();
	void insertALine(Line *aline);
	void redrawForArrow();
	int &style();
	void deleteOneLine();
	void doBreak();
	void doDetach();
	void doAttach();
	void makeArrow(int dir_type);
	BOOL isForkable(int x,int y,int &newX,int &newY);
	void getHotXY(int& hotX,int& hotY);
};

#endif
