// VCPPCodeGenerator.h: interface for the VCPPCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VCPPCODEGENERATOR_H__1CEAA4C9_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_VCPPCODEGENERATOR_H__1CEAA4C9_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CPPCommonCodeGenerator.h"

class VCPPCodeGenerator : public CPPCommonCodeGenerator  
{
public:
	VCPPCodeGenerator();
	VCPPCodeGenerator(VCPPCodeGenerator *from);
	virtual ~VCPPCodeGenerator();
	virtual void outputSFSpecialMacro();
	virtual void outputSFSpecialConstruct();
	virtual void printClassHeading();
	virtual void printClassTailing();
	virtual void printClassMemberSpecs();
private:
	void outputAMap(const char *mapName,CStringList *currentMap);
	void printDataMembers();
	void printMemberFunctionSpecs();
	void printAfxDataMembers();
	void printAfxFieldMembers();
	void printAfxVirtualMemberFunctionSpecs();
	void printAfxMsgMemberFunctionSpecs();
	void getGeneralDataMemberCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic);
	void getAfxDataMemberCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic);
	void getAfxFieldMemberCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic);
	void getGeneralMemberFunctionCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic);
	void getAfxVirtualMemberFunctionCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic);
	void getAfxMsgMemberFunctionCount(int &nOfPrivates,int &nOfProtected,int &nOfPublic);
};

#endif // !defined(AFX_VCPPCODEGENERATOR_H__1CEAA4C9_1C2E_11D4_AED4_00A0C9BA6734__INCLUDED_)
