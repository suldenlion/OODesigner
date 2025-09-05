// ExcludeRect.cpp: implementation of the ExcludeRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ExcludeRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcludeRect::ExcludeRect(Figure *ptr,int x1,int y1,int x2, int y2)
{
	_figurePtr = ptr;
	_rect.SetRect(x1,y1,x2,y2);
}

ExcludeRect::~ExcludeRect()
{

}
