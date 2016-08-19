/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: stack.h 1.4 1995/08/13 03:21:12 teb Exp $ */


#ifndef __STACK_H__
#define __STACK_H__


#include<object.h>
#include<node.h>

class TStack : public TObject
{
      TNode *fFirst;
   public:
      TStack();
      virtual ~TStack();
      
      void Push(TObject *obj);
      TObject *Pop();
      int EmptyStack();
      void ClearStack();
      
      virtual const char *getClassName(void);
};

#endif

