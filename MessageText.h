// MessageText.h: interface for the MessageText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGETEXT_H__AD4AE781_D32E_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_MESSAGETEXT_H__AD4AE781_D32E_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectionText.h"
#include "Line.h"

#define ARROW_AT_TOP		(NORTH)
#define ARROW_AT_RIGHT		(EAST)
#define ARROW_AT_BOTTOM		(SOUTH)
#define ARROW_AT_LEFT		(WEST)

class MessageText : public ConnectionText  
{
	DECLARE_SERIAL(MessageText)
private:
	int _arrowAt;
	int _arrowDir;
	Line *_arrow;
	void recalcArrowCoord();
	void clearArrow();
public:
	MessageText();
	MessageText(COODView *controller,Connection *connectionPtr,int ox,int oy,Popup *popup);
	virtual ~MessageText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void epilog(BOOL skipflag = FALSE);
	virtual void draw(CDC* dcp);
	virtual void bye();
	virtual void clear(CDC* dcp);
	virtual void setController(COODView *ptr);
	void setArrowAt(int place) { _arrowAt = place; }
	void shiftArrow();
	void invertArrow();
};

#endif // !defined(AFX_MESSAGETEXT_H__AD4AE781_D32E_11D3_BBC8_00A0C9BA6734__INCLUDED_)
