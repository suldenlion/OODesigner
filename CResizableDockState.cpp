#include "stdafx.h"
#include "CResizableDockState.h"

static const TCHAR szBarSection[] = _T("%s-Bar%d");
static const TCHAR szSummarySection[] = _T("%s-Summary");
static const TCHAR szBarID[] = _T("BarID");
static const TCHAR szBars[] = _T("Bars");
static const TCHAR szScreenCX[] = _T("ScreenCX");
static const TCHAR szScreenCY[] = _T("ScreenCY");

/////////////////////////////////////////////////////////////////////////////
// CResizableDockState - derived from CDockState
CResizableDockState::CResizableDockState()
{
}

CResizableDockState::~CResizableDockState()
{
}

void CResizableDockState::LoadState(LPCTSTR lpszProfileName)
{
	CWinApp* pApp = AfxGetApp();

	TCHAR szSection[256];
	wsprintf(szSection, szSummarySection, lpszProfileName);
	int nBars = pApp->GetProfileInt(szSection, szBars, 0);

	CSize size;
	size.cx = pApp->GetProfileInt(szSection, szScreenCX, 0);
	size.cy = pApp->GetProfileInt(szSection, szScreenCY, 0);
	SetScreenSize(size);

    CFrameWnd* pWnd = (CFrameWnd*)AfxGetMainWnd();
	for (int i = 0; i < nBars; i++)
	{
	    wsprintf(szSection, szBarSection, lpszProfileName, i);
    	int nBarID = pApp->GetProfileInt(szSection, szBarID, 0);
        if (nBarID != 0)
        {
            // GetControlBar for dock bar id's works on some boxes, not on
            // others. Doing the call also causes floating windows to come
            // back docked, therefore...don't do it.
            switch (nBarID)
            {
            case AFX_IDW_DOCKBAR_TOP:
            case AFX_IDW_DOCKBAR_LEFT:
            case AFX_IDW_DOCKBAR_RIGHT:
            case AFX_IDW_DOCKBAR_BOTTOM:
            case AFX_IDW_DOCKBAR_FLOAT:
                {
		            CControlBarInfo* pInfo = new CControlBarInfo;
		            m_arrBarInfo.Add(pInfo);
		            pInfo->LoadState(lpszProfileName, i, this);
                    break;
                }

            default:
                {
                    if ((pWnd->GetControlBar(nBarID)) != NULL)
                    {
		                CControlBarInfo* pInfo = new CControlBarInfo;
		                m_arrBarInfo.Add(pInfo);
		                pInfo->LoadState(lpszProfileName, i, this);
                    }
#ifdef _DEBUG
                    else
                    {
                        TRACE("Loading bar states: cannot find bar with id %d, ignoring\n", nBarID);
                    }
#endif
                    break;
                }
            }
        }
	}
}
