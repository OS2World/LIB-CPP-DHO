/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: example3.cc 1.2 1995/08/30 10:52:32 teb Exp $ */

/*******************************************
 *   Example3.cc 
 * 
 *   Example3 demonstrates how to create a 
 *   custom frame window subclass and to
 *   introduce it into a DHO application
 *******************************************/

#define INCL_WIN
#include<os2.h>

//DHO application object header file
#include<applicat.h>
#include<framewin.h>

#define kAppId 100

class TExampleFrameWin : public TFrameWindow
{

   public:
      TExampleFrameWin(ULONG id, char *title):TFrameWindow(id, title)
      {   fShellPos = TRUE;};
      virtual BOOL init()
      {
         if (TFrameWindow::init())
         {   // add a frame icon
            this->setIcon(WinQuerySysPointer(HWND_DESKTOP, 
                    SPTR_ICONINFORMATION, FALSE));
            return TRUE;
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