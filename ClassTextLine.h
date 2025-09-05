// ClassTextLine.h: interface for the ClassTextLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSTEXTLINE_H__1D4A9D62_138E_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CLASSTEXTLINE_H__1D4A9D62_138E_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Classes.h"
#include "TextLine.h"

class ClassTextLine : public TextLine  
{
	DECLARE_SERIAL(ClassTextLine)
private:
	BOOL _staticFlag;
	BOOL _virtualFlag;
	BOOL _afxVirtualFlag;
	BOOL _afxMsgFlag;
	BOOL _inlineFlag;
	BOOL _constFlag;
	BOOL _transientFlag;
	BOOL _abstractFlag;
	BOOL _nativeFlag;
	BOOL _synchronizedFlag;
	BOOL _afxDataFlag;
	BOOL _afxFieldFlag;
	BOOL _finalFlag;
	BOOL _internalFlag;
	BOOL _externFlag;
	BOOL _readonlyFlag;
	BOOL _overrideFlag;

	BOOL _errorFlag;
	int _visibility;
	int _whichCompartment;
	CString _nameInBrowser;
	CString _name; // data name or function name
	CString _type; // data type or return type
	CString _argument; 
	CString _property;
	ArgumentList *_arguments;
	CStringList _defaultValue;
	CStringList _functionBody;
	CStringList _comment;
	CStringList _baseClassInitialization;

	void setModifierFlags();
	void initialize();
	void remakeForNameWithVisibility(CString &newLine);
	void remakeForModifiers(CString &newLine);
	void setDefaultValue(const char *buffer);
public:
	ClassTextLine();
	virtual ~ClassTextLine();
	virtual void Serialize(CArchive& ar);
	virtual TextLine *born();
	virtual void copy(TextLine *from);
	virtual void clear();
	void getMemberBrowserString(CString &aLineString) {
		aLineString = _nameInBrowser; 
	}
	void getMethodSignatureString(CString &signature);
	void convertAsCArgument(char *buffer);
	CString &name() { return _name; }
	CString &type() { return _type; }
	int visibility() { return _visibility; }
	CStringList &defaultValue() { return _defaultValue; }
	CStringList &functionBody() { return _functionBody; }
	CStringList *comment() { return &_comment; }
	CStringList *baseClassInitialization() { return &_baseClassInitialization; }
	ArgumentList *arguments() { return _arguments; }
	BOOL hasArgument();
	void writeVisibility(CString &vis);
	void parseAsDataMember();
	void parseAsMemberFunction();
	void remakeAsDataMemberString();
	void remakeAsMemberFunctionString();

	BOOL &staticFlag() { return _staticFlag; }
	BOOL &virtualFlag() { return _virtualFlag; }
	BOOL &afxVirtualFlag() { return _afxVirtualFlag; }
	BOOL &afxMsgFlag() { return _afxMsgFlag; }
	BOOL &inlineFlag() { return _inlineFlag; }
	BOOL &constFlag() { return _constFlag; }
	BOOL &transientFlag() { return _transientFlag; }
	BOOL &abstractFlag() { return _abstractFlag; }
	BOOL &nativeFlag() { return _nativeFlag; }
	BOOL &synchronizedFlag() { return _synchronizedFlag; }
	BOOL &afxDataFlag() { return _afxDataFlag; }
	BOOL &afxFieldFlag() { return _afxFieldFlag; }
	BOOL &finalFlag() { return _finalFlag; }
	BOOL &internalFlag() { return _internalFlag; }
	BOOL &externFlag() { return _externFlag; }
	BOOL &readonlyFlag() { return _readonlyFlag; }
	BOOL &overrideFlag() { return _overrideFlag; }
};

#endif // !defined(AFX_CLASSTEXTLINE_H__1D4A9D62_138E_11D4_AED4_00A0C9BA6734__INCLUDED_)
