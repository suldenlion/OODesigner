// FontInfo.h: interface for the FontInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTINFO_H__6D4913E1_FC98_11D2_AC44_00008610434C__INCLUDED_)
#define AFX_FONTINFO_H__6D4913E1_FC98_11D2_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class FontInfo : public CObject
{
	DECLARE_SERIAL(FontInfo)
public:
	int size;
	int weight;
	COLORREF color;
	CString faceName;
	CString styleName;
	BOOL boldFlag;
	BOOL italicFlag;
	BOOL strikeOutFlag;
	BOOL underlineFlag;
	FontInfo();
	virtual ~FontInfo();
	virtual void Serialize(CArchive& ar);
	void resetFontInfo();
	void setFontInfo(CFontDialog *fontDlg);
	void copy(FontInfo *from);
};

#endif // !defined(AFX_FONTINFO_H__6D4913E1_FC98_11D2_AC44_00008610434C__INCLUDED_)
