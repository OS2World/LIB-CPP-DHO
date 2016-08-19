/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: applicat.cc 1.8 1995/08/29 18:16:09 teb Exp $ */


#include<applicat.h>
#include<framewin.h>
#include<stdlib.h>

TApplication *Application;  
TDesktopWindow *DesktopWin;



//-------------------------------------------------------------------
//   openINIfile
HINI TApplication::openINIfile(char* fname)
{
   hin = PrfOpenProfile (getAnchorBlock(), (PSZ)fname); 
   return (hin != (HINI)NULL);
}


//-------------------------------------------------------------------
//   closeINIfile
void TApplication::closeINIfile()
{
   PrfCloseProfile(hin);    
}



//-------------------------------------------------------------------
//   writeINIdata
void TApplication::writeINIdata(char* section, char* index, PVOID val, 
                                ULONG size)
{
   if (hin != (HINI)NULL)
      PrfWriteProfileData(hin, (PSZ)section, (PSZ)index, val, size);
}


//-------------------------------------------------------------------
//   inqINIdataSize
PULONG TApplication::inqINIdataSize(char* section, char* index)
{
   PULONG res = 0;
   if (hin != (HINI)NULL)
      
      PrfQueryProfileSize(hin, (PSZ)section, (PSZ)index, res);
   return res;
}


//-------------------------------------------------------------------
//   getINIdata
BOOL TApplication::getINIdata(char* section, char* index,
                              PVOID buf, ULONG size)
{
   return PrfQueryProfileData(hin, (PSZ)section, 
                              (PSZ)index, buf, &size);
}


//-------------------------------------------------------------------
//   TApplication
TApplication::TApplication(ULONG resource)
{   
   Application = this;
   DesktopWin = NULL;
   Proc = new TProcess;
   fResource = resource;
   if (Proc==NULL)
   {
#ifdef DEBUG
      WinMessageBox(HWND_DESKTOP,HWND_DESKTOP, 
         (PSZ)"Couldn't create Process Object", 
         (PSZ)"Error!",0, MB_MOVEABLE | MB_CANCEL ); 
#endif
      exit(1);
   }
   MainWin=NULL;
}



//-------------------------------------------------------------------
//   ~TApplication
TApplication::~TApplication()
{   
   if (DesktopWin)
      delete DesktopWin;
}


//-------------------------------------------------------------------
//   init
void TApplication::init(void)
{
   CreateMainWindow();
   if (MainWin!=NULL)
   {
       if (!MainWin->init())
            handleInitError("Couldn't create Window Frame");
       else
       {
          MainWin->shellSetPosition();
          MainWin->showWindow();
       }
       DesktopWin=new TDesktopWindow;
       if (!DesktopWin->init())
          DesktopWin=NULL;
   }
   else
      handleInitError("Couldn't create Window Object");
}


//-------------------------------------------------------------------
//   run
void TApplication::run(void)
{
   //  Standard message processing loop. WinGetMsg returns FALSE if the  
   //  returned message is WM_QUIT.  Returns TRUE for all other messages 

      while (WinGetMsg(Proc->getAnchorBlock(), &QueMsg, HMODULE(NULL),0,0))
         WinDispatchMsg(Proc->getAnchorBlock(), &QueMsg);

}
 

//-------------------------------------------------------------------
//   done
void TApplication::done(void)
{
   if (MainWin!=NULL)
      delete(MainWin);
   if (Proc!=NULL)
      delete(Proc);
}

//-------------------------------------------------------------------
//   CreateMainWindow
void TApplication::CreateMainWindow(void)
{
   MainWin = new TFrameWindow(fResource, "Standard Window");
}

//-------------------------------------------------------------------
//   getClassName
const char *TApplication::getClassName(void)
{
   return "TApplication";
}

//-------------------------------------------------------------------
//   getAnchorBlock
HAB TApplication::getAnchorBlock()
{
   return Proc->getAnchorBlock();
}

//-------------------------------------------------------------------
//   getMainWindow
TWinBase *TApplication::getMainWindow(void)
{
   return MainWin;  
}


//-------------------------------------------------------------------
//   handleInitError
void TApplication::handleInitError(char *errMsg)
{
#ifdef DEBUG
      WinMessageBox(HWND_DESKTOP,HWND_DESKTOP, 
         (PSZ)errMsg,
         (PSZ)"Error!",0, MB_MOVEABLE | MB_CANCEL ); 
#endif
      exit(1);
}
