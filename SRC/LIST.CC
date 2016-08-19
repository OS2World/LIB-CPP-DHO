/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: list.cc 1.4 1995/08/13 03:21:12 teb Exp $ */


#include"list.h"
#include"object.h"

#include<stdlib.h>
#include<memory.h>


//-------------------------------------------------------------------
//  TList
TList::TList( ListIndex aLimit, ListIndex aDelta )
{
   fCount = 0;
   fItems = 0;
   fDelta = aDelta;
   setLimit( aLimit );
}


//-------------------------------------------------------------------
//  TList
TList::TList()
{
    fItems = 0;
    fCount=0;
    fLimit=0;
    fDelta=0;
    fShouldDelete=True;
}


//-------------------------------------------------------------------
//  ~TList
TList::~TList()
{
    if( fShouldDelete )
        freeAll();
    setLimit(0);
}


//-------------------------------------------------------------------
//  at
TObject *TList::at( ListIndex index )
{
    return fItems[index];
}

//-------------------------------------------------------------------
//  atRemove
void TList::atRemove( ListIndex index )
{
    if( index >= fCount )
        error(1,0);

    fCount--;
    memmove( &fItems[index], &fItems[index+1], (fCount-index)*sizeof(TObject *) );
}


//-------------------------------------------------------------------
//  atFree
void TList::atFree( ListIndex index )
{
    TObject *item = at( index );
    atRemove( index );
    freeItem( item );
}


//-------------------------------------------------------------------
//  atInsert
void TList::atInsert(ListIndex index, TObject *item)
{
    if( index < 0 )
        error(1,0);
    if( fCount == fLimit )
        setLimit(fCount + fDelta);

    memmove( &fItems[index+1], &fItems[index], (fCount-index)*sizeof(TObject *) );
    fCount++;

    fItems[index] = item;
}


//-------------------------------------------------------------------
//  atPut
void TList::atPut( ListIndex index, TObject *item )
{
    if( index >= fCount )
        error(1,0);

    fItems[index] = item;
}


//-------------------------------------------------------------------
//  remove
void TList::remove( TObject *item )
{
    atRemove( indexOf(item) );
}


//-------------------------------------------------------------------
//  removeAll
void TList::removeAll()
{
    fCount = 0;
}


//-------------------------------------------------------------------
//  error
void TList::error( ListIndex code, ListIndex )
{
    exit(212 - code);
}


//-------------------------------------------------------------------
//  firstThat
TObject *TList::firstThat( TestFunc Test, void *arg )
{
    for( ListIndex i = 0; i < fCount; i++ )
        {
        if( Test( fItems[i], arg ) == True )
            return fItems[i];
        }
    return 0;
}


//-------------------------------------------------------------------
//  lastThat
TObject *TList::lastThat( TestFunc Test, void *arg )
{
    for( ListIndex i = fCount; i > 0; i-- )
        {
        if( Test( fItems[i-1], arg ) == True )
            return fItems[i-1];
        }
    return 0;
}


//-------------------------------------------------------------------
//  forEach
void TList::forEach( AppFunc action, void *arg )
{
    for( ListIndex i = 0; i < fCount; i++ )
        action( fItems[i], arg );
}


//-------------------------------------------------------------------
//  free
void TList::free( TObject *item )
{
    remove( item );
    freeItem( item );
}


//-------------------------------------------------------------------
//  freeAll
void TList::freeAll()
{
    for( ListIndex i =  0; i < fCount; i++ )
        freeItem( at(i) );
    fCount = 0;
}


//-------------------------------------------------------------------
//  freeItem
void TList::freeItem( TObject *item )
{
    delete item;
}

//-------------------------------------------------------------------
//  indexOf
ListIndex TList::indexOf(TObject *item)
{
    for( ListIndex i = 0; i < fCount; i++ )
        if( item == fItems[i] )
            return i;

    error(1,0);
    return NULL;
}


//-------------------------------------------------------------------
//  insert
ListIndex TList::insert( TObject *item )
{
    ListIndex loc = fCount;
    atInsert( fCount, item );
    return loc;
}


//-------------------------------------------------------------------
//  pack
void TList::pack()
{
    TObject **curDst = fItems;
    TObject **curSrc = fItems;
    TObject **last = fItems + fCount;
    while( curSrc < last )
        {
        if( *curSrc != 0 )
            *curDst++ = *curSrc;
        *curSrc++;
        }
}


//-------------------------------------------------------------------
//  setLimit
void TList::setLimit(ListIndex aLimit)
{
    if( aLimit < fCount )
        aLimit =  fCount;
    if( aLimit > maxCollectionSize)
        aLimit = maxCollectionSize;
    if( aLimit != fLimit )
        {
        TObject **aitems;
        if (aLimit == 0 )
            aitems = 0;
        else
            {
            aitems = new TObject *[aLimit];
            if( fCount !=  0 )
                memcpy( aitems, fItems, fCount*sizeof(TObject *) );
            }
        delete fItems;
        fItems =  aitems;
        fLimit =  aLimit;
        }
}


//-------------------------------------------------------------------
//  getCount
ListIndex TList::getCount(void)
{ 
   return fCount; 
}


//-------------------------------------------------------------------
//  getClassName
const char *TList::getClassName(void)
{
   return "TList";
}
