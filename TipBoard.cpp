// TipBoard.cpp : implementation file
//

#include "stdafx.h"
#include "TipString.h"
#include "OOD.h"
#include "TipBoard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int getRandom(int low,int high);

#define TEXT_FONT_SIZE	(19)
/////////////////////////////////////////////////////////////////////////////
// TipBoard

TipBoard::TipBoard()
{
	_index = 0;
}

TipBoard::~TipBoard()
{
}


BEGIN_MESSAGE_MAP(TipBoard, CWnd)
	//{{AFX_MSG_MAP(TipBoard)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void TipBoard::loadBitmap(UINT id)
{
	_background.LoadBitmap(id);
}

void TipBoard::setIndex()
{
	_index = getRandom(0,NOFTIPS);

	while (_index >= 0) {
		if (tip_str[_index][0] == '\0') {
			_index++;
			return;
		} else {
			_index--;
		}
	}
}

void TipBoard::setNextIndex() 
{
	while(tip_str[_index][0] != '\0') _index++;

	if (tip_str[_index+1][0] == '\0') _index = 1;
	else _index++;
}

/////////////////////////////////////////////////////////////////////////////
// TipBoard message handlers

void TipBoard::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC backDC;
	backDC.CreateCompatibleDC(&dc);
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
	CRect rectClient;
	GetClientRect(&rectClient);

	backDC.SelectObject(&_background);
	dc.BitBlt(0,0,rectClient.right,rectClient.bottom,&backDC,0,0,SRCCOPY);

	CFont font;
	font.CreateFont(26,0,0,0,
			FW_BOLD,FALSE,
			FALSE,FALSE,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Times New Roman");
	CFont *oldFont = dc.SelectObject(&font);
	dc.TextOut(60,14,"Did you know...",strlen("Did you know..."));
	dc.SelectObject(oldFont);

	CFont textFont;
	textFont.CreateFont(TEXT_FONT_SIZE,0,0,0,
			FW_NORMAL,FALSE,
			FALSE,FALSE,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Times New Roman");
	oldFont = dc.SelectObject(&textFont);
	
	int x = 60;
	int y = 60;
	int index = _index;
	while(tip_str[index][0] != '\0') {
		dc.TextOut(x,y,tip_str[index],strlen(tip_str[index]));
		y = y + TEXT_FONT_SIZE;
		index++;
	}
	dc.SelectObject(oldFont);
}
