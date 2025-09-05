// CustomToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CustomToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CustomToolBar

CustomToolBar::CustomToolBar()
{
}

CustomToolBar::~CustomToolBar()
{
}


BEGIN_MESSAGE_MAP(CustomToolBar, CToolBar)
	//{{AFX_MSG_MAP(CustomToolBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CustomToolBar message handlers

void CustomToolBar::getZoomValue(CString &value)
{
	_zoomBox.getZoomValue(value);
}

void CustomToolBar::setZoomValue(const char *value)
{
	_zoomBox.setZoomValue(value);
}

void CustomToolBar::makeZoomComboBox(CWnd *pFrame,int pos,UINT messageId,CSize size)
{
	CRect rect(-size.cx,-size.cy,0,0);
	_zoomBox.setFrameWnd(pFrame);
	_zoomBox.setMessageId(messageId);
	_zoomBox.Create(WS_CHILD|CBS_DROPDOWN|CBS_AUTOHSCROLL|WS_VSCROLL|CBS_HASSTRINGS,
		rect,this,messageId);
	GetItemRect(pos,rect);
	SetButtonInfo(pos,messageId,TBBS_SEPARATOR,size.cx);
	_zoomBox.SetWindowPos(NULL,
		rect.left,rect.top,0,0,
		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS);
	_zoomBox.SetItemHeight(-1,15);
	_zoomBox.AddString("100");
	_zoomBox.AddString("90");
	_zoomBox.AddString("80");
	_zoomBox.AddString("70");
	_zoomBox.AddString("60");
	_zoomBox.AddString("50");
	_zoomBox.AddString("40");
	_zoomBox.AddString("30");
	_zoomBox.AddString("20");
	_zoomBox.AddString("10");
	_zoomBox.AddString("auto");
	_zoomBox.ShowWindow(SW_SHOW);
}

