/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: multnode.h 1.2 1995/08/13 03:21:12 teb Exp $ */


#ifndef __MULTNODE_H__
#define __MULTNODE_H__


#include"object.h"
#include<stdlib.h>


class TxNode : public TObject
{
   protected:
      TxNode *lessThan;
      TxNode *greaterThan;
      TObject *lowObj;
      TObject *highObj;
   public:      
      TxNode(TxNode *lt=NULL, TxNode *gt=NULL,
	      TObject *lo=NULL, TObject *ho=NULL);
      virtual ~TxNode();
      TObject *getHighObject();
      TObject *getLowObject();
      void setHighObject(TObject *obj);
      void setLowObject(TObject *obj);

      TxNode *getLowNode();
      TxNode *getHighNode();
      void setHighNode(TxNode *nde);
      void setLowNode(TxNode *nde);
      virtual const char *getClassName();
};


class T3Node : public TxNode
{
   private:

      TxNode *middle;

   public:
      T3Node(TxNode *lt=NULL, TxNode *mid=NULL, TxNode *gt=NULL,
	      TObject *lo=NULL, TObject *ho=NULL);
      virtual ~T3Node();
      TxNode *getMiddleNode();
      void setMiddleNode(TxNode *nde);
      virtual const char *getClassName();
};

class T4Node : public TxNode
{
   private:
      TxNode *between1;
      TxNode *between2;
      TObject *midObj;
   public:
      T4Node(TxNode *lt=NULL, TxNode *mn1=NULL, TxNode *mn2=NULL,TxNode *gt=NULL,
	      TObject *lo=NULL, TObject *mo=NULL, TObject *ho=NULL);
      ~T4Node();

      TxNode *getLoBetweenNode();
      TxNode *getHiBetweenNode();
      void setLoBetweenNode(TxNode *nde);
      void setHiBetweenNode(TxNode *nde);

      TObject *getMiddleObj();
      void setMiddleObj(TObject *obj);
      
      virtual const char *getClassName();
};

#endif  //multnode.h

