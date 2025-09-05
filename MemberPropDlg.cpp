// MemberPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "MemberPropDlg.h"
#include "KtgMacro.h"
#include "CMainFrame.h"
#include "ClassTextLine.h"
#include "MemberOptionDlg.h"
#include "CResizableTreeBar.h"
#include "ClassFigureLibrary.h"
#include "COODClassDoc.h"
#include "COODView.h"
#include "ClassContent.h"
#include "Text.h"
#include "ClassPropDlg.h"
#include "CPPMethodPropGeneral.h"
#include "CPPVarPropGeneral.h"
#include "VCPPMethodPropGeneral.h"
#include "VCPPVarPropGeneral.h"
#include "CSharpMethodPropGeneral.h"
#include "CSharpVarPropGeneral.h"
#include "JavaMethodPropGeneral.h"
#include "JavaVarPropGeneral.h"
#include "CommentDlg.h"
#include "MethodBodyDlg.h"
#include "RelationTraverseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MemberPropDlg dialog

// 이 크기는 다이얼로그 상단의 시스템 메뉴 부분을 제외한 부분임
const int MemberPropDlg::ClientMinWidth = 428;
const int MemberPropDlg::ClientMinHeight = 340;

const int MemberPropDlg::MinWidth = 436;
const int MemberPropDlg::MinHeight = 367;

const int MemberPropDlg::BoundaryGapX = 4;
const int MemberPropDlg::BoundaryGapY = 41;

MemberPropDlg::MemberPropDlg(int whichMember,const char* language,CWnd* pParent /*=NULL*/)
	: PropCommonDlg(MemberPropDlg::IDD, pParent)
{
	_index = 0;
	_whichMember = whichMember;
	_languageName = language;

	_generalOption = NIL;
	_commentOption = NIL;
	_methodBodyOption = NIL;

	_initialWidth = 0;
	_initialHeight = 0;
	//{{AFX_DATA_INIT(MemberPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

MemberPropDlg::~MemberPropDlg()
{
	delete _generalOption;
	delete _commentOption;
	delete _methodBodyOption;
}

void MemberPropDlg::DoDataExchange(CDataExchange* pDX)
{
	PropCommonDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MemberPropDlg)
	DDX_Control(pDX, IDOK, m_buttonOKCtrl);
	DDX_Control(pDX, IDCANCEL, m_buttonCancelCtrl);
	DDX_Control(pDX, IDC_BUTTON_PREV, m_buttonPrevCtrl);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_buttonNextCtrl);
	DDX_Control(pDX, IDC_TAB_MEMBER_PROP, m_optionsTab);
	DDX_Control(pDX, IDC_STATIC_CLASS_NAME, m_staticClassNameCtrl);
	DDX_Control(pDX, IDC_EDIT_MEMBER_NAME, m_editMemberNameCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MemberPropDlg, PropCommonDlg)
	//{{AFX_MSG_MAP(MemberPropDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MEMBER_PROP, OnSelchangeTabMemberProp)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnButtonPrev)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MemberPropDlg message handlers

void MemberPropDlg::clearContents()
{
	m_editMemberNameCtrl.SetWindowText("");
	PropCommonDlg::clearContents();
}

