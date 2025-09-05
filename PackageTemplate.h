// PackageTemplate.h: interface for the PackageTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKAGETEMPLATE_H__D5BAD0C2_C4F8_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_PACKAGETEMPLATE_H__D5BAD0C2_C4F8_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditableFigure.h"

#define PACKAGETEMPLATE_INIT_WIDTH	(80)
#define XGAP_PACKAGETEMPLATE		(15)
#define YGAP_PACKAGETEMPLATE		(15)

class PackageTemplate : public EditableFigure  
{
	DECLARE_SERIAL(PackageTemplate)
	// �� ����Ÿ ������� NodeFigure Ŭ������ ���� �����Ǳ� ������
	// �� Ŭ�������� destruction ��ų �ʿ䰡 ����.
	Line *_hatLeft;
	Line *_hatUp;
	Line *_hatRight;
public:
	PackageTemplate();
	PackageTemplate(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual ~PackageTemplate();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual void draw(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual Figure* born(Figure* ptr = NIL);
	virtual void setSpecificDataMembers();
	virtual void getAdditionalExcludeRects(ExcludeRectList *pList);
	virtual void popup(CPoint* event,BOOL = FALSE);
};

#endif // !defined(AFX_PACKAGETEMPLATE_H__D5BAD0C2_C4F8_11D3_BBC8_00A0C9BA6734__INCLUDED_)
