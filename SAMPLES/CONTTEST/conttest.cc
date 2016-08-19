/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: conttest.cc 1.1 1995/08/15 01:59:53 teb Exp teb $ */

//==============================================
//
//   This sample program illustrates the use of the
//   DHO Container Class TContainerWindow and
//   some other basic DHO functions
//
//==============================================

//   Developer Helper Includes  
#include<mainwin.h>
#include<applicat.h>
#include<contain.h>
#include<pmutils.h>

//  OS/2 API Includes
#define INCL_WIN
#include<os2.h>

#include"conttest.h"

//-----------------------------------------------
//  a global data structure holding all system Icons
//    and their identifiers.
//-----------------------------------------------
IconInfo aIconInfo[NUM_SYS_ICONS] = 
{
   SPTR_ARROW, "SPTR_ARROW",
   SPTR_TEXT, "SPTR_TEXT",
   SPTR_WAIT, "SPTR_WAIT",
   SPTR_SIZE, "SPTR_SIZE",
   SPTR_MOVE, "SPTR_MOVE",
   SPTR_SIZENWSE, "SPTR_SIZENWSE",
   SPTR_SIZENESW, "SPTR_SIZENESW",
   SPTR_SIZEWE, "SPTR_SIZEWE",
   SPTR_SIZENS, "SPTR_SIZENS",
   SPTR_APPICON, "SPTR_APPICON",
   SPTR_ICONINFORMATION, "SPTR_ICONINFORMATION",
   SPTR_ICONQUESTION, "SPTR_ICONQUESTION",
   SPTR_ICONERROR, "SPTR_ICONERROR",
   SPTR_ICONWARNING, "SPTR_ICONWARNING",
   SPTR_ILLEGAL, "SPTR_ILLEGAL",
   SPTR_FILE, "SPTR_FILE",
   SPTR_FOLDER, "SPTR_FOLDER",
   SPTR_MULTFILE, "SPTR_MULTFILE",
   SPTR_PROGRAM, "SPTR_PROGRAM"
};

char *FrameTitle =  "Container Control Test Program";
char *aboutText="Developer Helper Sample App\n (c) 1994-95 Tom Bednarz\n     All Rights Reserved.";
char *aboutTitle="Product Information";


//=====================================================
//
//   Class Declarations
//
//=====================================================



//----------------------------------------------------
//   This class is the main, frame window.
class TContTestWin : public TMainWindow
{
      TContainerWindow *fContainerWindow;

   public:
     TContTestWin(ULONG resource);
     virtual ~TContTestWin();
     virtual BOOL init();

     virtual void doCommand(WinMsg wm);
     virtual void doControl(WinMsg wm);
};

//----------------------------------------------------
//   The Main Application Object
class TContTestApp : public TApplication
{
   public:
      TContTestApp(ULONG resource);
      virtual ~TContTestApp();
      virtual void CreateMainWindow(void);
};

//=====================================================
//
//   Class Definitions
//
//=====================================================

//----------------------------------------------------
//  TContTestWin
TContTestWin::TContTestWin(ULONG resource):
     TMainWindow(resource, FrameTitle)
{
   fContainerWindow = NULL;
}

//----------------------------------------------------
//  ~TContTestWin
TContTestWin::~TContTestWin()
{
   if (fContainerWindow)
      delete fContainerWindow;
}

//----------------------------------------------------
//  init
//     returns TRUE if window initialization is successful,
//     and returns FALSE otherwise
BOOL TContTestWin::init()
{
   if (TMainWindow::init())
   {
      fContainerWindow = new TContainerWindow(FID_CLIENT, this, FALSE);
      if (fContainerWindow->init())
      {
         for (int i = 0; i< NUM_SYS_ICONS; i++)
         {
            fContainerWindow->insertItem( (LONG)aIconInfo[i].iconId,
                                              (PSZ)aIconInfo[i].iconName );
         }
         return TRUE;
      }
   }
   return FALSE;
}


//----------------------------------------------------
//  doCommand
void TContTestWin::doCommand(WinMsg wm)
{
   switch (SHORT1FROMMP(wm.mp1))
   {
      case IDM_ICONVIEW:
         fContainerWindow->setViewType(icon);
      break;
      case IDM_NAME_FLOWED:
         fContainerWindow->setViewType(name_flowed);
      break;
      case IDM_NAME_NONFLOWED:
         fContainerWindow->setViewType(name_nonflowed);
      break;
      case IDM_TEXT_FLOWED:
         fContainerWindow->setViewType(text_flowed);
      break;
      case IDM_TEXT_NONFLOWED:
         fContainerWindow->setViewType(text_nonflowed);
      break;
      case IDM_ADDITEMS:
         fContainerWindow->insertItems((PContainerIconInfo)&aIconInfo,NUM_SYS_ICONS);
      break;
      case IDM_DELETE1:
         fContainerWindow->removeItem(1);
      break;
      case IDM_DELETE2:
         fContainerWindow->removeItem(2);
      break;
      case IDM_DELETE3:
         fContainerWindow->removeItem(3);
      break;
      case IDM_DELETEALL:
         fContainerWindow->removeAll();
      break;
      case IDM_PRODINFO:
            WinMessageBox(HWND_DESKTOP, hwnd, (PSZ)aboutText, 
                   (PSZ)aboutTitle, 0, MB_MOVEABLE | MB_OK 
                   | MB_ICONEXCLAMATION);
      break;
      case IDM_QUIT:
         WinPostMsg(wm.hwnd, WM_QUIT, 0,0);
      break;
   }
}


//----------------------------------------------------
//  doControl
void TContTestWin::doControl(WinMsg wm)
{
   if (SHORT2FROMMP(wm.mp1) == CN_CONTEXTMENU)
       createPopupMenu(this, ID_POPUPMENU, IDM_ICONVIEW);
}


//----------------------------------------------------
//   TContTestApp
TContTestApp::TContTestApp(ULONG resource):
   TApplication(resource)
{

}


//----------------------------------------------------
//
TContTestApp::~TContTestApp()
{

}


//----------------------------------------------------
//   CreateMainWindow
void TContTestApp::CreateMainWindow(void)
{
   MainWin = new TContTestWin(0);
}


//=====================================================
//  program entry point
INT main(void)
{
   TContTestApp app(100);
   app.init();
   app.run();
   return 0;
}
