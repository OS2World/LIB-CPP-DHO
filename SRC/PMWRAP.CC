/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: pmwrap.cc 1.1 1995/08/25 08:24:00 teb Exp $ */
#define INCL_WIN
#include<os2.h>

#include"pmwrap.h"


//-------------------------------------------------------------------
//  TPMWrapWindow
TPMWrapWindow::TPMWrapWindow(ULONG id, TWinBase *parent):
   TWindow(id, parent)
{

}


//-------------------------------------------------------------------
//  init
BOOL TPMWrapWindow::init()
{
   if (hwnd != (HWND)NULL)
   {
      WinSetWindowULong(hwnd,0,(ULONG)this);

      oldWndProc = WinSubclassWindow(hwnd, (PFNWP)getWindowProc());
      if (oldWndProc==(PFNWP)NULL)
      {
         WinDestroyWindow(hwnd);	
         return FALSE;
      }
      return TRUE;
   }
   return FALSE;   
}
