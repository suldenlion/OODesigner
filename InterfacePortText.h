// InterfacePortText.h: interface for the InterfacePortText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERFACEPORTTEXT_H__B71DA061_FFD7_11D3_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_INTERFACEPORTTEXT_H__B71DA061_FFD7_11D3_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Text.h"

class InterfacePortText : public Text  
{
	DECLARE_SERIAL(InterfacePortText)
private:
	NodeFigure *_master;
	int _baseXForEditing;
	void adjustXCoord(int newWidth);
public:
	InterfacePortText();
	InterfacePortText(COODView *controller,NodeFigure *master,int ox,int oy,Popup *popup);
	virtual ~InterfacePortText();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* container() {
		return (Figure*)_master;
	}
	virtual BOOL startEdit();
	virtual int insert(char* keypressed);
	virtual BOOL delChar();
	virtual BOOL delCharBack();
	virtual BOOL delLine();
	virtual void bye();
};

#endif // !defined(AFX_INTERFACEPORTTEXT_H__B71DA061_FFD7_11D3_AED4_00A0C9BA6734__INCLUDED_)
