/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: object.h 1.4 1995/08/13 03:21:12 teb Exp $ */


#ifndef __OBJECT_H__
#define __OBJECT_H__


#include<baseutil.h>

/* TObject is the base object class for all objects in the
      Developer Helper Object Set. */

class TObject
{
      const char *fCopyright;
   public:
     TObject(void);
     virtual const char *getClassName(void);
     virtual void *getKey(void);
     
     static short member(const char *ClassName, TObject Obj);
     static short member(const char *ClassName, TObject *Obj);
};




#endif

