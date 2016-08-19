/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: node.cc 1.3 1995/08/13 03:21:12 teb Exp $ */


#include"node.h"
#include<STDLIB.H>
#include<iostream.h>

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//  *TNode
//-------------------------------------------------------------------
//  setNext
void TNode::setNext(TNode *next)
{
   fNext=next;   
}

//-------------------------------------------------------------------
//  TNode
TNode::TNode(TObject *obj)
{
   fNext = NULL;
   fObject = obj;
}


//-------------------------------------------------------------------
//  getNext
TNode *TNode::getNext(void)
{
   return fNext;
}


//-------------------------------------------------------------------
//  getObject
TObject *TNode::getObject(void)
{
   return fObject;
}


//-------------------------------------------------------------------
//  getClassName
const char *TNode::getClassName()
{
   return "TNode";
}



