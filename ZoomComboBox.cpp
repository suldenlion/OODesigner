// ZoomComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "ZoomComboBox.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "CInPlaceFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZoomComboBox

ZoomComboBox::ZoomComboBox()
{
	_pRealMainFrame = NIL;
}

ZoomComboBox::~ZoomComboBox()
{
}

void ZoomComboBox::setFrameWnd(CWnd *pWnd)
{
	_pRealMainFrame = pWnd;
}

BEGIN_MESSAGE_MAP(ZoomComboBox, CComboBox)
	//{{AFX_MSG_MAP(ZoomComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void ZoomComboBox::setMessageId(UINT id)
{
	_messageId = id;
}

/////////////////////////////////////////////////////////////////////////////
// ZoomComboBox message handlers

BOOL ZoomComboBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_RETURN) {
		if (_pRealMainFrame != NIL) {
			::SendMessage(_pRealMainFrame->m_hWnd,WM_COMMAND,_messageId,0);
		}
	}
	return CComboBox::PreTranslateMessage(pMsg);
}

void ZoomComboBox::OnSelchange() 
{
	// TODO: Add your control notification handler code here CComboBox
	SetCurSel(GetCurSel());
	if (_pRealMainFrame != NIL) {
		::SendMessage(_pRealMainFrame->m_hWnd,WM_COMMAND,_messageId,0);
	}
}

void ZoomComboBox::setZoomValue(const char *value)
{
	SetWindowText(value);
}

void ZoomComboBox::getZoomValue(CString &value)
{
	GetWindowText(value);
}

