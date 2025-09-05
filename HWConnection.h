// HWConnection.h: interface for the HWConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HWCONNECTION_H__32DA74E1_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_)
#define AFX_HWCONNECTION_H__32DA74E1_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Connection.h"

class HWConnection : public Connection  
{
	DECLARE_SERIAL(HWConnection)
protected:
	virtual BOOL setModelSpecificSymbol(NodeFigure *focus);
public:
	HWConnection();
	HWConnection(COODView *controller,Popup *popup,Line *aLine);
	virtual ~HWConnection();
	virtual void Serialize(CArchive& ar);
	virtual char *connectionClassName() { return "a hardware communication"; }
	virtual Figure* born(Figure* ptr = NIL);
	virtual UnsignedLong* whoAreYou();
	HWConnectionText* selectOrCreateText();
};

#endif // !defined(AFX_HWCONNECTION_H__32DA74E1_D741_11D3_BBC8_00A0C9BA6734__INCLUDED_)
