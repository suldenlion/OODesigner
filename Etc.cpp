#include "stdafx.h"

#include "KTGMacro.h"
#include "common.h"
#include "figutil.h"
#include "XCoord.h"
#include "YCoord.h"

#ifndef MYDIGITS
#define MYDIGITS (10)
#endif

void ErrorMsg(const char* s)
{
	MessageBox(NULL,s,"OODesigner Error Message",MB_OK|MB_TASKMODAL|MB_ICONERROR);
}

void WarningMsg(const char* s)
{
	MessageBox(NULL,s,"OODesigner Warning Message",MB_OK|MB_TASKMODAL|MB_ICONWARNING);
}

void InfoMsg(const char* s)
{
	MessageBox(NULL,s,"OODesigner Information Message",MB_OK|MB_TASKMODAL|MB_ICONINFORMATION);
}

int YesNoMsg(const char *s)
{
	return MessageBox(NULL,s,"OODesigner Question Message",MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION);
}

int YesNoCancelMsg(const char *s)
{
	return MessageBox(NULL,s,"OODesigner Question Message",MB_YESNOCANCEL|MB_TASKMODAL|MB_ICONQUESTION);
}

CRgn* createRegion()
{
	CRgn* tmp = new CRgn();
	tmp->CreateRectRgn(0,0,0,0);
	return tmp;
}

BOOL isValidRegion(CRgn* reg) 
{
	if (reg == NIL) return FALSE;
	if (isEmptyRegion(reg)) return FALSE;
	return TRUE;
}

BOOL isEmptyRegion(CRgn* reg)
{
	CRgn* tmp = new CRgn();
	tmp->CreateRectRgn(0,0,0,0);
	BOOL is_empty = reg->EqualRgn(tmp);
	delete tmp;
	return is_empty;
}

void checkPoints(int& x1,int& y1,int& x2,int& y2)
{
	if (x1>x2) {
		int tmpx = x1; x1 = x2; x2 = tmpx;
	}
	if (y1>y2) {
		int tmpy = y1; y1 = y2; y2 = tmpy;
	}
}

void checkPoints(XCoord& x1,YCoord& y1,XCoord& x2,YCoord& y2)
{
	if (x1.x>x2.x) {
		int tmpx = x1.x; x1.x = x2.x; x2.x = tmpx;
	}
	if (y1.y>y2.y) {
		int tmpy = y1.y; y1.y = y2.y; y2.y = tmpy;
	}
}

int distance(int x1,int y1,int x2,int y2)
{
	int len1 = x2 - x1;
	int len2 = y2 - y1;
	int len = irint((double)sqrt((double)(len1*len1+len2*len2)));
	return len;
}

int sign(double x)
{
	if (x > 0) return 1;
	return -1;
}

int sign(float x)
{
	if ( x < 0 ) return (-1);
	else return(1);
}

int sign(int x)
{
	if ( x < 0 ) return (-1);
	else return(1);
}

int getRandom(int low,int high)
{
	int num = rand();
	num = num * (high - low) / RAND_MAX;
	num = num + low;
	return num;
}

