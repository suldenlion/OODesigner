// ClassTextLine.cpp: implementation of the ClassTextLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ClassTextLine.h"
#include "KtgMacro.h"
#include "ClassText.h"
#include "ArgumentInfo.h"
#include "ArgumentList.h"

#define	ERRORSTATE				(0)
#define INITIALSTATE			(1)
#define	VISIBILITYACCEPTEDSTATE (2)
#define NAMECOLLECTINGSTATE		(3)
#define READYTOACCEPTTYPESTATE	(4)
#define TYPECOLLECTINGSTATE		(5)
#define DEFAULTVALUECOLLECTINGSTATE	(6)
#define PROPERTYCOLLECTINGSTATE	(7)
#define ARGUMENTCOLLECTINGSTATE	(8)
#define ARGUMENTCOLLECTFINISHSTATE (9)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ENDTABLE(v) (v - 1 + sizeof v / sizeof v[0])

static struct _cTypeNames{
        char *typeName;
}

cTypeNames[] = {
	"char",
	"const",
	"double",
	"enum",
	"extern",
	"float",
	"int",
	"long",
	"register",
	"short",
	"signed",
	"struct",
	"union",
	"unsigned",
	"void",
	"volatile"
};

static void getLastWord(int lastIndex,char *buffer,char *aWord)
{
	aWord[0] ='\0';
	if (lastIndex <= 1) return;
	lastIndex--;
	int startIndex = 0;
	int i;
	for(i = 0; i < lastIndex; i++) {
		if (buffer[i] == ' ') startIndex = i;
	}
	if (buffer[startIndex] == ' ') startIndex++;
	if (buffer[startIndex] == '\0') return;
	int j = 0;
	for (i = startIndex; i <= lastIndex; i++) {
		aWord[j++] = buffer[i];
	}
	aWord[j] = '\0';
}

static BOOL alpha(char c)
{
	if (c >= 'a' && c <= 'z') return TRUE;
	if (c >= 'A' && c <= 'Z') return TRUE;
	return FALSE;
}

static BOOL alphaOr_(char c)
{
	if (c == '_') return TRUE;
	if (c >= 'a' && c <= 'z') return TRUE;
	if (c >= 'A' && c <= 'Z') return TRUE;
	return FALSE;
}

static BOOL alphaOrNum(char c)
{
	if (c == '_') return TRUE;
	if (c == '-') return TRUE;
	if (c == '.') return TRUE;
	if (c >= '0' && c <= '9') return TRUE;
	if (c >= 'a' && c <= 'z') return TRUE;
	if (c >= 'A' && c <= 'Z') return TRUE;
	return FALSE;
}