BOOL MemberPropDlg::saveToClassTextLine()
{
	BOOL repaintFlag = PropCommonDlg::saveToClassTextLine();

	CString newName;
	m_editMemberNameCtrl.GetWindowText(newName);
	char bufferNew[BUFSIZ];
	Text::strcpyCompact(bufferNew,newName,BUFSIZ);
	if (strlen(bufferNew) > 0) {
		CString orgName = _currentLine->name();
		char bufferOrg[BUFSIZ];
		Text::strcpyCompact(bufferOrg,orgName,BUFSIZ);
		orgName = bufferOrg;
		if (orgName.CompareNoCase(bufferNew) != 0) {
			_currentLine->name() = bufferNew;
			repaintFlag = TRUE;
		}
	}

	m_editMemberNameCtrl.SetWindowText(_currentLine->name());

	if (repaintFlag == TRUE) {
		if (_whichMember == DATA_MEMBER) {
			_currentLine->remakeAsDataMemberString();
			_currentLine->parseAsDataMember();
		} else { // MEMBER_FUNCTION
			_currentLine->remakeAsMemberFunctionString();
			_currentLine->parseAsMemberFunction();
		}
		mainFramePtr->m_wndTreeBar.replaceClass(_packageName,_className,_classContent);
		if (_pView != NIL) {
			_pView->Invalidate();
			if (_pView->GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc))) {
				theAppPtr->pCOODClassDoc->getClassFiguresLibrary()->replaceFieldTextContent(_packageName,_className,NIL,_pView);
				theAppPtr->pCOODClassDoc->UpdateAllViews((CView *)_pView);
			}
		}
		ClassPropDlg *classDlg = theAppPtr->getActiveClassPropDlg();
		if (classDlg != NIL) {
			if ((classDlg->GetStyle() & WS_VISIBLE) != 0) {
				classDlg->reloadClassMembers();
			}
		}
		if ((theAppPtr->theRelationTraverseDlg->GetStyle() & WS_VISIBLE) != 0) {
			theAppPtr->theRelationTraverseDlg->reloadClassMembers();
		}
	}
	if (theAppPtr->pCOODClassDoc != NIL)
		theAppPtr->pCOODClassDoc->setModifiedFlag();
	clearContents(); 
	return repaintFlag;
}

void MemberPropDlg::loadFromClassTextLine(COODView *aView,ClassTextLine *aLine,int index,ClassContent *aContent,CString &className,CString &packageName)
{
	if (_currentLine != NIL) {
		saveToClassTextLine();
	}
	_pView = aView;
	_currentLine = aLine;
	_index = index;
	_classContent = aContent;
	_className = className;
	_packageName = packageName;
	if (aLine == NIL) return;
	loadFromClassTextLine();
}

void MemberPropDlg::loadFromClassTextLine()
{
	CString classString = "of ";
	classString = classString + _className;
	_pStaticClassNameCtrl->SetWindowText(classString);
	m_editMemberNameCtrl.SetWindowText(_currentLine->name());
	PropCommonDlg::loadFromClassTextLine();
}

void MemberPropDlg::OnSelchangeTabMemberProp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
    ShowSelTabWindow();
	*pResult = 0;
}

BOOL MemberPropDlg::OnInitDialog() 
{
	PropCommonDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	
    RECT rect;
	GetWindowRect(&rect);

	CString title;
	if (_whichMember == DATA_MEMBER) {
		title = _languageName + " Data Member Properties";
		if (_languageName.CompareNoCase("Visual C++") == 0) {
			_generalOption = new VCPPVarPropGeneral(this);
			_generalOption->Create(IDD_VCPP_VAR_PROP_GENERAL,this);
		} else if (_languageName.CompareNoCase("C#") == 0) {
			_generalOption = new CSharpVarPropGeneral(this);
			_generalOption->Create(IDD_CSHARP_VAR_PROP_GENERAL,this);
		} else if (_languageName.CompareNoCase("Java") == 0) {
			_generalOption = new JavaVarPropGeneral(this);
			_generalOption->Create(IDD_JAVA_VAR_PROP_GENERAL,this);
		} else {
			_generalOption = new CPPVarPropGeneral(this);
			_generalOption->Create(IDD_CPP_VAR_PROP_GENERAL,this);
		}
	} else { // member function
		title = _languageName + " Member Function Properties";
		if (_languageName.CompareNoCase("Visual C++") == 0) {
			_generalOption = new VCPPMethodPropGeneral(this);
			_generalOption->Create(IDD_VCPP_METHOD_PROP_GENERAL,this);
		} else if (_languageName.CompareNoCase("C#") == 0) {
			_generalOption = new CSharpMethodPropGeneral(this);
			_generalOption->Create(IDD_CSHARP_METHOD_PROP_GENERAL,this);
		} else if (_languageName.CompareNoCase("Java") == 0) {
			_generalOption = new JavaMethodPropGeneral(this);
			_generalOption->Create(IDD_JAVA_METHOD_PROP_GENERAL,this);
		} else {
			_generalOption = new CPPMethodPropGeneral(this);
			_generalOption->Create(IDD_CPP_METHOD_PROP_GENERAL,this);
		}
	}
	_generalOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	SetWindowText(title);

	if (_whichMember == DATA_MEMBER) {
		_commentOption = new CommentDlg("method:",this);
	} else {
		_commentOption = new CommentDlg("data:",this);
	}
	_commentOption->Create(IDD_COMMENT_DLG,this);
	_commentOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	AddItem(m_optionsTab,0," General ",(LPARAM)_generalOption);
	AddItem(m_optionsTab,1," Documentation ",(LPARAM)_commentOption);

	_pTabCtrl = &m_optionsTab;
	_pStaticClassNameCtrl = &m_staticClassNameCtrl;

	if (_whichMember == DATA_MEMBER) {
		return TRUE;
	}

	_methodBodyOption = new MethodBodyDlg(this);
	_methodBodyOption->Create(IDD_METHOD_BODY_DLG,this);
	_methodBodyOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	AddItem(m_optionsTab,2," Programming ",(LPARAM)_methodBodyOption);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MemberPropDlg::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	
	if (_currentLine == NIL) return;
	saveToClassTextLine();
	_index++;
	if (_whichMember == DATA_MEMBER) {
		if (_classContent->nOfDataMembers() <= _index) _index = 0;
		_currentLine = _classContent->getDataMemberLine(_index);
	} else { //	MEMBER_FUNCTION
		if (_classContent->nOfMemberFunctions() <= _index) _index = 0;
		_currentLine = _classContent->getMemberFunctionLine(_index);
	}
	loadFromClassTextLine();
}


