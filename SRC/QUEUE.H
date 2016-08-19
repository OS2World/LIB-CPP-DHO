/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: queue.h 1.4 1995/08/13 03:21:12 teb Exp $ */


#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <object.h>
#include <node.h>

class TQueue : public TObject
{
     TNode *head;
     TNode *tail;
  public:
     TQueue();
     virtual ~TQueue();
     
     void Enqueue(TObject *obj);
     TObject *Dequeue();
     
     int EmptyQueue();
     
     void ClearQueue();  
     
     virtual const char *getClassName(void);
};

#endif

