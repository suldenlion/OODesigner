// ClassText.cpp: implementation of the ClassText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ClassText.h"
#include "ClassTemplate.h"
#include "TextContent.h"
#include "TextLine.h"
#include "ClassTextLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ClassText,SlaveryText,1)

ClassText::ClassText()
: SlaveryText()
{
}

ClassText::ClassText(COODView *controller,ClassTemplate *master,int whoAmI,int ox,int oy)
: SlaveryText(controller,(EditableFigure*)master,whoAmI,ox,oy)
{
	if (controller == NIL) return;
	if (_content != NIL) {
		_content->clear();
		_content->newLineAt(0,whoAreYou());
	}
}

ClassText::~ClassText()
{
	if (_whoAmI != 0) _content = NIL;
}

void ClassText::Serialize(CArchive& ar)
{
	SlaveryText::Serialize(ar);
}

Figure* ClassText::born(Figure* ptr)
{
	ClassText *copied;
	if (ptr == NIL) {
		copied = new ClassText(NIL,NIL,0,0,0);
	} else {
		copied = (ClassText *)ptr;
	}
	return (SlaveryText::born((Figure *)copied));
}

BOOL ClassText::doIHaveToProceed()
{
	if (_whoAmI != IAMCLASSNAME) return FALSE;
	if (nOfLines() >= 2) return TRUE;
	return FALSE;
}

void ClassText::goUp()
{
	if (_whoAmI == IAMCLASSNAME) {
		char name[BUFSIZ];
		int len = getName(name,BUFSIZ);
		if (len <= 0) {
			Beep(1000,1000);
			return;
		}
	}
	SlaveryText::goUp();
}

void ClassText::copyMemberContentIfNeed()
{
	((ClassTemplate *)_master)->copyMemberContentIfNeed();
}

void ClassText::getMemberBrowserString(int i,int &vis,CString &aLineString)
{
	TextLine *aLine = _content->lineAt(i);
	if (aLine == NIL) {
		// Error Case.
		aLineString = _T("");
		vis = 0;
		return;
	}
	if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
		// Error Case.
		aLineString = aLine->ptrAt(0);
		vis = 0;
		return;
	}
	ClassTextLine *memberLine = (ClassTextLine *)aLine;
	vis = memberLine->visibility();
	memberLine->getMemberBrowserString(aLineString);
}

void ClassText::parseMembers()
{
	if (isEmpty()) return;
	TextLine *aLine = _content->getFirst();
	while (aLine != NIL) {
		if (!aLine->IsKindOf(RUNTIME_CLASS(ClassTextLine))) {
			break;
		}
		ClassTextLine *memberLine = (ClassTextLine *)aLine;
		if (_whoAmI == IAMVARIABLES) {
			memberLine->parseAsDataMember();
		} else if (_whoAmI == IAMMETHODS) {
			memberLine->parseAsMemberFunction();
		}
		aLine = _content->getNext();
	}
}

void ClassText::goDown()
{
	if (_whoAmI == IAMCLASSNAME) {
		char name[BUFSIZ];
		int len = getName(name,BUFSIZ);
		if (len <= 0) {
			Beep(1000,1000);
			return;
		}
	}
	SlaveryText::goDown();
}

void ClassText::goNextLine()
{
	if (_whoAmI == IAMCLASSNAME) {
		char name[BUFSIZ];
		int len = getName(name,BUFSIZ);
		if (len <= 0) {
			Beep(1000,1000);
			return;
		}
	}
	SlaveryText::goNextLine();
}

void ClassText::activateNextText()
{
	if (_whoAmI == IAMCLASSNAME) {
		copyMemberContentIfNeed();
	}
	SlaveryText::activateNextText();
	return;
}

void ClassText::activatePrevText()
{
	if (_whoAmI == IAMCLASSNAME) {
		copyMemberContentIfNeed();
	}
	SlaveryText::activatePrevText();
	return;
}

UnsignedLong* ClassText::whoAreYou()
{
	return IAMCLASSTEXT;
}

