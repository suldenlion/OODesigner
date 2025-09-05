// ClassText.h: interface for the ClassText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSTEXT_H__9C23B747_01AE_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_CLASSTEXT_H__9C23B747_01AE_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SlaveryText.h"

// 다음 매크로의 숫자는 인덱스로 사용됨 
#define	IAMCLASSNAME	(0)
#define IAMVARIABLES	(1)
#define IAMMETHODS		(2)

class ClassText : public SlaveryText {
	DECLARE_SERIAL(ClassText)
protected:
	virtual BOOL doIHaveToProceed();
	void copyMemberContentIfNeed();
public:
	ClassText();
	ClassText(COODView *controller,ClassTemplate *master,int whoAmI,int ox,int oy);
	virtual ~ClassText();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void goUp();
	virtual void goDown();
	virtual void goNextLine();
	virtual void activateNextText();
	virtual void activatePrevText();
	void parseMembers();
	void getMemberBrowserString(int i,int &vis,CString &aLineString);
};

#endif // !defined(AFX_CLASSTEXT_H__9C23B747_01AE_11D3_AC44_00008610434C__INCLUDED_)
