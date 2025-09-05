// ExcludeRect.h: interface for the ExcludeRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCLUDERECT_H__D477C93F_E3D1_4656_9843_32B74025CD00__INCLUDED_)
#define AFX_EXCLUDERECT_H__D477C93F_E3D1_4656_9843_32B74025CD00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ExcludeRect : public CObject  
{
	Figure *_figurePtr;
	CRect _rect;
public:
	ExcludeRect(Figure *ptr,int x1,int y1,int x2, int y2);
	virtual ~ExcludeRect();
	Figure *figurePtr() { return _figurePtr; }
	CRect *rectPtr() { return &_rect; }
};

#endif // !defined(AFX_EXCLUDERECT_H__D477C93F_E3D1_4656_9843_32B74025CD00__INCLUDED_)
