#include "stdafx.h"
/* UnsignedLong.C */

#include "UnsignedLong.h"
#include "common.h"
// Super Class : CObject

static void findPosition(int n,int &byteIndex,int &bitIndex)
{
	byteIndex = 0;
	while(n >= 8) {
		byteIndex++;
		n = n - 8;
	}
	bitIndex = n;
}

static void setToByte(unsigned char &abyte,int index)
{
	abyte = abyte | (1<<index);	
}

UnsignedLong::~UnsignedLong()
{
	// Empty
}

UnsignedLong::UnsignedLong(int n)
: CObject()
{
	_n = n;
	initialize(_n);
}

void UnsignedLong::initialize(int n)
{
	if (n >= 8*NBYTES) {
		ErrorMsg("Out of range Error : UnsignedLong::UnsignedLong\n");
		return;
	}
	for(int i = 0; i < NBYTES; i++) {
		_bytes[i] = 0;
	}
	if (n == -1) return;
	int byteindex = 0;
	int bitindex = 0;
	findPosition(n,byteindex,bitindex);
	setToByte(_bytes[byteindex],bitindex);
}
BOOL UnsignedLong::notEqual(UnsignedLong *from)
{
	if (equals(from)) return FALSE;
	return TRUE;
}

BOOL UnsignedLong::equals(UnsignedLong *from)
{
    for(int i = 0; i < NBYTES; i++) {
		if (_bytes[i] != from->_bytes[i]) return FALSE;
    }
	return TRUE;
}

BOOL UnsignedLong::isIn(UnsignedLong *from)
{
    for(int i = 0; i < NBYTES; i++) {
		if ((_bytes[i] & from->_bytes[i]) != 0) return TRUE;
    }
    return FALSE;
}

UnsignedLong *UnsignedLong::oring(UnsignedLong *from)
{
    for(int i = 0; i < NBYTES; i++) {
		_bytes[i] = _bytes[i] | from->_bytes[i];
	}
	return this;
}
