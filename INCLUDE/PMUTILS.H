/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: pmutils.h 1.2 1995/08/13 03:21:12 teb Exp $ */

#ifndef __PMUTILS_H__
#define __PMUTILS_H__

#define INCL_DOSMODULEMGR
#define INCL_WIN
#include <os2.h>

#include<window.h>

void createPopupMenu(TWindow *parent, ULONG resource, ULONG selection);
void setModule(char *modName);
HMODULE getResHMODULE();

// presentation manager window placement
void getDefWindowPosition(ULONG &x, ULONG &y);
void getDefWindowSize(ULONG &width, ULONG &height);
void getDefWindowPlacement(ULONG &x, ULONG &y, ULONG &width, ULONG &height);

#endif
