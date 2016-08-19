/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: pmutils.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include<pmutils.h>
#include<applicat.h>

HMODULE resMod = NULL;

void createPopupMenu(TWindow *parent, ULONG resource, ULONG selection)
{
   HWND hwndMenu;
   POINTL pt;

   hwndMenu = WinLoadMenu(HWND_OBJECT, NULLHANDLE,resource);

   WinQueryPointerPos(HWND_DESKTOP, &pt);
    WinPopupMenu(HWND_DESKTOP,
                        parent->getHWND(),
                        hwndMenu,
                        (SHORT)pt.x,
                        (SHORT)pt.y,
                        selection,
                        PU_NONE | PU_SELECTITEM | PU_MOUSEBUTTON1 |
                        PU_MOUSEBUTTON2 | PU_KEYBOARD);
 

}


void setModule(char *modName)
{
   DosQueryModuleHandle((PSZ)modName, &resMod);
}


HMODULE getResHMODULE()
{
    return resMod;
}


void getDefWindowPosition(ULONG &x, ULONG &y)
{
   SWP swp;
   WinQueryTaskSizePos(Application->getAnchorBlock(), 0, &swp);

   x = swp.x;
   y = swp.y;
}

void getDefWindowSize(ULONG &width, ULONG &height)
{
   SWP swp;
   WinQueryTaskSizePos(Application->getAnchorBlock(), 0, &swp);

   width = swp.cx;
   height = swp.cy;
}

void getDefWindowPlacement(ULONG &x, ULONG &y, ULONG &width, ULONG &height)
{
   SWP swp;
   WinQueryTaskSizePos(Application->getAnchorBlock(), 0, &swp);

   x = swp.x;
   y = swp.y;
   width = swp.cx;
   height = swp.cy;

}

