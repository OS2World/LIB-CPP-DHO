/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: object.cc 1.3 1995/08/13 03:21:12 teb Exp $ */


#include<object.h>
#include<string.h>

//-------------------------------------------------------------------
//  TObject
TObject::TObject(void)
{
   fCopyright = CopyrightNotice;
}

//-------------------------------------------------------------------
//   getClassName
const char *TObject::getClassName(void)
{
   return "TObject";
}

//-------------------------------------------------------------------
//  getKey
void *TObject::getKey(void)
{
   return this;
}

short member(const char *ClassName, TObject Obj)
{
   return (strcmp(ClassName, Obj.getClassName())==0);   
}

short member(const char *ClassName, TObject *Obj)
{
   return (strcmp(ClassName, Obj->getClassName())==0);
}
