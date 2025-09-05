// TemplateClassTag.h: interface for the TemplateClassTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMPLATECLASSTAG_H__02A2F1C1_F376_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_TEMPLATECLASSTAG_H__02A2F1C1_F376_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditableFigure.h"

#define TEMPLATE_TAG_INIT_WIDTH		(50)
#define XGAP_TEMPLATE_TAG			(3)
#define YGAP_TEMPLATE_TAG			(1)

class TemplateClassTag : public EditableFigure  
{
	DECLARE_SERIAL(TemplateClassTag)
private:
	ClassTemplate *_classPointer;
public:
	TemplateClassTag();
	TemplateClassTag(COODView *controller,ClassTemplate *classPointer,int ox,int oy,int deltaV,Popup *popup);
	virtual ~TemplateClassTag();
	virtual void Serialize(CArchive& ar);
	virtual Figure* born(Figure* ptr = NIL);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual SlaveryText *nextText(SlaveryText *currentText);
	virtual BOOL needCentering();
	TemplateClassTagText *tagText();
	ClassTemplate *classPointer();
	void getTemplateTagString(char *buffer,int size);
};

#endif // !defined(AFX_TEMPLATECLASSTAG_H__02A2F1C1_F376_11D3_BBC8_00A0C9BA6734__INCLUDED_)