void MemberPropDlg::OnButtonPrev() 
{
	// TODO: Add your control notification handler code here
	
	if (_currentLine == NIL) return;
	saveToClassTextLine();
	_index--;
	if (_whichMember == DATA_MEMBER) {
		if (_index < 0) _index = _classContent->nOfDataMembers() - 1;
		_currentLine = _classContent->getDataMemberLine(_index);
	} else { //	MEMBER_FUNCTION
		if (_index < 0) _index = _classContent->nOfMemberFunctions() - 1;
		_currentLine = _classContent->getMemberFunctionLine(_index);
	}
	loadFromClassTextLine();
}

void MemberPropDlg::OnSize(UINT nType, int cx, int cy) 
{
	PropCommonDlg::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if ((GetStyle() & WS_VISIBLE) == 0) return;

	RECT rect;
	GetWindowRect(&rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	if (cx < ClientMinWidth &&
		cy < ClientMinHeight) {
		SetWindowPos(NULL,0,0,MinWidth,MinHeight,SWP_NOMOVE);
	} else if (cx < ClientMinWidth) {
		SetWindowPos(NULL,0,0,MinWidth,h,SWP_NOMOVE);
	} else if (cy < ClientMinHeight) {
		SetWindowPos(NULL,0,0,w,MinHeight,SWP_NOMOVE);
	}

	repositionAndResizeSubcontrols();

	_initialWidth = w;
	_initialHeight = h;
}

void MemberPropDlg::repositionBotton(RECT dialogRect,CButton& buttonCtrl)
{
	RECT buttonRect;
	buttonCtrl.GetWindowRect(&buttonRect);

	RECT buttonClientRect;
	buttonCtrl.GetClientRect(&buttonClientRect);

	int buttonH = buttonClientRect.bottom - buttonClientRect.top;
	int newLeft = buttonRect.left - dialogRect.left - BoundaryGapX;
	int newTop = dialogRect.bottom - dialogRect.top - buttonH - BoundaryGapY;
	buttonCtrl.SetWindowPos(NULL,newLeft,newTop,0,0,SWP_NOSIZE);
}

void MemberPropDlg::resizeIfNeededOnCreate()
{
	if (_initialWidth == 0 || _initialHeight == 0) return;
	SetWindowPos(NULL,0,0,_initialWidth,_initialHeight,SWP_NOMOVE);

	repositionAndResizeSubcontrols();
}

void MemberPropDlg::repositionAndResizeSubcontrols()
{
	RECT rect;
	GetWindowRect(&rect);

	repositionBotton(rect,m_buttonNextCtrl);
	repositionBotton(rect,m_buttonPrevCtrl);
	repositionBotton(rect,m_buttonOKCtrl);
	repositionBotton(rect,m_buttonCancelCtrl);

	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	resizeTabControlSize(w,h);

	_commentOption->resizeDialogToFitPropertyDialog(rect);
	if (_methodBodyOption != NIL) {
		_methodBodyOption->resizeDialogToFitPropertyDialog(rect);
	}
}