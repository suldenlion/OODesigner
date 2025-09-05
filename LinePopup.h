// LinePopup.h: interface for the LinePopup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LINEPOPUP_H)
#define _LINEPOPUP_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Classes.h"
#include "Popup.h"

class LinePopup : public Popup  
{
private : // data members
	CMenu *_stylePopup;
	CMenu *_thicknessPopup;
public:
	LinePopup();
	virtual ~LinePopup();
};

#endif // !defined(_LINEPOPUP_H)
