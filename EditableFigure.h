// EditableFigure.h: interface for the EditableFigure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITABLEFIGURE_H__9C23B744_01AE_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_EDITABLEFIGURE_H__9C23B744_01AE_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NodeFigure.h"

#define INIT_WIDTH	(100)

class EditableFigure : public NodeFigure {
	DECLARE_SERIAL(EditableFigure)
protected:
	int _initWidth;
	int _emptyGapX;
	int _moreGapAtTop;
	int _gapX;
	int _gapY;
	BOOL _modifiedFlag;
	SlaveryTextList *_texts;
	LineList *_separators;
protected:
	EditableFigure();
	EditableFigure(COODView *controller);
	virtual void Serialize(CArchive& ar);
	void findCoordToClear(int lineDX,int index,
		int &x1,int &y1,int &x2,int &y2,int &maxW,int &newW);
	int textMaxWidth(int skip = -1);
	void modifyWidth(int x2);
public:
	virtual ~EditableFigure();
	virtual void setFocus(int x = -OODMAXINT, int y = -OODMAXINT);
	virtual void draw(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual void drawBoundary(CDC* dcp);
	virtual void drawBoundaryEx(CDC* dcp);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void modifyWidthMinus(int dx,int index);
	virtual void modifyWidthPlus(int dx,int index);
	virtual void modifyHeight(int dy,int index);
	virtual Figure* born(Figure* ptr = NIL);
	virtual void bye();
	virtual BOOL startEdit();
	virtual BOOL needCentering();
	virtual void setController(COODView *ptr);
	virtual SlaveryText *nextText(SlaveryText* currentText);
	SlaveryText *prevText(SlaveryText* currentText);
	void setModifiedFlag(BOOL flag) {
		_modifiedFlag = flag;
	}
	int getX1ForCentering();
	int widthForCentering();
	int getName(char *buf,int bufSize);
	void setXY2FromContent();
};

#endif // !defined(AFX_EDITABLEFIGURE_H__9C23B744_01AE_11D3_AC44_00008610434C__INCLUDED_)
