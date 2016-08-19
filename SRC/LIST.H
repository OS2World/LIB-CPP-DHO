/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: list.h 1.4 1995/08/13 03:21:12 teb Exp $ */

#ifndef __LIST_H__
#define __LIST_H__


#include <object.h>

typedef short unsigned ushort;
typedef unsigned char uchar;


typedef Boolean (TestFunc)( TObject*, void * );
typedef void (*AppFunc)( TObject*, void* );


const char EOS = '\0';

typedef short ListIndex;

const ccNotFound = -1;
const maxCollectionSize = (int)((65536uL - 16)/sizeof( TObject* ));


class TList: public TObject
{

      virtual void freeItem( TObject *item );
   protected:

       TObject **fItems;
       ListIndex fCount;
       ListIndex fLimit;
       ListIndex fDelta;
       Boolean fShouldDelete;   

		 TList();
   public:
       TList(ListIndex aLimit, ListIndex aDelta);
       virtual ~TList();

       TObject *at(ListIndex index);
       virtual ListIndex indexOf(TObject *item);

       void atFree(ListIndex index);   
       void atRemove(ListIndex index);
       void remove(TObject *item);
       void removeAll();
       void free(TObject *item);
       void freeAll();

       void atInsert(ListIndex index, TObject *item);
       void atPut(ListIndex index, TObject *item);
       virtual ListIndex insert(TObject *item);

       static void error(ListIndex code, ListIndex info);

       TObject *firstThat(TestFunc Test, void *arg);
       TObject *lastThat(TestFunc Test, void *arg);
       void forEach(AppFunc action, void *arg); 

       void pack();
       virtual void setLimit(ListIndex aLimit);

       ListIndex getCount();

       virtual const char *getClassName(void);

};

#endif

