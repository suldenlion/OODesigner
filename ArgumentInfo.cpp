// ArgumentInfo.cpp: implementation of the ArgumentInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "ArgumentInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArgumentInfo::ArgumentInfo()
: CObject()
{
	initialize();
}

ArgumentInfo::~ArgumentInfo()
{

}

void ArgumentInfo::initialize()
{
	argName = _T("");
	argType = _T("");
	defaultValue = _T("");
}