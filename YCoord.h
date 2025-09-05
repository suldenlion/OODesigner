/* YCoord.h */

#ifndef _YCOORD_H
#define _YCOORD_H

#include "Classes.h"

class YCoord : public CObject {
	DECLARE_SERIAL(YCoord)
public:
	int y;
private : // data members
	COODView *_controller;
public : // member functions
	YCoord();
	YCoord(COODView *controller);
	YCoord(COODView *controller,int viewY);
	virtual ~YCoord();
	virtual void Serialize(CArchive& ar);
	void setController(COODView *controller);
	void set(int viewY);
	void set(YCoord &c);
	int get();
};

#endif
