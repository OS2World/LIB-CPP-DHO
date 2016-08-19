/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: baseutil.h 1.4 1995/08/13 03:21:12 teb Exp $ */

#ifndef __BASEUTIL_H__
#define __BASEUTIL_H__


static const char *CopyrightNotice = "(C) 1994, Thomas E. Bednarz, Jr.";

enum Boolean { False, True };

const char *DHOgetBaseVersion(void);
const char *DHOgetRev(void);


#endif

