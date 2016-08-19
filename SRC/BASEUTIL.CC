/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: baseutil.cc 1.5 1995/08/30 00:39:55 teb Exp $ */


#include<baseutil.h>

static const char *dho_base = "Developer Helper Base Objects, version 1.0Beta";
static const char *dho_ver = "1.0B";


const char *DHOgetBaseVersion(void)
{
   return dho_base;
}

const char *DHOgetRev(void)
{
   return dho_ver;
}
