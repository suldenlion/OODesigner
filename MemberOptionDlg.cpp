// MemberOptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "MemberOptionDlg.h"
#include "KtgMacro.h"
#include "ClassTextLine.h"
#include "ClassContent.h"
#include "COODClassDoc.h"
#include "ClassFigureLibrary.h"
#include "ClassPropDlg.h"
#include "CMainFrame.h"
#include "CResizableTreeBar.h"
#include "CommentDlg.h"
#include "MethodBodyDlg.h"
#include "COODCommonDoc.h"
#include "COODView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MemberOptionDlg dialog
IMPLEMENT_DYNAMIC(MemberOptionDlg,CDialog)

MemberOptionDlg::MemberOptionDlg(UINT id,CWnd* pParent /*=NULL*/)
	: CDialog(id, pParent)
{
	_currentLine = NIL;
	_classContent = NIL;
	_modifiedFlag = FALSE;
	//{{AFX_DATA_INIT(MemberOptionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MemberOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MemberOptionDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void MemberOptionDlg::loadButtonState(CButton *aButton,BOOL state)
{
	if (state == TRUE) {
		aButton->SetCheck(1);
	} else {
		aButton->SetCheck(0);
	}
} 

void MemberOptionDlg::writeDefaultValue(CEdit *defaultValueEdit,CStringList &theValue)
{
	int nOfLines = defaultValueEdit->GetLineCount();

	theValue.RemoveAll();
	if (nOfLines == 0) {
		return;
	} else if (nOfLines == 1) {
		char lineBuffer[BUFSIZ];
		int n = defaultValueEdit->GetLine(nOfLines-1,lineBuffer,BUFSIZ);
		if (n <= 0) return;
		lineBuffer[n] = '\0';
		theValue.AddTail(lineBuffer);
		return;
	}

	// 우선 실제 의미 있는 라인 수를 센다. 뒷 부분의 빈 라인 삭제...
	int nOfActualLine = nOfLines;

	while (nOfLines > 0) {
		char lineBuffer[BUFSIZ];
		int n = defaultValueEdit->GetLine(nOfLines-1,lineBuffer,BUFSIZ);
		if (n > 0) {
			break;
		}
		nOfLines--;
	}
	
	// 다시 한번 boundary condition 경우
	if (nOfLines == 0) {
		return;
	} else if (nOfLines == 1) {
		char lineBuffer[BUFSIZ];
		int n = defaultValueEdit->GetLine(nOfLines-1,lineBuffer,BUFSIZ);
		if (n <= 0) return;
		lineBuffer[n] = '\0';
		theValue.AddTail(lineBuffer);
		return;
	}

	int i = 0;
	for (i = 0; i < nOfLines; i++) {
		char lineBuffer[BUFSIZ];
		int n = defaultValueEdit->GetLine(i,lineBuffer,BUFSIZ);
		if (n < 0 || n >= BUFSIZ) {
			WarningMsg("Some line in this initial value is too long.\r\nThe line is truncated.");
			lineBuffer[BUFSIZ] = '\0';
		} else {
			lineBuffer[n] = '\0';
		}
		theValue.AddTail(lineBuffer);
	}
}

void MemberOptionDlg::loadDefaultValue(CEdit *defaultValueEdit,CStringList &theValue)
{
	if (theValue.IsEmpty()) {
		return;
	}
	POSITION pos = theValue.GetHeadPosition();
	while (pos != NULL) {
		CString aLine = theValue.GetNext(pos);
		defaultValueEdit->ReplaceSel(aLine);
		if (pos != NULL) 
			defaultValueEdit->ReplaceSel("\r\n");
	} 
	defaultValueEdit->SetSel(0);
	Invalidate();
}

void MemberOptionDlg::writeType(CComboBox *typeCombo,CString &typeString)
{
	typeCombo->GetWindowText(typeString);
}

void MemberOptionDlg::loadType(CComboBox *typeCombo,CString &typeString)
{
	typeCombo->ResetContent();

	typeCombo->AddString("char");
	typeCombo->AddString("double");
	typeCombo->AddString("float");
	typeCombo->AddString("int");
	typeCombo->AddString("short");
	typeCombo->AddString("signed");
	typeCombo->AddString("unsigned");
	typeCombo->AddString("void");
	typeCombo->SetWindowText(typeString);
}

void MemberOptionDlg::loadStereotype(CString &stereotype)
{
	stereotype = _classContent->stereotype();
}

void MemberOptionDlg::loadInnerClassOf(CString &innerClassOf)
{
	innerClassOf = _classContent->outerClassName();
}

void MemberOptionDlg::loadVisibilityForClass(CString &visibility)
{
	int vis = _classContent->visibility();
	if (vis == PUBLIC_ID) {
		visibility = "public";
	} else if (vis == PROTECTED_ID) {
		visibility = "protected";
	} else if (vis == PRIVATE_ID) {
		visibility = "private";
	} else {
		visibility = "default";
	}
}

void MemberOptionDlg::loadVisibilityForMember(CString &visibility)
{
	int vis = _currentLine->visibility();
	if (vis == PUBLIC_ID) {
		visibility = "public";
	} else if (vis == PROTECTED_ID) {
		visibility = "protected";
	} else if (vis == PRIVATE_ID) {
		visibility = "private";
	} else {
		visibility = "default";
	}
}

BOOL MemberOptionDlg::writeButtonState(CButton *aButton,BOOL &state)
{
	if (state == TRUE && aButton->GetCheck() != 0) {
		return FALSE;
	} else if (state == FALSE && aButton->GetCheck() == 0) {
		return FALSE;
	}

	if (aButton->GetCheck() == 0) {
		state = FALSE;
	} else {
		state = TRUE;
	}
	return TRUE;
} 

BOOL MemberOptionDlg::writeStereotype(CString &stereotype)
{
	if (_classContent == NIL) return FALSE;

	CString stype = _classContent->stereotype();
	if (stype.CompareNoCase(stereotype) == 0) {
		return FALSE;
	}

	_classContent->setStereotype(stereotype);
	return TRUE;
}

BOOL MemberOptionDlg::writeInnerClassOf(CString &innerClassOf)
{
	if (_classContent == NIL) return FALSE;

	CString oname = _classContent->outerClassName();
	if (oname.CompareNoCase(innerClassOf) == 0) {
		return FALSE;
	}

	_classContent->setOuterClassName(innerClassOf);
	return TRUE;
}

BOOL MemberOptionDlg::writeVisibilityForMember(CString &visibility)
{
	if (_currentLine == NIL) return FALSE;

	int vis = _currentLine->visibility();
	if ((vis == PUBLIC_ID && visibility.CompareNoCase("public") == 0) ||
		(vis == PROTECTED_ID && visibility.CompareNoCase("protected") == 0) ||
		(vis == PRIVATE_ID && visibility.CompareNoCase("private") == 0) ||
		(vis == DEFAULT_ID && visibility.CompareNoCase("default") == 0)) {
		return FALSE;
	}

	_currentLine->writeVisibility(visibility);
	return TRUE;
}

BOOL MemberOptionDlg::writeVisibilityForClass(CString &visibility)
{
	if (_classContent == NIL) return FALSE;

	int vis = _classContent->visibility();
	if ((vis == PUBLIC_ID && visibility.CompareNoCase("public") == 0) ||
		(vis == PROTECTED_ID && visibility.CompareNoCase("protected") == 0) ||
		(vis == PRIVATE_ID && visibility.CompareNoCase("private") == 0) ||
		(vis == DEFAULT_ID && visibility.CompareNoCase("default") == 0)) {
		return FALSE;
	}

	_classContent->writeVisibility(visibility);
	return TRUE;
}

BEGIN_MESSAGE_MAP(MemberOptionDlg, CDialog)
	//{{AFX_MSG_MAP(MemberOptionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MemberOptionDlg message handlers

void MemberOptionDlg::refreshAllViews()
{
	CWnd *pParent = GetParent();
	if (!pParent->IsKindOf(RUNTIME_CLASS(ClassPropDlg))) return;
	ClassPropDlg *parentDlg = (ClassPropDlg*)pParent;
	CString className = parentDlg->className();
	CString packageName = parentDlg->packageName();
	COODView *theView = parentDlg->pView();
	if (theView == NIL) return;
	CDocument *pDoc = theView->GetDocument();
	if (pDoc == NULL) return;
	if (pDoc->IsKindOf(RUNTIME_CLASS(COODCommonDoc))) {
		((COODCommonDoc*)pDoc)->replaceFieldTextContent(className,NIL,theView);
	} else {
		theAppPtr->pCOODClassDoc->getClassFiguresLibrary()->replaceFieldTextContent(packageName,className,NIL,theView);
		theAppPtr->pCOODClassDoc->SetModifiedFlag();
		theAppPtr->pCOODClassDoc->UpdateAllViews((CView *)NIL);
		mainFramePtr->m_wndTreeBar.replaceClass(packageName,className,_classContent);
	}
	theAppPtr->deactivateMemberPropertyDlgs();
}

BOOL MemberOptionDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pMsg->message == WM_KEYDOWN && (LOWORD(pMsg->wParam) == VK_RETURN)) {
		CWnd *focusWnd = GetFocus();
		if (focusWnd != NULL && focusWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
			if ((focusWnd->GetStyle() & ES_MULTILINE) != 0) {
				return CDialog::PreTranslateMessage(pMsg);
			}
		}
		if (!IsKindOf(RUNTIME_CLASS(CommentDlg)) &&
			!IsKindOf(RUNTIME_CLASS(MethodBodyDlg)))
			return -1;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
