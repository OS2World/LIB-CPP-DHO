/* Developer Helper Object Set, (C) 1994 Thomas E. Bednarz, Jr.
    All rights reserved */

/* $Id: wintest.cc 1.3 1995/08/27 00:17:22 teb Exp teb $    */

 /* ****************************************************
        This sample program illustrates the use of the List Box
        CUA interface object, as well as basic use of the non-
        modal dialog box as the main window of an application 
        and the use of modal dialog boxes to obtain information.

        (c) 1995 Tom Bednarz
     ****************************************************
  */

#include<mainwin.h>
#include<applicat.h>

//=====================================================
//
//   Class Declarations
//
//=====================================================

//--------------------------------------------------
//  this class is the frame window's client window 
class TTestClientWin : public TWindow
{
      SHORT sPageX, sPageY;
   public:
      TTestClientWin(ULONG id, TWinBase *parent):
           TWindow(id, parent) {;};
      virtual void paintWindow(HPS ps, RECTL rcl);
      virtual void doSize(WinMsg wm);
};


//--------------------------------------------------
//  this is the main frame window class
class TTestFrame : public TMainWindow
{
   public:
      TTestFrame(ULONG res, char *title) : TMainWindow(res, title)
          {fShellPos = TRUE;};
      ~TTestFrame(){ ;};
      virtual BOOL init();
};


//--------------------------------------------------
//  this is the main application object class
class TTestApp : public TApplication
{

   public:
      TTestApp(ULONG x): TApplication ( x){;};
      virtual void CreateMainWindow(){   MainWin = new TTestFrame(
                fResource, "Window Demo");}
};



//=====================================================
//
//   Class Declarations
//
//=====================================================
//--------------------------------------------------
//  doPaint
void TTestClientWin::paintWindow(HPS ps, RECTL rcl)
{
   POINTL ptl;
   SHORT w;

   if ((sPageX == 0) && (sPageY == 0))         
   {
      sPageX = rcl.xRight - rcl.xLeft;
      sPageY = rcl.yTop - rcl.yBottom; 
   }

   if (sPageX > sPageY)
      w = sPageY / 2;
   else
      w = sPageX / 2;         

   rcl.xLeft = (sPageX/2) -(w/2);
   rcl.xRight = rcl.xLeft +w;
   rcl.yBottom = (sPageY /2) -(w/2);
   rcl.yTop = rcl.yBottom+w;

   WinFillRect(ps, &rcl, CLR_BLUE);
}


//--------------------------------------------------
//  doSize
void TTestClientWin::doSize(WinMsg wm)
{
   sPageX = SHORT1FROMMP(wm.mp2);
   sPageY = SHORT2FROMMP(wm.mp2);
}


//--------------------------------------------------
//  init
BOOL TTestFrame::init()
{
   if (TFrameWindow::init())
   {
      setIcon(WinQuerySysPointer(HWND_DESKTOP, 
              SPTR_ICONINFORMATION, FALSE));
      TTestClientWin *client = new TTestClientWin(FID_CLIENT, this);
      return client->init();
   }
   return FALSE;
}


//==================================================
//  program entry point
INT main(void)
{
   TTestApp mw(100);
   mw.init();
   mw.run();
   return 0;
}
