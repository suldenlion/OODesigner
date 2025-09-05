// RelationshipInfoTuple.cpp: implementation of the RelationshipInfoTuple class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OOD.h"
#include "RelationshipInfoTuple.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(RelationshipInfoTuple,CObject,1)

RelationshipInfoTuple::RelationshipInfoTuple()
: CObject()
{
	_majorClassName = _T("");
	_minorClassName = _T("");
	_relationshipString = _T("");
	_tupleData = _T("");
}

RelationshipInfoTuple::RelationshipInfoTuple(char *majorClassName,char *minorClassName,char *relationshipString)
: CObject()
{
	_majorClassName = majorClassName;
	_minorClassName = minorClassName;
	_relationshipString = relationshipString;
	_tupleData = _T("public");
}

RelationshipInfoTuple::~RelationshipInfoTuple()
{

}

void RelationshipInfoTuple::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);  
	if (ar.IsStoring()) {
		ar << _majorClassName << _minorClassName << _tupleData << _relationshipString;
	} else {
		ar >> _majorClassName >> _minorClassName >> _tupleData >> _relationshipString;
	}
}

