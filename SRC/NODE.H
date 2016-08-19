/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: node.h 1.4 1995/08/13 03:21:12 teb Exp $ */


#ifndef __NODE_H__
#define __NODE_H__


#include<object.h>
#include<stdlib.h>

class TNode : public TObject
{
      TNode *fNext;   
      TObject *fObject;

   public:
      TNode(TObject *obj);
      TNode *getNext(void);
      void setNext(TNode *next);
      TObject *getObject(void);
      virtual const char *getClassName();
};




#endif   /* node.h */

