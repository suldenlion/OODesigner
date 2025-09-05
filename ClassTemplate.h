// ClassTemplate.h: interface for the ClassTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSTEMPLATE_H__9C23B746_01AE_11D3_AC44_00008610434C__INCLUDED_)
#define AFX_CLASSTEMPLATE_H__9C23B746_01AE_11D3_AC44_00008610434C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditableFigure.h"

#define CLASSTEMPLATE_INIT_WIDTH	(80)
#define XGAP_CLASSTEMPLATE			(6)
#define YGAP_CLASSTEMPLATE			(6)

#define INTERFACE_PORT_DELTA_Y		(30)

class ClassTemplate : public EditableFigure {
	DECLARE_SERIAL(ClassTemplate)
private:
	BOOL _templateFlag;

	BOOL _minimized;
	BOOL _fixedSizeFlag;
	BOOL _varSupressedFlag;
	BOOL _methodSupressedFlag;

	char _oldName[BUFSIZ];
	BOOL _alreadyCopiedFromContent;
	TemplateClassTag *_templateTag;
	CString _stereotypeTmp;
	// Association Class 경우
	Association * _associationPtr;
	BOOL _doNotDrawAssociationLink;
	/* 이 좌표 값들은 origin을 고려하지 않은 절대값 들이다. */ 
	int _savedX2;
	int _savedY2;
	ClassContent *_classContent;
	ClassText *_nameField;
	ClassText *_varField;
	ClassText *_methodField;
	Line *_separator1;
	Line *_separator2;
	InterfacePortList *_ports;
	Line *_interfaceExtensionLine;
	BOOL _canDoSupressDataMembers;
	BOOL _canDoSupressMemberFunctions;

	void moveCoordWhenMinimized(int dx,int dy);
	void adjustTemplateTagPosition();
	void resetInterfaceExtensionLineSize();
	PackageLibrary *getPackageLibrary();
	ClassFigureLibrary *getClassFigureLibrary();
	void makeShapeFromMemberContent();
	void replaceNameFieldContent();
public:
	ClassTemplate();
	ClassTemplate(COODView *controller,int ox,int oy,int deltaV,Popup *popup);
	virtual ~ClassTemplate();
	virtual void Serialize(CArchive& ar);
	virtual UnsignedLong* whoAreYou();
	virtual Figure* born(Figure* ptr = NIL);
	virtual void setSpecificDataMembers();
	virtual void clear(CDC* dcp);
	virtual void draw(CDC* dcp);
	virtual void drawBoundary(CDC* dcp);
	virtual void drawOnMetaFile(CDC* dcp);
	virtual void move(CDC* dcp,int dx,int dy);
	virtual void moveCoord(int dx,int dy);
	virtual void moveCoordForScroll(int dx,int dy);
	virtual void bye();
	virtual BOOL startEdit();
	virtual BOOL moveProlog(BOOL moveAllFlag=FALSE);
	virtual void epilog(BOOL = FALSE);
	virtual void popup(CPoint* event,BOOL = FALSE);
	virtual void setFocus(int x = -OODMAXINT, int y = -OODMAXINT);
	virtual BOOL wantToResize(int &x,int &y);
	virtual void makeRegion(CRgn *sourceClipRgn);
	virtual void resetRegion();
	virtual void releaseRegion();
	virtual void modifyWidthMinus(int dx,int index);
	virtual void modifyWidthPlus(int dx,int index);
	virtual void modifyHeight(int dy,int index);
	virtual BOOL onEnter(int x,int y);
	virtual void eraseDots(CDC* dcp);
	virtual void drawDots(CDC* dcp);
	virtual void deleteFocusObject();
	virtual BOOL adjustLine(Line *line,BOOL startPoint);
	virtual BOOL containsOnTupleBound(int x,int y);
	virtual void setController(COODView *ptr);
	virtual void setBackground(COLORREF c);
	int ptInWhichField(int x,int y);
	void getInterfacePortText(char *text,int bufsiz);
	void setStereotype(const char *stype);
	void setTemplateFlag();
	BOOL getTemplateFlag() { return _templateFlag; }
	BOOL getInterfaceFlag();
	TextContent *getNameContent();
	TextContent *getVarContent();
	TextContent *getMethodContent();
	BOOL canDoSupressDataMembers() {
		return _canDoSupressDataMembers;
	}
	BOOL canDoSupressMemberFunctions() {
		return _canDoSupressMemberFunctions;
	}
	void setClassContent(ClassContent *ptr);
	void resetAndReshapeClassTextContentFromClassContent(CString &packageName);
	void changeSize();
	void supressDataMembers();
	void supressMemberFuctions();
	void setAssociationPtr(Association *associationPtr) {
		_associationPtr = associationPtr;
	}
	void drawAssociationLink(CDC *dcp);
	InterfacePortText* createInterfacePort();
	char *getOldName() { return _oldName; }
	ClassContent *classContent() { return _classContent; }
	void registerClassContent();
	void justRegisterClassContent(ClassLibrary *pPackage);
	void deleteMemberTextContent();
	void copyMemberContentIfNeed();
	int nOfMemberFunctions();
	int nOfDataMembers();
	void parseMembers();
	void getTemplateTagString(char *buffer,int size);
	void getDataMemberBrowserString(int i,int &vis,CString &aLineString);
	void getMemberFunctionBrowserString(int i,int &vis,CString &aLineString);
	void replaceFieldTextContent(ClassTemplate *aClass,COODView *controller);
	BOOL hasClassNameInInterfacePorts(CString &interfaceName);
};

#endif // !defined(AFX_CLASSTEMPLATE_H__9C23B746_01AE_11D3_AC44_00008610434C__INCLUDED_)
