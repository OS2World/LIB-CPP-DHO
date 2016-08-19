/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: vsettest.cc 1.2 1995/08/15 03:54:33 teb Exp $    */

//==============================================
//
//   This sample program illustrates the use of the
//   DHO Valueset Class ValueSet and
//   some other basic DHO functions
//
//==============================================

//   Developer Helper Includes  
#include<applicat.h>
#include<mainwin.h>
#include<vset.h>

char *FrameTitle = "Value Set Control Test Program";


//=====================================================
//
//   Class Declarations
//
//=====================================================


//----------------------------------------------------
//   This class is the main, frame window.
class TTestWin : public TMainWindow
{
   TValueSet *fVset;
   public:
   TTestWin(ULONG resource, char* title):TMainWindow(resource, title){;};
    virtual BOOL init();
};


//----------------------------------------------------
//   The Main Application Object
class TVSetApp : public TApplication
{
   public:
      TVSetApp(ULONG x): TApplication ( x){;};
      virtual void CreateMainWindow();
};


//=====================================================
//
//   Class Definitions
//
//=====================================================

//----------------------------------------------------
//  init
BOOL TTestWin::init()
{
   if (TMainWindow::init())
   {
      fVset = new TValueSet(FID_CLIENT, this, 7,7);
      if (fVset)
      {
         fVset->init();
         int row=1, col=1;
         for (int i=1; i<=48; i++)
         {
            fVset->setItem(row, col, (void*)WinGetSysBitmap(HWND_DESKTOP, i));
            if (++col >=8)
            {
               col = 1;
               ++row;
            }
         }
         fVset->showWindow();
         return TRUE;
      }
   }
   return FALSE;
}


//----------------------------------------------------
//  CreateMainWindow
void TVSetApp::CreateMainWindow()
{   
   MainWin = new TTestWin (100, FrameTitle);
}


//=====================================================
//  program entry point
INT main(void)
{
   TVSetApp mw(100);
   mw.init();
   mw.run();
}
