// CChooseDirDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OOD.h"
#include <io.h>
#include "CChooseDirDlg.h"
#include "KtgMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FILE_CLOSE_BM_ID				(0)
#define FILE_OPEN_BM_ID					(1)

/////////////////////////////////////////////////////////////////////////////
// CChooseDirDlg dialog


CChooseDirDlg::CChooseDirDlg(CString &driveName,CString& dirName,CWnd* pParent /*=NULL*/)
	: CDialog(CChooseDirDlg::IDD, pParent)
{
	_remakeTreeFlag = FALSE;
	_initDriveName = driveName;
	//{{AFX_DATA_INIT(CChooseDirDlg)
	m_dirName = driveName+dirName;
	//}}AFX_DATA_INIT
}


void CChooseDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseDirDlg)
	DDX_Control(pDX, IDC_COMBO_DRIVE_NAME, m_comboDriveNames);
	DDX_Control(pDX, IDC_TREE_DIRS, m_treeDirs);
	DDX_Text(pDX, IDC_EDIT_DIR_NAME, m_dirName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseDirDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseDirDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVE_NAME, OnSelchangeComboDriveName)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DIRS, OnDblclkTreeDirs)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseDirDlg message handlers

BOOL CChooseDirDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comboDriveNames.Dir(DDL_DRIVES,"*");
	int n = m_comboDriveNames.GetCount();
	CString *drives = new CString[n];
	for (int i = 0; i < n; i++) {
		char buffer[BUFSIZ];
		m_comboDriveNames.GetLBText(i,buffer);
		int len = strlen(buffer);
		if (buffer[len-1] == ']') buffer[len-1] = '\0';
		if (buffer[len-2] == '-') buffer[len-2] = ':';
		int index = 0;
		while (buffer[index] != '\0') {
			if (buffer[index] >= 'a' && buffer[index] <= 'z') break;
			if (buffer[index] >= 'A' && buffer[index] <= 'Z') break;
			index++;
		}
		drives[i] = &buffer[0] + index;
	}
	m_comboDriveNames.ResetContent();
	for (int i = 0; i < n; i++) {
		m_comboDriveNames.InsertString(i,drives[i]);
		if (_initDriveName.CompareNoCase(drives[i]) == 0) {
			m_comboDriveNames.SetCurSel(i);
		}
	}
	delete []drives;

	char initDrive[BUFSIZ];
	strcpy_s(initDrive,BUFSIZ,_initDriveName);
	strcat_s(initDrive,BUFSIZ,"\\*.*");
	DlgDirList(initDrive,0,IDC_EDIT_DIR_NAME,DDL_DIRECTORY);

	_directoryImageList.Create(IDR_DIRECTORY_BITMAP,17,1,RGB(192,192,192));
	m_treeDirs.SetImageList(&_directoryImageList,TVSIL_NORMAL);
	showDirectory(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseDirDlg::showDirectory()
{
	UpdateData();
	char allString[BUFSIZ];
	strcpy_s(allString,BUFSIZ,m_dirName);
	char oneString[BUFSIZ];
	int allIndex = 0;
	int oneIndex = 0;
	HTREEITEM hCurrent = NULL;
	if (strlen(allString) < 1) return;
	m_treeDirs.DeleteAllItems();

	do  {
		char c = allString[allIndex];
		if (c == '\0') {
			oneString[oneIndex] = '\0';
			if (oneIndex == 0) break;
			if (hCurrent == NULL) { 
				hCurrent = m_treeDirs.InsertItem(oneString);
			} else {
				HTREEITEM hOld = hCurrent;
				hCurrent = m_treeDirs.InsertItem(oneString,hCurrent);
				m_treeDirs.SetItemImage(hCurrent,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
				m_treeDirs.Expand(hOld,TVE_EXPAND);
				m_treeDirs.SetItemImage(hOld,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
			}
		} else if (c != '\\') {
			oneString[oneIndex] = c;
			oneIndex++;
		} else {
			if (oneIndex > 0 && oneString[oneIndex-1] == ':') {
				oneString[oneIndex] = c;
				oneIndex++;
				oneString[oneIndex] = '\0';
			} else {
				oneString[oneIndex] = '\0';
			}
			if (hCurrent == NULL) {
				hCurrent = m_treeDirs.InsertItem(oneString);
			} else {
				HTREEITEM hOld = hCurrent;
				hCurrent = m_treeDirs.InsertItem(oneString,hCurrent);
				m_treeDirs.SetItemImage(hCurrent,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
				m_treeDirs.Expand(hOld,TVE_EXPAND);
				m_treeDirs.SetItemImage(hOld,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
			}
			oneIndex = 0;
		}
		allIndex++;
	} while (allString[allIndex] != '\0');

	if (hCurrent == NULL) return;

	struct _finddata_t dir;
	long hFile;

	strcpy_s(allString,BUFSIZ,m_dirName);
	strcat_s(allString,BUFSIZ,"*.*");

	if ((hFile = _findfirst(allString,&dir)) == -1L) return;
	while (_findnext(hFile,&dir) == 0) {
		if (dir.attrib & _A_SUBDIR) {
			char dirName[BUFSIZ];
			strcpy_s(dirName,BUFSIZ,dir.name);
			if (strcmp(dirName,"..") != 0 && strcmp(dirName,".") != 0) {
				m_treeDirs.InsertItem(dirName,hCurrent);
				m_treeDirs.SetItemImage(hCurrent,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
			}
		}
	}
	m_treeDirs.Expand(hCurrent,TVE_EXPAND);
	if (m_treeDirs.ItemHasChildren(hCurrent) == TRUE) {
		m_treeDirs.SetItemImage(hCurrent,FILE_OPEN_BM_ID,FILE_OPEN_BM_ID);
	} else {
		m_treeDirs.SetItemImage(hCurrent,FILE_CLOSE_BM_ID,FILE_CLOSE_BM_ID);
	}
	_findclose(hFile);
}

void CChooseDirDlg::OnSelchangeComboDriveName() 
{
	// TODO: Add your control notification handler code here
	int index = m_comboDriveNames.GetCurSel();
	m_comboDriveNames.GetLBText(index,m_dirName);
	m_dirName = m_dirName + '\\';
	UpdateData(FALSE);
	showDirectory();
}

void CChooseDirDlg::OnDblclkTreeDirs(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hCurrent = m_treeDirs.GetSelectedItem();
	if (hCurrent == NULL) return;
	CString allString;
	HTREEITEM hRoot = m_treeDirs.GetRootItem();
	HTREEITEM hTmp = hCurrent;
	CString reverseName = m_treeDirs.GetItemText(hTmp);
	reverseName.MakeReverse();
	if (hTmp == hRoot) {
		allString = allString + reverseName;
	} else {
		allString = allString + "\\" + reverseName;
	}
	while (hTmp != hRoot) {
		hTmp = m_treeDirs.GetParentItem(hTmp);
		reverseName = m_treeDirs.GetItemText(hTmp);
		reverseName.MakeReverse();
		if (hTmp == hRoot) {
			allString = allString + reverseName;
		} else {
			allString = allString + "\\" + reverseName;
		}
	}
	allString.MakeReverse();

	if (m_dirName.CompareNoCase(allString) == 0) {
		EndDialog(IDOK);
		return;
	}
	m_dirName = allString;
	UpdateData(FALSE);

	_remakeTreeFlag = TRUE;
	RECT rect;
	m_treeDirs.GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect,FALSE);

	*pResult = 0;
}

void CChooseDirDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (_remakeTreeFlag) {
		_remakeTreeFlag = FALSE;
		showDirectory();
	}
	// Do not call CDialog::OnPaint() for painting messages
}

