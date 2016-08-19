/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: baseutil.cc 1.4 1995/08/13 03:21:12 teb Exp $ */


#include<baseutil.h>

static const char *dho_base = "Developer Helper Base Objects, version 0.9a";
static const char *dho_ver = "1.0A";


const char *DHOgetBaseVersion(void)
{
   return dho_base;
}

const char *DHOgetRev(void)
{
   return dho_ver;
}
