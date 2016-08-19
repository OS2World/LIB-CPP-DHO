/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: winbase.cc 1.8 1995/08/21 05:26:50 teb Exp $ */


#include "winbase.h"
#include "applicat.h"

//-------------------------------------------------------------------
//  getScreenPS
HPS TWinBase::getScreenPS()
{
   return WinGetPS( getHWND() );
}

//-------------------------------------------------------------------
//  TWinBase
TWinBase::TWinBase(ULONG id)
{
   fResource = id;
   hwnd = (HWND)NULL;
}

//-------------------------------------------------------------------
//  ~TWinBase
TWinBase::~TWinBase(void)
{
   if (hwnd!=(HWND)NULL)
      WinDestroyWindow(hwnd);
}

//-------------------------------------------------------------------
//   getClassName
const char *TWinBase::getClassName(void)
{
   return "TWinBase";
}

//-------------------------------------------------------------------
//   GetFrame
HWND TWinBase::getHWND(void)
{
   return hwnd;
}

//-------------------------------------------------------------------
//  doControl
void TWinBase::doControl(WinMsg wm)
{
   
}


//-------------------------------------------------------------------
//   doCommand
void TWinBase::doCommand(WinMsg wm)
{

}


//-------------------------------------------------------------------
//   isEnabled
BOOL TWinBase::isEnabled()
{
   return WinIsWindowEnabled( getHWND() );
}

//-------------------------------------------------------------------
//   enableUpdate
BOOL TWinBase::enableUpdate(BOOL enable)
{
   WinEnableWindowUpdate( getHWND(),enable);
   return TRUE;
}

//-------------------------------------------------------------------
//   isVisible
BOOL TWinBase::isVisible()
{
   return WinIsWindowVisible( getHWND() );
}


//-------------------------------------------------------------------
//   setParent
BOOL TWinBase::setParent(TWinBase *parent, BOOL redraw)
{
   BOOL res = WinSetParent( getHWND(), parent->getHWND(), redraw);
   //fParent = parent;

   return res;
}


//-------------------------------------------------------------------
//   setFrameTitle
void TWinBase::setFrameTitle(char *title)
{
   HWND hwndTitlebar = WinWindowFromID(hwnd, FID_TITLEBAR);
   if (hwndTitlebar)
      WinSetWindowText(hwndTitlebar, (PSZ)title);

}

//-------------------------------------------------------------------
//   isChild
BOOL TWinBase::isChild(TWinBase *parent)
{
   return WinIsChild(getHWND() , parent->getHWND() );
}


//-------------------------------------------------------------------
//   
void TWinBase::shellSetPosition()
{
   SWP swp;

   WinQueryTaskSizePos(Application->getAnchorBlock(),
                       0, &swp);

   setWindowPosition(swp.x, swp.y);
}



//-------------------------------------------------------------------
//   setWindowPosition
void TWinBase::setWindowPosition(LONG x, LONG y)
{
   WinSetWindowPos(getHWND(), (HWND) NULL,  x, y, 0,0, SWP_MOVE);

}

//-------------------------------------------------------------------
//   getWindowPosition
void TWinBase::getWindowPosition(LONG &x, LONG &y, LONG &cx, LONG &cy)
{
   SWP swp;

   WinQueryWindowPos( getHWND(),&swp);
   x = swp.x;
   y = swp.y;
   cx = swp.cx;
   cy = swp.cy;

}


//-------------------------------------------------------------------
//   setWindowSize
void TWinBase::setWindowSize(LONG cx, long cy)
{
   LONG x,y,dum1, dum2;
   getWindowPosition(x,y,dum1, dum2);
   WinSetWindowPos(getHWND(), (HWND)NULL, x,y,cx,cy, SWP_MOVE | SWP_SIZE);
}



//-------------------------------------------------------------------
//   hideWindow
void TWinBase::hideWindow()
{
   WinShowWindow(getHWND(), FALSE);
}


//-------------------------------------------------------------------
//   showWindow
void TWinBase::showWindow()
{
   WinShowWindow(getHWND(), TRUE);
}


//-------------------------------------------------------------------
//   Update
void TWinBase::Update()
{
   WinUpdateWindow(getHWND());
}


//-------------------------------------------------------------------
//   ForceUpdate
void TWinBase::forceUpdate()
{
   WinInvalidateRect(hwnd, NULL, TRUE);
}

