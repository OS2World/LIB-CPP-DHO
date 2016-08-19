/* Developer Helper Object Set, (C) 1994 Thomas E. Bednarz, Jr.
    All rights reserved */

/* $Id: lboxtest.cc 1.2 1995/08/29 19:13:38 teb Exp $    */


 /* ****************************************************
        This sample program illustrates the use of the List Box
        CUA interface object, as well as basic use of the non-
        modal dialog box as the main window of an application 
        and the use of modal dialog boxes to obtain information.

        (c) 1995 Tom Bednarz
     ****************************************************
  */


//----------------------------------------
// includes
#include "applicat.h"
#include "nmdlog.h"
#include"moddlog.h"
#include"slider.h"
#include"edittext.h"
#include"lboxtest.h"
#include"static.h"
#include"listbox.h"
#include"radiobtn.h"

#define INCL_WIN
#define INCL_WINSTDSLIDER
#include<os2.h>
#include<stdlib.h>


#define kInitDlogId   300
#define kLBox         1
#define kComboBox     2
#define kPullDown     3



//=====================================================
//
//   Class Declarations
//
//=====================================================

//--------------------------------------------------
//   this class is for the dialog which prompts the
//   user to enter the text of a new item
class TETModalDialog: public TModalDialog
{
   protected:
      TEditText *fEditText;
      TListBase *fListBox;
   public:
      TETModalDialog(ULONG resource, TWinBase *owner, TListBase *lb);
      ~TETModalDialog();
      virtual BOOL init();
      virtual SHORT doOK(void);
};


//-----------------------------------------------------
//  this dialog prompts the user to enter the new text
//  for an already existing item in the listbox
class TChangeModDlog: public TModalDialog
{
   protected:
      TEditText *fEditText;
      TStaticText *fStaticText;
      TListBase *fListBox;

   public:
      TChangeModDlog(ULONG resource, TWinBase *owner, TListBase *lb);
      ~TChangeModDlog();
      virtual BOOL init();
      virtual SHORT doOK(void);
};



//-----------------------------------------------------
//  this dialog is executed at application startup
//  to obtain the type of list box to be created
class TInitModDlog: public TModalDialog
{
   protected:
      TRadioButton *fRadButt;

   public:
      TInitModDlog(ULONG resource, TWinBase *owner);
      ~TInitModDlog();
      virtual BOOL init();
      LONG getSelection(void);
};




//----------------------------------------------------
//  the main window
class TTestNMDialog: public TNonModalDialog
{
   TListBase *lBox;

   public:
     TTestNMDialog(ULONG resource):TNonModalDialog(resource) {;}
     virtual BOOL init();
     virtual void doCommand(WinMsg wm);
};



//--------------------------------------------------
// the application object
class TTestApp : public TApplication
{

   public:
      TTestApp(ULONG resource): TApplication(resource) {;};
      virtual void CreateMainWindow();
};


//=====================================================
//
//   Class Definitions
//
//=====================================================

//--------------------------------------------------
//  TETModalDialog
TETModalDialog::TETModalDialog(ULONG resource, TWinBase *owner, 
                               TListBase *lb):
   TModalDialog(resource, owner, NULL) 
{
   fEditText = NULL; 
   fListBox = lb;
}


//--------------------------------------------------
// ~TETModalDialog
TETModalDialog::~TETModalDialog() 
{
   delete fEditText;
};


//--------------------------------------------------
// init
BOOL TETModalDialog::init() 
{ 
  if (TModalDialog::init())
  {
     fEditText = new TEditText(this, 201);
     return TRUE;
  }
  return FALSE;
}


//--------------------------------------------------
// doOK
SHORT TETModalDialog::doOK(void)
{
   char* buf = (char*)malloc(sizeof(char)*31);
   fEditText->getControlText((PCH)buf, 30);
   fListBox->addItemLast(buf);
   free(buf);
   return 1;
}


