/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: simple.cc 1.3 1995/08/29 19:16:49 teb Exp $ */

//============================================
//
//   This application shows a minimal DHO application
//   It uses a non-modal dialog as a main window.
//
//============================================

//  DHO Includes
#include<applicat.h>
#include<nmdlog.h>
#include<moddlog.h>

#include"simple.h"


//=====================================================
//
//   Class Declarations
//
//=====================================================


//----------------------------------------------------
//   The Main Application Object
class TSimpleApp : public TApplication
{

   public:
      TSimpleApp(ULONG);
      virtual void CreateMainWindow();

};


//----------------------------------------------------
//   This class is the main window.
class TMainDialog: public TNonModalDialog
{
   public:
     TMainDialog(ULONG resource):TNonModalDialog(resource) {;};
     virtual void doCommand(WinMsg wm);
};



//=====================================================
//
//   Class Definitions
//
//=====================================================

//----------------------------------------------------
//  TSimpleApp
TSimpleApp::TSimpleApp(ULONG resource):
   TApplication(resource)
{


}


//=====================================================
//
//   Class Definitions
//
//=====================================================

//----------------------------------------------------
//  CreateMainWindow
void TSimpleApp::CreateMainWindow()
{
   MainWin = new TMainDialog(fResource);
}


//=====================================================
//
//   Class Definitions
//
//=====================================================

//----------------------------------------------------
//  doCommand
void TMainDialog::doCommand(WinMsg wm)
{
   SHORT command = SHORT1FROMMP(wm.mp1);
   if (command == ID_ABOUT)
   {
         TModalDialog dlog(ID_DLOGABOU,this, NULL);
         dlog.init();
         dlog.Execute();
   }
   else if (command == ID_QUIT)
   {
      WinPostMsg(wm.hwnd, WM_QUIT, 0,0);
   }
}


//=====================================================
//  program entry point
INT main(void)
{
   TSimpleApp app(ID_MAIN);
   app.init();
   app.run();
   return 0;
}
