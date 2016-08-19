/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: vset2.cc 1.2 1995/08/21 03:43:58 teb Exp $    */

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
      fVset = new TValueSet(FID_CLIENT, this, 3,3);
      fVset->fVSetAttr.items = colors;
      
      if (fVset)
      {
         fVset->init();
         fVset->setItem(1,1,MPFROMLONG(0x00000040));
         fVset->setItem(1,2,MPFROMLONG(0x00004000));
         fVset->setItem(1,3,MPFROMLONG(0x00400000));
         fVset->setItem(2,1,MPFROMLONG(0x0000007F));
         fVset->setItem(2,2,MPFROMLONG(0x00007F00));
         fVset->setItem(2,3,MPFROMLONG(0x007F0000));
         fVset->setItem(3,1,MPFROMLONG(0x000000FF));
         fVset->setItem(3,2,MPFROMLONG(0x0000FF00));
         fVset->setItem(3,3,MPFROMLONG(0x00FF0000));              

         setWindowSize(370, 330);

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
