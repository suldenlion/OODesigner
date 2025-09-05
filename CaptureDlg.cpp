// CaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "CaptureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CaptureDlg dialog


CaptureDlg::CaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CaptureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CaptureDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CaptureDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CaptureDlg, CDialog)
	//{{AFX_MSG_MAP(CaptureDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CaptureDlg message handlers

int CaptureDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	_userRect = CRect(0,0,GetSystemMetrics(SM_CXMAXTRACK),GetSystemMetrics(SM_CYMAXTRACK));
	MoveWindow(_userRect);

	CDC imageDC;
	CDC screenDC;

	screenDC.CreateDC("DISPLAY",NULL,NULL,NULL);
	BOOL succ = imageDC.CreateCompatibleDC(&screenDC);
	if (!succ) return -1;

	succ = _bitmap.CreateCompatibleBitmap(&screenDC,_userRect.Width(),_userRect.Height());
	if (!succ) return -1;

	imageDC.SelectObject(&_bitmap);
	succ = imageDC.BitBlt(0,0,_userRect.Width(),_userRect.Height(),
		&screenDC,
		_userRect.TopLeft().x,_userRect.TopLeft().y,SRCCOPY);
	if (!succ) return -1;

	return 0;
}

void CaptureDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	CDC aDC;
	aDC.CreateCompatibleDC(&dc);
	aDC.SelectObject(&_bitmap);
	dc.BitBlt(0,0,GetSystemMetrics(SM_CXMAXTRACK),GetSystemMetrics(SM_CYMAXTRACK),
				&aDC,0,0,SRCCOPY);
}

void CaptureDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);

	CRect size(point.x,point.y,point.x,point.y);
	CRectTracker aTracker(&size,CRectTracker::hatchedBorder);
	aTracker.TrackRubberBand(this,point);

	CDC imageDC;
	CDC screenDC;

	screenDC.CreateDC("DISPLAY",NULL,NULL,NULL);
	BOOL succ = imageDC.CreateCompatibleDC(&screenDC);
	if (!succ) {
		EndDialog(IDCANCEL);
		return;
	}

	succ = resultBitmap.CreateCompatibleBitmap(&screenDC,
		abs(aTracker.m_rect.Width()),abs(aTracker.m_rect.Height()));
	if (!succ) {
		EndDialog(IDCANCEL);
		return;
	}
	
	int sx = aTracker.m_rect.TopLeft().x;
	if (sx >= aTracker.m_rect.BottomRight().x) sx = aTracker.m_rect.BottomRight().x;
	int sy = aTracker.m_rect.TopLeft().y;
	if (sy >= aTracker.m_rect.BottomRight().y) sy = aTracker.m_rect.BottomRight().y;

	imageDC.SelectObject(&resultBitmap);
	succ = imageDC.BitBlt(0,0,abs(aTracker.m_rect.Width()),abs(aTracker.m_rect.Height()),
		&screenDC,sx,sy,SRCCOPY);

	if (!succ) {
		EndDialog(IDCANCEL);
		return;
	}

	EndDialog(IDOK);
}

BOOL CaptureDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CaptureDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
	EndDialog(IDCANCEL);
}

void CaptureDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
	EndDialog(IDCANCEL);
}
