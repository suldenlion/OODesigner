#ifndef _RESIZEGLOBALDATA_H
#define _RESIZEGLOBALDATA_H

#define CX_BORDER       1
#define CY_BORDER       1

class ResizeGlobalData {
public:
	BOOL    bWin4;
    int         cxBorder2, cyBorder2;
    COLORREF clrBtnFace, clrBtnShadow, clrBtnHilite;
    COLORREF clrBtnText, clrWindowFrame;
    HCURSOR hcurWait, hcurArrow, hcurSizeNS, hcurSizeWE;
    HBRUSH  hbrBtnHilite, hbrBtnShadow;
public:
     ResizeGlobalData();                 // constructor does the initialization automatically
    virtual ~ResizeGlobalData();
	void UpdateSysColors();
};

#endif