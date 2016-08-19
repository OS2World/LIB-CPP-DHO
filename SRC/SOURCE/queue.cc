/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: queue.cc 1.3 1995/08/13 03:21:12 teb Exp $ */


#include"queue.h"
#include<stdlib.h>
#include<iostream.h>

//-------------------------------------------------------------------
//  TQueue
TQueue::TQueue()
{
   head = NULL;
   tail = NULL;
}


//-------------------------------------------------------------------
//  ~TQueue
TQueue::~TQueue()
{
   ClearQueue();
}


//-------------------------------------------------------------------
//  Enqueue
void TQueue::Enqueue(TObject *obj)
{
   TNode *nd = new TNode(obj);
 
   if (head==NULL)
   {
      head = nd;
      tail = nd;
   }
   else 
   {
      tail->setNext(nd);
      tail = nd;
   }
}


//-------------------------------------------------------------------
//  Dequeue
TObject *TQueue::Dequeue()
{
   TObject *ret;
   TNode *tmp;
   
   ret = head->getObject();
   tmp = head;
   head = tmp->getNext();
   delete tmp;
   return ret;
}


//-------------------------------------------------------------------
//  EmptyQueue
int TQueue::EmptyQueue()
{
   return (head==NULL);   
}


//-------------------------------------------------------------------
//  ClearQueue
void TQueue::ClearQueue()
{
   TNode *tmp;
   while (!EmptyQueue())
   {
      tmp = head;
      head->setNext(tmp->getNext());
      delete tmp;
   }
}


//-------------------------------------------------------------------
//  getClassName
const char *TQueue::getClassName(void)
{
   return "TQueue";
}
