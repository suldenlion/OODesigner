// SimpleConnection.h: interface for the SimpleConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLECONNECTION_H__25252361_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_SIMPLECONNECTION_H__25252361_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define INIT_DX_OF_TEXT_FROM_CENTER	(10)
#define INIT_DY_OF_TEXT_FROM_CENTER	(-10)

#include "Connection.h"

/* 이 클랫의 하위 클래스들은 모두 하나의 라인만을 가질 수 있다. */
class SimpleConnection : public Connection  
{
	DECLARE_SERIAL(SimpleConnection)
protected:
	SimpleConnection();
	SimpleConnection(COODView *controller,Popup* popup,Line *aLine);
	int _dxOfTextFromCenter;
	int _dyOfTextFromCenter;
	void setMyText(int cx,int cy,char *fixedString);
	virtual void tailorEndLines(NodeFigure *lastNode);
	virtual void clearSymbolIfFirstLine();
public:
	virtual ~SimpleConnection();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual void letsGo(NodeFigure *leader);
	virtual void epilog(BOOL skipflag = FALSE);
	virtual void resizeProlog(NodeFigure* aNode = NIL);
	virtual BOOL wantToMove(int,int);
	virtual void setModelSpecificSymbolAll();
	virtual BOOL wantToResize(int &x,int &y);
	virtual void tailorEndLinesAll();
	void setDeltaOfTextFromCenter(int x1OfText,int y1OfText);
	NodeFigure *getTargetNodeForResizing();
};

#endif // !defined(AFX_SIMPLECONNECTION_H__25252361_D023_11D3_BBC8_00A0C9BA6734__INCLUDED_)
