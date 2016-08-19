/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: framewin.cc 1.15 1995/08/27 08:21:15 teb Exp $ */

#include"framewin.h"
#include"applicat.h"
#include"pmutils.h"
#define INCL_WIN
#include<os2.h>




TFrameWindowAttr defFrame = {   TRUE,TRUE, FALSE,FALSE,TRUE, TRUE,
                            TRUE, TRUE,FALSE, FALSE, FALSE, TRUE, 0,0,0,0};

//-------------------------------------------------------------------
//   TFrameWindow
TFrameWindow::TFrameWindow(ULONG id, char *title):
   TWindow(id, NULL)
{
   fFrAttr = defFrame;
   fCreateFlags = 0;
   fShellPos = FALSE;
   getDefWindowPlacement(fX, fY, fcX, fcY);   

   fTitle = title;
}


//-------------------------------------------------------------------
//   ~TFrameWindow
TFrameWindow::~TFrameWindow()
{

}


//-------------------------------------------------------------------
//   Init
BOOL TFrameWindow::init()
{
   if (fFrAttr.titlebar)
      fCreateFlags |= FCF_TITLEBAR;
   if (fFrAttr.sysmenu)
      fCreateFlags |= FCF_SYSMENU;
   if (fFrAttr.menu)
      fCreateFlags |= FCF_MENU;
   if (fFrAttr.icon)
      fCreateFlags |= FCF_ICON;
   if (fFrAttr.minbutton)
      fCreateFlags |= FCF_MINBUTTON;
   if (fFrAttr.maxbutton)
      fCreateFlags |= FCF_MAXBUTTON;
   if (fFrAttr.sizeborder)
      fCreateFlags |= FCF_SIZEBORDER;
   if (fFrAttr.tasklist)
      fCreateFlags |= FCF_TASKLIST;
   if (fFrAttr.vscroll)
      fCreateFlags |= FCF_VERTSCROLL;
   if (fFrAttr.hscroll)
      fCreateFlags |= FCF_HORZSCROLL;
   if (fFrAttr.acceltable)
      fCreateFlags |= FCF_ACCELTABLE;
   if (fFrAttr.shellPos)
   {
      fCreateFlags |= FCF_SHELLPOSITION;
      fShellPos = TRUE;
   }

   fcdata.cb = sizeof(FRAMECDATA);
   fcdata.flCreateFlags = fCreateFlags;
   fcdata.hmodResources = (HMODULE)NULL;
   fcdata.idResources = fId;
 
   hwnd = WinCreateWindow(
                HWND_DESKTOP,
                WC_FRAME,
                (PSZ)fTitle,
                0,0,0,0,0,
                NULL, HWND_TOP,
                fId,
                &fcdata,
                NULL);

   if (hwnd != (HWND)NULL)
   {
      WinSetWindowULong(hwnd,0,(ULONG)this);

      fOldWindProc = WinSubclassWindow(hwnd, (PFNWP)getWindowProc());
      if (fOldWindProc==NULL)
      {
         WinDestroyWindow(hwnd);	
         return FALSE;
      }
      if (! fShellPos)
      {
         setWindowPosition(fFrAttr.x, fFrAttr.y);
         setWindowSize(fFrAttr.width, fFrAttr.height);
      }
      return TRUE;
   }
   return FALSE;
}


//-------------------------------------------------------------------
//   getClassName
const char *TFrameWindow::getClassName()
{
   return "TFrameWindow";
}


//-------------------------------------------------------------------
//   setIcon
void TFrameWindow::setIcon(HPOINTER icon)
{
   WinSendMsg(getHWND(), WM_SETICON, (MPARAM)icon, NULL);

}

//-------------------------------------------------------------------
//   setFrameTitle
void TFrameWindow::setTitle(char *title)
{
   WinSetWindowText(hwnd, (PSZ)title);

}



//-------------------------------------------------------------------
//   maximize
void TFrameWindow::maximize()
{
   SWP swpCurr;
   WinQueryWindowPos(getHWND(), &swpCurr);
   WinSetWindowPos(getHWND(), (HWND)NULL, swpCurr.x, swpCurr.y,
                        swpCurr.cx, swpCurr.cy, SWP_MAXIMIZE | 
                        SWP_SIZE | SWP_MOVE);
}


//-------------------------------------------------------------------
//   minimize
void TFrameWindow::minimize()
{
   SWP swpCurr;
   WinQueryWindowPos(getHWND(), &swpCurr);
   WinSetWindowPos(getHWND(), (HWND)NULL, swpCurr.x, swpCurr.y,
                        swpCurr.cx, swpCurr.cy, SWP_MINIMIZE | 
                        SWP_SIZE | SWP_MOVE );
}



//-------------------------------------------------------------------
//  doCommand
void TFrameWindow::doCommand(WinMsg wm)
{
   WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  doCommand
void TFrameWindow::doControl(WinMsg wm)
{
   WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


void TFrameWindow::doInitMenu(WinMsg wm)
{
   WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}

//-------------------------------------------------------------------
//  getHWNDframe
HWND TFrameWindow::getHWND()
{
   return hwnd;
}


//-------------------------------------------------------------------
//  WndProc
MRESULT TFrameWindow::WndProc(HWND hWnd, ULONG Message, MPARAM mParam1, MPARAM mParam2 )
{
   HPS ps;
   RECTL rcl;
   WinMsg msg;
   msg.hwnd = hWnd;
   msg.msg = Message;
   msg.mp1 = mParam1;
   msg.mp2 = mParam2;

   if (Message == WM_COMMAND)
   {
      doCommand(msg);
      return (MRESULT)FALSE;
   }
   else if (Message == WM_CONTROL)
   {
      doControl(msg);
      return (MRESULT)FALSE;
   }
   else if (Message == WM_INITMENU)
   {
      doInitMenu(msg);
      return (MRESULT)FALSE;
   }
   else
     return (MRESULT)(*fOldWindProc)(hWnd, Message, mParam1, mParam2);

   return (MRESULT)(*fOldWindProc)(hWnd, Message, mParam1, mParam2);
}


//----------------------------------------------------------
//  getClientArea
BOOL TFrameWindow::getClientArea(PRECTL prectl)
{
   RECTL frameRct, tbRct;

   if (WinQueryWindowRect(WinWindowFromID(hwnd, FID_TITLEBAR), &tbRct))
      if (WinQueryWindowRect(hwnd, &frameRct))
  {

      prectl->xLeft = frameRct.xLeft;
      prectl->yBottom = frameRct.yBottom;
      prectl->xRight = frameRct.xRight;
      prectl->yTop = frameRct.yTop - tbRct.yTop-2;
      return TRUE;
   }
   return FALSE;
}

//----------------------------------------------------------
//  enableMenuItem
void TFrameWindow::enableMenuItem(ULONG menuItemId)
{
   WinEnableMenuItem(WinWindowFromID(this->getHWND(),FID_MENU),
                         menuItemId, TRUE);
}

//----------------------------------------------------------
//  disableMenuItem
void TFrameWindow::disableMenuItem(ULONG menuItemId)
{
   WinEnableMenuItem(WinWindowFromID(this->getHWND(),FID_MENU),
                         menuItemId, FALSE);
}
