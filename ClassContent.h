// ClassContent.h: interface for the ClassContent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSCONTENT_H__99727920_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_CLASSCONTENT_H__99727920_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MAP identification constants
#define KTG_MESSAGEMAP			(1<<1)
#define KTG_INTERFACEMAP		(1<<2)
#define KTG_DISPATCHMAP	        (1<<3)
#define KTG_OLECMDMAP			(1<<4)
#define KTG_CONNECTIONMAP		(1<<5)
#define KTG_EVENTSINKMAP		(1<<6)
#define KTG_UNSPECIFIEDMAP		(1<<7)

// These are used in ClassDocumentDlg class.
#define HFFRONT		(0)
#define SFFRONT		(1)
#define HFMIDDLE	(2)
#define HFEND		(3)

#include "Classes.h"

class ClassContent : public CObject  
{
public:
	DECLARE_SERIAL(ClassContent)
private:
	BOOL _visited; // transient
	BOOL _askedToDelete;
	BOOL _templateFlag;
	BOOL _abstractFlag;
	BOOL _staticFlag;
	BOOL _mfcClassFlag;
	BOOL _serializableFlag;
	BOOL _finalFlag;
	BOOL _dynamicFlag;
	BOOL _dyncreateFlag;
	BOOL _generateCodeFlag;
	int _visibility;
	unsigned int _employeedMap;

	CString _className;
	CString _outerClassName;
	CString _sourceFileName;
	CString _headerFileName;
	CString _targetDirectoryForCodeGeneration;
	CString _fileNameSpecified;
	CStringList _constraints;

	TextContent *_varContent;
	TextContent *_methodContent;
	CString _stereotype;
	CString _resourceID;
	CString _templateTagString;
	CStringList _headerFileFrontDocument;
	CStringList _sourceFileFrontDocument;
	CStringList _headerFileMiddleDocument;
	CStringList _headerFileEndDocument;
	CStringList _messageMap;
	CStringList _interfaceMap;
	CStringList _dispatchMap;
	CStringList _olecmdMap;
	CStringList _connectionMap;
	CStringList _eventsinkMap;
	CStringList _unspecifiedMaps;
	
public:
	ClassContent();
	virtual ~ClassContent();
	virtual void Serialize(CArchive& ar);
	void setClassContentFrom(ClassTemplate *fromClass);
	void parseMembers();
	TextContent *getVarContent();
	TextContent *getMethodContent();
	void setVarContent(TextContent *ptr);
	void setMethodContent(TextContent *ptr);
	CString &className() { return _className; }
	BOOL &abstractFlag() { return _abstractFlag; }
	BOOL &staticFlag() { return _staticFlag; }
	BOOL &mfcClassFlag() { return _mfcClassFlag; }
	BOOL &serializableFlag() { return _serializableFlag; }
	BOOL &dynamicFlag() { return _dynamicFlag; }
	BOOL &dyncreateFlag() { return _dyncreateFlag; }
	BOOL &finalFlag() { return _finalFlag; }
	BOOL getTemplateFlag() { return _templateFlag; }
	BOOL &generateCodeFlag() { return _generateCodeFlag; }
	BOOL isInnerClass();
	int &visibility() { return _visibility; }
	unsigned int &employeedMap() { return _employeedMap; }
	void setMfcClassFlag() { _mfcClassFlag = TRUE; }
	void setEmployeedMap(unsigned int mapId);
	void resetEmployeedMap(unsigned int mapId);
	void writeVisibility(CString &vis);
	BOOL hasEqualName(CString &aName);
	void setName(CString &aName) { _className = aName; }
	CStringList *headerFileFrontDocument() { return &_headerFileFrontDocument; }
	CStringList *sourceFileFrontDocument() { return &_sourceFileFrontDocument; }
	CStringList *headerFileMiddleDocument() { return &_headerFileMiddleDocument; }
	CStringList *headerFileEndDocument() { return &_headerFileEndDocument; }
	CStringList *messageMap() { return &_messageMap; }
	CStringList *interfaceMap() { return &_interfaceMap; }
	CStringList *dispatchMap() { return &_dispatchMap; }
	CStringList *olecmdMap() { return &_olecmdMap; }
	CStringList *connectionMap() { return &_connectionMap; }
	CStringList *eventsinkMap() { return &_eventsinkMap; }
	CStringList *unspecifiedMaps() { return &_unspecifiedMaps; }
	CString &stereotype() { return _stereotype; }
	CString &outerClassName() { return _outerClassName; }
	CString &targetDirectoryForCodeGeneration();
	CString &fileNameSpecified();
	CString &resourceID() { return _resourceID; }
	void setStereotype(const char *stype);
	void setOuterClassName(const char *oname);
	void setFileNameSpecified(const char *fname);
	BOOL getStereotype(char *stype);
	BOOL getInterfaceFlag();
	int nOfDataMembers();
	int nOfMemberFunctions();
	void getTemplateTagString(char *buffer,int size);
	void getDataMemberBrowserString(int i,int &vis,CString &aLineString);
	void getMemberFunctionBrowserString(int i,int &vis,CString &aLineString);
	void deleteMemberFunction(int index);
	void deleteDataMember(int index);
	ClassTextLine *getMemberFunctionLine(int index,CString &browserString);
	ClassTextLine *getMemberFunctionLine(int index);
	ClassTextLine *getDataMemberLine(int index,CString &browserString);
	ClassTextLine *getDataMemberLine(int index);
	TextContent *copyVarContent();
	TextContent *copyMethodContent();
	TextContent *varContent() { return _varContent; }
	TextContent *methodContent() { return _methodContent; }
	BOOL tryToInsertSerializationFunction();
	BOOL tryToInsertDefaultConstructor();
	void makeDefaultConstructorBody(ClassTextLine *theConstructor);
	void resetDocument(CStringList *aDocument,int which);
};

#endif // !defined(AFX_CLASSCONTENT_H__99727920_0BFB_11D4_AED4_00A0C9BA6734__INCLUDED_)
