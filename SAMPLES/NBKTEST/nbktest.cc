/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: nbktest.cc 1.3 1995/08/25 08:31:59 teb Exp teb $    */

/***********************************************
 *  This demo illustrates basic DHO concepts
 *  as well as the use of the DHO wrapper 
 *  around the CUA'91 notebook control.
 ***********************************************/



#include<applicat.h>
#include<mainwin.h>
#include<notebk.h>
#include<contain.h>
#include<moddlog.h>
#include<radiobtn.h>
#include<edittext.h>
#include<stdio.h>

#include"nbktest.h"


static int pageNo = 0;
static ULONG colNo = 1L;
static ULONG pageCnt=0;
char *aboutText="Developer Helper Sample App\n (c) 1994-95 Tom Bednarz\n     All Rights Reserved.";
char *aboutTitle="Product Information";



//=====================================================
//
//   Class Declarations
//
//=====================================================


//---------------------------------------------------
//  the window is the object which defines the pacges which
//  are inserted into the notebook control
class TPageWindow : public TWindow
{
      SHORT sPageX, sPageY;
      ULONG color;
   public:
      TPageWindow(ULONG id, TWinBase *parent);
      virtual ~TPageWindow(){;};
      virtual void paintWindow(HPS ps, RECTL rcl);
      virtual void doSize(WinMsg wm);
};



//----------------------------------------------------
//  this dialog is the object which defines the 
//  type of page which is to be inserted into the 
//  notebook control
class TAddPageDlog : public TModalDialog
{ 

      TRadioButton *fBtns;
      TEditText    *fTabText, *fSLtext;
   public:
      TAddPageDlog(ULONG res, TWinBase *parent);
      ~TAddPageDlog();
      virtual BOOL init();
      void getSettings(tabStyle &style, char *buf, ULONG bufLen, 
                       char *tt, ULONG bl2);
      virtual void doControl(WinMsg wm);
};



//----------------------------------------------------
//  This is the dialog class which is called at
//  application startup to define the type of the
//  notebook control to be created
class TNBKStngsDlog : public TModalDialog
{
      TRadioButton *fBindBtn, *fIntBtn;
   public:
      TNBKStngsDlog(ULONG res, TWinBase *parent);
      virtual ~TNBKStngsDlog();
      virtual BOOL init();
      void getSettings(binding &bnd, bindSide &side);
};


//----------------------------------------------------
//   This is the main frame window class
class TNBKTestWin : public TMainWindow
{
      TNotebook *fNotebook;
   public:
      TNBKTestWin(ULONG resource, char* title);
      virtual BOOL init();
      virtual void doCommand(WinMsg wm);
};


//----------------------------------------------------
//  this is the application class
class TNBKTestApp : public TApplication
{

   public:
      TNBKTestApp(ULONG x): TApplication ( x){;};
      virtual void CreateMainWindow();
};


//=====================================================
//
//   Class Definitions
//
//=====================================================
//----------------------------------------------------
//  TPageWindow
TPageWindow::TPageWindow(ULONG id, TWinBase *parent):
   TWindow(id, parent)
{
   color = colNo;
   if (colNo ==15) 
      colNo=1;
   else 
      colNo++;
};

//----------------------------------------------------
//  doPaint
void TPageWindow::paintWindow(HPS ps, RECTL rcl)
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

   WinFillRect(ps, &rcl, color);
};


//----------------------------------------------------
//  doSize
void TPageWindow::doSize(WinMsg wm)
{
   sPageX = SHORT1FROMMP(wm.mp2);
   sPageY = SHORT2FROMMP(wm.mp2);
}


//----------------------------------------------------
//  TAddPageDlog
TAddPageDlog::TAddPageDlog(ULONG res, TWinBase *parent):
    TModalDialog(res, parent, NULL)
{
   fBtns = NULL;
   fTabText = NULL;
   fSLtext = NULL;
}


//----------------------------------------------------
//  ~TAddPageDlog
TAddPageDlog::~TAddPageDlog()
{
   if (fBtns)
      delete fBtns;
   if (fTabText)
      delete fTabText;
   if (fSLtext)
      delete fSLtext;
}