//--------------------------------------------------
// TChangeModDlog
TChangeModDlog::TChangeModDlog(ULONG resource, TWinBase *owner, 
                               TListBase *lb):
   TModalDialog(resource, owner, NULL) 
{
   fEditText = NULL; 
   fListBox = lb; 
}


//--------------------------------------------------
// ~TChangeModDlog
TChangeModDlog::~TChangeModDlog() 
{
   delete fEditText; 
   delete fStaticText;
}
      

//--------------------------------------------------
// init
BOOL TChangeModDlog::init()
{  
   if (TModalDialog::init())
   {
      fEditText = new TEditText(this, kchngEditText);
      fStaticText = new TStaticText(this, kchngStaticText);
      char *itemText = fListBox->getItemAt(
                       fListBox->getSelectedItem());
      fStaticText->setText (itemText);
      delete itemText;
      return TRUE;
   }
   return FALSE;
}


//--------------------------------------------------
// doOK
SHORT TChangeModDlog::doOK(void)
{
   char* buf = (char*)malloc(sizeof(char)*31);
   fEditText->getControlText((PCH)buf, 30);
   fListBox->setItemText (buf,fListBox->getSelectedItem());
   free(buf);
   return 1;
}



//--------------------------------------------------
// TInitModDlog
TInitModDlog::TInitModDlog(ULONG resource, TWinBase *owner):
   TModalDialog(resource, owner, NULL) 
{
   fRadButt = NULL;
}



//--------------------------------------------------
//  ~TInitModDlog
TInitModDlog::~TInitModDlog() 
{
   if (fRadButt)
      delete fRadButt;
}
      


//--------------------------------------------------
// init
BOOL TInitModDlog::init() 
{  
   if (TModalDialog::init())
   {
      fRadButt = new TRadioButton(this, 302);
      fRadButt->clickButton();
      return TRUE;
   }
   return FALSE;
}


//--------------------------------------------------
// getSelection
LONG TInitModDlog::getSelection(void)
{
   return fRadButt->getGroupSelection();
}


//--------------------------------------------------
// init
BOOL TTestNMDialog::init() 
{
   if (TNonModalDialog::init()) 
   {
      if (fResource == 100)
      {
         lBox = new TListBox(this, kListBox);
      }
      else if (fResource == 500)
      {
         lBox = new TComboBox(this, kListBox);
      }
      else
      {
         lBox = new TPullDown(this, kListBox);
      }
      lBox->addItemAt("Item #1",0);
      lBox->addItemAt("Item #2",1);
      return TRUE;
   }
   return FALSE; 
}


//--------------------------------------------------
// doCommand
void TTestNMDialog::doCommand(WinMsg wm)
{
   SHORT command = SHORT1FROMMP(wm.mp1);
   if (command == cAddItem)
      {
         TETModalDialog etDlog(kEnterDlog, this, lBox);
         etDlog.init();
         etDlog.Execute();
      }
   else if (command == cQuit)
      WinPostMsg(wm.hwnd, WM_QUIT, 0,0);
   else if (command == cRemoveItem)
   {
      lBox->deleteItemAt(lBox->getSelectedItem());
   }
   else if (command == cRemoveAll)
   {
      lBox->deleteAll();
   }
   else if (command == cRenameItem)
   {
      TChangeModDlog aDlog(kChangeDlog, this, lBox);
      aDlog.init();
      aDlog.Execute();
   }

}


//--------------------------------------------------
// CreateMainWindow
void TTestApp::CreateMainWindow()
{
   ULONG type, res;

   TInitModDlog iniDlog(kInitDlogId, NULL);
   iniDlog.init();
   iniDlog.Execute();
   type = iniDlog.getSelection();
     
   if (type == 0)
      res = 100;
   else if (type == 1)
      res = 500;
   else
      res = 600;
   MainWin = new TTestNMDialog(res);
}




//===================================================
//  program Entry Point
INT main(void)
{
   TTestApp app(kAppRes);
   app.init();
   app.run();
   return 0;
}
