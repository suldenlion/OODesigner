// PropCommonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "PropCommonDlg.h"
#include "KtgMacro.h"
#include "MemberOptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PropCommonDlg dialog
IMPLEMENT_DYNAMIC(PropCommonDlg, TabDlgWithName)

PropCommonDlg::PropCommonDlg(UINT id,CWnd* pParent /*=NULL*/)
	: TabDlgWithName(id, pParent)
{
	_pView = NIL;
	_currentLine = NIL;
	_classContent = NIL;
	_className = _T("");
	_packageName = _T("");
	_languageName = _T("");
	_pStaticClassNameCtrl = NIL;
	//{{AFX_DATA_INIT(PropCommonDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void PropCommonDlg::DoDataExchange(CDataExchange* pDX)
{
	TabDlgWithName::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropCommonDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL PropCommonDlg::ShowWindow(int nCmdShow)
{
	if (nCmdShow == SW_HIDE) {
		clearContents();
		resetCurrentLine();	
	}

	return TabDlgWithName::ShowWindow(nCmdShow);
}


BEGIN_MESSAGE_MAP(PropCommonDlg, TabDlgWithName)
	//{{AFX_MSG_MAP(PropCommonDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropCommonDlg message handlers

void PropCommonDlg::clearContents()
{
    for (int i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        CWnd *aWnd = GetTabWindow(i);
		if (aWnd->IsKindOf(RUNTIME_CLASS(MemberOptionDlg))) {
			((MemberOptionDlg *)aWnd)->clearContents();
		}
    }
}

void PropCommonDlg::resetCurrentLine()
{
	_pView = NIL;
	_currentLine = NIL;
	_classContent = NIL;
	_className = _T("");
	_packageName = _T("");
	_pStaticClassNameCtrl->SetWindowText("No Selection");
    for (int i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        CWnd *aWnd = GetTabWindow(i);
		if (aWnd->IsKindOf(RUNTIME_CLASS(MemberOptionDlg))) {
			((MemberOptionDlg *)aWnd)->resetCurrentLine();
		}
    }
}

void PropCommonDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (_currentLine != NIL) {
		saveToClassTextLine();
		resetCurrentLine();	
	} else if (_classContent != NIL) {
		saveToClassTextLine();
		resetCurrentLine();	
	}
	ShowWindow(SW_HIDE);
}

void PropCommonDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	resetCurrentLine();	
	ShowWindow(SW_HIDE);
}

BOOL PropCommonDlg::saveToClassTextLine()
{
	updateData();
	BOOL repaintFlag = FALSE;
    for (int i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        CWnd *aWnd = GetTabWindow(i);
		if (aWnd->IsKindOf(RUNTIME_CLASS(MemberOptionDlg))) {
			repaintFlag = ((MemberOptionDlg *)aWnd)->writeOptionsToClassTextLine() || repaintFlag;
			repaintFlag = ((MemberOptionDlg *)aWnd)->isModified()  || repaintFlag;
		}
    }
	return repaintFlag;
}

void PropCommonDlg::loadFromClassTextLine()
{
	int i;
    for (i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        CWnd *aWnd = GetTabWindow(i);
		if (aWnd->IsKindOf(RUNTIME_CLASS(MemberOptionDlg))) {
			((MemberOptionDlg *)aWnd)->loadFromClassTextLine(_classContent,_currentLine,_className,_languageName);
		}
    }
    for (i = 0; i < _pTabCtrl->GetItemCount(); i++)
    {
        CWnd *aWnd = GetTabWindow(i);
		if (aWnd->IsKindOf(RUNTIME_CLASS(MemberOptionDlg))) {
			((MemberOptionDlg *)aWnd)->setModifiedFlag(FALSE);
		}
    }
}