//----------------------------------------------------
//  init
BOOL TAddPageDlog::init()
{
   char buffer[50];
   if (TModalDialog::init())
   {
      fBtns = new TRadioButton(this, kTabBtn);

      fTabText = new TEditText(this, kEditText);
      sprintf(buffer, "%s-%d", "Tab Number-", ++pageNo);
      fTabText->setControlText((PCH)buffer);
      fSLtext = new TEditText(this, kEditText+1);
      fSLtext->setControlText((PCH)buffer);
      fTabText->disable();
      return TRUE;
   }         
   return FALSE;
}


//----------------------------------------------------
//  getSettings
void TAddPageDlog::getSettings(tabStyle &style, char *buf, ULONG bufLen, char *tt, ULONG bl2)
{
   ULONG sel = fBtns->getGroupSelection();
   if (sel == 0)
      style = tabNone;
   else if (sel == 1)
      style = tabMajor;
   else
      style = tabMinor;
         
   fTabText->getControlText((PCH)buf, bufLen);
   fSLtext->getControlText((PCH)tt, bl2);
}


//----------------------------------------------------
//  doControl
void TAddPageDlog::doControl(WinMsg wm)
{
   if (fBtns)
   {
      if (fBtns->getGroupSelection() == 0)
      {
         fTabText->disable();
      }
      else
      {
        fTabText->enable();
      }
   }
}


//----------------------------------------------------
//  TNBKStngsDlog
TNBKStngsDlog::TNBKStngsDlog(ULONG res, TWinBase *parent):
    TModalDialog(res, parent, NULL)
{
   fBindBtn = fIntBtn = NULL;
}


//----------------------------------------------------
//  ~TNBKStngsDlog
TNBKStngsDlog::~TNBKStngsDlog()
{
   if (fBindBtn)
      delete fBindBtn;
   if (fIntBtn)
      delete fIntBtn;
}



//----------------------------------------------------
//  init
BOOL TNBKStngsDlog::init()
{
   if (TModalDialog::init())
   {
      fBindBtn = new TRadioButton(this, kSpBbtn);
      fBindBtn->clickButton();
      fIntBtn = new TRadioButton(this, kSoBtn);            
      fIntBtn->clickButton();
        
      return TRUE;
   }
   return FALSE;
}




//----------------------------------------------------
//  getSettings
void TNBKStngsDlog::getSettings(binding &bnd, bindSide &side)
 {
    LONG sel;
    sel = fBindBtn->getGroupSelection();
    if (sel == 0)
        bnd = spiral;
    else
        bnd = solid;
   sel = fIntBtn->getGroupSelection();
   if (sel == 0)
      side = bnd_right;
   else if (sel == 1)
      side = bnd_bottom;
   else if (sel == 2)
      side = bnd_top;
   else 
      side = bnd_left;
}



//----------------------------------------------------
//  TNBKTestWin
TNBKTestWin ::TNBKTestWin(ULONG resource, char* title):
       TMainWindow(resource, title)
{
   fFrAttr.menu = TRUE;
   fShellPos = TRUE;
}



//----------------------------------------------------
//  init
BOOL TNBKTestWin::init()
{
   if (!TMainWindow::init())
      return FALSE;
   TNBKStngsDlog iniParmDlog(200, this);
   iniParmDlog.init();
   iniParmDlog.Execute();           
   fNotebook = new TNotebook(FID_CLIENT, this);
   if (fNotebook)
   {
      char sline[50], tab[50];
      tabStyle style;
      TPageWindow *new_page;

      binding bndStyle;
      bindSide bndSide;
      iniParmDlog.getSettings(bndStyle,bndSide);
              
      fNotebook->fNBKattrs.fBindingStyle = bndStyle;
      fNotebook->fNBKattrs.fBindingSide = bndSide;
      fNotebook->init();
      fNotebook->setMajorTabSize(50,25);
      fNotebook->setMinorTabSize(40,25);

      fNotebook->showWindow();
   }
   setIcon(WinQuerySysPointer(HWND_DESKTOP, 
           SPTR_ICONQUESTION, FALSE));

   WinEnableMenuItem(WinWindowFromID(this->getHWND(),FID_MENU), 
                     cRemovePageFirst, FALSE);
   WinEnableMenuItem(WinWindowFromID(this->getHWND(),FID_MENU), 
                     cRemovePageLast, FALSE);

   return TRUE;
}



