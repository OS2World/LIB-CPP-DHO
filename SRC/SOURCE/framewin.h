/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: framewin.h 1.9 1995/08/21 05:50:47 teb Exp $ */

#ifndef __FRAMEWIN_H__
#define __FRAMEWIN_H__

#define INCL_PM
#define INCL_WIN
#define INCL_GPI
#include <os2.h>             
#include<window.h>


struct TFrameWindowAttr
{
   BOOL titlebar;
   BOOL sysmenu;
   BOOL menu;
   BOOL icon;
   BOOL minbutton;
   BOOL maxbutton;
   BOOL sizeborder;
   BOOL tasklist;
   BOOL vscroll;
   BOOL hscroll;
   BOOL acceltable;
   BOOL shellPos;
   ULONG x;
   ULONG y;
   ULONG width;
   ULONG height;
};


class TFrameWindow : public TWindow
{
   protected:
     ULONG fCreateFlags;
     char *fTitle;
     ULONG fX, fY, fcX, fcY;
     HWND hwndClient;
     BOOL fShellPos;
     FRAMECDATA fcdata;
     PFNWP fOldWindProc;

   public:
      TFrameWindowAttr fFrAttr;

      TFrameWindow(ULONG id, char *title);
      virtual ~TFrameWindow();
      virtual BOOL init();
      virtual const char *getClassName();
      BOOL getClientArea(PRECTL prectl);

      void setIcon(HPOINTER icon);
      void setTitle(char *title);

      void maximize();
      void minimize();

      virtual void doCommand(WinMsg wm);
      virtual void doControl(WinMsg wm);
      virtual void doInitMenu(WinMsg wm);
      virtual HWND getHWND();
      virtual MRESULT WndProc(HWND hWnd, ULONG Message,
                                   MPARAM mParam1, MPARAM mParam2);
      void enableMenuItem(ULONG menuItemId);
      void disableMenuItem(ULONG menuItemId);
};


#endif