BOOL ifCTypeName(char *testName)
{
	struct _cTypeNames *low = cTypeNames,
						*high = ENDTABLE(cTypeNames),
						*mid;
	int c;

	char name[BUFSIZ];
	strcpy_s(name,BUFSIZ,testName);
	int i = strlen(name)-1;
	while (i > 0) {
		if (name[i] == '*' || name[i] == '&') {
			name[i] = '\0';
		}
		i--;
	}
	if (strlen(name) <= 1) return FALSE;
	
	while(low <= high) {
		mid = low + (high - low) / 2;
		if ((c = strcmp(mid->typeName,name)) == 0) {
			return TRUE;
		} else if (c < 0) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ClassTextLine,TextLine,1)

ClassTextLine::ClassTextLine()
: TextLine()
{
	_arguments = new ArgumentList();
	_defaultValue.RemoveAll();
	_functionBody.RemoveAll();
	_comment.RemoveAll();
	_baseClassInitialization.RemoveAll();
	initialize();
}

ClassTextLine::~ClassTextLine()
{
	delete _arguments;
	_defaultValue.RemoveAll();
	_functionBody.RemoveAll();
	_comment.RemoveAll();
	_baseClassInitialization.RemoveAll();
}

BOOL ClassTextLine::hasArgument()
{
	if (_arguments->nOfList() > 0) return TRUE;
	return FALSE;
}

void ClassTextLine::initialize()
{
	_staticFlag = FALSE;
	_virtualFlag = FALSE;
	_afxVirtualFlag = FALSE;
	_afxMsgFlag = FALSE;
	_inlineFlag = FALSE;
	_constFlag = FALSE;
	_transientFlag = FALSE;
	_abstractFlag = FALSE;
	_nativeFlag = FALSE;
	_synchronizedFlag = FALSE;
	_afxDataFlag = FALSE;
	_afxFieldFlag = FALSE;
	_finalFlag = FALSE;
	_internalFlag = FALSE;
	_externFlag = FALSE;
	_readonlyFlag = FALSE;
	_overrideFlag = FALSE;

	_visibility = DEFAULT_ID;
	_errorFlag = FALSE;
	_whichCompartment = IAMCLASSNAME;

	_nameInBrowser = _T("");
	_name = _T(""); 
	_type = _T(""); 
	_argument = _T(""); 
	_property = _T("");

	ArgumentInfo *anArg = _arguments->getFirst();
	while (anArg != NIL) {
		delete anArg;
		anArg = _arguments->getNext();
	}
	_arguments->clear();
}

void ClassTextLine::Serialize(CArchive& ar)
{
	TextLine::Serialize(ar);   
	_defaultValue.Serialize(ar);
	_functionBody.Serialize(ar);
	_comment.Serialize(ar);
	_baseClassInitialization.Serialize(ar);
	if (ar.IsStoring()) {
		ar << (BYTE)_staticFlag;
		ar << (BYTE)_virtualFlag;
		ar << (BYTE)_afxVirtualFlag;
		ar << (BYTE)_afxMsgFlag;
		ar << (BYTE)_inlineFlag;
		ar << (BYTE)_constFlag;
		ar << (BYTE)_transientFlag;
		ar << (BYTE)_abstractFlag;
		ar << (BYTE)_nativeFlag;
		ar << (BYTE)_synchronizedFlag;
		ar << (BYTE)_afxDataFlag;
		ar << (BYTE)_afxFieldFlag;
		ar << (BYTE)_finalFlag;
		ar << (BYTE)_internalFlag;
		ar << (BYTE)_externFlag;
		ar << (BYTE)_readonlyFlag;
		ar << (BYTE)_overrideFlag;
		ar << (LONG)_visibility;
		ar << (LONG)_whichCompartment;
		ar << _nameInBrowser;
		ar << _name; 
		ar << _type; 
		ar << _argument; 
		ar << _property;
	} else {
		ar >> (BYTE&)_staticFlag;
		ar >> (BYTE&)_virtualFlag;
		ar >> (BYTE&)_afxVirtualFlag;
		ar >> (BYTE&)_afxMsgFlag;
		ar >> (BYTE&)_inlineFlag;
		ar >> (BYTE&)_constFlag;
		ar >> (BYTE&)_transientFlag;
		ar >> (BYTE&)_abstractFlag;
		ar >> (BYTE&)_nativeFlag;
		ar >> (BYTE&)_synchronizedFlag;
		ar >> (BYTE&)_afxDataFlag;
		ar >> (BYTE&)_afxFieldFlag;
		ar >> (BYTE&)_finalFlag;
		ar >> (BYTE&)_internalFlag;
		ar >> (BYTE&)_externFlag;
		ar >> (BYTE&)_readonlyFlag;
		ar >> (BYTE&)_overrideFlag;
		ar >> (LONG&)_visibility;
		ar >> (LONG&)_whichCompartment;
		ar >> _nameInBrowser;
		ar >> _name; 
		ar >> _type; 
		ar >> _argument; 
		ar >> _property;
	}
}

void ClassTextLine::clear()
{
	TextLine::clear();
	_defaultValue.RemoveAll();
	_functionBody.RemoveAll();
	_comment.RemoveAll();
	_baseClassInitialization.RemoveAll();
}

void ClassTextLine::copy(TextLine *from)
{
	TextLine::copy(from);
	if (!from->IsKindOf(RUNTIME_CLASS(ClassTextLine))) return;
	_defaultValue.AddTail(&(((ClassTextLine *)from)->_defaultValue));
	_functionBody.AddTail(&(((ClassTextLine *)from)->_functionBody));
	_comment.AddTail(&(((ClassTextLine *)from)->_comment));
	_baseClassInitialization.AddTail(&(((ClassTextLine *)from)->_baseClassInitialization));
}

TextLine *ClassTextLine::born()
{
	ClassTextLine *copied = new ClassTextLine();
	copied->copy(this);
	return (ClassTextLine *)copied;
}

void ClassTextLine::setDefaultValue(const char *buffer)
{
	if (_defaultValue.IsEmpty()) {
		_defaultValue.AddTail(buffer);
	} else {
		_defaultValue.RemoveHead();
		_defaultValue.AddHead(buffer);
	}
}

void ClassTextLine::parseAsDataMember()
{
	if (line[0] == '\0') return;
	initialize();
	_whichCompartment = IAMVARIABLES;
	int stateNo = INITIALSTATE;
	int index = 0;
	char buffer[BUFSIZ];
	int bufferIndex = 0;
	while (TRUE) {
		char c = line[index];
		switch(stateNo) {
		case ERRORSTATE:
			return;
		case INITIALSTATE:
			if (c == ' ') {
				stateNo = INITIALSTATE;
			} else if (c == '\0') {
				// ERROR STATE
				return;
			} else if (alphaOr_(c) || c == '/') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else if (c == '+') {
				_visibility = PUBLIC_ID;
				stateNo = VISIBILITYACCEPTEDSTATE;
			} else if (c == '#') {
				_visibility = PROTECTED_ID;
				stateNo = VISIBILITYACCEPTEDSTATE;
			} else if (c == '-') {
				_visibility = PRIVATE_ID;
				stateNo = VISIBILITYACCEPTEDSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case VISIBILITYACCEPTEDSTATE:
			if (c == ' ') {
				stateNo = VISIBILITYACCEPTEDSTATE;
			} else if (c == '\0') {
				// ERROR STATE
				return;
			} else if (alphaOr_(c) || c == '/') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case NAMECOLLECTINGSTATE:
			if (c == ' ') {
				stateNo = NAMECOLLECTINGSTATE;
			} else if (c == '\0') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex == 0) return;
				_name = buffer;
				_nameInBrowser = buffer;
				return;
			} else if (c == ':') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					_name = buffer;
					_nameInBrowser = buffer;
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = READYTOACCEPTTYPESTATE;
			} else if (c == '=') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					_name = buffer;
					_nameInBrowser = buffer;
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (c == '{') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					_name = buffer;
					_nameInBrowser = buffer;
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else if (alphaOrNum(c) || c == '[' || c == ']' || c == '(' || c == ')' || c == ',') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case READYTOACCEPTTYPESTATE:
			if (c == ' ') {
				stateNo = READYTOACCEPTTYPESTATE;
			} else if (c == '\0') {
				return;
			} else if (alphaOr_(c)) {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case TYPECOLLECTINGSTATE:
			if (c == ' ') {
				char aWord[BUFSIZ];
				getLastWord(bufferIndex,buffer,aWord);
//				if (strlen(aWord) > 0 && ifCTypeName(aWord)) {
				if (strlen(aWord) > 0 && buffer[bufferIndex-1] != ' ') {
					buffer[bufferIndex] = c;
					bufferIndex++;
				}
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == '\0') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex == 0) return;
				if (buffer[bufferIndex-1] == ' ') buffer[bufferIndex-1] = '\0';
				_type = buffer;
				return;
			} else if (c == '=') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					if (buffer[bufferIndex-1] == ' ') buffer[bufferIndex-1] = '\0';
					_type = buffer;
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (c == '{') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					if (buffer[bufferIndex-1] == ' ') buffer[bufferIndex-1] = '\0';
					_type = buffer;
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else if (alphaOrNum(c) 
				|| c == '&' || c == '*' || c == '[' || c == ']' || c == '<' || c == '>' || c == ',') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == ':' && line[index+1] == ':') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				buffer[bufferIndex] = c;
				bufferIndex++;
				index++;
				stateNo = TYPECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case DEFAULTVALUECOLLECTINGSTATE:
			if (c == ' ' && bufferIndex == 0) {
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (c == '\0') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex == 0) return;
				setDefaultValue(buffer);
				return;
			} else if (c == '{') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					setDefaultValue(buffer);
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			}
			break;
		case PROPERTYCOLLECTINGSTATE:
			if (c == ' ' && bufferIndex == 0) {
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else if (c == '\0' || c == '}') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex == 0) return;
				_property = buffer;
				setModifierFlags();
				return;
			} else {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = PROPERTYCOLLECTINGSTATE;
			}
			break;
		default:
			stateNo = ERRORSTATE;
			break;
		}
		index++;
	}
}

