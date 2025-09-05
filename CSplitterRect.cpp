#include "stdafx.h"
#include "CSplitterRect.h"
#include "ResizeGlobalData.h"

extern ResizeGlobalData afxData;

CSplitterRect::CSplitterRect(int type, const RECT & rect)
// in-line constructor moved out of line as ASSERT causes problems for .DEF file
// (end up with a symbol that contains THIS_FILE, and hence a path name, so we can't
// by portable across directories).
//-----------------------------------------------------------------------------------
{
//TRACE0("CSplitterRect::CSplitterRect\n");
	ASSERT(type == SPLITTER_VERT || type == SPLITTER_HORZ);
    m_rect = rect; m_type = type;
}; 

//-----------------------------------------------------------------------------------
void CSplitterRect::Draw(CDC *pDC)
//-----------------------------------------------------------------------------------
{
//TRACE0("CSplitterRect::Draw\n");
    CRect rect = m_rect;
    switch (m_type)
    {
        case SPLITTER_VERT:
        	rect.left ++;
        	pDC->FillSolidRect(rect.left, rect.top, 1, rect.Height(), afxData.clrBtnFace);
        	rect.left ++;
        	pDC->FillSolidRect(rect.left, rect.top, 1, rect.Height(), afxData.clrBtnHilite);

        	rect.right --;
        	pDC->FillSolidRect(rect.right, rect.top, 1, rect.Height(), afxData.clrWindowFrame);
        	rect.right --;
        	pDC->FillSolidRect(rect.right, rect.top, 1, rect.Height(), afxData.clrBtnShadow);
        	break;


        case SPLITTER_HORZ:
            rect.top ++;
            pDC->FillSolidRect(rect.left, rect.top, rect.Width(), 1, afxData.clrBtnFace);
            rect.top ++;
            pDC->FillSolidRect(rect.left, rect.top, rect.Width(), 1, afxData.clrBtnHilite);

            rect.bottom --;
            pDC->FillSolidRect(rect.left, rect.bottom, rect.Width(), 1, afxData.clrWindowFrame);
            rect.bottom --;
            pDC->FillSolidRect(rect.left, rect.bottom, rect.Width(), 1, afxData.clrBtnShadow);
            break;

         default:
            ASSERT(FALSE);
            break;
 	}
}

#ifdef _DEBUG

void CSplitterRect::Dump( CDumpContext& dc ) const
{
	dc << "pos = " << m_nPos;
	dc << (m_type == SPLITTER_HORZ ? " Horz" : " Vert");
}

#endif

