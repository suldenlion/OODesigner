#ifndef _FIGUTIL_H
#define _FIGUTIL_H

#include "Classes.h"

#ifndef RectangleOut
#define RectangleOut (0)
#endif
#ifndef RectangleIn
#define RectangleIn  (1)
#endif
#ifndef RectanglePart
#define RectanglePart (2)
#endif

#ifndef irint
#define irint int
#endif

extern CRgn* createRegion();
extern BOOL isEmptyRegion(CRgn* reg);
extern BOOL isValidRegion(CRgn* reg);

extern UnsignedLong *IAMFIGURE;
extern UnsignedLong *IAMBOX;
extern UnsignedLong *IAMTEXT;
extern UnsignedLong *IAMLINE;
extern UnsignedLong *IAMLINES;
extern UnsignedLong *IAMCLASSTEMPLATE;
extern UnsignedLong *IAMCLASSTEXT;
extern UnsignedLong *IAMPACKAGETEXT;
extern UnsignedLong *IAMTRIANGLE;
extern UnsignedLong *IAMDIAMOND;
extern UnsignedLong *IAMROUNDBOXA;
extern UnsignedLong *IAMROUNDBOXB;
extern UnsignedLong *IAMSTATE;
extern UnsignedLong *IAMSTATETEXT;
extern UnsignedLong *IAMDEPENDENCY;
extern UnsignedLong *IAMPACKAGETEMPLATE;
extern UnsignedLong *IAMGENERALIZATION;
extern UnsignedLong *IAMAGGREGATION;
extern UnsignedLong *IAMCIRCLE;
extern UnsignedLong *IAMINITIALSTATE;
extern UnsignedLong *IAMFINALSTATE;
extern UnsignedLong *IAMTRANSITION;
extern UnsignedLong *IAMACTIVITY;
extern UnsignedLong *IAMBEGINACTIVITY;
extern UnsignedLong *IAMENDACTIVITY;
extern UnsignedLong	*IAMSYNCHRONIZATIONBAR;
extern UnsignedLong *IAMACTIVITYTEXT;
extern UnsignedLong *IAMTRIGGER;
extern UnsignedLong *IAMACTOR;
extern UnsignedLong *IAMACTORNAMETEXT;
extern UnsignedLong *IAMUSECASE;
extern UnsignedLong *IAMUSECASETEXT;
extern UnsignedLong *IAMCOLLABORATIONOBJECT;
extern UnsignedLong *IAMOBJECTTEXT;
extern UnsignedLong *IAMMESSAGEFLOW;
extern UnsignedLong *IAMUSECASEUSESLINK;
extern UnsignedLong *IAMUSECASELINK;
extern UnsignedLong *IAMUSECASEEXTENDSLINK;
extern UnsignedLong *IAMSTATICCONNECTIONTEXT;
extern UnsignedLong *IAMSYSTEMBOUNDARY;
extern UnsignedLong *IAMMESSAGETEXT;
extern UnsignedLong *IAMCOLOBJMESSAGETEXT;
extern UnsignedLong *IAMEVENTTEXT;
extern UnsignedLong *IAMTRIGGERTEXT;
extern UnsignedLong *IAMSYNCCONDITIONTEXT;
extern UnsignedLong *IAMHARDWARENODE;
extern UnsignedLong *IAMCOMPONENTTEXT;
extern UnsignedLong *IAMCOMPONENTTEMPLATE;
extern UnsignedLong *IAMHWCONNECTION;
extern UnsignedLong *IAMHWCONNECTIONTEXT;
extern UnsignedLong *IAMCOMMUNICATION;
extern UnsignedLong *IAMASSOCIATION;
extern UnsignedLong *IAMSEQUENCEOBJECT;
extern UnsignedLong *IAMACTIVATIONBAR;
extern UnsignedLong *IAMSYNCMESSAGE;
extern UnsignedLong *IAMSEQUENCEMESSAGETEXT;
extern UnsignedLong *IAMASYNCMESSAGE;
extern UnsignedLong *IAMRETURNMESSAGE;
extern UnsignedLong *IAMSEQUENCESELFDELEGATION;
extern UnsignedLong *IAMONELINETEXT;
extern UnsignedLong *IAMTEMPLATECLASSTAGTEXT;
extern UnsignedLong *IAMCONNECTIONTEXT;
extern UnsignedLong *IAMQUALIFICATIONTEXT;
extern UnsignedLong *IAMINTERFACEPORTTEXT;
extern UnsignedLong *IAMBUCKET;
extern UnsignedLong *IAMNOTE;
extern UnsignedLong *IAMNOTETEXT;
extern UnsignedLong	*IAMANCHOR;
extern UnsignedLong	*IAMWIDESTATE;
extern UnsignedLong *IAMWIDEPACKAGE;

extern UnsignedLong *WEARENODEOBJECTS;
extern UnsignedLong *WEAREEDITABLEOBJECTS;
extern UnsignedLong *WEARETEXTOBJECTS;
extern UnsignedLong *WEARELINES;
extern UnsignedLong *WEARECONNECTIONS;
extern UnsignedLong *WEARESIMPLECONNECTIONS;
extern UnsignedLong *WEARECLASSOBJECTS;
extern UnsignedLong *WEARESTATEOBJECTS;
extern UnsignedLong *WEAREACTIVITYOBJECTS;
extern UnsignedLong *WEAREUSECASEOBJECTS;
extern UnsignedLong *WEARECOLLABORATIONOBJECTS;
extern UnsignedLong *WEAREWIDEOBJECTS;
extern UnsignedLong *WEAREDEPLOYMENTOBJECTS;
extern UnsignedLong *WEAREFORKABLELINES;
extern UnsignedLong *WEARESEQUENCEOBJECTS;
extern UnsignedLong *WEAREONELINETEXTS;
extern UnsignedLong *WEARECLIPBOARDOBJECTS;

#endif