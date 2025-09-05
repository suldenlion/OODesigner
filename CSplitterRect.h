#ifndef _CSPLITTERRECT_H
#define _CSPLITTERRECT_H

#define SPLITTER_VERT   1
#define SPLITTER_HORZ   2

class CSplitterRect : public CObject
{
public:
        CRect   m_rect;         // rectangle
        char    m_type;         // Vertical or Horizontal
        int             m_nPos;         // position at which it was inserted
                                        // ie points to pane immediately following it.
	CSplitterRect(int type, const RECT & rect);
	void Draw(CDC *pDC);
#ifdef _DEBUG
	void Dump( CDumpContext& dc ) const;
#endif
};

#endif