/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: mainwin.h 1.6 1995/08/21 05:43:49 teb Exp $ */

#ifndef __MAINWIN_H__
#define __MAINWIN_H__


#include<framewin.h>


#define cm_FileOpen 101
#define cm_FileSaveAs 102

class TMainWindow: public TFrameWindow
{
   protected:
      CHAR *fExtension;
   public:
     TMainWindow(ULONG resource, char* title);
     virtual ~TMainWindow();
     virtual void doCommand(WinMsg wm);
     virtual const char *getClassName(void);
     void doFileOpen();
     void readFile();
     void doFileSave();
     void writeFile();
     CHAR *getFileExtension();
     void setFileExtension(CHAR *ext);
};
#endif

