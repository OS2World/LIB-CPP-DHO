/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: winbase.h 1.9 1995/09/03 01:22:29 teb Exp $ */


#ifndef __WINBASE_H__
#define __WINBASE_H__

#define INCL_PM
#define INCL_WIN
#define INCL_GPI
#include <os2.h>             
#include<object.h>


const ULONG WinBase_NoResource = 0;

class WinMsg
{
   public:
      HWND hwnd;
      ULONG msg;
      MPARAM mp1;
      MPARAM mp2;
};


class TWinBase : public TObject
{
 
   protected:
     ULONG fResource;
     HWND hwnd;
   public:
      TWinBase(ULONG id);
      virtual ~TWinBase(void);
      virtual BOOL init()=0;
      virtual const char *getClassName(void);
      HWND getHWND(void);
      virtual void doCommand(WinMsg wm);
      virtual void doControl(WinMsg wm);

      BOOL isEnabled();
      BOOL enableUpdate(BOOL enable);
      BOOL isVisible();

      virtual BOOL setParent(TWinBase *parent, BOOL redraw);
      BOOL isChild(TWinBase *parent);

      void hideWindow();
      void showWindow();

      void setFrameTitle(char *title);
      void shellSetPosition(); 
      void setWindowPosition(LONG x, LONG y);
      void getWindowPosition(LONG &x, LONG &y, LONG &cx, LONG &cy);
      void setWindowSize(LONG cx, long cy);
      void update();
      void forceUpdate();
};


#endif  /* winbase */