//----------------------------------------------------
//  doCommand
void TNBKTestWin::doCommand(WinMsg wm)
{
   SHORT command = SHORT1FROMMP(wm.mp1);
   if (command == kQuit)
   {
      WinPostMsg(wm.hwnd, WM_QUIT, 0,0);
   }
   else if (command == cAddPageFirst)
   {
      char sline[50], tab[50];
      tabStyle style;
      TPageWindow *new_page;

      TAddPageDlog setup(300, this);
      setup.init();
      if (setup.Execute() == MBID_OK)
      {
         setup.getSettings(style,sline,50, tab, 50);
         new_page = new TPageWindow(900, this);
         new_page->init();

         if (style == tabNone)
            fNotebook->insertPageFirst(new_page);
         else
            fNotebook->insertPageFirst(new_page, style, sline);
         pageCnt++;
      }
      if (pageCnt == 1)
      {
         WinEnableMenuItem(WinWindowFromID(this->getHWND(),FID_MENU), 
                           cRemovePageFirst, TRUE);
         WinEnableMenuItem(WinWindowFromID(this->getHWND(), FID_MENU), 
                           cRemovePageLast, TRUE);
      }
   }
   else if (command == cAddPageLast)
   {
      char sline[50], tab[50];
      tabStyle style;

      TAddPageDlog setup(300, this);
      setup.init();
      if (setup.Execute() == MBID_OK)
      {
         setup.getSettings(style,sline,50, tab, 50);
         if (style == tabNone)
            fNotebook->insertPageLast(NULL);
         else
            fNotebook->insertPageLast(NULL, style, sline);
         pageCnt++;
      }
      if (pageCnt == 1)
      {
         WinEnableMenuItem(WinWindowFromID(this->getHWND(),FID_MENU), 
                           cRemovePageFirst, TRUE);
         WinEnableMenuItem(WinWindowFromID(this->getHWND(), FID_MENU), 
                           cRemovePageLast, TRUE);
      }
   }
   else if (command == cRemovePageFirst)
   {
      if (pageCnt)
      {
         fNotebook->deleteFirstPage();
         pageCnt--;
      }
      if (pageCnt == 0)
      {
         WinEnableMenuItem(WinWindowFromID(this->getHWND(),FID_MENU), 
                           cRemovePageFirst, FALSE);
         WinEnableMenuItem(WinWindowFromID(this->getHWND(), FID_MENU), 
                           cRemovePageLast, FALSE);
      }
   }
   else if (command == cRemovePageLast)
   {
      if (pageCnt)
      {
         fNotebook->deleteLastPage();
         pageCnt--;
      }
      if (pageCnt == 0)
      {
         WinEnableMenuItem(WinWindowFromID(this->getHWND(),FID_MENU), 
                           cRemovePageFirst, FALSE);
         WinEnableMenuItem(WinWindowFromID(this->getHWND(), FID_MENU), 
                           cRemovePageLast, FALSE);
      }
   }
   else if (command == cProductInfo)
   {
      WinMessageBox(HWND_DESKTOP, hwnd, (PSZ)aboutText, 
             (PSZ)aboutTitle, 0, MB_MOVEABLE | MB_OK 
             | MB_ICONEXCLAMATION);
   }
}


//----------------------------------------------------
//  CreateMainWindow
void TNBKTestApp::CreateMainWindow()
{   
   MainWin = new TNBKTestWin (100, "Notebook Control Test Program");
}



//=====================================================
//  program entry point
INT main(void)
{
   TNBKTestApp app(100);
   app.init();
   app.run();
   return 0;
}
