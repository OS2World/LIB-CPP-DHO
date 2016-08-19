/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: dtopwin.cc 1.3 1995/08/21 05:33:52 teb Exp $ */


#include"dtopwin.h"


//----------------------------------------------------------
//  TDesktopWindow
TDesktopWindow::TDesktopWindow():
   TWinBase(0)
{
   hwnd = HWND_DESKTOP;
}


//----------------------------------------------------------
//  ~TDesktopWindow
TDesktopWindow::~TDesktopWindow()
{

}



//----------------------------------------------------------
//  Init
BOOL TDesktopWindow::init()
{
   return TRUE;
}



//----------------------------------------------------------
//  getClassName
const char *TDesktopWindow::getClassName()
{
   return "TDesktopWindow";
}
      


//----------------------------------------------------------
//  doCommand
void TDesktopWindow::doCommand(WinMsg wm)
{

}




