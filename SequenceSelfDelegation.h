// SequenceSelfDelegation.h: interface for the SequenceSelfDelegation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCESELFDELEGATION_H__C8F8A1E1_ED3A_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SEQUENCESELFDELEGATION_H__C8F8A1E1_ED3A_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class SequenceSelfDelegation : public Connection  
{
	DECLARE_SERIAL(SequenceSelfDelegation)
private:
	int _moveUpperBound;
	int _moveLowerBound;
	BOOL _activationBarFlag;
	void drawActivationBar(CDC *dcp);
public:
	SequenceSelfDelegation();
	SequenceSelfDelegation(COODView *controller,SequenceObject *theObject,int x,int y,Popup *popup);
	virtual ~SequenceSelfDelegation();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a self delegation"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void epilog(BOOL skipflag = FALSE);
	virtual BOOL wantToResize(int &x,int &y);
	virtual void comeOn(CDC* dcp,int dx,int dy);
	virtual void tailorEndLinesAll();
	virtual void letsGo(NodeFigure *leader);
	virtual void draw(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void drawBoundary(CDC* dcp);
	virtual BOOL tryToDeleteOneLineSegment(NodeFigure *aNodeFigure);
	ConnectionText* selectOrCreateText();
};

#endif // !defined(AFX_SEQUENCESELFDELEGATION_H__C8F8A1E1_ED3A_11D3_BBC8_00A0C9BA6734__INCLUDED_)
