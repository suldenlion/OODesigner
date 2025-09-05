/* XCoord.h */

#ifndef _XCOORD_H
#define _XCOORD_H

#include "Classes.h"

class XCoord : public CObject {
	DECLARE_SERIAL(XCoord)
public:
	int x;
private : // data members
	COODView *_controller;
public : // member functions
	XCoord();
	XCoord(COODView *controller);
	XCoord(COODView *controller,int viewX);
	virtual ~XCoord();
	virtual void Serialize(CArchive& ar);
	void setController(COODView *controller);
	void set(int viewX);
	void set(XCoord &c);
	int get();
};

#endif
