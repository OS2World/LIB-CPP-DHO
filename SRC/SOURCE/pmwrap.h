/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: pmwrap.h 1.1 1995/08/25 08:24:00 teb Exp $ */

#ifndef __PMWRAP_H__
#define __PMWRAP_H__

#include"window.h"

/************************************************************
 *
 *   This class effectively forms a means to wrap Presentation Manager
 *   Window classes inside of a Developer Window Object descended
 *   from the class TWindow.  Using the methods in the TWindow class, 
 *   it is easy to override default behaviors of any PM WndClass which
 *   is wrapped with this class.  The init function member simply subclasses
 *   the window proc, setting the TWindow data member oldWndProc to the
 *   original wndproc. 
 **************************************************************/
class TPMWrapWindow : public TWindow
{

   public:
     TPMWrapWindow(ULONG id, TWinBase *parent);
     virtual BOOL init();
};

#endif
