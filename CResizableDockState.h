#ifndef _CRESIZABLEDOCKSTATE_H
#define _CRESIZABLEDOCKSTATE_H

#include <afxpriv.h>

class CResizableDockState : public CDockState
{
// Construction
public:
	CResizableDockState();		
    virtual ~CResizableDockState();

// Operations
	void LoadState(LPCTSTR lpszProfileName);

};

#endif