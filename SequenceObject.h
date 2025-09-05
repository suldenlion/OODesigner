// SequenceObject.h: interface for the SequenceObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCEOBJECT_H__BF9456A4_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SEQUENCEOBJECT_H__BF9456A4_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "EditableFigure.h"

#define SEQUENCE_OBJECT_INIT_WIDTH	(80)
#define XGAP_SEQUENCE_OBJECT		(10)
#define YGAP_SEQUENCE_OBJECT		(7)
#define ACTIVATION_BAR_WIDTH		(10)

class SequenceObject : public EditableFigure  
{
	DECLARE_SERIAL(SequenceObject)
private:
	int _resizeUpperBound;
	int _resizeLowerBound;
	Line *_lifeLane;
	Figure *_hiddenFocus;
	ActivationBarList *_activationBars;
	BOOL _killSignFlag;
	BOOL _canDoKillSign;
	void showBaseLine(CDC *dcp,int baseY);
	void setResizeUpperBound();
	void setResizeBoundsForActivation(ActivationBar *aBar);
	void setMoveBoundsForActivation(ActivationBar *aBar);
	int getNewActivationBarHeight(int topY);
	void drawKillSign(CDC *dcp);
public:
	SequenceObject();
	SequenceObject(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual ~SequenceObject();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC *dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual void clear(CDC* dcp);
	virtual void bye();
	virtual BOOL onEnter(int x,int y);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void setController(COODView *ptr);
	virtual BOOL checkInRegion(CRgn* someregion);
	virtual void drawDots(CDC* dcp);
	virtual void eraseDots(CDC* dcp);
	virtual BOOL wantToResize(int &x,int &y);
	virtual void drawing(CDC*,int dx,int dy);
	virtual void epilog(BOOL skipflag = FALSE);
	virtual void popup(CPoint* event,BOOL = FALSE);
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void deleteFocusObject();
	virtual BOOL adjustLine(Line *line,BOOL startPoint);
	virtual BOOL containedWithin(int x1,int y1,int x2,int y2);
	virtual void setBackground(COLORREF c);
	void makeNewActivationBar(int x,int y);
	void processKillSign();
	BOOL canDoKillSign() {
		return _canDoKillSign;
	}
	SequenceSelfDelegation* createSelfDelegation(COODView *controller,int ox,int oy,Popup *popup);
	Line *lifeLane() { return _lifeLane; }
};

#endif // !defined(AFX_SEQUENCEOBJECT_H__BF9456A4_E5FE_11D3_BBC8_00A0C9BA6734__INCLUDED_)
