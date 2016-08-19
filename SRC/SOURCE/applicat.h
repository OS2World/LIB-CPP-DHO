/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: applicat.h 1.7 1995/08/13 03:21:12 teb Exp $ */

#ifndef __APPLICAT_H__
#define __APPLICAT_H__

#define INCL_GPI
#define INCL_WIN
#include <os2.h>
#include <object.h>
#include <process.h>
#include <window.h>
#include <dtopwin.h>

class TApplication : public TObject
{
   protected:
      TProcess *Proc;
      QMSG     QueMsg;
      ULONG fResource;
      TWinBase  *MainWin;
      HINI hin;

      void handleInitError(char *errMsg);

   public:
    TApplication(ULONG resource);
    virtual ~TApplication();
    virtual void init(void);
    void run(void);
    void done(void);
    virtual const char *getClassName(void);
    virtual void CreateMainWindow(void);
    HAB getAnchorBlock(void);
    TWinBase *getMainWindow(void);
    BOOL openINIfile(char* fname);
    void closeINIfile();
    void writeINIdata(char* section, char* index, PVOID val, ULONG size);
    PULONG inqINIdataSize(char* section, char* index);
    BOOL getINIdata(char* section, char* index, PVOID buf, ULONG size);

};

extern TApplication *Application;
extern TDesktopWindow *DesktopWin;

#endif /* applicat.h */
