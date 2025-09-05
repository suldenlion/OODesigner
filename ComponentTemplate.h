// ComponentTemplate.h: interface for the ComponentTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPONENTTEMPLATE_H__BC2C6EC4_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_COMPONENTTEMPLATE_H__BC2C6EC4_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditableFigure.h"

#define COMPONENTTEMPLATE_INIT_WIDTH	(120)
#define XGAP_COMPONENTTEMPLATE			(20)
#define YGAP_COMPONENTTEMPLATE			(10)

class ComponentTemplate : public EditableFigure  
{
	DECLARE_SERIAL(ComponentTemplate)
	Circle *_port1;
	Box *_port2;
	Box *_port3;
public:
	ComponentTemplate();
	ComponentTemplate(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual void Serialize(CArchive& ar);
	virtual ~ComponentTemplate();
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void draw(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void setBackground(COLORREF c);
	virtual void getAdditionalExcludeRects(ExcludeRectList *pList);
	virtual void setSpecificDataMembers();
};

#endif // !defined(AFX_COMPONENTTEMPLATE_H__BC2C6EC4_D6F0_11D3_BBC8_00A0C9BA6734__INCLUDED_)
