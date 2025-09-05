#include "stdafx.h"
#include "ResizeGlobalData.h"

ResizeGlobalData afxData;
void AFXAPI AfxDeleteObject(HGDIOBJ* pObject);

ResizeGlobalData::ResizeGlobalData()
{
    DWORD dwVersion = ::GetVersion();
	//nWinVer = (LOBYTE(dwVersion) << 8) + HIBYTE(dwVersion);
	//bWin32s = (dwVersion & 0x80000000) != 0;
	bWin4 = (BYTE)dwVersion >= 4;
	
	cxBorder2 = bWin4 ? CX_BORDER*2 : CX_BORDER;
	cyBorder2 = bWin4 ? CY_BORDER*2 : CY_BORDER;

    hbrBtnHilite = NULL;
    hbrBtnShadow = NULL;
    
    hcurWait = ::LoadCursor(NULL, IDC_WAIT);
    hcurArrow = ::LoadCursor(NULL, IDC_ARROW);
    hcurSizeWE = NULL;
    hcurSizeNS = NULL;
		    
	UpdateSysColors();
}


ResizeGlobalData::~ResizeGlobalData()
{
	AfxDeleteObject((HGDIOBJ*)&hbrBtnShadow);
	AfxDeleteObject((HGDIOBJ*)&hbrBtnHilite);
}


void ResizeGlobalData::UpdateSysColors()
{

    clrBtnFace = ::GetSysColor(COLOR_BTNFACE);
    clrBtnShadow = ::GetSysColor(COLOR_BTNSHADOW);
    clrBtnHilite = ::GetSysColor(COLOR_BTNHIGHLIGHT);
    clrBtnText = ::GetSysColor(COLOR_BTNTEXT);
    clrWindowFrame = ::GetSysColor(COLOR_WINDOWFRAME);

    // brushes...
    AfxDeleteObject((HGDIOBJ*)&hbrBtnShadow);
	AfxDeleteObject((HGDIOBJ*)&hbrBtnHilite);
	
    hbrBtnShadow = ::CreateSolidBrush(clrBtnShadow);
	ASSERT(hbrBtnShadow != NULL);
	hbrBtnHilite = ::CreateSolidBrush(clrBtnHilite);
	ASSERT(hbrBtnHilite != NULL);
}

