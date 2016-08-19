/******************************************************
 *   Developer Helper Object Set                                 
 *  (C) 1994-95 Thomas E. Bednarz, Jr.                         
 *    All rights reserved
 *****************************************************/


/* $Id: prgtest.cc 1.4 1995/08/29 19:00:15 teb Exp $ */

/* **********************************************************
 *   this demo shows the use of the Progress Control provided by the
 *   Developer Helper Object Set
 ************************************************************/

#define INCL_DOSDATETIME
#define INCL_DOSPROCESS
#define INCL_WIN
#include<os2.h>

#include<applicat.h>
#include<nmdlog.h>
#include<prgress.h>
#include<framewin.h>
#include"prgtest.h"


//=====================================================
//
//   Class Declarations
//
//=====================================================

//----------------------------------------------------
//   This class is the main window.
class TMainNMDialog: public TNonModalDialog
{
     TProgressBar *bar;

   public:
     TMainNMDialog(ULONG resource):TNonModalDialog(resource) {;};
     virtual ~TMainNMDialog();
     virtual BOOL init();
     virtual void doCommand(WinMsg wm);
};

//----------------------------------------------------
//   this is the main application object
class TPrgTestApp : public TApplication
{

   public:
      TPrgTestApp():TApplication(ID_MAIN){};
      virtual void CreateMainWindow();
};



//=====================================================
//
//   Class Definitions
//
//=====================================================

//----------------------------------------------------
//  ~TMainNMDialog
TMainNMDialog::~TMainNMDialog()
{
   if (bar)
      delete bar;
}


//----------------------------------------------------
//  init
BOOL TMainNMDialog::init()
{
   if (TNonModalDialog::init())
   {
      LONG x, y, cx, cy;
      getWindowPosition(x, y, cx, cy);
      bar = new TProgressBar(999, this, 20, (cy/3)*2, cx-40, 25);
      if (bar)
      {
          bar->init();
          bar->setBackground(CLR_WHITE);
          bar->setForeground(CLR_BLUE);
          bar->setBorder(CLR_DARKGRAY);
          bar->showWindow(); 
          return TRUE;           
      }
    }
    return FALSE;
} 
    

//----------------------------------------------------
//  doCommand
void TMainNMDialog::doCommand(WinMsg wm)
{
   SHORT command = SHORT1FROMMP(wm.mp1);
   if (command == ID_EXIT)
   {
      WinPostMsg(wm.hwnd, WM_QUIT, 0,0);
   }
   else if (command == ID_PROGRESS)
   {
      for (int i=0; i<100; i+=5)
      {
         DosSleep(100);
         bar->setPercentDone(i);
      }
      bar->setPercentDone(100);
   } 
}


//----------------------------------------------------
//  CreateMainWindow
void TPrgTestApp::CreateMainWindow()
{
   MainWin = new TMainNMDialog(fResource);
}


//=====================================================
//  program entry point
INT main(void)
{
   TPrgTestApp app;
   app.init();
   app.run();
   return 0;
}
