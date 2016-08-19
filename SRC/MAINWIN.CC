/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: mainwin.cc 1.8 1995/09/03 01:54:17 teb Exp $ */


#include"mainwin.h"
#include<string.h>

//-------------------------------------------------------------------
//   TMainWindow
TMainWindow::TMainWindow( ULONG resource, char* title):
      TFrameWindow(resource, title)
{
   fExtension = "*.*";
   fFrAttr.tasklist=TRUE;
}


//-------------------------------------------------------------------
//   ~TMainWindow
TMainWindow::~TMainWindow()
{

}


//-------------------------------------------------------------------
//   doCommand
void TMainWindow::doCommand(WinMsg wm)
{
   short command = SHORT1FROMMP(wm.mp1);
   if (command == cm_FileOpen)
   {
      doFileOpen();
   }
   else if (command == cm_FileSaveAs)
   {
      doFileSave();
   }
}


//-------------------------------------------------------------------
//   getClassName
const char *TMainWindow::getClassName(void)
{
   return "TMainWindow";
}


//-------------------------------------------------------------------
//   doFileOpen
void TMainWindow::doFileOpen()
{
   FILEDLG FileDlg;
   HWND hwndDlg;

   memset(&FileDlg, 0, sizeof(FILEDLG) );
   FileDlg.cbSize = sizeof(FILEDLG);
   FileDlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_OPEN_DIALOG;
   FileDlg.pszTitle = (PSZ)"Open File";
   strcpy(FileDlg.szFullFile, fExtension);

   hwndDlg = WinFileDlg(HWND_DESKTOP, hwnd, (PFILEDLG)&FileDlg);

   if (hwndDlg && (FileDlg.lReturn == DID_OK))
   {
      readFile(FileDlg.szFullFile);
   }
}


//-------------------------------------------------------------------
//   readFile
void TMainWindow::readFile(char *fname)
{

}


//-------------------------------------------------------------------
//   doFileSave
void TMainWindow::doFileSave()
{
   FILEDLG FileDlg;
   HWND hwndDlg;

   memset(&FileDlg, 0, sizeof(FILEDLG) );
   FileDlg.cbSize = sizeof(FILEDLG);
   FileDlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_SAVEAS_DIALOG;
   FileDlg.pszTitle = (PSZ)"SaveFile";
   strcpy(FileDlg.szFullFile, fExtension);

   hwndDlg = WinFileDlg(HWND_DESKTOP, hwnd, (PFILEDLG)&FileDlg);

   if (hwndDlg && (FileDlg.lReturn == DID_OK))
   {
      writeFile(FileDlg.szFullFile);
   }

}


//-------------------------------------------------------------------
//   writeFile
void TMainWindow::writeFile(char *fname)
{

}



//-------------------------------------------------------------------
//   getFileExtension
CHAR *TMainWindow::getFileExtension()
{
   return fExtension;
}


//-------------------------------------------------------------------
//   setFileExtension
void TMainWindow::setFileExtension(CHAR *ext)
{
   fExtension = ext;
}

