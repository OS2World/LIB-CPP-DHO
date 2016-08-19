/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: example5.cc 1.2 1995/09/03 00:22:49 teb Exp $ */

/*******************************************
 *   Example5.cc 
 * 
 *   This example demonstrates how to add 
 *   a menu to the frame window
 *******************************************/

#define INCL_WIN
#include<os2.h>

//DHO application object header file
#include<applicat.h>
#include<framewin.h>

#define kAppId 100


class TExampleClientWin : public TWindow
{
      SHORT sPageX, sPageY;
   public:
      TExampleClientWin(ULONG id, TWinBase *parent):TWindow(id, parent){;};
      virtual void doSize(WinMsg wm)
      {
         sPageX = SHORT1FROMMP(wm.mp2);
         sPageY = SHORT2FROMMP(wm.mp2);
      }
      virtual void paintWindow(HPS ps, RECTL rcl)
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

         WinFillRect(ps, &rcl, CLR_BLUE);

         rcl.xLeft = (sPageX/2) -(w/2);
         rcl.xRight = rcl.xLeft +w;
         rcl.yBottom = (sPageY /2) -(w/2);
         rcl.yTop = rcl.yBottom+w;

         WinFillRect(ps, &rcl, CLR_YELLOW);
         
      }
};



class TExampleFrameWin : public TFrameWindow
{

   public:
      TExampleFrameWin(ULONG id, char *title):TFrameWindow(id, title)
      {   
         fShellPos = TRUE;
         fFrAttr.menu = TRUE;
         fFrAttr.icon = TRUE;
      };
      virtual BOOL init()
      {
         if (TFrameWindow::init())
         {
            TExampleClientWin *client = new
                TExampleClientWin(FID_CLIENT, this);
            return client->init();
         }
         return FALSE;
      }
};


class TExampleApp : public TApplication
{
   public:
      TExampleApp(ULONG res):TApplication(res){;};
      virtual void CreateMainWindow()
      {
         MainWin=new TExampleFrameWin(fResource, "DHO Tutorial App");
      }
};



//=========================================
//  program entry point
INT main(void)
{
   TExampleApp app(kAppId);

   app.init();     // initialize object
   app.run();      // begin event loop          

   return 0;
}