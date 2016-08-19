/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: sortlist.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"sortlist.h"

//-------------------------------------------------------------------
//  TSortedList
TSortedList::TSortedList(void)
{
   
};


//-------------------------------------------------------------------
//  keyOf
void *TSortedList::keyOf( TObject *item ) 
{ 
   return item->getKey(); 
}


//-------------------------------------------------------------------
//  TSortedList
TSortedList::TSortedList( ListIndex aLimit, ListIndex aDelta) :
	    TList( aLimit, aDelta )
{
   fDelta = aDelta; 
   setLimit( aLimit ); 
}


//-------------------------------------------------------------------
//  indexOf
ListIndex TSortedList::indexOf(TObject *item)
{
    ListIndex  i;

    if( search( keyOf(item), i ) == 0 )
        return ccNotFound;
    else
        {
        if( duplicates )
            {
            while( i < fCount && item != fItems[i] )
                i++;
            }
        if( i < fCount )
            return i;
        else
            return ccNotFound;
        }
}


//-------------------------------------------------------------------
//  insert
ListIndex TSortedList::insert( TObject *item )
{
    ListIndex  i;
    if( search( keyOf(item), i ) == 0 || duplicates )   // order dependency!
        atInsert( i, item );                            // must do Search
                                                        // before calling
                                                        // AtInsert
    return i;
}


//-------------------------------------------------------------------
//  search
Boolean TSortedList::search( void *key, ListIndex& index )
{
    ListIndex l = 0;
    ListIndex h = fCount - 1;
    Boolean res = False;
    while( l <= h )
        {
        ListIndex i = (l +  h) >> 1;
        ListIndex c = compare( keyOf( fItems[i] ), key );
        if( c < 0 )
            l = i + 1;
        else
            {
            h = i - 1;
            if( c == 0 )
                {
                res = True;
                if( !duplicates )
                    l = i;
                }
            }
        }
    index = l;
    return res;
}


//-------------------------------------------------------------------
//  KeepDuplicates
void TSortedList::KeepDuplicates(Boolean dups)
{
   duplicates = dups;
}


//-------------------------------------------------------------------
//  getDuplicateState
Boolean TSortedList::getDuplicateState(void)
{
   return duplicates;
}

//-------------------------------------------------------------------
//  getClassName
const char *TSortedList::getClassName(void)
{
   return "TSortedList";
}

