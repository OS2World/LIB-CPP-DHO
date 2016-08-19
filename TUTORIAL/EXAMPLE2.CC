/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: example2.cc 1.1 1995/08/30 01:40:11 teb Exp $ */

/*******************************************
 *   Example2.cc 
 * 
 *   This example demonstrates how to customize
 *   an application object, specifically how to modify
 *   the type of main window for the application
 *******************************************/

//DHO application object header file
#include<applicat.h>
#include<framewin.h>

#define kAppId 100


class TExampleApp : public TApplication
{
   public:
      TExampleApp(ULONG res):TApplication(res){;};
      virtual void CreateMainWindow()
      {
         MainWin=new TFrameWindow(fResource, "DHO Tutorial App");
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