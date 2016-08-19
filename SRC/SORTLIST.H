/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: sortlist.h 1.4 1995/08/13 03:21:12 teb Exp $ */


#ifndef __SORTLIST_H__
#define __SORTLIST_H__

#include<list.h>

class TSortedList: public TList
{

      virtual int compare( void *key1, void *key2 ) = 0;
  
   protected:

      TSortedList(void);
      virtual void *keyOf( TObject *item );
      Boolean duplicates;
   public:

      TSortedList( ListIndex aLimit, ListIndex aDelta);

      virtual Boolean search( void *key, ListIndex & index );

      virtual ListIndex indexOf( TObject *item );
      virtual ListIndex insert( TObject *item );

      void KeepDuplicates(Boolean dups);
      Boolean getDuplicateState(void);

      virtual const char *getClassName(void);
};


#endif

