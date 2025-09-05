#ifndef KTG_MACRO_H
#define KTG_MACRO_H

// Figure Ids
// These id should be assigned to concrete figures except Figure object.

typedef struct _nameTable {
	const char *name;
} Names;
#define	NTABLE(v)   (sizeof v / sizeof v[0])
#define	ENDTABLE(v) (v - 1 + sizeof v / sizeof v[0])

#define KTG_FIGURE				(0)
#define KTG_BOX					(1)
#define KTG_TEXT				(2)
#define KTG_LINE				(3)
#define KTG_LINES				(4)
#define KTG_CLASSTEMPLATE		(5)
#define KTG_CLASSTEXT			(6)
#define KTG_TRIANGLE			(7)
#define KTG_DIAMOND				(8)
#define KTG_ROUNDBOXA			(9)
#define KTG_ROUNDBOXB			(10)
#define KTG_CIRCLE				(11)
#define KTG_STATE				(12)
#define KTG_STATETEXT			(13)
#define KTG_DEPENDENCY			(14)
#define KTG_GENERALIZATION		(15)
#define KTG_REFINEMENT			(16)
#define KTG_AGGREGATION			(17)
#define KTG_COMPOSITION			(18)
#define KTG_ASSOCIATION			(19)
#define KTG_PACKAGETEMPLATE		(20)
#define KTG_PACKAGETEXT			(21)
#define KTG_INITIALSTATE		(22)
#define KTG_FINALSTATE			(23)
#define KTG_TRANSITION			(24)
#define KTG_ACTIVITY			(25)
#define KTG_BEGINACTIVITY		(26)
#define	KTG_ENDACTIVITY			(27)
#define KTG_SYNCHRONIZATIONBAR	(28)
#define KTG_ACTIVITYTEXT		(29)
#define KTG_TRIGGER				(30)
#define KTG_ACTOR				(31)
#define KTG_ACTORNAMETEXT		(32)
#define KTG_USECASE				(33)
#define KTG_USECASETEXT			(34)
#define KTG_COLLABORATIONOBJECT (35)
#define KTG_OBJECTTEXT			(36)
#define KTG_MESSAGEFLOW			(37)
#define KTG_USECASELINK			(38)
#define KTG_USECASEUSESLINK		(39)
#define KTG_USECASEEXTENDSLINK	(40)
#define KTG_STATICCONNECTIONTEXT (41)
#define KTG_SYSTEMBOUNDARY		(42)
#define KTG_MESSAGETEXT			(43)
#define KTG_COLOBJMESSAGETEXT	(44)
#define KTG_EVENTTEXT			(45)
#define KTG_TRIGGERTEXT			(46)
#define KTG_SYNCCONDITIONTEXT	(47)
#define KTG_HARDWARENODE		(48)
#define KTG_COMPONENTTEXT		(49)
#define KTG_COMPONENTTEMPLATE	(50)
#define KTG_HWCONNECTION		(51)
#define KTG_HWCONNECTIONTEXT	(52)
#define KTG_COMMUNICATION		(53)
#define KTG_SEQUENCEOBJECT		(54)
#define KTG_ACTIVATIONBAR		(55)
#define KTG_SYNCMESSAGE			(56)
#define KTG_SEQUENCEMESSAGETEXT	(57)
#define KTG_ASYNCMESSAGE		(58)
#define KTG_RETURNMESSAGE		(59)
#define KTG_SEQUENCESELFDELEGATION	(60)
#define KTG_ONELINETEXT			(61)
#define KTG_TEMPLATECLASSTAGTEXT	(62)
#define KTG_CONNECTIONTEXT		(63)
#define KTG_QUALIFICATIONTEXT	(64)
#define KTG_INTERFACEPORTTEXT	(65)
#define KTG_BUCKET				(66)
#define KTG_NOTE				(67)
#define KTG_NOTETEXT			(68)
#define KTG_ANCHOR				(69)
#define KTG_WIDESTATE			(70)
#define KTG_WIDEPACKAGE			(71)

// Diagram Types

#define KTG_PROJECT_WORKSPACE		(1)
#define KTG_TEXT_FILE				(2) 
#define KTG_CLASS_DIAGRAM			(3)
#define KTG_USE_CASES				(4) 
#define KTG_SEQUENCE_DIAGRAM		(5) 
#define KTG_COLLABORATION_DIAGRAM	(6) 
#define KTG_STATE_DIAGRAM			(7)
#define KTG_ACTIVITY_DIAGRAM		(8)
#define KTG_DEPLOYMENT_DIAGRAM		(9)

#define KTG_MAX_DGM_STYLE	    (8)

// Drawing Context

#define KTG_DRAWING				(1<<0)
#define KTG_FOCUSING			(1<<1)
#define KTG_HIGHLIGHTING        (1<<2)
#define KTG_RUBBERBANDING		(1<<3)
#define KTG_ERASING				(1<<4)

#define NIL						(0)
#define	KTGOK					(1)
#define KTGNOTOK				(0)

#define	ON						(TRUE)
#define OFF						(FALSE)

#define	ABSOLUTELY				(1)

#ifndef M_PI
#define M_PI (3.1415926535897)
#endif

#define DEFAULT_ID		(0)
#define PUBLIC_ID		(1)
#define PROTECTED_ID	(2)
#define PRIVATE_ID		(3)

#define HAT_WIDTH	(20)
#define HAT_HEIGHT	(10)

#define OODMAXINT					((int)(0x8FFF)) // two bytes max integer
#define MAXSCROLL				(10000)

#define theAppPtr				((COODApp*)AfxGetApp())
#define mainFramePtr			((CMainFrame *)AfxGetMainWnd())

#define _OOD_EXT	(".ood")
#define _USE_EXT	(".use")
#define _SEQ_EXT	(".seq")
#define _COL_EXT	(".col")
#define _STA_EXT	(".sta")
#define _ACT_EXT	(".act")
#define _DEP_EXT	(".dep")
#define _PAK_EXT	(".pac")

// for .ood
#define _EXT_LEN4	(4)
// for others 
#define _EXT_LEN5	(4)

#endif