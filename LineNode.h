/* LineNode.h */

#ifndef _LINENODE_H
#define _LINENODE_H

#include "Classes.h"

#include "common.h"
#include "KtgMacro.h"

class LineNode : public CObject {
	DECLARE_SERIAL(LineNode)
private : // data members
	LineNodeList* _beforeList;
	LineNodeList* _afterList;
	LineNode *_mother;
	LineNode *_borned;
	Line* _line;
	BOOL _mark;
	BOOL _move;
	BOOL _cascade;
	void insertANodeForNodeToBeDeleted(LineNode *me,LineNode *tobedelete);
public : // member functions
	LineNode(Line *line = NIL,LineNode *before = NIL,LineNode *after = NIL);
	virtual ~LineNode();
	virtual void Serialize(CArchive& ar);
	void insertObsoleteNode(LineNode *newNode);
	void insertBefore(LineNode *linenode);
	void insertAfter(LineNode *linenode);
	void removeBefore(LineNode *linenode);
	void removeAfter(LineNode *linenode);
	void insert(LineNode *linenode,int hot_spot);
	void setFollowLines(LineNodeList *newLineNodes);
	void setFollowLinesOnNodeBoundary(LineNodeList *newLineNodes);
	void swapBeforeAfter();
	LineNodeList *beforeList();
	LineNodeList *afterList();
	BOOL neighbor(LineNode *node);
	Line *line();
	BOOL &mark();
	BOOL &move();
	BOOL &cascade();
	BOOL checkToMerge(COODView *controller,LineNodeList *lines,BOOL rubberbandingflag = TRUE);
	BOOL checkIfObsolete();
	void merge(LineNode *node,LineNodeList *wheretoput);
	void resetFlags();
	int nOfNeigborNodes();
	LineNode *removeCycle();
	BOOL hasObsoletePointNeighborAt(int x,int y);
	int nOfVisitedLinesFromANode();
};

#endif
