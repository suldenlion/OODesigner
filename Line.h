/* Line.h */

#ifndef _LINE_H
#define _LINE_H

#include "TwoPointFigure.h" // Generalization

#define ATNOWHERE (0)
#define ATBEFORE  (1)
#define ATAFTER   (2)

#define ONEDIRECTION	(1)
#define BIDIRECTION		(2)

#define	NODIR 		(0x00)
#define	NORMAL_DIR 	(0x01)
#define	INVERT_DIR 	(0x02)
#define	BIDIR 		(0x03)

#define	HEADNONE 	(0)
/* 채워진 화살표 */
#define	HEADARROW1 	(1)
/* 실선으로된 화살표 */
#define HEADARROW2	(2)
/* 빈 삼각형 약간 큰거 */
#define HEADARROW3	(3)
/* 반 삼각형 채워진 화살표 */  
#define HEADARROW4	(4)

#define	ORDINARY 	(1)
#define	STRAIGHT 	(2)
#define	UNDEFINED 	(0)

#define	NORTH 		(1)
#define	EAST 		(2)
#define SOUTH		(3)
#define WEST		(4)

#define FORKTOLERANCE (REGIONLENGTH)

#define RESETORIENT (-1)

class Line : public TwoPointFigure {
	DECLARE_SERIAL(Line)
private : 
	void fillFgArrow(CDC* dcp,int x,int y,int dx1,int dy1,int dx2,int dy2);
	void fillFgHalfArrow(CDC* dcp,int x,int y,int dx1,int dy1,int dx2,int dy2);
	void fillBgArrow(CDC* dcp,int x,int y,int dx1,int dy1,int dx2,int dy2);
	void drawLineArrow(CDC* dcp,int x,int y,int dx1,int dy1,int dx2,int dy2);
	void drawHead(CDC* dcp);
	void drawTail(CDC* dcp);
protected : // member functions
	// direction of arrow
	int _direct; 
	// ORDINARY or STRAIGHT
	int _type; 
	// SOLID or DASHED
	int _style; 
	// UNDEFINED, NORTH, EAST
	int _orient; 
	int _head;
	double _slope;
	int _thickness;
	int _absoluteFollowPos;
	// flag used for resizing
	void makeRegion(int x,int y,int w,int h,CRgn *sourceClipRgn);
	void adjustDirs(Line *second);
public : // member functions
	virtual ~Line();
	Line();
	Line(COODView *controller,int x,int y,Popup* popup,int type);
	Line(COODView *controller,int x1,int y1,int x2,int y2,Popup* popup,int type);
	virtual void Serialize(CArchive& ar);
	virtual void clear(CDC* dcp);
	virtual BOOL checkNear(int x,int y);
	virtual void draw(CDC* dcp);
	virtual void following(CDC* dcp,int newx,int newy);
	virtual void drawing(CDC* dcp,int dx,int dy);
	virtual BOOL wantToResize(int &x,int &y);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC *dcp);
	virtual int setHotXY(int x,int y);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	void setAbsoluteFollowPos(int pos) { _absoluteFollowPos = pos; }
	void setSuperHotXY(int x,int y); 
	int resizeCoord(int x,int y);
	int resizeCoordDXY(int dx,int dy);
	void makeSmallRegion();
	virtual BOOL checkMinWH();
	virtual BOOL isObsolete();
	virtual void swapPoints();
	void drawingCoord(int dx,int dy);
	void setThickness(int val);
	int resizing(CDC* dcp,int dx,int dy);
	int whereToFollow();
	BOOL setFollowing(int x,int y);
	BOOL setFollowing2(int x,int y);
	BOOL setFollowing(int x,int y,int orient);
	int whereToMeet(int x,int y);
	int whereToMeet(Line *line);
	BOOL doesMeet(int x,int y);
	BOOL doesCross(Line *that);
	BOOL checkToMerge(Line *);
	void invertDir();
	int length();
	double slope();
	void merge(Line *node);
	void toggleHead(BOOL uniflag,int popupX = 0,int popupY = 0);
	int orient();
	int &head();
	int &style();
	void setDir(int dir,int headtype);
	Line* calcForkPoint(int popupX,int popupY,int &newx,int &newy,BOOL &swaped);
	void calcForkPoint(int popupX,int popupY,int &newx,int &newy);
	Line* calcBreakPoint(int popupX,int popupY,int &newx,int &newy,BOOL &swaped);
	BOOL checkIfSame(Line *line);
	int setOrient(int orient = RESETORIENT);
	BOOL incl(Line *aline,int &x,int &y);
	BOOL incl(int x,int y);
	void findTriangleStartPoints(int endX,int endY,int &startX,int &startY,int length);
	void findDiamondEndCorners(int &endX,int &endY,int &startX,int &startY,int length,int offset);
	int type();
	void setArrow(int popupX,int popupY);
	static int invertOrient(int orient);
};

#endif
