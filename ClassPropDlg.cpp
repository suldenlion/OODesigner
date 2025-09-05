// ClassPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include "ClassPropDlg.h"
#include "KtgMacro.h"
#include "COODClassDoc.h"
#include "COODView.h"
#include "ClassFigureLibrary.h"
#include "CPPClassPropGeneral.h"
#include "JavaClassPropGeneral.h"
#include "CSharpClassPropGeneral.h"
#include "VCPPClassPropGeneral.h"
#include "DataMembersOption.h"
#include "MemberFunctionsOption.h"
#include "VCPPClassPropMaps.h"
#include "ClassDocumentDlg.h"
#include "ClassOthersOption.h"
#include "CMainFrame.h"
#include "CResizableTreeBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ClassPropDlg dialog
IMPLEMENT_DYNAMIC(ClassPropDlg, PropCommonDlg)

ClassPropDlg::ClassPropDlg(const char* language,CWnd* pParent /*=NULL*/)
	: PropCommonDlg(ClassPropDlg::IDD, pParent)
{
	_languageName = language;
	_dataMembersOption = NIL;
	_generalOption = NIL;
	_memberFunctionsOption = NIL;
	_documentOption = NIL;
	_vcppMapsOption = NIL;
	_classOthersOption = NIL;
	//{{AFX_DATA_INIT(ClassPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ClassPropDlg::~ClassPropDlg()
{
	delete _dataMembersOption;
	delete _generalOption;
	delete _memberFunctionsOption;
	delete _documentOption;
	if (_vcppMapsOption != NIL) delete _vcppMapsOption;
	delete _classOthersOption;
}

void ClassPropDlg::DoDataExchange(CDataExchange* pDX)
{
	PropCommonDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ClassPropDlg)
	DDX_Control(pDX, IDC_TAB_CLASS_PROP, m_optionsTab);
	DDX_Control(pDX, IDC_STATIC_CLASS_NAME, m_staticClassNameCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ClassPropDlg, PropCommonDlg)
	//{{AFX_MSG_MAP(ClassPropDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CLASS_PROP, OnSelchangeTabClassProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ClassPropDlg message handlers

void ClassPropDlg::loadFromClassContent(COODView *theView,ClassContent *theContent,CString &className,CString &packageName)
{
	_currentLine = NIL;
	_pView = theView;
	_classContent = theContent;
	_className = className;
	_packageName = packageName;

	CString classString = _className + " of " + _packageName;
	_pStaticClassNameCtrl->SetWindowText(classString);
	PropCommonDlg::loadFromClassTextLine();
}

BOOL ClassPropDlg::saveToClassTextLine()
{
	BOOL repaintFlag = PropCommonDlg::saveToClassTextLine();

	if (repaintFlag == TRUE) {
		if (_pView != NIL) {
			_pView->Invalidate();
			if (_pView->GetDocument()->IsKindOf(RUNTIME_CLASS(COODClassDoc))) {
				theAppPtr->pCOODClassDoc->getClassFiguresLibrary()->replaceFieldTextContent(_packageName,_className,NIL,_pView);
				theAppPtr->pCOODClassDoc->UpdateAllViews((CView *)_pView);
			}
		}
	}
	if (_generalOption->isModified()) {
		mainFramePtr->m_wndTreeBar.replaceClass(_packageName,_className,_classContent);
	}
	if (theAppPtr->pCOODClassDoc != NIL)
		theAppPtr->pCOODClassDoc->setModifiedFlag();
	clearContents(); 
	return repaintFlag;
}

void ClassPropDlg::reloadClassMembers()
{
	_dataMembersOption->reloadClassMembers();
	_memberFunctionsOption->reloadClassMembers();
}

void ClassPropDlg::setMfcClassFlag()
{
	// 이 함수는 맵이 추가 되는 경우 일반 클래스를 MFC 클래스로 변경한다.
	// class content의 변경은 호출하는 곳에서 이루어진다.
	if (!_generalOption->IsKindOf(RUNTIME_CLASS(VCPPClassPropGeneral))) return;
	VCPPClassPropGeneral *genDlg = (VCPPClassPropGeneral *)_generalOption;
	genDlg->setMFCClassCtrl();
}

void ClassPropDlg::OnSelchangeTabClassProp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	ShowSelTabWindow();
	*pResult = 0;
}

BOOL ClassPropDlg::OnInitDialog() 
{
	PropCommonDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	
    RECT rect;
	GetWindowRect(&rect);

	CString title = _languageName + " Class Properties";
	SetWindowText(title);

	_generalOption = NIL;
	if (_languageName.CompareNoCase("Visual C++") == 0) {
		_generalOption = new VCPPClassPropGeneral(this);
		_generalOption->Create(IDD_VCPP_CLASS_PROP_GENERAL,this);
	} else if (_languageName.CompareNoCase("Java") == 0) {
		_generalOption = new JavaClassPropGeneral(this);
		_generalOption->Create(IDD_JAVA_CLASS_PROP_GENERAL,this);
	} else if (_languageName.CompareNoCase("C#") == 0){
		_generalOption = new CSharpClassPropGeneral(this);
		_generalOption->Create(IDD_CSHARP_CLASS_PROP_GENERAL,this);
	} else {
		_generalOption = new CPPClassPropGeneral(this);
		_generalOption->Create(IDD_CPP_CLASS_PROP_GENERAL,this);
	}
	_generalOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_dataMembersOption = new DataMembersOption(this);
	_dataMembersOption->Create(IDD_DATA_MEMBERS,this);
	_dataMembersOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_memberFunctionsOption = new MemberFunctionsOption(this);
	_memberFunctionsOption->Create(IDD_MEMBER_FUNCTIONS,this);
	_memberFunctionsOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_documentOption = new ClassDocumentDlg(this);
	_documentOption->Create(IDD_CLASS_DOCUMENT_DLG,this);
	_documentOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);

	_vcppMapsOption = NIL;

	AddItem(m_optionsTab,0," General ",(LPARAM)_generalOption);
	AddItem(m_optionsTab,1," Data ",(LPARAM)_dataMembersOption);
	AddItem(m_optionsTab,2," Functions ",(LPARAM)_memberFunctionsOption);
	AddItem(m_optionsTab,3," Documentation ",(LPARAM)_documentOption);

	if (_languageName.CompareNoCase("Visual C++") == 0) {
		_vcppMapsOption = new VCPPClassPropMaps(this);
		_vcppMapsOption->Create(IDD_VCPP_CLASS_PROP_MAPS,this);
		_vcppMapsOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);
		AddItem(m_optionsTab,4," Maps ",(LPARAM)_vcppMapsOption);
		_classOthersOption = new ClassOthersOption(this);
		_classOthersOption->Create(IDD_CLASS_OTHERS,this);
		_classOthersOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);
		AddItem(m_optionsTab,5," Others ",(LPARAM)_classOthersOption);
	} else {
		_classOthersOption = new ClassOthersOption(this);
		_classOthersOption->Create(IDD_CLASS_OTHERS,this);
		_classOthersOption->SetWindowPos(NULL,rect.left+PAGE_DISPX,rect.top+PAGE_DISPY,0,0,SWP_NOSIZE);
		AddItem(m_optionsTab,4," Others ",(LPARAM)_classOthersOption);
	}

	_pTabCtrl = &m_optionsTab;
	_pStaticClassNameCtrl = &m_staticClassNameCtrl;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
