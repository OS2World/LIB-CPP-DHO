/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: window.h 1.10 1995/08/26 22:45:28 teb Exp $ */


#ifndef __WINDOW_H__
#define __WINDOW_H__

#define INCL_PM
#define INCL_WIN
#define INCL_GPI
#include <os2.h>             
#include"winbase.h"


#define WC_DHOWINDOW "DevHlprWindow"

class TWindow: public TWinBase
{
   protected:
     TWinBase *fParent;
     ULONG fId;
     ULONG width, height;
     PFNWP oldWndProc;

     virtual void Register();

     // painting management functions
     void BeginPaint(HPS &hps, RECTL &rcl);
     void EndPaint(HPS hps);
     HPS GetPS();
     void ReleasePS(HPS hps);
     PFNWP getWindowProc();

   public:
     static BOOL fInitialized ;
     TWindow( ULONG id ,TWinBase *parent);
     virtual ~TWindow();
     virtual BOOL init();
     void ShowWindow();
     void HideWindow();
     BOOL Update(void) ;
     virtual const char *getClassName(void);

     HWND GetClient(void);
     void setTitle(char* title);

     virtual void paintWindow(HPS ps, RECTL rcl);

// Presentation Manager Window Proc Command things
     virtual MRESULT WndProc(HWND hWnd, ULONG Message,
                                  MPARAM mParam1, MPARAM mParam2);
     virtual void doCommand(WinMsg wm);
     virtual void doControl(WinMsg wm);
     virtual void doDestroy(WinMsg wm);
     virtual void doClose(WinMsg wm);
     virtual void doPaint(WinMsg wm);
     virtual void doSize(WinMsg wm);
     virtual void doRealizePallette(WinMsg wm);
     virtual void doHelp(WinMsg wm);
     virtual void doActivate(WinMsg wm);
     virtual void doChar(WinMsg wm);
     virtual void doButton1Up(WinMsg wm);
     virtual void doButton1Down(WinMsg wm);
     virtual void doButton1DblClick(WinMsg wm);
     virtual void doButton2Up(WinMsg wm);
     virtual void doButton2Down(WinMsg wm);
     virtual void doButton2DblClick(WinMsg wm);
     virtual void doButton3Up(WinMsg wm);
     virtual void doButton3Down(WinMsg wm);
     virtual void doButton3DblClick(WinMsg wm);
     virtual void doAdjustWindowPos(WinMsg wm);
     virtual void doTimer(WinMsg wm);
     virtual void doSetFocus(WinMsg wm);
};



#endif

