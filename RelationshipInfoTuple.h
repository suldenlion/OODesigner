// RelationshipInfoTuple.h: interface for the RelationshipInfoTuple class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELATIONSHIPINFOTUPLE_H__1EF0A102_20DB_11D4_AED4_00A0C9BA6734__INCLUDED_)
#define AFX_RELATIONSHIPINFOTUPLE_H__1EF0A102_20DB_11D4_AED4_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class RelationshipInfoTuple : public CObject  
{
	DECLARE_SERIAL(RelationshipInfoTuple)
	CString _majorClassName;
	CString _minorClassName;
	CString _relationshipString;
	CString _tupleData;
public:
	RelationshipInfoTuple();
	RelationshipInfoTuple(char *majorClassName,char *subClassName,char *relationshipString);
	virtual ~RelationshipInfoTuple();
	virtual void Serialize(CArchive& ar);
	void setVisibility(char *visibility) {
		_tupleData = visibility;
	}
	CString &majorClassName() {
		return _majorClassName;
	}
	CString &minorClassName() {
		return _minorClassName;
	}
	CString &visibility() {
		return _tupleData;
	}
	CString &relationshipString() {
		return _relationshipString;
	}
};

#endif // !defined(AFX_RELATIONSHIPINFOTUPLE_H__1EF0A102_20DB_11D4_AED4_00A0C9BA6734__INCLUDED_)
