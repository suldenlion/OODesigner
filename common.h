#ifndef _COMMON_H
#define _COMMON_H

#include "Math.h"

//extern BOOL runningAsInPlaceFrame();

// Message boxes
extern void ErrorMsg(const char*);
extern void InfoMsg(const char*);
extern void WarningMsg(const char*);
extern int YesNoMsg(const char *s);
extern int YesNoCancelMsg(const char *s);
#endif