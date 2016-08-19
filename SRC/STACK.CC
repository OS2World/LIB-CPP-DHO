/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: stack.cc 1.3 1995/08/13 03:21:12 teb Exp $ */


#include"stack.h"
#include<stdlib.h>
#include<iostream.h>


//-------------------------------------------------------------------
//  TStack
TStack::TStack()
{
   fFirst = (TNode*)NULL;
}


//-------------------------------------------------------------------
//  ~TStack
TStack::~TStack()
{
   ClearStack();
}


//-------------------------------------------------------------------
//  Push
void TStack::Push(TObject *obj)
{
   TNode *nd = new TNode(obj);
   nd->setNext(fFirst);
   fFirst = nd;
}


//-------------------------------------------------------------------
//  Pop
TObject *TStack::Pop()
{
   TObject *tmp = fFirst->getObject();
   TNode *tnde = fFirst;
   fFirst = fFirst->getNext();
   delete tnde;
   return tmp;
}

//-------------------------------------------------------------------
//  EmptyStack
int TStack::EmptyStack()
{
   return (fFirst==NULL);
}


//-------------------------------------------------------------------
//  ClearStack
void TStack::ClearStack()
{
  TNode *tmp;
  while (!EmptyStack())
  {
    tmp = fFirst;
    fFirst = tmp->getNext();
    delete tmp;
  }   
}


//-------------------------------------------------------------------
//  getClassName
const char *TStack::getClassName(void)
{
  return "TStack";  
}
