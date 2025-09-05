// NoteText.h: interface for the NoteText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTETEXT_H__6E699E42_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_NOTETEXT_H__6E699E42_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SlaveryText.h"

#define IAMNOTENAME	(0)

class NoteText : public SlaveryText  
{
	DECLARE_SERIAL(NoteText)
public:
	NoteText();
	NoteText(COODView *controller,Note *master,int whoAmI,int ox,int oy);
	virtual ~NoteText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual int insert(char* keypressed);
};

#endif // !defined(AFX_NOTETEXT_H__6E699E42_0BC7_11D4_AED4_00A0C9BA6734__INCLUDED_)