void ClassTextLine::parseAsMemberFunction()
{
	if (line[0] == '\0') return;
	initialize();
	_defaultValue.RemoveAll();
	_whichCompartment = IAMMETHODS;
	int stateNo = INITIALSTATE;
	int index = 0;
	char buffer[BUFSIZ];
	int bufferIndex = 0;
	BOOL bracketStackFlag = OFF;

	while (TRUE) {
		char c = line[index];
		switch(stateNo) {
		case ERRORSTATE:
			// ERROR STATE
			return;
		case INITIALSTATE:
			if (c == ' ') {
				stateNo = INITIALSTATE;
			} else if (c == '\0') {
				// ERROR STATE
				return;
			} else if (alphaOr_(c) || c == '~') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else if (c == '+') {
				_visibility = PUBLIC_ID;
				stateNo = VISIBILITYACCEPTEDSTATE;
			} else if (c == '#') {
				_visibility = PROTECTED_ID;
				stateNo = VISIBILITYACCEPTEDSTATE;
			} else if (c == '-') {
				_visibility = PRIVATE_ID;
				stateNo = VISIBILITYACCEPTEDSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case VISIBILITYACCEPTEDSTATE:
			if (c == ' ') {
				stateNo = VISIBILITYACCEPTEDSTATE;
			} else if (c == '\0') {
				// ERROR STATE
				return;
			} else if (alphaOr_(c) || c == '~') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case NAMECOLLECTINGSTATE:
			if (c == ' ') {
				buffer[bufferIndex] = '\0';
				if (strcmp(buffer,"operator") == 0 && alpha(line[index+1])) {
					buffer[bufferIndex] = c;
					bufferIndex++;
				} 
				stateNo = NAMECOLLECTINGSTATE;
			} else if (c == '\0') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex == 0) return;
				_name = buffer;
				_nameInBrowser = buffer;
				_nameInBrowser = _nameInBrowser + "()";
				return;
			} else if (c == ':') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					_name = buffer;
					_nameInBrowser = buffer;
					_nameInBrowser = _nameInBrowser + "()";
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = READYTOACCEPTTYPESTATE;
			} else if (c == '(') {
				buffer[bufferIndex] = '\0';
				if (strcmp(buffer,"operator") == 0) {
					buffer[bufferIndex] = c;
					bufferIndex++;
					stateNo = NAMECOLLECTINGSTATE;
				} else {
					if (bufferIndex > 0) {
						_name = buffer;
						_nameInBrowser = buffer;
					}
					buffer[0] = '\0';
					bufferIndex = 0;
					stateNo = ARGUMENTCOLLECTINGSTATE;
				}
			} else if (c == '+' || c == '-' || c == '*' || c == '/' ||
				c == '%' || c == '^' || c == '&' || c == '|' || c == ')' ||
				c == '~' || c == '!' || c == '=' || c == '<' || c == '>') {
				buffer[bufferIndex] = '\0';
				if (strlen(buffer) < 8) { 
					stateNo = ERRORSTATE;
				} else {
					char operatorString[BUFSIZ];
					strcpy_s(operatorString,BUFSIZ,buffer);
					operatorString[8] = '\0';
					if (strcmp(operatorString,"operator") == 0) {
						buffer[bufferIndex] = c;
						bufferIndex++;
						stateNo = NAMECOLLECTINGSTATE;
					} else {
						stateNo = ERRORSTATE;
					}
				}
			} else if (c == '=') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					_name = buffer;
					_nameInBrowser = buffer;
					_nameInBrowser = _nameInBrowser + "()";
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (c == '{') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					_name = buffer;
					_nameInBrowser = buffer;
					_nameInBrowser = _nameInBrowser + "()";
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else if (alphaOrNum(c) || c == '[' || c == ']') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case READYTOACCEPTTYPESTATE:
			if (c == ' ') {
				stateNo = READYTOACCEPTTYPESTATE;
			} else if (c == '\0') {
				return;
			} else if (alphaOr_(c)) {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case TYPECOLLECTINGSTATE:
			if (c == ' ') {
				char aWord[BUFSIZ];
				getLastWord(bufferIndex,buffer,aWord);
//				if (strlen(aWord) > 0 && ifCTypeName(aWord)) {
				if (strlen(aWord) > 0 && buffer[bufferIndex-1] != ' ') {
					buffer[bufferIndex] = c;
					bufferIndex++;
				}
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == '\0') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex == 0) return;
				if (buffer[bufferIndex-1] == ' ') buffer[bufferIndex-1] = '\0';
				_type = buffer;
				return;
			} else if (c == '=') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					if (buffer[bufferIndex-1] == ' ') buffer[bufferIndex-1] = '\0';
					_type = buffer;
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (c == '{') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex > 0) {
					if (buffer[bufferIndex-1] == ' ') buffer[bufferIndex-1] = '\0';
					_type = buffer;
				}
				buffer[0] = '\0';
				bufferIndex = 0;
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else if (alphaOrNum(c) 
				|| c == '&' || c == '*' || c == '[' || c == ']' || c == '<' || c == '>' || c == ',') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == ':' && line[index+1] == ':') {
				buffer[bufferIndex] = c;
				bufferIndex++;
				buffer[bufferIndex] = c;
				bufferIndex++;
				index++;
				stateNo = TYPECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case ARGUMENTCOLLECTINGSTATE:
			if (c == ' ' && bufferIndex == 0) {
				stateNo = ARGUMENTCOLLECTINGSTATE;
			} else if (c == '\0') {
				// 인수들의 마지막 괄호가 없음, ERROR STATE
				_nameInBrowser = _nameInBrowser + "()";
				buffer[bufferIndex] = '\0';
				return;
			} else if (c == '[') {
				bracketStackFlag = ON;
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = ARGUMENTCOLLECTINGSTATE;
			} else if (c == ']') {
				bracketStackFlag = OFF;
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = ARGUMENTCOLLECTINGSTATE;
			} else if (c == ')') {
				if (bracketStackFlag == OFF) {
					buffer[bufferIndex] = '\0';
					if (bufferIndex > 0) {
						convertAsCArgument(buffer);
					}
					CString tmpArg;
					_arguments->getAsCArgument(tmpArg,TRUE);
					_nameInBrowser = _nameInBrowser + "(" + tmpArg + ")";
					buffer[0] = '\0';
					bufferIndex = 0;
					stateNo = ARGUMENTCOLLECTFINISHSTATE;
				} else { // ON
					buffer[bufferIndex] = c;
					bufferIndex++;
					stateNo = ARGUMENTCOLLECTINGSTATE;
				}
			} else {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = ARGUMENTCOLLECTINGSTATE;
			}
			break;
		case ARGUMENTCOLLECTFINISHSTATE:
			if (c == ' ') {
				stateNo = ARGUMENTCOLLECTFINISHSTATE;
			} else if (c == '\0') {
				return;
			} else if (c == ':') {
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == '=') {
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (c == '{') {
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case DEFAULTVALUECOLLECTINGSTATE:
			if (c == ' ') {
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (c == '\0') {
				return;
			} else if (c == '0') {
				// pure virtual function
				setDefaultValue("0");
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (c == '{') {
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case PROPERTYCOLLECTINGSTATE:
			if (c == ' ' && bufferIndex == 0) {
				stateNo = PROPERTYCOLLECTINGSTATE;
			} else if (c == '\0' || c == '}') {
				buffer[bufferIndex] = '\0';
				if (bufferIndex == 0) return;
				_property = buffer;
				setModifierFlags();
				return;
			} else {
				buffer[bufferIndex] = c;
				bufferIndex++;
				stateNo = PROPERTYCOLLECTINGSTATE;
			}
			break;
		}
		index++;
	}
}

void ClassTextLine::convertAsCArgument(char *buffer)
{
	if (buffer[0] == '\0') return;
	BOOL acceptCommaAsName = FALSE;
	int stateNo = INITIALSTATE;
	int bufferIndex = 0;
	char nameBuffer[BUFSIZ];
	nameBuffer[0] = '\0';
	int nameBufferIndex = 0;
	char typeBuffer[BUFSIZ];
	typeBuffer[0] = '\0';
	int typeBufferIndex = 0;
	char valueBuffer[BUFSIZ];
	valueBuffer[0] = '\0';
	int valueBufferIndex = 0;
	ArgumentInfo *currentArg = NIL;
	while(TRUE) {
		char c = buffer[bufferIndex];
		switch(stateNo) {
		case ERRORSTATE:
			if (currentArg != NIL) delete currentArg;
			return;
		case INITIALSTATE:
			if (currentArg == NIL) {
				currentArg = new ArgumentInfo();
			}
			if (c == ' ') {
				stateNo = INITIALSTATE;
			} else if (c == '\0') {
				delete currentArg;
				return;
			} else if (alphaOr_(c)) {
				nameBuffer[nameBufferIndex] = c;
				nameBufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else if (c == ':') {
				nameBuffer[nameBufferIndex] = '\0';
				typeBuffer[0] = '\0';
				typeBufferIndex = 0;
				stateNo = READYTOACCEPTTYPESTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case NAMECOLLECTINGSTATE:
			if (c == ' ') {
				stateNo = NAMECOLLECTINGSTATE;
			} else if (c == '\0') {
				nameBuffer[nameBufferIndex] = '\0';
				if (nameBufferIndex == 0) return;
				currentArg->argName = nameBuffer;
				_arguments->insert(currentArg);
				return;
			} else if (c == ':') {
				nameBuffer[nameBufferIndex] = '\0';
				if (nameBufferIndex > 0) {
					currentArg->argName = nameBuffer;
				}
				nameBuffer[nameBufferIndex] = '\0';
				typeBuffer[0] = '\0';
				typeBufferIndex = 0;
				acceptCommaAsName = FALSE;
				stateNo = READYTOACCEPTTYPESTATE;
			} else if (c == '=') {
				nameBuffer[nameBufferIndex] = '\0';
				if (nameBufferIndex > 0) {
					currentArg->argName = nameBuffer;
				}
				nameBuffer[nameBufferIndex] = '\0';
				valueBuffer[0] = '\0';
				valueBufferIndex = 0;
				acceptCommaAsName = FALSE;
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (acceptCommaAsName == FALSE && c == ',') {
				nameBuffer[nameBufferIndex] = '\0';
				if (nameBufferIndex > 0) {
					currentArg->argName = nameBuffer;
					_arguments->insert(currentArg);
					currentArg = NIL;
				}
				nameBuffer[0] = '\0';
				nameBufferIndex = 0;
				stateNo = INITIALSTATE;
			} else if (acceptCommaAsName == TRUE && c == ',') {
				nameBuffer[nameBufferIndex] = c;
				nameBufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else if (alphaOrNum(c) || c == '[' || c == ']') {
				nameBuffer[nameBufferIndex] = c;
				nameBufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else if (c == '<') {
				acceptCommaAsName = TRUE;
				nameBuffer[nameBufferIndex] = c;
				nameBufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else if (c == '>') {
				acceptCommaAsName = FALSE;
				nameBuffer[nameBufferIndex] = c;
				nameBufferIndex++;
				stateNo = NAMECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case READYTOACCEPTTYPESTATE:
			if (c == ' ') {
				stateNo = READYTOACCEPTTYPESTATE;
			} else if (c == '\0') {
				nameBuffer[nameBufferIndex] = '\0';
				if (nameBufferIndex == 0) {
					delete currentArg;
					return;
				}
				currentArg->argName = nameBuffer;
				_arguments->insert(currentArg);
				return;
			} else if (alphaOr_(c)) {
				typeBuffer[typeBufferIndex] = c;
				typeBufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == '[') {
				// [ 가 나오는 경우는 interface에서 [in], [in, out] 등이 명시되는 경우임
				typeBuffer[typeBufferIndex] = c;
				typeBufferIndex++;
				bufferIndex++;
				while ((c = buffer[bufferIndex]) != '\0' && 
					c != ']') {
					typeBuffer[typeBufferIndex] = c;
					typeBufferIndex++;
					bufferIndex++;
				}
				if (c == '\0') {
					stateNo = ERRORSTATE;
				} else { // c == ']'
					typeBuffer[typeBufferIndex] = c;
					typeBufferIndex++;
					typeBuffer[typeBufferIndex] = ' ';
					typeBufferIndex++;
					stateNo = TYPECOLLECTINGSTATE;
				}
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case TYPECOLLECTINGSTATE:
			if (c == ' ') {
				char aWord[BUFSIZ];
				getLastWord(typeBufferIndex,typeBuffer,aWord);
//				if (strlen(aWord) > 0 && ifCTypeName(aWord)) {
				if (strlen(aWord) > 0 && buffer[bufferIndex-1] != ' ') {
					typeBuffer[typeBufferIndex] = c;
					typeBufferIndex++;
				}
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == ':' && buffer[bufferIndex+1] == ':') {
				typeBuffer[typeBufferIndex] = c;
				typeBufferIndex++;
				typeBuffer[typeBufferIndex] = c;
				typeBufferIndex++;
				bufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == '\0') {
				nameBuffer[nameBufferIndex] = '\0';
				typeBuffer[typeBufferIndex] = '\0';
				if (nameBufferIndex == 0 && typeBufferIndex == 0) {
					delete currentArg;
					return;
				}
				currentArg->argName = nameBuffer;
				currentArg->argType = typeBuffer;
				_arguments->insert(currentArg);
				return;
			} else if (c == '=') {
				typeBuffer[typeBufferIndex] = '\0';
				valueBuffer[0] = '\0';
				valueBufferIndex = 0;
				acceptCommaAsName = FALSE;
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			} else if (acceptCommaAsName == FALSE && c == ',') {
				nameBuffer[nameBufferIndex] = '\0';
				typeBuffer[typeBufferIndex] = '\0';
				if (nameBufferIndex > 0 || typeBufferIndex > 0) {
					currentArg->argName = nameBuffer;
					currentArg->argType = typeBuffer;
					_arguments->insert(currentArg);
					currentArg = NIL;
				}
				nameBuffer[0] = '\0';
				nameBufferIndex = 0;
				typeBuffer[0] = '\0';
				typeBufferIndex = 0;
				stateNo = INITIALSTATE;
			} else if (acceptCommaAsName == TRUE && c == ',') {
				typeBuffer[typeBufferIndex] = c;
				typeBufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else if (alphaOrNum(c) ||
				c == '&' || c == '*' || c == '[' || c == ']') {
				typeBuffer[typeBufferIndex] = c;
				typeBufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == '<') {
				acceptCommaAsName = TRUE;
				typeBuffer[typeBufferIndex] = c;
				typeBufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else if (c == '>') {
				acceptCommaAsName = FALSE;
				typeBuffer[typeBufferIndex] = c;
				typeBufferIndex++;
				stateNo = TYPECOLLECTINGSTATE;
			} else {
				stateNo = ERRORSTATE;
			}
			break;
		case DEFAULTVALUECOLLECTINGSTATE:
			if (c == '\0') {
				nameBuffer[nameBufferIndex] = '\0';
				typeBuffer[typeBufferIndex] = '\0';
				valueBuffer[valueBufferIndex] = '\0';
				if (nameBufferIndex == 0 && 
					typeBufferIndex == 0 &&
					valueBufferIndex == 0) {
					delete currentArg;
					return;
				}
				currentArg->argName = nameBuffer;
				currentArg->argType = typeBuffer;
				currentArg->defaultValue = valueBuffer;
				_arguments->insert(currentArg);
				return;
			} else if (c == ',') {
				nameBuffer[nameBufferIndex] = '\0';
				typeBuffer[typeBufferIndex] = '\0';
				valueBuffer[valueBufferIndex] = '\0';
				if (nameBufferIndex > 0 || 
					typeBufferIndex > 0 ||
					valueBufferIndex > 0) {
					currentArg->argName = nameBuffer;
					currentArg->argType = typeBuffer;
					currentArg->defaultValue = valueBuffer;
					_arguments->insert(currentArg);
					currentArg = NIL;
				}
				nameBuffer[0] = '\0';
				nameBufferIndex = 0;
				typeBuffer[0] = '\0';
				typeBufferIndex = 0;
				valueBuffer[0] = '\0';
				valueBufferIndex = 0;
				stateNo = INITIALSTATE;
			} else {
				valueBuffer[valueBufferIndex] = c;
				valueBufferIndex++;
				stateNo = DEFAULTVALUECOLLECTINGSTATE;
			}
			break;
		}
		bufferIndex++;
	}
}

void ClassTextLine::getMethodSignatureString(CString &signature)
{
	CString tmpArg;
	_arguments->getAsCArgument(tmpArg,FALSE);
	signature = _name + "(" + tmpArg + ")";
}

void ClassTextLine::writeVisibility(CString &vis)
{
	if (vis.CompareNoCase("public") == 0) {
		_visibility = PUBLIC_ID;
	} else if (vis.CompareNoCase("protected") == 0) {
		_visibility = PROTECTED_ID;
	} else if (vis.CompareNoCase("private") == 0) {
		_visibility = PRIVATE_ID;
	} else {
		_visibility = DEFAULT_ID;
	}
}

void ClassTextLine::remakeAsDataMemberString()
{
	CString newLine = _T("");
	remakeForNameWithVisibility(newLine);
	if (_type.GetLength() > 0) {
		newLine = newLine + " : " + _type;
	}
	if (_defaultValue.IsEmpty() == FALSE) {
		if (_defaultValue.GetHead().GetLength() > 0) {
			newLine = newLine + " = " + _defaultValue.GetHead();
		}
	}
	remakeForModifiers(newLine);
	setString(newLine);
}

void ClassTextLine::remakeAsMemberFunctionString()
{
	CString newLine = _T("");
	remakeForNameWithVisibility(newLine);
	CString tmpArg = _T("");
	_arguments->getArgumentString(tmpArg);
	newLine = newLine + "(" + tmpArg + ")";
	if (_type.GetLength() > 0) {
		newLine = newLine + " : " + _type;
	}
	if (_defaultValue.GetCount() > 0) {
		newLine = newLine + " = 0";
	}
	remakeForModifiers(newLine);
	setString(newLine);
}

void ClassTextLine::remakeForNameWithVisibility(CString &newLine) 
{
	if (_visibility == PUBLIC_ID) {
		newLine = newLine + "+";
	} else if (_visibility == PROTECTED_ID) {
		newLine = newLine + "#";
	} else if (_visibility == PRIVATE_ID) {
		newLine = newLine + "-";
	}
	newLine = newLine + _name;
}

void ClassTextLine::setModifierFlags()
{
	if (_property.GetLength() == 0) return;

	const int MAXTRY = 20;
	int i = 0;
	char buffer[BUFSIZ];
	Text::strcpyCompact(buffer,_property,BUFSIZ);
	CString modifierString = buffer;
	do {
		i++;
		CString aModifier = modifierString.SpanExcluding(",");
		int allLen = modifierString.GetLength();
		int len = aModifier.GetLength();
		if (aModifier.CompareNoCase("static") == 0) {
			_staticFlag = TRUE;
		} else if (aModifier.CompareNoCase("virtual") == 0) {
			_virtualFlag = TRUE;
		} else if (aModifier.CompareNoCase("afx_virtual") == 0) {
			_afxVirtualFlag = TRUE;
		} else if (aModifier.CompareNoCase("afx_msg") == 0) {
			_afxMsgFlag = TRUE;
		} else if (aModifier.CompareNoCase("inline") == 0) {
			_inlineFlag = TRUE;
		} else if (aModifier.CompareNoCase("const") == 0) {
			_constFlag = TRUE;
		} else if (aModifier.CompareNoCase("transient") == 0) {
			_transientFlag = TRUE;
		} else if (aModifier.CompareNoCase("abstract") == 0) {
			_abstractFlag = TRUE;
		} else if (aModifier.CompareNoCase("native") == 0) {
			_nativeFlag = TRUE;
		} else if (aModifier.CompareNoCase("synchronized") == 0) {
			_synchronizedFlag = TRUE;
		} else if (aModifier.CompareNoCase("afx_data") == 0) {
			_afxDataFlag = TRUE;
		} else if (aModifier.CompareNoCase("afx_field") == 0) {
			_afxFieldFlag = TRUE;
		} else if (aModifier.CompareNoCase("final") == 0) {
			_finalFlag = TRUE;
		} else if (aModifier.CompareNoCase("internal") == 0) {
			_internalFlag = TRUE;
		} else if (aModifier.CompareNoCase("extern") == 0) {
			_externFlag = TRUE;
		} else if (aModifier.CompareNoCase("readonly") == 0) {
			_readonlyFlag = TRUE;
		} else if (aModifier.CompareNoCase("override") == 0) {
			_overrideFlag = TRUE;
		}
		if (allLen-len <= 1) break;
		modifierString = modifierString.Right(allLen-len-1);
	} while(i < MAXTRY);
}

void ClassTextLine::remakeForModifiers(CString &newLine)
{
	if (_staticFlag == FALSE &&
		_virtualFlag == FALSE &&
		_afxVirtualFlag == FALSE &&
		_afxMsgFlag == FALSE &&
		_inlineFlag == FALSE &&
		_constFlag == FALSE &&
		_transientFlag == FALSE &&
		_abstractFlag == FALSE &&
		_nativeFlag == FALSE &&
		_synchronizedFlag == FALSE &&
		_afxDataFlag == FALSE &&
		_afxFieldFlag == FALSE &&
		_finalFlag == FALSE &&
		_internalFlag == FALSE &&
		_externFlag == FALSE &&
		_readonlyFlag == FALSE &&
		_overrideFlag == FALSE) return;
	int n = newLine.GetLength();
	if (newLine[n-1] == ' ') {
		newLine = newLine + "{";
	} else {
		newLine = newLine + " {";
	}

	CStringList modifiers;
	if (_staticFlag == TRUE) {
		modifiers.AddTail("static");
	}
	if (_virtualFlag == TRUE) {
		modifiers.AddTail("virtual");
	}
	if (_afxVirtualFlag == TRUE) {
		modifiers.AddTail("afx_virtual");
	}
	if (_afxMsgFlag == TRUE) {
		modifiers.AddTail("afx_msg");
	}
	if (_inlineFlag == TRUE) {
		modifiers.AddTail("inline");
	}
	if (_constFlag == TRUE) {
		modifiers.AddTail("const");
	}
	if (_transientFlag == TRUE) {
		modifiers.AddTail("transient");
	}
	if (_abstractFlag == TRUE) {
		modifiers.AddTail("abstract");
	}
	if (_nativeFlag == TRUE) {
		modifiers.AddTail("native");
	}
	if (_synchronizedFlag == TRUE) {
		modifiers.AddTail("synchronized");
	}
	if (_afxDataFlag == TRUE) {
		modifiers.AddTail("afx_data");
	}
	if (_afxFieldFlag == TRUE) {
		modifiers.AddTail("afx_field");
	}
	if (_finalFlag == TRUE) {
		modifiers.AddTail("final");
	}
	if (_internalFlag == TRUE) {
		modifiers.AddTail("internal");
	}
	if (_externFlag == TRUE) {
		modifiers.AddTail("extern");
	}
	if (_readonlyFlag == TRUE) {
		modifiers.AddTail("readonly");
	}
	if (_overrideFlag == TRUE) {
		modifiers.AddTail("override");
	}
	POSITION pos = modifiers.GetHeadPosition();
	while (pos != NULL) {
		CString aModifier = modifiers.GetNext(pos);
		newLine = newLine + aModifier;
		if (pos != NULL) {
			newLine = newLine + ",";
		}
	}
	newLine = newLine + "}";
}