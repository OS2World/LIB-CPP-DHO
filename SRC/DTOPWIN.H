/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: dtopwin.h 1.4 1995/08/21 05:49:22 teb Exp $ */

#ifndef __DTOPWIN_H__
#define __DTOPWIN_H__


#include<winbase.h>

class TDesktopWindow : public TWinBase
{
 
   public:
      TDesktopWindow();
      ~TDesktopWindow();
      virtual BOOL init();
      virtual const char *getClassName();
      
      virtual void doCommand(WinMsg wm);
};

#endif
