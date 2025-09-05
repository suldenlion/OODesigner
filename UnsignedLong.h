/* UnsignedLong.h */

#ifndef _UNSIGNEDLONG_H
#define _UNSIGNEDLONG_H

#include "Classes.h"

#define NBYTES	(16)
class UnsignedLong : public CObject {
private : // data members
	int _n;
	unsigned char _bytes[NBYTES];
	void initialize(int n);
public : // member functions
	virtual ~UnsignedLong();
	UnsignedLong(int n = -1);
	BOOL equals(UnsignedLong *from);
	BOOL notEqual(UnsignedLong *from);
	BOOL isIn(UnsignedLong *from);
	UnsignedLong *oring(UnsignedLong *from);
};

#endif
