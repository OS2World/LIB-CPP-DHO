/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: multnode.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"multnode.h"
#include<STDLIB.H>


//-------------------------------------------------------------------
//-------------------------------------------------------------------
//  *TxNode
//-------------------------------------------------------------------
//  TxNode
TxNode::TxNode(TxNode *lt, TxNode *gt,
	      TObject *lo, TObject *ho)
{
  lessThan = lt;
  greaterThan = gt;

  lowObj = lo;
  highObj = ho;
}



//-------------------------------------------------------------------
//  ~TxNode
TxNode::~TxNode()
{

}



//-------------------------------------------------------------------
//  getHighObject
TObject *TxNode::getHighObject()
{
    return highObj;
}



//-------------------------------------------------------------------
//  getLowObject
TObject *TxNode::getLowObject()
{
   return lowObj;
}




//-------------------------------------------------------------------
//  setHighObject
void TxNode::setHighObject(TObject *obj)
{
  highObj = obj;
}



//-------------------------------------------------------------------
//  setLowObject
void TxNode::setLowObject(TObject *obj)
{
   lowObj = obj;
}



//-------------------------------------------------------------------
//  getLowNode
TxNode *TxNode::getLowNode()
{
   return lessThan;
}



//-------------------------------------------------------------------
//  getHighNode
TxNode *TxNode::getHighNode()
{
   return greaterThan;
}



//-------------------------------------------------------------------
//  setHighNode
void TxNode::setHighNode(TxNode *nde)
{
   greaterThan = nde;
}



//-------------------------------------------------------------------
//  setLowNode
void TxNode::setLowNode(TxNode *nde)
{
   lessThan = nde;
}


//-------------------------------------------------------------------
//  getClassName
const char *TxNode::getClassName()
{
   return "TxNode";
}



//-------------------------------------------------------------------
//-------------------------------------------------------------------
//  T3Node
//-------------------------------------------------------------------
//  T3Node
T3Node::T3Node(TxNode *lt, TxNode *mid, TxNode *gt,
	      TObject *lo, TObject *ho):
   TxNode(lt, gt, lo, ho)
{
   middle = mid;
}



//-------------------------------------------------------------------
//  ~T3Node
T3Node::~T3Node()
{


}



//-------------------------------------------------------------------
//  getMiddle
TxNode *T3Node::getMiddleNode()
{
   return middle;
}

//-------------------------------------------------------------------
//  setMiddle
void T3Node::setMiddleNode(TxNode *nde)
{
   middle = nde;
}

//-------------------------------------------------------------------
//  getClassName
const char *T3Node::getClassName()
{
   return "T3Node";
}


//-------------------------------------------------------------------
//-------------------------------------------------------------------
//  			*T4Node
//-------------------------------------------------------------------
//  T4Node
T4Node::T4Node(TxNode *lt, TxNode *mn1, TxNode *mn2,TxNode *gt,
	      TObject *lo, TObject *mo, TObject *ho):
   TxNode(lt, gt, lo, ho)

{
   between1 = mn1;
   between2 = mn2;
   midObj = mo;
}


//-------------------------------------------------------------------
//  ~T4Node
T4Node::~T4Node()
{


}


//-------------------------------------------------------------------
//  getLoBetweenNode
TxNode *T4Node::getLoBetweenNode()
{
   return between1;
}

//-------------------------------------------------------------------
//  getHiBetweenNode
TxNode *T4Node::getHiBetweenNode()
{
   return between2;
}

//-------------------------------------------------------------------
//  setLoBetweenNode
void T4Node::setLoBetweenNode(TxNode *nde)
{
   between1 = nde;
}

//-------------------------------------------------------------------
//  setHiBetweenNode
void T4Node::setHiBetweenNode(TxNode *nde)
{
   between2 = nde;
}

//-------------------------------------------------------------------
//  getMiddleObj
TObject *T4Node::getMiddleObj()
{
   return midObj;
}

//-------------------------------------------------------------------
//  setMiddleObj
void T4Node::setMiddleObj(TObject *obj)
{
   midObj = obj;
}

//-------------------------------------------------------------------
//  getClassName      
const char *T4Node::getClassName()
{
   return "T4Node";
}

